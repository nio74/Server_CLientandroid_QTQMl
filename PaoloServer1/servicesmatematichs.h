#ifndef SERVICESMATEMATICHS_H
#define SERVICESMATEMATICHS_H

#include <math.h>

#include <QObject>

class ServicesMatematichs : public QObject
{
    Q_OBJECT
public:
    explicit ServicesMatematichs(QObject *parent = nullptr);
    double lireToEuro(double lireString);
    double euroToLire(double euroString);

signals:

public slots:

private:
     double lire,euro;


};

#endif // SERVICESMATEMATICHS_H
