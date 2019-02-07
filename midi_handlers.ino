void processMIDIusb(void) {
  byte type, channel, data1, data2, cable;
  int found = 0;
  int found_pos;

  type = usbMIDI.getType();       // which MIDI message, 128-255
  // channel = usbMIDI.getChannel(); // which MIDI channel, 1-16
  data1 = usbMIDI.getData1();     // first data byte of message, 0-127
  // data2 = usbMIDI.getData2();     // second data byte of message, 0-127

  switch (type) {
    case usbMIDI.NoteOff: // 0x80
      //a note is released. check if it is in the note memory
      for (int i = 0; i <= memory_index; i++) {
        if (data1 == note_memory[i]) {

          found = 1;
          found_pos = i;
          continue;
        }
      }
      if (found == 0) {
        // if it isn't already held do nothing.
        break;
      }
      else if (found == 1) {
        //the note was held. if it was the last one played, update pitch and retrigger envelope. if note, remove it
        //from the note stack and do nothing.
        if (found_pos == memory_index) {
          if (memory_index > 0) {
            memory_index--;
            Pitch.update_target(note_memory[memory_index]);
            output_retrigger();
            envelope.retrigger_envelope();
          }
          else {
            //no more notes held. set gate to 0
            memory_index--;
            output_gate(0);
            envelope.gate_envelope(0);
          }
        }
        else {
          shift_memory(found_pos);
        }
      }
      break;

    case usbMIDI.NoteOn: // 0x90
      //a note is pressed. we will search for it in the note_memory
      found = 0;
      for (int i = 0; i <= memory_index; i++) {
        if (data1 == note_memory[i]) {
          // the note is already pressed down. do nothing.
          found = 1;
          continue;
        }
      }
      if (found == 0) {
        //the note is not pressed. Add it in the note_memory stack and output the appropriate pitch signal
        if (memory_index < MEMORY_LENGTH - 1) {
          memory_index++;
          note_memory[memory_index] = data1;
          Pitch.update_target(data1);
        }
        else {
          shift_memory(0);
          note_memory[memory_index] = data1;

          Pitch.update_target(data1);
        }
      }
      //if another note was already pressed, output retrigger signal and retrigger internal envelope.
      if (memory_index > 0) {
        output_retrigger();
        envelope.retrigger_envelope();
      }
      //if no note was previously held, set gate to high and update gate status for the internal envelope.
      else {
        output_gate(1);
        envelope.gate_envelope(1);
      }
      break;
  }
}

void shift_memory(int index) {
  for (int i = index; i < memory_index; i++) {
    note_memory[i] = note_memory[i + 1];
  }
  memory_index--;
}
