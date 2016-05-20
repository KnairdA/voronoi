#! /usr/bin/fish

mkdir unit ^/dev/null
cd unit
rm *.ppm *.gif ^/dev/null

../unit_circle

for f in unit_circle_*
	convert $f -annotate +75+120 (echo "p =" (echo $f | grep -o "[0-9].[0-9]\{2\}" | head -n 1)) $f
end

convert -delay 8 -loop 0 *.ppm circle.gif
convert -reverse circle.gif circle_reversed.gif
convert circle.gif circle_reversed.gif circle_cycle.gif

cd ..
