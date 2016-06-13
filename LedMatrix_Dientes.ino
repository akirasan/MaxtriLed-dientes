//    Gamificación para lavarse los dientes
//    by akirasan.net
//    Febrero 2016

#include "LedControl.h"

LedControl lc = LedControl(2, 4, 3, 4); /* DIN, CLK, CS, NUM_DISPLA */

unsigned long delaytime = 0;
long int tiempo_15seg;
boolean inicio = true;
boolean final = false;
byte numero_avisos;

byte n0[8] = {B00111100,
              B01100110,
              B01100110,
              B01100110,
              B01100110,
              B01100110,
              B01100110,
              B00111100
             };

byte n1[8] = {B00011000,
              B00111000,
              B00011000,
              B00011000,
              B00011000,
              B00011000,
              B00011000,
              B00111100
             };

byte n2[8] = {B00111100,
              B01100110,
              B00000110,
              B00000110,
              B00001100,
              B00011000,
              B00110000,
              B01111110
             };

byte n3[8] = {B00111100,
              B01100110,
              B00000110,
              B00111110,
              B00111110,
              B00000110,
              B01100110,
              B00111100
             };

byte n4[8] = {B00000000,
              B00000000,
              B00000000,
              B00000000,
              B00000000,
              B00000000,
              B00000000,
              B00000000
             };

byte O[8] = { B01111110,
              B11000011,
              B11000011,
              B11000011,
              B11000011,
              B11000011,
              B11000011,
              B01111110
            };

byte K[8] = { B11000011,
              B11001100,
              B11011000,
              B11100000,
              B11110000,
              B11011000,
              B11001100,
              B11000110
            };

byte  a[8] = {B00000000,
              B01111110,
              B01100110,
              B01111110,
              B01111110,
              B01100110,
              B01100110,
              B01100110
             };

byte y[8] = {B00000000,
             B01100110,
             B01100110,
             B01100110,
             B01111110,
             B00011000,
             B00011000,
             B00011000
            };

byte _adm[8] = {B00111100,
                B00111100,
                B00011000,
                B00011000,
                B00011000,
                B00000000,
                B00111100,
                B00111100
               };

// Fotogramas animación cepillo dientes 
// FOTOGRAMA1
byte t1_3[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00011111,
  B00011111,
  B00000000
};

byte t1_2[8] = {
  B00000000,
  B00000000,
  B00000101,
  B00001101,
  B00001111,
  B11111111,
  B11111111,
  B00000000
};

byte t1_1[8] = {
  B00000000,
  B00000000,
  B01010000,
  B01011000,
  B11111000,
  B11111000,
  B11110000,
  B00000000
};

byte t1_0[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B11111111
};

// FOTOGRAMA2
byte t2_3[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00111111,
  B00111111,
  B00000000
};

byte t2_2[8] = {
  B00000000,
  B00000000,
  B00001010,
  B00011010,
  B00011111,
  B11111111,
  B11111111,
  B00000000
};

byte t2_1[8] = {
  B00000000,
  B00000000,
  B10100000,
  B10110000,
  B11110000,
  B11110000,
  B11100000,
  B00000000
};

// FOTOGRAMA3
byte t3_3[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01111111,
  B01111111,
  B00000000
};

byte t3_2[8] = {
  B00000000,
  B00000000,
  B00010101,
  B00110101,
  B00111111,
  B11111111,
  B11111111,
  B00000000
};

byte t3_1[8] = {
  B00000000,
  B00000000,
  B01000000,
  B01100000,
  B11100000,
  B11100000,
  B11000000,
  B00000000
};

byte caries[8] = {
  B10000001,
  B10111101,
  B01011010,
  B01111110,
  B01000010,
  B00111100,
  B11011011,
  B10000001
};

void all_led_on(byte matrix_id) {
  byte ON[8] = {B11111111,
                B11111111,
                B11111111,
                B11111111,
                B11111111,
                B11111111,
                B11111111,
                B11111111
               };
  lc.setRow(matrix_id, 0, ON[0]);
  lc.setRow(matrix_id, 1, ON[1]);
  lc.setRow(matrix_id, 2, ON[2]);
  lc.setRow(matrix_id, 3, ON[3]);
  lc.setRow(matrix_id, 4, ON[4]);
  lc.setRow(matrix_id, 5, ON[5]);
  lc.setRow(matrix_id, 6, ON[6]);
  lc.setRow(matrix_id, 7, ON[7]);
}

