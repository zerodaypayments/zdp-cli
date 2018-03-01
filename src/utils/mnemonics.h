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

}

#endif /* UTILS_MNEMONICS_H_ */
