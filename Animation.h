//
//  Animation.h
//  Animation
//
//  Created by justin on 2020/12/16.
//
#ifndef Animation_h
#define Animation_h

#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>

#define PIN 2
int init_display;

// millis
int idle1_video_state = 0;
unsigned long ms_from_start = 0;
unsigned long ms_previos_read_LED1 = 0;
unsigned long LED1_interval = 100;
/****************************************************/
/*
#define BRIGHTNESS 96

#define mw 8
#define mh 8

#define LED_BLACK    0

int counter = 0;
int bilderanzahl = 0;

Adafruit_NeoMatrix *matrix = new Adafruit_NeoMatrix(mw, mh, PIN,
    NEO_MATRIX_BOTTOM     + NEO_MATRIX_LEFT +
    NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
    NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix->Color(0, 0, 0), matrix->Color(0, 0, 0), matrix->Color(0, 0, 0) };
*/
#define BRIGHTNESS 96

struct RGB{
  byte r;
  byte g;
  byte b;
};

RGB white = { 255, 255, 255 };
RGB Red = { 255, 0, 0 };
RGB off = { 0, 0, 0 };

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0) };


/****************************************************/
/*
void fixdrawRGBBitmap(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h);

static const uint16_t PROGMEM RGB_bmp[][64] = {
  //Mario 1
  {
    0x937,  0x937,  0x937,  0x937,  0x937,  0x937,  0x937,  0x937,
    0x937,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x937,
    0x937,  0x000,  0x937,  0x000,  0x000,  0x937,  0x000,  0x937,
    0x937,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x937,
    0x937,  0x000,  0x937,  0x937,  0x937,  0x937,  0x000,  0x937,
    0x937,  0x000,  0x937,  0x937,  0x937,  0x937,  0x000,  0x937,
    0x937,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x937,
    0x937,  0x937,  0x937,  0x937,  0x937,  0x937,  0x937,  0x937,
  },
  //Mario 2
  {
    0x937,  0x937,  0x937,  0x937,  0x937,  0x937,  0x937,  0x937,
    0x937,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x937,
    0x937,  0x000,  0x937,  0x000,  0x000,  0x937,  0x000,  0x937,
    0x937,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x937,
    0x937,  0x000,  0x000,  0x937,  0x937,  0x000,  0x000,  0x937,
    0x937,  0x000,  0x000,  0x937,  0x937,  0x000,  0x000,  0x937,
    0x937,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x937,
    0x937,  0x937,  0x937,  0x937,  0x937,  0x937,  0x937,  0x937,
  },
};

static const uint16_t PROGMEM RGB_bmp_1[][64] = {
  // count 1
  {
    0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,
    0x000,  0x33E,  0x33E,  0x000,  0x000,  0x33E,  0x33E,  0x000,
    0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,
    0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,
    0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,
    0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,
    0x000,  0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,  0x000,
    0x000,  0x000,  0x000,  0x33E,  0x33E,  0x000,  0x000,  0x000,
  },
  {
    0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,
    0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,
    0x000,  0x000,  0x33E,  0x000,  0x000,  0x33E,  0x000,  0x000,
    0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,
    0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,
    0x000,  0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,  0x000,
    0x000,  0x000,  0x000,  0x33E,  0x33E,  0x000,  0x000,  0x000,
    0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,
  },
  // count 2
  {
    0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,
    0x000,  0x33E,  0x33E,  0x000,  0x000,  0x33E,  0x33E,  0x000,
    0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,
    0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,
    0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,
    0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,
    0x000,  0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,  0x000,
    0x000,  0x000,  0x000,  0x33E,  0x33E,  0x000,  0x000,  0x000,
  },
  {
    0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,
    0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,
    0x000,  0x000,  0x33E,  0x000,  0x000,  0x33E,  0x000,  0x000,
    0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,
    0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,
    0x000,  0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,  0x000,
    0x000,  0x000,  0x000,  0x33E,  0x33E,  0x000,  0x000,  0x000,
    0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,
  },
  //count 3
  {
    0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,
    0x000,  0x33E,  0x33E,  0x000,  0x000,  0x33E,  0x33E,  0x000,
    0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,
    0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,
    0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,
    0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,
    0x000,  0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,  0x000,
    0x000,  0x000,  0x000,  0x33E,  0x33E,  0x000,  0x000,  0x000,
  },
  {
    0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,
    0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,
    0x000,  0x000,  0x33E,  0x000,  0x000,  0x33E,  0x000,  0x000,
    0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,
    0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,
    0x000,  0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,  0x000,
    0x000,  0x000,  0x000,  0x33E,  0x33E,  0x000,  0x000,  0x000,
    0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,
  },
  // count 4
  {
    0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,
    0x000,  0x33E,  0x33E,  0x000,  0x000,  0x33E,  0x33E,  0x000,
    0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,
    0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,
    0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,
    0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,
    0x000,  0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,  0x000,
    0x000,  0x000,  0x000,  0x33E,  0x33E,  0x000,  0x000,  0x000,
  },
  {
    0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,
    0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,
    0x000,  0x000,  0x33E,  0x000,  0x000,  0x33E,  0x000,  0x000,
    0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,
    0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,
    0x000,  0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,  0x000,
    0x000,  0x000,  0x000,  0x33E,  0x33E,  0x000,  0x000,  0x000,
    0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,
  },
  // count 5
  {
    0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,
    0x000,  0x33E,  0x33E,  0x000,  0x000,  0x33E,  0x33E,  0x000,
    0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,
    0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,
    0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,
    0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,
    0x000,  0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,  0x000,
    0x000,  0x000,  0x000,  0x33E,  0x33E,  0x000,  0x000,  0x000,
  },
  {
    0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,
    0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,
    0x000,  0x000,  0x33E,  0x000,  0x000,  0x33E,  0x000,  0x000,
    0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,
    0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,
    0x000,  0x000,  0x33E,  0x33E,  0x33E,  0x33E,  0x000,  0x000,
    0x000,  0x000,  0x000,  0x33E,  0x33E,  0x000,  0x000,  0x000,
    0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,  0x000,
  },
};



void display_rgbBitmap(uint8_t bmp_num) {
  static uint16_t bmx, bmy;

  fixdrawRGBBitmap(bmx, bmy, RGB_bmp[bmp_num], 8, 8);
  bmx += 8;                                 
  if (bmx >= mw) bmx = 0;
  if (!bmx) bmy += 8;
  if (bmy >= mh) bmy = 0;
  matrix->show();
}

void display_rgbBitmap_1(uint8_t bmp_num) {
  static uint16_t bmx, bmy;

  fixdrawRGBBitmap(bmx, bmy, RGB_bmp_1[bmp_num], 8, 8);
  bmx += 8;                                 
  if (bmx >= mw) bmx = 0;
  if (!bmx) bmy += 8;
  if (bmy >= mh) bmy = 0;
  matrix->show();
}

// Convert a BGR 4/4/4 bitmap to RGB 5/6/5 used by Adafruit_GFX
void fixdrawRGBBitmap(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h) {
  uint16_t RGB_bmp_fixed[w * h];
  for (uint16_t pixel = 0; pixel < w * h; pixel++) {
    uint8_t r, g, b;
    uint16_t color = pgm_read_word(bitmap + pixel);

    //Serial.print(color, HEX);
    b = (color & 0xF00) >> 8;
    g = (color & 0x0F0) >> 4;
    r = color & 0x00F;
    //Serial.print(" ");
    //Serial.print(b);
    //Serial.print("/");
    //Serial.print(g);
    //Serial.print("/");
    //Serial.print(r);
    //Serial.print(" -> ");
    // expand from 4/4/4 bits per color to 5/6/5
    b = map(b, 0, 15, 0, 31);
    g = map(g, 0, 15, 0, 63);
    r = map(r, 0, 15, 0, 31);
    //Serial.print(r);
    //Serial.print("/");
    //Serial.print(g);
    //Serial.print("/");
    //Serial.print(b);
    RGB_bmp_fixed[pixel] = (r << 11) + (g << 5) + b;
   // Serial.print(" -> ");
    //Serial.print(pixel);
    //Serial.print(" -> ");
    //Serial.println(RGB_bmp_fixed[pixel], HEX);
  }
  matrix->drawRGBBitmap(x, y, RGB_bmp_fixed, w, h);
}
*/

