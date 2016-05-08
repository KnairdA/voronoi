#include <imgen.h>

int main(int, char*[]) {
	imgen::write_ppm(
		"test.ppm",
		500,
		500,
		[](std::size_t x, std::size_t y) -> imgen::color {
			return imgen::color(255, x % 255, y % 255);
		}
	);
}
