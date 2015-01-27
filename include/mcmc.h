#ifndef _MCMC_H
#define _MCMC_H

#include "optimizer.h"

class MCMC : public Optimizer{ // Markov Chain Monte Carlo
  private:
    double best_x;
    double best_y;
    double x;
    double y;
    double try_x;
    double try_y;

    double est;
    double best_est;
    double old_est;

    double diff;
    double variation;

    double beta;
    unsigned int accept;
  public:
    MCMC();
    void run();
  private:
    void iteration(const unsigned int &iter_nr);
};

#endif //_MCMC_H