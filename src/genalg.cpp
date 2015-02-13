#include "genalg.h"

Chromosome::Chromosome() {
  this->x = 0;
  this->y = 0;
  this->fitness = 0;
}

Chromosome::Chromosome(const double &_x, const double &_y) {
  this->x = _x;
  this->y = _y;
}

void Chromosome::calculate_fitness(TrialFunction *_tf) {
  this->fitness = _tf->calc(this->x, this->y);
}

const double& Chromosome::get_x() const {
  return this->x;
}

const double& Chromosome::get_y() const {
  return this->y;
}

const double& Chromosome::get_fitness() const {
  return this->fitness;
}

void Chromosome::mutate(const float& _variation) {
  float d = 0;
  if(this->get_random_number(0,1) > 0.5) { // vary x
    do {
      d = get_random_number(-_variation, _variation);
    } while(this->x + d < 0 || this->x + d > 4 * PI);
    this->x += d;
  } else { //vary y
    do {
      d = get_random_number(-_variation, _variation);
    } while(this->y + d < 0 || this->y + d > 4 * PI);
    this->y += d;
  }
}

double Chromosome::get_random_number(double min = 0.0, double max = 1.0) {
    return rand() / (double)RAND_MAX * (max - min) + min;
}

GeneticAlgorithm::GeneticAlgorithm() { // start with the generation 0 chromosome
  this->init();
}

void GeneticAlgorithm::genesis() {
  this->chromosomes.push_back(Chromosome(this->get_random_number(0,1), this->get_random_number(0,1)));
  this->max_nr_chromosomes = 32;
  this->variation = 3;
  this->rank_chance = 0.95;
  this->chromosomes.back().calculate_fitness(this->fptr);
}

void GeneticAlgorithm::create_new_chromosome(const unsigned int &_parent_id) {
  this->chromosomes.push_back(this->chromosomes[_parent_id]);
  this->chromosomes.back().mutate(this->variation);
  this->chromosomes.back().calculate_fitness(this->fptr);
}

void GeneticAlgorithm::run() {
  this->genesis();
  for(unsigned int i=0; i<50; i++) {
    this->iteration();
    this->store_genes();
  }
}

void GeneticAlgorithm::natural_selection() {
  if(this->chromosomes.size() < max_nr_chromosomes) {
    return;
  }

  std::vector<Chromosome> new_gene_pool;
  float chance = this->rank_chance;

  for(unsigned int i=0; i<this->chromosomes.size(); i++) {
    if(new_gene_pool.size() == 0 && i == this->chromosomes.size()-1) {
      new_gene_pool.push_back(this->chromosomes[i]);
    } else if(this->get_random_number(0,1) < chance) {
      new_gene_pool.push_back(this->chromosomes[i]);
    }
    chance *= this->rank_chance;
  }
  this->chromosomes = new_gene_pool;
}

void GeneticAlgorithm::iteration() {
  const unsigned int size = this->chromosomes.size();
  for(unsigned int i=0; i<size; i++) {
    this->create_new_chromosome(i);
  }
  this->sort_by_fitness();
  this->natural_selection();
}

void GeneticAlgorithm::print_gene_pool() {
  for(unsigned int i=0; i<this->chromosomes.size(); i++) {
    std::cout << "Gene" << (i+1) << "\t" << this->chromosomes[i].get_x() << "," <<
    this->chromosomes[i].get_y() << "\tFitness = " << this->chromosomes[i].get_fitness() 
    << std::endl;
  }
}

void GeneticAlgorithm::sort_by_fitness() {
  while(this->bubble_sort() != 0);
}

unsigned int GeneticAlgorithm::bubble_sort() {
  unsigned int nr_swap = 0;
  for(unsigned int i=0; i<this->chromosomes.size() - 1; i++) {
    if(this->chromosomes[i].get_fitness() < this->chromosomes[i+1].get_fitness()) { // swap them
      std::iter_swap(this->chromosomes.begin() + i, this->chromosomes.begin() + i + 1);
      nr_swap++;
    }
  }
  return nr_swap;
}

void GeneticAlgorithm::store_genes() {
  for(unsigned int i=0; i<this->chromosomes.size(); i++)  {
    this->output_x.push_back(this->chromosomes[i].get_x() );
    this->output_y.push_back(this->chromosomes[i].get_y() );
    this->output_value.push_back(this->chromosomes[i].get_fitness() );
  }
}