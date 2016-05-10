#!/usr/bin/python3
#*********************Python module file header******************************
__doc__ = """ Script Python che gira su PC o RaspberryPi.
-Rimane in attesa sulla porta seriale di un comando trasmesso da Arduino in base allo stato
della macchina conta accessi:
(es. comandi di un carattere)
i= ingresso avvenuto
u=uscita avvenuta
b=barriera bloccata
? altri comandi utili

-Trasmette comandi  alla macchina conta accessi su Arduino:
(es. comandi di un carattere)
r=reset contatori accessi
g=get contatore Accessi
? altri comandi utili

-Mostra su monitor i dati relativi agli accessi
-Pubblica su pagina WEB i dati relativi agli accessi

"""


__author__ = "Inserire Autore"
__copyright__ = """Inserire nota copyright"""
__license__ = "GPL"
__email__ = ""
__status__ = "Development[X] | Test[] | Production[]"

#History: (repeat the following line as many times as applicable)
__version__ = "0.1.1 original"
#******************************************************************************


print ("Gulli Controllo Accessi 1.0 !\n" )
print (__doc__)
