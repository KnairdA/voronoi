#include "color.h"

namespace imgen {

color red()     { return color{255,   0,   0}; }
color lime()    { return color{  0, 255,   0}; }
color blue()    { return color{  0,   0, 255}; }
color yellow()  { return color{255, 255,   0}; }
color cyan()    { return color{  0, 255, 255}; }
color magenta() { return color{255,   0, 255}; }
color silver()  { return color{192, 192, 192}; }
color maroon()  { return color{128,   0,   0}; }
color olive()   { return color{128, 128,   0}; }
color green()   { return color{  0, 128,   0}; }
color purple()  { return color{128,   0, 128}; }
color teal()    { return color{  0, 128, 128}; }
color navy()    { return color{  0,   0, 128}; }

}
