#include "ec_key.h"

#include <openssl/bn.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <iostream>

#include "big_number_context.h"
#include "ec_group.h"
#include "ec_point.h"

namespace zdp {
	namespace crypto {
		namespace openssl {
			
			ec_key::ec_key() {

				key = EC_KEY_new_by_curve_name(NID_secp256k1);

				if (!key) {
					std::cerr << "Can't generate curve secp256k1\n";
					std::abort();
				}
			}

			ec_key::ec_key(std::vector<unsigned char>& priv_key_bytes) {

				zdp::crypto::openssl::big_number priv (priv_key_bytes);

				this->set_private_key(priv);

				zdp::crypto::openssl::big_number_context ctx;

				zdp::crypto::openssl::ec_group group (*this);

				zdp::crypto::openssl::ec_point pt (group);

				EC_POINT_mul(group.get(), pt.get(), priv.get(), nullptr, nullptr, ctx.get());

				EC_KEY_set_public_key(key, pt.get());

			}

			ec_key::~ec_key() {
				if (key != nullptr) {
					EC_KEY_free(key);
					key = nullptr;
				}
			}
			
			EC_KEY* ec_key::get() {
				return key;
			}
		
			void ec_key::set_private_key(big_number& bn) {
				EC_KEY_set_private_key(key, bn.get());
			}

		} /* namespace openssl */
	} /* namespace crypto */
} /* namespace zdp */

