#include <iostream>
#include <nlohmann/json.hpp>
#include <curl/curl.h>


using json = nlohmann::json;

int main()
{
	CURL* curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com");
		CURLcode result = curl_easy_perform(curl);
		if (result != CURLE_OK)
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(result) << '\n';
		curl_easy_cleanup(curl);
	}
}

