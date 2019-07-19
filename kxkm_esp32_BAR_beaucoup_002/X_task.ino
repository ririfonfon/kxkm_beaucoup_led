
void Map1code( void * pvParameters ) {
  //void Map1code() {
  while (1) {
    // color mode
    if (color_mode >= 0 && color_mode <= 10) {
      for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
        pi_1_r[i] = rr;
        pi_1_g[i] = gg;
        pi_1_b[i] = bb;
        pi_1_w[i] = ww;

        pi_1_sr[i] = srr;
        pi_1_sg[i] = sgg;
        pi_1_sb[i] = sbb;
        pi_1_sw[i] = sww;

      }
    } else if (color_mode >= 11 && color_mode <= 20) {
      if (pix_mod >= 11 && pix_mod <= 20 || pix_mod >= 31 && pix_mod <= 60 || pix_mod >= 91 && pix_mod <= 120) {
        pix_pos = (((pix_start + N_L_P_S + pix_end) * pix_pos_v) / 255) - (pix_end + 1);
      } else if (pix_mod >= 21 && pix_mod <= 30 || pix_mod >= 61 && pix_mod <= 90 || pix_mod >= 121 && pix_mod <= 150) {
        pix_pos = (((pix_start + numberOfLed + pix_end) * pix_pos_v) / 255) - (pix_end + 1);
      } else {
        pix_pos = (((pix_start + N_L_P_S + pix_end) * pix_pos_v) / 255) - (pix_end + 1);
      }
      float P_S = srr;
      float P_E = sgg;
      float P_S_E;
      float P_S_N;

      for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
        if (P_S < P_E) {
          P_S_E = P_E - P_S;
        } else if (P_S > P_E) {
          P_S_E = P_S - P_E;
        } else if (P_S == P_E) {
          P_S_E = P_S;
        }
        P_S_N = P_S + ((P_S_E / NUM_LEDS_PER_STRIP ) * i);

        if (P_S_N >= 0 && P_S_N < 42.5) {
          rrr = map(P_S_N, 0, 42.5, 255, 255);
          ggg = map(P_S_N, 0, 42.5, 0, 255);
          bbb = map(P_S_N, 0, 42.5, 0, 0);
          www = 0;
        } else if (P_S_N >= 42.5 && P_S_N < 85) {
          rrr = map(P_S_N, 42.5, 85, 255, 0);
          ggg = map(P_S_N, 42.5, 85, 255, 255);
          bbb = map(P_S_N, 42.5, 85, 0, 0);
          www = 0;
        } else if (P_S_N >= 85 && P_S_N < 127.5) {
          rrr = map(P_S_N, 85, 127.5, 0, 0);
          ggg = map(P_S_N, 85, 127.5, 255, 255);
          bbb = map(P_S_N, 85, 127.5, 0, 255);
          www = 0;
        } else if (P_S_N >= 127.5 && P_S_N < 170) {
          rrr = map(P_S_N, 127.5, 170, 0, 0);
          ggg = map(P_S_N, 127.5, 170, 255, 0);
          bbb = map(P_S_N, 127.5, 170, 255, 255);
          www = 0;
        } else if (P_S_N >= 170 && P_S_N < 212.5) {
          rrr = map(P_S_N, 170, 212.5, 0, 255);
          ggg = map(P_S_N, 170, 212.5, 0, 0);
          bbb = map(P_S_N, 170, 212.5, 255, 255);
          www = 0;
        } else if (P_S_N >= 212.5 && P_S_N <= 255) {
          rrr = map(P_S_N, 212.5, 255, 255, 255);
          ggg = map(P_S_N, 212.5, 255, 0, 0);
          bbb = map(P_S_N, 212.5, 255, 255, 0);
          www = 0;
        }

        int ci = pix_pos + i - 1;
        if (ci > NUM_LEDS_PER_STRIP) {
          ci = ci - NUM_LEDS_PER_STRIP - 1;
        }

        if (ci >= 0 && ci <= N_L_P_S) {
          pi_1_r[ci] = (( rrr * rrr / 255 )  * rr) / 255;
          pi_1_g[ci] = (( ggg * ggg / 255 )  * gg) / 255;
          pi_1_b[ci] = (( bbb * bbb / 255 )  * bb) / 255;
          pi_1_w[ci] = (( www * www / 255 )  * ww) / 255;
          pi_1_sr[ci] = 0;
          pi_1_sg[ci] = 0;
          pi_1_sb[ci] = 0;
          pi_1_sw[ci] = 0;
        }
      }//for (i = 0 ; i < NUM_LEDS_PER_STRIP ; i++)
    }//(color_mode >= 11 && color_mode <= 20)

  }//while
}

void effTask( void * pvParameters ) {
  //  void effTask() {
  while (1) {
    do_effet_0();

    leds_show();
    yield(); // rend la main
  }
}
