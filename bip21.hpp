#include <cctype>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include <optional>

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

    using Component = std::vector<std::pair<std::string, std::string>>;
    struct Bip21 {
        std::string address;
        Component options;

        friend std::ostream& operator<<(std::ostream& os, const Bip21& b) {
            os << "Address ==> " << b.address << "\n";
            for(auto& v: b.options){
                std::cout << v.first << " ==> " << v.second << "\n";
            }
            return os;
        }
    };

    using Error = std::string;
    using Result = std::pair<Bip21, Error>;

    static auto decode(const std::string& uri, std::optional<std::string> customScheme) -> Result {

        std::string schemeToUse = "bitcoin:";

        if (customScheme) {
            schemeToUse = customScheme.value();
        }

        auto it = std::find_if(uri.begin(), uri.end(), [](char c){
            return c == ':';
        });

        std::string schemeComponent{uri.begin(), it};
        tolower(schemeComponent);

        auto queryStrIt = std::find_if(uri.begin(), uri.end(), [](char c){
            return c == '?';
        });

        std::string base58Addr{uri.begin() + schemeToUse.size(), uri.end()};
        if (queryStrIt == uri.end()) {
            return {Bip21{base58Addr, {}}, {}};
        }

        Bip21 res;
        res.address = std::move(base58Addr);

        std::string params{std::next(queryStrIt), uri.end()};
        auto v = split(params, '&');
        for(auto& e: v) {
            auto c = split(e, '=');
            res.options.push_back({c[0], c[1]});
        }
        return {res, {}};
    }

    static auto decode(const std::string& uri) -> Result {
        return decode(uri, std::nullopt);
    }


    static auto encode(const std::string& addr, std::optional<std::string> scheme,
                       std::optional<Component> components) -> std::string {
        
        if (!scheme) {
            std::string r{"bitcoin:" + addr};
            if (components) {
                ushort i{0}; 
                r += "?";
                for (const auto& v: components.value()) {
                    i++ == 0? r += v.first + "=" + v.second : r += "&"+v.first + "=" + v.second;
                }
            }
            return r; 
        }

        std::string r{scheme.value() + addr};
        if (components) {
            ushort i{0}; 
            r += "?";
            for (const auto& v: components.value()) {
                i++ == 0? r += v.first + "=" + v.second : r += "&"+v.first + "=" + v.second;
            }
        }
        return r;

    }
} //namespace sk::bip21