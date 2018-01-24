#ifndef WALLET_WALLET_EVENT_H_
#define WALLET_WALLET_EVENT_H_

#include <string>

namespace zdp {

	enum class wallet_event_type {
		NO_TYPE = -1, WALLET_CREATED = 0, ADDRESS_GENERATED = 1
	};

	class wallet_event {

		private:
			wallet_event_type type = wallet_event_type::NO_TYPE;
			long date = 0;
			std::string message;

		public:
			wallet_event();
			virtual ~wallet_event();
	};

} /* namespace zdp */

#endif /* WALLET_WALLET_EVENT_H_ */
