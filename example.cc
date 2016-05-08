#include <imgen.h>

#include <cmath>
#include <algorithm>

template <int p>
double minkowski_metric(int refX, int refY, int x, int y) {
	return std::pow(
		std::pow(std::abs(refX - x), p) + std::pow(std::abs(refY - y), p),
		1.0/p
	);
}

double euclidean_metric(int refX, int refY, int x, int y) {
	return minkowski_metric<2>(refX, refY, x, y);
}

int manhattan_metric(int refX, int refY, int x, int y) {
	return minkowski_metric<1>(refX, refY, x, y);
}

int main(int, char*[]) {
	using refpos = std::tuple<int, int, imgen::color>;

	std::array<refpos, 5> ref{
		refpos(100, 50,  imgen::color(255, 0,   0  )),
		refpos(490, 300, imgen::color(0,   255, 0  )),
		refpos(250, 250, imgen::color(0,   0,   255)),
		refpos(400, 20,  imgen::color(100, 10,  100)),
		refpos(60,  400, imgen::color(20,  60,  300))
	};

	imgen::write_ppm(
		"test.ppm",
		500,
		500,
		[&ref](std::size_t x, std::size_t y) -> imgen::color {
			const refpos& nearest = *std::min_element(
				ref.begin(),
				ref.end(),
				[x, y](const refpos& a, const refpos& b) -> bool {
					return   minkowski_metric<5>(std::get<0>(a), std::get<1>(a), x, y)
					       < minkowski_metric<5>(std::get<0>(b), std::get<1>(b), x, y);
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
