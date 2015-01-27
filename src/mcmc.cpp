#include "mcmc.h"

MCMC::MCMC() {
  this->init(); // get this from parent class
  this->best_x = 0;
  this->best_y = 0;
  this->best_est = 0.0;
  this->try_x = 0;
  this->try_y = 0;
  this->old_est = 0;
  this->diff = 0;
  this->variation = 1.00;
  this->beta = 0.0001;
  this->accept = 0;
  this->nr_iter = 100;
}

void MCMC::run() {
  // Start performing MCMC algorithm
  this->flag_moat = false;
  this->output = true;
  this->x = this->get_random_number(0,1);
  this->y = this->get_random_number(0,1);
  
  for(unsigned i=0; i<this->nr_iter; i++) {
    this->iteration(i);
  }
}

void MCMC::iteration(const unsigned int &iter_nr) {
  if(output) std::cout << iter_nr+1 << std::endl;
    if(iter_nr != 0) {
        double c = this->get_random_number(0,2);
        if(c < 1) {
            do {
               try_x += this->get_random_number(-1.0, 1.0) * variation;
            } while(try_x < 0 || try_x > 4*PI);
            try_y = y; 
        } else {
            do {
               try_y += this->get_random_number(-1.0, 1.0) * variation;
            } while(try_y < 0 || try_y > 4*PI);
            try_x = x;
        }
        est = this->func_ptr(try_x, try_y, this->flag_moat);

        if(output) std::cout << "Checking:\t" << try_x << "," << try_y << " (" << est << ")" << std::endl;

        diff = est - old_est;
        double chance = exp(diff * beta);
        double roll = this->get_random_number(0,1);
        if(diff > 0) { // accept new result
            x = try_x;
            y = try_y;
            accept++;
            old_est = est;
            if(output) std::cout << "This state was accepted" << std::endl;
        } else if(chance < roll) {
            x = try_x;
            y = try_y;
            accept++;
            if(output) std::cout << "Chance = " << (1.0-chance) << "\t" << "Roll = " << roll << std::endl;
            old_est = est;
        } else {
            if(output) std::cout << "This state was rejected" << std::endl;
        }

        // store best result so far
        if(est > best_est) {
            best_x = x;
            best_y = y;
            best_est = est;
        }
    }

    if(output) std::cout << "Current value:\t" << x << "," << y << std::endl;
}