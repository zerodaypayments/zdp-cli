/**
 * createwallet --file
 * 		- create a wallet with private/public key pair and metadata
 * walletinfo --file
 * 		- display wallet metadata and transactions
 * 	restorewallet --key or --words
 *		- create a wallet from a private key or a list of words (mnemonics)
 *	sync --file
 *		- synchronize a wallet (balance/transactions)
 *	getaddress --file
 *		- get uniqie address for a wallet
 *
 */
#include <openssl/crypto.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <cstdlib>
#include <ctime>
#include <cwchar>
#include <iomanip>
#include <iostream>
#include <string>

#include "args.hpp"
#include "json.hpp"
#include "utils/crypto_utils.h"
#include "utils/http_utils.h"
#include "utils/key_pair.h"
#include "utils/mnemonics.h"

args::Group arguments("arguments");
args::HelpFlag h(arguments, "help", "help", { 'h', "help" });

using nlohmann::json;

std::string host = "http://localhost";
//std::string host = "http://api.zdp.io";

const auto timeout = 10;
const auto user_agent = "zdp-cli";

int main(int argc, const char **argv) {

	auto random_bytes = zdp::crypto::random(32);

	std::cout << "sha 2: " << zdp::crypto::sha256(random_bytes) << std::endl;

	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << std::endl;


	/*
	 // Load the human readable error strings for libcrypto
	 ERR_load_crypto_strings();

	 // Load all digest and cipher algorithms
	 OpenSSL_add_all_algorithms();

	 // Load config file, and other important initialisation
	 OPENSSL_config(NULL);
	 */

	args::ArgumentParser p("ZDP command line interface (cli)");
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

		/*
		 zdp::utils::httpclient http_client;

		 auto resp = http_client.get(host + "/api/v1/account/new", timeout, user_agent);
		 if (!resp.error) {
		 auto json = json::parse(resp.data);
		 std::cout << json.dump(4) << std::endl;
		 }
		 */

		zdp::key_pair kp;
		std::cout << kp.to_json(zdp::language::english) << std::endl;

		//zdp::crypto::generate_new_key_pair();

	});

	args::Command keys(commands, "publickey", "Generate public key", [&](args::Subparser &parser)
	{

		args::ValueFlag<std::string> key(parser, "PRIVATEKEY", "Private key", {"key"}, args::Options::Required);

		parser.Parse();

		auto priv= args::get(key);

		zdp::key_pair kp (priv);

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