void black_off()
{
  matrix.fillScreen(matrix.Color(0, 0, 0));
  matrix.show();
}

void minute_wait_A()
{
  int M_C[8][8] = {  
   {0, 0, 0, 0, 1, 1, 1, 1},
   {1, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 0},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 1, 1, 1, 1, 1, 1, 1}
  };
  
  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(M_C[row][column] == 1) {
       matrix.drawPixel(column, row, matrix.Color(255, 0, 0));
     }
   }
  }
  matrix.show();
}

void minute_wait_B()
{
  int M_C_B[8][8] = {  
   {0, 0, 0, 0, 1, 1, 1, 1},
   {1, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 1, 1, 0, 0, 1},
   {1, 0, 0, 0, 1, 0, 0, 0},
   {1, 0, 0, 1, 0, 0, 0, 1},
   {1, 0, 0, 1, 1, 1, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 1, 1, 1, 1, 1, 1, 1}
  };
  
  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(M_C_B[row][column] == 1) {
       matrix.drawPixel(column, row, matrix.Color(255, 0, 0));
     }
   }
  }
  matrix.show();
}

void smile_frame_1()
{
  int M_C[8][8] = {  
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 1, 0, 0, 1, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 1, 1, 1, 1, 0, 1},
   {1, 0, 1, 1, 1, 1, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 1, 1, 1, 1, 1, 1, 1}
  };
  
  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(M_C[row][column] == 1) {
       matrix.drawPixel(column, row, matrix.Color(255, 0, 255));
     }
   }
  }
  matrix.show();
}

