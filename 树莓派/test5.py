#coding=utf-8

import socketserver
import serial    #import serial module
import json
import threading
import time


class MyTCPHandler(socketserver.BaseRequestHandler):   
    def handle(self):
        self.ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)  # open named p$
        print(self.client_address[0],"连接到了客户端")
        thread=ShowArduinoThread(self)
        while True:
            self.sendInfo("ok")
            try:
                #接收用户指令
                data=self.recvInfo(1024)
                #根据用户发出的指令，驱动电机
                self.controller(data)
            except ConnectionError as e:
                print('%s断开了连接！'%self.client_address[0])
                break
    def controller(self,data):
        if (data =="close"):
            print("close motor")
            self.sendAduinoInfo("C")
            self.dumpMotorState(False)
        elif(data=="open"):
            print('open motor')
            self.sendAduinoInfo("O")
            self.dumpMotorState(True)
        elif(data=="openNoopsyche"):
            print('open noopsyche')
            self.sendAduinoInfo('A')
        elif(data=="closeNoopsyche"):
            print('close Noopsyche')
            self.sendAduinoInfo('N')
    def dumpMotorState(self,state):
      json.dump(state,open("./motorState","w"))
    def loadMotorState(self):
      return json.load(open("./motorState","r"))
    def sendAduinoInfo(self,str):
        self.ser.isOpen()
        try:
            while 1:
                response = self.ser.readline().decode()
                if response.strip() == "ok":
                    break
                else:
                    print(response)
                self.ser.write(str.encode("utf8"))  # writ a string to port
        except:
            print("串口打开失败")
            self.request.close()
            self.ser.close()
    def sendInfo(self,info):
        self.request.send(info.encode())
    def recvInfo(self,size):
        return self.request.recv(size).decode()
class ShowArduinoThread(threading.Thread):
    def __init__(self,Command):
        super(ShowArduinoThread, self).__init__()
        self.command=Command
    def run(self):
        print("thread start")
        while True:
          response = self.command.ser.readline()
          print(response.decode("utf8"))
          self.command.sendInfo(response.decode())
          time.sleep(1)

if __name__ == '__main__':
      HOST,PORT="192.168.43.156",6962
      server=socketserver.TCPServer((HOST,PORT),MyTCPHandler)
      print('监听消息中……')
      server.serve_forever()

