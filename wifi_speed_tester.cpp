#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <curl/curl.h>
#include <rapidjson/document.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

using namespace std;
using namespace rapidjson;

size_t curl_callback(void* contents, size_t size, size_t nmemb, string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*) contents, newLength);
    }
    catch (std::bad_alloc &e) {
        cerr << RED << "Error allocating memory for download: " << e.what() << RESET << endl;
        return 0;
    }
    return newLength;
}

string get_wifi_location() {
    CURL* curl;
    CURLcode res;
    string response_string;
    string wifi_location_url = "https://ipinfo.io/json";

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, wifi_location_url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.69.1");
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res == CURLE_OK) {
            return response_string;
        } else {
            cerr << RED << "Error getting wifi location: " << curl_easy_strerror(res) << RESET << endl;
            return "";
        }
    } else {
        cerr << RED << "Error initializing curl" << RESET << endl;
        return "";
    }
}

void show_wifi_info(string wifi_info) {
    Document doc;
    doc.Parse(wifi_info.c_str());
    if (doc.HasParseError()) {
        cerr << RED << "Error parsing wifi info JSON" << RESET << endl;
        return;
    }

    string lat_long = doc["loc"].GetString();
    string google_maps_url = "https://www.google.com/maps/search/?api=1&query=" + lat_long;

    cout << CYAN << "\nWifi Information:" << RESET << endl;
    cout << "Location: " << BLUE << doc["city"].GetString() << ", " << doc["region"].GetString() << ", " << doc["country"].GetString() << RESET << endl;
    cout << "IP Address: " << YELLOW << doc["ip"].GetString() << RESET << endl;
    cout << "ISP: " << MAGENTA << doc["org"].GetString() << RESET << endl;
    cout << "Google Maps URL: " << GREEN << google_maps_url << RESET << endl;
}

void show_banner() {
    cout << GREEN << "**********************************" << RESET << endl;
    cout << GREEN << "*                                *" << RESET << endl;
    cout << GREEN << "*        Wifi Speed Tester       *" << RESET << endl;
    cout << GREEN << "*              BY Mr Sami        *" << RESET << endl;
    cout << GREEN << "**********************************" << RESET << endl;
}

int main() {
    show_banner();
    string wifi_info = get_wifi_location();
    if (!wifi_info.empty()) {
        show_wifi_info(wifi_info);
    }
    return 0;
}
