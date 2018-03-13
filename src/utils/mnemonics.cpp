#include <map>
#include <iostream>

#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/bn.h>
#include <openssl/ec.h>

#include "mnemonics.h"

std::vector<std::string> zdp::generate_mnemonics(zdp::language lang, std::string& key) {

	std::map<language, std::vector<std::string> > words;

	words[language::chinese_simplified] = get_mnemonics_chinese_simplified();
	words[language::chinese_traditional] = get_mnemonics_chinese_traditional();
	words[language::english] = get_mnemonics_english();
	words[language::french] = get_mnemonics_french();
	words[language::italian] = get_mnemonics_italian();
	words[language::japanese] = get_mnemonics_japanese();
	words[language::korean] = get_mnemonics_korean();
	words[language::spanish] = get_mnemonics_spanish();

	std::vector<std::string> words_to_use = words[lang];

	std::vector<std::string> vec;

	BIGNUM* bn = nullptr;

	BN_hex2bn(&bn, key.c_str());

	auto size = BN_num_bytes(bn);

	uint8_t buffer[size];

	BN_bn2bin(bn, buffer);

	BN_free(bn);

	return vec;

}
