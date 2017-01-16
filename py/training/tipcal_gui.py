# -*- coding: utf-8 -*-
import sys
import tipcal
#from PyQt4.QtGui import *
#from PyQt4.QtCore import *
from PySide import QtCore, QtGui
# PySide
from PySide.QtGui import *
from PySide.QtCore import *

class MyWindow(QWidget):
    def __init__(self):
        super(MyWindow,self).__init__()
        self.setupUI()

    def setupUI(self):
        self.setGeometry(320, 100, 300, 240)
        self.setWindowTitle("Tip calculator v0.1")

        self.pushButton = QPushButton("Start")
        self.pushButton.clicked.connect(self.pushButtonClicked)
        self.label = QLabel()

        layout = QVBoxLayout()
        layout.addWidget(self.pushButton)
        layout.addWidget(self.label)

        self.setLayout(layout)
        self.show()

    def pushButtonClicked(self):
        text, ok = QInputDialog.getInt(self, 'Tip calculator', 'input amount')
        if tipcal.isNumber(text) and tipcal.isPositive(text) and ok:
            amount=text
            text, ok = QInputDialog.getInt(self, 'Tip calculator', 'input tiprate')
            tiprate_10=text
            tip = tipcal.calc_tip(float(amount),float(tiprate_10))
            strtmp1 = """ ***** total ***** """
            strtmp2 = " tip {0:0.2f} $ ".format(tip)
            strtmp3 = " sum {0:0.2f} $ ".format(float(tip) + float(amount))
            self.label.setText(str(strtmp1+"\n"+strtmp2+"\n"+strtmp3))


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MyWindow()
    app.exec_()