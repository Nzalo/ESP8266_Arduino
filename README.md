# How to Connect ESP8266-based Devices to the relayr Cloud Using Arduino

The ESP8266 is a low-cost Wi-Fi chip with full TCP/IP stack and microcontroller capabilities. Its very low price, high availability, and big supporting community make it the perfect choice when developing rapid IoT-enabled prototypes.

In this repository you will find **code examples to connect to the relayr Cloud the most popular ESP8266-based development kits** in the market. The codes are slightly different from device to device (depending on the configuration and the manufacturer), so they are sorted in different folders.

## Pre-requisites

Let's install the following tools first:

* **[USB - TTL driver](http://www.wemos.cc/downloads/)**: if your laptop is running Windows or Mac, you’ll have to install this driver to be able to interface with the provided devkit. In Linux it’s not necessary, as it comes by default.

* **[Arduino IDE](https://www.arduino.cc/en/Main/Software)**: we will use it to develop our sketches, to flash the code in our devices and to inspect the serial data coming from them.

* **[Python 2.7](https://www.python.org/downloads/)**: required to install additional tools. Mac and most Linux distros have it by default, but you will have to install it if you use Windows.

## Adding the board to the Arduino IDE

To work with ESP8266-based development kits, first you will have to add the device itself to the boards manager, so the different models are recognized by the IDE. Simply follow these steps:

1. Start the Arduino IDE and open `Preferences`.

2. Copy and paste the link `http://arduino.esp8266.com/stable/package_esp8266com_index.json` into the Additional Boards Manager URLs field.

3. Open `Tools` → `Board: xxx` → `Boards Manager` and install "esp8266" by "ESP8266 Community".

4. After the installation, select the board that you will be using from `Tools` → `Board`.

## Required Libraries

To include 3rd party libraries in the Arduino IDE, simply download them from the GitHub repositories, and leave them as `.ZIP` files. Later on, in the Arduino IDE, navigate to `Sketch` → `Include Library`. At the top of the drop down list, select the option `Add .ZIP Library`. Now select the libraries from your file manager (one by one), and they will be integrated onto the IDE. To learn more, you may follow [this tutorial](https://www.arduino.cc/en/Guide/Libraries).

These code examples require the following libraries. Make sure to add them before getting started. Otherwise you will run into compilation errors!

* **[Arduino Client for MQTT](https://github.com/uberdriven/pubsubclient)**: this library provides a client for doing simple publish/subscribe messaging with an MQTT broker. This is just a modification of the excellent library developed by Nick O'Leary. For convenience, the maximum message size has been increased to 512 bytes. The rest remains the same.

* **[Arduino JSON](https://github.com/bblanchon/ArduinoJson)**: an efficient library for embedded systems that allows easy JSON decoding and encoding.

* **[DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library)**: arduino library for the DHT series of low cost temperature/humidity sensors.

## Select Your Board and Choose an Example

Now you're almost ready to go. Navigate to the folder with the examples suitable for your board, and follow the instructions that you may find there.

Please note that this repository is a work in progress! Time permitting, new boards will be added regularly, so stay tuned. Happy prototyping!