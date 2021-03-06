#include <iostream>
#include <vector>

#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/bn.h>
#include <openssl/ec.h>

#include "../json.hpp"

#include "crypto_utils.h"
#include "key_pair.h"
#include "base58.h"

namespace zdp {

	using json = nlohmann::json;

	key_pair::key_pair() {

		auto buffer = zdp::crypto::random(SHA256_DIGEST_LENGTH);

		auto key = zdp::crypto::ec_new_keypair(buffer);

		// Private key in Base58
		{

			auto priv_bn = EC_KEY_get0_private_key(key);

			std::vector<unsigned char> priv_byte_array(BN_num_bytes(priv_bn));

			BN_bn2bin(priv_bn, priv_byte_array.data());

			auto priv_base58 = zdp::base58::encode_base(priv_byte_array);

			this->private_key = priv_base58;

		}

		// Public key in Base58
		{

			auto pub_bn = BN_new();

			EC_POINT_point2bn(EC_KEY_get0_group(key), EC_KEY_get0_public_key(key), point_conversion_form_t::POINT_CONVERSION_COMPRESSED, pub_bn, nullptr);

			std::vector<unsigned char> pub_byte_array(BN_num_bytes(pub_bn));

			BN_bn2bin(pub_bn, pub_byte_array.data());

			auto pub_base58 = zdp::base58::encode_base(pub_byte_array);

			this->public_key = std::string(pub_base58);

		}

		EC_KEY_free(key);
	}

	key_pair::key_pair(std::string priv_key) {

		this->private_key = priv_key;
		this->public_key = zdp::crypto::get_public_key(priv_key);

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

