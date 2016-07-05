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
#define LARGHEZZA_VARCO 100  //[cm]
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
#define TTV_DELAY 1500 //tempo attraversamento barriera [ms]
bool timeout=false;

int contaIngressi=0;
int contaUscite=0;


int i=0;
float dist=0.0;

// oggetti NewPing per la gestione dei moduli sonar
NewPing ext_Sonar(EXT_SONAR_TRIG_PIN,EXT_SONAR_ECHO_PIN,LARGHEZZA_VARCO);
NewPing int_Sonar(INT_SONAR_TRIG_PIN,INT_SONAR_ECHO_PIN,LARGHEZZA_VARCO);

String msg="";

void setup()
{
Serial.begin(115200);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
tone(10, 200, 500);
}

void loop()
{

  /*
  bool BX=false;
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  Serial.print(F("Ping Ext Sonar:"));
  Serial.print(ext_Sonar.ping_cm());
  Serial.print(F("  Ping Int Sonar:"));
  Serial.print(int_Sonar.ping_cm());
  Serial.print(F("    Ingressi="));
  Serial.print(contaIngressi);
  Serial.print(F("  Uscite="));
  Serial.print(contaUscite);
  Serial.print("\r");

  //Controllo INGRESSO
  if (IsBarrierCrossed(ext_Sonar,8,LARGHEZZA_VARCO*0.9,0.6)) {
    TTV_timer=millis(); //inizializzo timer
    delay(6);
    while (! (IsBarrierCrossed(int_Sonar,5,LARGHEZZA_VARCO*0.9,0.6)||timeout)) { // attendo attraversamento barriera interna o timeout
      if (millis()-TTV_timer>TTV_DELAY) {
        timeout=true;
      }
    }
      if (! timeout) { // se sono uscito dal loop NON per timeout allora è un ingresso
        contaIngressi++;
        digitalWrite(8,HIGH);
        tone(11, 500, 500);

        Serial.print(F("INGRESSO ->[]                                             "));
      }
  }



// note di test
//Distanza moduli sonar 30 cm.
//Larghezza varco 85 cm
// altezza sensori 75


 //delay per esaurire echo sonar
 //delay(10);
  // Controllo USCITA
  //Controllo INGRESSO


  if (IsBarrierCrossed(int_Sonar,5,LARGHEZZA_VARCO*0.9,0.6)) {
    TTV_timer=millis(); //inizializzo timer
    delay(6);
    while (! (IsBarrierCrossed(ext_Sonar,8,LARGHEZZA_VARCO*0.9,0.6)||timeout)) { // attendo attraversamento barriera externa o timeout
      if (millis()-TTV_timer>TTV_DELAY) {
        timeout=true;
      }
    }
      if (! timeout) { // se sono uscito dal loop NON per timeout allora è una uscita
        contaUscite++;
          digitalWrite(7,HIGH);
          tone(11, 200, 500);

        Serial.print(F("USCITA ->[]                                             "));
      }
  }

  timeout=false;
  Serial.print("\r");
*/

  Serial.print(10);
  Serial.print(" ");
  Serial.print(20);
  Serial.print("\n");
  delay(10);
    //tone(11, 200, 100);



 /* ************************ TEST ***************************
dist=NormalizedSonarReading(ext_Sonar, 8,MAX_SONAR_DISTANCE);

//msg=TestSonarModule(ext_Sonar,millis());
if (dist< 0.6) {
  Serial.print(F("********************************* "));
  Serial.print(dist);
  Serial.println(F(" *********************************"));
}
else {
Serial.println(dist);
//delay(random(6));
}
  ************************ TEST ************************** */


}
