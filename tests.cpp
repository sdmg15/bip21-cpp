#include "bip21.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace sk::bip21;

TEST_CASE("Decode URIs") {

    static const char* b = "bitcoin:1BgGZ9tcN4rm9KBzDn7KprQz87SZ26SAMH";
    auto [r, e] = decode(b);

    REQUIRE(e.empty());
    REQUIRE(r.address == "1BgGZ9tcN4rm9KBzDn7KprQz87SZ26SAMH");
}