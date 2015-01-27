#ifndef _TRIAL_FUNCTION_H
#define _TRIAL_FUNCTION_H

#include "math.h"

#define PI 3.141527

class TrialFunction{
private:
  bool moat;
  double sigma;
public:
  TrialFunction(const bool &flag);
  double calc(const double &x, const double &y);
  typedef double(TrialFunction::*calcFunction)(const double&, const double&);
};

#endif //_TRIAL_FUNCTION_H