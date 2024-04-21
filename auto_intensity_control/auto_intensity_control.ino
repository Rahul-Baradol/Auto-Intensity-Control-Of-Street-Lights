#include <LiquidCrystal.h>

const int ldr1 = A0;
const int ldr2 = A1;
const int ldr3 = A4;
const int ldr4 = A5;

const int led1 = 3;
const int led2 = 5;
const int led3 = 6;
const int led4 = 9;

const int rs = 13;
const int en = 12;
const int d7 = 11;
const int d6 = 4;
const int d5 = 8;
const int d4 = 7;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  pinMode(ldr1, INPUT);
  pinMode(ldr2, INPUT);
  pinMode(ldr3, INPUT);
  pinMode(ldr4, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  lcd.begin(16, 2);
}

int calibratedMaxLDRValue = 900; // 900
const int calibratedMinLDRValue = 0; // 200
const int maxBrightnessValue = 255;

void printLDRInputValues(int ldrIn1, int ldrIn2, int ldrIn3, int ldrIn4) {
  Serial.print("LDR Input values: ");
  Serial.print(ldrIn1);
  Serial.print(" ");
  Serial.print(ldrIn2);
  Serial.print(" ");
  Serial.print(ldrIn3);
  Serial.print(" ");
  Serial.println(ldrIn4);
}

void printBrightness(int ldrIn1, int ldrIn2, int ldrIn3, int ldrIn4) {
  Serial.print("Brightness Values: ");
  Serial.print(ldrIn1);
  Serial.print(" ");
  Serial.print(ldrIn2);
  Serial.print(" ");
  Serial.print(ldrIn3);
  Serial.print(" ");
  Serial.println(ldrIn4);
}

int calculateBrightness(int ldrValue) {
  float ldrFactor = (ldrValue - calibratedMinLDRValue) / (calibratedMaxLDRValue - calibratedMinLDRValue * 1.0);

  if (ldrFactor < 0) {
    ldrFactor = 0;
  }

  if (ldrFactor > 1) {
    ldrFactor = 1;
  }

  float brightnessFactor = 1 - ldrFactor;
  int brightness = brightnessFactor * maxBrightnessValue;
  return brightness;
}

void displayLEDPercentage(int led1, int led2, int led3, int led4) {
  // Calculate percentage values
  int percentage1 = map(led1, 0, 255, 0, 100);
  int percentage2 = map(led2, 0, 255, 0, 100);
  int percentage3 = map(led3, 0, 255, 0, 100);
  int percentage4 = map(led4, 0, 255, 0, 100);
  
  // Clear the LCD screen
  lcd.clear();
  
  // Display percentages on LCD
  lcd.setCursor(0, 0);
  lcd.print("Led1:");
  lcd.print(percentage1);
  lcd.print("%");
  
  lcd.setCursor(0, 1);
  lcd.print("Led2:");
  lcd.print(percentage2);
  lcd.print("%");

  lcd.setCursor(8, 0);
  lcd.print("Led3:");
  lcd.print(percentage3);
  lcd.print("%");

  lcd.setCursor(8, 1);
  lcd.print("Led4:");
  lcd.print(percentage4);
  lcd.print("%");
}

int counter = 0;

void loop() {
  // reads analog data from light sensor
  int ldrIn1 = analogRead(ldr1);
  int ldrIn2 = analogRead(ldr2);
  int ldrIn3 = analogRead(ldr3);
  int ldrIn4 = analogRead(ldr4);

  if (counter <= 10) {
    if (ldrIn1 < calibratedMaxLDRValue) {
      calibratedMaxLDRValue = ldrIn1;
    }

    if (ldrIn2 < calibratedMaxLDRValue) {
      calibratedMaxLDRValue = ldrIn2;
    }

    if (ldrIn3 < calibratedMaxLDRValue) {
      calibratedMaxLDRValue = ldrIn3;
    }

    if (ldrIn4 < calibratedMaxLDRValue) {
      calibratedMaxLDRValue = ldrIn4;
    }

    counter++;
    return;
  }

  int brightness1 = calculateBrightness(ldrIn1);
  int brightness2 = calculateBrightness(ldrIn2);
  int brightness3 = calculateBrightness(ldrIn3);
  int brightness4 = calculateBrightness(ldrIn4);

  // this is being done because there is no resistor connected to this led
  const int noResistorBrightness4 = (brightness4 / 255.0) * 25; 

  analogWrite(led1, brightness1);
  analogWrite(led2, brightness2);
  analogWrite(led3, brightness3);
  analogWrite(led4, noResistorBrightness4);

  printLDRInputValues(ldrIn1, ldrIn2, ldrIn3, ldrIn4);
  printBrightness(brightness1, brightness2, brightness3, brightness4);
  Serial.println();

  displayLEDPercentage(brightness1, brightness2, brightness3, brightness4);

  delay(10);
}
