#ifndef PARAM_H
#define PARAM_H

#include <stdint.h>


// parameter set 1 (128bit security on biometric)
//#define LOGQ 32
//#define K 2048 // biometric bit
//#define N 928 // security
//#define M N + K // n+k
//#define LOGP 20 // log p
//#define STDEV 2.39 // error parameter
//#define STDEV_star 108 // error parameter
//#define SFT 64 - LOGQ

// Parameter Set 2 (128bit security on Biometric)
#define LOGQ 64
#define K 145832 // biometric bit
#define N 1368 // security
#define M N + K // N+K
#define LOGP 32 // log P
#define STDEV 295797.828 // error parameter
#define STDEV_star 112247383 // error parameter
#define SFT 64 - LOGQ


typedef uint64_t ZmodQ;
typedef ZmodQ Biometric[K]; // vector of +- 1

typedef struct {
	bool* S = new bool[N*K];
	ZmodQ* U = new ZmodQ[M];
} MasterSecretKey; // master secret key

typedef ZmodQ EncryptedBio[M + 1];
typedef ZmodQ EncryptedTemplate[M];

#endif
