#include <MD_REncoder.h>

// ----- VARIABLES -----
// PPM Variables
unsigned int ppm[16]; // the array of values for the timer1 interrupt timings
int curPpm = 0; // the position in the array of timings
byte curPpmMax; // the actual number of timer steps
byte loopCount = 0; // a crude substitute for delay()

//Rotary Encoder Variables
float pulsesX=305, XA_SIG=0, XB_SIG=1, pulsesY=305, YA_SIG=0, YB_SIG=1, xSpd=0, ySpd=0, xpotTest, ypotTest;

//Adjust these variables as needed
char pulsePin = 9; // the digital pin for sending PPM pulses to the transmitter
int xPotPin = 1;
int yPotPin = 0;
float xPotRaw = 0;
float yPotRaw = 0;
float SpdMult = 0.05;

//Smoothing Variables
const int numReadings = 6;

float pReadings[numReadings];      // the readings from the analog input
int pReadIndex = 0;              // the index of the current reading
float pTotal = 1830;                  // the running total
float pAverage = 305;                // the average
float tReadings[numReadings];      // the readings from the analog input
int tReadIndex = 0;              // the index of the current reading
float tTotal = 1830;                  // the running total
float tAverage = 305;                // the average


// ----- SETUP -----
void setup(){
//Rotary Encoder Setup
attachInterrupt(0, XA_RISE, RISING); // Pin 2
attachInterrupt(1, XB_RISE, RISING); // Pin 3
attachInterrupt(4, YA_RISE, RISING); // Pin 19
attachInterrupt(5, YB_RISE, RISING); // Pin 18

// Serial Output Setup
Serial.begin(115200);
delay(100);
Serial.print("Connected");


// PPM Setup
//set the pin directions
pinMode(pulsePin, OUTPUT);
// set the timing values
  ppm[0] = 1475; //3775; // long pulse - see notes above
  ppm[1] = 75; // short dividing pulse
  ppm[2] = 305; // loco1 ch1
  ppm[3] = 75; // short
  ppm[4] = 305; // loco2 ch2
  ppm[5] = 75; // short
  ppm[6] = 305; // loco3 ch3
  ppm[7] = 75; // short
  ppm[8] = 305; // loco4 ch4
  ppm[9] = 75; // short
  ppm[10] = 305; // loco5 ch5
  ppm[11] = 75; // short
  ppm[12] = 305; // loco6 ch6
  ppm[13] = 75; // short
  ppm[14] = 400; // loco7 ch7
  ppm[15] = 75; // short

  curPpmMax = 16; // the number of timer values
  curPpm = 0; // the starting position in the array of timings
  
  // setup and start timer interrupts
  // ppm is achieved by sending different delays to the timer interrupt
  noInterrupts();
    TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B
    // set compare match register to desired timer count:
    OCR1A = 1000; // It works by causing an interrupt when TCNT2 counts up to this number
                  // This number will be set from the ppm array when the program is running
    digitalWrite(pulsePin,0); // start with pin low
    // turn on CTC mode: Clear Timer on Compare
    bitSet(TCCR1B, WGM12);
    // Set CS10 and CS11 bits for 64 prescaler: 10, 12 = 1024
    bitSet(TCCR1B, CS10);
    bitSet(TCCR1B, CS11);
    bitClear(TCCR1B, CS12);
    // enable timer compare A interrupt:
    bitSet(TIMSK1, OCIE1A);
  interrupts();


   for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    pReadings[thisReading] = 305;
   }
   for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    tReadings[thisReading] = 305;
  }
  
}

// ----- ROTARY ENCODER SETUP -----

//X-Axis
void XA_RISE(){
detachInterrupt(0);
//delay(1);
XA_SIG=1;

if(XB_SIG==0)
pulsesX = pulsesX + xSpd;//moving forward
pulsesX = constrain(pulsesX, 100, 500);
if(XB_SIG==1)
pulsesX = pulsesX - xSpd;//moving reverse
pulsesX = constrain(pulsesX, 100, 500);

attachInterrupt(0, XA_FALL, FALLING);
}

void XA_FALL(){
detachInterrupt(0);
//delay(1);
XA_SIG=0;

if(XB_SIG==1)
pulsesX = pulsesX + xSpd;//moving forward
pulsesX = constrain(pulsesX, 100, 500);
if(XB_SIG==0)
pulsesX = pulsesX - xSpd;//moving reverse
pulsesX = constrain(pulsesX, 100, 500);

attachInterrupt(0, XA_RISE, RISING);
}

void XB_RISE(){
detachInterrupt(1);
//delay(1);
XB_SIG=1;

if(XA_SIG==1)
pulsesX = pulsesX + xSpd;//moving forward
pulsesX = constrain(pulsesX, 100, 500);
if(XA_SIG==0)
pulsesX = pulsesX - xSpd;//moving reverse
pulsesX = constrain(pulsesX, 100, 500);

attachInterrupt(1, XB_FALL, FALLING);
}

