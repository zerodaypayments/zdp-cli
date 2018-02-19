/**
 * 	zdp fee - returns <fee>
 *	zdp newaccount - returns <seed>
 *	zdp ping - returns <current time>
 *	zdp keys <seed> - return key pair for the seed
 *	zdp balance <seed> - returns <seed> balance
 *	zdp address <seed> - returns unique address for the transfer
 *	zdp tx <uuid> - returns tx information
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "utils/http_utils.h"
#include "json.hpp"

using nlohmann::json;

void help() {
}

int main(int argc, char** argv) {

	std::vector<std::string> args;

	for (int i = 0; i < argc; ++i) {
		args.push_back(std::string { argv[i] });
	}

	if (args.size() == 1) {
		help();
		return EXIT_SUCCESS;
	}

	std::string host = "http://localhost";

	const auto arg_1 = args[1];

	const auto timeout = 10;
	const auto user_agent = "zdp-cli";

	zdp::utils::httpclient http_client;

	if (arg_1 == "ping") {

		auto resp = http_client.get(host + "/ping", timeout, user_agent);
		std::cout << resp.data << std::endl;

	} else if (arg_1 == "fee") {

		auto resp = http_client.get(host + "/api/v1/fee", timeout, user_agent);
		std::cout << resp.data << std::endl;

	} else if (arg_1 == "newaccount") {

		auto resp = http_client.get(host + "/api/v1/account/seed", timeout, user_agent);
		auto json = json::parse(resp.data);
		std::cout << json.dump(4) << std::endl;

	} else if (arg_1 == "keys") {

		const auto arg_2 = args[2];

		if (args.size() < 3) {
			std::cerr << "Please, specify the <seed> value";
			return EXIT_FAILURE;
		}

		auto resp = http_client.get(host + "/api/v1/account/keys/" + arg_2, timeout, user_agent);
		auto json = json::parse(resp.data);
		std::cout << json.dump(4) << std::endl;

	} else if (arg_1 == "balance") {

		const auto arg_2 = args[2];

		if (args.size() < 3) {
			std::cerr << "Please, specify the <seed> value";
			return EXIT_FAILURE;
		}

		auto resp = http_client.get(host + "/api/v1/seed/balance/" + arg_2, timeout, user_agent);
		auto json = json::parse(resp.data);
		std::cout << json.dump(4) << std::endl;

	} else if (arg_1 == "address") {

		const auto arg_2 = args[2];

		if (args.size() < 3) {
			std::cerr << "Please, specify the <seed> value";
			return EXIT_FAILURE;
		}

		auto resp = http_client.get(host + "/api/v1/seed/address/" + arg_2, timeout, user_agent);
		auto json = json::parse(resp.data);
		std::cout << json.dump(4) << std::endl;

	} else if (arg_1 == "tx") {

		const auto arg_2 = args[2];

		if (args.size() < 3) {
			std::cerr << "Please, specify the <transaction UUID>";
			return EXIT_FAILURE;
		}

		auto resp = http_client.get(host + "/api/v1/tx/" + arg_2, timeout, user_agent);
		auto json = json::parse(resp.data);
		std::cout << json.dump(4) << std::endl;

	};

	return EXIT_SUCCESS;

}
