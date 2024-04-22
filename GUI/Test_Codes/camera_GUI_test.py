import sys
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton, QLabel
from PyQt5.QtGui import QPixmap
from picamera2 import Picamera2, Preview
from threading import Thread
import time

class CameraPreview(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Camera Preview")
        self.setGeometry(100, 100, 640, 480)

        layout = QVBoxLayout()

        self.label = QLabel()
        layout.addWidget(self.label)

        self.button = QPushButton("Start Preview")
        self.button.clicked.connect(self.start_preview)
        layout.addWidget(self.button)

        self.setLayout(layout)

        self.picamera = Picamera2()

    def start_preview(self):
        self.preview_thread = Thread(target=self.preview_worker)
        self.preview_thread.start()

    def preview_worker(self):
        try:
            self.picamera.start_preview(Preview.QTGL)
            time.sleep(5)  # Preview for 5 seconds
            self.picamera.stop_preview()
        except Exception as e:
            print(f"Error starting camera preview: {e}")

    def closeEvent(self, event):
        self.picamera.stop_preview()
        event.accept()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = CameraPreview()
    window.show()
    sys.exit(app.exec_())
