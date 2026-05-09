#include "CMainWindow.h"
#include "ui_CMainWindow.h"
#include <QColorDialog>
#include <QPushButton>
#include <QResizeEvent>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <QMessageBox>
#include <QFileDialog>
#include "Figures/CTriangle/CTriangle.h"

using std::cout, std::endl;

CMainWindow::CMainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::CMainWindow) {
    ui->setupUi(this);

    canvas = qobject_cast<CCanvas*>(ui->canvas);
    scene = new CScene(this);
    
    canvas->setScene(scene);
    scene->setWidget(canvas);

    animationTimer = new QTimer(this);
    progress_t = 0.0;
    isMovingForward = true;

    scene->loadFigures("figures.txt");

    connect(animationTimer, &QTimer::timeout, this, &CMainWindow::on_animation_tick);
    connect(ui->btn_Create, &QPushButton::clicked, this, &CMainWindow::on_btn_Create_clicked);
    connect(ui->btn_Clear, &QPushButton::clicked, this, &CMainWindow::on_btn_Clear_clicked);
    
}

CMainWindow::~CMainWindow() {
    scene->saveFigures("figures.txt");
    delete ui;
}

void CMainWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    int currentWidth = event->size().width();

    int targetHeight = currentWidth*3/4; 

    if (this->height() != targetHeight) {
        this->resize(currentWidth, targetHeight);
    }
}

void CMainWindow::on_btn_Create_clicked() {
    scene->clearFigures();

    QPointF pA, pB, pC;
    double r = ui->spin_Radius->value(); 
    if (r > 0) {
        double cx = ui->spin_Center_x->value();
        double cy = ui->spin_Center_y->value();
        
        double R = 2 * r;
        double side = 2 * r * std::sqrt(3.0);

        pA = QPointF(cx, cy + R);
        pB = QPointF(cx - side / 2.0, cy - r); 
        pC = QPointF(cx + side / 2.0, cy - r); 
    } else {
        pA = QPointF(ui->spin_A_x->value(), ui->spin_A_y->value());
        pB = QPointF(ui->spin_B_x->value(), ui->spin_B_y->value());
        pC = QPointF(ui->spin_C_x->value(), ui->spin_C_y->value());

        double area = 0.5 * std::abs(pA.x()*(pB.y() - pC.y()) + pB.x()*(pC.y() - pA.y()) + pC.x()*(pA.y() - pB.y()));
        if (area < 1e-6) {
            QMessageBox::critical(this, "Error", "Your coordinates are forming one line or one dot.");
            return;
        }

        if (ui->checkbox_Right_triangle->isChecked()) {
            auto distSq = [](QPointF p1, QPointF p2) {
                return std::pow(p1.x()-p2.x(), 2) + std::pow(p1.y()-p2.y(), 2);
            };
            double dAB = distSq(pA, pB);
            double dBC = distSq(pB, pC);
            double dCA = distSq(pC, pA);

            if (std::abs(dAB - dBC) > 1e-2 || std::abs(dBC - dCA) > 1e-2) {
                QMessageBox::warning(this, "Error", "Your coordinates does not form a right triangle.");
                return;
            }
        }
    }

    scene->addFigure(new CTriangle(pA, pB, pC));
    ui->canvas->update();
}

void CMainWindow::on_btn_Clear_clicked() {
    scene->clearFigures();
    ui->canvas->update();
}

void CMainWindow::on_btn_Export_clicked() {
    QString fileName = QFileDialog::getSaveFileName(this,
        "Save image", 
        "", 
        "Images (*.png *.jpg *.jpeg *.bmp);;All Files (*)");

    if (fileName.isEmpty()) {
        return; 
    }

    QPixmap pixmap = ui->canvas->grab();

    if (pixmap.save(fileName)) {
        // QMessageBox::information(this, "Success", "Image is saved");
    } else {
        QMessageBox::critical(this, "Error", "Unable to save the image");
    }
}









void CMainWindow::on_btn_Start_clicked() {
    CFigure* fig = scene->getFirstFigure(); 
    if (!fig) return;

    double N = ui->spin_Move_x->value();
    double M = ui->spin_Move_y->value();
    double angle = ui->spin_Angle->value();
    QPointF center = fig->getCenter();

    fig->resetTransform();
    
    // Reverse
    fig->translate(-center.x(), -center.y());
    fig->rotate(-angle);
    fig->translate(center.x(), center.y());
    fig->translate(N, M);

    int colW = 10; 

    std::cout << "--- Matrix ---" << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "[" << std::setw(colW) << fig->getMatrixElement(0,0) << "  " 
                     << std::setw(colW) << fig->getMatrixElement(0,1) << "  " 
                     << std::setw(colW) << fig->getMatrixElement(0,2) << " ]\n";
    std::cout << "[" << std::setw(colW) << fig->getMatrixElement(1,0) << "  " 
                     << std::setw(colW) << fig->getMatrixElement(1,1) << "  " 
                     << std::setw(colW) << fig->getMatrixElement(1,2) << " ]\n";
    std::cout << "[" << std::setw(colW) << fig->getMatrixElement(2,0) << "  " 
                     << std::setw(colW) << fig->getMatrixElement(2,1) << "  " 
                     << std::setw(colW) << fig->getMatrixElement(2,2) << " ]\n";

    std::ofstream file("transformation_matrix.txt");
    if (file.is_open()) {
        file << std::fixed << std::setprecision(4);
        file << "Matrix:\n";
        file << std::setw(colW) << fig->getMatrixElement(0,0) << "\t" 
             << std::setw(colW) << fig->getMatrixElement(0,1) << "\t" 
             << std::setw(colW) << fig->getMatrixElement(0,2) << "\n";
        file << std::setw(colW) << fig->getMatrixElement(1,0) << "\t" 
             << std::setw(colW) << fig->getMatrixElement(1,1) << "\t" 
             << std::setw(colW) << fig->getMatrixElement(1,2) << "\n";
        file << std::setw(colW) << fig->getMatrixElement(2,0) << "\t" 
             << std::setw(colW) << fig->getMatrixElement(2,1) << "\t" 
             << std::setw(colW) << fig->getMatrixElement(2,2) << "\n";
        file.close();
    }


    fig->resetTransform();
    fig->applyTransform();
    
    progress_t = 0.0;
    isMovingForward = true;
    animationTimer->start(20); // 20 ms per frame (50 FPS)
}

void CMainWindow::on_animation_tick() {
    double step = 0.015;

    if (isMovingForward) {
        progress_t += step;
        if (progress_t >= 1.0) {
            progress_t = 1.0;
            isMovingForward = false; 
        }
    } else {
        progress_t -= step;
        if (progress_t <= 0.0) {
            progress_t = 0.0;
            animationTimer->stop();
            isMovingForward = true;
        }
    }

    CFigure* fig = scene->getFirstFigure();
    if (fig) {
        double N = ui->spin_Move_x->value();
        double M = ui->spin_Move_y->value();
        double angle = ui->spin_Angle->value();
        QPointF center = fig->getCenter();

        fig->resetTransform(); 
        
        fig->translate(-center.x(), -center.y());
        fig->rotate(-angle * progress_t);
        fig->translate(center.x(), center.y());
        fig->translate(N * progress_t, M * progress_t);
        
        fig->applyTransform(); 
        ui->canvas->update(); 
    }
}

void CMainWindow::on_btn_Stop_clicked() {

    if (animationTimer->isActive()) {
        animationTimer->stop();
    } else if (scene->getFirstFigure()) {
        animationTimer->start(20);
    }
}