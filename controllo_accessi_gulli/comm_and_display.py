#!/usr/bin/env  python
# coding=utf-8
import serial,time
import make_html

# file per il salvataggio degli accessi
log_file_name='accessi.log'

# apro porta seriale per comunicazione con Arduino
ser = serial.Serial('/dev/ttyAMA0',57600 , timeout=1)

rx_buffer=" "
rx_data=[0, 0]
status=" "
ingressi=0
uscite=0
timestamp=""
ser.flushInput()
ser.flushOutput()
print(ser.name)

# ricarico i valori dei contatori dal file di log. Il formato del file è: [timestamp] [Ingressi] [Uscite]
with open(log_file_name,"a+") as logfile:
    for line in logfile:
        if(line.strip()):
                try:
                    rx_data=line.split()
                    ingressi=int(rx_data[1])
                    uscite=int(rx_data[2])
                except:
                    status="log file error"



# trasmetto comando CNT su seriale
ser.write("CNT")
# ricevo da seriale
rx_buffer=ser.readline()
#rx_buffer=ser.read(5)
print(rx_buffer)
if(rx_buffer.find("\n")>=0): # se ho ricevuto senza timeout
    try:
    #estraggo i valori  dalla stringa ricevuta ed aggiorno i contatori Ingressi/Uscite
        print("found !")
        rx_data=rx_buffer.split()
        ingressi+=int(rx_data[0])
        uscite+=int(rx_data[1])
        # trasmetto  ACK su seriale
        ser.write("ACK")
    except:
        status="comm. error"


    # aggiorno il file di log se necessario
    if(rx_data[0]!=0 or rx_data[1]!=0):
    # aggiungo timestamp al file
        timestamp=time.strftime("%H:%M:%S-%d/%m/%Y ",time.localtime())
        rx_buffer=timestamp + rx_buffer
        with open(log_file_name,"a+") as logfile:
            logfile.write(rx_buffer +"\n")

else:
    status="comm. error"
ser.flushInput()
ser.close()
# creo file html per Display Controllo Accessi
#make_html.MakeHTML(ingressi,uscite,status)
print("Ingressi= " + str(ingressi)+"\n")
print("Uscite= " + str(uscite) + "\n")
print("Status= " +  str(status) + "\n")
