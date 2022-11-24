#pragma once

class Matrix {
protected:
	int row, //����
		col; //����
	double** arr; //��������ָ��
public:
	//Constructor
	Matrix(int row, int col);

	//Copy constructor
	Matrix(const Matrix& m);

	//Destructor
	~Matrix();

	//�������
	void init(int row, int col);

	//ɾ������
	void del();

	//����ֵ
	void set(int x,int y,double num);

	//ȡֵ
	double get(int x, int y);

	//���
	void output();

	//�������
	double distance(Matrix* a);

	//����
	void multipleNumber(const double n);

	//���
	void add(double n, Matrix* m);
};