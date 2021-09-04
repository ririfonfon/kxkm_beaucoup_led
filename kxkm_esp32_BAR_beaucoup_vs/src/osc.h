#include <WiFiUdp.h>
#include <OSCMessage.h> //https://github.com/stahlnow/OSCLib-for-ESP8266

int recv_port = 1818;
int send_port = 1819;

bool osc_running = false;

IPAddress serverIP;
bool linkStatus = false;
String lastPacket = "";

bool osc_newChannel = false;
int osc_channel = 0;

void oscC_task( void * parameter );
bool oscC_parsePacket(String command, IPAddress remote );
void oscC_beacon(WiFiUDP udp_out);
String oscC_id();
String oscC_next(String& currentData);
void oscC_newChan(bool doit);
String oscC_ch();
bool oscC_isLinked();
bool oscC_newChan();
int oscC_chan();
void oscC_start();


void oscC_task( void * parameter ) {

  unsigned long last_beacon = 0;

  // input socket
  WiFiUDP udp_in;
  udp_in.begin(recv_port);
  char incomingPacket[1472];
  int len;

  // output socket
  WiFiUDP udp_out;

  // loop
  while (osc_running) {

    // Check if incoming packets
    if (udp_in.parsePacket()) {

      //Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
      len = udp_in.read(incomingPacket, 1470);
      if (len >= 0) {
        incomingPacket[len] = 0;

#ifdef DEBUG
        Serial.printf("UDP: packet received: %s\n", incomingPacket);
#endif


        // Parse Packet
        bool valid = oscC_parsePacket(String(incomingPacket), udp_in.remoteIP());

        // Set Server IP
        if (valid && !linkStatus) {
          //serverIP = udp_in.remoteIP();
          linkStatus = true;
        }
      }
    }

    // Beacon out
    if ((millis() - last_beacon) > 2000) {
      oscC_beacon(udp_out);
      last_beacon = millis();
    }

    // yield();
    delay(100);
  }

  vTaskDelete(NULL);
}

bool oscC_parsePacket(String command, IPAddress remote ) {
  String currentData = command;

  // Check identity
  String data = oscC_next(currentData);

  data = oscC_next(currentData);
  if (data == "ping") return true;
  if (data != oscC_id() && data != "all" && data != oscC_ch()) {
#ifdef DEBUG
    Serial.println("Not for me ... " + data);
#endif
    return false;
  }

  // Command
  data = oscC_next(currentData);
  if (data == "hello") ;
  //  else if (data == "sync") {
  //    sync_setHost(remote);
  //    sync_do(oscC_next(currentData).toInt());
  //  }
  //  else if (data == "stop") audio_stop();
  //  else if (data == "play") {
  //    String mediaPath = sd_getPathNote(oscC_next(currentData).toInt(), oscC_next(currentData).toInt());
  //    audio_volume(oscC_next(currentData).toInt());
  //    audio_play(mediaPath);
  //  }
  //  else if (data == "playtest") {
  //    String mediaPath = "test.mp3";
  //    audio_play(mediaPath);
  //  }
  //  else if (data == "volume") audio_volume(oscC_next(currentData).toInt());
  //  else if (data == "setchannel") {
  //    if (!oscC_newChan()) {
  //      osc_channel = oscC_next(currentData).toInt();
  //      oscC_newChan(true);
  //    }
  //  }
  //  else if (data == "setid") settings_set("id", oscC_next(currentData).toInt());
  //  else if (data == "loop") audio_loop((bool) oscC_next(currentData).toInt());
  else if (data == "reset") stm32_reset();
  else if (data == "shutdown") stm32_shutdown();
  //
  //  else if (data == "led") {
  //    String strip = oscC_next(currentData);
  //    int s;
  //    if (strip == "all" ) s = -1;
  //    else s = strip.toInt();
  //
  //    String pixel = oscC_next(currentData);
  //    int p;
  //    if (pixel == "all" ) p = -1;
  //    else p = pixel.toInt();
  //
  //    int red = oscC_next(currentData).toInt();
  //    int green = oscC_next(currentData).toInt();
  //    int blue = oscC_next(currentData).toInt();
  //
  //    leds_setPixel(s, p, red, green, blue);
  //  }
#ifdef DEBUG
  else Serial.printf ("Command unknown: %s\n", data.c_str());
#endif

  return true;
}


//
// Send info beacon as heartbeat (status and autodiscovery)
//
void oscC_beacon(WiFiUDP udp_out)
{
  char mac[18] = { 0 };
  sprintf(mac, "%02X:%02X:%02X", WiFi.BSSID()[3], WiFi.BSSID()[4], WiFi.BSSID()[5]);

  udp_out.beginPacket(serverIP, send_port);

  // OSC over UDP
  OSCMessage msg("/status");
  //msg.add((uint32_t)ESP.getEfuseMac());
  msg.add(BAR_BB_NUMBER);
  msg.add(15);
  msg.add(VERSION);
  msg.add(mac);
  msg.add(WiFi.localIP().toString().c_str());
  msg.add(WiFi.RSSI());
  msg.add(linkStatus);
  msg.add(stm32_batteryLevel());
  msg.add(false); //audio_sdOK
  msg.add("stop");// audio media
  msg.add("");//audio_Error().c_str()
  msg.add(0);//audio bank
  msg.add(0); // % sync sd
  msg.add("");//sunc error

  msg.send(udp_out);

  udp_out.endPacket();
#ifdef DEBUG
  Serial.println("beacon");
#endif
}

//
// Unpack /esp/manual/who/how/what
//
String oscC_next(String& currentData) {
  String dataCopy(currentData.c_str());
  for (int i = 0; i < dataCopy.length(); i++) {
    if (dataCopy.substring(i, i + 1) == "/") {
      currentData = dataCopy.substring(i + 1);
      return dataCopy.substring(0, i);
      break;
    }
  }
  currentData = "";
  return dataCopy;
}


String oscC_id() {
  return "e" + String(BAR_BB_NUMBER);
}

String oscC_ch() {
  byte ch = 15;
  String ans = "c";
  if (ch < 10) ans += "0";
  ans += String(ch);
  return ans;
}

bool oscC_isLinked() {
  return linkStatus;
}

bool oscC_newChan() {
  return osc_newChannel;
}

void oscC_newChan(bool doit) {
  osc_newChannel = doit;
}

int oscC_chan() {
  return osc_channel;
}

void oscC_start() {

  osc_channel = BAR_BB_NUMBER;

  IPAddress myIP = WiFi.localIP();
  IPAddress mask = WiFi.subnetMask();

  serverIP[0] = myIP[0] | (~mask[0]);
  serverIP[1] = myIP[1] | (~mask[1]);
  serverIP[2] = myIP[2] | (~mask[2]);
  serverIP[3] = myIP[3] | (~mask[3]);

#ifdef DEBUG
  Serial.print("OSC: Broadcasting on ");
  Serial.println(serverIP);
#endif

  osc_running = true;

  xTaskCreatePinnedToCore(
    oscC_task,
    "oscC_task",
    10000,
    NULL,
    1,
    NULL,
    0);
}


