import sys
import random
import pyrebase
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QMainWindow, QDialog, QApplication, QMessageBox, QLCDNumber, QWidget, QVBoxLayout, QLabel
from PyQt5.QtGui import QDesktopServices, QFont
from PyQt5.QtCore import QUrl, QTimer, QTime, Qt
from PyQt5.uic import loadUi
from datetime import datetime



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

class InfoScreen(QMainWindow):
    def __init__(self):
        super(InfoScreen,self).__init__()
        loadUi("PyQt/infoScreen.ui",self)
        ########## Time ########
        self.lcd = self.findChild(QLCDNumber, "lcdTime")
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.showTime)
        self. timer.start(1000) 
        self.showTime()
        self.show()
        ########## Parking Mode ########
        self.ParkingButton.clicked.connect(self.gotoCamera)


        ########## Updates ########
        self.updateButton.clicked.connect(self.gotologin)

    def showTime(self):
        time = datetime.now()
        formatted_time = time.strftime("%I:%M:%S")
        self.lcd.setDigitCount(8)
        self.lcd.display(formatted_time)

    def gotoCamera(self):
        print("open camera and warnings")

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
        loadUi("PyQt/CreateAcc.ui",self)
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