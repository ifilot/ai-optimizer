#ifndef _TRIAL_FUNCTION_H
#define _TRIAL_FUNCTION_H

class TrialFunction{
private:
  bool moat;
  double sigma;
public:
  TrialFunction(const bool &flag);
  double calc(const double &x, const double &y);
};

#endif //_TRIAL_FUNCTION_H