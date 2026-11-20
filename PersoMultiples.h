#include "Comportement.h"
#include "Couleur.h"

class PersoMultiples : public Comportement {
public:
    void agir(
        Bestiole& b,
        const std::vector<Bestiole*>& proches,
        Bestiole* plusProche
    ) override;

    Comportement* clone() const override {
        return new PersoMultiples(*this);
    }

    Couleur getCouleur() const override {
        return {100, 100, 100};
    }
};
