#include <cstdlib>
#include <math.h>
#include "color_scheme.h"
#include "marching_squares.h"
#include "svg.h"
#include "mcmc.h"

#define PI 3.141527

double func(double x, double y, bool moat = false) {
    const double sigma = 10.0f;

    if(moat) {
      if((x > 2.0*PI && x < 3.0*PI) || (y > 2.0*PI && y < 3.0*PI)) {
        return 0;
      }
    }

    if(x < 0 || y < 0 || x > 4*PI || y > 4*PI) {
        return 0;
    } else {
        return pow(sin(x),2.0)*pow(sin(y),2.0)*exp((x+y)/sigma);
    }
}

int main() {

  bool flag_moat = false;

  const unsigned int tx = 1000;
  const unsigned int ty = 1000;

  svg::Dimensions dimensions(tx, ty);
  svg::Document doc("graph.svg", svg::Layout(dimensions, svg::Layout::BottomLeft));

  const unsigned int sx = 250;
  const unsigned int sy = 250;

  const double min_x = 0.0;
  const double max_x = 4 * PI;
  const double min_y = 0.0;
  const double max_y = 4 * PI;

  const double ratio = (double)tx / (max_x - min_x);
  const double squaresize = (double)tx / (double)sx;

  const double dx = (max_x - min_x) / (double)sx;
  const double dy = (max_y - min_y) / (double)sy;

  std::vector<double> scalar_field;
  colorscheme::ColorScheme scheme(0.0, 4.0);

  for(unsigned int i=0; i<=sy; i++) {
      for(unsigned int j=0; j<=sx; j++) {
          double _x = j * dx + min_x;
          double _y = i * dy + min_y;

          colorscheme::Color rgb = scheme.get_color(func(_x, _y, flag_moat));
          doc << svg::Rectangle(svg::Point(_x*ratio - squaresize / 2.0, _y*ratio - squaresize / 2.0), squaresize+1, squaresize+1, svg::Color(rgb.get_r(), rgb.get_g(), rgb.get_b()));
      }
  }

  MCMC opt;
  opt.set_function(func);
  opt.run();

  doc.save();

  return 0;
}
