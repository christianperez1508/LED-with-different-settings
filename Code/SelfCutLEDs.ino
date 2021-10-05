#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDRESS 0x27

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

const byte R_PIN = 9;
const byte G_PIN = 10;
const byte B_PIN = 11;
const byte BUTT_PIN = 2;

typedef struct {
  byte butt_delay;
  unsigned long first_case_time;
  unsigned long second_case_time;
  unsigned long current_time;
  unsigned long butt_time;
} Timers;

typedef struct {
  int main_menu;
  int menu1;
} Menu;

typedef struct {
  volatile byte state;
  volatile byte flag;
} Interrupts;

Timers timers = {50, 0, 0, 0, 0};
Menu menu = {0, 0};
Interrupts states = {0, 0};

void setup() {
  pinMode(BUTT_PIN, INPUT_PULLUP);
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  lcd.begin();
  attachInterrupt(digitalPinToInterrupt(BUTT_PIN), read_butt, LOW);
  lcd.setCursor(3, 0);
  lcd.print("Christian's");
  lcd.setCursor(0, 1);
  lcd.print("Self-Cut System");
  delay(5000);
  check_menu();
}

void loop() {
  if (states.flag) {
    store_timers();
  }
  switch (menu.main_menu) {
    case 0:
      switch (menu.menu1) {
        case 0:
          tungsten(100);
          break;

        case 1:
          tungsten(75);
          break;

        case 2:
          tungsten(50);
          break;

        case 3:
          tungsten(25);
          break;
      }
      break;

    case 1:
      switch (menu.menu1) {
        case 0:
          halogen(100);
          break;

        case 1:
          halogen(75);
          break;

        case 2:
          halogen(50);
          break;

        case 3:
          halogen(25);
          break;
      }
      break;

    case 2:
      switch (menu.menu1) {
        case 0:
          carbon_arc(100);
          break;

        case 1:
          carbon_arc(75);
          break;

        case 2:
          carbon_arc(50);
          break;

        case 3:
          carbon_arc(25);
          break;
      }
      break;

    case 3:
      switch (menu.menu1) {
        case 0:
          sun(100);
          break;

        case 1:
          sun(75);
          break;

        case 2:
          sun(50);
          break;

        case 3:
          sun(25);
          break;
      }
      break;

    case 4:
      switch (menu.menu1) {
        case 0:
          blue_sky(100);
          break;

        case 1:
          blue_sky(75);
          break;

        case 2:
          blue_sky(50);
          break;

        case 3:
          blue_sky(25);
          break;
      }
      break;
  }
}

void read_butt() {
  if ((millis() - timers.butt_time) > timers.butt_delay) {
    states.flag = 1;
    if (states.state < 1) states.state++;
    else states.state = 0;
    timers.butt_time = millis();
  }
}

void store_timers() {
  switch (states.state) {
    case 0:
      timers.second_case_time = millis();
      break;

    case 1:
      timers.first_case_time = millis();
      break;

    default:
      break;
  }
  states.flag = 0;
  check_menu();
}

void check_menu() {
  if (timers.second_case_time > timers.first_case_time) {
    if ((timers.second_case_time - timers.first_case_time) < 500) {
      menu.menu1 = 0;
      if (menu.main_menu < 4) menu.main_menu++;
      else menu.main_menu = 0;
    }
    else {
      if (menu.menu1 < 3) menu.menu1++;
      else menu.menu1 = 0;
    }
  }
  else {
    if ((timers.first_case_time - timers.second_case_time) < 500) {
      menu.menu1 = 0;
      if (menu.main_menu < 4) menu.main_menu++;
      else menu.main_menu = 0;
    }
    else {
      if (menu.menu1 < 3) menu.menu1++;
      else menu.menu1 = 0;
    }
  }
  update_screen();
}

