#include "Scheme.h"
#include "distr.h"

#include <iostream>


using namespace std;

namespace Scheme {
	void mskGen(MasterSecretKey& msk) {
		int i, j, k;
		for (i = 0; i <N; ++i) {
			for (j = 0; j < K; ++j) {
				msk.S[i * K + j] = (U(GEN)%2);
			}
		}
		for (k = 0; k < M; ++k) msk.U[k] = (U(GEN) >> (SFT));
	}

	void templateGen(EncryptedTemplate& encX, MasterSecretKey& msk, Biometric& x) {
		int i, j;
		for (i = 0; i < K; ++i) encX[i] = x[i] + msk.U[i];
		for (i = 0; i < N; ++i) {
			encX[i + K] = msk.U[i + K];
			for (j = 0; j < K; ++j){
				encX[i + K] += (msk.S[i * K + j] * x[j]);
			}
		}
	}

	void encryptBio(EncryptedBio& encY, MasterSecretKey& msk, Biometric& y) {
		int i, j;
		for (i = K + 1; i < M + 1; ++i) encY[i] = (U(GEN) << (SFT));
		for (i = 0; i < K; ++i) {
			encY[i + 1] = (ZmodQ)(DG(GEN)*pow(2, SFT) + 0.5) + (y[i] << (LOGQ - LOGP + SFT));
			for (j = 0; j < N; ++j) encY[i + 1] -= encY[K + 1 + j] * msk.S[j * K + i];
		}
		encY[0] = (ZmodQ)(DGstar(GEN)*pow(2, SFT) + 0.5);
		for (i = 0; i < M; ++i) encY[0] -= msk.U[i] * encY[i + 1];	
	}

	int64_t innerProduct(EncryptedTemplate& encX, EncryptedBio& encY) {
		ZmodQ res = encY[0];
		int64_t comp = 1;
		comp <<= (LOGP - 1);
		int64_t result;

		for (int i = 0; i < M; ++i) res += encX[i] * encY[i + 1];
		res += ((ZmodQ)1 << (LOGQ - LOGP - 1 + SFT));
		res >>= (LOGQ - LOGP + SFT);
		result = (int64_t) res;
		if (result >= comp)	result -= 2 * comp;

		return result;
	}
};
