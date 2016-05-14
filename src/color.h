#pragma once

#include <tuple>
#include <cstdint>

namespace imgen {

using color = std::tuple<std::uint8_t, std::uint8_t, std::uint8_t>;

color red();
color lime();
color blue();
color yellow();
color cyan();
color magenta();
color silver();
color maroon();
color olive();
color green();
color purple();
color teal();
color navy();

}
