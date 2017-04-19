#ifndef MATRIX2D_H
#define MATRIX2D_H

#include "Vector2D.h"
#include "stdio.h"

typedef struct DynamicMatrix2D //动态矩阵，矩阵内容为浮点型
{
	float **pMx; //矩阵首地址(一个二维指针)，使用时按形如pMx[1][2]即可调用矩阵第二行的第三个元素（注意从0开始）。
	int R; //行数,row
	int C; //列数,column
}MX;

MX CreatMx(float data[], int R, int C, int z); //创建矩阵，data为一维数据，浮点型，按行遍历。R为行数，C为列数。z为参数，等于0时则创建0矩阵，等于1则按data中数据创建。
	
void FreeMx(float **p, int R); //释放矩阵，p为首地址，R为列数


/*
将pResult设置为单位矩阵
*/
void Matrix2DIdentity(MX *pResult);

/*
计算pMtx的转置，并将结果放到pResult
*/
void Matrix2DTranspose(MX *pResult, MX *pMtx);

/*
pResult = pMtx0 * pMtx1
*/
void Matrix2DConcat(MX *pResult, MX *pMtx0, MX *pMtx1);

/*
将pResult设置为平移矩阵，平移位移为x和y 
*/
void Matrix2DTranslate(MX *pResult, float x, float y);

/*
将pResult设置为缩放矩阵，x和y分别为水平和垂直方向的缩放比例
*/
void Matrix2DScale(MX *pResult, float x, float y);

/*
将pResult设置为旋转矩阵，旋转量为Angle，为度数
*/
void Matrix2DRotDeg(MX *pResult, float Angle);

/*
将pResult设置为旋转矩阵，旋转量为Angle，为弧度
*/
void Matrix2DRotRad(MX *pResult, float Angle);

MX MultiMx(MX X, MX Y); //矩阵乘法，M=X*Y，自带创建M矩阵


#endif