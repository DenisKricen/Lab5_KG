#ifndef CMOTION_H
#define CMOTION_H

#include <QTransform>
#include <QPointF>

class CMotion {
public:
    static QTransform getTransform(QPointF center, double N, double M, double angle, double t);
};

#endif // CMOTION_H