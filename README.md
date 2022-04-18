# BIP 21 utility library

```cpp

#include "bip21.hpp"


using namespace sk::bip21;
auto main() -> int {

    // Decoding 
    std::string s{"bitcoin:1BgGZ9tcN4rm9KBzDn7KprQz87SZ26SAMH"};
    auto [res, err] = decode(s);

    std::cout << res;

    // Encoding 
    Component c = { {"amount", "0.23"}, {"label", "foobar"}, {"message", "donation"} };
    const auto encoded =  encode("1BgGZ9tcN4rm9KBzDn7KprQz87SZ26SAMH", std::nullopt, c);

    std::cout << encoded; // bitcoin:1BgGZ9tcN4rm9KBzDn7KprQz87SZ26SAMH?amount=0.23&label=foobar&message=donation
}
```