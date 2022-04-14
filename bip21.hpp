#include <cctype>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>

namespace sk::bip21 {
        
    static auto split(const std::string& str, const char delimiter) -> std::vector<std::string> {
        std::vector<std::string> internal;
        std::stringstream ss(str);
        std::string tok;

        while (getline(ss, tok, delimiter)) {
            internal.push_back(tok);
        }
        return internal;
    }

    static void tolower(std::string& s) {
        for(auto& c: s) {
            std::tolower(c);
        }
    }

    struct Bip21 {
        std::string address;
        std::vector<std::pair<std::string, std::string>> options;

        friend std::ostream& operator<<(std::ostream& os, const Bip21& b) {
            os << "Address ==> " << b.address << "\n";
            for(auto& v: b.options){
                std::cout << v.first << " ==> " << v.second << "\n";
            }
            return os;
        }
    };

    using Error = std::string;

    static auto decode(const std::string& uri) -> std::pair<Bip21, Error> {

        auto it = std::find_if(uri.begin(), uri.end(), [](char c){
            return c == ':';
        });

        std::string schemeComponent{uri.begin(), it};
        tolower(schemeComponent);

        if (schemeComponent != "bitcoin") {
            return {{}, Error{"Unknown URL scheme"}};
        }

        auto queryStrIt = std::find_if(uri.begin(), uri.end(), [](char c){
            return c == '?';
        });

        std::string base58Addr{std::next(it), uri.end()};
        if (queryStrIt == uri.end()) {
            return {Bip21{base58Addr, {}}, {}};
        }

        Bip21 res;
        res.address = base58Addr;

        std::string params{std::next(queryStrIt), uri.end()};
        auto v = split(params, '&');
        for(auto& e: v) {
            auto c = split(e, '=');
            res.options.push_back({c[0], c[1]});
        }
        return {res, {}};
    }
} //namespace sk::bip21