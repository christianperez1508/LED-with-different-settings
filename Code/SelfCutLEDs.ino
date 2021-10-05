#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDRESS 0x27

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

typedef struct {
  uint8_t RED;
  uint8_t GREEN;
  uint8_t BLUE;
  uint8_t BUTTON;
} Pins;

typedef struct {
  unsigned long first_case_time;
  unsigned long second_case_time;
  unsigned long current_time;
  unsigned long butt_time;
} Timers;

typedef struct {
  uint8_t main_menu;
  uint8_t menu1;
} Menu;

typedef struct {
  volatile uint8_t state;
  volatile uint8_t flag;
} Interrupts;

const Pins pins = {9, 10, 11, 2};
Timers timers = {0, 0, 0, 0};
Menu menu = {0, 0};
Interrupts states = {0, 0};
const uint8_t butt_delay = 50;

void setup() {
  pinMode(pins.BUTTON, INPUT_PULLUP);
  pinMode(pins.RED, OUTPUT);
  pinMode(pins.GREEN, OUTPUT);
  pinMode(pins.BLUE, OUTPUT);
  lcd.begin();
  attachInterrupt(digitalPinToInterrupt(pins.BUTTON), read_butt, LOW);
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
  if ((millis() - timers.butt_time) > butt_delay) {
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

void RGB(uint8_t Red, uint8_t Green, uint8_t Blue) {
  analogWrite(pins.RED, Red);
  analogWrite(pins.GREEN, Green);
  analogWrite(pins.BLUE, Blue);
}

void tungsten(float intensity) {
  uint8_t brightness_red = (intensity / 100) * 255;
  uint8_t brightness_green = (intensity / 100) * 187;
  uint8_t brightness_blue = (intensity / 100) * 120;
  RGB(brightness_red, brightness_green, brightness_blue);
}

void halogen(float intensity) {
  uint8_t brightness_red = (intensity / 100) * 255;
  uint8_t brightness_green = (intensity / 100) * 241;
  uint8_t brightness_blue = (intensity / 100) * 224;
  RGB(brightness_red, brightness_green, brightness_blue);
}

void carbon_arc(float intensity) {
  uint8_t brightness_red = (intensity / 100) * 255;
  uint8_t brightness_green = (intensity / 100) * 187;
  uint8_t brightness_blue = (intensity / 100) * 120;
  RGB(brightness_red, brightness_green, brightness_blue);
}

void sun(float intensity) {
  uint8_t brightness_red = (intensity / 100) * 255;
  uint8_t brightness_green = (intensity / 100) * 255;
  uint8_t brightness_blue = (intensity / 100) * 251;
  RGB(brightness_red, brightness_green, brightness_blue);
}

void blue_sky(float intensity) {
  uint8_t brightness_red = (intensity / 100) * 64;
  uint8_t brightness_green = (intensity / 100) * 156;
  uint8_t brightness_blue = (intensity / 100) * 255;
  RGB(brightness_red, brightness_green, brightness_blue);
}
