/*
 *********************Arduino Source File Header**************************
__file_name__ = controllo_accessi_gulli.ino
__description__="Modulo per la prova delle funzionalità dei sensori sonar
e la liberria NewPing "
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
#include <NewPing.h> // libreria per gestione moduli Sonar HC-SR04

//****************** global variables definition ******************
// Collegamenti moduli Sonar
#define EXT_SONAR_TRIG_PIN 3
#define EXT_SONAR_ECHO_PIN  4
#define INT_SONAR_TRIG_PIN 5
#define INT_SONAR_ECHO_PIN 6
#define MAX_SONAR_DISTANCE 80.0f  //[cm]
#define SPEED_OF_SOUND 33.0f    //[cm/ms]


//codifica dello stato delle barriere sonar
#define SB_EXT_X B00000010 //barriera esterna attraversata
#define SB_INT_X B00000001 //barriera interna attraversata
#define SB_NONE  B00000000 // barriere libere

// LED per eventi Ingresso e uscita
#define LED_SB_INT 7
#define LED_SB_EXT 8

//****************** global variables definition ******************
byte sonarBarries=B00000000; // così composta -> [0 0 0 0 0 0 extSonar intSonar ]

unsigned long TTV_timer=0; // timer per attraversamento barriera
#define TTV_DELAY 2500 //tempo attraversamento barriera [ms]
bool timeout=false;

int contaIngressi=0;
int contaUscite=0;

// oggetti NewPing per la gestione dei moduli sonar
NewPing ext_Sonar(EXT_SONAR_TRIG_PIN,EXT_SONAR_ECHO_PIN,MAX_SONAR_DISTANCE);
NewPing int_Sonar(INT_SONAR_TRIG_PIN,INT_SONAR_ECHO_PIN,MAX_SONAR_DISTANCE);


void setup()
{
Serial.begin(115200);
}

void loop()
{
  bool BX=false;
  Serial.print(F("Ping Ext Sonar:"));
  Serial.print(ext_Sonar.ping_cm());
  Serial.print(F("  Ping Int Sonar:"));
  Serial.print(int_Sonar.ping_cm());
  Serial.print(F("    Ingressi="));
  Serial.print(contaIngressi);
  Serial.print(F("  Uscite="));
  Serial.print(contaUscite);
  Serial.print("\r");

  // Controllo INGRESSO
  BX=IsBarrierCrossed(ext_Sonar);
  if (BX) {
    TTV_timer=millis(); //inizializzo timer
    while (! (IsBarrierCrossed(int_Sonar)||timeout)) { // attendo attraversamento barriera interna o timeout
      if (millis()-TTV_timer>TTV_DELAY) {
        timeout=true;
      }
    }
      if (! timeout) { // se sono uscito dal loop NON per timeout allora è un ingresso
        contaIngressi++;
        Serial.print(F("INGRESSO ->[]                                             "));
      }

  }

 // delay per esaurire echo sonar
 delay(10);
  // Controllo USCITA
  BX=IsBarrierCrossed(int_Sonar);
  if (BX) {
    TTV_timer=millis(); //inizializzo timer
    while (! (IsBarrierCrossed(ext_Sonar)||timeout)) { // attendo attraversamento barriera interna o timeout
      if (millis()-TTV_timer>TTV_DELAY) {
        timeout=true;
      }
    }
      if (! timeout) { // se sono uscito dal loop NON per timeout allora è un'uscita
        contaUscite++;
        Serial.print(F("USCITA []->                                             "));
      }
  }
  // delay per esaurire echo sonar
delay(10);
  timeout=false;
  Serial.print("\r");

}
