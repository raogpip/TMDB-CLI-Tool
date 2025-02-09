#include <iostream>
#include <nlohmann/json.hpp>
#include <curl/curl.h>

using json = nlohmann::json;

std::string get_api_key();
std::string get_api_access_token();
void get_movies(std::string type, const std::string api_access_token);
void printMovies(nlohmann::json j);
size_t json_callback(void* contents, size_t size, size_t nmemb, void* userp);

int main(int argc, char* argv[])
{
	std::string api_key = get_api_key();
	const std::string api_access_token = get_api_access_token();
	if (argc < 3) {
		std::cerr << "Usage: tmdb-app --type <type>" << std::endl;
		return 1;
	}

	std::string type;
	for (int i = 1; i < argc; ++i) {
		if (std::string(argv[i]) == "--type") {
			if (i + 1 < argc) {
				type = argv[i + 1];
			}
			else {
				std::cerr << "Error: No type provided after --type" << std::endl;
				return 1;
			}
		}
	}

	if (type == "playing" || type == "popular" || type == "top" || type == "upcoming") {
		get_movies(type, api_access_token);
	}
	else {
		std::cerr << "Invalid type. Choose from: playing, popular, top, upcoming." << std::endl;
	}
}

size_t json_callback(void* contents, size_t size, size_t nmemb, void* userp) {
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

void get_movies(std::string type, const std::string api_access_token) {
	if (type == "playing") type = "now_playing";
	
	CURL* handle = curl_easy_init();
	
	std::string url = "https://api.themoviedb.org/3/movie/"+type;
	std::string buffer = "Authorization: Bearer " + api_access_token;
	const char* curl_header = buffer.c_str();
	std::string response_data;
	
	if (handle) {
		curl_easy_setopt(handle, CURLOPT_CUSTOMREQUEST, "GET");
		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, json_callback);
		curl_easy_setopt(handle, CURLOPT_WRITEDATA, &response_data);
		curl_easy_setopt(handle, CURLOPT_URL, url.c_str());

		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "accept: application/json");
		headers = curl_slist_append(headers, curl_header);
		curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);

		CURLcode result = curl_easy_perform(handle);
		if (result != CURLE_OK) {
			std::cout << "CURL ERROR: " << curl_easy_strerror(result) << std::endl;
		}
		else {

			int http_code = 0;
			curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &http_code);

			if (http_code == 200) {
				auto json_response = nlohmann::json::parse(response_data);
				printMovies(json_response);
			}
			else {
				std::cerr << "API Error: HTTP Status Code " << http_code << '\n';
				if (http_code == 401) {
					std::cerr << "Unauthorized: Invalid API key or token." << std::endl;
				}
				else if (http_code == 404) {
					std::cerr << "Not Found: The requested resource does not exist." << std::endl;
				}
				else if (http_code >= 500) {
					std::cerr << "Server Error: Something went wrong on the server side." << std::endl;
				}
			}
		}

		curl_easy_cleanup(handle);
		curl_slist_free_all(headers);
	}
}

void printMovies(nlohmann::json j) {
	for (const auto &movie : j["results"]) {
		std::cout << movie["original_title"] << "\n";
	}
}

std::string get_api_key() {
	char* env_var_value = nullptr;
	size_t len = 0;
	
	if (_dupenv_s(&env_var_value, &len, "TMDB_API_KEY") == 0 && env_var_value != nullptr) {
		std::string api_key(env_var_value);
		free(env_var_value);
		return api_key;
	}
	else {
		return "";
	}
}

std::string get_api_access_token() {
	char* env_var_value = nullptr;
	size_t len = 0;

	if (_dupenv_s(&env_var_value, &len, "TMDB_ACCESS_TOKEN") == 0 && env_var_value != nullptr) {
		std::string api_access_token(env_var_value);
		free(env_var_value);
		return api_access_token;
	}
	else {
		return "";
	}
}