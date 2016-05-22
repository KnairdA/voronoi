#! /usr/bin/fish

mkdir voronoi_gif ^/dev/null
cd voronoi_gif
rm *.ppm *.gif ^/dev/null

../voronoi

for f in voronoi_*
	convert $f -annotate +450+500 (
		echo "p =" (echo $f | grep -o "[0-9].[0-9]\{2\}" | head -n 1)
	) $f
end

convert -delay 4 -loop 0 *.ppm voronoi.gif
convert -reverse voronoi.gif voronoi_reversed.gif
convert voronoi.gif voronoi_reversed.gif voronoi_cycle.gif

cd ..
