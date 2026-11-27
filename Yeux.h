#ifndef YEUX_H
#define YEUX_H
// Yeux.h : la classe (le "moule")
class Yeux {
public :
   double distance;
   double angle;
   double gamma;
   Yeux() : distance(0.), angle(0.), gamma(0.) {}
   Yeux( double d, double a, double g ) : distance(d), angle(a), gamma(g) {}
};
#endif
