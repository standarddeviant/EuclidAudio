#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "audio_objects.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthSimpleDrum     drumKick;          //xy=134,80
AudioSynthSimpleDrum     drumSnare;          //xy=134,135
AudioSynthSimpleDrum     drumHiHat;          //xy=138,180
AudioSynthKarplusStrong  string1;        //xy=171,265
AudioSynthToneSweep      tonesweep1;     //xy=177,382
AudioSynthWaveform       waveform1;      //xy=178,320
AudioEffectBitcrusher    bitcrusher1;    //xy=293,134
AudioMixer4              mixerDrum;         //xy=473,142
AudioMixer4              mixerMelody;         //xy=488,298
AudioMixer4              mixerL;         //xy=718,178
AudioMixer4              mixerR;         //xy=723,266
AudioOutputI2S           i2s1;           //xy=1028,207
AudioConnection          patchCord1(drumKick, 0, mixerDrum, 0);
AudioConnection          patchCord2(drumSnare, bitcrusher1);
AudioConnection          patchCord3(drumHiHat, 0, mixerDrum, 3);
AudioConnection          patchCord4(string1, 0, mixerMelody, 0);
AudioConnection          patchCord5(tonesweep1, 0, mixerMelody, 2);
AudioConnection          patchCord6(waveform1, 0, mixerMelody, 1);
AudioConnection          patchCord7(bitcrusher1, 0, mixerDrum, 1);
AudioConnection          patchCord8(mixerDrum, 0, mixerL, 0);
AudioConnection          patchCord9(mixerDrum, 0, mixerR, 0);
AudioConnection          patchCord10(mixerMelody, 0, mixerR, 1);
AudioConnection          patchCord11(mixerMelody, 0, mixerL, 1);
AudioConnection          patchCord12(mixerL, 0, i2s1, 0);
AudioConnection          patchCord13(mixerR, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=459,379
// GUItool: end automatically generated code





eubit_seq_t eubitKick;
eubit_seq_t eubitSnare;
eubit_seq_t eubitHiHat;
eubit_seq_t eubitString;

#define DELAY_LINE_NSAMP (AUDIO_BLOCK_SAMPLES*4)
short delayLineL[AUDIO_BLOCK_SAMPLES] = {0};
short delayLineR[AUDIO_BLOCK_SAMPLES] = {0};

void setup_audio_objects(void) {
    AudioMemory(18);

    // set initial volume to -12dB
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.5f);

    // drum setup
    drumKick.frequency(55.0f);
    drumKick.length(200);
    drumKick.secondMix(0.3f);
    drumKick.pitchMod(0.6f);
    eubit_init(&eubitKick, 64, 13);

    drumSnare.frequency(300.0f);
    drumSnare.length(80);
    drumSnare.secondMix(0.3f);
    drumSnare.pitchMod(0.45f);
    bitcrusher1.bits(8);
    bitcrusher1.sampleRate(1500.0f);
    eubit_init(&eubitSnare, 32, 5);

    drumHiHat.frequency(800.0f);
    drumHiHat.length(50);
    drumHiHat.secondMix(0.7f);
    drumHiHat.pitchMod(0.5f);
    eubit_init(&eubitHiHat, 64, 15);

    mixerDrum.gain(0, 1.000f);
    mixerDrum.gain(1, 0.500f);
    mixerDrum.gain(2, 0.400f);

    eubit_init(&eubitString, 24, 7);
    mixerMelody.gain(0, 0.1);

    // chorusL.begin(delayLineL, DELAY_LINE_NSAMP, 4);
    // chorusR.begin(delayLineL, DELAY_LINE_NSAMP, 4);
}
