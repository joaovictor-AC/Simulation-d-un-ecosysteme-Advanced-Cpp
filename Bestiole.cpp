#include "Bestiole.h"
#include "Milieu.h"
#include "Comportement.h"
#include "Aleatoire.h"
#include "Gregaire.h"
#include <cmath>
#include <limits>
#include <stdexcept>
#include <utility>

namespace { constexpr double PI = 3.14159265358979323846; }

int Bestiole::next = 0;

const int Bestiole::NB_MAX = 3;
const int Bestiole::DUREE_FUITE = 20;
const double Bestiole::FACTEUR_FUITE = 3.;
const int Bestiole::HORIZON = 10;
const int Bestiole::DUREE_PERSONNALITE_MIN = 50;
const int Bestiole::DUREE_PERSONNALITE_MAX = 149;

Bestiole::Bestiole()
    : Bestiole(Aleatoire::entier(1000, 2000), Aleatoire::reel(1., 4.),
               Aleatoire::reel(12., 20.), Aleatoire::reel(0.05, 0.30))
{
    equiperYeux(Aleatoire::reel(50., 200.), Aleatoire::reel(PI / 6., 2. * PI / 3.),
                Aleatoire::reel(0.5, 1.));
    equiperOreilles(Aleatoire::reel(50., 250.), Aleatoire::reel(0.5, 1.));
    equiperNageoires(Aleatoire::reel(1., 2.));
    equiperCarapace(Aleatoire::reel(1., 3.), Aleatoire::reel(1., 2.));
    equiperCamouflage(Aleatoire::reel(0.1, 0.9));
}


//// VERIFIER, COMMENCER AVEC LE COMPORTEMENT GREGAIRE

Bestiole::Bestiole(int ageLimite, double vitesseCroisiere, double taille, double probaMortCollision)
    : id(++next), ageLimite(ageLimite), orientation(Aleatoire::reel(0., 2. * PI)),
      vitesse(vitesseCroisiere), vitesseCroisiere(vitesseCroisiere),
      taille(taille), probaMortCollision(probaMortCollision), comportement(new Gregaire)
{
    if (ageLimite <= 0 || !std::isfinite(vitesseCroisiere) || vitesseCroisiere < 0. ||
        !std::isfinite(taille) || taille <= 0. || !std::isfinite(probaMortCollision) ||
        probaMortCollision < 0. || probaMortCollision > 1.)
        throw std::invalid_argument("Parametres de Bestiole invalides");
}

Bestiole::Bestiole(const Bestiole &b)
    : id(++next), age(b.age), ageLimite(b.ageLimite), x(b.x), y(b.y), orientation(b.orientation),
      vitesse(b.vitesse), vitesseCroisiere(b.vitesseCroisiere), taille(b.taille),
      probaMortCollision(b.probaMortCollision), marqueeMorte(b.marqueeMorte),
      comportement(b.comportement->clone()),
      yeux(b.yeux ? new Yeux(*b.yeux) : nullptr),
      oreilles(b.oreilles ? new Oreilles(*b.oreilles) : nullptr),
      carapace(b.carapace ? new Carapace(*b.carapace) : nullptr),
      nageoires(b.nageoires ? new Nageoires(*b.nageoires) : nullptr),
      camouflage(b.camouflage ? new Camouflage(*b.camouflage) : nullptr) {}
Bestiole &Bestiole::operator=(const Bestiole &b)
{
    if (this != &b)
    {
        Bestiole copie(b);
        copie.id = id;
        *this = std::move(copie);
    }
    return *this;
}
Bestiole::Bestiole(Bestiole &&) noexcept = default;
Bestiole &Bestiole::operator=(Bestiole &&) noexcept = default;
Bestiole::~Bestiole() = default;

