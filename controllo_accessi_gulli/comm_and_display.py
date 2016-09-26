#!/usr/bin/env  python
# coding=utf-8

#*********************Python module file header******************************
__doc__="""comm_and_display.py: Script python che gira su Raspberrypi e viene chiamato
come script CGI da un browser. Lo script accede alla porta  seriale al quale è collegato il modulo
conta accessi basato su arduino. Viene trasmesso un comando su seriale al quale il modulo
connesso risponde con il numero di ingressi ed uscite accumulato dopo l'ultima richiesta.
Dopo aver ricevuto la stringa '[ingressi] [uscite]\n' viene spedito un ACK ed il modulo connesso
resetta i contatori ingresso uscita"""
__author__ = "Stefano Baldacci"
__copyright__ = """Copyright information The content of this file is property of
Stefano Baldacci.It cannot be used, copied, modified, transferred or disclosed
without prior written agreement"""
__license__ = "GPL"
__email__ = "stefano.baldacci@gmail.com"
__status__ = "Production"
#History: (repeat the following line as many times as applicable)
__version__ = "0.1 original"

#******************************************************************************
#!/usr/bin/env  python
# coding=utf-8
import serial,time,sys
import make_html

# file per il salvataggio degli accessi
log_file_name='accessi.log'

rx_buffer=" "
rx_data=[0, 0]
status="OK"
ingressi=0
uscite=0
timestamp=""


# ricarico i valori dei contatori dal file di log. Il formato del file è: [timestamp] [Ingressi] [Uscite]
with open(log_file_name,"a+") as logfile:
    for line in logfile:
        if(line.strip()):
                try:
                    rx_data=line.split()
                    ingressi+=int(rx_data[1])
                    uscite+=int(rx_data[2])
                except:
                    status="Error reading log file"




# apro porta seriale per comunicazione con Arduino
try:
	ser = serial.Serial('/dev/ttyUSB0',115200 , timeout=2)
except serial.SerialException:
	status="Error opening serial port"
	make_html.MakeHTML(ingressi,uscite,status)
	sys.exit(0)

ser.flushInput()
ser.flushOutput()
#print(ser.name)




# trasmetto comando CNT su seriale
ser.write("C")
# ricevo da seriale
rx_buffer=ser.readline()
#rx_buffer=ser.read(5)
#print(rx_buffer)
if(rx_buffer.find("\n")>=0): # se ho ricevuto senza timeout
    try:
    #estraggo i valori  dalla stringa ricevuta ed aggiorno i contatori Ingressi/Uscite
        rx_data=rx_buffer.split()
        ingressi+=int(rx_data[0])
        uscite+=int(rx_data[1])
        # trasmetto  ACK su seriale
        ser.write("A")
    except:
        status="Error parsing serial rx buffer"


    # aggiorno il file di log se necessario
   # print("ingressi:uscite " + str(rx_data[0]) +":" + str(rx_data[1]))
    if(rx_data[0]!='0' or rx_data[1]!='0'):
    # aggiungo timestamp al file
        timestamp=time.strftime("%H:%M:%S-%d/%m/%Y ",time.localtime())
        rx_buffer=timestamp + rx_buffer
        with open(log_file_name,"a+") as logfile:
            logfile.write(rx_buffer +"\n")

else:
    status="Error Arduino not responding"

ser.flushInput()
ser.close()
# creo file html per Display Controllo Accessi
make_html.MakeHTML(ingressi,uscite,status)


#print("Ingressi= " + str(ingressi)+"\n")
#print("Uscite= " + str(uscite) + "\n")
#print("Status= " +  str(status) + "\n")
