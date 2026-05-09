#include "CCanvas.h"
#include "CScene/CScene.h"
#include <QWheelEvent>
#include <QMouseEvent>

CCanvas::CCanvas(CScene* s, QWidget* parent) : QWidget(parent), scene(s) {}

CCanvas::CCanvas(QWidget* parent) : QWidget(parent), scene(nullptr) {}

void CCanvas::setScene(CScene* s) {
    scene = s;
}

void CCanvas::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); 
    if(scene) {
        scene->render(painter);
    }
}

void CCanvas::wheelEvent(QWheelEvent *event) {

    if (event->angleDelta().y() > 0) {
        zoomFactor *= 1.1; 
    } else {
        zoomFactor /= 1.1;
    }
    update(); 
}

void CCanvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        isPanning = true;
        lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor); 
    }
}

void CCanvas::mouseMoveEvent(QMouseEvent *event) {
    if (isPanning) {
        QPoint delta = event->pos() - lastMousePos;
        panOffset += delta;
        lastMousePos = event->pos();
        update(); 
    }
}

void CCanvas::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        isPanning = false;
        setCursor(Qt::ArrowCursor); 
    }
}