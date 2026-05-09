#ifndef CFIGURE_H
#define CFIGURE_H

#include <QPainter>
#include <string>
#include <QTransform>
#include <QPointF>

class CFigure {

public:

    virtual void draw(QPainter& painter)=0;
    virtual std::string serialize() const = 0;
    virtual std::string getType() const = 0;
    virtual ~CFigure() = default;

    virtual void applyTransform(const QTransform& matrix) = 0;
    virtual QPointF getCenter() const = 0;

};

#endif//CFIGURE_H