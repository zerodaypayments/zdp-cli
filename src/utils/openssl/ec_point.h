#ifndef UTILS_OPENSSL_EC_POINT_H_
#define UTILS_OPENSSL_EC_POINT_H_

#include <openssl/ec.h>

#include "ec_group.h"

namespace zdp {
	namespace crypto {
		namespace openssl {
			
			class ec_point final {

				private:

					EC_POINT *pt = nullptr;

				public:

					ec_point(ec_group& group);
					~ec_point();

					EC_POINT *get();
			};
		
		} /* namespace openssl */
	} /* namespace crypto */
} /* namespace zdp */

#endif /* UTILS_OPENSSL_EC_POINT_H_ */
