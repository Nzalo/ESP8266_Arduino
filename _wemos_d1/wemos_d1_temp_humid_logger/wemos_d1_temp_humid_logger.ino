
//Have a look at the onboarding tutorial at the relayr Github:
//https://github.com/relayr/ESP8266_Arduino


//Libraries used: To be added manually on the Arduino IDE!
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>


//WiFi credentials: 2.4GHz networks only!
//Avoid long SSIDs and passwords, and use preferably only letters and numbers
#define SSID "INTRODUCE_YOUR_SSID_HERE"
#define PASSWORD "INTRODUCE_YOUR_PASSWORD_HERE"


//Credentials from the developer dashboard
#define DEVICE_ID "INTRODUCE_YOUR_DEVICE_ID_HERE"
#define MQTT_USER "INTRODUCE_YOUR_MQTT_USER_HERE"
#define MQTT_PASSWORD "INTRODUCE_YOUR_MQTT_PASSWORD_HERE"
#define MQTT_CLIENTID "INTRODUCE_YOUR_MQTT_CLIENT_HERE" //It can be anything else
#define MQTT_TOPIC "INTRODUCE_YOUR_MQTT_TOPIC_HERE"
#define MQTT_SERVER "mqtt.relayr.io"


//This configures the sensor and creates the DHT instance
#define DHTPIN D4
#define DHTTYPE DHT11 //Type 22 is recommended
DHT dht(DHTPIN, DHTTYPE);


//This creates the WiFi client and the pub-sub client instance
WiFiClient espClient;
PubSubClient client(espClient);


//Some definitions, including the publishing period
const int led = BUILTIN_LED; //If the LED doesn't work, try changing "BUILTIN_LED" for "D0" or "D4"
boolean ledState = LOW;
unsigned long lastPublishTime = 0;
unsigned long lastBlinkTime = 0;
int publishingPeriod = 2000;
float humidity, temperature;


//Function prototypes
void setup_wifi();
void mqtt_connect();
void callback(char* topic, byte* payload, unsigned int length);
void handlePayload(char* payload);
void publish();


//Setup function
void setup()
{
  //Initializing pins
  pinMode(DHTPIN, INPUT);
  pinMode(led, OUTPUT);

  //Initializing the serial port
  Serial.begin(9600);
  Serial.println("");
  Serial.println("Hello there, I'm your ESP8266.");
  Serial.println("Let's talk to the relayr Cloud!");

  //Initializing the sensor
  dht.begin();

  //Initializing the WiFi
  setup_wifi();
  client.setServer(MQTT_SERVER, 1883);
  client.setCallback(callback);

  //200ms is the minimum publishing period
  publishingPeriod = publishingPeriod > 200 ? publishingPeriod : 200;
  mqtt_connect();
}




//------------------------------------------------------------------------------------//
// This function connects to the WiFi network, and prints the current IP address      //
//------------------------------------------------------------------------------------//

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}




//------------------------------------------------------------------------------------//
// Callback function, necessary for the MQTT communication                            //
//------------------------------------------------------------------------------------//

void callback(char* topic, byte* payload, unsigned int length)
{
  //Store the received payload and convert it to string
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  //Print the topic and the received payload
  Serial.println("topic: " + String(topic));
  Serial.println("payload: " + String(p));
  //Call our method to parse and use the received payload
  handlePayload(p);
}




//------------------------------------------------------------------------------------//
// This processes the payload; commands and configurations should be implemented here //  
//------------------------------------------------------------------------------------//

void handlePayload(char* payload)
{
  StaticJsonBuffer<200> jsonBuffer;
  //Convert payload to json
  JsonObject& json = jsonBuffer.parseObject(payload);
  
  if (!json.success())
  {
    Serial.println("json parsing failed");
    return;
  }

  //Get the value of the key "name", aka. listen to incoming commands and configurations
  const char* command = json["name"];
  Serial.println("parsed command: " + String(command));

  //CONFIGURATION "frequency": We can change the publishing period
  if (String(command).equals("frequency"))
  {
    int frequency = json["value"];
    
    if ( (frequency>=2000) && (frequency<=60000) )
    {
      Serial.println("Adjusting publishing period (ms): " + String(frequency));
      publishingPeriod = frequency;
    }

    else
      Serial.println("The requested publishing period is out of the defined range!");   
  }
}




