#include<iostream>
#include<iomanip>
#include<cstring>
#include<math.h>
#include"matrix.h"

using namespace std;

	//Constructor
	Matrix::Matrix(int row = 0, int col = 0) :row(row), col(col) {
		init(row, col);
	}

	//Copy constructor
	Matrix::Matrix(const Matrix& m) :row(m.row), col(m.col) {
		init(row, col);
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				arr[i][j] = m.arr[i][j];
	}

	//Destructor
	Matrix::~Matrix() {
		del();
	}

	//¹¹Ôì¾ØÕó
	void Matrix::init(int row, int col) {
		if (row && col) {
			arr = new double* [row];
			for (int i = 0; i < row; i++) {
				arr[i] = new double[col];
				for (int j = 0; j < col; j++)
					arr[i][j] = 0;
			}
		}
		else
			cout << endl << "length cannot be zero." << endl;
	}

	//É¾³ý¾ØÕó
	void Matrix::del() {
		if (arr) {
			for (int i = 0; i < row; i++)
				if (arr[i]) {
					delete[] arr[i];
					arr[i] = nullptr;
				}
			if (arr)
				delete[] arr;
			arr = nullptr;
		}
	}
	void Matrix::set(int x, int y, double num) {
		arr[x][y] = num;
	}
	void Matrix::output() {
		cout << "output: (" << row << ", " << col << ")" << endl;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++)
				cout<< arr[i][j]<<" ";
			cout << endl;
		}
	}
	double Matrix::get(int x, int y) {
		return arr[x][y];
	}
	double Matrix::distance(Matrix* a) {
		if (col != a->col || row != a->row) {
			return 0;
		}
		else {
			double result = 0;
			for (int i = 0; i < row; i++)
				for (int j = 0; j < col; j++)
					result += pow(arr[i][j] - a->get(i, j), 2);
			result = sqrt(result);
			return result;
		}
	}

	//double * Matrix
	void Matrix::multipleNumber(const double n) {
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				arr[i][j] *= n;
	}
	void Matrix::add(double n,Matrix* m) {
		if (row == m->row && col == m->col) {
			for (int i = 0; i < row; i++)
				for (int j = 0; j < col; j++)
					arr[i][j] = arr[i][j] + n * m->arr[i][j];
		}
		else
			cout << endl << "Matrices don't match" << endl;
	}