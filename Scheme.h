#ifndef SCHEME_H_
#define SCHEME_H_

#include "defines.h"

#include <cstdint>

using namespace std;

namespace Scheme {
	void mskGen(MasterSecretKey& msk);
	void templateGen(EncryptedTemplate& encX, MasterSecretKey& msk, Biometric& x);
	void encryptBio(EncryptedBio& encY, MasterSecretKey& msk, Biometric& y);
	int64_t innerProduct(EncryptedTemplate& encX, EncryptedBio& encY);
}

#endif /* SCHEME_H_ */
