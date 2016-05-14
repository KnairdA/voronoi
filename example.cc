#include <imgen.h>

#include <cmath>
#include <algorithm>

int minkowski_metric(double p, int refX, int refY, int x, int y) {
	return static_cast<int>(std::nearbyint(
		std::pow(
			std::pow(std::abs(refX - x), p) + std::pow(std::abs(refY - y), p),
			1.0 / p
		)
	));
}

int euclidean_metric(int refX, int refY, int x, int y) {
	return minkowski_metric(2, refX, refY, x, y);
}

int manhattan_metric(int refX, int refY, int x, int y) {
	return minkowski_metric(1, refX, refY, x, y);
}

int main(int, char*[]) {
	using refpos = std::tuple<int, int, imgen::color>;

	std::array<refpos, 9> ref{
		refpos( 0,    0,   imgen::color(255, 0,   0   )),
		refpos( 100,  100, imgen::color(0,   255, 0   )),
		refpos(-100,  100, imgen::color(0,   0,   255 )),
		refpos( 100, -100, imgen::color(255, 255, 0   )),
		refpos(-100, -100, imgen::color(0,   255, 255 )),
		refpos( 200,  200, imgen::color(255, 0,   0   )),
		refpos(-200,  200, imgen::color(0,   255, 0   )),
		refpos( 200, -200, imgen::color(0,   255, 255 )),
		refpos(-200, -200, imgen::color(255, 255, 0   ))
	};

	imgen::write_ppm(
		"test.ppm",
		512,
		512,
		[&ref](std::ptrdiff_t x, std::ptrdiff_t y) -> imgen::color {
			const refpos& nearest = *std::min_element(
				ref.begin(),
				ref.end(),
				[x, y](const refpos& a, const refpos& b) -> bool {
					return   euclidean_metric(std::get<0>(a), std::get<1>(a), x, y)
					       < euclidean_metric(std::get<0>(b), std::get<1>(b), x, y);
				}
			);

			if ( euclidean_metric(std::get<0>(nearest), std::get<1>(nearest), x, y) <= 5 ) {
				return imgen::color(0, 0, 0);
			} else {
				return std::get<2>(nearest);
			}
		}
	);
}
