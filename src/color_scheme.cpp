#include "color_scheme.h"

colorscheme::ColorScheme::ColorScheme(const double &_low, const double &_high) {
  this->low = _low;
  this->high = _high;
  this->construct_scheme();
  this->convert_scheme();
}

void colorscheme::ColorScheme::construct_scheme() {
  this->scheme.push_back("ffffd9");
  this->scheme.push_back("edf8b1");
  this->scheme.push_back("c7e9b4");
  this->scheme.push_back("7fcdbb");
  this->scheme.push_back("41b6c4");
  this->scheme.push_back("1d91c0");
  this->scheme.push_back("225ea8");
  this->scheme.push_back("253494");
  this->scheme.push_back("081d58");
}

void colorscheme::ColorScheme::convert_scheme() {
  for(unsigned int i=0; i<this->scheme.size(); i++) {
    this->colors.push_back(this->rgb2color(this->scheme[i]));
  }
}

colorscheme::Color colorscheme::ColorScheme::rgb2color(const std::string &_hex) {
  return colorscheme::Color(this->hex2int(_hex.substr(0,2)),
                            this->hex2int(_hex.substr(2,2)),
                            this->hex2int(_hex.substr(4,2)));
}

colorscheme::Color colorscheme::ColorScheme::get_color(const double &_value) {
  if(_value > this->high) {
    return this->colors.back();
  }
  if(_value < this->low) {
    return this->colors.front();
  }

  unsigned int bin = floor((_value - this->low) / ((this->high - this->low)/(double)this->colors.size() ) );
  return this->colors[bin];
}

unsigned int colorscheme::ColorScheme::hex2int(const std::string &_hex) {
  char* offset;
  if(_hex.length() > 2) {
    if(_hex[0] == '0' && _hex[1] == 'x') {
      return strtol(_hex.c_str(), &offset, 0);
    }
  }
  return strtol(_hex.c_str(), &offset, 16);
}

colorscheme::Color::Color(unsigned int _r, unsigned int _g, unsigned int _b) {
  this->r = _r;
  this->g = _g;
  this->b = _b;
}

const unsigned int& colorscheme::Color::get_r() const {
  return this->r;
}

const unsigned int& colorscheme::Color::get_g() const {
  return this->g;
}

const unsigned int& colorscheme::Color::get_b() const {
  return this->b;
}