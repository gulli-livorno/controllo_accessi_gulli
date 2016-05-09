
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
o via Ethernet.

Il SW controllo accessi che gira su Arduino dovrebbe:

1) comunicare al PC connesso
quando c'è stato un passaggio attraverso la barriera in modo che il PC connesso possa
aggiornare un display.

2) comunicare al PC connesso
se una barriera è bloccata in modo da generare un allarme audio/video

3) rispondere a comandi dal PC connesso

4) altre cose che ci vengono in mente . . . . .
*/

/* funzione int TxCounters():
Trasmette  il valore dei contatori di ingresso di uscita
*/
int TxCounters(){

return 0;
}

/* funzione int TxIngresso():
Trasmette  un evento di avvenuto ingresso
*/
int TxIngresso(){

return 0;
}

/* funzione int TxUscita():
Trasmette  un evento di avvenuta uscita
*/
int TxUscita(){

return 0;
}

/* funzione int TxBlocked():
Trasmette  un evento di barriera bloccata
*/
int TxBlocked(){

return 0;
}


/* funzione int ProcessSerialInput():
Elabora eventuali comandi ricevuti da PC esterno
*/
int ProcessSerialInput(){

return 0;
}

