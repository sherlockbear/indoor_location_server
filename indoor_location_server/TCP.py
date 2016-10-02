from socketserver import (TCPServer as TCP, StreamRequestHandler as SRH, ThreadingMixIn as TMI)  #可以通过as起别名
from time import ctime
from extract_fingerprint import extract
from insert import *

HOST = '192.168.1.101'
PORT = 1234
ADDR = (HOST, PORT)
class Server(TMI, TCP):
    pass

class MyRequestHandler(SRH):
    def handle(self):
        print ('已经连接:', self.client_address)
        while True:  
            request = self.request.recv(1024)  
            if not request:   
                break
            request_pri = str(request, encoding = "utf-8")
            print(request_pri)
            '''fingerprint=extract(request_pri)
            print(fingerprint)'''
            self.request.send(request) 
        '''self.request.sendall(bytes('OK',encoding = "utf-8"))'''
        #插入数据
        '''fingerprint=extract(request)
        print(fingerprint)
        storageOfFingerprint([1,5,8],fingerprint)
        data_view()'''

tcpServ = Server(ADDR, MyRequestHandler)
print ('等待新的连接。。。。')

tcpServ.serve_forever()
