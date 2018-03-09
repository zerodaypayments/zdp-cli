// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

/**
 * Why base-58 instead of standard base-64 encoding?
 * - Don't want 0OIl characters that look the same in some fonts and
 *      could be used to create visually identical looking data.
 * - A string with non-alphanumeric characters is not as easily accepted as input.
 * - E-mail usually won't line-break if there's no punctuation to break at.
 * - Double-clicking selects the whole string as one word if it's all alphanumeric.
 */
#ifndef BITCOIN_BASE58_H
#define BITCOIN_BASE58_H

#include <string>
#include <vector>

namespace zdp {

	namespace base58 {

		/**
		 * Encode a byte sequence as a base58-encoded string.
		 * pbegin and pend cannot be nullptr, unless both are.
		 */
		std::string encode_base(const unsigned char* pbegin, const unsigned char* pend);

		/**
		 * Encode a byte vector as a base58-encoded string
		 */
		std::string encode_base(const std::vector<unsigned char>& vch);

		/**
		 * Decode a base58-encoded string (psz) into a byte vector (vchRet).
		 * return true if decoding is successful.
		 * psz cannot be nullptr.
		 */
		bool decode_base(const char* psz, std::vector<unsigned char>& vchRet);

		/**
		 * Decode a base58-encoded string (str) into a byte vector (vchRet).
		 * return true if decoding is successful.
		 */
		bool decode_base(const std::string& str, std::vector<unsigned char>& vchRet);

	}
}
#endif // BITCOIN_BASE58_H
