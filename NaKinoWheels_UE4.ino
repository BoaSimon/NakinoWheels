
// ----- VARIABLES -----
// Rotary Encoder Variables
float pulsesX, XA_SIG=0, XB_SIG=1, pulsesY, YA_SIG=0, YB_SIG=1, xSpd=0, ySpd=0, xPotRaw=0, yPotRaw=0;

//Smoothing Variables
const int numReadings = 1;
float pReadings[numReadings];      // the readings from the analog input
int pReadIndex = 0;              // the index of the current reading
float pTotal = 0;                  // the running total
float pAverage = 0;                // the average
float tReadings[numReadings];      // the readings from the analog input
int tReadIndex = 0;              // the index of the current reading
float tTotal = 0;                  // the running total
float tAverage = 0;                // the average

// Adjust these variables as needed
int xPotPin = 1;
int yPotPin = 0;
float SpdMult = 0.05;


// ----- SETUP -----
void setup(){
//Rotary Encoder Setup
attachInterrupt(0, XA_RISE, RISING); // Pin 2
attachInterrupt(1, XB_RISE, RISING); // Pin 3
attachInterrupt(4, YA_RISE, RISING); // Pin 19
attachInterrupt(5, YB_RISE, RISING); // Pin 18

//Serial Output Setup
Serial.begin(115200);
delay(100);
Serial.print("Connected");

//Smoothing Setup
   for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    pReadings[thisReading] = 0;
   }
   for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    tReadings[thisReading] = 0;
  }
}

// ----- ROTARY ENCODER INTERRUPTS -----
//X-Axis
void XA_RISE(){
detachInterrupt(0);
//delay(1);
XA_SIG=1;

if(XB_SIG==0)
pulsesX = pulsesX + xSpd;//moving forward
if(XB_SIG==1)
pulsesX = pulsesX - xSpd;//moving reverse

attachInterrupt(0, XA_FALL, FALLING);
}

void XA_FALL(){
detachInterrupt(0);
//delay(1);
XA_SIG=0;

if(XB_SIG==1)
pulsesX = pulsesX + xSpd;//moving forward
if(XB_SIG==0)
pulsesX = pulsesX - xSpd;//moving reverse

attachInterrupt(0, XA_RISE, RISING);
}

void XB_RISE(){
detachInterrupt(1);
//delay(1);
XB_SIG=1;

if(XA_SIG==1)
pulsesX = pulsesX + xSpd;//moving forward
if(XA_SIG==0)
pulsesX = pulsesX - xSpd;//moving reverse

attachInterrupt(1, XB_FALL, FALLING);
}

void XB_FALL(){
detachInterrupt(1);
//delay(1);
XB_SIG=0;

if(XA_SIG==0)
pulsesX = pulsesX + xSpd;//moving forward
if(XA_SIG==1)
pulsesX = pulsesX - xSpd;//moving reverse

attachInterrupt(1, XB_RISE, RISING);
}

//Y-Axis
void YA_RISE(){
detachInterrupt(4);
//delay(1);
YA_SIG=1;

if(YB_SIG==0)
pulsesY = pulsesY + ySpd;//moving forward
pulsesY = constrain(pulsesY, -89.99, 89.99);
if(YB_SIG==1)
pulsesY = pulsesY - ySpd;//moving reverse
pulsesY = constrain(pulsesY, -89.99, 89.99);

attachInterrupt(4, YA_FALL, FALLING);
}

void YA_FALL(){
detachInterrupt(4);
//delay(1);
YA_SIG=0;

if(YB_SIG==1)
pulsesY = pulsesY + ySpd;//moving forward
pulsesY = constrain(pulsesY, -89.99, 89.99);
if(YB_SIG==0)
pulsesY = pulsesY - ySpd;//moving reverse
pulsesY = constrain(pulsesY, -89.99, 89.99);

attachInterrupt(4, YA_RISE, RISING);
}

void YB_RISE(){
detachInterrupt(5);
//delay(1);
YB_SIG=1;

if(YA_SIG==1)
pulsesY = pulsesY + ySpd;//moving forward
pulsesY = constrain(pulsesY, -89.99, 89.99);
if(YA_SIG==0)
pulsesY = pulsesY - ySpd;//moving reverse
pulsesY = constrain(pulsesY, -89.99, 89.99);

attachInterrupt(5, YB_FALL, FALLING);
}

void YB_FALL(){
detachInterrupt(5);
//delay(1);
YB_SIG=0;

if(YA_SIG==0)
pulsesY = pulsesY + ySpd;//moving forward
pulsesY = constrain(pulsesY, -89.99, 89.99);
if(YA_SIG==1)
pulsesY = pulsesY - ySpd;//moving reverse
pulsesY = constrain(pulsesY, -89.99, 89.99);

attachInterrupt(5, YB_RISE, RISING);
}

// ----- LOOP -----
void loop(){
//Update Potentiometers
xPotRaw = analogRead(xPotPin);
yPotRaw = analogRead(yPotPin);
xSpd = SpdMult * (xPotRaw / 1018);
ySpd = SpdMult * (yPotRaw / 1018);


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

//Serial Output
Serial.print("p");
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
}
