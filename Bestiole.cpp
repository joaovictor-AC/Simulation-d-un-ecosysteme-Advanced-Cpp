#include "Bestiole.h"
#include "Milieu.h"
#include "Comportement.h"
#include "Aleatoire.h"
#include <cmath>
#include <limits>
#include <stdexcept>
#include <utility>

int Bestiole::next = 0;

Bestiole::Bestiole(const ConfigParams& c)
    : id(++next), ageLimite(0), orientation(0.), vitesse(0.), vitesseCroisiere(0.), config(c),
      equipement(new SansEquipement) {
    config.valider();
    ageLimite = Aleatoire::entier(config.ageLimiteMin, config.ageLimiteMax);
    orientation = Aleatoire::reel(0., 2. * PI);
    vitesse = vitesseCroisiere = Aleatoire::reel(config.vitesseMin, config.vitesseMax);
    comportement = creerComportement(BehaviorType::GREGAIRE, config);
}
Bestiole::Bestiole(const Bestiole& b)
    : id(++next), age(b.age), ageLimite(b.ageLimite), x(b.x), y(b.y), orientation(b.orientation),
      vitesse(b.vitesse), vitesseCroisiere(b.vitesseCroisiere), marqueeMorte(b.marqueeMorte), config(b.config),
      comportement(b.comportement->clone()), equipement(b.equipement->clone()) {}
Bestiole& Bestiole::operator=(const Bestiole& b) {
    if (this != &b) {
        Bestiole copie(b);
        copie.id = id;
        *this = std::move(copie);
    }
    return *this;
}
Bestiole::Bestiole(Bestiole&&) noexcept = default;
Bestiole& Bestiole::operator=(Bestiole&&) noexcept = default;
Bestiole::~Bestiole() = default;

