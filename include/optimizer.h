#ifndef _OPTIMIZER_H
#define _OPTIMIZER_H

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <math.h>
#include "trial_function.h"

#define PI 3.141527

class Optimizer{
private:

public:
  Optimizer();
  void set_function(TrialFunction &_fptr);
  void set_output(const bool &flag);
protected:
  double get_random_number(double min, double max);
  bool flag_moat;
  bool output;
  void init();
  unsigned int nr_iter;
  TrialFunction *fptr;
};

#endif //_OPTIMIZER_H