//------------------------------------------------------------------------------------//
// This function establishes the connection with the MQTT server                      //
//------------------------------------------------------------------------------------//

void mqtt_connect()
{
  Serial.println("");
  Serial.println("Connecting to MQTT server...");
  
  if (client.connect(MQTT_CLIENTID, MQTT_USER, MQTT_PASSWORD))
  {
    Serial.println("Connection successful! Subscribing to topic...");
    //Subscribing to the topic "cmd", so we can listen to commands
    client.subscribe("/v1/"DEVICE_ID"/cmd");
    //And to "config" as well, for the configurations
    client.subscribe("/v1/"DEVICE_ID"/config");
  }

  else
  {
      Serial.println("Connection failed! Check your credentials or the WiFi network");
      //This reports the error code
      Serial.println("rc = ");
      Serial.print(client.state());
      //And it tries again in 5 seconds
      Serial.println("Retrying in 5 seconds...");
      delay(5000);
  }
}




//------------------------------------------------------------------------------------//
// This is for the LED to blink                                                       //
//------------------------------------------------------------------------------------//

void blink(int interval)
{
  if (millis() - lastBlinkTime > interval)
  {
    //Save the last time you blinked the LED
    lastBlinkTime = millis();
    
    if (ledState == LOW)
      ledState = HIGH;
      
    else
      ledState = LOW;
      
    //Set the LED with the ledState of the variable:
    digitalWrite(led, ledState);
  }
}




//------------------------------------------------------------------------------------//
// This is the MAIN LOOP, it's repeated until the end of time! :)                     //
//------------------------------------------------------------------------------------//

void loop()
{
  //If we're connected, we can send data...
  if (client.connected())
  {
    client.loop();
    //Publish within the defined publishing period
        if (millis() - lastPublishTime > publishingPeriod)
        {
            lastPublishTime = millis();
            //Publishing...
            publish();
        }
        //Blink LED  
        blink(publishingPeriod / 2);
  }

  //If the connection is lost, then reconnect...
  else
  {
    Serial.println("Retrying...");
    mqtt_connect();
  }      

  //This function prevents the device from crashing
  //since it allows the ESP8266 background functions to be executed
  //(WiFi, TCP/IP stack, etc.)
  yield();

  //Acquiring values from the sensor
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  //If the routine fails, it'll let us know 
  if (isnan(humidity) || isnan(temperature))
  {
    Serial.println("Failed to read from the DHT sensor!");
  }

  //DHTxx are relatively slow sensors, we have to wait a bit between readings
  //2000ms = 2s by default
  delay(publishingPeriod);
}




//------------------------------------------------------------------------------------//
// Publish function: What we want to send to the relayr Cloud                         //
//------------------------------------------------------------------------------------//

void publish()
{    
  //MQTT_MAX_PACKET_SIZE is defined in "PubSubClient.h", it's 128 bytes by default
  //A modified version with 512 bytes it's available here:
  //https://github.com/uberdriven/pubsubclient
  StaticJsonBuffer<MQTT_MAX_PACKET_SIZE> pubJsonBuffer;
  //Create our JsonArray
  JsonArray& root = pubJsonBuffer.createArray();

//-------------------------------------------------
  //First object: temperature
  JsonObject& leaf1 = root.createNestedObject();
  leaf1["meaning"] = "temperature";
  leaf1["value"] = temperature;
//-------------------------------------------------
  
//-------------------------------------------------  
  //Second object: humidity
  JsonObject& leaf2 = root.createNestedObject();
  leaf2["meaning"] = "humidity";
  leaf2["value"] = humidity;
//-------------------------------------------------
  
  char message_buff[MQTT_MAX_PACKET_SIZE];
  root.printTo(message_buff, sizeof(message_buff));
  client.publish("/v1/"DEVICE_ID"/data", message_buff);
  Serial.println("Publishing " + String(message_buff));
}



