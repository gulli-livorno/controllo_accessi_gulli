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


float NormalizedSonarReading(NewPing sonar, byte num_samples,int ref_distance ) {

  float acc_dist=0.0f;
  for (byte i=0; i < num_samples;i++) {
    acc_dist+=sonar.ping_cm();
    delay(int(MAX_SONAR_DISTANCE/SPEED_OF_SOUND + 0.5));
  }
  acc_dist=acc_dist/num_samples;
  return acc_dist/ref_distance;
}


bool IsBarrierCrossed(NewPing sonar){

  int distance,ref_distance=0;
  #define TTB_DELAY 100 //ms
  bool barrier_crossed=false;

  distance=ext_Sonar.ping_cm(); //lettura istantanea barriera

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



/* funzione ReadSonars()
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
