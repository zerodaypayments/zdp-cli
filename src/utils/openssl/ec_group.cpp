#include "ec_group.h"

namespace zdp {
	namespace crypto {
		namespace openssl {
			
			ec_group::ec_group(ec_key& key) {
				this->group = EC_KEY_get0_group(key.get());
			}
			
			ec_group::~ec_group() {
				if (group != nullptr) {
					// TODO EC_GROUP_clear_free(group);
					group = nullptr;
				}
			}
			
			const EC_GROUP* ec_group::get() {
				return group;
			}
		
		} /* namespace openssl */
	} /* namespace crypto */
} /* namespace zdp */
