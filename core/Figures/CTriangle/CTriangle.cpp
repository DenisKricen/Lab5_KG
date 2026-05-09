#include "CTriangle.h"
#include <sstream>

CTriangle::CTriangle(QPointF p1, QPointF p2, QPointF p3) 
    : origA(p1), origB(p2), origC(p3), currA(p1), currB(p2), currC(p3) {
}

void CTriangle::draw(QPainter& painter) {
    QPen pen(Qt::red, 3);
    pen.setCosmetic(true); 
    painter.setPen(pen);

    QPolygonF triangle;

    triangle << currA << currB << currC;
    painter.drawPolygon(triangle);
}

void CTriangle::applyTransform() {

    auto mapPoint = [this](QPointF p) {

        double newX = p.x() * matrix[0][0] + p.y() * matrix[1][0] + matrix[2][0];
        double newY = p.x() * matrix[0][1] + p.y() * matrix[1][1] + matrix[2][1];
        return QPointF(newX, newY);
    };


    currA = mapPoint(origA);
    currB = mapPoint(origB);
    currC = mapPoint(origC);
}

QPointF CTriangle::getCenter() const {

    return QPointF((origA.x() + origB.x() + origC.x()) / 3.0, 
                   (origA.y() + origB.y() + origC.y()) / 3.0);
}

std::string CTriangle::getType() const {
    return "triangle";
}

std::string CTriangle::serialize() const {
    std::ostringstream oss;

    oss << origA.x() << " " << origA.y() << " " 
        << origB.x() << " " << origB.y() << " " 
        << origC.x() << " " << origC.y();
    return oss.str();
}

CTriangle* CTriangle::deserialize(const std::string& data) {
    std::istringstream iss(data);
    double ax, ay, bx, by, cx, cy;
    iss >> ax >> ay >> bx >> by >> cx >> cy;
    return new CTriangle(QPointF(ax, ay), QPointF(bx, by), QPointF(cx, cy));
}