void XB_FALL(){
detachInterrupt(1);
//delay(1);
XB_SIG=0;

if(XA_SIG==0)
pulsesX = pulsesX + xSpd;//moving forward
 pulsesX = constrain(pulsesX, 100, 500);
if(XA_SIG==1)
pulsesX = pulsesX - xSpd;//moving reverse
pulsesX = constrain(pulsesX, 100, 500);

attachInterrupt(1, XB_RISE, RISING);
}

//Y-Axis
void YA_RISE(){
detachInterrupt(4);
//delay(1);
YA_SIG=1;

if(YB_SIG==0)
pulsesY = pulsesY + ySpd;//moving forward
 pulsesY = constrain(pulsesY, 100, 500);
if(YB_SIG==1)
pulsesY = pulsesY - ySpd;//moving reverse
 pulsesY = constrain(pulsesY, 100, 500);

attachInterrupt(4, YA_FALL, FALLING);
}

void YA_FALL(){
detachInterrupt(4);
//delay(1);
YA_SIG=0;

if(YB_SIG==1)
pulsesY = pulsesY + ySpd;//moving forward
 pulsesY = constrain(pulsesY, 100, 500);
if(YB_SIG==0)
pulsesY = pulsesY - ySpd;//moving reverse
 pulsesY = constrain(pulsesY, 100, 500);

attachInterrupt(4, YA_RISE, RISING);
}

void YB_RISE(){
detachInterrupt(5);
//delay(1);
YB_SIG=1;

if(YA_SIG==1)
pulsesY = pulsesY + ySpd;//moving forward
 pulsesY = constrain(pulsesY, 100, 500);
if(YA_SIG==0)
pulsesY = pulsesY - ySpd;//moving reverse
 pulsesY = constrain(pulsesY, 100, 500);

attachInterrupt(5, YB_FALL, FALLING);
}

void YB_FALL(){
detachInterrupt(5);
//delay(1);
YB_SIG=0;

if(YA_SIG==0)
pulsesY = pulsesY + ySpd;//moving forward
 pulsesY = constrain(pulsesY, 100, 500);
if(YA_SIG==1)
pulsesY = pulsesY - ySpd;//moving reverse
 pulsesY = constrain(pulsesY, 100, 500);

attachInterrupt(5, YB_RISE, RISING);
}



// ----- LOOP -----
void loop(){
xPotRaw = analogRead(xPotPin);
yPotRaw = analogRead(yPotPin);
xSpd = SpdMult * (xPotRaw / 1018);
ySpd = SpdMult * (yPotRaw / 1018);

if (loopCount == 1) {

  //Smoothing
// subtract the last reading:
pTotal = pTotal - pReadings[pReadIndex];
 // read from the sensor:
  pReadings[pReadIndex] = pulsesX;
  // add the reading to the total:
  pTotal = pTotal + pReadings[pReadIndex];
  // advance to the next position in the array:
  pReadIndex = pReadIndex + 1;

  // if we're at the end of the array...
  if (pReadIndex >= numReadings) {
    // ...wrap around to the beginning:
    pReadIndex = 0;
  }

  // calculate the average:
  pAverage = pTotal / numReadings;

 // subtract the last reading:
tTotal = tTotal - tReadings[tReadIndex];
 // read from the sensor:
  tReadings[tReadIndex] = pulsesY;
  // add the reading to the total:
  tTotal = tTotal + tReadings[tReadIndex];
  // advance to the next position in the array:
  tReadIndex = tReadIndex + 1;

  // if we're at the end of the array...
  if (tReadIndex >= numReadings) {
    // ...wrap around to the beginning:
    tReadIndex = 0;
  }

  // calculate the average:
  tAverage = tTotal / numReadings;
  
    // the reading must be converted from the range 0 - 1023 to the range 250 - 500
    //   which means dividing by 4 and adding 180 to give 305 at the centre
    //pulsesX = constrain(pulsesX, 250, 500);
    //pulsesY = constrain(pulsesY, 250, 500);
    
   
    //xpotTest = constrain(xPotRaw, 100, 500);
    //ypotTest = constrain(yPotRaw, 100, 500);
    ppm[4] = pAverage;       
    ppm[6] = tAverage;
    //Serial.print(pulsesX);
    Serial.println(pAverage);
  }

  loopCount = loopCount + 1; // it will roll over to zero automatically

/*Serial.print("p");
Serial.print(pulsesX);
Serial.print("t");
Serial.print(pulsesY);
Serial.println(",");
//Serial.print("panSpeed");
//Serial.print(xSpd);
//Serial.print("tiltSpeed");
//Serial.print(ySpd);
//Serial.println("end");
delay(60);
*/

}


// interrupt routine that is triggered when the timer counts up to the preset value
ISR(TIMER1_COMPA_vect) {
  noInterrupts();
    digitalWrite(pulsePin, !digitalRead(pulsePin)); // change the state of the pin
    OCR1A = ppm[curPpm]; // set the value for the next time interval
    curPpm = ((curPpm + 1) % curPpmMax); // move the index on
                                         // the modulus operator makes the index roll over to the start
  interrupts();
}
