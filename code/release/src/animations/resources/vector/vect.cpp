/*
 * vector.cpp
 *
 * Created: 18/01/2019 00:24:51
 *  Author: Conrad
 */


#include "vect.h"

#include "../../../interface/interface.h"

#include <math.h>

vect::vect(float x, float y, float z) {
    Matrix[0] = x;
    Matrix[1] = y;
    Matrix[2] = z;
}

void vect::loadVector(Frame &vectorFrame, uint8_t brightness) {
    Color B = Color(brightness, brightness, brightness);
    vectorFrame.addLight(Matrix, B.rgb);
}

void moveSupport(float *support, const float *directionOrig) {
    float gabFactor = 1;
    for (unsigned int i = 0; i < 3; i++) {
        if ((float) (int) (support[i]) == support[i])
            gabFactor = 0;
        else {
            if (directionOrig[i] != 0) {
                float buffer = ((float) (int) (support[i]) - support[i]) / directionOrig[i];
                if (fabsf(buffer) < fabsf(gabFactor)) gabFactor = buffer;
            }
        }
    }
    if (gabFactor != 0) {    // move support vector until at least one factor is an integer
        for (unsigned int i = 0; i < 3; i++) {
            support[i] = (directionOrig[i] * gabFactor) + support[i];
        }
    }
}

void calcLimit(int8_t limit[], const float support[], float direction[]) {
    unsigned int s = 0;
    for (unsigned int i = 1; i < 3; i++) {
        if (support[i] * fabs(direction[s]) < support[s] * fabs(direction[i])) {
            s = i;
        }
    }
    int x = 0;
    if (direction[s] < 0) {
        x = 3;
    }
    limit[0] = (int8_t) (((float) x - support[s]) / direction[s]);
    limit[1] = (int8_t) (((float) (3 - x) - support[s]) / direction[s]);
}

void
calcPlainPos(float supportReturn[], const float supportOrig[], const float directionA[], const float directionB[]) {
    bool insideCube = true;
    for (unsigned int i = 0; i < 3; i++) {
        supportReturn[i] = supportOrig[i];
        if (supportOrig[i] <= 0 || 4 <= supportOrig[i])
            insideCube = false;
    }
    if (insideCube) {    // check if plain hit Cube
        return;
    }

    for (unsigned int counter = 0; counter < 4; counter++) {
        // 0<x || 4>x
        // (3|0|0) + x*(-1| 1| 1);
        // (0|3|0) + x*( 1|-1| 1);
        // (0|0|3) + x*( 1| 1|-1);
        // (0|0|0) + x*( 1| 1| 1);

        float matrix[3][4];
        for (unsigned int i = 0; i < 3; i++) {
            bool b = (counter == i);
            matrix[i][0] = (float) (1 - (b * 2));
            matrix[i][1] = directionA[i];
            matrix[i][2] = directionB[i];
            matrix[i][3] = supportOrig[i] - (float) (b * 3);
        }
        for (unsigned int column = 0; column < 3; column++) {    // matrix calculation
            float x = matrix[column][column];
            if (x == 0) {   // plain doesn't hit this test vector inside the cube
                break;
            }
            float buffer[4];
            for (unsigned int i = 0; i < 4; i++) {
                matrix[column][i] /= x;
                buffer[i] = matrix[column][i];
            }
            for (unsigned int row = 0; row < 3; row++) {
                if (row == column) {
                    continue;
                }
                for (unsigned int i2 = 0; i2 < 4; i2++) {
                    matrix[column][i2] *= matrix[row][column];  // multiply
                }
                for (unsigned int i1 = 0; i1 < 4; i1++) {
                    matrix[row][i1] -= matrix[column][i1];   // subtract
                    matrix[column][i1] = buffer[i1];    // re-add
                }
            }
        }
        float check[3];
        bool passTest = true;
        for (unsigned int i = 0; i < 3; i++) {
            // (mat[0][3])*vector + support
            if (counter == i + 1) {
                check[i] = -matrix[0][3] - 3;
            } else {
                check[i] = matrix[0][3];
            }
            if (check[i] < 0 || 4 < check[i]) {
                passTest = false;
                break;
            }
        }
        if (passTest) {
            supportReturn[0] = check[0];
            supportReturn[1] = check[1];
            supportReturn[2] = check[2];
            return;
        }
    }

}
