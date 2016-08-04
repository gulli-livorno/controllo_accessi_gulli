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
Calcola la media delle letture del sonar in rapporto ad una distanza di riferimento.

Parametri:
NewPing sonar = o0ggetto di tipo NewPing per la gestione del modulo sonar
byte num_samples =................ numero di letture sulle quali effettuare la media
int ref_distance = lettura di riferimento rispetto alla quale si normalizza la media delle letture
Ritorno:
float rapporto della media delle letture rispetto alla larghezza del varco (stima di barriera libera)
      valori > 0.9 indicano barriera libera
      valori < 0.5 indicano barriera interrotta
*/
float NormalizedSonarReading(NewPing sonar, byte num_samples,int ref_distance ) {

  float acc_dist=0.0f; //accumulatore delle letture di distanza
  for (byte i=0; i < num_samples;i++) { //eseguo letture ripetute
    acc_dist+=sonar.ping_cm(); // le sommo tutte
    // inserisco un delay. Non sono sicuro che serva ?
    delay(2);
  }
  acc_dist=acc_dist/num_samples; //calcolo la media delle letture
  return acc_dist/ref_distance; // normalizzo rispetto alla lettura di riferimento iniziale
}

/* bool IsBarrierCrossed(NewPing sonar,int num_samples,int ref_distance,float margin):
Controlla se la  barriera sonar  è stata attraversata correttamente.
Viene stimata la probabilità che la barriera sia realmente interrotta
misurando ripetutamente la distanza del sonar rispetto alla larghezza della barriera.
Di seguito la funzione entra in in loop ed attende che la barriera
venga liberata segnalando un attraversamento valido. Fintanto che la barriera non viene
liberata la funzionegenera un messaggio di "Barriera bloccata"
Parametri:
NewPing sonar = oggetto di tipo NewPing per la gestione del modulo sonar
int num_samples = numero di letture su cui fare la media
int ref_distance = lettura del sonar quando la barriera è libera (circa 0.9 * MAX_SONAR_DISTANCE)
float margin = margine  al di sotto/sopra  della quale considero la barriera interrotta/libera
Ritorno:
bool Vero se la barriera è stata attraversata correttamente,
Falso altrimenti
*/
bool IsBarrierCrossed(NewPing sonar,int num_samples,int ref_distance,float margin){

  bool barrier_crossed=false;

    if (NormalizedSonarReading(sonar, num_samples, ref_distance) < margin) { // stimo validità interruzione
      //interruzione valida

      while (! barrier_crossed) { // attendo riapertura barriera
        if (NormalizedSonarReading(sonar, num_samples, ref_distance) > margin) { // stimo validità barriera aperta
          //barriera aperta
          barrier_crossed=true;
        } else {
          //barriera bloccata
          //Serial.println("Barriera bloccata >||<");
          }
      }
    }

  return barrier_crossed;
}



String TestSonarModule(NewPing sonar,unsigned long start_time) {

String msg=String("TSM: d[cm] t[ms]");
String distance=String("");
distance+=sonar.ping_cm();
String atime=String("");
atime+=(millis()-start_time);
msg.replace("d",distance);
msg.replace("t",atime);
return msg;

}
