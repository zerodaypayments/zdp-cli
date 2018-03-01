#ifndef UTILS_KEY_PAIR_H_
#define UTILS_KEY_PAIR_H_

#include <string>

#include "mnemonics.h"

namespace zdp {
	
	class key_pair final {

		private:

			std::string private_key;
			std::string public_key;

		private:

			void generate_mnemonics(zdp::language lang);

		public:

			/**
			 * Create a new key pair
			 */
			key_pair();

			/*
			 * Create from an existing private key
			 */
			key_pair(std::string priv_key);

			virtual ~key_pair();

			std::string to_json(zdp::language lang);

			std::string const & get_private_key() const;

			std::string const & get_public_key() const;

	};

} /* namespace zdp */

#endif /* UTILS_KEY_PAIR_H_ */
