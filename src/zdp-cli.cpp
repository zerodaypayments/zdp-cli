#include <iostream>

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#include "args.hpp"
#include "utils/http_utils.h"
#include "utils/crypto_utils.h"
#include "utils/key_pair.h"
#include "json.hpp"

args::Group arguments("arguments");
args::HelpFlag h(arguments, "help", "help", { 'h', "help" });

using nlohmann::json;

std::string host = "http://localhost";
//	std::string host = "http://api.zdp.io";

const auto timeout = 10;
const auto user_agent = "zdp-cli";

int main(int argc, const char **argv) {

/*
	// Load the human readable error strings for libcrypto
	ERR_load_crypto_strings();

	// Load all digest and cipher algorithms
	OpenSSL_add_all_algorithms();

	// Load config file, and other important initialisation
	OPENSSL_config(NULL);
	*/

	std::string key = "03F15CA200C6683D0469F39A58ECD93B39ECA2E4D4204095D99C32DF292F7867B4";
	std::string text = "hello world!";

	// unsigned char* t = reinterpret_cast<unsigned char *>( text.c_str()  );

	//auto enc = ecies_encrypt(const_cast<char*> (key.c_str() ), t , text.size());

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

		parser.Parse();

		/*
		 args::ValueFlag<std::string> lang(parser, "LANGUAGE", "Mnemonics language", {"lang"}, "english");

		 parser.Parse();

		 auto language = args::get(lang);
		 */

		zdp::key_pair kp;
		std::cout << kp.to_json(zdp::language::english) << std::endl;

	});

	args::Command keys(commands, "publickey", "Generate public key", [&](args::Subparser &parser)
	{

		args::ValueFlag<std::string> keyValue(parser, "PRIVATEKEY", "Private key", {"key"}, args::Options::Required);

		parser.Parse();

		auto key = args::get(keyValue);

		zdp::key_pair kp (key);
		std::cout << kp.to_json(zdp::language::english) << std::endl;

	});

	args::Command balance(commands, "balance", "Get account's balance", [&](args::Subparser &parser)
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

	// Removes all digests and ciphers
	EVP_cleanup();

	// if you omit the next, a small leak may be left when you make use of the BIO (low level API) for e.g. base64 transformations
	CRYPTO_cleanup_all_ex_data();

	// Remove error strings
	ERR_free_strings();

	return EXIT_SUCCESS;
}
