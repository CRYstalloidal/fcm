#pragma once
#include"matrix.h"
#define WIDTH 4
#define HEIGHT 4

double** fuzzy_CMeans(Matrix** allPos, int posNum, Matrix** cluster, int clusterNum, int m, int itertime);

Matrix** randomPosition(int posNum, int range);

void outputResult(Matrix** allPos, Matrix** cluster, double** u, int posNum, int clusterNum);