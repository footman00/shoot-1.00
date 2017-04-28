#ifndef MATRIX2D_H
#define MATRIX2D_H

#include "Vector2D.h"
#include <stdio.h>
#include <math.h>

typedef struct DynamicMatrix2D //��̬���󣬾�������Ϊ������
{
	float **pMx; //�����׵�ַ(һ����άָ��)��ʹ��ʱ������pMx[1][2]���ɵ��þ���ڶ��еĵ�����Ԫ�أ�ע���0��ʼ����
	int R; //����,row
	int C; //����,column
}MX;

MX CreatMx(float data[], int R, int C, int z); //��������dataΪһά���ݣ������ͣ����б�����RΪ������CΪ������zΪ����������0ʱ�򴴽�0���󣬵���1��data�����ݴ�����
	
void FreeMx(float **p, int R); //�ͷž���pΪ�׵�ַ��RΪ����


/*
��pResult����Ϊ��λ����
*/
void SetIdentityMx(MX *pResult);

/*
��pResult��������Ϊ��ת��
*/
void SetTransposeMx(MX *pResult);

/*
����һ��ƽ�ƾ��󲢷���
*/
MX CreatTranslateMx(float x, float y);

/*
����һ�����ž��󲢷��أ�x,yΪ��׼�㣬sx��sy�ֱ�Ϊˮƽ�ʹ�ֱ��������ű�����
*/
MX CreatScaleMx(float x, float y, float sx, float sy);

/*
����һ����ת���󲢷��أ�x,yΪ��׼�㣬AngleΪ�Ƕȣ���λΪ��
*/
MX CreatRotateMx(float x, float y, float Angle);

MX MultiMx(MX X, MX Y); //����˷���M=X*Y���Դ�����M����
XY MultiVec(MX T, XY P); //�任��������������ر任���������

#endif