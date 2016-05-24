/*
 *********************Arduino Source File Header**************************
__file_name__ = "sonar_barrier.ino"
__description__="cosa fa questo codice ?"
__author__ = "Stefano Baldacci"
__copyright__ = "Informazioni di Copyright"
__license__ = "GPL"
__email__ = "stefano.baldacci@gmail.com"
__status__ = "Development[X]";"Test[]";"Production[]";
__History__: (repeat the following line as many times as applicable)
    __version__ = "0.1 original"
***************************************************************************
*/

//************************************Implementazione Funzioni Globali ****************************************//

/* funzione int IsBarrierCrossed(NewPing sonar):
Controlla se una barriera sonar è stata attraversata correttamente.
*/
bool IsBarrierCrossed(NewPing sonar) {

//TODO: vedi specifiche in .docs/IsBarrierCrossed.pdf
return false;
  }

  /* funzione bool IsEXTBarrierCrossed():
  Controlla se la  barriera sonar Esterna è stata attraversata correttamente.
  */
  bool IsEXTBarrierCrossed() {
  //TODO: vedi specifiche in .docs/IsBarrierCrossed.pdf
  return false;
    }


    /* funzione bool IsINTBarrierCrossed():
    Controlla se la  barriera sonar Interna è stata attraversata correttamente.
    */
    bool IsINTBarrierCrossed() {

    //TODO: vedi specifiche in .docs/IsBarrierCrossed.pdf
    return false;
      }



  /* versione di test della IsEXTBarrierCrossed(NewPing sonar):
  La barriera Sonar è simulata da un tasto collegato tra il pin
  EXT_SONAR_ECHO_PIN e massa. Il pin deve essere in modo PULLUP
  */
  bool _t_IsEXTBarrierCrossed() {
  //TODO: vedi specifiche in .docs/IsBarrierCrossed.pdf
  byte return_value=false;
  pinMode(EXT_SONAR_ECHO_PIN,INPUT_PULLUP );
  // controllo se il tast che simula la barriera è premuto
  if (digitalRead(EXT_SONAR_ECHO_PIN)==LOW) { // tasto premuto

    //mi blocco fino a che il tasto è premuto ed accendo un LED
    while(digitalRead(EXT_SONAR_ECHO_PIN)==LOW) digitalWrite(LED_SB_EXT,HIGH);

    //il tasto è rilasciato e mi sblocco. Questo simula barriera attraversata.
    //Spengo il LED
    digitalWrite(LED_SB_EXT,LOW);

    return_value=true;
    }

  return return_value;

    }



    /* versione di test della IsINTBarrierCrossed(NewPing sonar):
    La barriera Sonar è simulata da un tasto collegato tra il pin
    INT_SONAR_ECHO_PIN e massa. Il pin deve essere in modo PULLUP
    */
    bool _t_IsINTBarrierCrossed() {
    byte return_value=false;
    pinMode(INT_SONAR_ECHO_PIN,INPUT_PULLUP );
    // controllo se il tast che simula la barriera è premuto
    if (digitalRead(INT_SONAR_ECHO_PIN)==LOW) { // tasto premuto

      //mi blocco fino a che il tasto è premuto ed accendo un LED
      while(digitalRead(INT_SONAR_ECHO_PIN)==LOW) digitalWrite(LED_SB_INT,HIGH);

      //il tasto è rilasciato e mi sblocco. Questo simula barriera attraversata.
      //Spengo il LED
      digitalWrite(LED_SB_INT,LOW);

      return_value=true;
      }

    return return_value;

      }

/* funzione  byte _t_ReadSonars():
Versione di test della ReadSonars()
*/
 byte _t_ReadSonars(){

   byte returnValue=B00000000;
   bool INT_Sonar,EXTSonar=false;

   INT_Sonar=_t_IsINTBarrierCrossed();
   EXTSonar=_t_IsEXTBarrierCrossed();
   bitWrite(returnValue,1,EXTSonar);
   bitWrite(returnValue,0, INT_Sonar);

   return returnValue;
}


byte ReadSonars(){

//TODO: vedi specifiche in .docs/ReadSonar.pdf

return 0;

  }
