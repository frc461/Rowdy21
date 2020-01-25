#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

#define PIN 6
#define trueNum 18
#define BRIGHTNESS 50

void dot();
void space();

static String scolor;

uint8_t color = 0x00;
uint8_t datas[1] = {color};

static uint8_t dataFromRobot = 0x00;
int spinCounter;
//Declare a strip of leds with length of "trueNum" and on pin "PIN"
Adafruit_NeoPixel strip = Adafruit_NeoPixel(trueNum, PIN, NEO_RGB + NEO_KHZ800);

//COLOR LIST:
//50 = Yellow
//70 = Orange
//85 = Red
//100 = Magenta
//140 = Purple
//180 = Blue
//230 = Teal
//250 = Green

/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
// Pick analog outputs, for the UNO these three work well
// use ~560  ohm resistor between Red & Blue, ~1K for green (its brighter)
#define redpin 3
#define greenpin 5
#define bluepin 6
// for a common anode LED, connect the common pin to +5V
// for common cathode, connect the common to ground

// set to false if using a common cathode LED
#define commonAnode true

// our RGB -> eye-recognized gamma color
byte gammatable[256];

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  //Need 115200 Baud rate for LED communication protocol. 
  Serial.begin(115200);
  
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show();
  
  Wire.begin(4);
  Wire.onRequest(sendData);
  Wire.onReceive(readData);
  if (tcs.begin()) {
  } 
  else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }

// use these three pins to drive an LED
#if defined(ARDUINO_ARCH_ESP32)
  ledcAttachPin(redpin, 1);
  ledcSetup(1, 12000, 8);
  ledcAttachPin(greenpin, 2);
  ledcSetup(2, 12000, 8);
  ledcAttachPin(bluepin, 3);
  ledcSetup(3, 12000, 8);
#else
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
#endif

}

void setHue(int h, uint16_t n) {
  //this is the algorithm to convert from a decimal to RGB
  //Don't worry about the math behind this too much. Just accept that it works and use it :)
  double r=0; 
  double g=0; 
  double b=0;

  double hf=h/42.5; // Not /60 as range is _not_ 0-360

  int i=(int)floor(h/42.5);
  double f = h/42.5 - i;
  double qv = 1 - f;
  double tv = f;

  switch (i)
  {
  case 0: 
    r = 1;
    g = tv;
    break;
  case 1: 
    r = qv;
    g = 1;
    break;
  case 2: 
    g = 1;
    b = tv;
    break;
  case 3: 
    g = qv;
    b = 1;
    break;
  case 4:
    r = tv;
    b = 1;
    break;
  case 5: 
    r = 1;
    b = qv;
    break;
  }

  int red = constrain((int)255*r,0,255);
  int green = constrain((int)255*g,0,255);
  int blue = constrain((int)255*b,0,255);
  strip.setPixelColor(n,strip.Color(red,green,blue));
}
/********************************************************************************************************************************************/

/********************************************************************************************************************************************/
void loop() {
  strip.setBrightness(BRIGHTNESS);
  IntakeIn();
  //Climb();
  //climb();
 // SpinTheWheel();
  //Disco();
  //Teleop();
  //Autonomous();
  //OnAndConnected();
  //OnButNotConnected();
  //MotorGauge();
  //LowVoltage();
  //Overcurrent();
  //LowPressure();
  //Climb();
  //LimelightAim();
  strip.show();
}
void SelectProgram(){
  uint8_t states = dataFromRobot;
  switch(states){
  case 0x06:
  OnAndConnected();
  break;
  case 0x07:
  OnButNotConnected();
  break;
  case 0x08:
  Autonomous();
  break;
  case 0x09:
  Teleop();
  break;
  case 0x0A:
  ColorSensor();
  break;
  case 0x0B:
  SpinTheWheel();
  break;
  case 0x0C:
  //MotorGauge();
  break;
  case 0x0D:
  //Shooting();
  break;
  case 0x0E:
  LowVoltage();
  break;
  case 0x0F:
  Overcurrent();
  break;
  case 0x10:
  LowPressure();
  break;
  case 0x11:
  Climb();
  break;
  case 0x12:
  Disco();
  break;
  case 0x13:
  LimelightAim();
  break;
  case 0x14:
  //IntakeOut();
  break;
  case 0x15:
  IntakeIn();
  break;
  
  default:
    break;  
  }
}

