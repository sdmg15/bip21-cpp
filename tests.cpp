#include "bip21.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace sk::bip21;

TEST_CASE("Decode URIs") {

    static const char* b = "bitcoin:1BgGZ9tcN4rm9KBzDn7KprQz87SZ26SAMH";
    auto [r, e] = decode(b);

    REQUIRE(e.empty());
    REQUIRE(r.address == "1BgGZ9tcN4rm9KBzDn7KprQz87SZ26SAMH");


    static const char* customScheme = "bitcoin://1BgGZ9tcN4rm9KBzDn7KprQz87SZ26SAMH";
    auto [res, err] = decode(customScheme, "bitcoin://");

    REQUIRE(err.empty());
    REQUIRE(res.address == "1BgGZ9tcN4rm9KBzDn7KprQz87SZ26SAMH");
}

TEST_CASE("Encode") {

    const auto res = encode("1BgGZ9tcN4rm9KBzDn7KprQz87SZ26SAMH", std::nullopt, std::nullopt);
    REQUIRE(res == "bitcoin:1BgGZ9tcN4rm9KBzDn7KprQz87SZ26SAMH");

    const auto res2 = encode("1BgGZ9tcN4rm9KBzDn7KprQz87SZ26SAMH", "bitcoin://", std::nullopt);
    REQUIRE(res2 == "bitcoin://1BgGZ9tcN4rm9KBzDn7KprQz87SZ26SAMH");

    Component c = { {"amount", "0.23"}, {"label", "foobar"}, {"message", "donation"} };

    const auto res3 =  encode("1BgGZ9tcN4rm9KBzDn7KprQz87SZ26SAMH", std::nullopt, c);
    
    REQUIRE(res3 == "bitcoin:1BgGZ9tcN4rm9KBzDn7KprQz87SZ26SAMH?amount=0.23&label=foobar&message=donation");

    const auto withscheme =  encode("1BgGZ9tcN4rm9KBzDn7KprQz87SZ26SAMH", "satoshi:", c);

    REQUIRE(withscheme == "satoshi:1BgGZ9tcN4rm9KBzDn7KprQz87SZ26SAMH?amount=0.23&label=foobar&message=donation");
}