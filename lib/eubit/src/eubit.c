// eubit.c

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include "eubit.h"

void eubit_init(eubit_seq_t *s,
                eubit_seq_len_t num_steps,
                eubit_seq_len_t num_onsets) {
    // TODO - assert k is >= 1
    // TODO - support different init rotations?

    int current, previous=-1;
    float slope = (float)num_onsets / (float)num_steps;

    // unsigned int itr, ix, a;

    // mirror input variables to struct
    s->m = num_steps;
    s->k = num_onsets;

    // zero out sequence bytes
    for(int itr=0; itr<EUBIT_MAX_SEQ_BYTE_LEN; itr++) {
        s->seq[itr] = 0;
    }

    // with the simple euclid algorithm below, rotating the index by 1 ensures
    // a beat on the 1st beat which is more typical
    for(int count=0; count<num_steps; count++) {
        current = (unsigned char)(floor((float)count * slope));
        if(current != previous) {
            s->seq[EUBIT_IX_BYTE(s, count)] += \
                1 << EUBIT_IX_SHIFT(s, count);
        }
        previous = current;

#if 0
        ix = EUBIT_IX_INCR(s, 0);
        a = (
            ( ((itr % s->m) + s->ix) * s->m )
            % s->m
        );
        if(a < s->k) {
            s->seq[EUBIT_IX_BYTE(s, itr)] += \
                1 << EUBIT_IX_SHIFT(s, itr);
        }
        else {
            // no action needed, the default data is already zero
        }
#endif

#if 0
        bucket += num_onsets;
        if (bucket >= num_steps) {
            bucket -= num_steps;
            // add a 'pulse' or '1' to the sequence
            s->seq[EUBIT_IX_BYTE(s, itr)] += \
                1 << EUBIT_IX_SHIFT(s, itr);
            // out.append(1)
        }
        else if(bucket < num_steps) {
            // no action needed, the default data is already zero
        }
        print(f"ix = {ix:2d}, bucket={bucket:2d}, steps={num_steps}, o={out[-1]}")
#endif
    } // end for

    // at the end set the index or rotation to 0
    s->ix = 0;
} // end eubit_init


unsigned char eubit_take(eubit_seq_t *s) {
    // get bit where 0 = rest, 1 = note
    unsigned char out = EUBIT_GET_BIT(s, 0);

    // increment index in struct
    s->ix = EUBIT_IX_INCR(s, 1);

    // return bit
    return out;
}


#ifdef __cplusplus
}
#endif
