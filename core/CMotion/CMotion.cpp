#include "CMotion.h"

QTransform CMotion::getTransform(QPointF center, double N, double M, double angle, double t) {
    QTransform matrix;

    // REVERSE ORDER BECAUSE Qt COMPLETESE THOSE ACTIONS IN REVERSE ORDER
        
    // Move figure on vector N,M
    matrix.translate(N * t, M * t);

    // Return figure to original position
    matrix.translate(center.x(), center.y());
    
    // Rotate figure
    matrix.rotate(-angle * t);
    
    // Move figure's center to 0,0
    matrix.translate(-center.x(), -center.y());
    
    return matrix;
}