#include "Prevoyante.h"
#include "Bestiole.h"
#include <cmath>

void Prevoyante::agir(Bestiole& b, const std::vector<Bestiole*>& proches, Bestiole*)
{
    const double bx = std::cos(b.getOrientation());
    const double by = -std::sin(b.getOrientation());
    const double pi = std::acos(-1.);

    for (const Bestiole* o : proches) {
        const double seuil = (b.getTaille() + o->getTaille()) / 2.;

        for (int k = 1; k <= Bestiole::HORIZON; ++k) {
            // Positions des deux bestioles au meme instant futur.
            const double mx = b.getX() + bx * b.getVitesseEffective() * k;
            const double my = b.getY() + by * b.getVitesseEffective() * k;
            const double ox = o->getX() + std::cos(o->getOrientation()) * o->getVitesseEffective() * k;
            const double oy = o->getY() - std::sin(o->getOrientation()) * o->getVitesseEffective() * k;

            if (std::hypot(mx - ox, my - oy) < seuil) {
                const double rx = o->getX() - b.getX();
                const double ry = o->getY() - b.getY();
                const double cote = bx * ry - by * rx;
                b.setOrientation(b.getOrientation() + (cote > 0. ? pi / 4. : -pi / 4.));
                return; // Un seul ajustement par pas.
            }
        }
    }
}
