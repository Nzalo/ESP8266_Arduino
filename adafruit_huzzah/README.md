# Arduino Examples for the Adafruit HUZZAH

***IMPORTANT!***  
*Before proceeding with any example, please follow [this tutorial](https://github.com/relayr/ESP8266_Arduino), which details how to flash codes on your device, and explains what are the readings, the commands and the configurations, and how to work with them.*

--

Here you may find some code examples to quickly **connect your [Adafruit HUZZAH](https://www.adafruit.com/product/2471) to the relayr Cloud**. They are written in Wiring, the programming language popularized by Arduino. Files with the extension ".ino" are called sketches.

These examples are highly commented, and in most cases it's enough to go through the code to understand what they do. However, here's a brief description of each of them, for your convenience.

Before diving into the examples, it's important to understand the difference between readings, commands, and configurations. On the relayr Cloud, devices can *send* (publish) **readings**, for example a temperature value provided by a sensor, an analog input, a number resulting from a calculation, or even a message, like the status.

On the other hand, our devices can *listen* (subscribe) to our **commands** too, for example, to toggle an LED, or to activate a motor. That is, commands implement actions.

Besides, we can also send **configurations**, to adjust the refresh rate, or the resolution of the readings. In other words, configurations modify the behavior of our devices.