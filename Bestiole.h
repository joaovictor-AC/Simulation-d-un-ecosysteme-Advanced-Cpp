#ifndef BESTIOLE_H
#define BESTIOLE_H
#include "UImg.h"
#include "Comportement.h"
#include "Yeux.h"
#include "Oreilles.h"
#include "Carapace.h"
#include "Nageoires.h"
#include "Camouflage.h"
#include <memory>
#include <vector>
enum class TypeEquipement
{
    YEUX,
    OREILLES,
    CARAPACE,
    NAGEOIRES,
    CAMOUFLAGE
};
class Milieu;
class Bestiole;
struct Detection
{
    std::vector<Bestiole *> proches;
    Bestiole *plusProche = nullptr;
};
class Bestiole
{
private:
    static const double MAX_VITESSE;
    static const double LIMITE_VUE;
    static const double TAILLE_MIN, TAILLE_MAX;
    static const int AGE_MIN, AGE_MAX;

    static int next;

private:
    int id;
    int age = 0;
    int ageLimite;
    double x = 0., y = 0.; // Positions reelles pour conserver les petits deplacements.
    double orientation, vitesse, vitesseCroisiere;
    double taille, probaMortCollision;
    bool marqueeMorte = false;
    std::unique_ptr<Comportement> comportement;
    std::unique_ptr<Yeux> yeux;
    std::unique_ptr<Oreilles> oreilles;
    std::unique_ptr<Carapace> carapace;
    std::unique_ptr<Nageoires> nageoires;
    std::unique_ptr<Camouflage> camouflage;

public:
    // Parametres communs aux comportements : valeurs dans Bestiole.cpp.
    static const int NB_MAX;
    static const int DUREE_FUITE;
    static const double FACTEUR_FUITE;
    static const int HORIZON;
    static const int DUREE_PERSONNALITE_MIN, DUREE_PERSONNALITE_MAX;

    Bestiole(); // Attributs et caracteristiques des cinq equipements tires au hasard.
    explicit Bestiole(int ageLimite, double vitesseCroisiere = 2.,
                      double taille = 16., double probaMortCollision = 0.1);
    Bestiole(const Bestiole &);            // Nouvelle identite, copie profonde de l'etat.
    Bestiole &operator=(const Bestiole &); // Conserve l'identite du destinataire.
    Bestiole(Bestiole &&) noexcept;
    Bestiole &operator=(Bestiole &&) noexcept;
    ~Bestiole();
    Bestiole clone() const; // Nouveau-ne : age nul et nouvel identifiant.

    void action(Milieu &);
    void agir(const Detection &);
    void bouge(int xLim, int yLim);
    void collision(const Bestiole &);
    void vieillir();
    void mourir() { marqueeMorte = true; }
    bool estMorte() const { return marqueeMorte; }
    double distance(const Bestiole &) const;
    bool enCollision(const Bestiole &) const;
    bool jeTeVois(const Bestiole &) const; // Yeux OU oreilles.
    Detection detecterProches(std::vector<Bestiole> &bestioles) const;
    std::vector<const Bestiole *> detecterCollisions(const std::vector<Bestiole> &) const;

    void setComportement(std::unique_ptr<Comportement>);
    void setComportement(const Comportement &);
    void setOrientation(double angle);
    void setVitesse(double valeur);
    void setPosition(double px, double py);

    int getId() const { return id; }
    int getAge() const { return age; }
    int getAgeLimite() const { return ageLimite; }
    double getX() const { return x; }
    double getY() const { return y; }
    double getTaille() const { return taille; }
    double getOrientation() const { return orientation; }
    double getVitesse() const { return vitesse; }
    double getVitesseMax() const { return MAX_VITESSE; }

    double getVitesseCroisiere() const { return vitesseCroisiere; }
    double getVitesseEffective() const;
    double getProbaMortCollision() const;
    double getCamouflage() const;
    const Comportement &getComportement() const;

    bool possede(TypeEquipement type) const;
    // Ouverture des yeux en radians (pi/2 par defaut).

    void equiperYeux(double distance = 80., double angle = 1.5707963267948966, double gamma = 0.8);
    void equiperOreilles(double distance = 50., double gamma = 0.6);
    void equiperCarapace(double omega = 2., double eta = 1.5);
    void equiperNageoires(double nu = 1.5);
    void equiperCamouflage(double valeur = 0.5);

    void initCoords(int xLim, int yLim);
    void draw(UImg &) const;
    friend bool operator==(const Bestiole &a, const Bestiole &b) { return a.id == b.id; }
};
#endif
