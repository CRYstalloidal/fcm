// fcm.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include"fcm.h"

int main()
{
	Matrix** allPos = randomPosition(100,100);
	Matrix** cluster = new Matrix * [5];
	double** u=fuzzy_CMeans(allPos,100,cluster, 5, 2, 5); //数据点,数据点个数，聚类中心，中心个数，m，迭代次数
	outputResult(allPos, cluster, u, 100, 5);
	return 0;
}