void smile_frame_2()
{
  int M_C[8][8] = {  
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 1, 0, 0, 1, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 1, 1, 0, 0, 1},
   {1, 0, 0, 1, 1, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 1, 1, 1, 1, 1, 1, 1}
  };
  
  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(M_C[row][column] == 1) {
       matrix.drawPixel(column, row, matrix.Color(255, 0, 255));
     }
   }
  }
  matrix.show();
}

void love_frame_1()
{
  int M_C[8][8] = {  
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 1, 0, 0, 1, 0, 0},
   {0, 1, 1, 1, 1, 1, 1, 0},
   {0, 1, 1, 1, 1, 1, 1, 0},
   {0, 0, 1, 1, 1, 1, 0, 0},
   {0, 0, 0, 1, 1, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0}
  };
  
  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(M_C[row][column] == 1) {
       matrix.drawPixel(column, row, matrix.Color(255, 0, 0));
     }
   }
  }
  matrix.show();
}

void love_frame_2()
{
  int M_C[8][8] = {  
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 1, 1, 0, 0, 1, 1, 0},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {0, 1, 1, 1, 1, 1, 1, 0},
   {0, 0, 1, 1, 1, 1, 0, 0},
   {0, 0, 0, 1, 1, 0, 0, 0}
  };
  
  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(M_C[row][column] == 1) {
       matrix.drawPixel(column, row, matrix.Color(255, 0, 0));
     }
   }
  }
  matrix.show();
}

void min_frame_three_1()
{
  int M_C[8][8] = {  
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 0, 0, 0, 0, 1, 1},
   {1, 1, 1, 1, 1, 0, 1, 1},
   {1, 1, 0, 0, 0, 0, 1, 1},
   {1, 1, 1, 1, 1, 0, 1, 1},
   {1, 1, 0, 0, 0, 0, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1}
  };
  
  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(M_C[row][column] == 1) {
       matrix.drawPixel(column, row, matrix.Color(255, 0, 0));
     }
   }
  }
  matrix.show();
}

void min_frame_three_2()
{
  int M_C[8][8] = {  
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1}
  };
  
  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(M_C[row][column] == 1) {
       matrix.drawPixel(column, row, matrix.Color(255, 0, 0));
     }
   }
  }
  matrix.show();
}

void min_frame_one_1()
{
  int M_C[8][8] = {  
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 0, 0, 1, 1, 1},
   {1, 1, 1, 1, 0, 1, 1, 1},
   {1, 1, 1, 1, 0, 1, 1, 1},
   {1, 1, 1, 1, 0, 1, 1, 1},
   {1, 1, 0, 0, 0, 0, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1}
  };
  
  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(M_C[row][column] == 1) {
       matrix.drawPixel(column, row, matrix.Color(255, 0, 0));
     }
   }
  }
  matrix.show();
}

