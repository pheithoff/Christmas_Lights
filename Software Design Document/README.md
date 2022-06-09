# Software Design Document - Christmas_Lights

# Library Selection
This section is to compare the execution time of the NeoPixel library with the FastLED library. The NeoPixel library is run from the Thonny IDE using Micropython and the FastLED library was ran from the Arduino IDE in C.

## Execution Time - NeoPixel Library
A study was ran using 50 LED's to estimate the execution time of writing new states to the LEDs and learn how the execution time relates to number of LEDs. The study used the neoPixel library and ran execution time tests turning on 1, 10, 25, and 50 with the data stored in LED_ExecutionTime.xlsx spreadsheet.<br>

From the study it appears to be a linear relationship between number of LED's and writing a new state to the LEDs. This relationship has the equation of: $y = 30.213x + 647.45$ with time in units of microseconds. We can conclude that scaling this project to ~500 LEDs the time to write a new state to all LEDs will be about 15781 microseconds or 15.781 ms. That is an approximate refresh rate of 63 Hz.<br>

## Execution Time - FastLED Library

https://github.com/FastLED/FastLED/wiki/<br>
The FastLED in comparison, had the same amount of execution time per pixel but had a much faster start-up time of just 30 microseconds. For 50 LEDs it took only 1554 microseconds in comparison to the NeoPixel library which took 2181 microseconds.<br>
We can estimate that for 500 LEDs the time to write a new state to all LEDs will be about 15080 microseconds which is a refresh rate of 66.3 Hz. This 


# Determining Refresh Rate
To decide on refresh rate we know we will have a maximum refresh rate of 63 Hz. This refresh rate is not practical in reality because it will take a certain amount of time to calculate the next state of the LEDs. This section is used to determine what an appropriate refresh rate should be.




