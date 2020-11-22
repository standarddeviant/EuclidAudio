#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "audio_objects.h"

// GUItool: begin automatically generated code
AudioSynthSimpleDrum     drumKick;       //xy=227,104
AudioSynthSimpleDrum     drumSnare;      //xy=228,145
AudioSynthSimpleDrum     drumHiHat;      //xy=230,187
AudioSynthKarplusStrong  string1;        //xy=229,355
AudioSynthToneSweep      tonesweep1;     //xy=235,472
AudioSynthWaveform       waveform1;      //xy=236,410
AudioMixer4              mixerDrum;      //xy=501,113
AudioMixer4              mixerMelody;    //xy=518,359
AudioMixer4              mixerL;         //xy=721,216
AudioMixer4              mixerR;         //xy=726,304
AudioOutputI2S           i2s1;           //xy=869,268
AudioConnection          patchCord1(drumKick, 0, mixerDrum, 0);
AudioConnection          patchCord2(drumSnare, 0, mixerDrum, 1);
AudioConnection          patchCord3(string1, 0, mixerMelody, 0);
AudioConnection          patchCord4(drumHiHat, 0, mixerDrum, 2);
AudioConnection          patchCord5(tonesweep1, 0, mixerMelody, 2);
AudioConnection          patchCord6(waveform1, 0, mixerMelody, 1);
AudioConnection          patchCord7(mixerDrum, 0, mixerL, 0);
AudioConnection          patchCord8(mixerDrum, 0, mixerR, 0);
AudioConnection          patchCord9(mixerMelody, 0, mixerL, 1);
AudioConnection          patchCord10(mixerMelody, 0, mixerR, 1);
AudioConnection          patchCord11(mixerL, 0, i2s1, 0);
AudioConnection          patchCord12(mixerR, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=517,570
// GUItool: end automatically generated code

eubit_seq_t eubitKick;
eubit_seq_t eubitSnare;
eubit_seq_t eubitHiHat;

void setup_audio_objects(void) {
    AudioMemory(18);

    // set initial volume to -12dB
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.5f);

    // drum setup
    drumKick.frequency(45.0f);
    drumKick.length(300);
    drumKick.secondMix(0.3f);
    drumKick.pitchMod(0.7f);
    eubit_init(&eubitKick, 32, 13);

    drumSnare.frequency(300.0f);
    drumSnare.length(500);
    drumSnare.secondMix(0.8f);
    drumSnare.pitchMod(0.1f);
    eubit_init(&eubitSnare, 32, 5);

    drumHiHat.frequency(800.0f);
    drumHiHat.length(50);
    drumHiHat.secondMix(0.7f);
    drumHiHat.pitchMod(0.5f);
    eubit_init(&eubitHiHat, 32, 9);

    mixerDrum.gain(0, 1.000f);
    mixerDrum.gain(1, 0.707f);
    mixerDrum.gain(2, 0.500f);
}
