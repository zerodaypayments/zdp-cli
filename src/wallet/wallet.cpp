#include "wallet.h"

#include <iostream>

namespace zdp {

	wallet::wallet() {
		std::cout << "Creating new wallet\n";
	}

	wallet::~wallet() {
	}

	const std::string& wallet::get_name() const {
		return name;
	}

	void wallet::set_name(const std::string& name) {
		this->name = name;
	}

} /* namespace zdp */
