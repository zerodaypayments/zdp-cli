/* Copyright (C) 2018 ZDP Developers - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 *
 * Proprietary and confidential
 *
 * <zdp@zdp.io>
 */

#ifndef WALLET_WALLET_TRANSACTION_H_
#define WALLET_WALLET_TRANSACTION_H_

#include <string>
#include <vector>

namespace zdp {

	class wallet_transaction final {

		private:

			std::string uuid;
			unsigned long long int amount = 0;
			unsigned long long int fee = 0;
			unsigned long long int date = 0;
			std::string from;
			std::string to;
			std::string memo;

		public:

			wallet_transaction();
			~wallet_transaction();


	};

} /* namespace zdp */

#endif /* WALLET_WALLET_TRANSACTION_H_ */