Bestiole Bestiole::clone() const {
    Bestiole enfant(*this);
    enfant.age = 0;
    enfant.marqueeMorte = false;
    return enfant;
}
void Bestiole::action(Milieu& milieu) {
    if (estMorte()) return;
    // Le Milieu initial n'expose pas sa population : il gere seulement le mouvement.
    // Les interactions restent disponibles via detecterProches(), agir() et collision().
    bouge(milieu.getWidth(), milieu.getHeight());
}
void Bestiole::agir(const Detection& detection) {
    if (!estMorte()) comportement->agir(*this, detection.proches, detection.plusProche);
}
void Bestiole::bouge(int xLim, int yLim) {
    if (xLim <= 0 || yLim <= 0) throw std::invalid_argument("Dimensions du milieu invalides");
    if (estMorte()) return;
    double nx = x + std::cos(orientation) * getVitesseEffective();
    double ny = y - std::sin(orientation) * getVitesseEffective();
    // Repli sur les bords, y compris plusieurs rebonds dans un seul pas.
    const auto replier = [](double& position, int limite) {
        if (limite == 1) { position = 0.; return false; }
        const double bord = limite - 1.;
        position = std::fmod(position, 2. * bord);
        if (position < 0.) position += 2. * bord;
        if (position > bord) { position = 2. * bord - position; return true; }
        return false;
    };
    if (replier(nx, xLim)) setOrientation(PI - orientation);
    if (replier(ny, yLim)) setOrientation(-orientation);
    x = nx;
    y = ny;
}
void Bestiole::collision(const Bestiole& autre) {
    if (estMorte() || *this == autre) return;
    // Un seul tirage apres application de la carapace (pas p * p).
    if (Aleatoire::evenement(getProbaMortCollision())) mourir();
    else setOrientation(orientation + PI);
}
void Bestiole::vieillir() {
    if (!estMorte() && ++age >= ageLimite) mourir();
}
double Bestiole::distance(const Bestiole& b) const { return std::hypot(x - b.x, y - b.y); }
bool Bestiole::enCollision(const Bestiole& b) const {
    return !(*this == b) && !estMorte() && !b.estMorte() && distance(b) < (getTaille() + b.getTaille()) / 2.;
}
bool Bestiole::jeTeVois(const Bestiole& b) const {
    return !(*this == b) && !estMorte() && !b.estMorte() && equipement->detecte(*this, b);
}
Detection Bestiole::detecterProches(const std::vector<Bestiole>& bestioles) const {
    Detection resultat;
    double minimum = std::numeric_limits<double>::infinity();
    for (const Bestiole& autre : bestioles) {
        if (!jeTeVois(autre)) continue;
        resultat.proches.push_back(&autre);
        const double d = distance(autre);
        if (d < minimum) { minimum = d; resultat.plusProche = &autre; }
    }
    return resultat;
}
std::vector<const Bestiole*> Bestiole::detecterCollisions(const std::vector<Bestiole>& bestioles) const {
    std::vector<const Bestiole*> resultat;
    for (const Bestiole& autre : bestioles)
        if (enCollision(autre)) resultat.push_back(&autre);
    return resultat;
}
void Bestiole::setComportement(std::unique_ptr<Comportement> c) {
    if (!c) throw std::invalid_argument("Une bestiole doit avoir un comportement");
    comportement = std::move(c);
    vitesse = vitesseCroisiere;
}
void Bestiole::setComportement(const Comportement& c) { setComportement(c.clone()); }
void Bestiole::setComportement(BehaviorType type) { setComportement(creerComportement(type, config)); }
void Bestiole::setOrientation(double angle) {
    if (!std::isfinite(angle)) throw std::invalid_argument("Orientation non finie");
    orientation = std::fmod(angle, 2. * PI);
    if (orientation < 0.) orientation += 2. * PI;
}
void Bestiole::setVitesse(double valeur) {
    if (!std::isfinite(valeur) || valeur < 0. || !std::isfinite(valeur * config.nu))
        throw std::invalid_argument("Vitesse invalide");
    vitesse = valeur;
}
void Bestiole::setPosition(double px, double py) {
    if (!std::isfinite(px) || !std::isfinite(py)) throw std::invalid_argument("Position non finie");
    x = px;
    y = py;
}
double Bestiole::getVitesseEffective() const { return equipement->vitesse(vitesse); }
double Bestiole::getProbaMortCollision() const { return equipement->probaMort(config.probaMortCollision); }
double Bestiole::getCamouflage() const { return equipement->camouflage(); }
BehaviorType Bestiole::getTypeComportement() const { return comportement->type(); }
const Comportement& Bestiole::getComportement() const { return *comportement; }
bool Bestiole::possede(TypeEquipement type) const { return equipement->possede(type); }
void Bestiole::equiperYeux() {
    if (!possede(TypeEquipement::YEUX)) equipement.reset(new Yeux(std::move(equipement), config));
}
void Bestiole::equiperOreilles() {
    if (!possede(TypeEquipement::OREILLES)) equipement.reset(new Oreilles(std::move(equipement), config));
}
void Bestiole::equiperCarapace() {
    if (!possede(TypeEquipement::CARAPACE)) equipement.reset(new Carapace(std::move(equipement), config));
}
void Bestiole::equiperNageoires() {
    if (!possede(TypeEquipement::NAGEOIRES)) equipement.reset(new Nageoires(std::move(equipement), config));
}
void Bestiole::equiperCamouflage() {
    if (!possede(TypeEquipement::CAMOUFLAGE)) equipement.reset(new Camouflage(std::move(equipement), config));
}
void Bestiole::initCoords(int xLim, int yLim) {
    if (xLim <= 0 || yLim <= 0) throw std::invalid_argument("Dimensions du milieu invalides");
    x = Aleatoire::reel(0., xLim - 1.);
    y = Aleatoire::reel(0., yLim - 1.);
}
void Bestiole::draw(UImg& support) const {
    if (estMorte()) return;
    static const T couleurs[5][3] = {{50, 130, 220}, {40, 170, 80}, {220, 60, 50}, {220, 160, 20}, {150, 60, 200}};
    const T* couleur = couleurs[static_cast<std::size_t>(getTypeComportement())];
    const T noir[] = {30, 30, 30};
    const T gris[] = {120, 120, 120};
    const double rayon = getTaille() / 2.;
    const int cx = static_cast<int>(std::round(x)), cy = static_cast<int>(std::round(y));
    const int xt = static_cast<int>(x + std::cos(orientation) * rayon / 2.1);
    const int yt = static_cast<int>(y - std::sin(orientation) * rayon / 2.1);
    const float opacite = possede(TypeEquipement::CAMOUFLAGE) ? 0.45f : 1.f;
    if (possede(TypeEquipement::CARAPACE)) support.draw_circle(cx, cy, static_cast<int>(rayon), gris, 0.5f);
    if (possede(TypeEquipement::NAGEOIRES)) {
        const int fx = static_cast<int>(std::sin(orientation) * rayon);
        const int fy = static_cast<int>(std::cos(orientation) * rayon);
        support.draw_line(cx - fx, cy - fy, cx + fx, cy + fy, couleur, opacite);
    }
    support.draw_ellipse(cx, cy, rayon, rayon / 5., -orientation / PI * 180., couleur, opacite);
    support.draw_circle(xt, yt, static_cast<int>(rayon / 2.), couleur, opacite);
    if (possede(TypeEquipement::YEUX)) support.draw_circle(xt, yt, 1, noir);
    if (possede(TypeEquipement::OREILLES)) support.draw_circle(cx, cy, 2, noir);
}
