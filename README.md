To put together...  
sudo esptool.py --port /dev/cu.SLAB_USBtoUART write_flash 0x00000 ESP_8266_BIN0.92.bin

screen /dev/cu.SLAB_USBtoUART

ls /dev/cu.*

https://github.com/me-no-dev/EspExceptionDecoder

2.4 Ghz WiFi network (and not to a 5 Ghz one)  
Check the cable (sometimes, WunderBar cables don't work if you wanna use the serial port!)


# How To Flash Your ESP8266-based Board with the Example Code Using the Arduino IDE

[comment]: <> (This application allows you to control the color of the **RGB LED**, toggle the **digital outputs `D0` and `D1`**, and display the values of the **analog inputs `A0` and `A1`** directly in the developer dashboard.)

##Install the driver
cp2102 driver  
https://www.silabs.com/products/mcu/Pages/USBtoUARTBridgeVCPDrivers.aspx

In some boards: http://iot.fkainka.de/en/driver

## 1. Install the required libraries
* ESPWiFi (+ the boards manager!)  
 How to install the ESP8266 boards package, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266-based board in "Tools -> Board"

* **[PubSubClient](https://github.com/uberdriven/pubsubclient)**: 
* **[ArduinoJSON](https://github.com/bblanchon/ArduinoJson)**: used to encode the data we want to send to the cloud in JSON format. Download the 

[comment]: <> (EVERYTHING DOWN HERE FOR NOW...)

...

...


## 2. Paste the Code
For every new app, the IDE will create a default template, with the functions `setup()` and `loop()`. **Remove the content** of the entire page, and **paste the example code** provided by the relayr Developer Dashboard.

After that, **remove the first two lines of code**, which include two libraries, as shown below. But don't panic! We will re-add them manually in the next step.

<img src="assets/step2-1.png" class="center" width=1000px>

**Don't forget to save it**, clicking on the icon which looks like a small folder, on the left bar.

## 3. Add the Required Libraries
In the Particle IDE, libraries have to be added manually for every new app we create, that's why we remove the `#include` directives in the previous step.

First we'll be **adding the MQTT protocol library**, necessary for the communication. On the left bar of the screen, on the bottom, click on the icon that looks a small bookmark.

<img src="assets/step3-1.png" class="center" width=1000px>

Then click on "include in app," as shown below.

<img src="assets/step3-2.png" class="center" width=1000px>

And an additional line of code will pop up at the beginning of your code. **Click on save** to prevent unnecessary frustrations (remember, the icon that looks like a folder).

Now let's **add the JSON library**, which is named SparkJson, and follow the same procedure.

<img src="assets/step3-3.png" class="center" width=1000px>

At this point your code should look more or less like this:

<img src="assets/step3-4.png" class="center" width=1000px>

## 4. Downgrade the Version of the Compiler
To be completely sure that your app will work, we strongly recommend to **downgrade the version of the compiler**, since there are known issues with the new version and the MQTT library.

For that, on the Particle IDE, simply **click on "devices,"** on the left bar of the window (an icon that looks like a target). Then click on your device, and you'll see the option "you are building with firmware:". Now **select version 0.4.5**.

<img src="assets/step4-1.png" class="center" width=1000px>

## 5. Flash Your Photon
Now you should be ready to go, so **click on "flash"** (lightning bolt icon on the left bar) and your device will be updated.

<img src="assets/step5-1.png" class="center" width=1000px>

If everything went well, the blue LED of your Photon will be blinking with a constant pattern, meaning that it's connected and properly publishing.

## 6. Let's Test It!

Now you can **go back to the [relayr Developer Dashboard](https://developer.relayr.io)**, click on "devices" and select your Photon. **Under "readings" you will see the raw data coming from the analog ports**. As a quick test, you can touch the pins `A0` and `A1` with the tip of your fingers, and you'll see how the values change.

Besides, you can send commands **to make sure that the communication with the relayr Cloud works in both directions**. This code implements some predefined commands for that purpose, like toggling the digital pins `D0` and `D1` directly from the dashboard, and to change the color of the RGB LED.
