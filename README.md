# Connecting the WeMos D1 to the relayr Cloud

## Arduino-based Code Examples: Introduction

**IMPORTANT:**
Before proceeding with these examples, please follow [this tutorial](https://github.com/relayr/DeveloperDocumentation/tree/master/ESP8266_Arduino), which details how to flash codes on your device.

Here you may find some code examples to quickly connect your [WeMos D1 Mini and WeMos D1 R2](http://www.wemos.cc) to the relayr Cloud. They are written in Wiring, the programming language popularized by Arduino. Files with the extension ".ino" are called sketches.

These examples are highly commented, and in most cases it's enough to go through the code to understand what they do. However, here's a brief description of each of them, for your convenience.

Before diving into the examples, it's important to understand the difference between readings, commands, and configurations. On the relayr Cloud, devices can *send* (publish) **readings**, for example a temperature value provided by a sensor, an analog input, a number resulting from a calculation, or even a message, like the status.

On the other hand, our devices can *listen* (subscribe) to our **commands** too, for example, to toggle an LED, or to activate a motor. That is, commands implement actions.

Besides, we can also send **configurations**, to adjust the refresh rate, or the resolution of the readings. In other words, configurations modify the behavior of our devices.

## The relayr Wizard App
The "wizard app" is a demo code that works out of the box and helps you going through the onboarding process. With "onboarding" we mean to connect your device to the relayr Cloud, in this case publishing and subscribing to data via MQTT. Since this is just a demo, **this app requires no additional hardware**.

#### Readings:

* **Analog Pin 0, set as input:**  
Published in the following format, where `analog0` is an integer: `{"meaning":"analog0","value":analog0}`  
If there's nothing connected to the physical pin, it will display the *floating* value of such pin. If we touch it we will change slightly the voltage, and thus, the value will change.

* **Test Counter:**  
Published in the following format, where `test_counter` is an integer: `{"meaning":"test_counter","value":test_counter++}`  
This counter increments everytime the device publishes, i.e. it's proportional to the publishing period.

#### Commands:

* **Digital Pin 0 (D0), set as output:**  
Toggle ON output D0: `{"name":"d0","value":"high"}`  
Toggle OFF output D0: `{"name":"d0","value":"low"}`

* **Digital Pin 1 (D1), set as output:**  
Toggle ON output D1: `{"name":"d1","value":"high"}`  
Toggle OFF output D1: `{"name":"d1","value":"low"}`

#### Configurations:

* **Adjust publishing period (and thus the message frequency):**  
Where `frequency` is an integer; on the widget displayed at the relayr Developer Dashboard, this value lies between 200ms and 5s (but virtually, it has no limits): `{"name":"d1","value":frequency}`

## Temperature & Humidity Logger
This code uses a DHTxx temperature and humidity sensor, connected in the following way:

```
  GND (sensor) ------------- (board) G or GND
  VCC (sensor) ------------- (board) 3V3
   NC (sensor) ------------- (board) Not connected
  SIG (sensor) ------------- (board) D4
```

It is **highly recommended to use a DHT22 sensor**, since it's much more reliable and accurate.


#### Readings:

* **Temperature:**  
Published in the following format, where `temperature` is a float and stores the value retrieved from the sensor, in °C: `{"meaning":"temperature","value":temperature}`

* **Humidity:**  
Published in the following format, where `humidity` is a float and stores the value retrieved from the sensor, in % (relative humidity): `{"meaning":"humidity","value":humidity}`

#### Commands:

* This code example doesn't feature any command.

#### Configurations:

* **Adjust publishing period (and thus the message frequency):**  
Where `frequency` is an integer; on the widget displayed at the relayr Developer Dashboard, this value lies between 2s and 60s (but virtually, it has no limits): `{"name":"d1","value":frequency}`