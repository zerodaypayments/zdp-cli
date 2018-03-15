#include "big_number.h"

#include <openssl/bn.h>
#include <openssl/ec.h>

namespace zdp {
	namespace crypto {
		namespace openssl {
			
			big_number::big_number() {

				this->bn = BN_new();

			}
			
			big_number::big_number(std::vector<unsigned char>& byte_array) :
					big_number::big_number() {

				BN_bin2bn(byte_array.data(), byte_array.size(), this->bn);

			}

			big_number::~big_number() {
				if (this->bn != nullptr) {
					BN_clear_free(this->bn);
					this->bn = nullptr;
				}
			}
			
			std::vector<unsigned char> big_number::to_byte_array() const {

				std::vector<unsigned char> buffer(this->get_size_in_bytes());

				BN_bin2bn(buffer.data(), buffer.size(), this->bn);

				return buffer;

			}
			
			int big_number::get_size_in_bytes() const {
				return BN_num_bytes(bn);
			}
			
			BIGNUM* big_number::get() {
				return bn;
			}
		
		}
	}
}

