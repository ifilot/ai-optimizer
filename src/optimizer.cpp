#include "optimizer.h"

Optimizer::Optimizer() {
  this->init();
}

void Optimizer::set_function(TrialFunction &_fptr) {
  this->fptr = &_fptr;
}

void Optimizer::set_output(const bool &flag) {
  this->output = flag;
}

void run() {

}

void Optimizer::init() {
  srand (time(NULL));
  this->flag_moat = false;
  this->output = false;
}

double Optimizer::get_random_number(double min = 0.0, double max = 1.0) {
    return rand() / (double)RAND_MAX * (max - min) + min;
}