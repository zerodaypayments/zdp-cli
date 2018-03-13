/* Copyright (C) 2018 ZDP Developers - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 *
 * Proprietary and confidential
 *
 * <zdp@zdp.io>
 */

#ifndef WALLET_WALLET_H_
#define WALLET_WALLET_H_

#include <string>
#include <vector>

#include "../utils/mnemonics.h"
#include "wallet_transaction.h"

namespace zdp {

	enum class wallet_language {
	};

	class wallet final {

		private:
			std::vector<wallet_transaction> transactions;
			unsigned long long int date_created = 0;
			unsigned long long int date_last_updated = 0;
			std::string private_key;
			std::string public_key;
			unsigned long long int balance = 0;

		public:
			wallet();
			~wallet();

			/*
			 * Return transaction by UUID
			 */
			wallet_transaction& get_by_uuid(std::string& uuid);

			/*
			 * Return list of transactions sorted by date (descending order)
			 */
			std::vector<wallet_transaction> get_transactions();

			unsigned long long int get_balance() const;
			void set_balance(unsigned long long int balance = 0);

			unsigned long long int get_date_created() const;
			void set_date_created(unsigned long long int dateCreated = 0);

			unsigned long long int get_date_last_updated() const;
			void set_date_last_updated(unsigned long long int dateLastUpdated = 0);

			const std::string& get_private_key() const;
			void set_private_key(const std::string& privateKey);

			const std::string& get_public_key() const;
			void set_public_key(const std::string& publicKey);

			std::string to_json();

	};

} /* namespace zdp */

#endif /* WALLET_WALLET_H_ */
