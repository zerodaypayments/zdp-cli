#ifndef UTILS_MNEMONICS_H_
#define UTILS_MNEMONICS_H_

#include <string>
#include <vector>

namespace zdp {

	enum class language {
		chinese_simplified, //
		chinese_traditional, //
		english, //
		french, //
		italian, //
		japanese, //
		korean, //
		spanish //
	};

	std::vector<std::string> generate_mnemonics(language lang, std::string& key);

	std::vector<std::string> get_mnemonics_chinese_simplified();
	std::vector<std::string> get_mnemonics_chinese_traditional();
	std::vector<std::string> get_mnemonics_english();
	std::vector<std::string> get_mnemonics_french();
	std::vector<std::string> get_mnemonics_italian();
	std::vector<std::string> get_mnemonics_japanese();
	std::vector<std::string> get_mnemonics_korean();
	std::vector<std::string> get_mnemonics_spanish();

}

#endif /* UTILS_MNEMONICS_H_ */
