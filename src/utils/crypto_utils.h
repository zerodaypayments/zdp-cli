#ifndef UTILS_CRYPTO_UTILS_H_
#define UTILS_CRYPTO_UTILS_H_

#include <crtdefs.h>
#include <openssl/ossl_typ.h>
#include <string>

namespace zdp {
	namespace crypto {

		//void randomise(const void* arr, unsigned int length);
		std::string sha256(void* data, unsigned int length);
		std::string sha256(const std::string str);


		EC_KEY *bbp_ec_new_keypair(const uint8_t *priv_bytes);
		EC_KEY *bbp_ec_new_pubkey(const uint8_t *pub_bytes, size_t pub_len);

	}
}

#endif /* UTILS_CRYPTO_UTILS_H_ */
