# The relayr Wizard App

The "wizard app" is a demo code that works out of the box and helps you going through the onboarding process. With "onboarding" we mean to connect your device to the relayr Cloud, in this case publishing and subscribing to data via MQTT.

## Required hardware:

Since this is just a demo, **this app requires no additional hardware** aside from the board itself.

## Model on the Developer Dashboard:

When adding your device, select the model **"Adafruit HUZZAH"** on the relayr Developer Dashboard.

## Readings:

* **Analog Pin 0, set as input:**  
Published in the following format, where `analog0` is an integer: `{"meaning":"analog0","value":analog0}`  
If there's nothing connected to the physical pin, it will display the *floating* value of such pin. If we touch it we will change slightly the voltage, and thus, the value will change.

* **Test Counter:**  
Published in the following format, where `test_counter` is an integer: `{"meaning":"test_counter","value":test_counter++}`  
This counter increments everytime the device publishes, i.e. it's proportional to the publishing period.

## Commands:

* **Digital Pin 0 (D0), set as output:**  
Toggle ON output D0: `{"name":"d0","value":"high"}`  
Toggle OFF output D0: `{"name":"d0","value":"low"}`

* **Digital Pin 1 (D1), set as output:**  
Toggle ON output D1: `{"name":"d1","value":"high"}`  
Toggle OFF output D1: `{"name":"d1","value":"low"}`

## Configurations:

* **Adjust publishing period (and thus the message frequency):**  
Where `frequency` is an integer; on the widget displayed at the relayr Developer Dashboard, this value lies between 200ms and 5s (but virtually, it has no limits): `{"name":"d1","value":frequency}`
