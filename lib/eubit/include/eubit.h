
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _EUBIT_H_
#define _EUBIT_H_

// eubit.h

// length defines for core data type
#define EUBIT_MAX_SEQ_BIT_LEN (256) // power-of-2 for simplicity
#define EUBIT_MAX_SEQ_BYTE_LEN (EUBIT_MAX_SEQ_BIT_LEN >> 3)

// support data types
typedef enum {
    EUBIT_0 = 0,
    EUBIT_1 = 1
} eubit_t;
typedef enum {
    EUBIT_SEQ_TYPE_NA,
    EUBIT_SEQ_TYPE_BINARY,
    EUBIT_SEQ_TYPE_NOTE,
    EUBIT_NUM_SEQ_TYPES
} eubit_seq_type_t;
typedef unsigned int eubit_seq_ix_t;
typedef eubit_seq_ix_t eubit_seq_len_t;

// core data type
typedef struct {
    eubit_seq_len_t m;
    eubit_seq_len_t k;
    eubit_seq_ix_t ix;
    unsigned char seq[EUBIT_MAX_SEQ_BYTE_LEN];
} eubit_seq_t;

// convenient, efficient macros for interactions with core data type
#define EUBIT_IX_INCR(s, incr)  \
(                               \
    ((s)->ix + incr < (s)->m) ? \
    ((s)->ix + incr) :          \
    ((s)->ix + incr - (s)->m)   \
)
#define EUBIT_IX_BYTE(s, incr) (EUBIT_IX_INCR(s, incr)>>3)
#define EUBIT_IX_SHIFT(s, incr) (7-((EUBIT_IX_INCR(s, incr))&0b111))
#define EUBIT_GET_BYTE(s, incr) ((s)->seq[EUBIT_IX_BYTE(EUBIT_IX_BYTE())])
#define EUBIT_GET_BIT(s, incr)                              \
(                                                           \
    (                                                       \
        (s)->seq[EUBIT_IX_BYTE(s, EUBIT_IX_INCR(s, incr))]  \
        >> EUBIT_IX_SHIFT(s, EUBIT_IX_INCR(s, incr))        \
    ) & 1                                                   \
)

void eubit_init(eubit_seq_t *s, eubit_seq_len_t m, eubit_seq_len_t k);
unsigned char eubit_take(eubit_seq_t *s);

#endif // _EUBIT_H_

#ifdef __cplusplus
}
#endif