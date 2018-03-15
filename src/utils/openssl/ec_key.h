#ifndef UTILS_OPENSSL_EC_KEY_H_
#define UTILS_OPENSSL_EC_KEY_H_

#include <openssl/ossl_typ.h>
#include <vector>

#include "big_number.h"

namespace zdp {

	namespace crypto {

		namespace openssl {
			
			class ec_key final {

				private:

					EC_KEY *key = nullptr;

				public:

					ec_key();

					ec_key(std::vector<unsigned char>& priv_key_bytes);

					~ec_key();

					void set_private_key(big_number& bn);

					EC_KEY *get();
			};
		
		} /* namespace openssl */
	} /* namespace crypto */
} /* namespace zdp */

#endif /* UTILS_OPENSSL_EC_KEY_H_ */
