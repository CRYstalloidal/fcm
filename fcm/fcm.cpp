#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"fcm.h"



//随机生成数据点
Matrix** randomPosition(int posNum, int range)
{
	printf("初始化数据点：\n");
	srand((unsigned)time(NULL));
	//数据坐标申请内存空间
	Matrix** a = new Matrix*[posNum+3];

	for (int i = 0; i < posNum; i++)
	{
		a[i] = new Matrix(HEIGHT, WIDTH);
		for (int j = 0; j < HEIGHT; j++) {
			for (int k = 0; k < WIDTH; k++) {
				a[i]->set(j,k,rand() / double(RAND_MAX) * range);
			}
		}
		a[i]->output();
	}
	printf("\n");
	return a;
}

//初始化隶属矩阵
double** init(int posNum, int clusterNum)
{
	printf("初始化隶属矩阵：\n");
	double** u = (double**)malloc(sizeof(double*) * clusterNum);
	for (int i = 0; i < clusterNum; i++)
	{
		u[i] = (double*)malloc(sizeof(double) * posNum);
	}
	srand((unsigned)time(NULL));
	double sum;
	for (int i = 0; i < posNum; i++)
	{
		sum = 1;
		for (int j = 0; j < clusterNum - 1; j++)
		{
			u[j][i] = rand() / double(RAND_MAX) * sum;
			sum -= u[j][i];
			printf("u[%d][%d]:%f\n", j, i, u[j][i]);
		}
		u[clusterNum - 1][i] = sum;
		printf("u[%d][%d]:%f\n\n", clusterNum - 1, i, u[clusterNum - 1][i]);
	}
	return u;
}

/*double sumXi(double** u, Matrix** allPos, int posNum, int i, int m)
{
	double res = 0;
	for (int j = 0; j < posNum; j++)
	{
		res = res + allPos[j].x * pow(u[i][j], m);
	}
	//printf("sumXi:%f \n",res);
	return res;
}*/


//隶属于聚类中心i的数据点的隶属程度之和
double sumUi(double** u, int posNum, int i, int m)
{
	double res = 0;
	for (int j = 0; j < posNum; j++)
	{
		res = res + pow(u[i][j], m);
	}
	//printf("sumUi:%f \n",res);
	return res;
}

//更新聚类中心
void updateCluster(Matrix** allPos, Matrix** cluster, double** u, int posNum, int clusterNum, int m)
{
	//printf("聚类中心：\n");
	double t = 1;
	Matrix* tmp;
	for (int i = 0; i < clusterNum; i++)
	{
		t = 1 / sumUi(u, posNum, i, m);
		tmp = new Matrix(HEIGHT, WIDTH);
		for (int j = 0; j < posNum; j++) {
			tmp->add(pow(u[i][j],m) * t, allPos[j]);
		}
		cluster[i]->del();
		cluster[i] = tmp;
	}
}


//点j到所有聚类中心的距离平方之和
double sumDis(Matrix* pos, Matrix** cluster, int clusterNum, int m)
{
	double res = 0;
	for (int i = 0; i < clusterNum; i++)
	{
		res = res + (double)1 / pow(pos->distance(cluster[i]), (double)2 / (m - 1));
	}
	return res;
}

//更新隶属矩阵
void updateU(Matrix** allPos, Matrix** cluster, double** u, int posNum, int clusterNum, int m)
{
	double disXi = 0;
	//printf("隶属矩阵U：\n");
	for (int i = 0; i < clusterNum; i++)
	{
		for (int j = 0; j < posNum; j++)
		{
			disXi = pow(allPos[j]->distance(cluster[i]), (double)2 / (m - 1));
			u[i][j] = (double)1 / (disXi * sumDis(allPos[j], cluster, clusterNum, m));
			//printf("u[%d][%d]:%f\n", i, j, u[i][j]);
		}
		//printf("\n");
	}

}

void outputResult(Matrix** allPos,Matrix** cluster, double** u, int posNum, int clusterNum)
{
	for (int i = 0; i < posNum; i++)
	{
		for (int j = 0; j < clusterNum - 1; j++)
		{
			printf("u[%d][%d]:%f\n", j, i, u[j][i]);
		}
		printf("u[%d][%d]:%f\n\n", clusterNum - 1, i, u[clusterNum - 1][i]);
	}
	for (int i = 0; i < clusterNum;i++) {
		cluster[i]->output();
	}
	for (int i = 0; i < posNum; i++)
	{
		double maxU = 0;
		int index=0;
		for (int j = 0; j < clusterNum; j++)
		{
			if (u[j][i] > maxU)
			{
				maxU = u[j][i];
				index = j;
			}

		}
		printf("Position[%d] belongs to cluster[%d]\n", i, index);
	}
}

double** fuzzy_CMeans( Matrix** allPos,int posNum, Matrix** cluster, int clusterNum, int m, int itertime)
{
	for (int i = 0; i < clusterNum; i++)
	{
		cluster[i] = new Matrix(HEIGHT, WIDTH);
	}
	//初始化隶属矩阵
	double** u = init(posNum, clusterNum);
	//隶属矩阵拷贝



	//计算
	for (int i = 0; i < itertime; i++)
	{
		//printf("迭代第%d次：\n", i + 1);
		updateCluster(allPos, cluster, u, posNum, clusterNum, m);
		updateU(allPos, cluster, u, posNum, clusterNum, m);
		//outpuCost_fun(allPos,cluster,u,posNum,clusterNum,m);
	}
	return u;
}