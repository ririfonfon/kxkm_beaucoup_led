/////////////////////////////////////////lib/////////////////////////////////////////
#include <WiFi.h>
//#include <WiFiUdp.h>
//#include <ArtnetWifi.h>

/////////////////////////////////////////Wifi settings/////////////////////////////////////
//const char* ssid = "kxkm-wifi";
//const char* password = "KOMPLEXKAPHARNAUM";
const char* ssid = "kxkm24";
const char* password = "";

bool wifi_available = false;

//IPAddress ip(2, 0, 0, BAR_BB_NUMBER + 100); // Static IP
//IPAddress gateway(2, 0, 0, 1);
//IPAddress subnet(255, 0, 0, 0);

void ConnectWifi();
void wifi_event(WiFiEvent_t event);
bool wifi_isok();

void ConnectWifi() {
  WiFi.onEvent(wifi_event);
  //  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
#ifdef DEBUG
  Serial.println("");
  Serial.println("Connecting to WiFi");
  // Wait for connection
  Serial.print("Connecting");
#endif
}//ConnectWifi

void wifi_event(WiFiEvent_t event) {
  static byte retry = 0;
  static byte maxRetry = 15;

  switch (event) {
    case SYSTEM_EVENT_STA_DISCONNECTED:
      master = 0;
      rr = 0;
      gg = 0;
      bb = 0;
      ww = 0;
      mod = 0;
      pix_mod = 0;
      pix_start = 0;
      modulo = 0;
      str_ws = 0;
      pix_center = 0;
      srr = 0;
      sgg = 0;
      sbb = 0;
      sww = 0;
      color_mode = 0;
      mirror = 0;
      break;
  }


  switch (event) {
    case SYSTEM_EVENT_STA_CONNECTED:
#ifdef DEBUG
      Serial.print("WiFi connected - ");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
#endif
      break;
    case SYSTEM_EVENT_STA_GOT_IP:
#ifdef DEBUG
      Serial.print("Got IP - ");
      Serial.println(WiFi.localIP());
#endif
      if (client.connect(nodeName)) {
#ifdef DEBUG
        Serial.println("connected");
#endif
        client.subscribe( ("k32/c"+String(BAR_BB_NUMBER)+"/leds").c_str() );
        client.subscribe( "k32/all/leds" );
      } else {
#ifdef DEBUG
        Serial.print("failed, rc=");
        Serial.print(client.state());
#endif
      }
      break;
    case SYSTEM_EVENT_STA_LOST_IP:
#ifdef DEBUG
      Serial.print("Lost IP..");
#endif
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
#ifdef DEBUG
      Serial.print("WiFi lost connection... ");
#endif
      break;
  }


  if (event == SYSTEM_EVENT_STA_DISCONNECTED) {
    wifi_available = false;
    retry += 1;

    #ifdef DEBUG
        Serial.print(" reconnecting ");
        Serial.print(retry);
        Serial.print("/");
        Serial.println(maxRetry);
    #endif
    WiFi.reconnect();
  }
  else if (event == SYSTEM_EVENT_STA_GOT_IP) {
    wifi_available = true;
    retry = 0;
  }
}// wifi_event

bool wifi_isok() {
  return wifi_available;
}//wifi_isok()
