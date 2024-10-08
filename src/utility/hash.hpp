#pragma once
#ifndef MOCHI_UTILITY_HASH_HPP
#define MOCHI_UTILITY_HASH_HPP

#include <boost/beast.hpp>
#include <string>

template <>
struct std::hash<std::pair<boost::beast::http::verb, std::string>> {
    inline std::size_t operator()(const std::pair<boost::beast::http::verb, std::string>& key) const {
        std::size_t seed = 0;
        boost::hash_combine(seed, key.first);
        boost::hash_combine(seed, key.second);
        return seed;
    }
};

#endif // !MOCHI_UTILITY_HASH_HPP