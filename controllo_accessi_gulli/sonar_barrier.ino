/*
 *********************Arduino Source File Header**************************
__file_name__ = "sonar_barrier.ino"
__description__="cosa fa questo codice ?"
__author__ = ""
__copyright__ = "Informazioni di Copyright"
__license__ = "GPL"
__email__ = "stefano.baldacci@gmail.com"
__status__ = "Development[X]";"Test[]";"Production[]";
__History__: (repeat the following line as many times as applicable)
    __version__ = "0.1 original"
***************************************************************************
*/

//************************************Implementazione Funzioni Globali ****************************************//
#include <NewPing.h>

/* float NormalizedSonarReading(NewPing sonar, byte num_samples,int ref_distance ):
Stima l'attendibilità delle  letture del sonar a seguito di una prima lettura diversa da 0.
Se la barriera è libera la funzione di libreria sonar.ping_cm() restituisce 0 altrimenti il
valore della distanza in cm. Siccome la lettura è instabile e certe volte produce 0 anche
quando il fascio sonar è riflesso allora è necessario effettuare una sorta di filtraggio per stimare la
validità delle letture e poter affermare che la barriera è stata interrotta e non si tratta di un segnale spurio.
Parametri:
NewPing sonar = oggetto di tipo NewPing per la gestione del modulo sonar
byte num_samples = numero di letture sulle quali effettuare la media
int ref_distance = lettura di riferimento rispetto alla quale si normalizza la media delle letture
Ritorno:
float stima della probabilità che la barriera sia stabilmente interrotta
[1=barriera sicuramente interrotta; 0 barriera sicuramente aperta]
*/
float NormalizedSonarReading(NewPing sonar, byte num_samples,int ref_distance ) {

  float acc_dist=0.0f; //accumulatore delle letture di distanza
  for (byte i=0; i < num_samples;i++) { //eseguo letture ripetute
    acc_dist+=sonar.ping_cm(); // le sommo tutte
    // attendo un tempo sufficiente alla riflessione completa del fascio sonar (??)
    float f=MAX_SONAR_DISTANCE/SPEED_OF_SOUND + 0.5;
    delay(int(f));
  }
  acc_dist=acc_dist/num_samples; //calcolo la media delle letture
  return acc_dist/ref_distance; // normalizzo rispetto alla lettura di riferimento iniziale
}

/* bool IsBarrierCrossed(NewPing sonar):
Controlla se la  barriera sonar  è stata attraversata correttamente.
A seguito di una singola lettura diversa da zero viene stimata la probabilità che la barriera
sia realmente interrotta e di seguito la funzione entra in in loop ed attende che la barriera
venga liberata segnalando un attraversamento valido. Fintanto che la barriera non viene
liberata la funzionegenera un messaggio di "Barriera bloccata"
Parametri:
NewPing sonar = oggetto di tipo NewPing per la gestione del modulo sonar
Ritorno:
bool Vero se la barriera è stata attraversata correttamente,
Falso altrimenti in caso di barriera libera o segnale spurio
*/
bool IsBarrierCrossed(NewPing sonar){

  int distance,ref_distance=0;
  #define TTB_DELAY 100 //ms
  bool barrier_crossed=false;

  distance=ext_Sonar.ping_cm(); //lettura istantanea barriera
  ref_distance=distance; // lettura di riferimento
  if (distance > 0) { //catturo la prima lettura diversa da 0
    if (NormalizedSonarReading(sonar, 10, ref_distance)>0.8) { // stimo validità interruzione
      //interruzione valida
      delay(TTB_DELAY);

      while (! barrier_crossed) { // attendo riapertura barriera
        if (NormalizedSonarReading(sonar, 10, ref_distance)<0.2) { // stimo validità barriera aperta
          //barriera aperta
          barrier_crossed=true;
        } else {
          //barriera bloccata
          Serial.println("Barriera bloccata >||<");
          }
      }
    }
  }
  return barrier_crossed;
}

  /* funzione bool IsEXTBarrierCrossed():
  Controlla se la  barriera sonar Esterna è stata attraversata correttamente.
  eliminare se la funzione bool IsBarrierCrossed(NewPing sonar)
  funziona correttamente
  */

  bool IsEXTBarrierCrossed() {
  //vedi specifiche in .docs/IsBarrierCrossed.pdf
  byte zeroCount=0;
  int distance=0;
  unsigned long TTB_Timer=0;
  #define TTB_DELAY 100 //ms
  bool barrier_crossed=false;

  distance=ext_Sonar.ping_cm();
  int distance_ref=distance;

if (distance > 0) {
  distance=0;
  Serial.println("prima interruzione");
  Serial.print("distanceref = ");
  Serial.print(distance_ref);
  for(int j=0;j<10;j++) {
    distance+=ext_Sonar.ping_cm();
    delay(2);
    }

    if(distance<5*distance_ref) {
    // disurbo
    return false;
  }
  Serial.println(" interruzione valida");
  delay(TTB_DELAY); // si può eliminare ?
  while (! barrier_crossed) {
  distance=0;
  for(int j=0;j<10;j++) {
    distance+=ext_Sonar.ping_cm();
    delay(2);
  }
  Serial.print("distance in while loop = ");
  Serial.print(distance);
  if(distance < 2*distance_ref){
    barrier_crossed=true; // barriera attraversata
    Serial.println(" barriera attraversata");
  } else {
  Serial.println("Barriera Bloccata");
  }
}
 }
 return barrier_crossed;
}



/* byte ReadSonars():
Legge lo stato delle  barriere sonar  "ext_Sonar" ed "int_Sonar" e lo codifica in un byte
Parametri:
nessuno
Ritorno:
byte
[0 0 0 0 0 0 0 0] -> barriere "ext_Sonar" ed "int_Sonar" libere
[0 0 0 0 0 0 1 0] -> barriera "ext_Sonar" attraversata
[0 0 0 0 0 0 0 1] -> barriera "int_Sonar" attraversata
[altri valori non ammessi]

*/
 byte ReadSonars(){

   byte returnValue=B00000000;
   bool INT_Sonar,EXTSonar=false;

   INT_Sonar=IsBarrierCrossed(int_Sonar);
   EXTSonar=IsBarrierCrossed(ext_Sonar);
   bitWrite(returnValue,1,EXTSonar);
   bitWrite(returnValue,0, INT_Sonar);

   return returnValue;
}