void min_frame_one_2()
{
  int M_C[8][8] = {  
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1}
  };
  
  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(M_C[row][column] == 1) {
       matrix.drawPixel(column, row, matrix.Color(255, 0, 0));
     }
   }
  }
  matrix.show();
}


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(64, PIN, NEO_GRB + NEO_KHZ800);

byte smile[] = {B00000000, B00000000, B01111110, B01000010, B00000000, B00100100, B00100100, B00000000};
byte hhLogo[] = {B00000000, B01010000, B01111010, B01011110, B10001010, B01000001, B00110010, B00001100};
byte diamond[] = {B00000000, B00011000, B00111100, B01111110, B01111110, B00111100, B00011000, B00000000};
byte hacksterLogo[] = {B00000000, B00100100, B00100100, B01110100, B10111101, B00101110, B00100100, B00100100};
byte subscribe[] = {B00000000, B01110000, B00100100, B00101110, B00100100, B00110000, B00100000, B00000000};

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void clear() {
  for(int i=0;i<64;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  }
}

void setPixelForColor(int row, int col, uint32_t color) {
  if ((row % 2) == 1){
    pixels.setPixelColor(row*8+(7-col), color); 
  } else {
    pixels.setPixelColor(row*8+col, color); 
  }
}




void drawShape(byte shape[], uint32_t color, boolean flash, int cycles, int delayTime) {
  for(int c = 0; c < cycles; c++) {
    for(int i=0;i<8;i++) {
      for(int j=0; j<8; j++) {
        if(bitRead(shape[i], j) == 1) {
          setPixelForColor(i, j, color);
        }
      }
    }
  
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayTime); // Delay for a period of time (in milliseconds).
  
    if (flash) {
      clear();
      pixels.show();
      delay(delayTime); // Delay for a period of time (in milliseconds).
    }
  }

  clear();
  pixels.show();
}

void animate(byte shape[][8], int frames, uint32_t color, int cycles, int delayTime) {
  for (int c=0; c<cycles; c++) {
    for (int s=0; s<frames; s++) {
      drawShape(shape[s], color, false, 1, delayTime);
    }
  }

  clear();
  pixels.show();
}

void rainbowShape(byte shape[], uint8_t wait){
  for(int r=0; r<256; r++) {
    for(int i=0;i<8;i++){
      for(int j=0; j<8; j++) {
        if(bitRead(shape[i], j) == 1){
          setPixelForColor(i, j, Wheel((i+j+r) & 255));
        }
      }
    }
    
    pixels.show();
    delay(wait);
  }
  clear();
  pixels.show();
}

void rainbowAnimation(byte shape[][8], int frames, int cycles, int delayTime) {
  for (int c=0; c<cycles; c++) {
    for (int r=0; r<256; r+=35) {
      for (int s=0; s<frames; s++) {
        drawShape(shape[s], Wheel(r), false, 1, delayTime);
      }
    }
  }

  clear();
  pixels.show();
}

void tunnelAnimation(uint32_t color, boolean rainbow, int cycles, int delayTime) {
  byte animation[][8] = {{B00000000, B00000000, B00000000, B00011000, B00011000, B00000000, B00000000, B00000000},
  {B00000000, B00000000, B00111100, B00100100, B00100100, B00111100, B00000000, B00000000},
  {B00000000, B01111110, B01000010, B01000010, B01000010, B01000010, B01111110, B00000000},
  {B11111111, B10000001, B10000001, B10000001, B10000001, B10000001, B10000001, B11111111}};

  if (rainbow) {
    rainbowAnimation(animation, 4, cycles, delayTime);
  } else {
    animate(animation, 4, color, cycles, delayTime); 
  }
}

void rain(int cycles, int delayTime) {
  int rain[] = {0,0,0,0,0,0,0,0};
  int values[] = {0,0,0,0,0,0,0,0};

  for (int v=0; v<8; v++) {
    values[v] = random(0, 10) * 10;
  }

  for (int c=0; c<cycles; c++) {
    for (int f=0; f<10; f++) {
      for (int col = 0; col < 8; col++) {
        int row = map(values[col], 0, 100, 0, 8);
        if ((row % 2) == 1) {
          pixels.setPixelColor((64-row*8)+(7-col), pixels.Color(200,0,200));
        } else {
          pixels.setPixelColor((64-row*8)+col, pixels.Color(200,0,200));
        }
      }
      
      pixels.show();
      delay(delayTime);
      
      for (int v=0; v<8; v++) {
        values[v] = (values[v] + 10) % 100;
      }
      
      clear();
      //delay(100);
     }
   }
}


