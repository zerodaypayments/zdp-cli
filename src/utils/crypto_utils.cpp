#include "crypto_utils.h"

#include <openssl/rand.h>
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>

#include "base58.h"
#include "openssl/ec_key.h"

/*
EC_KEY *zdp::crypto::ec_new_keypair(const uint8_t *priv_bytes) {

	EC_KEY *key = nullptr;
	BIGNUM *priv = nullptr;
	BN_CTX *ctx = nullptr;
	const EC_GROUP *group = nullptr;
	EC_POINT *pub = nullptr;

	key = EC_KEY_new_by_curve_name(NID_secp256k1);

	if (!key) {
		std::cerr << "Can't generate curve secp256k1\n";
		std::abort();
	}

	priv = BN_new();
	BN_bin2bn(priv_bytes, 32, priv);
	EC_KEY_set_private_key(key, priv);

	ctx = BN_CTX_new();
	BN_CTX_start(ctx);

	group = EC_KEY_get0_group(key);
	pub = EC_POINT_new(group);
	EC_POINT_mul(group, pub, priv, NULL, NULL, ctx);
	EC_KEY_set_public_key(key, pub);

	EC_POINT_free(pub);
	BN_CTX_end(ctx);
	BN_CTX_free(ctx);
	BN_clear_free(priv);

	return key;
}

EC_KEY *zdp::crypto::ec_new_pubkey(const uint8_t *pub_bytes, size_t pub_len) {

	EC_KEY *key = nullptr;
	const uint8_t *pub_bytes_copy = nullptr;

	key = EC_KEY_new_by_curve_name(NID_secp256k1);
	pub_bytes_copy = pub_bytes;
	o2i_ECPublicKey(&key, &pub_bytes_copy, pub_len);

	return key;
}
*/
std::string zdp::crypto::get_public_key(std::string& priv_key) {

	std::vector<unsigned char> byte_array;

	zdp::base58::decode_base(priv_key, byte_array);


	zdp::crypto::openssl::ec_key key;



/*
	auto key = zdp::crypto::ec_new_keypair(byte_array.data());

	// Public key in Base58

	auto pub_bn = BN_new();

	EC_POINT_point2bn(EC_KEY_get0_group(key), EC_KEY_get0_public_key(key), point_conversion_form_t::POINT_CONVERSION_COMPRESSED, pub_bn, nullptr);

	std::vector<unsigned char> pub_byte_array(BN_num_bytes(pub_bn));

	BN_bn2bin(pub_bn, pub_byte_array.data());

	auto pub_base58 = zdp::base58::encode_base(pub_byte_array);

	return std::string(pub_base58);
*/
}

std::string zdp::crypto::sha256(std::string const & str) {

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

std::pair<std::string, std::string> zdp::crypto::generate_new_key_pair() {

	std::pair<std::string, std::string> pair;

	zdp::crypto::openssl::ec_key();


	return pair;
}

std::vector<unsigned char> zdp::crypto::sign(std::string& private_key, std::string const & text) {
	
}

std::vector<unsigned char> zdp::crypto::random(const unsigned int length) {

	std::vector<unsigned char> buffer(length);

	RAND_bytes(buffer.data(), length);

	return buffer;

}
