#ifndef UTILS_CRYPTO_UTILS_H_
#define UTILS_CRYPTO_UTILS_H_

#include <openssl/ossl_typ.h>
#include <openssl/ec.h>

#include <string>

namespace zdp {
	namespace crypto {


		EC_KEY *ec_new_keypair(const uint8_t *priv_bytes);
		EC_KEY *ec_new_pubkey(const uint8_t *pub_bytes, size_t pub_len);

		int sign(EC_KEY * key, const std::string& text);

	}
}

#endif /* UTILS_CRYPTO_UTILS_H_ */
