/**************************************************************************
 *   color_scheme.cpp                                                     *
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

#ifndef _COLOR_SCHEME_H
#define _COLOR_SCHEME_H

#include <iostream>
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
  float get_r() const;
  float get_g() const;
  float get_b() const;
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