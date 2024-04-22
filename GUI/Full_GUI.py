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
from picamera2 import Picamera2, Preview


# Serial port configuration
serial_port = '/dev/ttyAMA0'  # Adjust this according to your USB to TTL module
baud_rate = 9600

 # GPIO pin for LED output
warningLED = 26 
# Initialize serial port
ser = serial.Serial(
    port=serial_port,
    baudrate=baud_rate,
    timeout=0.1  
)

# Set GPIO mode
GPIO.setmode(GPIO.BCM)
# Set pins for trigger and echo
TRIG_PIN = 23
ECHO_PIN = 24

# Set up GPIO pins
GPIO.setup(TRIG_PIN, GPIO.OUT)
GPIO.setup(ECHO_PIN, GPIO.IN)
GPIO.setup(warningLED, GPIO.OUT)

######################################################################################
firebaseConfig = {
  'apiKey': "AIzaSyA3HzDdr3tIjrK1E0GV2HfLO4-bdmSH0qY",
  'authDomain': "fota-project-wazzefa-tech.firebaseapp.com",
  'databaseURL': "https://fota-project-wazzefa-tech-default-rtdb.firebaseio.com",
  'projectId': "fota-project-wazzefa-tech",
  'storageBucket': "fota-project-wazzefa-tech.appspot.com",
  'messagingSenderId': "647612809040",
  'appId': "1:647612809040:web:66e33d30e58275f2f03655",
  'measurementId': "G-24HK5S75DW"
}

firebase=pyrebase.initialize_app(firebaseConfig)
auth=firebase.auth()
database=firebase.database()


flag = False

class InfoScreen(QMainWindow):
    def __init__(self):
        super(InfoScreen,self).__init__()
        loadUi("PyQt/infoScreen.ui",self)
        ############## Time ##############
        self.lcd = self.findChild(QLCDNumber, "lcdTime")
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.showTime)
        self. timer.start(1000) 
        self.showTime()
        self.show()

        self.picam2 = Picamera2()
        self.picam2.start_preview(Preview.QTGL)
        self.picam2.configure(preview_config)
        ########## Parking Mode ##########
        self.ParkingButton.clicked.connect(self.gotoParkingMode)

        ########## System Updates ########
        self.updateButton.clicked.connect(self.gotologin)

    def showTime(self):
        time = datetime.now()
        formatted_time = time.strftime("%I:%M:%S")
        self.lcd.setDigitCount(8)
        self.lcd.display(formatted_time)

    def gotoParkingMode(self):
        #data = self.checkUARTData()
        if self.checkUARTData():
            print("helllooooo")
            ultrasonic_reading = self.getUltrasonicReading()
            print("Ultrasonic Reading:", ultrasonic_reading)
            if ultrasonic_reading < 20:
                QMessageBox.warning(self, "Warning", "Obstacle detected! Please be cautious.")
                GPIO.output(warningLED, GPIO.HIGH)
            else:
                print("opening camera")
                    
                self.picam2.start()

        else:
            QMessageBox.warning(self, "NOT FOUND ", "Parking Mode not accessible.")
            GPIO.output(warningLED, GPIO.LOW)
        time.sleep(0.01) 

    
    def checkUARTData(self):
        #if ser.in_waiting > 0:
           # data = ser.readline().decode().strip()
          #  return data
       # else:
         #   pass
        while True:
            data = ser.readline().decode().strip()
            if data:
                flag = True
                return flag
            else:
                continue 
            
    def getUltrasonicReading(self):
        # Set trigger to HIGH
        GPIO.output(TRIG_PIN, True)
        time.sleep(0.00001)
        GPIO.output(TRIG_PIN, False)
        pulse_start = time.time()
        pulse_end = time.time()
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

    def gotologin(self):
        LogIn=Login()
        widget.addWidget(LogIn)
        widget.setCurrentIndex(widget.currentIndex()+1)

