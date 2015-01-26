#include <cstdlib>
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "marching_squares.h"
#include "svg.h"

#define PI 3.141527

double func(double x, double y) {
    const double sigma = 10.0f;
    if(x < 0 || y < 0 || x > 4*PI || y > 4*PI) {
        return 0;
    } else {
        return pow(sin(x),2.0)*pow(sin(y),2.0)*exp((x+y)/sigma);
    }
}

struct Color {
    float x,y,z;
};

double get_random_number(double min = 0.0, double max = 1.0) {
    return rand() / (double)RAND_MAX * (max - min) + min;
}

Color hsv_to_rgb(double h, double s, double v) {
  Color rgb;

  if( s == 0 ) {
    // achromatic (grey)
    rgb.x = rgb.y = rgb.z = v;
  }

  /* always get h in the interval [0,360] */
  if(h > 360.0) {
    h -= 360.0;
  }
  if(h < 0.0) {
    h += 360.0;
  }

  h /= 60.0;      // sector 0 to 5
  int i = floor(h);
  double f = h - i;      // factorial part of h
  double p = v * ( 1 - s );
  double q = v * ( 1 - s * f );
  double t = v * ( 1 - s * ( 1 - f ) );

  switch(i) {
    case 0:
      rgb.x = v;
      rgb.y = t;
      rgb.z = p;
      break;
    case 1:
      rgb.x = q;
      rgb.y = v;
      rgb.z = p;
      break;
    case 2:
      rgb.x = p;
      rgb.y = v;
      rgb.z = t;
      break;
    case 3:
      rgb.x = p;
      rgb.y = q;
      rgb.z = v;
      break;
    case 4:
      rgb.x = t;
      rgb.y = p;
      rgb.z = v;
      break;
    default: // case 5:
      rgb.x = v;
      rgb.y = p;
      rgb.z = q;
      break;
  }

  return rgb;
}

int main() {
    srand (time(NULL));

    const unsigned int tx = 1000;
    const unsigned int ty = 1000;

    svg::Dimensions dimensions(tx, ty);
    svg::Document doc("graph.svg", svg::Layout(dimensions, svg::Layout::BottomLeft));

    const unsigned int sx = 150;
    const unsigned int sy = 150;

    const double min_x = 0.0;
    const double max_x = 4 * PI;
    const double min_y = 0.0;
    const double max_y = 4 * PI;

    const double ratio = (double)tx / (max_x - min_x);
    const double squaresize = (double)tx / (double)sx;

    const double dx = (max_x - min_x) / (double)sx;
    const double dy = (max_y - min_y) / (double)sy;

    std::vector<double> scalar_field;

    msquares::MarchingSquares ms(min_x, min_y, max_x, max_y, sx, sy);
    for(unsigned int i=0; i<=sy; i++) {
        for(unsigned int j=0; j<=sx; j++) {
            double _x = j * dx + min_x;
            double _y = i * dy + min_y;

            scalar_field.push_back(func(_x, _y));
            ms.set_value(j, i, &scalar_field.back() );
            Color rgb = hsv_to_rgb(scalar_field.back() * 25.0, 1, 1);
            doc << svg::Rectangle(svg::Point(_x*ratio - squaresize / 2.0, _y*ratio - squaresize / 2.0), squaresize+1, squaresize+1, svg::Color(rgb.x * 255, rgb.y * 255, rgb.z * 255));
        }
    }

    // Start performing MCMC algorithm
    double x = get_random_number(0,1);
    double y = get_random_number(0,1);
    double try_x = 0;
    double try_y = 0;
    double est = func(x,y);
    double old_est = 0, diff = 0;
    double variation = 1.00;
    double beta = 0.0001;
    bool output = false;
    unsigned int accept = 0;
    unsigned int nr_iter = 50000;
    double best_x = 0;
    double best_y = 0;
    double best_est = 0.0;

    for(unsigned i=0; i<nr_iter; i++) {

        if(output) std::cout << i+1 << std::endl;
        if(i != 0) {
            double c = get_random_number(0,2);
            if(c < 1) {
                do {
                   try_x += get_random_number(-1.0, 1.0) * variation;
                } while(try_x < 0 || try_x > 4*PI);
                try_y = y; 
            } else {
                do {
                   try_y += get_random_number(-1.0, 1.0) * variation;
                } while(try_y < 0 || try_y > 4*PI);
                try_x = x;
            }
            est = func(try_x, try_y);

            if(output) std::cout << "Checking:\t" << try_x << "," << try_y << " (" << est << ")" << std::endl;

            diff = est - old_est;
            double chance = exp(diff * beta);
            double roll = get_random_number(0,1);
            if(diff > 0) { // accept new result
                x = try_x;
                y = try_y;
                accept++;
                old_est = est;
                if(output) std::cout << "This state was accepted" << std::endl;
            } else if(chance < roll) {
                x = try_x;
                y = try_y;
                accept++;
                if(output) std::cout << "Chance = " << (1.0-chance) << "\t" << "Roll = " << roll << std::endl;
                old_est = est;
            } else {
                if(output) std::cout << "This state was rejected" << std::endl;
            }

            // store best result so far
            if(est > best_est) {
                best_x = x;
                best_y = y;
                best_est = est;
            }
        }

        if(output) std::cout << "Current value:\t" << x << "," << y << std::endl;

        doc << svg::Circle(svg::Point(x*ratio, y*ratio), 3.0, svg::Color(0,0,0));
    }

    std::cout << "Acceptance: " << (float)accept / (float)nr_iter << std::endl;
    std::cout << "Best value: " << best_x << "," << best_y << std::endl;

    accept = 0;
    x = best_x;
    y = best_y;
    beta = 0.5;
    variation = 0.1;
    nr_iter = 1000;

    for(unsigned i=0; i<nr_iter; i++) {

        if(output) std::cout << i+1 << std::endl;
        if(i != 0) {
            double c = get_random_number(0,2);
            if(c < 1) {
                do {
                   try_x += get_random_number(-1.0, 1.0) * variation;
                } while(try_x < 0 || try_x > 4*PI);
                try_y = y; 
            } else {
                do {
                   try_y += get_random_number(-1.0, 1.0) * variation;
                } while(try_y < 0 || try_y > 4*PI);
                try_x = x;
            }
            est = func(try_x, try_y);

            if(output) std::cout << "Checking:\t" << try_x << "," << try_y << " (" << est << ")" << std::endl;

            diff = est - old_est;
            double chance = exp(diff * beta);
            double roll = get_random_number(0,1);
            if(diff > 0) { // accept new result
                x = try_x;
                y = try_y;
                accept++;
                old_est = est;
                if(output) std::cout << "This state was accepted" << std::endl;
            } else if(chance < roll) {
                x = try_x;
                y = try_y;
                accept++;
                if(output) std::cout << "Chance = " << (1.0-chance) << "\t" << "Roll = " << roll << std::endl;
                old_est = est;
            } else {
                if(output) std::cout << "This state was rejected" << std::endl;
            }

            // store best result so far
            if(est > best_est) {
                best_x = x;
                best_y = y;
                best_est = est;
            }
        }

        if(output) std::cout << "Current value:\t" << x << "," << y << std::endl;

        doc << svg::Circle(svg::Point(x*ratio, y*ratio), 3.0, svg::Color(0,255,0));
    }

    std::cout << "Acceptance: " << (float)accept / (float)nr_iter << std::endl;
    std::cout << "Best value: " << best_x << "," << best_y << std::endl;
    doc << svg::Circle(svg::Point(best_x*ratio, best_y*ratio), 10.0, svg::Color(255,255,255));

    doc.save();

    return 0;
}
