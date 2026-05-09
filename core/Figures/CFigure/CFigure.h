#ifndef CFIGURE_H
#define CFIGURE_H

#include <QPainter>
#include <string>
#include <QPointF>

class CFigure {
protected:
    double matrix[3][3];

    void multiplyMatrix(const double other[3][3]);

public:
    CFigure();
    virtual ~CFigure() = default;

    void resetTransform();
    void translate(double dx, double dy);
    void rotate(double angleDeg);
    double getMatrixElement(int row, int col) const;

    virtual void draw(QPainter& painter) = 0;
    virtual std::string serialize() const = 0;
    virtual std::string getType() const = 0;
    virtual QPointF getCenter() const = 0;
    virtual void applyTransform() = 0; 
};

#endif // CFIGURE_H