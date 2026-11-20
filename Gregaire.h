#include "Comportement.h"
#include "Couleur.h"

class Gregaire : public Comportement {
public:
    void agir(
        Bestiole& b,
        const std::vector<Bestiole*>& proches,
        Bestiole* plusProche
    ) override;

    Comportement* clone() const override {
        return new Gregaire(*this);
    }

    Couleur getCouleur() const override {
        return {0, 255, 0};
    }
};
