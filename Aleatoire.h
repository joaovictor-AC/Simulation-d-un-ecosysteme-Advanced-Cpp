#ifndef ALEATOIRE_H
#define ALEATOIRE_H
#include <random>
namespace Aleatoire {
inline std::mt19937& moteur() {
    static std::mt19937 instance(std::random_device{}());
    return instance;
}
inline void initialiser(unsigned int graine) { moteur().seed(graine); }
inline double reel(double min = 0., double max = 1.) {
    return std::uniform_real_distribution<double>(min, max)(moteur());
}
inline int entier(int min, int max) {
    return std::uniform_int_distribution<int>(min, max)(moteur());
}
inline bool evenement(double probabilite) { return reel() < probabilite; }
}
#endif
