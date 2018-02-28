#include <iostream>
#include "args.hpp"
#include "utils/http_utils.h"
#include "utils/crypto_utils.h"
#include "json.hpp"
#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/bn.h>
#include <openssl/ec.h>

args::Group arguments("arguments");
args::HelpFlag h(arguments, "help", "help", { 'h', "help" });

using nlohmann::json;

std::string host = "http://localhost";
//	std::string host = "http://api.zdp.io";

const auto timeout = 10;
const auto user_agent = "zdp-cli";

int main(int argc, const char **argv) {

	uint8_t buffer[32];

	int rc = RAND_bytes(buffer, sizeof(buffer));
	unsigned long err = ERR_get_error();

	if(rc != 1) {
		std::cerr << "Can't generate random number\n";
	} else {
		std::cout << "Generated random number\n";
	}

	auto key = zdp::crypto::bbp_ec_new_keypair(buffer);

	{
		auto priv_bn = EC_KEY_get0_private_key(key);
		auto str = BN_bn2hex(priv_bn);
		std::cout << "Private key: " << std::string(str) << std::endl;
	}

	{
		auto pub_bn = EC_KEY_get0_public_key(key);
		auto str = EC_POINT_point2hex(EC_KEY_get0_group(key), EC_KEY_get0_public_key(key), point_conversion_form_t::POINT_CONVERSION_COMPRESSED, nullptr);
		std::cout << "Public key: " << std::string(str) << std::endl;
	}

/*
	args::ArgumentParser p("ZDP command line interface");
	args::Group commands(p, "commands");

	args::Command fee(commands, "fee", "Get the current network fee", [&](args::Subparser &parser)
	{

		parser.Parse();

		zdp::utils::httpclient http_client;

		auto resp = http_client.get(host + "/api/v1/fee", timeout, user_agent);

		if (!resp.error) {
			auto json = json::parse(resp.data);
			std::cout << json.dump(4) << std::endl;
		}

	});

	args::Command ping(commands, "ping", "Ping the network", [&](args::Subparser &parser)
	{

		parser.Parse();

		zdp::utils::httpclient http_client;

		auto resp = http_client.get(host + "/ping", timeout, user_agent);
		if (!resp.error) {
			auto json = json::parse(resp.data);
			std::cout << json.dump(4) << std::endl;
		}

	});

	args::Command newAccount(commands, "newaccount", "Create new account", [&](args::Subparser &parser)
	{

		args::ValueFlag<std::string> lang(parser, "LANGUAGE", "Mnemonics language", {"lang"});

		parser.Parse();

		auto url = host + "/api/v1/account/seed";

		auto language = args::get(lang);

		url += "?lang=" + language;

		zdp::utils::httpclient http_client;

		auto resp = http_client.get(url, timeout, user_agent);

		if (!resp.error) {
			auto json = json::parse(resp.data);
			std::cout << json.dump(4) << std::endl;
		}

	});

	args::Command keys(commands, "keys", "Generate public and private key pair for a secret key", [&](args::Subparser &parser)
	{

		args::ValueFlag<std::string> keyValue(parser, "SECRETKEY", "Secret key", {"key"}, args::Options::Required);

		parser.Parse();

		auto key = args::get(keyValue);

		zdp::utils::httpclient http_client;

		auto resp = http_client.get(host + "/api/v1/account/keys/" + key, timeout, user_agent);
		if (!resp.error) {
			auto json = json::parse(resp.data);
			std::cout << json.dump(4) << std::endl;
		}

	});

	args::Command balance(commands, "balance", "Get account's balance by a secret key", [&](args::Subparser &parser)
	{

		args::ValueFlag<std::string> keyValue(parser, "SECRETKEY", "Secret key", {"key"}, args::Options::Required);

		parser.Parse();

		auto key = args::get(keyValue);

		zdp::utils::httpclient http_client;

		auto resp = http_client.get(host + "/api/v1/seed/balance/" + key, timeout, user_agent);
		if (!resp.error) {
			auto json = json::parse(resp.data);
			std::cout << json.dump(4) << std::endl;
		}

	});

	args::Command address(commands, "newaddress", "Generate a unique address for an existing account", [&](args::Subparser &parser)
	{

		args::ValueFlag<std::string> keyValue(parser, "SECRETKEY", "Secret key", {"key"}, args::Options::Required);

		parser.Parse();

		auto key = args::get(keyValue);

		zdp::utils::httpclient http_client;

		auto resp = http_client.get(host + "/api/v1/address/" + key, timeout, user_agent);
		if (!resp.error) {
			auto json = json::parse(resp.data);
			std::cout << json.dump(4) << std::endl;
		}

	});

	args::Command tx(commands, "tx", "Get transaction information by UUID", [&](args::Subparser &parser)
	{

		args::ValueFlag<std::string> uuidValue(parser, "UUID", "Transaction UUID", {"uuid"}, args::Options::Required);

		parser.Parse();

		auto uuid = args::get(uuidValue);

		zdp::utils::httpclient http_client;

		auto resp = http_client.get(host + "/api/v1/tx/" + uuid, timeout, user_agent);

		if (!resp.error) {

			auto json = json::parse(resp.data);
			std::cout << json.dump(4) << std::endl;
		}

	});

	args::GlobalOptions globals(p, arguments);

	try {
		p.ParseCLI(argc, argv);
	} catch (args::Help) {
		std::cout << p;
	} catch (args::Error& e) {
		std::cerr << e.what() << std::endl << p;
		return EXIT_FAILURE;
	}

	*/
	return EXIT_SUCCESS;
}
