#ifndef _OPTIMIZER_H
#define _OPTIMIZER_H

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <math.h>

#define PI 3.141527

class Optimizer{
private:

public:
  Optimizer();
  void set_function(double (*func_ptr)(double, double, bool));
protected:
  double (*func_ptr)(double, double, bool); // pointer to function
  double get_random_number(double min, double max);
  bool flag_moat;
  bool output;
  void init();
  unsigned int nr_iter;
};

#endif //_OPTIMIZER_H