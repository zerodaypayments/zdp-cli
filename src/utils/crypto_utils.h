#ifndef UTILS_CRYPTO_UTILS_H_
#define UTILS_CRYPTO_UTILS_H_

#include <openssl/ossl_typ.h>
#include <string>
#include <utility>
#include <vector>

namespace zdp {
	namespace crypto {

		std::vector<unsigned char> random(const unsigned int length);

		std::pair<std::string, std::string> generate_new_key_pair();

		std::string sha256(const std::string& value);
		std::string sha256(std::vector<unsigned char>& value);

		EC_KEY *ec_new_keypair(const uint8_t *priv_bytes);
		EC_KEY *ec_new_pubkey(const uint8_t *pub_bytes, size_t pub_len);

		std::string get_public_key(std::string& private_key);

		std::vector<unsigned char> sign(std::string& private_key, const std::string& text);

	}
}

#endif /* UTILS_CRYPTO_UTILS_H_ */
