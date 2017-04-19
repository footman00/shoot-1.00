#ifndef MATRIX2D_H
#define MATRIX2D_H

#include "Vector2D.h"
#include "stdio.h"

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
void Matrix2DIdentity(MX *pResult);

/*
����pMtx��ת�ã���������ŵ�pResult
*/
void Matrix2DTranspose(MX *pResult, MX *pMtx);

/*
pResult = pMtx0 * pMtx1
*/
void Matrix2DConcat(MX *pResult, MX *pMtx0, MX *pMtx1);

/*
��pResult����Ϊƽ�ƾ���ƽ��λ��Ϊx��y 
*/
void Matrix2DTranslate(MX *pResult, float x, float y);

/*
��pResult����Ϊ���ž���x��y�ֱ�Ϊˮƽ�ʹ�ֱ��������ű���
*/
void Matrix2DScale(MX *pResult, float x, float y);

/*
��pResult����Ϊ��ת������ת��ΪAngle��Ϊ����
*/
void Matrix2DRotDeg(MX *pResult, float Angle);

/*
��pResult����Ϊ��ת������ת��ΪAngle��Ϊ����
*/
void Matrix2DRotRad(MX *pResult, float Angle);

MX MultiMx(MX X, MX Y); //����˷���M=X*Y���Դ�����M����


#endif