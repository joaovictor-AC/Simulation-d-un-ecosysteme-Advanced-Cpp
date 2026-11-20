#include "Bestiole.h"

//Interface
class Comportement{
    virtual Comportement();
    virtual ~Comportement();
    virtual Comportement * clone() const = 0;   // pure virtuelle
    virtual void agir( //implementation différente selon le type de comportement
        Bestiole& b,
        const std::vector<Bestiole*>& proches,
        Bestiole* plusProche) = 0; 
    virtual getCouleur(); //pour différencier les bestioles dans l'interface

}