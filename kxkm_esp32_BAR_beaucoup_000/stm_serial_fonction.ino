/* Send commands / receive answers */

void sendSerialCommand(KXKM_STM32_Energy::CommandType cmd, int arg)
{
  flushSerialIn();

  Serial.write(KXKM_STM32_Energy::PREAMBLE);
  Serial.write(cmd);
  Serial.write(' ');
  Serial.println(arg);
}

void sendSerialCommand(KXKM_STM32_Energy::CommandType cmd)
{
  flushSerialIn();

  Serial.write(KXKM_STM32_Energy::PREAMBLE);
  Serial.write(cmd);
  Serial.println("");
}

void setLeds(uint8_t *values)
{
  int arg = 0;
  for (int i = 0; i < 6; i++)
    arg += values[i] * pow(10, i);

  sendSerialCommand(KXKM_STM32_Energy::SET_LEDS, arg);
}

long readSerialAnswer()
{
  if (Serial.find(KXKM_STM32_Energy::PREAMBLE))
  {
    long arg = Serial.parseInt();
    return arg;
  }
  return 0;
}

void flushSerialIn()
{
  while (Serial.available())
    Serial.read();
}

void get_percentage() {
//  sendSerialCommand(KXKM_STM32_Energy::GET_API_VERSION);
//  readSerialAnswer();
//  sendSerialCommand(KXKM_STM32_Energy::GET_BATTERY_PERCENTAGE);
//  percentage = readSerialAnswer();
//  if (percentage > 50) {
//    //3ledverte
//    for (int i = 0 ; i < 3 ; i++) {
//      strands[0]->pixels[i] = pixelFromRGB(0, led_niv, 0);
//    }//for i
//  }
//  else if (percentage > 33) {
//    //3ledorange
//    for (int i = 0 ; i < 3 ; i++) {
//      strands[0]->pixels[i] = pixelFromRGB(led_niv, (led_niv / 3), 0);
//    }//for i
//  }
//  else if (percentage > 16) {
//    //3ledrouge
//    for (int i = 0 ; i < 3 ; i++) {
//      strands[0]->pixels[i] = pixelFromRGB(127, 0, 0);
//    }//for i
//  }
//    else  {
//      //3ledrouge clignote
//      if (etat_r != 1) {
//        for (int i = 0 ; i < 3 ; i++) {
//        strands[0]->pixels[i] = pixelFromRGB(255, 0, 0);
//        }
//        etat_r = 1;
//      }
//      else if (etat_r != 0) {
//        for (int i = 0 ; i < 3 ; i++) {
//       strands[0]->pixels[i] = pixelFromRGB(0, 0, 0);
//        }
//       etat_r = 0;
//      }
//    }
}
