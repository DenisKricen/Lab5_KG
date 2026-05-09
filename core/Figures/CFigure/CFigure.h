#ifndef CFIGURE_H
#define CFIGURE_H

#include <QPainter>
#include <string>

class CFigure {

public:

    virtual void draw(QPainter& painter)=0;
    virtual std::string serialize() const = 0;
    virtual std::string getType() const = 0;
    virtual ~CFigure() = default;

};

#endif//CFIGURE_H