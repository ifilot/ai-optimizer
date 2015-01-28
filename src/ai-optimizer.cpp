#include "color_scheme.h"
#include "svg.h"
#include "mcmc.h"
#include "genalg.h"
#include "trial_function.h"

#define PI 3.141527

int main() {

  TrialFunction tf(false);

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

          colorscheme::Color rgb = scheme.get_color(tf.calc(_x, _y));
          doc << svg::Rectangle(svg::Point(_x*ratio - squaresize / 2.0, _y*ratio - squaresize / 2.0), squaresize+1, squaresize+1, svg::Color(rgb.get_r(), rgb.get_g(), rgb.get_b()));
      }
  }

  // MCMC opt;
  // opt.set_function(tf);
  // opt.set_parameters(6000, 1e-5, 0.95);
  // opt.set_output(false); // suppress output
  // opt.run();

  // for(unsigned int i=0; i<=opt.get_iterations(); i++) {
  //   doc << svg::Circle(svg::Point(opt.get_output_x(i)*ratio, opt.get_output_y(i)*ratio), 15.0, svg::Color(0,0,0), svg::Stroke(1.0, svg::Color(255,255,255)));
  // }

  //std::cout << "Best result: " << opt.get_x() << "," << opt.get_y() << std::endl;

  GeneticAlgorithm genalg;
  genalg.set_function(tf);
  genalg.run();
  genalg.print_gene_pool();

  doc.save();

  return 0;
}
