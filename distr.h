#ifndef DISTR_H_
#define DISTR_H_

#include <random>

#include "defines.h"
#include "Scheme.h"

static std::random_device RD;
static std::mt19937_64 GEN(RD());
static std::uniform_int_distribution<ZmodQ> U;											// uniform in ZmodQ
static std::normal_distribution<> DG(0,STDEV);											// Error distribution
static std::normal_distribution<> DGstar(0, STDEV_star);								// Error distribution

#endif /* DISTR_H_ */