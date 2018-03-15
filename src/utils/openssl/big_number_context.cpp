#include "big_number_context.h"

#include <openssl/bn.h>

namespace zdp {
	namespace crypto {
		namespace openssl {
			
			big_number_context::big_number_context() {
				ctx = BN_CTX_new();
				BN_CTX_start(ctx);
			}
			
			big_number_context::~big_number_context() {
				if (ctx != nullptr) {
					BN_CTX_end(ctx);
					BN_CTX_free(ctx);
					ctx = nullptr;
				}
			}
			
			BN_CTX* big_number_context::get() {
				return ctx;
			}
		
		} /* namespace openssl */
	} /* namespace crypto */
} /* namespace zdp */
