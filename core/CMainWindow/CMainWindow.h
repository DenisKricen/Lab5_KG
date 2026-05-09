#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QColor>
#include <QWidget>
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

protected:
    void resizeEvent(QResizeEvent *event) override;

public:
    CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

private slots:

};

#endif // CMAINWINDOW_H