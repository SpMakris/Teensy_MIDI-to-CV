#include <MCPDAC.h>
#include <math.h>
#include <MIDI.h>
#include "GlobalVariables.h"
#include "EnvelopeClass.h"
#include "CVClass.h"


ADSR envelope;
PitchCV Pitch;
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, serialMIDI);

void setup() {

  analogWriteFrequency(17, 100000);
  analogWriteResolution(12);

  Serial.begin(38400);
  serialMIDI.begin(MIDI_CHANNEL_OMNI);

  Pitch.initial();
  envelope.initial();


  pinMode(GATE, OUTPUT);
  pinMode(GLIDE, INPUT);
  pinMode(ATTACK, INPUT);
  pinMode(DECAY, INPUT);
  pinMode(SUSTAIN, INPUT);
  pinMode(RELEASE, INPUT);
  pinMode(RETRIGGER, OUTPUT);

  memory_index = -1;
//run voltage update routines every 50us. Can be increased to 500-1000us.
  VTimer.begin(Vupdate, 100);
}

void loop() {
  if (usbMIDI.read()) {
    processMIDIusb();
  }
  
  //  else if (serialMIDI.read()) {
  //    processMIDIserial();
  //  }
  
  else {
    controls_read();

  }
}
