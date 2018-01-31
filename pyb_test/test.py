import pyb

leds = []

for i in range(1,5):
    leds.append(pyb.LED(i))

def rainbow():
    for i in range(0,100):
        for l in leds:
            l.toggle()
            pyb.delay(100)
