#include "Comportement.h"
#include "Couleur.h"

class Peureuse : public Comportement {
public:
    void agir(
        Bestiole& b,
        const std::vector<Bestiole*>& proches,
        Bestiole* plusProche
    ) override;

    Comportement* clone() const override {
        return new Peureuse(*this);
    }

    Couleur getCouleur() const override {
        return {0, 0, 255};
    }
};
