import numpy as np
import serial
import time
serdev = 'COM4'
s = serial.Serial(serdev)
#void locate(int column, int row); 
s.write(b'1')
time.sleep(1)
# void cls();
s.write(b'2')
time.sleep(1)
#int rows();
s.write(b'3')
time.sleep(1)
line = s.readline()
print(line.decode())
#int columns();
s.write(b'4')
time.sleep(1)
line = s.readline()
print(line.decode())
#int putc(int c);
s.write(b'5')
s.close
