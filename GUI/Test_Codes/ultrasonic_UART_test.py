import sys
import random
import pyrebase

import RPi.GPIO as GPIO
import serial
import time

from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QMainWindow, QDialog, QApplication, QMessageBox, QLCDNumber, QWidget, QVBoxLayout, QLabel
from PyQt5.QtGui import QDesktopServices, QFont
from PyQt5.QtCore import QUrl, QTimer, QTime, Qt
from PyQt5.uic import loadUi
from datetime import datetime
# Serial port configuration
serial_port = '/dev/ttyAMA0' 
baud_rate = 9600

# Initialize serial port
ser = serial.Serial(
        port=serial_port,
        baudrate=baud_rate,
        timeout=0.1)

GPIO.setmode(GPIO.BCM)

# GPIO pin for LED output
output_pin = 26  
# Set pins for trigger and echo
TRIG_PIN = 23
ECHO_PIN = 24

# Set up GPIO pins
GPIO.setup(TRIG_PIN, GPIO.OUT)
GPIO.setup(ECHO_PIN, GPIO.IN)
flag = False 
class InfoScreen(QMainWindow):
    def __init__(self):
        super(InfoScreen,self).__init__()
        loadUi("../PyQt/infoScreen.ui",self)
        self.ParkingButton.clicked.connect(self.gotoParkingMode)
    def gotoParkingMode(self):
        
        if flag:
            print("helllooooo")
            ultrasonic_reading = self.distance()
            print("Ultrasonic Reading:", ultrasonic_reading)
            if ultrasonic_reading < 20:
                QMessageBox.warning(self, "Warning", "Obstacle detected in", ultrasonic_reading ,"cm away!" "Please be cautious.")
                GPIO.output(warningLED, GPIO.HIGH)
            else:
                print("opening camera")
                    
        else:
            QMessageBox.warning(self, "NOT FOUND ", "Parking Mode not accessible.")
            GPIO.output(warningLED, GPIO.LOW)
            
        time.sleep(0.01) 

    
    def checkUARTData(self):
        if ser.in_waiting > 0:
            data = ser.readline().decode().strip()
            return data
        else:
            pass

    def distance():
        # Set trigger to HIGH
        GPIO.output(TRIG_PIN, True)
        time.sleep(0.00001)
        GPIO.output(TRIG_PIN, False)

        # Wait for echo pin to go HIGH
        while GPIO.input(ECHO_PIN) == 0:
            pulse_start = time.time()

        # Wait for echo pin to go LOW
        while GPIO.input(ECHO_PIN) == 1:
            pulse_end = time.time()

        # Calculate pulse duration
        pulse_duration = pulse_end - pulse_start
        # Calculate distance (speed of sound is 34300 cm/s)
        distance = pulse_duration * 17150
        # Round distance to 2 decimal places
        distance = round(distance, 2)

        return distance

GPIO.setup(output_pin, GPIO.OUT)

try:
    while True:
        # Read data from serial port
        data = ser.readline().decode().strip()
        if data:
            flag = True
            break
        #if data :
            # If 'A' is received, get ultrasonic reading and display
           # dist = distance()
            #distance = ser.readline().decode().strip()
          #  print("Ultrasonic reading:", dist)
            # If data is received, turn on the LED
         #   GPIO.output(output_pin, GPIO.HIGH)
      #  else:
            # If no data or data other than 'A' received, turn off the LED
           # GPIO.output(output_pin, GPIO.LOW)

        time.sleep(0.1)  # Add a small delay to avoid excessive CPU usage

except KeyboardInterrupt:
    print("Program terminated by user")
finally:
    GPIO.cleanup()