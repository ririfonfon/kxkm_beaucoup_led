//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// onDmxFrame //////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data) {
void onDmxFrame(char* topic, byte* data, unsigned int length) {

  boolean tail = false;

#ifdef DEBUG_dmx
  Serial.print("***********************");

  Serial.print("master = ");
  Serial.println(master);
  Serial.print("r = ");
  Serial.println(rr);
  Serial.print("g = ");
  Serial.println(gg);
  Serial.print("b = ");
  Serial.println(bb);
  Serial.print("w = ");
  Serial.println(ww);
  Serial.print("pix_mod = ");
  Serial.println(pix_mod);
  Serial.print("pix_start = ");
  Serial.println(pix_start);
  Serial.print("pix_center = ");
  Serial.println(pix_center);
  Serial.print("pix_end = ");
  Serial.println(pix_end);
  Serial.print("pix_pos = ");
  Serial.println(pix_pos);
  Serial.print("modulo = ");
  Serial.println(modulo);
  Serial.print("str_ws = ");
  Serial.println(str_ws);
  Serial.print("srr = ");
  Serial.println(srr);
  Serial.print("sgg = ");
  Serial.println(sgg);
  Serial.print("sbb = ");
  Serial.println(sbb);
  Serial.print("sww = ");
  Serial.println(sww);
  Serial.print("color_mode = ");
  Serial.println(color_mode);
  Serial.print("mirror = ");
  Serial.println(mirror);
#endif

  master = data[adr - 1];
  rr = (data[adr] * data[adr]) / 255;
  gg = (data[adr + 1] * data[adr + 1]) / 255;
  bb = (data[adr + 2] * data[adr + 2]) / 255;
  ww = (data[adr + 3] * data[adr + 3]) / 255;
  //  mod = data[adr + 4];
  pix_mod = data[adr + 4];
  pix_start = data[adr + 5] - 1;
  pix_pos_v = data[adr + 6];

  pix_end = pix_start + pix_start;
  if (pix_mod >= 11 && pix_mod <= 20 || pix_mod >= 31 && pix_mod <= 60 || pix_mod >= 91 && pix_mod <= 120) {
    pix_pos = (((pix_start + N_L_P_S + pix_end) * data[adr + 6]) / 255) - (pix_end + 1);
  } else if (pix_mod >= 21 && pix_mod <= 30 || pix_mod >= 61 && pix_mod <= 90 || pix_mod >= 121 && pix_mod <= 150) {
    pix_pos = (((pix_start + numberOfLed + pix_end) * data[adr + 6]) / 255) - (pix_end + 1);
  }
  modulo = data[adr + 7];
  str_ws = (data[adr + 8] * data[adr + 8]) / 33;
  pix_center = ((pix_start) / 2) + pix_pos;

  srr = (data[adr + 9] * data[adr + 9]) / 255;
  sgg = (data[adr + 10] * data[adr + 10]) / 255;
  sbb = (data[adr + 11] * data[adr + 11]) / 255;
  sww = (data[adr + 12] * data[adr + 12]) / 255;
  color_mode = data[adr + 13];
  mirror = data[adr + 14];




  // modulo mode && mirror
  if (mirror >= 0 && mirror <= 10) {// no mirror
    N_L_P_S = (NUM_LEDS_PER_STRIP);
    if ((modulo >= 0) && modulo <= 10) {
      type_modulo = 0;
    } else if ((modulo >= 11) && modulo <= 20) {
      type_modulo = 1;
    } else if ((modulo >= 21) && modulo <= 30) {
      type_modulo = 2;
    } else if ((modulo >= 31) && modulo <= 110) {
      Black();
      type_modulo = 3;
      S_seuil = (modulo - 30) * 4;
      //    type_effet = 255;
    } else if ((modulo >= 111) && modulo <= 120) {
      type_modulo = 4;
    } else if ((modulo >= 121) && modulo <= 200) {
      Black();
      type_modulo = 5;
      S_seuil = (modulo - 120) * 4;
      //    type_effet = 255;
    } else if ((modulo >= 201) && modulo <= 255) {
      type_modulo = 6;
      S_seuil = (modulo - 200) * 4;
      //    type_effet = 255;
    }
  } else if (mirror >= 11 && mirror <= 20) {// mirror <>
    N_L_P_S = (NUM_LEDS_PER_STRIP / 2);
    if ((modulo >= 0) && modulo <= 10) {
      type_modulo = 10;
    } else if ((modulo >= 11) && modulo <= 20) {
      type_modulo = 11;
    } else if ((modulo >= 21) && modulo <= 30) {
      type_modulo = 12;
    } else if ((modulo >= 31) && modulo <= 110) {
      Black();
      type_modulo = 13;
      S_seuil = (modulo - 30) * 4;
      //    type_effet = 255;
    } else if ((modulo >= 111) && modulo <= 120) {
      type_modulo = 14;
    } else if ((modulo >= 121) && modulo <= 200) {
      Black();
      type_modulo = 15;
      S_seuil = (modulo - 120) * 4;
      //    type_effet = 255;
    } else if ((modulo >= 201) && modulo <= 255) {
      type_modulo = 16;
      S_seuil = (modulo - 200) * 4;
      //    type_effet = 255;
    }
  } else if (mirror >= 21 && mirror <= 30) {// mirror <><
    N_L_P_S = (NUM_LEDS_PER_STRIP / 3);
    if ((modulo >= 0) && modulo <= 10) {
      type_modulo = 20;
    } else if ((modulo >= 11) && modulo <= 20) {
      type_modulo = 21;
    } else if ((modulo >= 21) && modulo <= 30) {
      type_modulo = 22;
    } else if ((modulo >= 31) && modulo <= 110) {
      Black();
      type_modulo = 23;
      S_seuil = (modulo - 30) * 4;
      //    type_effet = 255;
    } else if ((modulo >= 111) && modulo <= 120) {
      type_modulo = 24;
    } else if ((modulo >= 121) && modulo <= 200) {
      Black();
      type_modulo = 25;
      S_seuil = (modulo - 120) * 4;
      //    type_effet = 255;
    } else if ((modulo >= 201) && modulo <= 255) {
      type_modulo = 26;
      S_seuil = (modulo - 200) * 4;
      //    type_effet = 255;
    }
  } else if (mirror >= 31 && mirror <= 40) {// mirror <><>
    N_L_P_S = (NUM_LEDS_PER_STRIP / 4);
    if ((modulo >= 0) && modulo <= 10) {
      type_modulo = 30;
    } else if ((modulo >= 11) && modulo <= 20) {
      type_modulo = 31;
    } else if ((modulo >= 21) && modulo <= 30) {
      type_modulo = 32;
    } else if ((modulo >= 31) && modulo <= 110) {
      Black();
      type_modulo = 33;
      S_seuil = (modulo - 30) * 4;
      //    type_effet = 255;
    } else if ((modulo >= 111) && modulo <= 120) {
      type_modulo = 34;
    } else if ((modulo >= 121) && modulo <= 200) {
      Black();
      type_modulo = 35;
      S_seuil = (modulo - 120) * 4;
      //    type_effet = 255;
    } else if ((modulo >= 201) && modulo <= 255) {
      type_modulo = 36;
      S_seuil = (modulo - 200) * 4;
      //    type_effet = 255;
    }
  } else if (mirror >= 41 && mirror <= 50) {// mirror <<
    N_L_P_S = (NUM_LEDS_PER_STRIP / 2);
    if ((modulo >= 0) && modulo <= 10) {
      type_modulo = 40;
    } else if ((modulo >= 11) && modulo <= 20) {
      type_modulo = 41;
    } else if ((modulo >= 21) && modulo <= 30) {
      type_modulo = 42;
    } else if ((modulo >= 31) && modulo <= 110) {
      Black();
      type_modulo = 43;
      S_seuil = (modulo - 30) * 4;
      //    type_effet = 255;
    } else if ((modulo >= 111) && modulo <= 120) {
      type_modulo = 44;
    } else if ((modulo >= 121) && modulo <= 200) {
      Black();
      type_modulo = 45;
      S_seuil = (modulo - 120) * 4;
      //    type_effet = 255;
    } else if ((modulo >= 201) && modulo <= 255) {
      type_modulo = 46;
      S_seuil = (modulo - 200) * 4;
      //    type_effet = 255;
    }
  } else if (mirror >= 51 && mirror <= 60) {// mirror <<<
    N_L_P_S = (NUM_LEDS_PER_STRIP / 3);
    if ((modulo >= 0) && modulo <= 10) {
      type_modulo = 50;
    } else if ((modulo >= 11) && modulo <= 20) {
      type_modulo = 51;
    } else if ((modulo >= 21) && modulo <= 30) {
      type_modulo = 52;
    } else if ((modulo >= 31) && modulo <= 110) {
      Black();
      type_modulo = 53;
      S_seuil = (modulo - 30) * 4;
      //    type_effet = 255;
    } else if ((modulo >= 111) && modulo <= 120) {
      type_modulo = 54;
    } else if ((modulo >= 121) && modulo <= 200) {
      Black();
      type_modulo = 55;
      S_seuil = (modulo - 120) * 4;
      //    type_effet = 255;
    } else if ((modulo >= 201) && modulo <= 255) {
      type_modulo = 56;
      S_seuil = (modulo - 200) * 4;
      //    type_effet = 255;
    }
  } else if (mirror >= 61 && mirror <= 70) {// mirror <<<<
    N_L_P_S = (NUM_LEDS_PER_STRIP / 4);
    if ((modulo >= 0) && modulo <= 10) {
      type_modulo = 60;
    } else if ((modulo >= 11) && modulo <= 20) {
      type_modulo = 61;
    } else if ((modulo >= 21) && modulo <= 30) {
      type_modulo = 62;
    } else if ((modulo >= 31) && modulo <= 110) {
      Black();
      type_modulo = 63;
      S_seuil = (modulo - 30) * 4;
      //    type_effet = 255;
    } else if ((modulo >= 111) && modulo <= 120) {
      type_modulo = 64;
    } else if ((modulo >= 121) && modulo <= 200) {
      Black();
      type_modulo = 65;
      S_seuil = (modulo - 120) * 4;
      //    type_effet = 255;
    } else if ((modulo >= 201) && modulo <= 255) {
      type_modulo = 66;
      S_seuil = (modulo - 200) * 4;
      //    type_effet = 255;
    }
  }

  //  previousDataLength = length;
  //
  //  if (sendFrame) {
  //    // Reset universeReceived to 0
  //    memset(universesReceived, 0, maxUniverses);
  //  }//sendFrame
}//onframedmx
