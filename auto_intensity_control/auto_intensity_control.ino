const int ldr1 = A0;
const int ldr2 = A1;
const int ldr3 = A4;
const int ldr4 = A5;

const int led1 = 3;
const int led2 = 5;
const int led3 = 6;
const int led4 = 9;

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
}

const int calibratedMaxLDRValue = 900;
const int calibratedMinLDRValue = 200;
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

void loop() {
  // reads analog data from light sensor
  int ldrIn1 = analogRead(ldr1);
  int ldrIn2 = analogRead(ldr2);
  int ldrIn3 = analogRead(ldr3);
  int ldrIn4 = analogRead(ldr4);

  int brightness1 = calculateBrightness(ldrIn1);
  int brightness2 = calculateBrightness(ldrIn2);
  int brightness3 = calculateBrightness(ldrIn3);
  int brightness4 = calculateBrightness(ldrIn4);

  analogWrite(led1, brightness1);
  analogWrite(led2, brightness2);
  analogWrite(led3, brightness3);
  analogWrite(led4, brightness4);

  printLDRInputValues(ldrIn1, ldrIn2, ldrIn3, ldrIn4);
  printBrightness(brightness1, brightness2, brightness3, brightness4);
  Serial.println();

  delay(10);
}
