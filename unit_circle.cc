#include <imgen.h>

#include <cmath>
#include <vector>
#include <algorithm>

int p_norm(double p, int x, int y) {
	return static_cast<int>(std::nearbyint(
		std::pow(
			std::pow(std::abs(x), p) + std::pow(std::abs(y), p),
			1.0 / p
		)
	));
}

void generate_p_unit_circle(
	const double lower,
	const double upper,
	const double epsilon
) {
	for ( double p = lower; p < upper + epsilon; p = p + epsilon ) {
		imgen::write_ppm(
			"unit_circle_" + std::to_string(p) + ".ppm",
			128,
			128,
			[p](std::ptrdiff_t x, std::ptrdiff_t y) -> imgen::color {
				if ( p_norm(p, x, y) <= 32 ) {
					return imgen::black();
				} else {
					return imgen::white();
				}
			}
		);
	}
}

int main(int, char*[]) {
	generate_p_unit_circle(1.0, 3.0, 0.05);
}
