#pragma once

#include <string>
#include <functional>

#include "color.h"

namespace imgen {

using vector         = std::tuple<std::ptrdiff_t, std::ptrdiff_t>;
using colored_vector = std::tuple<std::ptrdiff_t, std::ptrdiff_t, color>;

void write_ppm(
	const std::string&                                   path,
	const std::size_t                                    sizeX,
	const std::size_t                                    sizeY,
	std::function<color(std::ptrdiff_t, std::ptrdiff_t)> generator
);

}
