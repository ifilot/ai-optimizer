#ifndef _GENALG_H
#define _GENALG_H

#include <algorithm>
#include "optimizer.h"
#include "trial_function.h"

class Chromosome {
private:
  double x,y,fitness,space;
  unsigned int space_rank, fitness_rank;
public:
  Chromosome();
  Chromosome(const double &_x, const double &_y);
  void calculate_fitness(TrialFunction *_tf);
  const double& get_fitness() const;
  const double& get_space() const;
  const unsigned int& get_space_rank() const;
  const unsigned int& get_fitness_rank() const;
  void mutate(const float& _variation);
  const double& get_x() const;
  const double& get_y() const;
  void set_space(unsigned int idx, const std::vector<Chromosome> *chromosomes);
  void set_fitness_rank(unsigned int rank);
  void set_space_rank(unsigned int rank);
  double distance(const Chromosome* _leader);
  unsigned int get_rank_space() const;
private:
  double get_random_number(double min, double max);
};

bool operator== (Chromosome &cP1, Chromosome &cP2);
bool operator== (const Chromosome &cP1, const Chromosome &cP2);

class GeneticAlgorithm : public Optimizer {
private:
  std::vector<Chromosome> chromosomes;
  unsigned int max_nr_chromosomes;
  float variation;
  float rank_chance;
public:
  GeneticAlgorithm();
  void run();
  void print_gene_pool();
private:
  void genesis(); // create gene 0
  void create_new_chromosome(const unsigned int &_parent_id);
  void mate_chromosomes(const unsigned int &_parent_id1, 
                                        const unsigned int &_parent_id2);
  bool spawn_chromosome(const Chromosome* spawnling);
  void iteration();
  void natural_selection();
  void sort_by_fitness();
  void sort_by_rank_space();
  void store_genes();
  unsigned int bubble_sort_by_fitness();
  unsigned int bubble_sort_by_space();
  unsigned int bubble_sort_by_rank_space();
};

#endif //_GENALG_H