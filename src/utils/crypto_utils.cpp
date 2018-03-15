#include "crypto_utils.h"

#include <iostream>
#include <sstream>
#include <iomanip>

#include <openssl/bn.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/ecdsa.h>

#include "base58.h"

EC_KEY *zdp::crypto::ec_new_keypair(std::vector<unsigned char>& priv_bytes) {

	EC_KEY *key = nullptr;
	BIGNUM *priv = nullptr;
	BN_CTX *ctx = nullptr;
	const EC_GROUP *group = nullptr;
	EC_POINT *pub = nullptr;

	/* init empty OpenSSL EC keypair */

	key = EC_KEY_new_by_curve_name(NID_secp256k1);

	if (!key) {
		std::cerr << "Can't generate curve secp256k1\n";
		std::abort();
	}

	/* set private key through BIGNUM */

	priv = BN_new();
	BN_bin2bn(priv_bytes.data(), 32, priv);
	EC_KEY_set_private_key(key, priv);

	/* derive public key from private key and group */

	ctx = BN_CTX_new();
	BN_CTX_start(ctx);

	group = EC_KEY_get0_group(key);
	pub = EC_POINT_new(group);
	EC_POINT_mul(group, pub, priv, NULL, NULL, ctx);
	EC_KEY_set_public_key(key, pub);

	/* release resources */

	EC_POINT_free(pub);
	BN_CTX_end(ctx);
	BN_CTX_free(ctx);
	BN_clear_free(priv);

	return key;
}

EC_KEY *zdp::crypto::ec_new_pubkey(std::vector<unsigned char>& pub_key) {

	EC_KEY *key = nullptr;
	const uint8_t *pub_bytes_copy = nullptr;

	key = EC_KEY_new_by_curve_name(NID_secp256k1);
	pub_bytes_copy = pub_key.data();
	o2i_ECPublicKey(&key, &pub_bytes_copy, pub_key.size());

	return key;
}

std::string zdp::crypto::get_public_key(std::string& priv_key) {

	auto byte_array = zdp::base58::decode_base(priv_key);

	auto key = zdp::crypto::ec_new_keypair(byte_array);

	// Public key in Base58

	auto pub_bn = BN_new();

	EC_POINT_point2bn(EC_KEY_get0_group(key), EC_KEY_get0_public_key(key), point_conversion_form_t::POINT_CONVERSION_COMPRESSED, pub_bn, nullptr);

	std::vector<unsigned char> pub_byte_array(BN_num_bytes(pub_bn));

	BN_bn2bin(pub_bn, pub_byte_array.data());

	auto pub_base58 = zdp::base58::encode_base(pub_byte_array);

	return std::string(pub_base58);

}

std::string zdp::crypto::sha256(std::string& str) {

	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str.c_str(), str.size());
	SHA256_Final(hash, &sha256);
	std::stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		ss << std::hex << std::setw(2) << std::setfill('0') << (int) hash[i];
	}
	return ss.str();

}

std::string zdp::crypto::sha256(std::vector<unsigned char>& unhashed) {

	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, unhashed.data(), unhashed.size());
	SHA256_Final(hash, &sha256);
	std::stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		ss << std::hex << std::setw(2) << std::setfill('0') << (int) hash[i];
	}
	return ss.str();

}

std::vector<unsigned char> zdp::crypto::random(const unsigned int length) {

	std::vector<unsigned char> buffer(length);

	RAND_bytes(buffer.data(), length);

	return buffer;

}

std::vector<unsigned char> zdp::crypto::sign(std::string& private_key_58, std::string& text) {

	// Convert Base58 private key to EC_KEY
	auto priv_key_bytes = zdp::base58::decode_base(private_key_58);

	auto ec_key = zdp::crypto::ec_new_keypair(priv_key_bytes);

    auto signature = ECDSA_do_sign((const unsigned char*)text.data(), text.size(), ec_key);

    // https://stackoverflow.com/questions/30102116/how-to-convert-ecdsa-sig-signature-to-array-of-characters-in-c
}

std::vector<unsigned char> zdp::crypto::encrypt(std::string& public_key_58, std::string& text) {
}
