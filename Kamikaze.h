#include "Comportement.h"
#include "Couleur.h"

class Kamikaze : public Comportement {
public:
    void agir(
        Bestiole& b,
        const std::vector<Bestiole*>& proches,
        Bestiole* plusProche
    ) override;

    Comportement* clone() const override {
        return new Kamikaze(*this);
    }

    Couleur getCouleur() const override {
        return {255, 0, 0};
    }
};
