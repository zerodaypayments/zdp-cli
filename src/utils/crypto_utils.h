#ifndef UTILS_CRYPTO_UTILS_H_
#define UTILS_CRYPTO_UTILS_H_

#include <openssl/ossl_typ.h>
#include <openssl/ec.h>

#include <string>
#include <vector>

namespace zdp {
	namespace crypto {

		std::vector<unsigned char> random(const unsigned int length);

		std::string sha256(std::string& value);
		std::string sha256(std::vector<unsigned char>& value);

		EC_KEY *ec_new_keypair(std::vector<unsigned char>& byte_array);
		EC_KEY *ec_new_pubkey(std::vector<unsigned char>& pub_key);

		std::string get_public_key(std::string& private_key);

		std::vector<unsigned char> sign(std::string& private_key_58, std::string& text);

		std::vector<unsigned char> encrypt(std::string& public_key_58, std::string& text);

	}
}

#endif /* UTILS_CRYPTO_UTILS_H_ */
