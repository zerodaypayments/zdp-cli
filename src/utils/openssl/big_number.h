#ifndef UTILS_OPENSSL_BIG_NUMBER_H_
#define UTILS_OPENSSL_BIG_NUMBER_H_

#include <openssl/ossl_typ.h>
#include <vector>

namespace zdp {
	namespace crypto {
		namespace openssl {
			
			class big_number final {

					BIGNUM *bn = nullptr;

				public:

					big_number();
					big_number(std::vector<unsigned char>& byte_array);

					~big_number();

					std::vector<unsigned char> to_byte_array() const;
					int get_size_in_bytes() const;

					BIGNUM* get();



			};
		
		} /* namespace openssl */
	} /* namespace crypto */
} /* namespace zdp */

#endif /* UTILS_OPENSSL_BIG_NUMBER_H_ */
