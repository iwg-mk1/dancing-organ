//DUOPHONIC using split keyboard
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>
#include "Adafruit_Crickit.h"
#include "seesaw_motor.h"

Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);
Adafruit_Crickit crickit;
seesaw_Motor motor_b(&crickit);
seesaw_Motor motor_s(&crickit);

//           note, voltage
float noteMap[256]; 

void setNoteMap() {
  for (int i = 0; i < 256; i++) {
    noteMap[i] = 1.5 + 4 * (i / 256.0);
  }
}



void setup() {
  Serial.begin(115200);
  
  if(!crickit.begin()){
    Serial.println("ERROR!");
    while(1) delay(1);
  }
  else Serial.println("Crickit started");

  MIDI.begin(1);
  MIDI.setHandleNoteOn(handleNoteOn);
  //MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.setHandleControlChange(handleControlChange);


  motor_b.attach(CRICKIT_MOTOR_A1, CRICKIT_MOTOR_A2);
  motor_s.attach(CRICKIT_MOTOR_B1, CRICKIT_MOTOR_B2);

  setNoteMap();
}



float voltageBig = 0;
float voltageSmall = 0;
byte curNoteBig = 0;
byte curNoteSmall = 0;
byte offsetBig = 0;
byte offsetSmall = 0;
byte keySplit = 60; //C4 (middle C)

void loop() {
  MIDI.read();
  motor_b.throttle(voltageBig);
  motor_s.throttle(voltageSmall);
}

//take note, match it with fundamental frequency
void handleNoteOn(byte channel, byte note, byte velocity) {
  if (note < 60) {
    curNoteBig = note;
    voltageBig = noteMap[note];
  } else {
    curNoteBig = note;
    voltageBig = noteMap[note];
  }
}

void handleNoteOff(byte channel, byte note, byte velocity) {
  if(note == curNoteBig) {
    curNoteBig = 0; //replace this
    //Add signal to relay mute switch
  } else if (note == curNoteSmall) {
    curNoteSmall = 0; //replace this
    //Add signal to relay mute switch
  }
}


void handleControlChange(byte channel, byte number, byte value) {
  switch(number) {
    case 1: //Modulation wheel
      break;
  }
}

