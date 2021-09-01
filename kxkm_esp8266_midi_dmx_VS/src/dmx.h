void copyDMXToOutput(char* topic, uint8_t* data, unsigned int length) {



  for (int i = 1; i < DMX_MAX_FRAME; i++) {
    if (i <= length) {
      ESP8266DMX.setSlot(i , (uint8_t((data[i-1]*data[i-1]) / 255)));
#ifdef DEBUGDMX
      Serial.print(i);
      Serial.print(" = ");
      Serial.println(data[i]);
#endif
    }
  }
}