/*
void rain(int cycles) {
  int rain[] = {0,0,0,0,0,0,0,0};
  int values[] = {0,0,0,0,0,0,0,0};

  for (int v=0; v<8; v++) {
    values[v] = random(0, 10) * 10;
  }

  for (int c=0; c<cycles; c++) {
    for (int f=0; f<10; f++) {
      for (int col = 0; col < 8; col++) {
        int row = map(values[col], 0, 100, 0, 8);
        if ((row % 2) == 1) {
          pixels.setPixelColor((64-row*8)+(7-col), pixels.Color(200,0,200));
        } else {
          pixels.setPixelColor((64-row*8)+col, pixels.Color(200,0,200));
        }
      }
      pixels.show();
      
      //delay(delayTime);
      ms_from_start = millis();
      if(ms_from_start - ms_previos_read_LED1 > LED1_interval)
      {
        ms_previos_read_LED1 = ms_from_start;
        if(idle1_video_state == 0)idle1_video_state = 1;
        else idle1_video_state = 0;
      }  
      if(idle1_video_state == 1)
      {  
        for (int v=0; v<8; v++) {
          values[v] = (values[v] + 10) % 100;
        }
        //clear();
      }
      clear();
      //delay(50);     // 100
    }
  }
}
*/

void sineWave(int cycles, int delayLength) {
  int wave[] = {0,0,0,0,0,0,0,0};
   int values[] = {0,0,0,0,0,0,0,0};

   for (int c = 0; c < cycles; c++) {
    for (int p = 0; p < 360/10; p++) {
       wave[0] = (wave[0] + 10) % 360;
       values[0] = int(50.0*(sin(1*(wave[0]*PI/180)) + 1));
    
       for(int i=1; i<8; i++) {
        wave[i] = (wave[i-1] + int(360.0/8.0)) % 360;
        values[i] = int(50.0*(sin(1*(wave[i]*PI/180)) + 1));
       }
      
      clear();
      
      //Draw the audio levels
      for (int col = 0; col < 8; col++) {
        for(int row = 0; row < map(values[col], 0, 100, 2, 8); row++){
          if ((row % 2) == 1) {
            pixels.setPixelColor(row*8+(7-col), pixels.Color(row*30,  96 - 10*row, 0));
          } else {
            pixels.setPixelColor(row*8+col, pixels.Color(row*30,  96 - 12*row, 0));
          }
          
        }
      }
      pixels.show();
      delay(delayLength);
    }
   }
   //clear();
   pixels.show();
}

void audioLevels(int cycles, int delayLength) {
  int wave[] = {0,0,0,0};
   int values[] = {0,0,0,0};

   for (int c = 0; c < cycles; c++) {
    for (int p = 0; p < 360/10; p++) {
       wave[0] = (wave[0] + 10) % 360;
       values[0] = int(50.0*(sin(1*(wave[0]*PI/180)) + 1));
    
       for(int i=1; i<4; i++) {
        wave[i] = (wave[i-1] + 102) % 360;
        values[i] = int(50.0*(sin(1*(wave[i]*PI/180)) + 1));
       }
      
      clear();
      
      //Draw the audio levels
      for (int col = 0; col < 4; col++) {
        for(int row = 0; row < map(values[col], 0, 100, 2, 8); row++){
          if ((row % 2) == 1) {
            pixels.setPixelColor(row*8+(7-2*col), pixels.Color(0,  row*30, 96 - 10*row));
            pixels.setPixelColor(row*8+(7-2*col-1), pixels.Color(0,  row*30, 96 - 10*row));
          } else {
            pixels.setPixelColor(row*8+2*col, pixels.Color(0,  row*30, 96 - 12*row));
            pixels.setPixelColor(row*8+2*col+1, pixels.Color(0, row*30,  96 - 12*row));
          }
          
        }
      }
      
      pixels.show();
      delay(delayLength);
    }
   }
   clear();
   pixels.show();
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<64; i++) {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
  clear();
  pixels.show();
}

#endif /* Animation_h */
