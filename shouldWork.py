import app_controller as ap
from time import sleep
from serial import Serial
from math import atan2, pi
from communication import robot as ab

######### bindig port for socket host
port = 8000
while True:
    try:
        session = ap.joy(port)
        break
    except:
        port += 1

######### get connection info and save image
_, img = session.info(port)
print(*session.getIP())
print(_)
img.save("qrcode.jpg")
img.show()
session.connect()
print("connected")

######### connect to robot
wire = ab()


while True:
    ret = session.update() #update data in session, ret returns vals if you are connected, but None if disconnected
    #print(ret)
    if ret is None:
        #if disconnected retry to connect
        print("Reconnecting...")
        _, img = session.info(port)
        print(_)
        addr = session.getIP()
        session.connect()
    data = session.read()
    
    ######### calculate
    ang =  int((pi + atan2(data[14], data[15])) * 1000)
    if(int(data[14]) == 0 and  int(data[15]) == 0):
        ang = 0
    sp = int((data[16] + 3) * 1000)
    dist = int((data[17] + 3) * 1000)
    
    deg = ang / 1000  / pi *180
    
    print(deg, sp, dist)
    wire.write(ang, sp, dist)
