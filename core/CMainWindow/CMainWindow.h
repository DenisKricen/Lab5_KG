#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QColor>
#include <QWidget>
#include <QTimer>
#include "CScene/CScene.h"    
#include "CCanvas/CCanvas.h"
#include "Figures/CFigure/CFigure.h"

namespace Ui {
    class CMainWindow;
}

class CMainWindow : public QWidget {
    Q_OBJECT
private:
    CScene* scene;
    CCanvas* canvas;
    Ui::CMainWindow *ui;

    QTimer* animationTimer;
    double progress_t;
    bool isMovingForward;

protected:
    void resizeEvent(QResizeEvent *event) override;

public:
    CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

private slots:
    void on_btn_Create_clicked();
    void on_btn_Clear_clicked();
    void on_btn_Export_clicked();
    void on_btn_Start_clicked();
    void on_btn_Stop_clicked();
    void updateAnimationFrame();
};

#endif // CMAINWINDOW_H