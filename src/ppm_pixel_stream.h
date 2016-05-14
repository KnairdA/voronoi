#pragma once

#include <string>
#include <fstream>

#include "color.h"

namespace imgen {

class ppm_pixel_stream {
	public:
		ppm_pixel_stream(const std::string& path,
		                 const std::size_t  width,
		                 const std::size_t  height);

		ppm_pixel_stream& operator<<(const color& value);

	private:
		std::ofstream stream_;

};

}
