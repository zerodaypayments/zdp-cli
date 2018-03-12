/* Copyright (C) 2018 ZDP Developers - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 *
 * Proprietary and confidential
 *
 * <zdp@zdp.io>
 */

#ifndef UTILS_FILE_UTILS_H_
#define UTILS_FILE_UTILS_H_

#include <string>
#include <vector>

namespace zdp {
	namespace files {

		std::vector<std::string> read_lines(std::string file_name);

		std::string to_string(const std::string file);

	}
}

#endif /* UTILS_FILE_UTILS_H_ */
