import neopixel
import machine
import time

np = neopixel.NeoPixel(machine.Pin(26), 50)
np[0] = (0, 0, 128) # set to red, full brightness
np[1] = (0, 128, 0)
np[2] = (128, 0, 0)
np[3] = (0, 128, 128)
np[4] = (128, 0, 128)
np[5] = (128, 128, 0)
np[6] = (128, 128, 128)
np.write()
# np[1] = (0, 64, 0) # set to green, half brightness
# np[2] = (0, 0, 64)  # set to blue, quarter brightness
print('Hello World')




def demo(np):
    n = np.n

    # cycle
    for i in range(4 * n):
        for j in range(n):
            np[j] = (0, 0, 0)
        np[i % n] = (255, 255, 255)
        np.write()
        time.sleep_ms(25)

    # bounce
    for i in range(4 * n):
        for j in range(n):
            np[j] = (0, 128, 128)
        if (i // n) % 2 == 0:
            np[i % n] = (0, 0, 0)
        else:
            np[n - 1 - (i % n)] = (0, 0, 0)
        np.write()
        time.sleep_ms(60)

    # fade in/out
    for i in range(0, 4 * 256, 8):
        for j in range(n):
            if (i // 256) % 2 == 0:
                val = i & 0xff
            else:
                val = 255 - (i & 0xff)
            np[j] = (val, 0, 0)
        np.write()

    # clear
    for i in range(n):
        np[i] = (0, 0, 0)
    np.write()
    
demo(np)