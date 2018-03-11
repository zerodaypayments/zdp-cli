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

#include "base58.h"

EC_KEY *zdp::crypto::ec_new_keypair(const uint8_t *priv_bytes) {

	EC_KEY *key = nullptr;
	BIGNUM *priv = nullptr;
	BN_CTX *ctx = nullptr;
	const EC_GROUP *group = nullptr;
	EC_POINT *pub = nullptr;

	/* init empty OpenSSL EC keypair */

	key = EC_KEY_new_by_curve_name(NID_secp256k1);

	if (!key) {
		std::cerr << "Can't generate curve NID_secp256k1\n";
		std::abort();
	}

	/* set private key through BIGNUM */

	priv = BN_new();
	BN_bin2bn(priv_bytes, 32, priv);
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

EC_KEY *zdp::crypto::ec_new_pubkey(const uint8_t *pub_bytes, size_t pub_len) {

	EC_KEY *key = nullptr;
	const uint8_t *pub_bytes_copy = nullptr;

	key = EC_KEY_new_by_curve_name(NID_secp256k1);
	pub_bytes_copy = pub_bytes;
	o2i_ECPublicKey(&key, &pub_bytes_copy, pub_len);

	return key;
}

std::string zdp::crypto::get_public_key(std::string& priv_key) {

	std::vector<unsigned char> byte_array;

	zdp::base58::decode_base(priv_key, byte_array);

	auto key = zdp::crypto::ec_new_keypair(byte_array.data());

	// Public key in Base58

	auto pub_bn = BN_new();

	EC_POINT_point2bn(EC_KEY_get0_group(key), EC_KEY_get0_public_key(key), point_conversion_form_t::POINT_CONVERSION_COMPRESSED, pub_bn, nullptr);

	std::vector<unsigned char> pub_byte_array(BN_num_bytes(pub_bn));

	BN_bn2bin(pub_bn, pub_byte_array.data());

	auto pub_base58 = zdp::base58::encode_base(pub_byte_array);

	return std::string(pub_base58);

}

std::vector<unsigned char> zdp::crypto::sign(std::string& private_key, std::string const & text) {



}
