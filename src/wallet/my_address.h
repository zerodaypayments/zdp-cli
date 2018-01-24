#ifndef WALLET_MY_ADDRESS_H_
#define WALLET_MY_ADDRESS_H_

#include <crypto++/rsa.h>
#include <string>

namespace zdp {

	class my_address final {

		private:
			CryptoPP::RSA::PrivateKey key;
			std::string address;
			std::string seed;
			std::string description;
			double balance = 0;
			long date = 0;

		public:
			my_address();
			~my_address();
	};

} /* namespace zdp */

#endif /* WALLET_MY_ADDRESS_H_ */
