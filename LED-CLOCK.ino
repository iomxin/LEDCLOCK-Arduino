#include<TM1638plus.h>

#define STB 4
#define CLK 6
#define DIO 7
int h = 0, m = 0, s = 0;
long tmpMillis = 0;
String converter = String();
String converter1 = String();
String converter2 = String();
TM1638plus tm(STB, CLK, DIO);
char sec[16];
uint8_t mode = 0, modein = 0;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buttons = tm.readButtons();
  if (buttons == 1) {
    mode++;
    delay(500);
  }
  if (mode == 0) {
    long currentMillis = millis();
    if (currentMillis > tmpMillis) {
      tmpMillis = currentMillis + 1000;
      s++;
    }
    Time();
    showTime();
  }
  if (mode == 1) {
    Time();
    showTime();
    if (buttons == 8) {
      modein++;
      delay(400);
    }
    if (modein > 2) {
      modein = 0;
    }
    if (modein == 0) {
      if (buttons == 2) {
        s++;
        delay(500);
      }
      if (buttons == 4) {
        s--;
        delay(500);
      }
    }
        if (modein == 1) {
      if (buttons == 2) {
        m++;
        delay(500);
      }
      if (buttons == 4) {
        m--;
        delay(500);
      }
    }
        if (modein == 2) {
      if (buttons == 2) {
        h++;
        delay(500);
      }
      if (buttons == 4) {
        h--;
        delay(500);
      }
    }
  }
  if (mode > 1) {
    mode = 0;
  }
  tm.displayText(sec);
}
void showTime() {
  if (s < 10 && m < 10 && h < 10) {
    converter = "0" + String(h) + "-" + "0" + String(m) + "-" + "0" + String(s); //000
    converter.toCharArray(sec, 16);
  }
  if (s >= 10 && m < 10 && h < 10) {
    converter = "0" + String(h) + "-" + "0" + String(m) + "-" + String(s);//001
    converter.toCharArray(sec, 16);
  }
  if (s < 10 && m >= 10 && h < 10) {
    converter = "0" + String(h) + "-" + String(m) + "-" + "0" + String(s); //010
    converter.toCharArray(sec, 16);
  }
  if (s >= 10 && m >= 10 && h < 10) {
    converter = "0" + String(h) + "-" + String(m) + "-" + String(s); //011
    converter.toCharArray(sec, 16);
  }
  if (s < 10 && m < 10 && h >= 10) {
    converter = String(h) + "-" + "0" + String(m) + "-" + "0" + String(s); //100
    converter.toCharArray(sec, 16);
  }
  if (s >= 10 && m < 10 && h >= 10) {
    converter = String(h) + "-" + "0" + String(m) + "-" + String(s); //101
    converter.toCharArray(sec, 16);
  }
  if (s < 10 && m >= 10 && h >= 10) {
    converter = String(h) + "-" + String(m) + "-" + "0" + String(s); //110
    converter.toCharArray(sec, 16);
  }
  if (s >= 10 && m >= 10 && h >= 10) {
    converter = String(h) + "-" + String(m) + "-" + String(s); //111
    converter.toCharArray(sec, 16);
  }
}
void Time() {
  if (s > 59) {
    s = 0;
    m++;
  }
  if (m > 59) {
    m = 0;
    h++;
  }
  if (h > 23) {
    h = 0;
  }
}
