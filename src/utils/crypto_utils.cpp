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

std::string zdp::crypto::sha256(const std::string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

std::string zdp::crypto::sha256(void* data, unsigned int length)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data, length);
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}



EC_KEY *zdp::crypto::ec_new_keypair(const uint8_t *priv_bytes) {

	EC_KEY *key;
	BIGNUM *priv;
	BN_CTX *ctx;
	const EC_GROUP *group;
	EC_POINT *pub;

	/* init empty OpenSSL EC keypair */

	key = EC_KEY_new_by_curve_name(NID_secp256k1);

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

EC_KEY *zdp::crypto::ec_new_pubkey(const uint8_t *pub_bytes,
		size_t pub_len) {
	EC_KEY *key;
	const uint8_t *pub_bytes_copy;

	key = EC_KEY_new_by_curve_name(NID_secp256k1);
	pub_bytes_copy = pub_bytes;
	o2i_ECPublicKey(&key, &pub_bytes_copy, pub_len);

	return key;
}

/*
 void zdp::crypto::randomise(const void* arr, unsigned int length) {

 byte buffer[length];

 int rc = RAND_bytes(buffer, sizeof(buffer));
 unsigned long err = ERR_get_error();

 if (rc != 1) {
 std::cerr << "Can't generate random number\n";
 } else {
 std::cout << "Generated random number\n";
 }
 }
 */
