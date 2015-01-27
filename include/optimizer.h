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
  void set_function(double (*func_ptr)(double, double, bool));
  //virtual void run();
  void set_output(const bool &flag);
protected:
  double (TrialFunction::*func_ptr)(double, double, bool); // pointer to function
  double get_random_number(double min, double max);
  bool flag_moat;
  bool output;
  void init();
  unsigned int nr_iter;
};

#endif //_OPTIMIZER_H