/**************************************************************************
 *   plotter.h                                                            *
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

#ifndef _PLOTTER_H
#define _PLOTTER_H

#include <cairo/cairo.h>
#include "color_scheme.h"
#include "mcmc.h"

class Plotter {
private:
  cairo_t *cr;
  cairo_surface_t *surface;
  unsigned int width, height;
public:
  Plotter(unsigned int _width, unsigned int _height);
  void set_background(const colorscheme::Color &_color);
  void write(const char* filename);
  void draw_filled_rectangle(float xstart, float ystart, float xstop, float ystop, 
                      const colorscheme::Color &_color);
  void draw_empty_rectangle(float xstart, float ystart, float xstop, float ystop, 
                      const colorscheme::Color &_color, float line_width);
  void draw_line(float xstart, float ystart, float xstop, float ystop, 
                 const colorscheme::Color &_color, float line_width);
  void draw_filled_circle(float cx, float cy, float radius, 
                          const colorscheme::Color &_color);
  void draw_empty_circle(float cx, float cy, float radius, 
                        const colorscheme::Color &_color, float line_width);
private:
  
};

#endif //_PLOTTER_H