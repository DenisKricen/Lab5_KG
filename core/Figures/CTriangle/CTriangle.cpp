#include "CTriangle.h"

CTriangle::CTriangle(int x, int y, int s) : centerX(x), centerY(y), size(s) {

}

void CTriangle::draw(QPainter& painter) {

    QPen pen(Qt::red, 3);
    pen.setCosmetic(true); 
    painter.setPen(pen);
    
    painter.save();
    painter.translate(centerX, centerY);

    QPolygonF triangle;
    
    triangle << QPointF(0, 0) << QPointF(size, 0) << QPointF(0, size);
    painter.drawPolygon(triangle);

    painter.restore();
}

std::string CTriangle::getType() const {
    return "triangle";
}

std::string CTriangle::serialize() const {
    std::ostringstream oss;
    oss << centerX << " " << centerY << " " << size;
    return oss.str();
}

CTriangle* CTriangle::deserialize(const std::string& data) {
    std::istringstream iss(data);
    int x, y, s;
    iss >> x >> y >> s;
    return new CTriangle(x, y, s);
}