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


#define RITARDO 5000 // tempo in [msec] per attraversare la barriera


//codifica dello stato delle barriere
#define SB_EXT_X B00000010 //barriera esterna attraversata
#define SB_INT_X B00000001 //barriera interna attraversata
#define SB_NONE  B00000000 // barriere libere

// LED per eventi Ingresso e uscita
#define LED_SB_INT 7
#define LED_SB_EXT 8

//****************** global variables definition ******************
long int aTime,bTime=0;
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
// TODO
sonarBarries=_t_ReadSonars();
Serial.print("\rRead Sonars: ");
Serial.print(sonarBarries, BIN);
//Serial.print(" loop time[us]= ");
/*bTime=aTime;
aTime=micros();
Serial.print("lt=");
Serial.println(aTime-bTime);
*/
switch (SM_STATUS) {
  case SM_STATUS_L: // stato libero
  Serial.print(F(" ->SM_STATUS_L       "));
    TTV_timer=millis(); //inizializzo Timer attraversamento barriere
    switch (sonarBarries) {
      case SB_EXT_X:
        SM_STATUS=SM_STATUS_PI;
        Serial.println(F("\tSB_EXT_X"));
      break;
      case SB_INT_X:
        SM_STATUS=SM_STATUS_PU;
          Serial.println(F("\tSB_INT_X"));
      break;
      case SB_NONE:
        SM_STATUS=SM_STATUS_L;
      break;

      default:
        SM_STATUS=SM_STATUS_L;
      break;
    }
  break;

  case SM_STATUS_PI: // stato di pre-ingresso
    Serial.print(F(" ->SM_STATUS_PI       "));
    switch (sonarBarries) {
      case SB_EXT_X: // nessun ingresso. Il soggetto è tornato indietro ....
        SM_STATUS=SM_STATUS_L;
        Serial.println(F("SB_EXT_X - Mancato ingresso !"));
      break;
      case SB_INT_X:
        //è avvenuto un ingresso
        contaIngressi++;
        SM_STATUS=SM_STATUS_L;
        Serial.println(F("SB_INT_X - Ingresso-->[]"));
        TxIngresso();
      break;
      case SB_NONE: // in attesa di un attraversamento . .
      //Serial.println(TTV_timer-millis());
      //delay(1000);
        if ((millis()-TTV_timer)>=RITARDO) {
          //il timer attraversamento barriera è scaduto
          //torno nello stato libero
          Serial.println(F("SB_NONE - Timeout scaduto - NO ingresso ! "));
          SM_STATUS=SM_STATUS_L;
        } else {
          // aspetto che il timer scada o ci sia un attraversamento della barriera INTerna
          SM_STATUS=SM_STATUS_PI;
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
      case SB_EXT_X: // è avvenuta una uscita
        contaUscite++;
        Serial.println(F("SB_EXT_X - Uscita[]-->"));
        SM_STATUS=SM_STATUS_L;
      break;
      case SB_INT_X: // nessun ingresso. Il soggetto è tornato indietro ...
        SM_STATUS=SM_STATUS_L;
        Serial.println(F("SB_EXT_X - Mancata uscita !"));
      break;
      case SB_NONE: // in attesa di un attraversamento . . .
          if ((millis()-TTV_timer)>=RITARDO) {
          //il timer attraversamento barriera è scaduto
          //torno nello stato libero
          Serial.println(F("SB_NONE - Timeout scaduto - NO uscita ! "));
          SM_STATUS=SM_STATUS_L;
        } else {
          // aspetto che il timer scada o ci sia un attraversamento della barriera EXTerna
          SM_STATUS=SM_STATUS_PU;
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
// State machine
// Data display and communication

}
