#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "Figures/CFigure/CFigure.h"
#include <sstream>

class CTriangle : public CFigure {

    int centerX;
    int centerY;
    int size;

    float ax, ay;
    float bx, by;
    float cx, cy;

    public:

    CTriangle(int x,int y,int s);
    
    virtual void draw(QPainter& painter) override;
    virtual std::string serialize() const override;
    virtual std::string getType() const override;
    static CTriangle* deserialize(const std::string& data);

};

#endif//CTRIANGLE_H