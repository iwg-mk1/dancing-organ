#include <USB-MIDI.h>

USBMIDI_CREATE_DEFAULT_INSTANCE();
Adafruit_Crickit crickit;
seesaw_Motor motor_m(&crickit);

void setup() {
  Serial.begin(115200);
  
  if(!crickit.begin()){
    Serial.println("ERROR!");
    while(1) delay(1);
  }
  else Serial.println("Crickit started");

  MIDI.begin(1);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleControlChange(handleControlChange);
}

//           note, voltage
unordered_map<int, float> noteMap;
float voltage = 0;
byte curNote = 0;

void loop() {
  MIDI.read();
  motor_m.throttle(voltage);
  if (CircuitPlayground.leftButton()) createNoteMap();
}

//Currently set for calibration. eventually it should take note, match it with fundamental frequency
void handleNoteOn(byte channel, byte note, byte velocity) {
  curNote = note;
  /*
  voltage = noteMap(note);
  */
}


void handleControlChange(byte channel, byte number, byte value) {
  switch(number) {
    case 1:
      voltage = (6.0/127.0) * value; //Voltage between 0 and 6 volts, might set to 1.5-6v later
      break;
  }
}
//Helper to create note map
void createNoteMap() {
  Serial.print("noteMap[\"" + note +   "\"] = " + voltage + ";");
}

