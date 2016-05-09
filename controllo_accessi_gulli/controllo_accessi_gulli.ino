/*
 *********************Arduino Source File Header**************************
__file_name__ = controllo_accessi_gulli.ino
__description__="Gestisce la state machine oper il controllo accessi  attraverso
 le barriere sonar e si connette con un PC esterno (via seriale o Ethernet) per
 comunicare gli aggiornameti degli accessi o condizioni anomale di blocco delle barriere"
__author__ = "Stefano Baldacci"
__copyright__ = "Informazioni di Copyright"
__license__ = "GPL"
__email__ = "stefano.baldacci@gmail.com"
__status__ = "Development[X]";"Test[]";"Production[]";
__History__: (repeat the following line as many times as applicable)
    __version__ = "0.1 original"
***************************************************************************
*/




//#include "Arduino.h" // libreria per compatibilita con PlatformIO. Vedi www.platformio.org
#include <NewPing.h> // librearia per gestione moduli Sonar HC-SR04

//****************** global variables definition ******************
byte sonarBarries=0; // così composta -> [0 0 0 0 0 0 extSonar intSonar ]

// codifica stati della State Machine
#define SM_STATUS_Start 0 // in pratica non è usato
#define SM_STATUS_L 1
#define SM_Status_PI 2
#define SM_Status_PU 3
#define SM_Status_I 4
#define SM_Status_U 5

int SM_Status = SM_STATUS_L;  //stato corrente della SM
//****************** global variables definition ******************


void setup()
{

// TODO

// creazione oggetti sonar
// inizializzazione time-out
//

}


void loop()
{

// TODO
// State machine
// Data display and communication

}

