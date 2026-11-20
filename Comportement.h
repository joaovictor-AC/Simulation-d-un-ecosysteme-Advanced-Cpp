#ifndef COMPORTEMENT_H
#define COMPORTEMENT_H

#include "UImg.h"
#include "Bestiole.h"

#include <vector>

class Comportement {

public:

    virtual ~Comportement() = default;

    virtual Comportement* clone() const = 0;

    virtual void agir(
        Bestiole& b,
        const std::vector<Bestiole*>& proches,
        Bestiole* plusProche
    ) = 0;

    virtual const T* getCouleur() const = 0;

};

#endif
