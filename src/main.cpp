#include <Arduino.h>
#include <IntervalTimer.h>

#include "audio_objects.h"

IntervalTimer g_euc_metronome;
volatile unsigned int g_euc_tick = 0;
// unsigned int g_euc_micros = (unsigned int)(1000000.0f / 120.0f / 16.0f);
unsigned int g_euc_micros = (unsigned int)(1000000.0f / (100.0f * 4.0f) * 60.f);
void euc_metronome_isr(void) {
    g_euc_tick++;
}

void setup() {
    Serial.begin(115200);

    setup_audio_objects();

    // put your setup code here, to run once:
    g_euc_metronome.begin(euc_metronome_isr, g_euc_micros);
}

unsigned int g_euc_tick_counter = 0;
void loop() {
    // put your main code here, to run repeatedly:
    static unsigned int last_print = 0;
    static unsigned int last_count = 0;
    unsigned int loc_euc_tick;
    unsigned int now = millis();

    noInterrupts();
    loc_euc_tick = g_euc_tick;
    interrupts();

    if(now - last_print > 1000) {
        last_print = now;
        Serial.println(loc_euc_tick - last_count);
        last_count = loc_euc_tick;
    }

    // potenttially play notes
    if(loc_euc_tick) {
        // process drums sounds
        // TODO - make list with structs/pointers for cleaner iteration
        if(EUBIT_GET_BIT(&eubitKick, 0))
            drumKick.noteOn();
        eubitKick.ix = EUBIT_IX_INCR(&eubitKick, 1);

        if(EUBIT_GET_BIT(&eubitSnare, 0))
            drumSnare.noteOn();
        eubitSnare.ix = EUBIT_IX_INCR(&eubitSnare, 1);

        if(EUBIT_GET_BIT(&eubitHiHat, 0))
            drumHiHat.noteOn();
        eubitHiHat.ix = EUBIT_IX_INCR(&eubitHiHat, 1);

        // subtract one from g_euc_tick after processing a metronome tick
        noInterrupts();
        g_euc_tick--;
        interrupts();

        if((g_euc_tick_counter & 0xF) == 0) {
            Serial.printf("measure = %u, ticks = %u\n",
                g_euc_tick_counter>>4, g_euc_tick_counter);
        }
        g_euc_tick_counter++;
    } //  end if(if(loc_euc_tick)
}