#ifndef _COLOR_SCHEME_H
#define _COLOR_SCHEME_H

#include <vector>
#include <string>
#include <cstdlib>
#include <math.h>

namespace colorscheme {

class Color {
private:
	unsigned int r,g,b;
public:
	Color(unsigned int _r, unsigned int _g, unsigned int _b);
	const unsigned int& get_r() const;
	const unsigned int& get_g() const;
	const unsigned int& get_b() const;
};

class ColorScheme {
private:
	std::vector<std::string> scheme;
	std::vector<Color> colors;
	double low, high;
public:
	ColorScheme(const double &_low, const double &_high);
	Color get_color(const double &_value);
private:
	void construct_scheme();
	void convert_scheme();
	Color rgb2color(const std::string &_hex);
	unsigned int hex2int(const std::string &_hex);
};

} // end namespace colorscheme

#endif //_COLOR_SCHEME_H