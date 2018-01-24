
#ifndef WALLET_RECEPIENT_ADDRESS_H_
#define WALLET_RECEPIENT_ADDRESS_H_

#include <string>

namespace zdp {

	class recepient_address final {

		private:
			std::string address;
			std::string description;
			long date = 0;


		public:
			recepient_address();
			~recepient_address();
	};

} /* namespace zdp */

#endif /* WALLET_RECEPIENT_ADDRESS_H_ */
