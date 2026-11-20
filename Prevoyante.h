#include "Comportement.h"
#include "Couleur.h"

class Prevoyante : public Comportement {
public:
    void agir(
        Bestiole& b,
        const std::vector<Bestiole*>& proches,
        Bestiole* plusProche
    ) override;

    Comportement* clone() const override {
        return new Prevoyante(*this);
    }

    Couleur getCouleur() const override {
        return {255, 255, 0};
    }
};