void setup() {
  for (int i = 0; i < 4; i++) {
    lc.shutdown(i, false);
    lc.clearDisplay(i);
  }
  delay(2000);
}

void draw_matriz(int matrix_id, byte datos[8]) {
  lc.setRow(matrix_id, 0, datos[0]);
  lc.setRow(matrix_id, 1, datos[1]);
  lc.setRow(matrix_id, 2, datos[2]);
  lc.setRow(matrix_id, 3, datos[3]);
  lc.setRow(matrix_id, 4, datos[4]);
  lc.setRow(matrix_id, 5, datos[5]);
  lc.setRow(matrix_id, 6, datos[6]);
  lc.setRow(matrix_id, 7, datos[7]);
}

void numero(int matrix_id, char numero) {
  if (numero == '1') {
    draw_matriz(matrix_id, n1);
  }
  else if (numero == '2') {
    draw_matriz(matrix_id, n2);

  } else if (numero == '3') {
    draw_matriz(matrix_id, n3);

  } else if (numero == '0') {
    draw_matriz(matrix_id, n0);
  }
}

void fade_in(int matrix_id) {
  for (int intensidad = 0; intensidad <= 10; intensidad++) {
    lc.setIntensity(matrix_id, intensidad); delay(50);
  }
}

void fade_out(int matrix_id) {
  for (int intensidad = 10; intensidad >= 0; intensidad--) {
    lc.setIntensity(matrix_id, intensidad); delay(50);
  }
}


void cuenta_atras() {
  lc.setIntensity(3, 0);
  numero (3, '3');
  fade_in(3); fade_out(3);
  delay(100);
  lc.clearDisplay(3);

  lc.setIntensity(2, 0);
  numero (2, '2');
  fade_in(2); fade_out(2);
  delay(100);
  lc.clearDisplay(2);

  numero (1, '1');
  fade_in(1); fade_out(1);
  delay(100);
  lc.clearDisplay(1);

  numero (0, '0');
  fade_in(0); fade_out(0);
  delay(100);
  lc.clearDisplay(0);

  for (int t = 1; t < 8; t++) {
    draw_matriz(3, y);
    draw_matriz(2, a);
    draw_matriz(1, _adm);
    draw_matriz(0, _adm);
    delay(100);
    lc.clearDisplay(3);
    lc.clearDisplay(2);
    lc.clearDisplay(1);
    lc.clearDisplay(0);
  }
}

void aviso_15seg() {
  lc.clearDisplay(0);
  all_led_on(0); delay(125);
  lc.clearDisplay(0); delay(125);
  all_led_on(0); delay(125);
  lc.clearDisplay(0);
  caries[numero_avisos] = 0;
}

void cepilla() {
  draw_matriz(3, t1_3);
  draw_matriz(2, t1_2);
  draw_matriz(1, t1_1);
  draw_matriz(0, caries);
  delay(50);

  draw_matriz(3, t2_3);
  draw_matriz(2, t2_2);
  draw_matriz(1, t2_1);
  delay(50);

  draw_matriz(3, t3_3);
  draw_matriz(2, t3_2);
  draw_matriz(1, t3_1);
  delay(50);

  draw_matriz(3, t2_3);
  draw_matriz(2, t2_2);
  draw_matriz(1, t2_1);
  delay(50);
}


void fin() {
  for (int i = 3; i >= 0; i--) {
    lc.clearDisplay(i);
  }
  draw_matriz(2, O);
  draw_matriz(1, K);

  while (true) {
    fade_in(2); fade_out(2);
    fade_in(1); fade_out(1);
  }
}

void loop() {

  if (inicio) {
    cuenta_atras();
    inicio = false;
    tiempo_15seg = millis();
    numero_avisos = 0;
  }

  if (!final) {
    cepilla();

    if (((millis() - tiempo_15seg) / 1000) >= 15) {
      aviso_15seg();
      numero_avisos++;
      tiempo_15seg = millis();
    }

    if (numero_avisos == 8) {
      fin();
      final = true;
    }
  }
}
