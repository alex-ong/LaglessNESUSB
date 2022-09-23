#include "Joystick2.h"


#define NES
//#define SNES
//Connector (Connect also GND and 5V):  CLOCK, LATCH,     DATA
const uint8_t inputPinsPort1[] =       {  2,     3,     4 }; //change these as necessary
const uint8_t inputPinsPort2[] =       {  5,     7,     6 }; //change these as necessary

//Settings for PCB in hardware folder:    CLOCK  LATCH   DATA
//const uint8_t inputPinsPort1[] =       {  4,     3,     2 }; //change these as necessary
//const uint8_t inputPinsPort2[] =       {  7,     6,     5 }; //change these as necessary

uint8_t lastStatusPort1[20]; //4 directions + 16 buttons
uint8_t newStatusPort1[20];
uint8_t lastStatusPort2[20];
uint8_t newStatusPort2[20];

//--------NES--------
// http://www.mit.edu/~tarvizo/nes-controller.html
#if defined(NES) || defined(SNES)

#define CLOCK1 inputPinsPort1[0]
#define LATCH1 inputPinsPort1[1]
#define DATA1 inputPinsPort1[2]

#define CLOCK2 inputPinsPort2[0]
#define LATCH2 inputPinsPort2[1]
#define DATA2 inputPinsPort2[2]

#ifdef NES
#define BITS 8
#else
#define BITS 16
#endif

#define EVENTS_TOTAL BITS

void setupJoysticks() {
  pinMode(LATCH1, OUTPUT);
  pinMode(CLOCK1, OUTPUT);
  pinMode(DATA1, INPUT_PULLUP);
  pinMode(LATCH2, OUTPUT);
  pinMode(CLOCK2, OUTPUT);
  pinMode(DATA2, INPUT_PULLUP);
}

#define latchlow digitalWrite(LATCH1, LOW); digitalWrite(LATCH2, LOW);
#define latchhigh digitalWrite(LATCH1, HIGH); digitalWrite(LATCH2, HIGH)
#define clocklow digitalWrite(CLOCK1, LOW); digitalWrite(CLOCK2, LOW)
#define clockhigh digitalWrite(CLOCK1, HIGH); digitalWrite(CLOCK2, HIGH)
#define wait delayMicroseconds(12)


void readJoysticks() {
  latchlow;
  clocklow;
  latchhigh;
  wait;
  latchlow;

  for (int i = 0; i < BITS; i++) {
    newStatusPort1[i] = digitalRead(DATA1);
    newStatusPort2[i] = digitalRead(DATA2);
    clockhigh;
    wait;
    clocklow;
    wait;
  }
}

void interpretJoystickState(uint8_t j, uint8_t *status) {
  Joystick[j].setYAxis(0);
  Joystick[j].setXAxis(0);
  if (!status[4]) Joystick[j].setYAxis(-127); //UP
  if (!status[5]) Joystick[j].setYAxis(127); //DOWN
  if (!status[6]) Joystick[j].setXAxis(-127); //LEFT
  if (!status[7]) Joystick[j].setXAxis(127); //RIGHT
  #ifdef NES
  Joystick[j].setButton(0, !status[3]); //BUTTON1 (Start)  
  Joystick[j].setButton(1, !status[2]); //BUTTON2 (Select)
  Joystick[j].setButton(2, !status[0]); //BUTTON3 (A)
  Joystick[j].setButton(3, !status[1]); //BUTTON4 (B)
  #else
  Joystick[j].setButton(0, !status[3]); //BUTTON1 (Start)  
  Joystick[j].setButton(1, !status[2]); //BUTTON2 (Select)
  Joystick[j].setButton(2, !status[8]); //BUTTON3 (A)
  Joystick[j].setButton(3, !status[0]); //BUTTON4 (B)
  Joystick[j].setButton(4, !status[9]); //BUTTON5 (X)
  Joystick[j].setButton(5, !status[1]); //BUTTON6 (Y)
  Joystick[j].setButton(6, !status[10]); //BUTTON7 (L1) ("LB")
  Joystick[j].setButton(7, !status[11]); //BUTTON8 (R1) ("RB")
  #endif
}

#endif


void setup() {
  //clear statusarrays (1=OFF, 0=ON)
  for (uint8_t i = 0; i < EVENTS_TOTAL; i++) {
    lastStatusPort1[i] = 1;
    newStatusPort1[i] = 1;
    lastStatusPort2[i] = 1;
    newStatusPort2[i] = 1;
  }
  
  setupJoysticks();

  Joystick[0].begin(false);
  Joystick[1].begin(false);
}


uint8_t inputChangedP1 = 0;
uint8_t inputChangedP2 = 0;


void loop() {

  readJoysticks();

  //check for changes - do not raise a flag if nothing changes
  for (uint8_t i=0; i < EVENTS_TOTAL; i++) {
    if (newStatusPort1[i] != lastStatusPort1[i]) {
      lastStatusPort1[i] = newStatusPort1[i]; 
      inputChangedP1 = 1;
    }
    if (newStatusPort2[i] != lastStatusPort2[i]) {
      lastStatusPort2[i] = newStatusPort2[i]; 
      inputChangedP2 = 1;
    }
  }
  
  if (inputChangedP1) interpretJoystickState(0, newStatusPort1);
  if (inputChangedP2) interpretJoystickState(1, newStatusPort2);

  //minimize port1 time advantage - try to send both states as simultaneous as possible
  if (inputChangedP1) Joystick[0].sendState();
  if (inputChangedP2) Joystick[1].sendState();
  inputChangedP1 = 0;
  inputChangedP2 = 0;

}
