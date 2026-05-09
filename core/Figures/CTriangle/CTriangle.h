#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "Figures/CFigure/CFigure.h"
#include <QPointF>

class CTriangle : public CFigure {
    QPointF origA, origB, origC;
    QPointF currA, currB, currC;

public:
    CTriangle(QPointF p1, QPointF p2, QPointF p3);
    
    virtual void draw(QPainter& painter) override;
    virtual std::string serialize() const override;
    virtual std::string getType() const override;
    static CTriangle* deserialize(const std::string& data);
    
    virtual void applyTransform(const QTransform& matrix) override;
    virtual QPointF getCenter() const override;
};

#endif
