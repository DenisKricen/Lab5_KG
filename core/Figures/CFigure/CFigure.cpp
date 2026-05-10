#include "CFigure.h"
#include <cmath>

CFigure::CFigure() {
    resetTransform();
}

// Left-multiply the current transform by another matrix.
void CFigure::multiplyMatrix(const double other[3][3]) {
    double res[3][3] = {0};
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                res[i][j] += this->matrix[i][k] * other[k][j];
            }
        }
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            this->matrix[i][j] = res[i][j];
        }
    }
}

// Restore the identity transform.
void CFigure::resetTransform() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            matrix[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
}

// Append a translation to the current transform matrix.
void CFigure::translate(double dx, double dy) {
    double T[3][3] = {
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {dx,  dy,  1.0}
    };
    multiplyMatrix(T);
}

// Append a rotation around of the coordinate's origin.
void CFigure::rotate(double angleDeg) {
    double rad = angleDeg * M_PI / 180.0;
    double cosA = std::cos(rad);
    double sinA = std::sin(rad);
    double R[3][3] = {
        { cosA, sinA, 0.0},
        {-sinA, cosA, 0.0},
        { 0.0,  0.0,  1.0}
    };
    multiplyMatrix(R);
}

double CFigure::getMatrixElement(int row, int col) const {
    return matrix[row][col];
}