#ifndef _MCMC_H
#define _MCMC_H

#include "optimizer.h"

class MCMC : public Optimizer{ // Markov Chain Monte Carlo
private:
  double x;     // current x value
  double y;     // current y value
  double try_x; // newly generated x value
  double try_y; // newly generated y value
  double best_x; // best x solution so far
  double best_y; // best y solution so far

  double est;       // current estimate of function
  double best_est;  // best result of function
  double old_est;   // old result of function

  double diff;      // difference between est and old_est

  double variation; // how much x and y are allowed to change between iterations
  double beta;      // acceptance parameter
  unsigned int accept;  // how many states are accepted
public:
  MCMC();
  void run();
  void set_parameters(const unsigned int &_nr_iter, const double &_beta, const double &_variation);
  const double& get_x() const;
  const double& get_y() const;
  const double& get_x_best() const;
  const double& get_y_best() const;
private:
  void iteration(const unsigned int &iter_nr);
};

#endif //_MCMC_H