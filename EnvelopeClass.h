//The ADSR class creatres an envelope object that holds the A, D, S, R values and updates the output value at regular
//intervals. The envelope is controlled by gate_envelope(state). State = 1 signifies a held note and state = 0 signifies
//a note release. Note priority should be handled by the program that uses the class. Envelope is retriggered by calling
//retrigger_envelope()

class ADSR {
  public:
    void initial() {
      time_constant[0] = 100;
      time_constant[1] = 100;
      time_constant[2] = 1;
      time_constant[3] = 100;
      gate = 0;
      state = 3;
      env_value = 0;

      tolerance[0] = 500;
      tolerance[1] = 10;
      tolerance[2] = 2 * tolerance[1];
      tolerance[3] = 2 * tolerance[1];
      targets[0] = MAX_ENV + tolerance[0];
      targets[1] = 4 * 500;
      targets[2] = 4 * 500;
      targets[3] = 0;
    }

//update the A, D, S, R constants. Use exp() for better potentiometer feel when using linear pots. Replace with log pots
//to ditch the exp(). Minimum value of time constants should be around 1 - there is no max limit.
    void control_update(float Att, float Dec, float Sus, float Rel) {
      time_constant[0] = 500 * (exp((Att) / 256) - 1);
      time_constant[1] = 1000 * (exp((Dec) / 256) - 1);
      time_constant[3] = 1000 * (exp((Rel) / 256) - 1);
//      targets[2] = 76.4 * (exp((Sus) / 256) - 1);;
targets[2] = 4*Sus;
      targets[1] = targets[2];
    }
    
    void gate_envelope(int gate) {
      this->gate = gate;
    }
    
    void retrigger_envelope() {
      state = 0;
    }

//to be called at regular intervals. updates the envelope state, calculates and outputs the next voltage point.
    void env_update() {
      if (gate == 1) {
        if (state == 3) {
          state = 0;
        }
      }
      else {
        state = 3;
      }

      env_value = env_value + (targets[state] - env_value) / (time_constant[state] + 1) ;

      if (abs(env_value - targets[state]) < tolerance[state]) {
        if (state < 2) {
          state++;
        }
      }
      analogWrite(ENVELOPE, (int)env_value);
    }
  private:
    int gate;
    int state;
    float env_value;
    float time_constant[4];
    float targets[4];
    int tolerance[4];
};
