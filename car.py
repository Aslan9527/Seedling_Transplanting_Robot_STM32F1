import sensor, image, time, math
from pyb import UART,LED

uart = UART(3,9600)
uart.init(9600, bits=8, parity=None, stop=1)

red_led   = LED(1)
green_led = LED(2)

thresholds =(39, 76, 24, 127, -128, 127)# (42, 72, 32, 121, -115, 114)
my_roi = [50,0,220,240]
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False) # must be turned off for color tracking
clock = time.clock()

while(True):
    clock.tick()
    img = sensor.snapshot()
    blobs = img.find_blobs([thresholds],area_threshold=25,merge =True,margin =50)
    if blobs :
        for blob in blobs:
            img.draw_rectangle(blob.rect())
            img.draw_cross(blob.cx(), blob.cy())
            b = blobs[0]
            img.draw_rectangle(b[0:4])
            Lm =int((b[2]+b[3])/2)

            #print(Lm,blob.cx(),blob.cy(),clock.fps())

            data = bytearray([0xb3,0xb3,blob.cx(),Lm,0x5b])
            uart.write(data)
            red_led.on()
    else:
        #print('没物体')
        data = bytearray([0xb3,0xb3,0xa0,0x00,0x5b])
        uart.write(data)    #打印XY轴的偏移坐标
        red_led.off()
