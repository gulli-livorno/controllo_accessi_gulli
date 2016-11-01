
/*
 *********************Arduino Source File Header**************************
__file_name__ = "communications.ino"
__description__="cosa fa questo codice ?"
__author__ = ""
__copyright__ = "Informazioni di Copyright"
__license__ = "GPL"
__email__ = " "
__status__ = "Development[]";"Test[X]";"Production[]";
__History__: (repeat the following line as many times as applicable)
    __version__ = "1.0 Linux Day 2016"
***************************************************************************
*/



//TODO
/* implementare un modulo per la comunicazione con un PC connesso via seriale

*/


//************************************Implementazione Funzioni Globali ****************************************//





/* funzione int TxBlocked():
Trasmette sulla porta seriale  un evento di barriera bloccata
Ritorna un eventuale codice di errore/conferma
*/
int TxBlocked(){

Serial.print("B");
return 0;
}


/* funzione int ProcessSerialInput():
Elabora eventuali comandi ricevuti da PC esterno sulla porta seriale
Ritorna un eventuale codice di errore/conferma
*/
int ProcessSerialCommands(){
byte retval=0;
char cmdBuffer[]=" ";
if (Serial.available()) {

  Serial.readBytes(cmdBuffer, 1); // comandi di un carattere
  /* if (strcmp(cmdBuffer,"R")==0) { // reset counters
    contaIngressi=0;
    contaUscite=0;
    Serial.println("ACK");
  }
  if (strcmp(cmdBuffer,"HBT")==0) { // Heart beat. Arduino è in funzione e gira tutto OK
    Serial.println("ACK");
  }


  */

  if (strcmp(cmdBuffer,"C")==0) { // Trasmetto i valori dei counters ingressi e uscite
    // dopo la trasmissione   e ricezione ACK azzero i contatori
    digitalWrite(LED_SERIAL,HIGH);
    Serial.print(contaIngressi);
    Serial.print(" ");
    Serial.print(contaUscite);
    Serial.print("\n");
    if (Serial.find("A")) { // ACK ricevuto da HOST PC.
      contaIngressi=0;
      contaUscite=0;
      retval=1;
    }
    else {
      //errore di comunicazione.
      retval=0;
    }

  }
return retval;
}
}
