// eubit.c

#ifdef __cplusplus
extern "C" {
#endif

#include "eubit.h"

void eubit_init(eubit_seq_t *s,
                eubit_seq_len_t num_steps,
                eubit_seq_len_t num_pulses) {
    // TODO - assert k is >= 1
    // TODO - support different init rotations?

    // unsigned int itr, ix, a;

    // mirror input variables to struct
    s->m = num_steps;
    s->k = num_pulses;

    // zero out sequence bytes
    for(int itr=0; itr<EUBIT_MAX_SEQ_BYTE_LEN; itr++) {
        s->seq[itr] = 0;
    }

    // with the simple euclid algorithm below, rotating the index by 1 ensures
    // a beat on the 1st beat which is more typical
    s->ix = 2;
    float ratio = ((float)num_pulses) / ((float)num_steps);
    float accum = 1.0f;
    s->seq[EUBIT_IX_BYTE(s, 0)] += \
        1 << EUBIT_IX_SHIFT(s, 0);
    for(int count=1; count<num_steps; count++) {
        // probably not quite right, but pretty good when starting @ ix=2
        // m = n - k
        if(ratio*((float)count) < accum) {
            // nothing to do - zero or rest case
        }
        else {
            s->seq[EUBIT_IX_BYTE(s, count)] += \
                1 << EUBIT_IX_SHIFT(s, count);
            accum += 1.0f;
        }

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
        bucket += num_pulses;
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
