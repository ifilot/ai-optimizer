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
    } while(this->x + d < 0);
    this->x += d;
  } else { //vary y
    do {
      d = get_random_number(-_variation, _variation);
    } while(this->y + d < 0);
    y += d;
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
  this->max_nr_chromosomes = 4;
  this->variation = 0.9;
  this->chromosomes.back().calculate_fitness(this->fptr);
}

void GeneticAlgorithm::create_new_chromosome(const unsigned int &_parent_id) {
  this->chromosomes.push_back(this->chromosomes[_parent_id]);
  this->chromosomes.back().mutate(this->variation);
  this->chromosomes.back().calculate_fitness(this->fptr);
}

void GeneticAlgorithm::run() {
  this->genesis();
  this->iteration();
  this->iteration();
  this->iteration();
  this->iteration();
  this->iteration();
  this->iteration();
}

void GeneticAlgorithm::iteration() {
  const unsigned int size = this->chromosomes.size();
  for(unsigned int i=0; i<size; i++) {
    this->create_new_chromosome(i);
  }
  this->sort_by_fitness();
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