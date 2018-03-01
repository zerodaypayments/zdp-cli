#include <iostream>

#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/bn.h>
#include <openssl/ec.h>

#include "../json.hpp"

#include "crypto_utils.h"
#include "key_pair.h"

namespace zdp {

	using json = nlohmann::json;

	key_pair::key_pair() {

		uint8_t buffer[32];

		int rc = RAND_bytes(buffer, sizeof(buffer));

		if (rc != 1) {
			std::cerr << "Can't generate a number: " << std::to_string(ERR_get_error()) << std::endl;
			std::abort();
		}

		auto key = zdp::crypto::ec_new_keypair(buffer);

		auto priv_bn = EC_KEY_get0_private_key(key);

		this->private_key = BN_bn2hex(priv_bn);
		this->public_key = EC_POINT_point2hex(EC_KEY_get0_group(key), EC_KEY_get0_public_key(key), point_conversion_form_t::POINT_CONVERSION_COMPRESSED, nullptr);

		EC_KEY_free(key);
	}

	key_pair::key_pair(std::string priv_key) {

		BIGNUM* bn = nullptr;

		BN_hex2bn(&bn, priv_key.c_str());

		uint8_t buffer[BN_num_bytes(bn)];
		BN_bn2bin(bn, buffer);

		auto key = zdp::crypto::ec_new_keypair(buffer);

		auto priv_bn = EC_KEY_get0_private_key(key);
		this->private_key = BN_bn2hex(priv_bn);

		this->public_key = EC_POINT_point2hex(EC_KEY_get0_group(key), EC_KEY_get0_public_key(key), point_conversion_form_t::POINT_CONVERSION_COMPRESSED, nullptr);

		EC_KEY_free(key);

	}

	key_pair::~key_pair() {
	}

	std::string key_pair::to_json(zdp::language lang) {

		//std::vector<std::string> vec = zdp::generate_mnemonics(lang, this->private_key);
		//json mnemonics (vec);

		json j = { { "privateKey", private_key }, { "publicKey", public_key } };

		return j.dump(4);
	}

	std::string const & key_pair::get_private_key() const {
		return private_key;
	}

	std::string const & key_pair::get_public_key() const {
		return public_key;
	}

} /* namespace zdp */

