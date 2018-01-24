#ifndef SERVICE_WALLET_SERVICE_H_
#define SERVICE_WALLET_SERVICE_H_

#include <string>

namespace zdp {
	class wallet;
} /* namespace zdp */

namespace zdp {

	class wallet_service final {

		public:
			wallet_service();
			~wallet_service();

			zdp::wallet create_new_wallet(const std::string& name = "New wallet") const;

			void save(const std::string& file, const std::string& password) const;

			zdp::wallet load(const std::string& name, const std::string& password) const;

	};

} /* namespace zdp */

#endif /* SERVICE_WALLET_SERVICE_H_ */
