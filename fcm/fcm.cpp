#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"fcm.h"



//����������ݵ�
Matrix** randomPosition(int posNum, int range)
{
	printf("��ʼ�����ݵ㣺\n");
	srand((unsigned)time(NULL));
	//�������������ڴ�ռ�
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

//��ʼ����������
double** init(int posNum, int clusterNum)
{
	printf("��ʼ����������\n");
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


//�����ھ�������i�����ݵ�������̶�֮��
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

//���¾�������
void updateCluster(Matrix** allPos, Matrix** cluster, double** u, int posNum, int clusterNum, int m)
{
	//printf("�������ģ�\n");
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


//��j�����о������ĵľ���ƽ��֮��
double sumDis(Matrix* pos, Matrix** cluster, int clusterNum, int m)
{
	double res = 0;
	for (int i = 0; i < clusterNum; i++)
	{
		res = res + (double)1 / pow(pos->distance(cluster[i]), (double)2 / (m - 1));
	}
	return res;
}

//������������
void updateU(Matrix** allPos, Matrix** cluster, double** u, int posNum, int clusterNum, int m)
{
	double disXi = 0;
	//printf("��������U��\n");
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
	//��ʼ����������
	double** u = init(posNum, clusterNum);
	//�������󿽱�



	//����
	for (int i = 0; i < itertime; i++)
	{
		//printf("������%d�Σ�\n", i + 1);
		updateCluster(allPos, cluster, u, posNum, clusterNum, m);
		updateU(allPos, cluster, u, posNum, clusterNum, m);
		//outpuCost_fun(allPos,cluster,u,posNum,clusterNum,m);
	}
	return u;
}