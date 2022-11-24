#pragma once

class Matrix {
protected:
	int row, //行数
		col; //列数
	double** arr; //矩阵数组指针
public:
	//Constructor
	Matrix(int row, int col);

	//Copy constructor
	Matrix(const Matrix& m);

	//Destructor
	~Matrix();

	//构造矩阵
	void init(int row, int col);

	//删除矩阵
	void del();

	//设置值
	void set(int x,int y,double num);

	//取值
	double get(int x, int y);

	//输出
	void output();

	//计算距离
	double distance(Matrix* a);

	//数乘
	void multipleNumber(const double n);

	//相加
	void add(double n, Matrix* m);
};