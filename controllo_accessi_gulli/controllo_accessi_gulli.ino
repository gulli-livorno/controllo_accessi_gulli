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
__STATUS__ = "Development[X]";"Test[]";"Production[]";
__History__: (repeat the following line as many times as applicable)
    __version__ = "0.1 original"
***************************************************************************
*/

//#include "Arduino.h" // libreria per compatibilita con PlatformIO. Vedi www.platformio.org
#include <NewPing.h> // librearia per gestione moduli Sonar HC-SR04

//****************** global variables definition ******************
// Collegamenti moduli Sonar
#define EXT_SONAR_TRIG_PIN 3
#define EXT_SONAR_ECHO_PIN  99
#define INT_SONAR_TRIG_PIN 99
#define INT_SONAR_ECHO_PIN 99
#define MAX_SONAR_DISTANCE 100

// codifica stati della State Machine
#define SM_STATUS_Start 0 // in pratica non è usato
#define SM_STATUS_L 1
#define SM_STATUS_PI 2
#define SM_STATUS_PU 3
#define SM_STATUS_I 4
#define SM_STATUS_U 5

#define RITARDO 5000 // tempo in [sec] per attraversare la barriera

//codifica dello stato delle barriere
#define SB_EXT_X 2 //barriera esterna attraversata
#define SB_INT_X 1 //barriera interna attraversata
#define SB_NONE 0 // barriere libere

//****************** global variables definition ******************
int contaIngressi=0; // contatore degli avventuti ingressi
int contaUscite=0;  // contatore delle avvenute uscite
byte sonarBarries=B00000000; // così composta -> [0 0 0 0 0 0 extSonar intSonar ]
byte SM_STATUS = SM_STATUS_L;  //stato iniziale  della SM
unsigned long TTV_timer=0;
NewPing ext_Sonar(EXT_SONAR_TRIG_PIN,EXT_SONAR_ECHO_PIN,MAX_SONAR_DISTANCE);
NewPing int_Sonar(INT_SONAR_TRIG_PIN,INT_SONAR_ECHO_PIN,MAX_SONAR_DISTANCE);


void setup()
{
// TODO
// creazione oggetti sonar
// inizializzazione time-out
//

}


void loop()
{

// TODO
sonarBarries=ReadSonars();
TTV_timer=millis()+RITARDO;

switch (SM_STATUS) { // stato libero
  case SM_STATUS_L:
    switch (sonarBarries) {
      case SB_EXT_X:
        SM_STATUS=SM_STATUS_PI;
      break;
      case SB_INT_X:
        SM_STATUS=SM_STATUS_PU;
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
    switch (sonarBarries) {
      case SB_EXT_X: // nessun ingresso. Il soggetto è tornato indietro ....
        SM_STATUS=SM_STATUS_L;
      break;
      case SB_INT_X:
        //è avvenuto un ingresso
        contaIngressi++;
        SM_STATUS=SM_STATUS_L;
      break;
      case SB_NONE: // in attesa di un attraversamento . . .
        if (TTV_timer-millis()<=0) {
          //il timer attraversamento barriera è scaduto
          //torno nello stato libero
          SM_STATUS=SM_STATUS_L;
        } else {
          // aspetto che il timer scada o ci sia un attraversamento della barriera INTerna
          SM_STATUS=SM_STATUS_PI;
        }
      break;
      default:
        SM_STATUS=SM_STATUS_L;
      break;
    }
  break;

  case SM_STATUS_PU: // stato di pre-uscita
    switch (sonarBarries) {
      case SB_EXT_X: // è avvenuta una uscita
        contaUscite++;
        SM_STATUS=SM_STATUS_L;
      break;
      case SB_INT_X: // nessun ingresso. Il soggetto è tornato indietro ...
        SM_STATUS=SM_STATUS_L;
      break;
      case SB_NONE: // in attesa di un attraversamento . . .
        if (TTV_timer-millis()<=0) {
          //il timer attraversamento barriera è scaduto
          //torno nello stato libero
          SM_STATUS=SM_STATUS_L;
        } else {
          // aspetto che il timer scada o ci sia un attraversamento della barriera EXTerna
          SM_STATUS=SM_STATUS_PU;
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