void sendData() {
  datas[0] = color;
  Wire.write(datas[0]);
}
void readData(int l) {
  while(Wire.available()) {
    dataFromRobot = Wire.read();
    Serial.println(dataFromRobot);
  }
}

void ColorSensor() {
  float red;
  float green;
  float blue;
  tcs.setInterrupt(true);
  tcs.getRGB(&red, &green, &blue);
  
  if (red > blue and red > green and red > 120){
    scolor = "red";
    color = 0x01;
    for (int r = 0; r < trueNum; r++){
      setHue(85, r);
    }
  }
  else if (blue > red and blue > green - 20){
    scolor = "blue";
    color = 0x02;
    for (int r = 0; r < trueNum; r++){
       setHue(180, r);
    }
  }
  else if (green > red and green > blue + 50){
    scolor = "green";
    color = 0x03;
    for (int r= 0; r< trueNum; r++){
      setHue(250,r);
    }
  }
  else if (abs(red - green) < 60 and abs(red - blue) > 30){
    scolor = "yellow";
    color = 0x04;
    for (int r = 0; r < trueNum; r++){
      setHue(50, r);
    }
  }
  else {
    scolor = "idk man";
    color = 0x05;
    for(int r = 0; r<trueNum; r++){
      setHue(100,r);
    }
  }
}

void OnButNotConnected() {
  for (int i = 0; i < trueNum; i++) {
    for (int j = 0; j < trueNum; j++) {
      if (j != i) {
        setHue(255, j);
      }
      else {
        setHue(50, j-2);
        setHue(50, j-1);
        setHue(50, j);
        setHue(50, j+1);
        setHue(50, j+2);
        strip.show();
      }
    }
    delay(50);
  }
  for (int i = trueNum; i > 0; i--) {
    for (int j = trueNum; j > 0; j--) {
      if (j != i) {
        setHue(255, j);
      }
      else {
        setHue(50, j-2);
        setHue(50, j-1);
        setHue(50, j);
        setHue(50, j+1);
        setHue(50, j+2);
        strip.show();
      }
    }
    delay(50);
  }
}

void OnAndConnected() {
  int color = rand() % 255;
  for (int i = 0; i < trueNum; i++){
    setHue(color, i);
    strip.show();
  }
  delay(100);
  for (int i = 0; i < trueNum; i++){
    setHue(color, i);
    strip.show();
  }
  delay(100);
}

void Autonomous() {
  // anything flashy??
}

void Teleop() {
  for(int x = 0; x < trueNum; x++){
    for(int y = 0; y < trueNum; y++){
      int localColor;
      localColor = localColor + 1;
      if(localColor>255){
        localColor = 0;
      }
      if(y != x){
        setHue(255, y);
      }
      else {
        setHue(localColor, y);
        setHue(localColor, y-1);
        setHue(localColor, y+1);
        setHue(localColor, y+2);
        setHue(localColor, y-2);
        strip.show();
      }
    }
    delay(100);
  }
  for(int x = trueNum; x > 0; x--){
    for(int y = 0; y < trueNum; y++){
      int localColor;
      localColor = localColor + 1;
      if(localColor>255){
        localColor = 0;
      }
      if(y != x){
        setHue(255, y);
      }
      else{
        setHue(localColor, y);
        setHue(localColor, y-1);
        setHue(localColor, y+1);
        setHue(localColor, y+2);
        setHue(localColor, y-2);
        strip.show();
      }
    }
    delay(100);
  }
}

void MotorGauge(double motorSpeed) {
  if (motorSpeed <= 1) {
    for (int i = 0; i < (int)(abs(motorSpeed)*trueNum); i++) {
      setHue(50, i);
    }
  }
  else {
    for (int i = 0; i < trueNum; i++)
      setHue(255, i);
  }
}

void LowVoltage() {
  for (int i = 0; i < trueNum; i++){
    setHue(70, i);
    strip.show();
  }
  delay(100);
  for (int i = 0; i < trueNum; i++){
    setHue(255, i);
    strip.show();
  }
  delay(100);
}

void Overcurrent() {
  for (int i = 0; i < trueNum; i++){
    setHue(85, i);
    strip.show();
  }
  delay(100);
  for (int i = 0; i < trueNum; i++){
    setHue(255, i);
    strip.show();
  }
  delay(100);
}

void LowPressure() {
  for (int i = 0; i < trueNum; i++){
    setHue(90, i);
    strip.show();
  }
  delay(100);
  for (int i = 0; i < trueNum; i++){
    setHue(255, i);
    strip.show();
  }
  delay(100);
}

