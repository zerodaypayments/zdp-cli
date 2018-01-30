/**
 * 	zdp wallet create <wallet-file> <private-key>
 *
 * 	zdp wallet balance <walletfile> <password>
 * 	zdp wallet dumpprivkeys <walletfile> <password> <filename>
 * 	zdp wallet encrypt <walletfile> <oldpassword> <newpassword>
 *
 * 	zdp wallet address add-existing <seed> <walletfile> <password>
 * 	zdp wallet address add-new <walletfile> <password>
 * 	zdp wallet address delete <address> <walletfile> <password>
 * 	zdp wallet address list <address> <walletfile> <password>
 *
 * 	zdp address get-new
 * 	zdp address get-existing <seed>
 * 	zdp address balance <address> <
 *
 * 	zdp tx <uuid>
 * 	gettransaction <txid>							Produces a human-readable JSON object for a transaction.
 *	dumpprivkey <address>							Reveals the private key corresponding to <address>
 * 	dumpwallet <filename>							Exports all wallet private keys to file
 *	encryptwallet <oldpassphrase> <newpassphrase> 	Encrypts the wallet with <passphrase>.
 *	getaddress	<address>							Returns the address details.
 *  getnewaddress									Creates a new address
 *	getbalance  <address>							Returns address balanc
 *
 *	Common flags:
 *		-v, --verbose
 *		-ver, --version
 *
 */

#include <iostream>
#include <string>
#include <vector>

const auto app_version = 1.023;

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

	if (args[1] == "wallet") {
		std::cout << "wallet\n";
	}

	return EXIT_SUCCESS;

}
