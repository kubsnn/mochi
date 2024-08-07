#pragma once
#ifndef __APP_GLOBALS_HPP__
#define __APP_GLOBALS_HPP__

#include <string_view>

namespace mochi::globals {
    
    inline const std::string_view name = "cpp-rest-api";

    inline const std::string_view version = "0.0.1";

    inline bool debug = false;

} // namespace app::globals

#endif // !__APP_GLOBALS_HPP__