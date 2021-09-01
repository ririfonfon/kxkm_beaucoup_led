/**************************************************************************/
/*!
    @file     kxkm_esp8266_midi_dmx
    @author   riri
    @NodeMCU 1.0(ESP-12E Module)
*/
/**************************************************************************/

/****************************** WIFI ********************/
#include <ESP8266WiFi.h>
#include <PubSubClient.h> //https://github.com/knolleary/pubsubclient

const char *ssid = "kxkm24";
const char *password = "";

// const char *ssid = "riri_new";
// const char *password = "B2az41opbn6397";

const char *mqtt_server = "2.0.0.1";

WiFiClient espClient;
PubSubClient client(espClient);

// #define DEBUG 1
// #define DEBUGDMX 1
// #define DEBUGDMXvalue 1

/****************************** DMX ********************/
#include <LXESP8266UARTDMX.h> //https://github.com/claudeheintz/LXESP8266DMX

#define DMX_DIRECTION_PIN D3
#define DMX_SERIAL_OUTPUT_PIN D4
long level;
uint8_t part;
float dmxbuffer[DMX_MAX_FRAME];

#include <dmx.h>
#include <fonction_wifi.h>

/**************************** SETUP ********************/
void setup()
{

#ifdef DEBUG
  Serial.begin(115200);     //74880 freq de l'esp8266 crash
  Serial.setDebugOutput(1); //use uart0 for debugging
  Serial.println("setup");
#endif

  pinMode(DMX_DIRECTION_PIN, OUTPUT);
  digitalWrite(DMX_DIRECTION_PIN, HIGH);

  pinMode(DMX_SERIAL_OUTPUT_PIN, OUTPUT);
  ESP8266DMX.startOutput();

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(copyDMXToOutput);

#ifdef DEBUG
  Serial.println("setup complete");
#endif
}

/***************************** LOOP ********************/
void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
}
