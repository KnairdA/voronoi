#include "imgen.h"

#include <fstream>

namespace {

inline void write_color(std::ofstream& out, const imgen::color& color) {
	out << std::get<0>(color);
	out << std::get<1>(color);
	out << std::get<2>(color);
}

}

namespace imgen {

void write_ppm(
	const std::string&                             path,
	const std::size_t                              sizeX,
	const std::size_t                              sizeY,
	std::function<color(std::size_t, std::size_t)> generator
) {
	std::ofstream out;
	out.open(path, std::ios::binary | std::ios::out);
	out.sync_with_stdio(false);

	out << "P6\n" << sizeX << " " << sizeY << "\n255\n";

	for ( std::size_t posY = 0; posY < sizeY; ++posY ) {
		for ( std::size_t posX = 0; posX < sizeX; ++posX ) {
			write_color(out, generator(posX, posY));
		}
	}
}

}
