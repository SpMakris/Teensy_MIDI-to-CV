//The PitchCV class realises smooth value transition for pitch CV. The value is updated at the speed set by glide_time.
//Calling update_target(note) will make the output glide towards that note. The variable "note" refers to one of the 128
//midi notes.
class PitchCV {
  public:

    float target_pitch;
    float current_pitch;
    float glide_time;
    float tolerance;
    void initial() {
      target_pitch = 60;
      current_pitch = 60;
      glide_time = 1;
      tolerance = 10;
    }
    void update_target(int note){
      target_pitch=note*VoltageScale;
    }
//update glide time constant. exp() gives better feel for linear potentiometers. Use log potentiometers to get rid of
//the exp() function.
    void update_glide(float glidetime) {
      glide_time =100 * (exp((glidetime) / 256) - 1); 
    }

//to be called at regular intervals.   
    void control_update() {

      current_pitch = current_pitch + (target_pitch - current_pitch) / (glide_time + 1) ;

      analogWrite(DAC, (int)current_pitch);
    }
};
