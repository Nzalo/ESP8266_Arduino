## Pre-requisites

* **[USB - TTL driver](http://www.wemos.cc/downloads/)**: if your laptop is running Windows or Mac, you’ll have to install this driver to be able to interface with the provided devkit. In Linux it’s not necessary, as it comes by default.

* **[Arduino IDE](https://www.arduino.cc/en/Main/Software)**: we will use it to develop our sketches, to flash the code in our devices and to inspect the serial data coming from them.

* **[Python 2.7](https://www.python.org/downloads/)**: required to install additional tools. Mac and most Linux distros have it by default, but you will have to install it if you use Windows.

## Adding the board to the Arduino IDE

1. Start Arduino and open `Preferences`.

2. Enter `http://arduino.esp8266.com/stable/package_esp8266com_index.json` into Additional Boards Manager URLs field.

3. Open `Tools` → `Board:xxx` → `Boards Manager` and install esp8266 by ESP8266 Community.

4. Select the board from `Tools` → `Board` after the installation.
