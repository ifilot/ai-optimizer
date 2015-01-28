#ifndef _OPTIMIZER_H
#define _OPTIMIZER_H

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <vector>
#include <math.h>
#include "trial_function.h"

#define PI 3.141527

class Optimizer{
private:

public:
  Optimizer();
  void set_function(TrialFunction &_fptr);
  void set_output(const bool &flag);
  const unsigned int get_iterations() const;
  const double& get_output_x(const unsigned int &i);
  const double& get_output_y(const unsigned int &i);
protected:
  double get_random_number(double min, double max);
  bool flag_moat;
  bool output;
  void init();
  unsigned int nr_iter;
  TrialFunction *fptr;
  std::vector<double> output_x;
  std::vector<double> output_y;
  std::vector<double> output_value;
};

#endif //_OPTIMIZER_H