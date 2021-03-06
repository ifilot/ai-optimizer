#include "color_scheme.h"
#include "svg.h"
#include "mcmc.h"
#include "genalg.h"
#include "trial_function.h"
#include "plotter.h"

#define PI 3.141527

int main() {

  TrialFunction tf(true);

  const unsigned int tx = 1000;
  const unsigned int ty = 1000;

  Plotter plt(tx, ty);
  colorscheme::ColorScheme scheme(0,8);

  const unsigned int sx = 1000;
  const unsigned int sy = 1000;

  const double min_x = 0.0;
  const double max_x = 4 * PI;
  const double min_y = 0.0;
  const double max_y = 4 * PI;

  const double ratio = (double)tx / (max_x - min_x);
  const double squaresize = (double)tx / (double)sx;

  const double dx = (max_x - min_x) / (double)sx;
  const double dy = (max_y - min_y) / (double)sy;

  std::vector<double> scalar_field;

  // draw contour plot
  for(unsigned int i=0; i<=sy; i++) {
      for(unsigned int j=0; j<=sx; j++) {
          double _x = j * dx + min_x;
          double _y = i * dy + min_y;

          colorscheme::Color rgb = scheme.get_color(tf.calc(_x, _y));
          plt.draw_filled_rectangle(_x*ratio - squaresize / 2.0, ty - _y*ratio - squaresize / 2.0, squaresize+1, squaresize+1, rgb);
      }
  }

  // MCMC opt;
  // opt.set_function(tf);
  // opt.set_parameters(6000, 1e-5, 0.95);
  // opt.set_output(false); // suppress output
  // opt.run();

  //std::cout << "Best result: " << opt.get_x() << "," << opt.get_y() << std::endl;

  GeneticAlgorithm genalg;
  genalg.set_function(tf);
  genalg.run();
  genalg.print_gene_pool();

  for(unsigned int i=0; i <= genalg.get_iterations(); i++) {
    if(i >= genalg.get_iterations() - genalg.get_nr_chromosomes()) {
      plt.draw_filled_circle(genalg.get_output_x(i)*ratio, ty - genalg.get_output_y(i)*ratio, 7.0, colorscheme::Color(255,0,0));
      plt.draw_empty_circle(genalg.get_output_x(i)*ratio, ty - genalg.get_output_y(i)*ratio, 7.0, colorscheme::Color(255,255,255), 1.0);
    } else {
      plt.draw_filled_circle(genalg.get_output_x(i)*ratio, ty - genalg.get_output_y(i)*ratio, 7.0, colorscheme::Color(0,0,0));
      plt.draw_empty_circle(genalg.get_output_x(i)*ratio, ty - genalg.get_output_y(i)*ratio, 7.0, colorscheme::Color(255,255,255), 1.0);
    }
    
  }

  plt.write("test.png");

  return 0;
}
