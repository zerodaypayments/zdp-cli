#ifndef UTILS_OPENSSL_EC_GROUP_H_
#define UTILS_OPENSSL_EC_GROUP_H_

#include <openssl/ec.h>

#include "ec_key.h"

namespace zdp {
	namespace crypto {
		namespace openssl {
			
			class ec_group final {
				private:
					const EC_GROUP* group = nullptr;
				public:
					ec_group(ec_key& key);
					~ec_group();

					const EC_GROUP* get();
			};
		
		} /* namespace openssl */
	} /* namespace crypto */
} /* namespace zdp */

#endif /* UTILS_OPENSSL_EC_GROUP_H_ */
