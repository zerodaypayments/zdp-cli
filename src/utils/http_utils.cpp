/*
 * http_utils.cpp
 *
 *  Created on: 19Feb.,2018
 *      Author: sxn144
 */

#include <curl/curl.h>

#include <iostream>
#include <string>
#include <ostream>
#include <sstream>

#include "http_utils.h"

namespace zdp {

	namespace utils {

		size_t data_write(void* buf, size_t size, size_t nmemb, void* userp) {
			if (userp) {
				std::ostream& os = *static_cast<std::ostream*>(userp);
				std::streamsize len = size * nmemb;
				if (os.write(static_cast<char*>(buf), len))
					return len;
			}

			return 0;
		}

		httpclient::httpclient() {
			this->curl = curl_easy_init();
		}

		httpclient::~httpclient() {
			if (curl != nullptr) {
				curl_easy_cleanup(curl);
			}
		}


		httpresponse httpclient::post(std::string& url, int timeoutInSeconds, std::string& agent, std::string& json) {

		}

		httpresponse httpclient::get(std::string& url, int timeoutInSeconds, std::string& agent) {

//			std::cout << "HTTP Get [" << url << "] with [" << agent << "]" << std::endl;

			std::ostringstream stream;

//			curl_easy_setopt(curl, CURLOPT_PROXY, "http://eisproxyau:8080");

			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &data_write);
			curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
			curl_easy_setopt(curl, CURLOPT_FILE, &stream);
			curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeoutInSeconds);
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_USERAGENT, agent.c_str());

			httpresponse response;

			CURLcode res = curl_easy_perform(curl);

			if (res != CURLE_OK) {

				std::cerr << "Cannot connect to the network" << std::endl;
				response.error = true;

			} else {

				if (CURLE_OK == res) {

					char *ct;
					/* ask for the content-type */
					res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);

					if ((CURLE_OK == res) && ct) {
						response.contentType = std::string(ct);
					}

					response.data = stream.str();
					response.length = response.data.size();

//					std::cout << "Got response type: " << response.contentType << std::endl;
//					std::cout << "Got response length: " << std::to_string(response.length) << std::endl;
//					std::cout << "Got response: " << response.data << std::endl;

				}
			}

			return response;

		}

	}
}
