/**************************************************************************
 *   color_scheme.h                                                       *
 *                                                                        *
 *   MYOCASTOR                                                            *
 *                                                                        *
 *   Authors: Ivo Filot                                                   *
 *            Bart Zijlstra                                               *
 *            Robin Broos                                                 *
 *            Emiel Hensen                                                *
 *                                                                        *
 *   (C) Copyright 2015 Inorganic Materials Chemistry                     *
 *                                                                        *
 *   This is a legal licensing agreement (Agreement) between              *
 *   You (an individual or single legal entity) and                       *
 *   Inorganic Materials Chemistry (IMC) governing the in-house use       *
 *   of the MYOCASTOR software product (Software).                        *
 *   By downloading, installing, or using Software, You agree to be bound *
 *   by the license terms as given on http://www.myocastor.nl/license.    *
 *                                                                        *
 **************************************************************************/

#include "color_scheme.h"

/**
 * Constructor
 *
 * Define lower and upper boundary of the color scheme. The colorscheme will
 * generate only colors by interpolation if the requested value to be colorcoded
 * is within the boundaries set here.
 *
 */
colorscheme::ColorScheme::ColorScheme(const double &_low, const double &_high) {
  this->low = _low;
  this->high = _high;
  this->construct_scheme();
  this->convert_scheme();
}

/**
 * Method
 *
 * Construct a colorscheme. The color values are here hardcoded and extracted from:
 * http://colorbrewer2.org/
 *
 */
void colorscheme::ColorScheme::construct_scheme() {
  // this->scheme.push_back("ffffd9");
  // this->scheme.push_back("edf8b1");
  // this->scheme.push_back("c7e9b4");
  // this->scheme.push_back("7fcdbb");
  // this->scheme.push_back("41b6c4");
  // this->scheme.push_back("1d91c0");
  // this->scheme.push_back("225ea8");
  // this->scheme.push_back("253494");
  // this->scheme.push_back("081d58");

  this->scheme.push_back("053061");
  this->scheme.push_back("2166ac");
  this->scheme.push_back("4393c3");
  this->scheme.push_back("92c5de");
  this->scheme.push_back("d1e5f0");
  this->scheme.push_back("f7f7f7");
  this->scheme.push_back("fddbc7");
  this->scheme.push_back("f4a582");
  this->scheme.push_back("d6604d");
  this->scheme.push_back("b2182b");
  this->scheme.push_back("67001f");
}

/**
 * Method
 *
 * Convert the colorscheme set in hexidecimal RGB to integer RGB
 *
 */
void colorscheme::ColorScheme::convert_scheme() {
  for(unsigned int i=0; i<this->scheme.size(); i++) {
    this->colors.push_back(this->rgb2color(this->scheme[i]));
  }
}

/**
 * Method
 *
 * Convert string of hexidecimal RGB values to three integers
 *
 */
colorscheme::Color colorscheme::ColorScheme::rgb2color(const std::string &_hex) {
  return colorscheme::Color(this->hex2int(_hex.substr(0,2)),
                            this->hex2int(_hex.substr(2,2)),
                            this->hex2int(_hex.substr(4,2)));
}

/**
 * Method
 *
 * Return a color by interpolation by supplying a value
 *
 */
colorscheme::Color colorscheme::ColorScheme::get_color(const double &_value) {
  if(_value > this->high) {
    return this->colors.back();
  }
  if(_value < this->low) {
    return this->colors.front();
  }

  float binsize = ((this->high - this->low)/(double)(this->colors.size()-1));
  unsigned int bin = floor((_value - this->low) / binsize);

  // interpolate between the two colors
  float residual = (_value - this->low - (float)bin * binsize) / binsize;

  float r = residual * this->colors[bin+1].get_r() + (1.0-residual) * this->colors[bin].get_r();
  float g = residual * this->colors[bin+1].get_g() + (1.0-residual) * this->colors[bin].get_g();
  float b = residual * this->colors[bin+1].get_b() + (1.0-residual) * this->colors[bin].get_b();

  return colorscheme::Color(r,g,b);
}

/**
 * Method
 *
 * Convert a single hexidecimal value to an integer
 *
 */
unsigned int colorscheme::ColorScheme::hex2int(const std::string &_hex) {
  char* offset;
  if(_hex.length() > 2) {
    if(_hex[0] == '0' && _hex[1] == 'x') {
      return strtol(_hex.c_str(), &offset, 0);
    }
  }
  return strtol(_hex.c_str(), &offset, 16);
}

/**
 * Constructor
 *
 * Color
 *
 */
colorscheme::Color::Color(unsigned int _r, unsigned int _g, unsigned int _b) {
  this->r = _r;
  this->g = _g;
  this->b = _b;
}

/**
 * Method
 *
 * Return the integer value for red (divide by 255 because we want on the [0,1] interval)
 *
 */
float colorscheme::Color::get_r() const {
  return this->r;
}

/**
 * Method
 *
 * Return the integer value for green (divide by 255 because we want on the [0,1] interval)
 *
 */
float colorscheme::Color::get_g() const {
  return this->g;
}

/**
 * Method
 *
 * Return the integer value for blue (divide by 255 because we want on the [0,1] interval)
 *
 */
float colorscheme::Color::get_b() const {
  return this->b;
}