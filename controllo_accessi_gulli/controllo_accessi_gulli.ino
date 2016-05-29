/*
 *********************Arduino Source File Header**************************
__file_name__ = controllo_accessi_gulli.ino
__description__="Gestisce la state machine oper il controllo accessi  attraverso
 le barriere sonar e si connette con un PC esterno (via seriale o Ethernet) per
 comunicare gli aggiornameti degli accessi o condizioni anomale di blocco delle barriere"
__author__ = "Stefano Baldacci"
__copyright__ = "Informazioni di Copyright"
__license__ = "GPL"
__email__ = "stefano.baldacci@gmail.com"
__STATUS__ = "Development[]";"Test[X]";"Production[]";
__branch__= test_SM (SHA1)
__History__: (repeat the following line as many times as applicable)
    __version__ = "0.1 original"
***************************************************************************
*/

//#include "Arduino.h" // libreria per compatibilita con PlatformIO. Vedi www.platformio.org
#include <NewPing.h> // librearia per gestione moduli Sonar HC-SR04

//****************** global variables definition ******************
// Collegamenti moduli Sonar
#define EXT_SONAR_TRIG_PIN 3
#define EXT_SONAR_ECHO_PIN  4
#define INT_SONAR_TRIG_PIN 5
#define INT_SONAR_ECHO_PIN 6
#define MAX_SONAR_DISTANCE 100 //[cm]

// codifica stati della State Machine
#define SM_STATUS_L 1
#define SM_STATUS_PI 2
#define SM_STATUS_PU 3

// tempo in [msec] per attraversare la barriera
#define RITARDO 5000

//codifica dello stato delle barriere sonar
#define SB_EXT_X B00000010 //barriera esterna attraversata
#define SB_INT_X B00000001 //barriera interna attraversata
#define SB_NONE  B00000000 // barriere libere

// LED per eventi Ingresso e uscita
#define LED_SB_INT 7
#define LED_SB_EXT 8

//****************** global variables definition ******************
int contaIngressi=0; // contatore degli avventuti ingressi
int contaUscite=0;  // contatore delle avvenute uscite
byte sonarBarries=B00000000; // così composta -> [0 0 0 0 0 0 extSonar intSonar ]
byte SM_STATUS = SM_STATUS_L;  //stato iniziale  della SM
unsigned long TTV_timer=0; // timer per attraversamento barriera

// oggetti NewPing per la gestione dei moduli sonar
NewPing ext_Sonar(EXT_SONAR_TRIG_PIN,EXT_SONAR_ECHO_PIN,MAX_SONAR_DISTANCE);
NewPing int_Sonar(INT_SONAR_TRIG_PIN,INT_SONAR_ECHO_PIN,MAX_SONAR_DISTANCE);



void setup()
{
Serial.begin(115200);
Serial.println(F("************************************"));
Serial.println(F("GULLI: Controllo Accessi 1.0 Test SW"));
Serial.println(F("************************************"));
delay(5000);
}



void loop()
{
sonarBarries=_t_ReadSonars();
Serial.print("\rRead Sonars: ");
Serial.print(sonarBarries, BIN);

// ************************** STATE MACHINE *******************************//
switch (SM_STATUS) {
  case SM_STATUS_L: // stato libero
  Serial.print(F(" ->SM_STATUS_L       "));
    TTV_timer=millis(); //inizializzo Timer attraversamento barriere
    switch (sonarBarries) { // controllo lo stato delle barriere sonar
      case SB_EXT_X: // rilevato attraversamento barriera esterna
        SM_STATUS=SM_STATUS_PI; // mando la State Machine nello stato di Pre-Ingresso
        Serial.println(F("\tSB_EXT_X"));
      break;
      case SB_INT_X: // rilevato attraversamento barriera interna
        SM_STATUS=SM_STATUS_PU; // mando la State Machine nello stato di Pre-Uscita
          Serial.println(F("\tSB_INT_X"));
      break;
      case SB_NONE: // nessun attraversamento barriera rilevato
        SM_STATUS=SM_STATUS_L; // rimango nello stato Libero
      break;

      default:
        SM_STATUS=SM_STATUS_L;
      break;
    }
  break;

  case SM_STATUS_PI: // stato di pre-ingresso
    Serial.print(F(" ->SM_STATUS_PI       "));
    switch (sonarBarries) {
      case SB_EXT_X: // rilevato attraversamento barriera esterna. Il soggetto è tornato indietro
        SM_STATUS=SM_STATUS_L; // mando la State Machine nello stato di Libero
        Serial.println(F("SB_EXT_X - Mancato ingresso !"));
      break;
      case SB_INT_X: // rilevato attraversamento barriera esterna. E' avvenuto un ingresso
        contaIngressi++; // incremento contatore ingressi
        SM_STATUS=SM_STATUS_L; // torno nello stato Libero
        Serial.println(F("SB_INT_X - Ingresso-->[]"));
        TxIngresso();
      break;
      case SB_NONE: // nessun attraversamento barriera rilevato. In attesa di un attraversamento
        if ((millis()-TTV_timer)>=RITARDO) { // controllo il timer di attraversamento barriera
          //il timer attraversamento barriera è scaduto. Torno nello stato libero
          Serial.println(F("SB_NONE - Timeout scaduto - NO ingresso ! "));
          SM_STATUS=SM_STATUS_L;
        } else {
          // aspetto che il timer scada o ci sia un attraversamento della barriera interna
          SM_STATUS=SM_STATUS_PI; // rimango nello stato di Pre-ingresso fino a che il timer non scade
          Serial.println(F("SB_NONE - In attesa di ingresso "));
        }
      break;
      default:
        SM_STATUS=SM_STATUS_L;
      break;
    }
  break;
  case SM_STATUS_PU: // stato di pre-uscita
    Serial.print(F(" ->SM_STATUS_PU       "));
    switch (sonarBarries) {
      case SB_EXT_X: // rilevato attraversamento barriera esterna. E' avvenuta una uscita
        contaUscite++; // incremento contatore uscite
        Serial.println(F("SB_EXT_X - Uscita[]-->"));
        SM_STATUS=SM_STATUS_L; // torno nello stato Libero
      break;
      case SB_INT_X: // // rilevato attraversamento barriera interna. Il soggetto è tornato indietro
        SM_STATUS=SM_STATUS_L; // torno nello stato Libero
        Serial.println(F("SB_EXT_X - Mancata uscita !"));
      break;
      case SB_NONE: // // nessun attraversamento barriera rilevato. In attesa di un attraversamento
          if ((millis()-TTV_timer)>=RITARDO) {
          //il timer attraversamento barriera è scaduto torno nello stato libero
          Serial.println(F("SB_NONE - Timeout scaduto - NO uscita ! "));
          SM_STATUS=SM_STATUS_L;
        } else {
          // // aspetto che il timer scada o ci sia un attraversamento della barriera esterna
          SM_STATUS=SM_STATUS_PU; // rimango nello stato di Pre-uscita fino a che il timer non scade
          Serial.println(F("SB_NONE - In attesa di uscita "));
        }
      break;
      default:
        SM_STATUS=SM_STATUS_L;
      break;
    }
  break;
  //default:
  break;

}
// ************************** STATE MACHINE *******************************//

// TODO
// Data display and communication

}