Bestiole Bestiole::clone() const
{
    Bestiole enfant(*this);
    enfant.age = 0;
    enfant.marqueeMorte = false;
    return enfant;
}
void Bestiole::action(Milieu &milieu)
{
    if (estMorte())
        return;
    // Le Milieu initial n'expose pas sa population : il gere seulement le mouvement.
    // Les interactions restent disponibles via detecterProches(), agir() et collision().
    bouge(milieu.getWidth(), milieu.getHeight());
}
void Bestiole::agir(const Detection &detection)
{
    if (!estMorte())
        comportement->agir(*this, detection.proches, detection.plusProche);
}
void Bestiole::bouge(int xLim, int yLim)
{
    if (xLim <= 0 || yLim <= 0)
        throw std::invalid_argument("Dimensions du milieu invalides");
    if (estMorte())
        return;
    double nx = x + std::cos(orientation) * getVitesseEffective();
    double ny = y - std::sin(orientation) * getVitesseEffective();
    // Repli sur les bords, y compris plusieurs rebonds dans un seul pas.
    const auto replier = [](double &position, int limite)
    {
        if (limite == 1)
        {
            position = 0.;
            return false;
        }
        const double bord = limite - 1.;
        position = std::fmod(position, 2. * bord);
        if (position < 0.)
            position += 2. * bord;
        if (position > bord)
        {
            position = 2. * bord - position;
            return true;
        }
        return false;
    };
    if (replier(nx, xLim))
        setOrientation(PI - orientation);
    if (replier(ny, yLim))
        setOrientation(-orientation);
    x = nx;
    y = ny;
}
void Bestiole::collision(const Bestiole &autre)
{
    if (estMorte() || *this == autre)
        return;
    // Un seul tirage apres application de la carapace (pas p * p).
    if (Aleatoire::evenement(getProbaMortCollision()))
        mourir();
    else
        setOrientation(orientation + PI);
}
void Bestiole::vieillir()
{
    if (!estMorte() && ++age >= ageLimite)
        mourir();
}
double Bestiole::distance(const Bestiole &b) const { return std::hypot(x - b.x, y - b.y); }
bool Bestiole::enCollision(const Bestiole &b) const
{
    return !(*this == b) && !estMorte() && !b.estMorte() && distance(b) < (getTaille() + b.getTaille()) / 2.;
}
bool Bestiole::jeTeVois(const Bestiole &b) const
{
    if (*this == b || estMorte() || b.estMorte()) return false;
    const double d = distance(b);
    if (oreilles && d <= oreilles->distance && oreilles->gamma > b.getCamouflage()) return true;
    if (!yeux || d > yeux->distance || yeux->gamma <= b.getCamouflage()) return false;
    const double direction = std::atan2(y - b.y, b.x - x);
    return d == 0. || std::abs(std::remainder(direction - orientation, 2. * PI)) <= yeux->angle / 2.;
}
Detection Bestiole::detecterProches(
    std::vector<Bestiole> &bestioles) const
{
    Detection resultat;
    double minimum = std::numeric_limits<double>::infinity();

    for (Bestiole &autre : bestioles)
    {
        if (!jeTeVois(autre))
            continue;

        resultat.proches.push_back(&autre);

        const double d = distance(autre);
        if (d < minimum)
        {
            minimum = d;
            resultat.plusProche = &autre;
        }
    }
    return resultat;
}
std::vector<const Bestiole *> Bestiole::detecterCollisions(const std::vector<Bestiole> &bestioles) const
{
    std::vector<const Bestiole *> resultat;
    for (const Bestiole &autre : bestioles)
        if (enCollision(autre))
            resultat.push_back(&autre);
    return resultat;
}
void Bestiole::setComportement(std::unique_ptr<Comportement> c)
{
    if (!c)
        throw std::invalid_argument("Une bestiole doit avoir un comportement");
    comportement = std::move(c);
    vitesse = vitesseCroisiere;
}
void Bestiole::setComportement(const Comportement &c)
{
    setComportement(
        std::unique_ptr<Comportement>(c.clone()));
}
void Bestiole::setOrientation(double angle)
{
    if (!std::isfinite(angle))
        throw std::invalid_argument("Orientation non finie");
    orientation = std::fmod(angle, 2. * PI);
    if (orientation < 0.)
        orientation += 2. * PI;
}
void Bestiole::setVitesse(double valeur)
{
    if (!std::isfinite(valeur) || valeur < 0. || !std::isfinite(valeur * (nageoires ? nageoires->nu : 1.)))
        throw std::invalid_argument("Vitesse invalide");
    vitesse = valeur;
}
void Bestiole::setPosition(double px, double py)
{
    if (!std::isfinite(px) || !std::isfinite(py))
        throw std::invalid_argument("Position non finie");
    x = px;
    y = py;
}
double Bestiole::getVitesseEffective() const {
    return vitesse * (nageoires ? nageoires->nu : 1.) / (carapace ? carapace->eta : 1.);
}
double Bestiole::getProbaMortCollision() const {
    return probaMortCollision / (carapace ? carapace->omega : 1.);
}
double Bestiole::getCamouflage() const { return camouflage ? camouflage->psi : 0.; }
const Comportement &Bestiole::getComportement() const { return *comportement; }
bool Bestiole::possede(TypeEquipement type) const {
    switch (type) {
    case TypeEquipement::YEUX: return bool(yeux);
    case TypeEquipement::OREILLES: return bool(oreilles);
    case TypeEquipement::CARAPACE: return bool(carapace);
    case TypeEquipement::NAGEOIRES: return bool(nageoires);
    case TypeEquipement::CAMOUFLAGE: return bool(camouflage);
    }
    return false;
}
void Bestiole::equiperYeux(double distance, double angle, double gamma) {
    if (!std::isfinite(distance) || distance <= 0. || !std::isfinite(angle) || angle <= 0. ||
        angle > 2. * PI || !std::isfinite(gamma) || gamma < 0. || gamma > 1.)
        throw std::invalid_argument("Parametres des yeux invalides");
    yeux.reset(new Yeux(distance, angle, gamma));
}
void Bestiole::equiperOreilles(double distance, double gamma) {
    if (!std::isfinite(distance) || distance <= 0. || !std::isfinite(gamma) || gamma < 0. || gamma > 1.)
        throw std::invalid_argument("Parametres des oreilles invalides");
    oreilles.reset(new Oreilles(distance, gamma));
}
void Bestiole::equiperCarapace(double omega, double eta) {
    if (!std::isfinite(omega) || omega < 1. || !std::isfinite(eta) || eta < 1.)
        throw std::invalid_argument("Parametres de carapace invalides");
    carapace.reset(new Carapace(omega, eta));
}
void Bestiole::equiperNageoires(double nu) {
    if (!std::isfinite(nu) || nu < 1. || !std::isfinite(vitesse * nu) || !std::isfinite(vitesseCroisiere * nu))
        throw std::invalid_argument("Coefficient de nageoires invalide");
    nageoires.reset(new Nageoires(nu));
}
void Bestiole::equiperCamouflage(double valeur) {
    if (!std::isfinite(valeur) || valeur < 0. || valeur > 1.)
        throw std::invalid_argument("Camouflage hors de [0, 1]");
    camouflage.reset(new Camouflage(valeur));
}
void Bestiole::initCoords(int xLim, int yLim)
{
    if (xLim <= 0 || yLim <= 0)
        throw std::invalid_argument("Dimensions du milieu invalides");
    x = Aleatoire::reel(0., xLim - 1.);
    y = Aleatoire::reel(0., yLim - 1.);
}
void Bestiole::draw(UImg &support) const
{
    if (estMorte())
        return;
    const Couleur rgb = comportement->getCouleur();
    const T couleur[] = {static_cast<T>(rgb[0]), static_cast<T>(rgb[1]), static_cast<T>(rgb[2])};
    const T noir[] = {30, 30, 30};
    const T gris[] = {120, 120, 120};
    const double rayon = getTaille() / 2.;
    const int cx = static_cast<int>(std::round(x)), cy = static_cast<int>(std::round(y));
    const int xt = static_cast<int>(x + std::cos(orientation) * rayon / 2.1);
    const int yt = static_cast<int>(y - std::sin(orientation) * rayon / 2.1);
    const float opacite = possede(TypeEquipement::CAMOUFLAGE) ? 0.45f : 1.f;
    if (possede(TypeEquipement::CARAPACE))
        support.draw_circle(cx, cy, static_cast<int>(rayon), gris, 0.5f);
    if (possede(TypeEquipement::NAGEOIRES))
    {
        const int fx = static_cast<int>(std::sin(orientation) * rayon);
        const int fy = static_cast<int>(std::cos(orientation) * rayon);
        support.draw_line(cx - fx, cy - fy, cx + fx, cy + fy, couleur, opacite);
    }
    support.draw_ellipse(cx, cy, rayon, rayon / 5., -orientation / PI * 180., couleur, opacite);
    support.draw_circle(xt, yt, static_cast<int>(rayon / 2.), couleur, opacite);
    if (possede(TypeEquipement::YEUX))
        support.draw_circle(xt, yt, 1, noir);
    if (possede(TypeEquipement::OREILLES))
        support.draw_circle(cx, cy, 2, noir);
}
