#include <Arduino.h>
#include <IntervalTimer.h>

#include "audio_objects.h"

#include "eubit_print.h"

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
    // while(true) {
    //     eubit_print(&eubitKick);
    //     delay(5000);
    //     // eubit_print(&eubitSnare);
    //     // delay(5000);
    //     // eubit_print(&eubitHiHat);
    //     // delay(5000);
    // }


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
        if(eubit_take(&eubitKick))
            drumKick.noteOn();

        if(eubit_take(&eubitSnare))
            drumSnare.noteOn();

        if(eubit_take(&eubitHiHat))
            drumHiHat.noteOn();

        if(eubit_take(&eubitString))
            string1.noteOn(440.0f, 0.5);
        else
            string1.noteOff(0.5);

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