
/*
 *********************Arduino Source File Header**************************
__file_name__ = "communications.ino"
__description__="cosa fa questo codice ?"
__author__ = ""
__copyright__ = "Informazioni di Copyright"
__license__ = "GPL"
__email__ = " "
__status__ = "Development[X]";"Test[]";"Production[]";
__History__: (repeat the following line as many times as applicable)
    __version__ = "0.1 original"
***************************************************************************
*/



//TODO
/* implementare un modulo per la comunicazione con un PC connesso via seriale


Il SW controllo accessi che gira su Arduino dovrebbe:

1) comunicare al PC connesso
quando c'è stato un passaggio attraverso la barriera in modo che il PC connesso possa
aggiornare un display.

2) comunicare al PC connesso
se una barriera è bloccata in modo da generare un allarme audio/video

3) rispondere a comandi dal PC connesso

4) altre cose che ci vengono in mente . . . . .

5) arduino spedisce "i"/"o" seguito da un numero incrementale fino  a che il PC non ha ricevuto e manda conferma con un messaggio
ACK e quindi il contatore di arduino si resetta

6) Meccanismo heartbeat: PC manda periodicamente un richiesta ad ARD. che risponde se è OK. Altrimenti PC manda allarme ARD. is dead !

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
char cmdBuffer[]="   ";
if (Serial.available()) {

  Serial.readBytes(cmdBuffer, 3); // comandi di tre caratteri
  if (strcmp(cmdBuffer,"RST")==0) { // reset counters
    contaIngressi=0;
    contaUscite=0;
    Serial.println("ACK");
  }
  if (strcmp(cmdBuffer,"HBT")==0) { // Heart beat. Arduino è in funzione e gira tutto OK
    Serial.println("ACK");
  }

  if (strcmp(cmdBuffer,"XXX")==0) { //
    /* code */
  }

  if (strcmp(cmdBuffer,"CNT")==0) { // Trasmetto i valori dei counters ingressi e uscite
    // dopo la trasmissione   e ricezione ACK azzero i contatori
    Serial.print(contaIngressi);
    Serial.print(" ");
    Serial.println(contaUscite);
    if (Serial.find("ACK")) { // ACK ricevuto da HOST PC.
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
