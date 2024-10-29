//DUOPHONIC using split keyboard
#include <Adafruit_TinyUSB.h>
#include "Adafruit_Crickit.h"
#include "seesaw_motor.h"
#include <Adafruit_CircuitPlayground.h>


Adafruit_Crickit crickit;
seesaw_Motor motor_a(&crickit);
seesaw_Motor motor_b(&crickit);


void setup() {
  Serial.begin(115200);

  CircuitPlayground.begin();

  if(!crickit.begin()){
    Serial.println("ERROR!");
    while(1) delay(1);
  }
  else Serial.println("Crickit started");

  pinMode(CRICKIT_SIGNAL1, INPUT);  
  pinMode(CRICKIT_SIGNAL2, INPUT);  
  motor_a.attach(CRICKIT_MOTOR_A1, CRICKIT_MOTOR_A2);
  motor_b.attach(CRICKIT_MOTOR_B1, CRICKIT_MOTOR_B2);

}

float voltageBig = 0;
float voltageSmall = 0;


void loop() {
  CircuitPlayground.setPixelColor(0, 0, 0, 200);
  /*if(analogRead(CRICKIT_SIGNAL1) < 600) {
    CircuitPlayground.setPixelColor(1, 0, 0, 200);
  } else if (analogRead(CRICKIT_SIGNAL1) < 1020) {
    CircuitPlayground.setPixelColor(2, 1, 0, 200);
  } else CircuitPlayground.setPixelColor(3, 1, 0, 200);*/
  //voltageBig = analogRead(CRICKIT_SIGNAL1) / 1024.0;
  //voltageSmall = analogRead(CRICKIT_SIGNAL1) / 1024.0;
  //motor_a.throttle(voltageBig);
  //motor_b.throttle(voltageSmall);
  if (CircuitPlayground.slideSwitch()) {
    motor_a.throttle((float) crickit.analogRead(CRICKIT_SIGNAL1) / 1024.0);
    motor_b.throttle((float) crickit.analogRead(CRICKIT_SIGNAL2) / 1024.0);
  } else {
    motor_a.throttle(0);
    motor_b.throttle(0);
  }
  
}
