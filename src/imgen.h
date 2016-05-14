#include <string>
#include <utility>
#include <fstream>
#include <functional>

namespace imgen {

using color = std::tuple<std::uint8_t, std::uint8_t, std::uint8_t>;

class ppm_pixel_stream {
	public:
		ppm_pixel_stream(const std::string& path,
		                 const std::size_t  width,
		                 const std::size_t  height);

		ppm_pixel_stream& operator<<(const color& value);

	private:
		std::ofstream stream_;

};

void write_ppm(
	const std::string&                                   path,
	const std::size_t                                    sizeX,
	const std::size_t                                    sizeY,
	std::function<color(std::ptrdiff_t, std::ptrdiff_t)> generator
);

}
