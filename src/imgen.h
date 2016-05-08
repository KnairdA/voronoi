#include <string>
#include <utility>
#include <functional>

namespace imgen {

using color = std::tuple<std::uint8_t, std::uint8_t, std::uint8_t>;

void write_ppm(
	const std::string&                             path,
	const std::size_t                              sizeX,
	const std::size_t                              sizeY,
	std::function<color(std::size_t, std::size_t)> generator
);

}
