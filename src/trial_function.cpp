#include "trial_function.h"

TrialFunction::TrialFunction(const bool &flag) {
  this->sigma = 10.0;
  this->moat = flag;
}

double TrialFunction::calc(const double &x, const double &y) {
  if(moat) {
    if((x > 2.0*PI && x < 3.0*PI) || (y > 2.0*PI && y < 3.0*PI)) {
      return 0;
    }
  }

  if(x < 0 || y < 0 || x > 4*PI || y > 4*PI) {
      return 0;
  } else {
      return pow(sin(x),2.0)*pow(sin(y),2.0)*exp((x+y)/this->sigma);
  }
}
