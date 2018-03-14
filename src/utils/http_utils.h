/*
 * http_utils.h
 *
 *  Created on: 19Feb.,2018
 */

#ifndef UTILS_HTTP_UTILS_H_
#define UTILS_HTTP_UTILS_H_

#include <curl/curl.h>

#include <string>

namespace zdp {

	namespace utils {

		size_t data_write(void* buf, size_t size, size_t nmemb, void* userp);

		class httpresponse {

			public:
				bool error = false;
				std::string data;
				std::string contentType;
				unsigned int length = -1;

		};

		class httpclient {

			public:

				httpclient();

				~httpclient();

				httpresponse get(std::string url, int timeoutInSeconds, std::string agent);

				httpresponse postJson(std::string url, int timeoutInSeconds, std::string agent, std::string json);

			private:

				CURL* curl = nullptr;

		};

	}
}

#endif /* UTILS_HTTP_UTILS_H_ */
