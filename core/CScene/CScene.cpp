#include "CScene.h"
#include <fstream>
#include <sstream>
#include "Figures/CFigure/CFigure.h"
#include "Figures/CTriangle/CTriangle.h"

void drawAxis(QPainter& painter, int x1, int y1, int x2, int y2, QColor color, int width) {
    painter.setPen(QPen(color, width));
    painter.drawLine(x1, y1, x2, y2);
}

void CScene::drawCoorSystem(QPainter& painter, int width, int height, int /*marks*/) {
    double zoom = canvas->getZoomFactor();
    QPointF pan = canvas->getPanOffset();

    double centerX = width / 2.0 + pan.x();
    double centerY = height / 2.0 + pan.y();

    double basePixelsPerUnit = 50.0; 
    
    absSegment = basePixelsPerUnit * zoom;
    ordSegment = basePixelsPerUnit * zoom; 

    drawAxis(painter, centerX, 0, centerX, height, Qt::black, 2); 
    drawAxis(painter, 0, centerY, width, centerY, Qt::black, 2); 

    double targetPixelsPerMark = 80.0;
    
    double rawStep = targetPixelsPerMark / absSegment;

    double exp = std::floor(std::log10(rawStep));
    double frac = rawStep / std::pow(10, exp);
    double niceFrac;
    if (frac <= 1.5) niceFrac = 1.0;
    else if (frac <= 3.5) niceFrac = 2.0;
    else if (frac <= 7.5) niceFrac = 5.0;
    else niceFrac = 10.0;
    double step = niceFrac * std::pow(10, exp);

    double minLogicX = (0 - centerX) / absSegment;
    double maxLogicX = (width - centerX) / absSegment;
    
    double minLogicY = (centerY - height) / ordSegment; 
    double maxLogicY = (centerY - 0) / ordSegment;

    double startX = std::floor(minLogicX / step) * step;
    double startY = std::floor(minLogicY / step) * step;

    int markSize = 5;
    painter.setFont(QFont("Arial", 9));
    
    int decimals = (step < 1.0) ? -std::floor(std::log10(step)) : 0;

    for (double logicX = startX; logicX <= maxLogicX; logicX += step) {
        if (std::abs(logicX) < 1e-9) continue; 

        double screenX = centerX + logicX * absSegment;
        painter.drawLine(screenX, centerY - markSize, screenX, centerY + markSize);
        painter.drawText(screenX - 10, centerY + markSize * 2 + 5, QString::number(logicX, 'f', decimals));
    }

    for (double logicY = startY; logicY <= maxLogicY; logicY += step) {
        if (std::abs(logicY) < 1e-9) continue; 

        double screenY = centerY - logicY * ordSegment;
        painter.drawLine(centerX - markSize, screenY, centerX + markSize, screenY);
        painter.drawText(centerX + markSize + 5, screenY + 4, QString::number(logicY, 'f', decimals));
    }

    painter.drawText(centerX + 5, centerY + markSize * 2 + 5, "0");
}

void CScene::render(QPainter& painter) {
    int cvWd = canvas->width();
    int cvHt = canvas->height();

    drawCoorSystem(painter, cvWd, cvHt, 10); 
    
    double centerX = cvWd / 2.0 + canvas->getPanOffset().x();
    double centerY = cvHt / 2.0 + canvas->getPanOffset().y();

    painter.save();
    
    painter.translate(centerX, centerY);
    
    painter.scale(absSegment, -ordSegment); 
    
    for(auto figure : figures) {
        figure->draw(painter);
    }
    
    painter.restore();
}

CScene::CScene(QObject* parent) : QObject(parent){

}

void CScene::setWidget(QWidget* widget){

    canvas = qobject_cast<CCanvas*>(widget);

}

void CScene::addFigure(CFigure* figure) {

    figures.push_back(figure);

}

void CScene::clearFigures() {

    for(auto figure : figures) {
        delete figure;
    }
    figures.clear();
}

double CScene::getAbsSegment() {
    return absSegment;
}

double CScene::getOrdSegment() {
    return ordSegment;
}

void CScene::saveFigures(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return;
    
    for(auto fig : figures) {
        file << fig->getType() << " " << fig->serialize() << "\n";
    }
    file.close();
}

void CScene::loadFigures(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    
    clearFigures();
    
    std::string line;
    while(std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;
        
        std::string data;
        std::getline(iss, data);
        if(!data.empty() && data[0] == ' ') data = data.substr(1);
        
        if(type == "triangle") {
            figures.push_back(CTriangle::deserialize(data));
        }
    }
    file.close();
}