#include <imgen.h>

#include <cmath>
#include <thread>
#include <vector>
#include <algorithm>

int minkowski_metric(double p, int refX, int refY, int x, int y) {
	return static_cast<int>(std::nearbyint(
		std::pow(
			std::pow(std::abs(refX - x), p) + std::pow(std::abs(refY - y), p),
			1.0 / p
		)
	));
}

int manhattan_metric(int refX, int refY, int x, int y) {
	return minkowski_metric(1, refX, refY, x, y);
}

int euclidean_metric(int refX, int refY, int x, int y) {
	return minkowski_metric(2, refX, refY, x, y);
}

void generate_minkowski_voronoi(
	const double lower,
	const double upper,
	const double epsilon
) {
	constexpr std::array<imgen::colored_vector, 9> ref{
		imgen::colored_vector{   0,    0, imgen::red()    },
		imgen::colored_vector{ 240,  200, imgen::green()  },
		imgen::colored_vector{-100,  230, imgen::blue()   },
		imgen::colored_vector{ 120, -100, imgen::yellow() },
		imgen::colored_vector{ -42, -200, imgen::cyan()   },
		imgen::colored_vector{ 120,   40, imgen::magenta()},
		imgen::colored_vector{-150,   50, imgen::silver() },
		imgen::colored_vector{  60, -128, imgen::maroon() },
		imgen::colored_vector{-240,  -20, imgen::olive()  }
	};

	for ( double p = lower; p < upper + epsilon; p = p + epsilon ) {
		imgen::write_ppm(
			"voronoi_" + std::to_string(p) + ".ppm",
			512,
			512,
			[&ref, p](std::ptrdiff_t x, std::ptrdiff_t y) -> imgen::color {
				std::array<int, 9> distances;

				std::transform(
					ref.begin(),
					ref.end(),
					distances.begin(),
					[x, y, p](const imgen::colored_vector& pos) {
					return minkowski_metric(p, std::get<0>(pos), std::get<1>(pos), x, y);
				});

				const auto& minimal_distance = std::min_element(
					distances.begin(),
					distances.end()
				);
				const imgen::colored_vector& nearest = ref[
					std::distance(distances.begin(), minimal_distance)
				];

				if ( *minimal_distance <= 5 ) {
					return imgen::color(0, 0, 0);
				} else {
					return std::get<2>(nearest);
				}
			}
		);
	}
}

void generate_parallel_minkowski_voronoi(
	const unsigned int thread_count,
	const double       lower,
	const double       upper,
	const double       epsilon
) {
	std::vector<std::thread> threads;

	const double step = ( ( upper - lower ) / thread_count ) - epsilon;
	double offset     = lower;

	threads.emplace_back([offset, step, epsilon]{
		generate_minkowski_voronoi(
			offset,
			offset + step + epsilon,
			epsilon
		);
	});

	offset += step + epsilon + epsilon;

	while ( threads.size() < thread_count ) {
		threads.emplace_back([offset, step, epsilon]{
			generate_minkowski_voronoi(
				offset,
				offset + step,
				epsilon
			);
		});

		offset += step + epsilon;
	}

	for ( auto& thread : threads ) {
		thread.join();
	}
}

int main(int, char*[]) {
	generate_parallel_minkowski_voronoi(4, 1.0, 16.0, 0.05);
}
