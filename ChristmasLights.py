import neopixel
import machine
import time
import twinkleLights

np = neopixel.NeoPixel(machine.Pin(26), 1, timing=1)
n = np.n



#np.write()
# np[1] = (0, 64, 0) # set to green, half brightness
# np[2] = (0, 0, 64)  # set to blue, quarter brightness
print('Hello World')
twinkleLights.twinkleLights(np)
   
#demo.demo(np)