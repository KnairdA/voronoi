cmake_minimum_required(VERSION 2.8)
project(imgen)

set(
	CMAKE_CXX_FLAGS
	"${CMAKE_CXX_FLAGS} -std=c++14 -W -Wall -Wextra -Winline -pedantic"
)

include_directories(
	src/
)

add_library(
	imgen SHARED
		src/imgen.cc
		src/ppm_pixel_stream.cc
)

add_executable(
	voronoi
		voronoi.cc
)

add_executable(
	unit_circle
		unit_circle.cc
)

target_link_libraries(
	voronoi
		m
		imgen
		pthread
)

target_link_libraries(
	unit_circle
		m
		imgen
)
