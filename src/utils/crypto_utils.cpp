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

EC_KEY *zdp::crypto::ec_new_keypair(const uint8_t *priv_bytes) {

	EC_KEY *key = nullptr;
	BIGNUM *priv = nullptr;
	BN_CTX *ctx = nullptr;
	const EC_GROUP *group = nullptr;
	EC_POINT *pub = nullptr;

	/* init empty OpenSSL EC keypair */

	key = EC_KEY_new_by_curve_name(NID_brainpoolP256r1);

	if (!key) {
		std::cerr << "Can't generate curve NID_brainpoolP256r1\n";
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

	key = EC_KEY_new_by_curve_name(NID_brainpoolP256r1);
	pub_bytes_copy = pub_bytes;
	o2i_ECPublicKey(&key, &pub_bytes_copy, pub_len);

	return key;
}

int zdp::crypto::sign(EC_KEY* key, std::string const & text) {

}
