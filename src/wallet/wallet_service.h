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

#ifndef WALLET_WALLET_SERVICE_H_
#define WALLET_WALLET_SERVICE_H_

#include <string>
#include <vector>

#include "../utils/mnemonics.h"
#include "wallet.h"


namespace zdp {

	class wallet_service final {

		public:

			wallet_service();
			~wallet_service();

			wallet create_wallet(std::string& file_name, zdp::language language);
			wallet load_wallet(std::string& file_name);
			wallet restore_wallet(std::string& file_name, std::string& private_key);
			wallet restore_wallet(std::string& file_name, std::vector<std::string> mnemonics);


	};

} /* namespace zdp */

#endif /* WALLET_WALLET_SERVICE_H_ */