void update_screen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  switch (menu.main_menu) {
    case 0:
      lcd.print("Tungsten");
      switch (menu.menu1) {
        case 0:
          lcd.setCursor(0, 1);
          lcd.print("Brightness: 100%");
          break;

        case 1:
          lcd.setCursor(0, 1);
          lcd.print("Brightness: 75%");
          break;

        case 2:
          lcd.setCursor(0, 1);
          lcd.print("Brightness: 50%");
          break;

        case 3:
          lcd.setCursor(0, 1);
          lcd.print("Brightness: 25%");
          break;
      }
      break;

    case 1:
      lcd.print("Halogen");
      switch (menu.menu1) {
        case 0:
          lcd.setCursor(0, 1);
          lcd.print("Brightness: 100%");
          break;

        case 1:
          lcd.setCursor(0, 1);
          lcd.print("Brightness: 75%");
          break;

        case 2:
          lcd.setCursor(0, 1);
          lcd.print("Brightness: 50%");
          break;

        case 3:
          lcd.setCursor(0, 1);
          lcd.print("Brightness: 25%");
          break;
      }
      break;

    case 2:
      lcd.print("Carbon Arc");
      switch (menu.menu1) {
        case 0:
          lcd.setCursor(0, 1);
          lcd.print("Brightness: 100%");
          break;

        case 1:
          lcd.setCursor(0, 1);
          lcd.print("Brightness: 75%");
          break;

        case 2:
          lcd.setCursor(0, 1);
          lcd.print("Brightness: 50%");
          break;

        case 3:
          lcd.setCursor(0, 1);
          lcd.print("Brightness: 25%");
          break;
      }
      break;

    case 3:
      lcd.print("Sun");
      switch (menu.menu1) {
        case 0:
          lcd.setCursor(0, 1);
          lcd.print("Brightness: 100%");
          break;

        case 1:
          lcd.setCursor(0, 1);
          lcd.print("Brightness: 75%");
          break;

        case 2:
          lcd.setCursor(0, 1);
          lcd.print("Brightness: 50%");
          break;

        case 3:
          lcd.setCursor(0, 1);
          lcd.print("Brightness: 25%");
          break;
      }
      break;

    case 4:
      lcd.print("Blue Sky");
      switch (menu.menu1) {
        case 0:
          lcd.setCursor(0, 1);
          lcd.print("Brightness: 100%");
          break;

        case 1:
          lcd.setCursor(0, 1);
          lcd.print("Brightness: 75%");
          break;

        case 2:
          lcd.setCursor(0, 1);
          lcd.print("Brightness: 50%");
          break;

        case 3:
          lcd.setCursor(0, 1);
          lcd.print("Brightness: 25%");
          break;
      }
      break;
  }
}

void RGB(int Red, int Green, int Blue) {
  analogWrite(R_PIN, Red);
  analogWrite(B_PIN, Green);
  analogWrite(G_PIN, Blue);
}

void tungsten(float intensity) {
  int brightness_red = (intensity / 100) * 255;
  int brightness_green = (intensity / 100) * 187;
  int brightness_blue = (intensity / 100) * 120;
  RGB(brightness_red, brightness_green, brightness_blue);
}

void halogen(float intensity) {
  int brightness_red = (intensity / 100) * 255;
  int brightness_green = (intensity / 100) * 241;
  int brightness_blue = (intensity / 100) * 224;
  RGB(brightness_red, brightness_green, brightness_blue);
}

void carbon_arc(float intensity) {
  int brightness_red = (intensity / 100) * 255;
  int brightness_green = (intensity / 100) * 187;
  int brightness_blue = (intensity / 100) * 120;
  RGB(brightness_red, brightness_green, brightness_blue);
}

void sun(float intensity) {
  int brightness_red = (intensity / 100) * 255;
  int brightness_green = (intensity / 100) * 255;
  int brightness_blue = (intensity / 100) * 251;
  RGB(brightness_red, brightness_green, brightness_blue);
}

void blue_sky(float intensity) {
  int brightness_red = (intensity / 100) * 64;
  int brightness_green = (intensity / 100) * 156;
  int brightness_blue = (intensity / 100) * 255;
  RGB(brightness_red, brightness_green, brightness_blue);
}
