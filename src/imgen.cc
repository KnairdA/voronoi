#include "imgen.h"

#include "ppm_pixel_stream.h"

namespace imgen {

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

	for ( std::ptrdiff_t posY = max_y; posY > min_y; --posY ) {
		for ( std::ptrdiff_t posX = min_x; posX < max_x; ++posX ) {
			file << generator(posX, posY);
		}
	}
}

}
