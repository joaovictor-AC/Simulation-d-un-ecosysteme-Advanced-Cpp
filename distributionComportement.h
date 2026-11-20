#ifndef DISTRIBUTION_COMPORTEMENT_H
#define DISTRIBUTION_COMPORTEMENT_H

#include "Comportement.h"

#include <vector>

enum class TypeComportement {
    GREGAIRE,
    PEUREUSE,
    KAMIKAZE,
    PREVOYANTE,
    MULTIPLE
};

struct ConfigComportement {
    TypeComportement type;
    double probabilite;
};

using DistributionComportement = std::vector<ConfigComportement>;

#endif
