
#define MEMORY_LENGTH 4 //number of pressed notes remembered

#define VoltageScale 32 // Dac voltage scale. 1V/oct, about 2.5 external analog gain
#define DAC 26 //dac pin
#define ENVELOPE 17//env pin
#define GATE 3//gate pin
#define VELOCITY 16//velocity pin
#define RETRIGGER 2//retrigger pin
#define MAX_ENV 4096 //max envelope number
#define ATTACK 14//attack pot pin
#define DECAY 18//decay pot pin
#define SUSTAIN 19//sustain pot pin
#define RELEASE 21//release pot pin
#define GLIDE 15//glide pot pin
IntervalTimer RetriggerTimer; //retrigger pulse timer
IntervalTimer VTimer; //voltage update timer

int note_memory[MEMORY_LENGTH];
int memory_index;
