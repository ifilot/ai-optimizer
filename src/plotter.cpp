/**************************************************************************
 *   plotter.cpp                                                          *
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

#include "plotter.h"

Plotter::Plotter(unsigned int _width, unsigned int _height) {
  this->width = _width;
  this->height = _height;

  this->surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, this->width, this->height);
  this->cr = cairo_create (this->surface);

  this->set_background(colorscheme::Color(255, 252, 213));
}

void Plotter::set_background(const colorscheme::Color &_color) {
  cairo_set_source_rgb(this->cr, _color.get_r()/255.0, _color.get_g()/255.0, _color.get_b()/255.0);
  cairo_rectangle(this->cr, 0, 0, this->width, this->height);
  cairo_fill(this->cr);
}

void Plotter::draw_line(float xstart, float ystart, float xstop, float ystop, 
                        const colorscheme::Color &_color, float line_width) {
  cairo_set_source_rgb(this->cr, _color.get_r()/255.0, _color.get_g()/255.0, _color.get_b()/255.0);
  cairo_move_to(this->cr, xstart, ystart);
  cairo_line_to(this->cr, xstop, ystop);
  cairo_set_line_width(this->cr, line_width);
  cairo_stroke(this->cr);
}

void Plotter::draw_filled_rectangle(float xstart, float ystart, float xstop, float ystop, 
                        const colorscheme::Color &_color) {
  cairo_set_source_rgb(this->cr, _color.get_r()/255.0, _color.get_g()/255.0, _color.get_b()/255.0);
  cairo_rectangle (this->cr, xstart, ystart, xstop, ystop);
  cairo_fill(this->cr);
}

void Plotter::draw_empty_rectangle(float xstart, float ystart, float xstop, float ystop, 
                        const colorscheme::Color &_color, float line_width) {
  cairo_set_source_rgb(this->cr, _color.get_r()/255.0, _color.get_g()/255.0, _color.get_b()/255.0);
  cairo_rectangle (this->cr, xstart, ystart, xstop, ystop);
  cairo_set_line_width(this->cr, line_width);
  cairo_stroke(this->cr);
}

void Plotter::draw_filled_circle(float cx, float cy, float radius, 
                          const colorscheme::Color &_color) {
  cairo_set_source_rgb(this->cr, _color.get_r()/255.0, _color.get_g()/255.0, _color.get_b()/255.0);
  cairo_arc(this->cr, cx, cy, radius, 0.0, 2 * M_PI);
  cairo_fill(this->cr);
}

void Plotter::draw_empty_circle(float cx, float cy, float radius, 
                          const colorscheme::Color &_color, float line_width) {
  cairo_set_source_rgb(this->cr, _color.get_r()/255.0, _color.get_g()/255.0, _color.get_b()/255.0);
  cairo_arc(this->cr, cx, cy, radius, 0.0, 2 * M_PI);
  cairo_set_line_width(this->cr, line_width);
  cairo_stroke(this->cr);
}

void Plotter::write(const char* filename) {
  cairo_surface_write_to_png(this->surface, filename);
}