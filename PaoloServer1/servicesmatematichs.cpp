#include "servicesmatematichs.h"

ServicesMatematichs::ServicesMatematichs(QObject *parent) : QObject(parent)

{

}

double ServicesMatematichs::lireToEuro(double l_lire)
{
 return euro = round(l_lire / 19.363)/100;

}

double ServicesMatematichs::euroToLire(double e_euro)
{
    return lire = round(e_euro * 1936.3);

}
