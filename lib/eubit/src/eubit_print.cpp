// eubit_print.c

#include <Arduino.h>
#include "eubit_print.h"


void eubit_print(eubit_seq_t *s) {
    Serial.printf("\neubit(n=%u, k=%u, rot=%u) = ...\n",
        s->m, s->k, s->ix);
    for(int ix=0; ix<s->m; ix++) {
        Serial.printf("    %u, %u, %s\n",
            ix, EUBIT_IX_INCR(s, ix),
            EUBIT_GET_BIT(s, ix) ? "X" : ".");
    }
}

