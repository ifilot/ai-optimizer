#include "marching_squares.h"

using namespace msquares;

Square::Square(const double &x1, const double &y1,
               const double &x2, const double &y2,
               const double &x3, const double &y3,
               const double &x4, const double &y4) {
  this->x[0] = x1;
  this->x[1] = x2;
  this->x[2] = x3;
  this->x[3] = x4;
  this->y[0] = y1;
  this->y[1] = y2;
  this->y[2] = y3;
  this->y[3] = y4;

  this->idx = 0;
}

void Square::set_values(const double* v1,
                        const double* v2,
                        const double* v3,
                        const double* v4) {
  this->values[0] = v1;
  this->values[1] = v2;
  this->values[2] = v3;
  this->values[3] = v4;
}

void Square::set_idx(const double &_isovalue) {
  this->idx = 0;
  for(unsigned int i=0; i<4; i++) {
    if(*this->values[i] > _isovalue) {
      this->idx |= (1 << i);
    }
  }
}

void Square::print_value() const {
  std::cout << this->x[0] << "\t"
            << this->y[0] << "\t"
            << *this->values[0] << "\t"
            << this->idx << "\t" << std::endl;
}

void Square::grab_points(unsigned int *points, double* x, double* y) {
  if(this->idx == 0 || this->idx == 15) {
    return;
  } else if(this->idx == 5 || this->idx == 10) {
    *points = 4;
  } else {
    *points = 2;
  }

  unsigned int j=0;
  for(unsigned int i=0; i<4; i++) {
    if(squares_lookuptable[this->idx] & i) {
      switch(i) {
        case 0:
          x[j] = (this->x[1] + this->x[0]) / 2.0;
          y[j] = this->y[0];
        break;
        case 1:
          x[j] = this->x[1];
          y[j] = (this->y[2] + this->y[1]) / 2.0;
        break;
        case 2:
          x[j] = (this->x[2] + this->x[3]) / 2.0;
          y[j] = this->y[2];
        break;
        case 3:
          x[j] = this->x[0];
          y[j] = (this->y[0] + this->y[3]) / 2.0;
        break;
      }
      j++;
    }
  }
}

MarchingSquares::MarchingSquares(const double &_xmin,
                                 const double &_ymin,
                                 const double &_xmax,
                                 const double &_ymax,
                                 const unsigned int &_gridsize_x,
                                 const unsigned int &_gridsize_y) {
  this->xmin = _xmin;
  this->ymin = _ymin;
  this->xmax = _xmax;
  this->ymax = _ymax;
  this->gridsize_x = _gridsize_x;
  this->gridsize_y = _gridsize_y;
  this->dx = (_xmax - _xmin) / _gridsize_x;
  this->dy = (_ymax - _ymin) / _gridsize_x;

  for(unsigned int i=0; i<_gridsize_y; i++) {
    for(unsigned int j=0; j<_gridsize_x; j++) {
      this->squares.push_back(Square(
          (double)j * this->dx + this->xmin, (double)i * this->dy + this->ymin,
          (double)(j+1) * this->dx + this->xmin, (double)i * this->dy + this->ymin,
          (double)(j+1) * this->dx + this->xmin, (double)(i+1) * this->dy + this->ymin,
          (double)j * this->dx + this->xmin, (double)(i+1) * this->dy + this->ymin
        )
      );
    }
  }
  this->field.resize((_gridsize_x+1) * (_gridsize_y+1));
}

void MarchingSquares::set_value(const unsigned int &_i, const unsigned int &_j, const double* _v) {
  this->field[_j * (this->gridsize_x+1) + _i] = _v;
}

void MarchingSquares::set_isovalue(const double &_isovalue) {
  this->construct_squares();
  for(unsigned int i=0; i<this->squares.size(); i++) {
    this->squares[i].set_idx(_isovalue);
  }
}

void MarchingSquares::reset_isovalue(const double &_isovalue) {
  this->x.clear();
  this->y.clear();
  for(unsigned int i=0; i<this->squares.size(); i++) {
    this->squares[i].set_idx(_isovalue);
  }
}

void MarchingSquares::print_values() const{
  for(unsigned int i=0; i<this->gridsize_y; i++) {
    for(unsigned int j=0; j<this->gridsize_x; j++) {
      std::cout << "(" << (double)j * this->dx + this->xmin << ","
                << (double)i * this->dy + this->ymin << ") \t" <<
      *this->field[i * this->gridsize_x + j] << std::endl;
    }
  }
}

void MarchingSquares::print_squares() const{
  for(unsigned int i=0; i<this->squares.size(); i++) {
    this->squares[i].print_value();
  }
}

void MarchingSquares::construct_squares() {
  for(unsigned int i=0; i<this->gridsize_y; i++) {
    for(unsigned int j=0; j<this->gridsize_x; j++) {
      this->set_square(j, i, get_sfield_value(j, i),
                             get_sfield_value(j+1, i),
                             get_sfield_value(j+1, i+1),
                             get_sfield_value(j, i+1));
    }
  }
}

void MarchingSquares::set_square(const unsigned int &_x,
                                const unsigned int &_y,
                                const double* _v1,
                                const double* _v2,
                                const double* _v3,
                                const double* _v4) {
  this->squares[_y * this->gridsize_x + _x].set_values(_v1, _v2, _v3, _v4);
}

const double* MarchingSquares::get_sfield_value(const unsigned int &_i, const unsigned int &_j) {
  return this->field[_j * (this->gridsize_x+1) + _i];
}

void MarchingSquares::get_points_list() {
  unsigned int pts = 0;
  double _x[4];
  double _y[4];

  for(unsigned int i=0; i<this->squares.size(); i++) {
    this->squares[i].grab_points(&pts, _x, _y);
    for(unsigned int j=0; j<pts; j++) {
      this->x.push_back(_x[j]);
      this->y.push_back(_y[j]);
    }
  }
}

std::vector<double>& MarchingSquares::get_isopoint_values_x() {
  return this->x;
}

std::vector<double>& MarchingSquares::get_isopoint_values_y() {
  return this->y;
}