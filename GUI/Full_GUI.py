import sys
import random


import RPi.GPIO as GPIO
import serial
import time
import pyrebase
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QMainWindow, QDialog, QApplication, QMessageBox, QLCDNumber, QWidget, QVBoxLayout, QLabel
from PyQt5.QtGui import QDesktopServices, QFont
from PyQt5.QtCore import QUrl, QTimer, QTime, Qt
from PyQt5.uic import loadUi
from datetime import datetime

######################################################################################
firebaseConfig = {
  'apiKey': "AIzaSyCdpuLA18tyrXDbLyhiVD3HPrZMa46Ihss",
  'authDomain': "fir-led-sing-be438.firebaseapp.com",
  'projectId': "fir-led-sing-be438",
  'storageBucket': "fir-led-sing-be438.appspot.com",
  'messagingSenderId': "908349557819",
  'appId': "1:908349557819:web:664cf0280268954817e01e",
  'measurementId': "G-KDF9C42H79"
}

firebase=pyrebase.initialize_app(firebaseConfig)
auth=firebase.auth()
database=firebase.database()
data={"update_flag": 0}
database.child("flags").set(data)
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






class InfoScreen(QMainWindow):
    def __init__(self):
        super(InfoScreen,self).__init__()
        loadUi("PyQt/infoScreen.ui",self)
        ############## Time ##############
        self.lcd = self.findChild(QLCDNumber, "lcdTime")
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.showTime)
        self.timer.start(1000) 
        self.showTime()
        self.show()

        

        ########## Parking Mode ##########
        self.ParkingButton.clicked.connect(self.gotoParkingMode)
        # Flag to track if ParkingButton was clicked
        self.parking_button_clicked = False
        ########## System Updates ########
        self.updateButton.clicked.connect(self.gotologin)


        

    def showTime(self):
        time = datetime.now()
        formatted_time = time.strftime("%I:%M:%S")
        self.lcd.setDigitCount(8)
        self.lcd.display(formatted_time)

    def gotoParkingMode(self):
        self.parking_button_clicked = True
        update_flag = database.child("flags").child("update_flag").get().val()
        print("flag Reading:", update_flag)
        
        if ((self.parking_button_clicked) and update_flag==0):
            reply=QMessageBox.warning(self, "NOT FOUND ", "Parking Mode not accessible.")
            self.parking_button_clicked = False

            if reply == QMessageBox.Close:
                #widget.setCurrentIndex(widget.currentIndex()) 

                self.returnToHome()
                return
        if update_flag:
            while self.checkUARTData():

                print("helllooooo")
                ultrasonic_reading = self.getUltrasonicReading()
                print("Ultrasonic Reading:", ultrasonic_reading)
                if ultrasonic_reading < 20:
                    QMessageBox.warning(self, "Warning", "Obstacle detected! Please be cautious.")
                    GPIO.output(warningLED, GPIO.HIGH)
                    time.sleep(0.05)
                    break
                else:
                    GPIO.output(warningLED, GPIO.LOW)
                    time.sleep(0.05)
                    break
        self.returnToHome()
      
    
    def checkUARTData(self):
        while True:
            data = ser.read(1)
            if data:
                data_str = data.decode(errors='ignore')  # Ignore errors in decoding
                if data_str == 'D':
                    return True
            else:
                pass 
    def returnToHome(self):
        self.show()

    def closeEvent(self, event):
        self.returnToHome()
        event.accept()
        
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
        update_data={"update_flag": 1}
        # Update firebase new code to true
        database.child("flags").update(update_data)
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
