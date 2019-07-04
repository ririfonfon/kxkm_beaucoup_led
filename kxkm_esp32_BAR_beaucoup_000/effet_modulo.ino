
void eff_modulo() {
  float fade_coef = 10;
  unsigned long t_now = millis();
  if ( type_modulo == 0 ) {
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {

      strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[i] / 255) * master), ((pi_n_1_g[i] / 255) * master), ((pi_n_1_b[i] / 255) * master), ((pi_n_1_w[i] / 255) * master));
      strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[i] / 255) * master), ((pi_n_1_g[i] / 255) * master), ((pi_n_1_b[i] / 255) * master), ((pi_n_1_w[i] / 255) * master));

    }

  }
  else if ( type_modulo == 1) {
    if (str == 0 && t_now - str_ws_last > str_ws) {
      str_ws_last = t_now;
      str = 1;
    } else if (str == 1 && t_now - str_ws_last > STROB_ON_MS) {
      str_ws_last = t_now;
      str = 0;
    } else {
      return;
    }
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {

      strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));
      strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));

    }

  }//modulo 1

  else if (type_modulo == 2) {
    if (str_ws <= 0) str_ws = 1;
    float time_modulo = str_ws * fade_coef;
    int t_modulo = str_ws * fade_coef;
    //    float module = 2 * abs( (t_now % str_ws) - time_modulo / 2) / time_modulo;
    float module = 2 * abs( (t_now % t_modulo) - time_modulo / 2) / time_modulo;
    module *= module;
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {

      strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * module * master / 255), (pi_n_1_g[i] * module * master / 255), (pi_n_1_b[i] * module * master / 255), (pi_n_1_w[i] * module * master / 255));
      strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * module * master / 255), (pi_n_1_g[i] * module * master / 255), (pi_n_1_b[i] * module * master / 255), (pi_n_1_w[i] * module * master / 255));

    }

  }// modulo 2

  else if ( type_modulo == 3 ) {
    if (str == 0 && t_now - str_ws_last > str_ws) {
      str_ws_last = t_now;
      str = 1;
    } else if (str == 1 && t_now - str_ws_last > STROB_ON_MS) {
      str_ws_last = t_now;
      str = 0;
      Black();
    } else {
      return;
    }

    int n_led_to_show = (min(numberOfLed - 8, S_seuil));
    int n_strip = 0;
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , numberOfLed );
        n_strip = a / NUM_LEDS_PER_STRIP;
      } while (strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].r != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].g != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].b != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].w != 0);


      strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
      strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));

    }//for i
  }//modulo 3

  else if ( type_modulo == 4) {
    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws)) {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3) {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    } else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS)) {
      str_ws_last = t_now;
      str = 0;
    } else {
      return;
    }
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {

      strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));
      strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));

    }

  }//modulo 4
  else if ( type_modulo == 5 ) {
    int S_seuil_B;
    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws)) {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3) {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    } else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS)) {
      str_ws_last = t_now;
      str = 0;
      Black();
    } else {
      return;
    }

    int n_led_to_show = min(numberOfLed - 8, S_seuil);
    int n_strip = 0;
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , numberOfLed );
        n_strip = a / NUM_LEDS_PER_STRIP;
      } while (strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].r != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].g != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].b != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].w != 0 );

      strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
      strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));

    }//for i
  }//modulo 5

  else if ( type_modulo == 6 ) {
    if (old_S_seuil != S_seuil) {
      Black();
      old_S_seuil = S_seuil;
    }
    int S_seuil_B;
    int n_led_to_show = min(numberOfLed - 8, S_seuil);
    int n_strip = 0;
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , numberOfLed );
        n_strip = a / NUM_LEDS_PER_STRIP;
      } while (strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].r != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].g != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].b != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].w != 0 );

      strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255));
      strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255));

    }//for i
    old_S_seuil = S_seuil - 1;
  }//modulo 6



  else if ( type_modulo == 10 ) {
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[i] / 255) * master), ((pi_n_1_g[i] / 255) * master), ((pi_n_1_b[i] / 255) * master), ((pi_n_1_w[i] / 255) * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[i] / 255) * master), ((pi_n_1_g[i] / 255) * master), ((pi_n_1_b[i] / 255) * master), ((pi_n_1_w[i] / 255) * master));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, NUM_LEDS_PER_STRIP, N_L_P_S, 0);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));

      }
    }
  }//modulo 10
  else if ( type_modulo == 11) {
    if (str == 0 && t_now - str_ws_last > str_ws) {
      str_ws_last = t_now;
      str = 1;
    } else if (str == 1 && t_now - str_ws_last > STROB_ON_MS) {
      str_ws_last = t_now;
      str = 0;
    } else {
      return;
    }
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, NUM_LEDS_PER_STRIP, N_L_P_S, 0);

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));

      }
    }
  }//modulo 11

  else if (type_modulo == 12) {
    if (str_ws <= 0) str_ws = 1;
    float time_modulo = str_ws * fade_coef;
    int t_modulo = str_ws * fade_coef;
    float module = 2 * abs( (t_now % t_modulo) - time_modulo / 2) / time_modulo;
    module *= module;
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * module * master / 255), (pi_n_1_g[i] * module * master / 255), (pi_n_1_b[i] * module * master / 255), (pi_n_1_w[i] * module * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * module * master / 255), (pi_n_1_g[i] * module * master / 255), (pi_n_1_b[i] * module * master / 255), (pi_n_1_w[i] * module * master / 255));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, NUM_LEDS_PER_STRIP, N_L_P_S, 0);

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * module * master / 255), (pi_n_1_g[di] * module * master / 255), (pi_n_1_b[di] * module * master / 255), (pi_n_1_w[di] * module * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * module * master / 255), (pi_n_1_g[di] * module * master / 255), (pi_n_1_b[di] * module * master / 255), (pi_n_1_w[di] * module * master / 255));

      }
    }
  }// modulo 12

  else if ( type_modulo == 13 ) {
    if (str == 0 && t_now - str_ws_last > str_ws) {
      str_ws_last = t_now;
      str = 1;
    } else if (str == 1 && t_now - str_ws_last > STROB_ON_MS) {
      str_ws_last = t_now;
      str = 0;
      Black();
    } else {
      return;
    }

    int n_led_to_show = (min(numberOfLed - 8, S_seuil));
    int n_strip = 0;
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , numberOfLed );
        n_strip = a / NUM_LEDS_PER_STRIP;
      } while (strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].r != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].g != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].b != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].w != 0);

      if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S) {
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), N_L_P_S + 1, NUM_LEDS_PER_STRIP, N_L_P_S, 0);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      }

    }//for i
  }//modulo 13

  else if ( type_modulo == 14) {
    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws)) {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3) {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    } else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS)) {
      str_ws_last = t_now;
      str = 0;
    } else {
      return;
    }
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, NUM_LEDS_PER_STRIP, N_L_P_S, 0);

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));

      }
    }

  }//modulo 14

  else if ( type_modulo == 15 ) {
    int S_seuil_B;
    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws)) {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3) {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    } else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS)) {
      str_ws_last = t_now;
      str = 0;
      Black();
    } else {
      return;
    }

    int n_led_to_show = min(numberOfLed - 8, S_seuil);
    int n_strip = 0;
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , numberOfLed );
        n_strip = a / NUM_LEDS_PER_STRIP;
      } while (strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].r != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].g != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].b != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].w != 0 );



      if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S) {
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), N_L_P_S + 1, NUM_LEDS_PER_STRIP, N_L_P_S, 0);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      }

    }//for i
  }//modulo 15

  else if ( type_modulo == 16 ) {
    if (old_S_seuil != S_seuil) {
      Black();
      old_S_seuil = S_seuil;
    }
    int S_seuil_B;
    int n_led_to_show = min(numberOfLed - 8, S_seuil);
    int n_strip = 0;
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , numberOfLed );
        n_strip = a / NUM_LEDS_PER_STRIP;
      } while (strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].r != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].g != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].b != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].w != 0 );


      if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S) {
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), N_L_P_S + 1, NUM_LEDS_PER_STRIP, N_L_P_S, 0);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
      }

    }//for i
    old_S_seuil = S_seuil - 1;
  }//modulo 16

  else if ( type_modulo == 20 ) {
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[i] / 255) * master), ((pi_n_1_g[i] / 255) * master), ((pi_n_1_b[i] / 255) * master), ((pi_n_1_w[i] / 255) * master));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));

      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));

      }
    }
  }//modulo 20

  else if ( type_modulo == 21) {
    if (str == 0 && t_now - str_ws_last > str_ws) {
      str_ws_last = t_now;
      str = 1;
    } else if (str == 1 && t_now - str_ws_last > STROB_ON_MS) {
      str_ws_last = t_now;
      str = 0;
    } else {
      return;
    }
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));

      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));

      }
    }
  }//modulo 21

  else if (type_modulo == 22) {
    if (str_ws <= 0) str_ws = 1;
    float time_modulo = str_ws * fade_coef;
    int t_modulo = str_ws * fade_coef;
    float module = 2 * abs( (t_now % t_modulo) - time_modulo / 2) / time_modulo;
    module *= module;
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * module * master / 255), (pi_n_1_g[i] * module * master / 255), (pi_n_1_b[i] * module * master / 255), (pi_n_1_w[i] * module * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * module * master / 255), (pi_n_1_g[i] * module * master / 255), (pi_n_1_b[i] * module * master / 255), (pi_n_1_w[i] * module * master / 255));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));

      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));

      }
    }
  }// modulo 22

  else if ( type_modulo == 23 ) {
    if (str == 0 && t_now - str_ws_last > str_ws) {
      str_ws_last = t_now;
      str = 1;
    } else if (str == 1 && t_now - str_ws_last > STROB_ON_MS) {
      str_ws_last = t_now;
      str = 0;
      Black();
    } else {
      return;
    }

    int n_led_to_show = (min(numberOfLed - 8, S_seuil));
    int n_strip = 0;
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , numberOfLed );
        n_strip = a / NUM_LEDS_PER_STRIP;
      } while (strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].r != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].g != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].b != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].w != 0);


      if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S) {
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 3 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S * 2)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      }

    }//for i
  }//modulo 23

  else if ( type_modulo == 24) {
    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws)) {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3) {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    } else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS)) {
      str_ws_last = t_now;
      str = 0;
    } else {
      return;
    }
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));

      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));

      }
    }

  }//modulo 24
  else if ( type_modulo == 25 ) {
    int S_seuil_B;
    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws)) {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3) {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    } else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS)) {
      str_ws_last = t_now;
      str = 0;
      Black();
    } else {
      return;
    }

    int n_led_to_show = min(numberOfLed - 8, S_seuil);
    int n_strip = 0;
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , numberOfLed );
        n_strip = a / NUM_LEDS_PER_STRIP;
      } while (strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].r != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].g != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].b != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].w != 0 );


      if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S) {
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 3 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S * 2)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      }

    }//for i
  }//modulo 25

  else if ( type_modulo == 26 ) {
    if (old_S_seuil != S_seuil) {
      Black();
      old_S_seuil = S_seuil;
    }
    int S_seuil_B;
    int n_led_to_show = min(numberOfLed - 8, S_seuil);
    int n_strip = 0;
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , numberOfLed );
        n_strip = a / NUM_LEDS_PER_STRIP;
      } while (strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].r != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].g != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].b != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].w != 0 );


      if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S) {
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 3 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S * 2)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
      }

    }//for i
    old_S_seuil = S_seuil - 1;
  }//modulo 26



  else if ( type_modulo == 30 ) {
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[i] / 255) * master), ((pi_n_1_g[i] / 255) * master), ((pi_n_1_b[i] / 255) * master), ((pi_n_1_w[i] / 255) * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[i] / 255) * master), ((pi_n_1_g[i] / 255) * master), ((pi_n_1_b[i] / 255) * master), ((pi_n_1_w[i] / 255) * master));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));

      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));

      } else if (i <= N_L_P_S * 4 & i >= N_L_P_S * 3) {
        int di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, N_L_P_S, 0);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));

      }
    }
  }//modulo 30

  else if ( type_modulo == 31) {
    if (str == 0 && t_now - str_ws_last > str_ws) {
      str_ws_last = t_now;
      str = 1;
    } else if (str == 1 && t_now - str_ws_last > STROB_ON_MS) {
      str_ws_last = t_now;
      str = 0;
    } else {
      return;
    }
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));

      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));

      } else if (i <= N_L_P_S * 4 & i >= N_L_P_S * 3) {
        int di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, N_L_P_S, 0);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));

      }
    }
  }//modulo 31

  else if (type_modulo == 32) {
    if (str_ws <= 0) str_ws = 1;
    float time_modulo = str_ws * fade_coef;
    int t_modulo = str_ws * fade_coef;
    float module = 2 * abs( (t_now % t_modulo) - time_modulo / 2) / time_modulo;
    module *= module;
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * module * master / 255), (pi_n_1_g[i] * module * master / 255), (pi_n_1_b[i] * module * master / 255), (pi_n_1_w[i] * module * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * module * master / 255), (pi_n_1_g[i] * module * master / 255), (pi_n_1_b[i] * module * master / 255), (pi_n_1_w[i] * module * master / 255));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));

      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));

      } else if (i <= N_L_P_S * 4 & i >= N_L_P_S * 3) {
        int di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, N_L_P_S, 0);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));

      }
    }
  }// modulo 32

  else if ( type_modulo == 33 ) {
    if (str == 0 && t_now - str_ws_last > str_ws) {
      str_ws_last = t_now;
      str = 1;
    } else if (str == 1 && t_now - str_ws_last > STROB_ON_MS) {
      str_ws_last = t_now;
      str = 0;
      Black();
    } else {
      return;
    }

    int n_led_to_show = (min(numberOfLed - 8, S_seuil));
    int n_strip = 0;
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , numberOfLed );
        n_strip = a / NUM_LEDS_PER_STRIP;
      } while (strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].r != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].g != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].b != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].w != 0);


      if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S) {
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 3 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S * 2)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 4 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S * 3)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), (N_L_P_S * 3) + 1, N_L_P_S * 4, N_L_P_S, 0);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      }

    }//for i
  }//modulo 33

  else if ( type_modulo == 34) {
    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws)) {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3) {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    } else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS)) {
      str_ws_last = t_now;
      str = 0;
    } else {
      return;
    }
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));

      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));

      } else if (i <= N_L_P_S * 4 & i >= N_L_P_S * 3) {
        int di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, N_L_P_S, 0);

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));

      }
    }

  }//modulo 34
  else if ( type_modulo == 35 ) {
    int S_seuil_B;
    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws)) {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3) {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    } else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS)) {
      str_ws_last = t_now;
      str = 0;
      Black();
    } else {
      return;
    }

    int n_led_to_show = min(numberOfLed - 8, S_seuil);
    int n_strip = 0;
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , numberOfLed );
        n_strip = a / NUM_LEDS_PER_STRIP;
      } while (strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].r != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].g != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].b != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].w != 0 );


      if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S) {
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 3 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S * 2)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 4 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S * 3)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), (N_L_P_S * 3) + 1, N_L_P_S * 4, N_L_P_S, 0);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      }

    }//for i
  }//modulo 35

  else if ( type_modulo == 36 ) {
    if (old_S_seuil != S_seuil) {
      Black();
      old_S_seuil = S_seuil;
    }
    int S_seuil_B;
    int n_led_to_show = min(numberOfLed - 8, S_seuil);
    int n_strip = 0;
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , numberOfLed );
        n_strip = a / NUM_LEDS_PER_STRIP;
      } while (strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].r != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].g != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].b != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].w != 0 );


      if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S) {
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 3 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S * 2)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 4 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S * 3)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), (N_L_P_S * 3) + 1, N_L_P_S * 4, N_L_P_S, 0);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
      }

    }//for i
    old_S_seuil = S_seuil - 1;
  }//modulo 36

  else if ( type_modulo == 40 ) {
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[i] / 255) * master), ((pi_n_1_g[i] / 255) * master), ((pi_n_1_b[i] / 255) * master), ((pi_n_1_w[i] / 255) * master));
        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[i] / 255) * master), ((pi_n_1_g[i] / 255) * master), ((pi_n_1_b[i] / 255) * master), ((pi_n_1_w[i] / 255) * master));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, NUM_LEDS_PER_STRIP, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));

      }
    }
  }//modulo 40
  else if ( type_modulo == 41) {
    if (str == 0 && t_now - str_ws_last > str_ws) {
      str_ws_last = t_now;
      str = 1;
    } else if (str == 1 && t_now - str_ws_last > STROB_ON_MS) {
      str_ws_last = t_now;
      str = 0;
    } else {
      return;
    }
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, NUM_LEDS_PER_STRIP, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));

      }
    }
  }//modulo 41

  else if (type_modulo == 42) {
    if (str_ws <= 0) str_ws = 1;
    float time_modulo = str_ws * fade_coef;
    int t_modulo = str_ws * fade_coef;
    float module = 2 * abs( (t_now % t_modulo) - time_modulo / 2) / time_modulo;
    module *= module;
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * module * master / 255), (pi_n_1_g[i] * module * master / 255), (pi_n_1_b[i] * module * master / 255), (pi_n_1_w[i] * module * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * module * master / 255), (pi_n_1_g[i] * module * master / 255), (pi_n_1_b[i] * module * master / 255), (pi_n_1_w[i] * module * master / 255));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, NUM_LEDS_PER_STRIP, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * module * master / 255), (pi_n_1_g[di] * module * master / 255), (pi_n_1_b[di] * module * master / 255), (pi_n_1_w[di] * module * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * module * master / 255), (pi_n_1_g[di] * module * master / 255), (pi_n_1_b[di] * module * master / 255), (pi_n_1_w[di] * module * master / 255));

      }
    }
  }// modulo 42

  else if ( type_modulo == 43 ) {
    if (str == 0 && t_now - str_ws_last > str_ws) {
      str_ws_last = t_now;
      str = 1;
    } else if (str == 1 && t_now - str_ws_last > STROB_ON_MS) {
      str_ws_last = t_now;
      str = 0;
      Black();
    } else {
      return;
    }

    int n_led_to_show = (min(numberOfLed - 8, S_seuil));
    int n_strip = 0;
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , numberOfLed );
        n_strip = a / NUM_LEDS_PER_STRIP;
      } while (strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].r != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].g != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].b != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].w != 0);

      if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S) {
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), N_L_P_S + 1, NUM_LEDS_PER_STRIP, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      }

    }//for i
  }//modulo 43

  else if ( type_modulo == 44) {
    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws)) {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3) {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    } else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS)) {
      str_ws_last = t_now;
      str = 0;
    } else {
      return;
    }
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, NUM_LEDS_PER_STRIP, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));

      }
    }

  }//modulo 44

  else if ( type_modulo == 45 ) {
    int S_seuil_B;
    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws)) {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3) {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    } else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS)) {
      str_ws_last = t_now;
      str = 0;
      Black();
    } else {
      return;
    }

    int n_led_to_show = min(numberOfLed - 8, S_seuil);
    int n_strip = 0;
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , numberOfLed );
        n_strip = a / NUM_LEDS_PER_STRIP;
      } while (strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].r != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].g != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].b != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].w != 0 );



      if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S) {
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), N_L_P_S + 1, NUM_LEDS_PER_STRIP, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      }

    }//for i
  }//modulo 45

  else if ( type_modulo == 46 ) {
    if (old_S_seuil != S_seuil) {
      Black();
      old_S_seuil = S_seuil;
    }
    int S_seuil_B;
    int n_led_to_show = min(numberOfLed - 8, S_seuil);
    int n_strip = 0;
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , numberOfLed );
        n_strip = a / NUM_LEDS_PER_STRIP;
      } while (strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].r != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].g != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].b != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].w != 0 );


      if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S) {
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), N_L_P_S + 1, NUM_LEDS_PER_STRIP, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
      }

    }//for i
    old_S_seuil = S_seuil - 1;
  }//modulo 46

  else  if ( type_modulo == 50 ) {
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[i] / 255) * master), ((pi_n_1_g[i] / 255) * master), ((pi_n_1_b[i] / 255) * master), ((pi_n_1_w[i] / 255) * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[i] / 255) * master), ((pi_n_1_g[i] / 255) * master), ((pi_n_1_b[i] / 255) * master), ((pi_n_1_w[i] / 255) * master));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));

      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));

      }
    }
  }//modulo 50

  else if ( type_modulo == 51) {
    if (str == 0 && t_now - str_ws_last > str_ws) {
      str_ws_last = t_now;
      str = 1;
    } else if (str == 1 && t_now - str_ws_last > STROB_ON_MS) {
      str_ws_last = t_now;
      str = 0;
    } else {
      return;
    }
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));

      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));

      }
    }
  }//modulo 51

  else if (type_modulo == 52) {
    if (str_ws <= 0) str_ws = 1;
    float time_modulo = str_ws * fade_coef;
    int t_modulo = str_ws * fade_coef;
    float module = 2 * abs( (t_now % t_modulo) - time_modulo / 2) / time_modulo;
    module *= module;
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * module * master / 255), (pi_n_1_g[i] * module * master / 255), (pi_n_1_b[i] * module * master / 255), (pi_n_1_w[i] * module * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * module * master / 255), (pi_n_1_g[i] * module * master / 255), (pi_n_1_b[i] * module * master / 255), (pi_n_1_w[i] * module * master / 255));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));

      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));

      }
    }
  }// modulo 52

  else if ( type_modulo == 53 ) {
    if (str == 0 && t_now - str_ws_last > str_ws) {
      str_ws_last = t_now;
      str = 1;
    } else if (str == 1 && t_now - str_ws_last > STROB_ON_MS) {
      str_ws_last = t_now;
      str = 0;
      Black();
    } else {
      return;
    }

    int n_led_to_show = (min(numberOfLed - 8, S_seuil));
    int n_strip = 0;
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , numberOfLed );
        n_strip = a / NUM_LEDS_PER_STRIP;
      } while (strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].r != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].g != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].b != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].w != 0);


      if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S) {
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 3 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S * 2)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      }

    }//for i
  }//modulo 53

  else if ( type_modulo == 54) {
    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws)) {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3) {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    } else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS)) {
      str_ws_last = t_now;
      str = 0;
    } else {
      return;
    }
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));

      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));

      }
    }

  }//modulo 54
  else if ( type_modulo == 55 ) {
    int S_seuil_B;
    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws)) {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3) {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    } else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS)) {
      str_ws_last = t_now;
      str = 0;
      Black();
    } else {
      return;
    }

    int n_led_to_show = min(numberOfLed - 8, S_seuil);
    int n_strip = 0;
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , numberOfLed );
        n_strip = a / NUM_LEDS_PER_STRIP;
      } while (strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].r != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].g != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].b != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].w != 0 );


      if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S) {
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 3 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S * 2)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      }

    }//for i
  }//modulo 55

  else if ( type_modulo == 56 ) {
    if (old_S_seuil != S_seuil) {
      Black();
      old_S_seuil = S_seuil;
    }
    int S_seuil_B;
    int n_led_to_show = min(numberOfLed - 8, S_seuil);
    int n_strip = 0;
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , numberOfLed );
        n_strip = a / NUM_LEDS_PER_STRIP;
      } while (strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].r != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].g != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].b != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].w != 0 );


      if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S) {
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 3 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S * 2)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
      }

    }//for i
    old_S_seuil = S_seuil - 1;
  }//modulo 56
  else if ( type_modulo == 60 ) {
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[i] / 255) * master), ((pi_n_1_g[i] / 255) * master), ((pi_n_1_b[i] / 255) * master), ((pi_n_1_w[i] / 255) * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[i] / 255) * master), ((pi_n_1_g[i] / 255) * master), ((pi_n_1_b[i] / 255) * master), ((pi_n_1_w[i] / 255) * master));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));

      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));

      } else if (i <= N_L_P_S * 4 & i >= N_L_P_S * 3) {
        int di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));

      }
    }
  }//modulo 60

  else if ( type_modulo == 61) {
    if (str == 0 && t_now - str_ws_last > str_ws) {
      str_ws_last = t_now;
      str = 1;
    } else if (str == 1 && t_now - str_ws_last > STROB_ON_MS) {
      str_ws_last = t_now;
      str = 0;
    } else {
      return;
    }
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));

      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));

      } else if (i <= N_L_P_S * 4 & i >= N_L_P_S * 3) {
        int di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));

      }
    }
  }//modulo 61

  else if (type_modulo == 62) {
    if (str_ws <= 0) str_ws = 1;
    float time_modulo = str_ws * fade_coef;
    int t_modulo = str_ws * fade_coef;
    float module = 2 * abs( (t_now % t_modulo) - time_modulo / 2) / time_modulo;
    module *= module;
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * module * master / 255), (pi_n_1_g[i] * module * master / 255), (pi_n_1_b[i] * module * master / 255), (pi_n_1_w[i] * module * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * module * master / 255), (pi_n_1_g[i] * module * master / 255), (pi_n_1_b[i] * module * master / 255), (pi_n_1_w[i] * module * master / 255));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));

      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));

      } else if (i <= N_L_P_S * 4 & i >= N_L_P_S * 3) {
        int di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));

      }
    }
  }// modulo 62

  else if ( type_modulo == 63 ) {
    if (str == 0 && t_now - str_ws_last > str_ws) {
      str_ws_last = t_now;
      str = 1;
    } else if (str == 1 && t_now - str_ws_last > STROB_ON_MS) {
      str_ws_last = t_now;
      str = 0;
      Black();
    } else {
      return;
    }

    int n_led_to_show = (min(numberOfLed - 8, S_seuil));
    int n_strip = 0;
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , numberOfLed );
        n_strip = a / NUM_LEDS_PER_STRIP;
      } while (strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].r != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].g != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].b != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].w != 0);


      if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S) {
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 3 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S * 2)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 4 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S * 3)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), (N_L_P_S * 3) + 1, N_L_P_S * 4, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      }

    }//for i
  }//modulo 63

  else if ( type_modulo == 64) {
    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws)) {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3) {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    } else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS)) {
      str_ws_last = t_now;
      str = 0;
    } else {
      return;
    }
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));

      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));

      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));

      } else if (i <= N_L_P_S * 4 & i >= N_L_P_S * 3) {
        int di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, 0, N_L_P_S);

        strands[0]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));

      }
    }

  }//modulo 64
  else if ( type_modulo == 65 ) {
    int S_seuil_B;
    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws)) {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3) {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    } else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS)) {
      str_ws_last = t_now;
      str = 0;
      Black();
    } else {
      return;
    }

    int n_led_to_show = min(numberOfLed - 8, S_seuil);
    int n_strip = 0;
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , numberOfLed );
        n_strip = a / NUM_LEDS_PER_STRIP;
      } while (strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].r != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].g != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].b != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].w != 0 );


      if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S) {
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 3 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S * 2)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 4 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S * 3)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), (N_L_P_S * 3) + 1, N_L_P_S * 4, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      }

    }//for i
  }//modulo 65

  else if ( type_modulo == 66 ) {
    if (old_S_seuil != S_seuil) {
      Black();
      old_S_seuil = S_seuil;
    }
    int S_seuil_B;
    int n_led_to_show = min(numberOfLed - 8, S_seuil);
    int n_strip = 0;
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , numberOfLed );
        n_strip = a / NUM_LEDS_PER_STRIP;
      } while (strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].r != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].g != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].b != 0 || strands[n_strip]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)].w != 0 );


      if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S) {
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * n_strip)] * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 3 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S * 2)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * n_strip) <= N_L_P_S * 4 & a - (NUM_LEDS_PER_STRIP * n_strip >= N_L_P_S * 3)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * n_strip), (N_L_P_S * 3) + 1, N_L_P_S * 4, 0, N_L_P_S);
        strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * n_strip)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
      }

    }//for i
    old_S_seuil = S_seuil - 1;
  }//modulo 66
}//eff_modulo
