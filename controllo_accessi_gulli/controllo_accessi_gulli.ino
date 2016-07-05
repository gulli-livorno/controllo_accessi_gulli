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
#define TEST_INGRESSO 3
#define TEST_USCITA 4

// LED per eventi Ingresso e uscita
#define LED_SB_INT 7
#define LED_SB_EXT 8

int contaIngressi=0;
int contaUscite=0;
int failedTx=0;
String rxBuffer="   ";

String msg="";

void setup()
{
Serial.begin(115200);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);

pinMode(TEST_INGRESSO, INPUT_PULLUP);
pinMode(TEST_USCITA, INPUT_PULLUP);
tone(10, 200, 500);
}

void loop()
{


  bool BX=false;
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);

  // INGRESSO




// USCITA

  timeout=false;
  Serial.print("\r");


  Serial.print(10);
  Serial.print(" ");
  Serial.print(20);
  Serial.print("\n");
  delay(10);
    //tone(11, 200, 100);





}
