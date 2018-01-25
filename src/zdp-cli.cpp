#include <iostream>

#include "cxxopts.hpp"

int main(int argc, char* argv[]) {

	try {

		cxxopts::Options options(argv[0], "ZDP command line options");

		//options.positional_help("[optional args]").show_positional_help();

		options.add_options()
			("c, command", "ZDP command to execute", cxxopts::value<std::vector<std::string>>())
			("f, file", "Path to wallet file", cxxopts::value<std::vector<std::string>>(), "file")
			("h, 	help", "Print help");

		//options.parse_positional( { "input", "output", "positional" });

		auto result = options.parse(argc, argv);

		if (result.count("help")) {
			std::cout << options.help( { "", "Group" }) << std::endl;
			exit(0);
		}

		if (result.count("f")) {
			auto& ff = result["f"].as<std::vector<std::string>>();
			std::cout << "Files" << std::endl;
			for (const auto& f : ff) {
				std::cout << f << std::endl;
			}
		}

	} catch (const cxxopts::OptionException& e) {
		std::cerr << "error parsing options: " << e.what() << std::endl;
		exit(1);
	}

	return 0;
}
