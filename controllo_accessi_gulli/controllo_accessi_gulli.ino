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
__branch__= test_SM (SHA1) àà
__History__: (repeat the following line as many times as applicable)
    __version__ = "0.1 original"
***************************************************************************
*/


//#define DEBUG

//#include "Arduino.h" // libreria per compatibilita con PlatformIO. Vedi www.platformio.org
#include <NewPing.h> // libreria per gestione moduli Sonar HC-SR04
#include <avr/wdt.h>      // Watchdog timer

//****************** global variables definition ******************
// Collegamenti moduli Sonar
#define EXT_SONAR_TRIG_PIN 3 // barriera ESTERNA TRIG pin
#define EXT_SONAR_ECHO_PIN 4 // barriera ESTERNA ECHO pin
#define INT_SONAR_TRIG_PIN 5 // barriera INTTERNA TRIG pin
#define INT_SONAR_ECHO_PIN 6 // barriera INTTERNA TRIG pin
#define LARGHEZZA_VARCO 100  //[cm]
#define SPEED_OF_SOUND 33.0f //[cm/ms]

/* note di test
Distanza moduli sonar 30 cm.
Larghezza varco 100 cm
altezza sensori 75 cm
*/

// LED per segnalazione eventi eventi Ingresso e uscita
#define LED_INGRESSO 7
#define LED_USCITA 8
#define LED_SERIAL 9

// BUZZER
#define BUZZER 10

// TIMERS
unsigned long TTV_timer=0; // timer per attraversamento barriera
#define TTV_DELAY 1500    //tempo attraversamento barriera [ms]
bool timeout=false;

//CONTATORI
int contaIngressi=0;
int contaUscite=0;
int i=0;
float dist,nsr=0.0;

// oggetti NewPing per la gestione dei moduli sonar
NewPing ext_Sonar(EXT_SONAR_TRIG_PIN,EXT_SONAR_ECHO_PIN,LARGHEZZA_VARCO);
NewPing int_Sonar(INT_SONAR_TRIG_PIN,INT_SONAR_ECHO_PIN,LARGHEZZA_VARCO);

String msg="";

void setup()
{
Serial.begin(115200);
Serial.setTimeout(2000);
pinMode(LED_USCITA, OUTPUT);
pinMode(LED_INGRESSO, OUTPUT);
pinMode(BUZZER, OUTPUT);
//tone(10, 200, 500);
}

void loop()
{
  bool BX=false;
  digitalWrite(LED_USCITA,LOW);
  digitalWrite(LED_INGRESSO,LOW);
  digitalWrite(LED_SERIAL,LOW);
/*Serial.print(F("Ping Ext Sonar:"));
  Serial.print(ext_Sonar.ping_cm());
  Serial.print(F("  Ping Int Sonar:"));
  Serial.print(int_Sonar.ping_cm());
  Serial.print(F("    Ingressi="));
  Serial.print(contaIngressi);
  Serial.print(F("  Uscite="));
  Serial.print(contaUscite);
  Serial.print("\r");
*/

  //Controllo INGRESSO
  #ifdef DEBUG
  Serial.print("Ingresso EXT SONAR");
  #endif
  if (IsBarrierCrossed(ext_Sonar,5,LARGHEZZA_VARCO*0.9,0.6)) {
    TTV_timer=millis(); //inizializzo timer
    delay(6);
    #ifdef DEBUG
    Serial.print("Ingresso INT SONAR");
    #endif
    while (! (IsBarrierCrossed(int_Sonar,5,LARGHEZZA_VARCO*0.9,0.6)||timeout)) { // attendo attraversamento barriera interna o timeout
      if (millis()-TTV_timer>TTV_DELAY) {
        timeout=true;
      }
    }
      if (! timeout) { // se sono uscito dal loop NON per timeout allora è un ingresso
        contaIngressi++;
        digitalWrite(LED_INGRESSO,HIGH);
        tone(BUZZER, 1000, 100);
      //  Serial.print(F("INGRESSO ->[]                                             "));
      }
  }


//delay per esaurire echo sonar
//delay(10);

  // Controllo USCITA
  #ifdef DEBUG
  Serial.println("Uscita INT SONAR");
  #endif
  if (IsBarrierCrossed(int_Sonar,5,LARGHEZZA_VARCO*0.9,0.6)) {
    TTV_timer=millis(); //inizializzo timer
    delay(6);
    #ifdef DEBUG
    Serial.println("uscita EXT SONAR");
    #endif
    while (! (IsBarrierCrossed(ext_Sonar,5,LARGHEZZA_VARCO*0.9,0.6)||timeout)) { // attendo attraversamento barriera externa o timeout
      if (millis()-TTV_timer>TTV_DELAY) {
        timeout=true;
      }
    }
      if (! timeout) { // se sono uscito dal loop NON per timeout allora è una uscita
        contaUscite++;
          digitalWrite(LED_USCITA,HIGH);
          tone(BUZZER, 250, 100);
      //    Serial.print(F("USCITA ->[]                                             "));
      }
  }

  timeout=false;
//  Serial.print("\r");

// Controllo porta seriale per gestire collegamento seriale con Raspberrypi
  ProcessSerialCommands();
  delay(10);



 // ************************ TEST ***************************
/*
msg=TestSonarModule(ext_Sonar,millis());
msg="EXT: " + msg;
Serial.println(msg);
nsr=NormalizedSonarReading(ext_Sonar, 5, 100);
Serial.print("EXT NSR= ");
Serial.println(nsr);


msg=TestSonarModule(int_Sonar,millis());
msg="INT: " + msg;
Serial.println(msg);
nsr=NormalizedSonarReading(int_Sonar, 5, 100);
Serial.print("INT NSR= ");
Serial.println(nsr);
delay(100);
*/
//  ************************ TEST ************************** */


}
