#!/usr/bin/env  python

import serial,time
import make_html

rx_buffer=" "
rx_data=[0, 0]
status=" "
ingressi=0
uscite=0
timestamp=""
ser = serial.Serial('/dev/ttyAMA0', 115200, timeout=1)
ser.flushInput()
ser.flushOutput()
#print(ser.name)
#time.sleep(5)

#load  counters from File
with open('accessi.log') as logfile:
    for line in logfile:
        if(line.strip()):
                try:
                    logdata=line.split()
                    ingressi=int(logdata[1])
                    uscite=int(logdata[2])
                except:
                    continue


# send CNT command
ser.write('CNT')

# receive and parse counters
rx_buffer=ser.readline()
if(rx_buffer.find("\n")):
    # do stuff
    timestamp=time.strftime("%H:%M:%S-%d/%m/%Y ",time.localtime())
    rx_buffer=timestamp+rx_buffer
    with open('accessi.log',a) as logfile:
        logfile.write(timestamp + rx_buffer +"\n")
        try:
        logdata=line.split()
        ingressi=int(logdata[1])
        uscite=int(logdata[2])
        except:
             continue
else:
    status="comm. error"


# update File
# generate html


while 1:
    if(ser.inWaiting()):
        counter+=1
        rx_buffer=ser.readline()
        if(rx_buffer.find("IN")>-1 or rx_buffer.find("OUT")>-1):
            ser.write('ACK')
	    rx_data=rx_buffer.split()
            msg= str(rx_data[0]) + ":"+ str(rx_data[1])
            #print(str(counter ) + " " + msg)
            if(rx_buffer.find("IN")):
                ingressi+=int(rx_data[1])
            if(rx_buffer.find("OUT")):
                uscite+=int(rx_data[1])
    make_html.MakeHTML(ingressi,uscite,"OK")
    #print("Ingressi= " + str(ingressi)+"\n")
    #print("Uscite= " + str(uscite) + "\n")
