# Temperature & Humidity Logger

This example shows how to implement a low-cost IoT temperature & humidity logger based on the popular DHTxx sensor. By default, it transmits the temperature in degrees Celsius and the relative humidity (a percentage).

## Required hardware:

The DHTxx sensor should be connected to the Adafruit HUZZAH board in the following way:

```
  GND (sensor) ------------- (board) G or GND
  VCC (sensor) ------------- (board) 3V3
   NC (sensor) ------------- (board) Not connected
  SIG (sensor) ------------- (board) D4
```

It is **highly recommended to use a DHT22 sensor**, since it's much more reliable and accurate.

## Model on the Developer Dashboard:

When adding your device, select the model **"Adafruit HUZZAH (temp/humid logger)"** on the relayr Developer Dashboard.


## Readings:

* **Temperature:**  
Published in the following format, where `temperature` is a float and stores the value retrieved from the sensor, in °C: `{"meaning":"temperature","value":temperature}`

* **Humidity:**  
Published in the following format, where `humidity` is a float and stores the value retrieved from the sensor, in % (relative humidity): `{"meaning":"humidity","value":humidity}`

## Commands:

* This code example doesn't feature any command.

## Configurations:

* **Adjust publishing period (and thus the message frequency):**  
Where `frequency` is an integer; on the widget displayed at the relayr Developer Dashboard, this value lies between 2s and 60s (and it's limited on the code, so the device will ignore values that exceed these limits): `{"name":"frequency","value":frequency}`