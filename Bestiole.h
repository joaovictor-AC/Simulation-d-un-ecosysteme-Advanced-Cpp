#ifndef BESTIOLE_H
#define BESTIOLE_H
#include "UImg.h"
#include "ConfigParams.h"
#include "Equipement.h"
#include <memory>
#include <vector>
class Milieu;
class Comportement;
class Bestiole;
struct Detection {
    std::vector<const Bestiole*> proches;
    const Bestiole* plusProche = nullptr;
};
class Bestiole {
    static int next;
    int id;
    int age = 0;
    int ageLimite;
    double x = 0., y = 0.; // Positions reelles pour conserver les petits deplacements.
    double orientation, vitesse, vitesseCroisiere;
    bool marqueeMorte = false;
    ConfigParams config;
    std::unique_ptr<Comportement> comportement;
    std::unique_ptr<Equipement> equipement;
public:
    explicit Bestiole(const ConfigParams& = ConfigParams());
    Bestiole(const Bestiole&); // Nouvelle identite, copie profonde de l'etat.
    Bestiole& operator=(const Bestiole&); // Conserve l'identite du destinataire.
    Bestiole(Bestiole&&) noexcept;
    Bestiole& operator=(Bestiole&&) noexcept;
    ~Bestiole();
    Bestiole clone() const; // Nouveau-ne : age nul et nouvel identifiant.
    void action(Milieu&);
    void agir(const Detection&);
    void bouge(int xLim, int yLim);
    void collision(const Bestiole&);
    void vieillir();
    void mourir() { marqueeMorte = true; }
    bool estMorte() const { return marqueeMorte; }
    double distance(const Bestiole&) const;
    bool enCollision(const Bestiole&) const;
    bool jeTeVois(const Bestiole&) const; // Yeux OU oreilles.
    Detection detecterProches(const std::vector<Bestiole>&) const;
    std::vector<const Bestiole*> detecterCollisions(const std::vector<Bestiole>&) const;
    void setComportement(std::unique_ptr<Comportement>);
    void setComportement(const Comportement&);
    void setComportement(BehaviorType);
    void setOrientation(double angle);
    void setVitesse(double valeur);
    void setPosition(double px, double py);
    int getId() const { return id; }
    int getAge() const { return age; }
    int getAgeLimite() const { return ageLimite; }
    double getX() const { return x; }
    double getY() const { return y; }
    double getTaille() const { return config.taille; }
    double getOrientation() const { return orientation; }
    double getVitesse() const { return vitesse; }
    double getVitesseCroisiere() const { return vitesseCroisiere; }
    double getVitesseEffective() const;
    double getProbaMortCollision() const;
    double getCamouflage() const;
    BehaviorType getTypeComportement() const;
    const Comportement& getComportement() const;
    bool possede(TypeEquipement type) const;
    void equiperYeux();
    void equiperOreilles();
    void equiperCarapace();
    void equiperNageoires();
    void equiperCamouflage();
    void initCoords(int xLim, int yLim);
    void draw(UImg&) const;
    friend bool operator==(const Bestiole& a, const Bestiole& b) { return a.id == b.id; }
};
#endif