void Climb() {
  int color = 0;
  bool change = false;
  for (int i = 0; i < trueNum; i++) {
    if (color >= 250) change = true;
    else if (color <= 0) change = false;

    if (!change) color+=10;
    else if (change) color-=10;
    
    setHue(color, i);
    setHue(color, trueNum-i);
    delay(100);
    strip.show();
  }
}

void LimelightAim() {
  int green = 250;
  for(int i = 0; i<99;i++){
    strip.setBrightness(i%100);
    for (int j = 0; j < trueNum; j++) {
      setHue(green, j);
    }
    strip.show();
    delay(10);
    }
    for(int i = 99; i>0;i--){
      strip.setBrightness(i%100);
    for (int j = 0; j < trueNum; j++) {
      setHue(green, j);
    }
    strip.show();
    delay(10);
  }
}


void SpinTheWheel() {
 float red;
 float green;
 float blue;
  tcs.setInterrupt(false);
  String prevColor = scolor;
    tcs.getRGB(&red, &green, &blue);
  if (red > blue and red > green and red > 120){
    scolor = "red";
  }
  else if (blue > red and blue > green - 20){
    scolor = "blue";
  }
  else if (green > red and green > blue + 20){
    scolor = "green";
  }
  else if (abs(red - green) < 50 and abs(red - blue) > 50){
    scolor = "yellow";
  }
  else if (abs(red - green) < 50 and abs (blue - green) < 50 and green > 120){
    scolor = "white";
  }
  else if (red < 90 and green < 90 and blue < 90){
    scolor = "black";
  }
  else {
    scolor = "idk man";
  }
  if (scolor != prevColor){
    prevColor = scolor;
    spinCounter = spinCounter + trueNum/8;
    if (spinCounter>trueNum){
      spinCounter = 0;
    }
    setHue(230, spinCounter);
    setHue(230, spinCounter - 1);
    strip.show();
  }
  if(spinCounter == 0){
    for(int x = 0; x < trueNum; x++){
      setHue(255, x);
      strip.show();
    }
  }
  Serial.print ("Color: ");
  Serial.println (scolor);
  Serial.print (spinCounter);
}
void Disco(){
  for (int z = 0; z < 40; z++){
  int x = random(1, 18);
  int r = random(1, 254);
  setHue(r,x);
  setHue(r, x + 1);
  setHue(r, x - 1);
  setHue(r, x + 2);
  setHue(r, x - 2);
  strip.show();
  delay(50);
  setHue(255, x);
  setHue(255, x+1);
  setHue(255, x-1);
  setHue(255, x + 2);
  setHue(255, x - 2);
  delay(50);
  }
  for(int x = 0; x < 3; x++){
    climb();
  }
}
void climb(){
  for(int x = 0; x < trueNum; x++){
    int y = y + 255 / trueNum;
    if(y > 255){
      y = 0;
    }
    setHue(y, x);
    strip.show();
    delay (30);
    
  }
    for(int x = 0; x < trueNum; x++){
    int y = 0;
    setHue(255, x);
    strip.show();
    delay (30);
  }
}
void IntakeIn(){
  for(int x = 0; x < trueNum; x++){
    setHue(150, x);
    strip.show();
  }
    for(int y = 1; y < 100; y++){
      delay(20);
      strip.setBrightness(y);
      strip.show();
  }
  for(int y = 100; y > 1; y--){
          delay(20);
      strip.setBrightness(y);
      strip.show();
  }
}
void IntakeOut(){
  for(int x = 0; x < trueNum; x++){
    setHue(100, x);
    strip.show();
  }
    for(int y = 1; y < 100; y++){
      delay(20);
      strip.setBrightness(y);
      strip.show();
  }
  for(int y = 100; y > 1; y--){
          delay(20);
      strip.setBrightness(y);
      strip.show();
  }
}

//void Dot(){
//  for(int x = 0; x < trueNum; x++){
//    setHue(100, x);
//    strip.show(); 
//  }
//  delay(500);
//  for(int x = 0; x < trueNum; x++){
//    setHue(255, x);
//    strip.show();
//  }
//  delay(500);
//}
//
//void Space(){
//  for(int x = 0; x < trueNum; x++){
//    setHue(100, x);
//    strip.show(); 
//  }
//  delay(2000);
//  for(int x = 0; x < trueNum; x++){
//    setHue(255, x);
//    strip.show(); 
//  }
//  delay(500);
//}
