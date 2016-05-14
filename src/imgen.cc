#include "imgen.h"

namespace {

inline void write_color(std::ofstream& out, const imgen::color& color) {
	out << std::get<0>(color)
	    << std::get<1>(color)
	    << std::get<2>(color);
}

}

namespace imgen {

ppm_pixel_stream::ppm_pixel_stream(
	const std::string& path,
	const std::size_t  width,
	const std::size_t  height
): stream_() {
	this->stream_.open(path, std::ios::binary | std::ios::out);
	this->stream_.sync_with_stdio(false);

	this->stream_ << "P6\n" << width << " " << height << "\n255\n";
}

ppm_pixel_stream& ppm_pixel_stream::operator<<(const color& value) {
	write_color(this->stream_, value);

	return *this;
}

void write_ppm(
	const std::string&                                   path,
	const std::size_t                                    width,
	const std::size_t                                    height,
	std::function<color(std::ptrdiff_t, std::ptrdiff_t)> generator
) {
	ppm_pixel_stream file(path, width, height);

	const std::ptrdiff_t min_y = height / 2 * -1;
	const std::ptrdiff_t max_y = height / 2;
	const std::ptrdiff_t min_x = width  / 2 * -1;
	const std::ptrdiff_t max_x = width  / 2;

	for ( std::ptrdiff_t posY = min_y; posY < max_y; ++posY ) {
		for ( std::ptrdiff_t posX = min_x; posX < max_x; ++posX ) {
			file << generator(posX, posY);
		}
	}
}

}
