#ifndef UTILS_CRYPTO_UTILS_H_
#define UTILS_CRYPTO_UTILS_H_

#include <openssl/ossl_typ.h>
#include <string>
#include <utility>
#include <vector>

namespace zdp {

	namespace crypto {

		/*
		 * Generate random private key in Base58 format for NID_secp256k1 curve
		 */
		std::string generate_random_private_key();

		/**
		 * Generate public key in Base58 format for a given private key (in Base58 format)
		 */
		std::string generate_public_key(const std::string& private_key_58);

		/**
		 * Generate a byte vector of random bytes of specified length
		 */
		std::vector<unsigned char> random(const unsigned int length);

		/**
		 * Calculates the SHA-256 digest and returns the value as a string value
		 */
		std::string sha256(const std::string& value);

		/**
		 * Calculates the SHA-256 digest and returns the value as a string value
		 */
		std::string sha256(const std::vector<unsigned char>& value);

		/**
		 * Sign some text and return as a byte vector
		 */
		std::vector<unsigned char> sign(const std::string& private_key, const std::string& text);

		/**
		 * Ecnrypt some text using a network public key and return as a string
		 */
		std::string encrypt_with_network_public_key(const std::string& text);

	}
}

#endif /* UTILS_CRYPTO_UTILS_H_ */
