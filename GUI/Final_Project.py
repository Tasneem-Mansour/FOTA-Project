import sys
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QMainWindow, QDialog, QApplication, QMessageBox, QLCDNumber, QWidget, QVBoxLayout, QLabel
from PyQt5.QtGui import QDesktopServices, QFont
from PyQt5.QtCore import QUrl, QTimer, QTime, Qt
from PyQt5.uic import loadUi
from datetime import datetime
email_passwords = {}


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

    def loginfunction(self):
        email=self.email.text()
        password=self.password.text()
        if email in email_passwords and email_passwords[email] == password:

            QDesktopServices.openUrl(QUrl("https://www.example.com"))  # Replace URL with AWARDSPACE webpage



        else:
            QMessageBox.warning(self, "Login Failed", "Incorrect email or password. Please try again.")
            self.email.clear()
            self.password.clear()
            self.exec_() 

    def gotoCreateAcc(self):
        signUp=CreateAcc()
        widget.addWidget(signUp)
        widget.setCurrentIndex(widget.currentIndex()+1)

class CreateAcc(QDialog):
    def __init__(self):
        super(CreateAcc,self).__init__()
        loadUi("PyQt/createAcc.ui",self)
        self.signupButton.clicked.connect(self.CreateAccFun)
        self.password.setEchoMode(QtWidgets.QLineEdit.Password)
        self.confirmpass.setEchoMode(QtWidgets.QLineEdit.Password)

    def CreateAccFun(self):
        global email_passwords
        email = self.email.text()

        if self.password.text()==self.confirmpass.text():
            password=self.password.text()
            email_passwords[email] = password
            print("Successfully created acc with email: ", email)
            login=Login()
            widget.addWidget(login)
            widget.setCurrentIndex(widget.currentIndex()+1)
        else:
            QMessageBox.warning(self, "unmatched password", "Please try again.")
            self.password.clear()
            self.confirmpass.clear()
            self.exec_() 

app=QApplication(sys.argv)
mainwindow=InfoScreen()
widget=QtWidgets.QStackedWidget()
widget.addWidget(mainwindow)
widget.setFixedWidth(820)
widget.setFixedHeight(500)
widget.show()
app.exec_()