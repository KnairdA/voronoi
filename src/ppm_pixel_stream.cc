#include "ppm_pixel_stream.h"

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

	this->stream_ << "P6\n" << width << " " << height << "\n255\n";
}

ppm_pixel_stream& ppm_pixel_stream::operator<<(const color& value) {
	write_color(this->stream_, value);

	return *this;
}

}