class Login(QDialog):
    def __init__(self):
        super(Login,self).__init__()
        loadUi("PyQt/Login.ui",self)

        self.loginButton.clicked.connect(self.loginfunction)
        self.password.setEchoMode(QtWidgets.QLineEdit.Password)
        
        self.createaccButton.clicked.connect(self.gotoCreateAcc)

        self.backButton.clicked.connect(self.goBack)
        self.homeButton.clicked.connect(self.goHome) 

    def loginfunction(self):
        email=self.email.text()
        password=self.password.text()

        try:
            login = auth.sign_in_with_email_and_password(email, password)          
            #UPDATE system 
            Download=Update()
            widget.addWidget(Download)
            widget.setCurrentIndex(widget.currentIndex()+1)
            #QDesktopServices.openUrl(QUrl("https://www.example.com"))  # Replace URL with AWARDSPACE webpage

        except:
            print("Invalid email or password")
            QMessageBox.warning(self, "Login Failed", "Incorrect email or password. Please try again.")
            self.email.clear()
            self.password.clear()
            self.exec_() 

    def gotoCreateAcc(self):
        signUp=CreateAcc()
        widget.addWidget(signUp)
        widget.setCurrentIndex(widget.currentIndex()+1)

    def goBack(self):
        widget.setCurrentIndex(widget.currentIndex() - 1) 
    def goHome(self):
        widget.setCurrentIndex(0) 

class Update(QDialog):
    def __init__(self):
        super(Update,self).__init__()
        loadUi("PyQt/Updates.ui",self)
        self.progressValue = 0
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.updateProgressBar)

        self.DownloadUpdate.clicked.connect(self.startProgressBar)

        self.backButton.clicked.connect(self.goBack) 
        self.homeButton.clicked.connect(self.goHome) 


    def startProgressBar(self):
        self.timer.start(1000) 

    def updateProgressBar(self):
        # Increment progress value randomly
        increment = random.randint(5, 15)  
        self.progressValue += increment
        if self.progressValue > 100:
            self.progressValue = 100
            self.timer.stop() 
            self.completeUpdate()
        self.progressBar.setValue(self.progressValue)


    def completeUpdate(self):
        # Update firebase new code to true
        database.child("code").update({"new": "true"})

        # Turn off UPDATES by switching to the next page
        noUpdates = NoUpdate()
        widget.addWidget(noUpdates)
        widget.setCurrentIndex(widget.currentIndex() + 1)


    def goBack(self):
        widget.setCurrentIndex(widget.currentIndex() - 1)
    def goHome(self):
        widget.setCurrentIndex(0)

class NoUpdate(QDialog):
    def __init__(self):
        super(NoUpdate,self).__init__()
        loadUi("PyQt/NoUpdates.ui",self)
        self.backButton.clicked.connect(self.goBack) 
        self.homeButton.clicked.connect(self.goHome) 


    def goBack(self):
        widget.setCurrentIndex(widget.currentIndex() - 2) 
    def goHome(self):
        widget.setCurrentIndex(0)

class CreateAcc(QDialog):
    def __init__(self):
        super(CreateAcc,self).__init__()
        loadUi("PyQt/createAcc.ui",self)
        self.signupButton.clicked.connect(self.CreateAccFun)
        self.password.setEchoMode(QtWidgets.QLineEdit.Password)
        self.confirmpass.setEchoMode(QtWidgets.QLineEdit.Password)
        self.backButton.clicked.connect(self.goBack)
        self.homeButton.clicked.connect(self.goHome) 

    def CreateAccFun(self):
        email = self.email.text()
        try:
            if self.password.text()==self.confirmpass.text():
                password=self.password.text()
                user = auth.create_user_with_email_and_password(email, password)
                print("Successfully created account with email: ", email)
                login=Login()
                widget.addWidget(login)
                widget.setCurrentIndex(widget.currentIndex()+1)
            else:
                QMessageBox.warning(self, "unmatched password", "Please try again.")
                self.password.clear()
                self.confirmpass.clear()
                self.exec_() 
        except: 
            QMessageBox.warning(self, "Email already exists", "Please try again.")
            self.password.clear()
            self.confirmpass.clear()
            self.exec_()

    def goBack(self):
        widget.setCurrentIndex(widget.currentIndex() - 1)
    def goHome(self):
        widget.setCurrentIndex(0)

app=QApplication(sys.argv)
mainwindow=InfoScreen()
widget=QtWidgets.QStackedWidget()
widget.addWidget(mainwindow)
widget.setFixedWidth(820)
widget.setFixedHeight(500)
widget.show()
app.exec_()