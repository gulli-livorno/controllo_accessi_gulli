#!/usr/bin/ python

import serial,time
rx_buffer=""
rx_data=[]
msg=" "
ser = serial.Serial('/dev/ttyAMA0', 115200, timeout=1)
ser.flushInput()
ser.flushOutput()
print(ser.name)
While True:
    if(ser.inWaiting():
        rx_buffer=ser.readline()
        rx_data=[]=rx_buffer.split()
        msg="Ingressi: " + rx_data[0].str()
        print("msg")
    else:
        print("idle")
