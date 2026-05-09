#ifndef CCANVAS_H
#define CCANVAS_H

#include <QWidget>
#include <QPainter>
class CScene;

class CCanvas : public QWidget {
    Q_OBJECT

    CScene* scene;

    double zoomFactor = 1.0;
    QPointF panOffset = QPointF(0, 0);
    QPoint lastMousePos;
    bool isPanning = false;

    public:

    double getZoomFactor() const { return zoomFactor; }
    QPointF getPanOffset() const { return panOffset; }

    explicit CCanvas(CScene* s, QWidget* parent=nullptr);
    explicit CCanvas(QWidget* parent=nullptr);
    void setScene(CScene* s);

    protected:

    virtual void paintEvent(QPaintEvent* event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    

};

#endif//CCANVAS_H