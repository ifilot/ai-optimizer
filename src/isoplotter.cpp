#include <math.h>
#include "marching_squares.h"
#include "svg.h"

#define PI 3.141527

double func(double x, double y) {
	const double sigma = 10.0f;
	return pow(sin(x),2.0)*pow(sin(y),2.0)*exp((x+y)/sigma);
}

int main() {
    const unsigned int tx = 1000;
    const unsigned int ty = 1000;

    svg::Dimensions dimensions(tx, ty);
    svg::Document doc("graph.svg", svg::Layout(dimensions, svg::Layout::BottomLeft));

    const unsigned int sx = 50;
    const unsigned int sy = 50;

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
            doc << svg::Rectangle(svg::Point(_x*ratio, _y*ratio), squaresize, squaresize, svg::Color(scalar_field.back()*255, scalar_field.back()*255, scalar_field.back()*255));
        }
    }
    ms.set_isovalue(1);
    ms.get_points_list();

    for(unsigned int i=0; i<ms.get_isopoint_values_x().size(); i++) {
        doc << svg::Rectangle(svg::Point(ms.get_isopoint_values_x()[i] * ratio, ms.get_isopoint_values_y()[i] * ratio), squaresize / 2.0, squaresize / 2.0, svg::Color(255, 0.0, 0.0));
    }

    // ms.reset_isovalue(1);
    // ms.get_points_list();

    // for(unsigned int i=0; i<ms.get_isopoint_values_x().size(); i++) {
    //     doc << svg::Rectangle(svg::Point(ms.get_isopoint_values_x()[i] * ratio, ms.get_isopoint_values_y()[i] * ratio), squaresize / 2.0, squaresize / 2.0, svg::Color(0, 255, 0.0));
    // }

    doc.save();

    return 0;
}
