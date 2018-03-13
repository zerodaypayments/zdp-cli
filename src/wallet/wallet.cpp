/* Copyright (C) 2018 ZDP Developers - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 *
 * Proprietary and confidential
 *
 * <zdp@zdp.io>
 */

#include "../wallet/wallet.h"

namespace zdp {

	wallet::wallet() {

	}

	wallet::~wallet() {
	}

	unsigned long long int wallet::get_balance() const {
		return balance;
	}

	void wallet::set_balance(unsigned long long int balance) {
		this->balance = balance;
	}

	unsigned long long int wallet::get_date_created() const {
		return date_created;
	}

	void wallet::set_date_created(unsigned long long int dateCreated) {
		date_created = dateCreated;
	}

	unsigned long long int wallet::get_date_last_updated() const {
		return date_last_updated;
	}

	void wallet::set_date_last_updated(unsigned long long int dateLastUpdated) {
		date_last_updated = dateLastUpdated;
	}

	const std::string& wallet::get_private_key() const {
		return private_key;
	}

	void wallet::set_private_key(const std::string& privateKey) {
		private_key = privateKey;
	}

	const std::string& wallet::get_public_key() const {
		return public_key;
	}

	void wallet::set_public_key(const std::string& publicKey) {
		public_key = publicKey;
	}

	wallet_transaction& wallet::get_by_uuid(std::string& uuid) {
	}

	std::vector<wallet_transaction> wallet::get_transactions() {
	}

	std::string wallet::to_json() {
	}

} /* namespace zdp */
