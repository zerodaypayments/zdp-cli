/**
 * 	zdp fee - returns <fee>
 *	zdp newaccount <language> - returns <secretkey>
 *	zdp ping - returns <current time>
 *	zdp keys <secretkey> - return key pair for the seed
 *	zdp balance <secretkey> - returns <seed> balance
 *	zdp newaddress <secretkey> - returns unique address for the transfer
 *	zdp tx <uuid> - returns tx information
 *	TODO zdp restore <comma-separated-list-of-words> - returns seed
 *	TODO zdp transfer --key <secretkey> --amount <amount> <from> <to> <amount> <memo>  - return TX UUID or error
 *	TODO zdp txfrom <address>
 *	TODO zdp txto <address>
 *	TODO zdp txfrommemo <from> <memo>
 *	TODO zdp txtomemo <to> <memo>
 *	TODO zdp txlist <seed> [number-of-transactions] - returns last of max of 100 latest tx
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
//	std::string host = "http://api.zdp.io";

	const auto arg_1 = args[1];

	const auto timeout = 10;
	const auto user_agent = "zdp-cli";

	zdp::utils::httpclient http_client;

	if (arg_1 == "ping") {

		auto resp = http_client.get(host + "/ping", timeout, user_agent);
		if (!resp.error) {
			auto json = json::parse(resp.data);
			std::cout << json.dump(4) << std::endl;
		}

	} else if (arg_1 == "fee") {

		auto resp = http_client.get(host + "/api/v1/fee", timeout, user_agent);
		if (!resp.error) {
			auto json = json::parse(resp.data);
			std::cout << json.dump(4) << std::endl;
		}

	} else if (arg_1 == "newaccount") {

		auto url = host + "/api/v1/account/seed";

		if (args.size() == 3) {
			url += "?lang=" + args[2];
		}

		auto resp = http_client.get(url, timeout, user_agent);

		if (!resp.error) {
			auto json = json::parse(resp.data);
			std::cout << json.dump(4) << std::endl;
		}

	} else if (arg_1 == "keys") {

		if (args.size() < 3) {
			std::cerr << "Please, specify the <seed> value\n";
			return EXIT_FAILURE;
		}

		const auto arg_2 = args[2];

		auto resp = http_client.get(host + "/api/v1/account/keys/" + arg_2, timeout, user_agent);
		if (!resp.error) {
			auto json = json::parse(resp.data);
			std::cout << json.dump(4) << std::endl;
		}

	} else if (arg_1 == "balance") {

		if (args.size() < 3) {
			std::cerr << "Please, specify the <seed> value\n";
			return EXIT_FAILURE;
		}

		const auto arg_2 = args[2];

		auto resp = http_client.get(host + "/api/v1/seed/balance/" + arg_2, timeout, user_agent);
		if (!resp.error) {
			auto json = json::parse(resp.data);
			std::cout << json.dump(4) << std::endl;
		}

	} else if (arg_1 == "newaddress") {

		const auto arg_2 = args[2];

		if (args.size() < 3) {
			std::cerr << "Please, specify the <seed> value\n";
			return EXIT_FAILURE;
		}

		auto resp = http_client.get(host + "/api/v1/seed/address/" + arg_2, timeout, user_agent);
		if (!resp.error) {
			auto json = json::parse(resp.data);
			std::cout << json.dump(4) << std::endl;
		}

	} else if (arg_1 == "tx") {

		if (args.size() < 3) {
			std::cerr << "Please, specify the <transaction UUID>\n";
			return EXIT_FAILURE;
		}

		const auto arg_2 = args[2];

		auto resp = http_client.get(host + "/api/v1/tx/" + arg_2, timeout, user_agent);

		if (!resp.error) {

			auto json = json::parse(resp.data);
			std::cout << json.dump(4) << std::endl;
		}

	};

	return EXIT_SUCCESS;

}

