#ifndef WALLET_WALLET_H_
#define WALLET_WALLET_H_

#include <string>
#include <vector>

#include "my_address.h"
#include "recepient_address.h"
#include "wallet_event.h"

namespace zdp {

	class wallet final {

		private:
			std::vector<my_address> my_addresses;
			std::vector<recepient_address> recepient_addresses;
			std::vector<wallet_event> wallet_events;
			long date = 0;
			std::string name;
			int version = 0;
			std::string file;
			int sequence = 0;

		public:

			wallet();
			~wallet();

			const std::string& get_name() const;
			void set_name(const std::string& name);
	};

} /* namespace zdp */

#endif /* WALLET_WALLET_H_ */
