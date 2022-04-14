# BIP 21 utility library

```cpp

#include "bip21.hpp"


using namespace sk::bip21;
auto main() -> int {

    std::string s{"bitcoin:1BgGZ9tcN4rm9KBzDn7KprQz87SZ26SAMH"};
    auto [res, err] = decode(s);

    std::cout << res;
}
```