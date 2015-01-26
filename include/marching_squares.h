#ifndef _MARCHING_SQUARES_H
#define _MARCHING_SQUARES_H

#include <vector>
#include <iostream>

namespace msquares{

  const int squares_lookuptable[16] = {
                                     0,
                                     (1 << 0) | (1 << 3),
                                     (1 << 0) | (1 << 1),
                                     (1 << 1) | (1 << 3),
                                     (1 << 1) | (1 << 2),
                                     (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3),
                                     (1 << 0) | (1 << 3),
                                     (1 << 2) | (1 << 3),
                                     (1 << 2) | (1 << 3),
                                     (1 << 0) | (1 << 3),
                                     (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3),
                                     (1 << 1) | (1 << 2),
                                     (1 << 1) | (1 << 3),
                                     (1 << 0) | (1 << 1),
                                     (1 << 0) | (1 << 3),
                                     0
                                     };

  class Square {
  private:
    const double* values[4];
    double x[4];
    double y[4];
    int idx;
  public:
    Square(const double &x1, const double &y1,
           const double &x2, const double &y2,
           const double &x3, const double &y3,
           const double &x4, const double &y4);
    void set_values(const double* v1,
                    const double* v2,
                    const double* v3,
                    const double* v4);
    void set_idx(const double &_isovalue);
    void print_value() const;
    void grab_points(unsigned int *points, double* x, double* y);
  };

  class MarchingSquares{
    private:
      unsigned int gridsize_x;
      unsigned int gridsize_y;
      double xmin;
      double ymin;
      double xmax;
      double ymax;
      double dx;
      double dy;
      std::vector<const double*> field;
      std::vector<Square> squares;

      std::vector<double> x;
      std::vector<double> y;

    public:
      MarchingSquares(const double &_xmin,
                      const double &_ymin,
                      const double &_xmax,
                      const double &_ymax,
                      const unsigned int &_gridsize_x,
                      const unsigned int &_gridsize_y);
      void set_value(const unsigned int &_x, const unsigned int &_y, const double* v1);
      void print_values() const;
      void print_squares() const;
      void set_isovalue(const double &_isovalue);
      void reset_isovalue(const double &_isovalue);
      void get_points_list();
      std::vector<double>& get_isopoint_values_x();
      std::vector<double>& get_isopoint_values_y();

    private:
      void construct_squares();
      const double* get_sfield_value(const unsigned int &_i, const unsigned int &_j);
      void set_square(const unsigned int &_x, const unsigned int &_y, const double* v1,
                     const double* v2, const double* v3, const double* v4);
  };
}

#endif //_MARCHING_SQUARES_H