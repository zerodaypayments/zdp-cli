#ifndef UTILS_OPENSSL_BIG_NUMBER_CONTEXT_H_
#define UTILS_OPENSSL_BIG_NUMBER_CONTEXT_H_

#include <openssl/ossl_typ.h>

namespace zdp {
	namespace crypto {
		namespace openssl {
			
			class big_number_context final {
				private:
					BN_CTX *ctx = nullptr;
				public:
					big_number_context();
					~big_number_context();

					BN_CTX* get();
			};
		
		} /* namespace openssl */
	} /* namespace crypto */
} /* namespace zdp */

#endif /* UTILS_OPENSSL_BIG_NUMBER_CONTEXT_H_ */
