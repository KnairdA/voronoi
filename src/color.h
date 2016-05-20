#pragma once

#include <tuple>
#include <cstdint>

namespace imgen {

using color = std::tuple<std::uint8_t, std::uint8_t, std::uint8_t>;

constexpr color black()   { return color{  0,   0,   0}; }
constexpr color white()   { return color{255, 255, 255}; }
constexpr color red()     { return color{255,   0,   0}; }
constexpr color lime()    { return color{  0, 255,   0}; }
constexpr color blue()    { return color{  0,   0, 255}; }
constexpr color yellow()  { return color{255, 255,   0}; }
constexpr color cyan()    { return color{  0, 255, 255}; }
constexpr color magenta() { return color{255,   0, 255}; }
constexpr color silver()  { return color{192, 192, 192}; }
constexpr color maroon()  { return color{128,   0,   0}; }
constexpr color olive()   { return color{128, 128,   0}; }
constexpr color green()   { return color{  0, 128,   0}; }
constexpr color purple()  { return color{128,   0, 128}; }
constexpr color teal()    { return color{  0, 128, 128}; }
constexpr color navy()    { return color{  0,   0, 128}; }

}
