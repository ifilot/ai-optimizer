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

const double& Chromosome::get_space() const {
  return this->space;
}

const unsigned int& Chromosome::get_space_rank() const {
  return this->space_rank;
}

const unsigned int& Chromosome::get_fitness_rank() const {
  return this->fitness_rank;
}

unsigned int Chromosome::get_rank_space() const {
  return this->fitness_rank + this->space_rank;
}

void Chromosome::set_space_rank(unsigned int rank) {
  this->space_rank = rank;
}

void Chromosome::set_fitness_rank(unsigned int rank) {
  this->fitness_rank = rank;
}

double Chromosome::distance(const Chromosome* _leader) {
  double dist = (pow(this->get_x() - _leader->get_x(),2.0) + pow(this->get_y() - _leader->get_y(),2.0) );
  if(dist == 0) {
    return 1e23; // some large number
  } else {
    return 1.0 / dist;
  }
}

void Chromosome::set_space(unsigned int idx, const std::vector<Chromosome> *chromosomes) {
  this->space = 0;
  for(unsigned int i=0; i < idx; i++) {
    this->space += this->distance(&chromosomes->at(i));
  }
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

bool operator == (Chromosome &cP1, Chromosome &cP2) {
  return cP1.get_x() == cP2.get_x() &&
         cP1.get_y() == cP2.get_y();
}

bool operator == (const Chromosome &cP1, const Chromosome &cP2) {
  return cP1.get_x() == cP2.get_x() &&
         cP1.get_y() == cP2.get_y();
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
  Chromosome* spawn;
  do {
    spawn = new Chromosome(this->chromosomes[_parent_id]);
    spawn->mutate(this->variation);  
  } while(!this->spawn_chromosome(spawn));
}

void GeneticAlgorithm::mate_chromosomes(const unsigned int &_parent_id1, 
                                        const unsigned int &_parent_id2) {
  Chromosome cr1(this->chromosomes[_parent_id1].get_x(), 
                 this->chromosomes[_parent_id2].get_y());
  Chromosome cr2(this->chromosomes[_parent_id2].get_x(), 
                 this->chromosomes[_parent_id1].get_y());
  this->spawn_chromosome(&cr1);
  this->spawn_chromosome(&cr2);
}

bool GeneticAlgorithm::spawn_chromosome(const Chromosome* spawnling) {
  for(unsigned int i=0; i<this->chromosomes.size(); i++) {
    if(this->chromosomes[i] == *spawnling) {
      return false;
    }
  }
  this->chromosomes.push_back(*spawnling);
  this->chromosomes.back().calculate_fitness(this->fptr);
  return true;
}

void GeneticAlgorithm::run() {
  bool found = false;
  this->genesis();
  for(unsigned int i=0; i<1000 && !found; i++) {
    this->iteration();
    for(unsigned int j=0; j<this->chromosomes.size(); j++) {
      if(this->chromosomes[j].get_fitness() > 8.75) {
        std::cout << "Optimum found at generation " << i << std::endl;
        found = true;
        break;
      }
    }
    this->store_genes();
  }
  this->store_genes();
}

void GeneticAlgorithm::natural_selection() {
  if(this->chromosomes.size() < max_nr_chromosomes) {
    return;
  }

  std::vector<Chromosome> new_gene_pool;
  float chance = 1.0;

  for(unsigned int i=0; i<this->chromosomes.size(); i++) {
    if(this->get_random_number(0,1) < chance) {
      new_gene_pool.push_back(this->chromosomes[i]);
    }
    chance *= this->rank_chance;
  }
  this->chromosomes = new_gene_pool; // make the survival chance increasingly smaller
}

void GeneticAlgorithm::iteration() {
  unsigned int size = this->chromosomes.size();

  for(unsigned int i=0; i<size; i++) {
    this->create_new_chromosome(i);
  }

  if(size >= 4) {
    unsigned int r2;
    for(unsigned int i=0; i<size; i++) {
      do {
        r2 = (unsigned int)this->get_random_number(0, size-1); 
      } while(i == r2);
      this->mate_chromosomes(i, r2);
    }
  }

  this->sort_by_rank_space();
  this->natural_selection();
}

void GeneticAlgorithm::print_gene_pool() {
  for(unsigned int i=0; i<this->chromosomes.size(); i++) {
    std::cout << "Gene" << (i+1) << "\t" << this->chromosomes[i].get_x() << "," <<
    this->chromosomes[i].get_y() << "\tFitness = " << this->chromosomes[i].get_fitness() 
    << "\tSpace = " << this->chromosomes[i].get_space() << "\t"
    << this->chromosomes[i].get_space_rank() << " "
    << this->chromosomes[i].get_fitness_rank() << " "
    << this->chromosomes[i].get_fitness_rank() + this->chromosomes[i].get_space_rank()
    << " " << std::endl;
  }
}

void GeneticAlgorithm::sort_by_fitness() {
  while(this->bubble_sort_by_fitness() != 0);
}

void GeneticAlgorithm::sort_by_rank_space() {
  // first perform a sort by fitness
  while(this->bubble_sort_by_fitness() != 0);

  // take the first chromosome and make a copy
  this->chromosomes[0].set_space_rank(this->chromosomes.size());
  this->chromosomes[0].set_fitness_rank(0);
  for(unsigned int i=1; i<this->chromosomes.size(); i++) {
    this->chromosomes[i].set_space(i, &this->chromosomes);
    this->chromosomes[i].set_fitness_rank(i);
  }

  while(this->bubble_sort_by_space() != 0);

  for(unsigned int i=0; i<this->chromosomes.size() - 1; i++) {
    this->chromosomes[i].set_space_rank(i);
  }

  while(this->bubble_sort_by_rank_space() != 0);
}

unsigned int GeneticAlgorithm::bubble_sort_by_fitness() {
  unsigned int nr_swap = 0;
  for(unsigned int i=0; i<this->chromosomes.size(); i++) {
    if(this->chromosomes[i].get_fitness() < this->chromosomes[i+1].get_fitness()) { // swap them
      std::iter_swap(this->chromosomes.begin() + i, this->chromosomes.begin() + i + 1);
      nr_swap++;
    }
  }
  return nr_swap;
}

unsigned int GeneticAlgorithm::bubble_sort_by_space() {
  unsigned int nr_swap = 0;
  for(unsigned int i=1; i<this->chromosomes.size() - 1; i++) {
    if(this->chromosomes[i].get_space() > this->chromosomes[i+1].get_space()) { // swap them
      std::iter_swap(this->chromosomes.begin() + i, this->chromosomes.begin() + i + 1);
      nr_swap++;
    }
  }
  return nr_swap;
}

unsigned int GeneticAlgorithm::bubble_sort_by_rank_space() {
  unsigned int nr_swap = 0;
  for(unsigned int i=1; i<this->chromosomes.size() - 1; i++) {
    if(this->chromosomes[i].get_rank_space() > this->chromosomes[i+1].get_rank_space()) { // swap them
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

unsigned int GeneticAlgorithm::get_nr_chromosomes() const {
  return this->chromosomes.size();
}