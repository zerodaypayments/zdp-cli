/* 
 * Copyright (C) 2018 ZDP Developers - All Rights Reserved
 *  _________  ____  
 * |__  /  _ \|  _ \ 
 *   / /| | | | |_) |
 *  / /_| |_| |  __/ 
 * /____|____/|_|    
 *
 * <zdp@zdp.io>
 */

#include "wallet_service.h"

#include <iostream>

#include "../utils/key_pair.h"
#include "../utils/file_utils.h"

namespace zdp {

	wallet_service::wallet_service() {
		// TODO Auto-generated constructor stub

	}

	wallet_service::~wallet_service() {
		// TODO Auto-generated destructor stub
	}

	wallet wallet_service::load_wallet(std::string& file_name) {
	}

	wallet wallet_service::restore_wallet(std::string& file_name, std::string& private_key) {
	}

	wallet wallet_service::create_wallet(std::string& file_name, zdp::language language) {

		std::cout << "Creating new wallet: " << file_name << std::endl;

		zdp::key_pair kp;

//		zdp::files::write_string_to_file(file_name, kp.to_json(language));

	}

	wallet wallet_service::restore_wallet(std::string& file_name, std::vector<std::string> mnemonics) {
		wallet w;
		return w;
	}

} /* namespace zdp */
