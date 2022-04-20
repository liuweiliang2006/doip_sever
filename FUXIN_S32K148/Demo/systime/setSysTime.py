import datetime
#import time
import serial #导入模块
#import struct
#python.exe -m pip install --upgrade pip
#pip3 install pyserial
try:
  #端口，GNU / Linux上的/ dev / ttyUSB0 等 或 Windows上的 COM3 等
  portx="COM10"
  #波特率，标准值之一：50,75,110,134,150,200,300,600,1200,1800,2400,4800,9600,19200,38400,57600,115200
  bps=115200
  #超时设置,None：永远等待操作，0为立即返回请求结果，其他值为等待超时时间(单位为秒）
  timex=5
  # 打开串口，并得到串口对象
  ser=serial.Serial(portx,bps,timeout=timex)

  now = datetime.datetime.now()
  print(ser.name)
  print(now.year)
  print(now.month)
  print(now.day)
  print(now.hour)
  print(now.minute)
  print(now.second)
  currenttime = ([now.month,now.day,now.hour,now.minute,now.second])
  # 写数据
  result=ser.write("time".encode("gbk"))
  result=ser.write(currenttime)
  #result=ser.write("ABCDE".encode("gbk"))
  print("写总字节数:",result)

  ser.close()#关闭串口

except Exception as e:
    print("---异常---：",e)