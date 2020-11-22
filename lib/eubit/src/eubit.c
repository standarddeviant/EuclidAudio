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

    int itr, bucket = 0;

    // mirror input variables to struct
    s->m = num_steps;
    s->k = num_pulses;

    // zero out sequence bytes
    for(itr=0; itr<EUBIT_MAX_SEQ_BYTE_LEN; itr++) {
        s->seq[itr] = 0;
    }

    // with the simple euclid algorithm below, rotating the index by 1 ensures
    // a beat on the 1st beat which is more typical
    s->ix = 1;

    bucket = 0;
    for(int itr=0; itr<num_steps; itr++) {
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
        // print(f"ix = {ix:2d}, bucket={bucket:2d}, steps={num_steps}, o={out[-1]}")
    } // end for

    // at the end set the index or rotation to 0
    s->ix = 0;
} // end eubit_init

#ifdef __cplusplus
}
#endif
