#ifndef _GENALG_H
#define _GENALG_H

#include "optimizer.h"
#include "trial_function.h"

class Chromosome {
private:
  double x,y,fitness;
public:
  Chromosome();
  Chromosome(const double &_x, const double &_y);
  void calculate_fitness(TrialFunction *_tf);
  const double& get_fitness() const;
  void mutate(const float& _variation);
  const double& get_x() const;
  const double& get_y() const;
private:
  double get_random_number(double min, double max);
};

class GeneticAlgorithm : public Optimizer {
private:
  std::vector<Chromosome> chromosomes;
  unsigned int max_nr_chromosomes;
  float variation;
public:
  GeneticAlgorithm();
  void run();
  void print_gene_pool();
private:
  void genesis(); // create gene 0
  void create_new_chromosome(const unsigned int &_parent_id);
  void iteration();
};

#endif //_GENALG_H