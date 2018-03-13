/* Copyright (C) 2018 ZDP Developers - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 *
 * Proprietary and confidential
 *
 * <zdp@zdp.io>
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "file_utils.h"

namespace zdp {

	namespace files {

		std::vector<std::string> read_lines(const std::string& file_name) {

			std::vector<std::string> lines;

			// read map file to vector
			std::ifstream infile(file_name);

			std::string line;
			for (std::string line; std::getline(infile, line);) {
				lines.push_back(line);
			}

			return lines;

		}

		std::string to_string(const std::string& file) {

			std::cout << "Read string from file [" << file << "]" << std::endl;

			std::ifstream t(file);

			std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

			return str;

		}

	}

	void write_string_to_file(std::string const & file_name, std::string const & content) {

		std::cout << "Write string to file [" << file_name << "]" << std::endl;

		std::ofstream file(file_name);
		file << content;

	}

}

