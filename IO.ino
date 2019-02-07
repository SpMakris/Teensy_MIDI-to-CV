//voltage update routine calls. to be called at regular intervals.
void Vupdate() {
  envelope.env_update();
  Pitch.control_update();

}

//get control readings and update time constants
void controls_read() {
  float Attack = analogRead(ATTACK);

  float Decay = analogRead(DECAY);

  float sus = analogRead(SUSTAIN);

  float Release = analogRead(RELEASE);
  float glidetime = 1024 - analogRead(GLIDE);
  Pitch.update_glide(glidetime);
  envelope.control_update(Attack, Decay, sus, Release);
}

//gate output
void output_gate(int state) {
  if (state == 1) {
    digitalWrite(GATE, HIGH);
  }
  else if (state == 0) {
    digitalWrite(GATE, LOW);
  }
}

//retrigger output
void output_retrigger() {
  digitalWrite(RETRIGGER, HIGH);
  RetriggerTimer.begin(trigoff, 1000);
}

void trigoff() {
  digitalWrite(RETRIGGER, LOW);
  RetriggerTimer.end();
}
