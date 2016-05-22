#include <imgen.h>

#include <cmath>
#include <thread>
#include <vector>
#include <algorithm>

double minkowski_metric(
	const double        p,
	const imgen::vector a,
	const imgen::vector b
) {
	return std::pow(
		  std::pow(std::abs(std::get<0>(a) - std::get<0>(b)), p)
		+ std::pow(std::abs(std::get<1>(a) - std::get<1>(b)), p),
		1.0 / p
	);
}

std::pair<double, imgen::colored_vector> get_distance_to_nearest(
	const std::function<double(imgen::vector, imgen::vector)>& metric,
	const imgen::vector a
) {
	constexpr std::array<imgen::colored_vector, 9> reference_vectors{
		imgen::colored_vector{   0,    0, imgen::red()                },
		imgen::colored_vector{ 240,  200, imgen::color{220, 220, 220} },
		imgen::colored_vector{-100,  230, imgen::color{ 94, 113, 106} },
		imgen::colored_vector{ 120, -100, imgen::color{140, 146, 172} },
		imgen::colored_vector{ -42, -200, imgen::color{128, 128, 128} },
		imgen::colored_vector{ 120,   40, imgen::color{ 16,  20,  22} },
		imgen::colored_vector{-150,   50, imgen::color{192, 192, 192} },
		imgen::colored_vector{  60, -128, imgen::color{178, 190, 181} },
		imgen::colored_vector{-240,  -20, imgen::color{ 54,  69,  79} }
	};

	std::array<double, 9> distances;

	std::transform(
		reference_vectors.begin(),
		reference_vectors.end(),
		distances.begin(),
		[&a, &metric](const imgen::colored_vector b) {
			return metric(a, imgen::vector{std::get<0>(b), std::get<1>(b)});
		}
	);

	const auto& minimal_distance{
		std::min_element(distances.begin(), distances.end())};
	const imgen::colored_vector& nearest{
		reference_vectors[std::distance(distances.begin(), minimal_distance)]};

	return std::make_pair(*minimal_distance, nearest);
}

void generate_minkowski_voronoi(const double p) {
	const auto metric{[p](const imgen::vector a, const imgen::vector b) -> double {
		return minkowski_metric(p, a, b);
	}};

	imgen::write_ppm(
		"voronoi_" + std::to_string(p) + ".ppm",
		512,
		512,
		[&metric](std::ptrdiff_t x, std::ptrdiff_t y) -> imgen::color {
			const auto& nearest = get_distance_to_nearest(
				metric,
				imgen::vector{x, y}
			);

			if ( nearest.first <= 5.0 ) {
				return imgen::black();
			} else {
				return std::get<2>(nearest.second);
			}
		}
	);
}

void generate_minkowski_voronoi(
	const double lower,
	const double upper,
	const double epsilon
) {
	const auto n{ std::nearbyint( ( upper - lower ) / epsilon) };

	for ( std::size_t i = 0; i < n; ++i ) {
		generate_minkowski_voronoi(lower + i * epsilon);
	}
}

void generate_parallel_minkowski_voronoi(
	const unsigned int thread_count,
	const double       lower,
	const double       upper,
	const double       epsilon
) {
	std::vector<std::thread> threads;

	const double step = ( upper - lower ) / thread_count;
	double offset     = lower;

	while ( threads.size() < thread_count ) {
		threads.emplace_back([offset, step, epsilon]{
			generate_minkowski_voronoi(
				offset,
				offset + step,
				epsilon
			);
		});

		offset += step;
	}

	generate_minkowski_voronoi(upper);

	for ( auto& thread : threads ) {
		thread.join();
	}
}

int main(int, char*[]) {
	generate_parallel_minkowski_voronoi(4, 1.0, 2.0, 0.025);
}
