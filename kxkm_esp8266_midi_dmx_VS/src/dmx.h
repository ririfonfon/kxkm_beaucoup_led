String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void copyDMXToOutput(char* topic, unsigned char* data, unsigned int length) {

  char payload[length];
  for (int j=0; j<length; j++) payload[j] = data[j];

  // Serial.println(topic);
  

  String dest = getValue(topic, '/', 1);
  int chan = -1;
  if (dest == "c1") chan = 1;
  if (dest == "c2") chan = 2;
  if (dest == "c3") chan = 3;
  if (dest == "c4") chan = 4;
  if (dest == "c5") chan = 5;
  if (dest == "c6") chan = 6;
  if (dest == "c7") chan = 7;
  if (dest == "c8") chan = 8;
  if (dest == "c9") chan = 9;
  if (dest == "c10") chan = 10;
  if (dest == "c11") chan = 11;
  if (dest == "c12") chan = 12;
  if (dest == "c13") chan = 13;
  if (dest == "c14") chan = 14;
  if (dest == "c15") chan = 15;
  if (dest == "c16") chan = 0;
  if (dest == "all") chan = 0;

  if (chan < 0) return;

  // Serial.printf("channel %d\n", chan);

  String pay = String(payload);
  for(int k=0; k<20; k++) 
  {

    int val = getValue(pay, '|', k).toInt();
    // val = val*val/255;

    if (chan > 0) ESP8266DMX.setSlot( k + (chan-1) * 20 + 1 , val);
    else {
      // ALL
      for(int i=0; i<15; i++)
        ESP8266DMX.setSlot( k + i * 20 + 1 , val);
    }

    // Serial.print(k + (chan-1) * 20 + 1);
    // Serial.print('=');
    // Serial.print(val);
    // Serial.print(' ');
  }
  // Serial.println(' ');

}
