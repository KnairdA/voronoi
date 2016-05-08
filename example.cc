#include <imgen.h>

#include <cmath>
#include <algorithm>

double metric(std::size_t refX, std::size_t refY, std::size_t x, std::size_t y) {
	return std::sqrt(
		(refX - x)*(refX - x) + (refY - y)*(refY - y)
	);
}

int main(int, char*[]) {
	using refpos = std::tuple<std::size_t, std::size_t, imgen::color>;

	std::array<refpos, 5> ref{
		refpos(100, 50,  imgen::color(255, 0,   0  )),
		refpos(500, 300, imgen::color(0,   255, 0  )),
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
					return   metric(std::get<0>(a), std::get<1>(a), x, y)
					       < metric(std::get<0>(b), std::get<1>(b), x, y);
				}
			);

			return std::get<2>(nearest);
		}
	);
}
