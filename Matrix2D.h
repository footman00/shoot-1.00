#ifndef MATRIX2D_H
#define MATRIX2D_H

#include "Vector2D.h"
#include <stdio.h>
#include <math.h>

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
void SetIdentityMx(MX *pResult);

/*
把pResult矩阵设置为其转置
*/
void SetTransposeMx(MX *pResult);

/*
生成一个平移矩阵并返回
*/
MX CreatTranslateMx(float x, float y);

/*
生成一个缩放矩阵并返回，x,y为基准点，sx和sy分别为水平和垂直方向的缩放比例，
*/
MX CreatScaleMx(float x, float y, float sx, float sy);

/*
生成一个旋转矩阵并返回，x,y为基准点，Angle为角度，单位为度
*/
MX CreatRotateMx(float x, float y, float Angle);

MX MultiMx(MX X, MX Y); //矩阵乘法，M=X*Y，自带创建M矩阵
XY MultiVec(MX T, XY P); //变换矩阵乘向量，返回变换后的向量。

#endif