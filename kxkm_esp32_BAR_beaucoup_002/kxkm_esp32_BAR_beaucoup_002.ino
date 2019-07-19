/////////////////////////////////////////ID/////////////////////////////////////////
#define BAR_BB_NUMBER 6
#define VERSION 20
#define NOEUX 0

////////////////////////////////////////TaskHandle_t //////////////////////////////////
//TaskHandle_t Map1;
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

/////////////////////////////////////////Adresse/////////////////////////////////////
//#define adr (1+(BAR_BB_NUMBER-1)*16)
#define adr 1
#define NUM_LEDS_PER_STRIP 120
int N_L_P_S = NUM_LEDS_PER_STRIP;

/////////////////////////////////////////Debug///////////////////////////////////////
//#define DEBUG 1
//#define DEBUG_dmx 1
//#define DEBUG_STR 1

/////////////////////////////////////////lib/////////////////////////////////////////
#include "KXKM_STM32_energy_API.h"
#include <WiFi.h>
//#include <WiFiUdp.h>
//#include <ArtnetWifi.h>//https://github.com/rstephan/ArtnetWifi
#include <PubSubClient.h>//https://github.com/knolleary/pubsubclient
const char* mqtt_server = "2.0.0.1";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastRefresh = 0;
#define REFRESH 10
unsigned long lastRefresh_bat = 0;
#define REFRESH_BAT 100


#if defined(ARDUINO) && ARDUINO >= 100
// No extras
#elif defined(ARDUINO) // pre-1.0
// No extras
#elif defined(ESP_PLATFORM)
#include "arduinoish.hpp"
#endif

#define HBSIZE 32
char nodeName[HBSIZE];
byte myID;

///////////////////////////////Lib esp32_digital_led_lib//////////////////////////////
#include "esp32_digital_led_lib.h"
#define min(m,n) ((m)<(n)?(m):(n))
#define NUM_STRIPS 2
int PINS[NUM_STRIPS] = {22, 21};
const int numberOfChannels = NUM_STRIPS * NUM_LEDS_PER_STRIP * 4;
const int numberOfLed =  NUM_LEDS_PER_STRIP ;
strand_t STRANDS[NUM_STRIPS];
strand_t * strands [] = { &STRANDS[0], &STRANDS[1]};
bool randArray[numberOfLed];

///////////////////////////////////dmx variables////////////////////////////////////
float pi_n_1_r[NUM_LEDS_PER_STRIP];
float pi_n_1_g[NUM_LEDS_PER_STRIP];
float pi_n_1_b[NUM_LEDS_PER_STRIP];
float pi_n_1_w[NUM_LEDS_PER_STRIP];

float pi_1_r[NUM_LEDS_PER_STRIP];
float pi_1_g[NUM_LEDS_PER_STRIP];
float pi_1_b[NUM_LEDS_PER_STRIP];
float pi_1_w[NUM_LEDS_PER_STRIP];

float pi_1_sr[NUM_LEDS_PER_STRIP];
float pi_1_sg[NUM_LEDS_PER_STRIP];
float pi_1_sb[NUM_LEDS_PER_STRIP];
float pi_1_sw[NUM_LEDS_PER_STRIP];

int color_mode;
int mirror;

unsigned long now;
int effet_etat = 0;
int last_time_effet = 0;
int type_effet = 0;
int modulo = 0;
unsigned int str_ws = 0;
unsigned int l_str;
int type_modulo = 0;
int str = 0;
int str_l = 0;
int pix_pos;
int pix_pos_v;
int pix_start;
int pix_center;
int pix_end;
int master;
float rrr;
float ggg;
float bbb;
float www;
float rr;
float gg;
float bb;
float ww;
float r;
float g;
float b;
float w;
float srr;
float sgg;
float sbb;
float sww;
int mod;
int pix_mod;
unsigned long t_now_effet = 0;
uint8_t strob_count = 0;
uint8_t strob_count_l = 0;
unsigned long str_ws_last = 0;
unsigned long t_last_l = 0;
#define STROB_FRACTION 5
#define STROB_ON 1
#define STROB_ON_MS 15
#define STROB_FRACTION_L 5
#define STROB_ON_L 1
#define STROB_ON_MS_L 15
int l_s_count = 1;
int pix_start_v;
int ref_pix_pos;
float pix_coef;
float pix_coefi;
float pix_coef_fond;
float pix_coefi_fond;
int M_g;
int M_g_ref;
int M_g1;
int M_g1_ref;
int M_g2;
int M_g2_ref;
int M_g3;
int M_g3_ref;
int M_g4;
int S_seuil;
int old_S_seuil = 0;
int S_count;
int a;
float str_blind_ws = 1;
float str_blind_l = 1;

///////////////////////////////////// baterie variable /////////////////////////////////////

int percentage;
int led_niv = 10;
int etat_r = 0;

///////////////////////////////////// Artnet settings /////////////////////////////////////
//ArtnetWifi artnet;
////const int startUniverse = 0; // CHANGE FOR YOUR SETUP most software this is 1, some software send out artnet first universe as 0.
//const int startUniverse = NOEUX; // CHANGE FOR NOEUX.
//
//// Check if we got all universes
//const int maxUniverses = numberOfChannels / 512 + ((numberOfChannels % 512) ? 1 : 0);
//bool universesReceived[maxUniverses];
//bool sendFrame = 1;
//int previousDataLength = 0;

///////////////////////////////////////////////// SETUP ////////////////////////////////////////
void setup() {

    Serial.begin(115200);

  ///////////////////////////////////////////////// BAR_BB_NUMBER ID //////////////////////////////////////
#ifdef BAR_BB_NUMBER
  eeprom_setID((byte)BAR_BB_NUMBER);
#endif

  // NAME
  myID = eeprom_getID();
  String myName("BAR_BB");
  sprintf(nodeName, "BAR_BB %02i %i", myID, VERSION);
#ifdef DEBUG
  Serial.print("Starting ");
  Serial.println(nodeName);
#endif

  leds_init();
  ConnectWifi();
  // OTA
  ota_setup();
  //  artnet.begin();
  //  artnet.setArtDmxCallback(onDmxFrame);
  client.setServer(mqtt_server, 1883);
  client.setCallback(onDmxFrame);
  initTest();

  //  create a task that will be executed in the Map1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(Map1code, "Map1code", 4096, NULL, 1, NULL, 1);   // core 1 = loop
  xTaskCreatePinnedToCore(effTask, "effTask", 4096, NULL, 1, NULL, 0);    // core 0 = wifi

  ///////////////////////////////////////////////// osc //////////////////////////////////////
  oscC_start();

}//setup

///////////////////////////////////////// LOOP /////////////////////////////////////////////////
void loop() {
  if (wifi_isok()) {
    //    artnet.read();
    client.loop();
    //    Map1code();
    eff_modulo();
    //    effet();
  }// if wifi

  //  if ((millis() - lastRefresh) > REFRESH) {
  //    if (!wifi_isok())  ledBlack();//passe led noir
  //    lastRefresh = millis();
  //  }
  //  // MILLIS overflow protection
  //  if (millis() < lastRefresh) {
  //    lastRefresh = millis();
  //  }

  // OTA
  ota_loop();
}//loop
