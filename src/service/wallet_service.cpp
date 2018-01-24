/* Copyright (C) 2018 Ivelle Games - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 *
 * Proprietary and confidential
 *
 * <ivelle@qaxml.com>
 */

#include "wallet_service.h"
#include "../wallet/wallet.h"

namespace zdp {

	wallet_service::wallet_service() {
		// TODO Auto-generated constructor stub

	}

	wallet_service::~wallet_service() {
		// TODO Auto-generated destructor stub
	}

	zdp::wallet wallet_service::create_new_wallet(const std::string& name) const {

		zdp::wallet w;
		w.set_name(name);

		return w;

	}

} /* namespace zdp */
