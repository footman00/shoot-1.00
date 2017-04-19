#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>

// 2维向量
typedef struct Vector2D{ //坐标
	float x;
	float y;
}XY;

/*
将2维向量pResult的两个坐标值设置为0
*/
void Vector2DZero(XY *pResult);

/*
分别将2维向量pResult的两个值设置为x和y
*/
void Vector2DSet(XY *pResult, float x, float y);

/*
pResult设置为pVec0的反方向
*/
void Vector2DNeg(XY *pResult, XY *pVec0);

/*
pResult = pVec0 + pVec1
*/
void Vector2DAdd(XY *pResult, XY *pVec0, XY *pVec1);

/*
pResult = pVec0 - pVec1
*/
void Vector2DSub(XY *pResult, XY *pVec0, XY *pVec1);

/*
pResult设置为向量pVec0的单位向量
*/
void Vector2DNormalize(XY *pResult, XY *pVec0);

/*
pResult设置为向量pVec0缩放c倍的结果
*/
void Vector2DScale(XY *pResult, XY *pVec0, float c);

/*
pResult = 向量pVec0缩放c倍 + pVec1 
*/
void Vector2DScaleAdd(XY *pResult, XY *pVec0, XY *pVec1, float c);

/*
pResult = 向量pVec0缩放c倍 - pVec1 
*/
void Vector2DScaleSub(XY *pResult, XY *pVec0, XY *pVec1, float c);

/*
计算向量pVec0的长度
*/
float Vector2DLength(XY *pVec0);

/*
计算向量pVec0长度的平方，避免平方根运算
*/
float Vector2DSquareLength(XY *pVec0);

/*
pVec0和pVec1是2维空间的两个点，计算这两个点的距离
*/
float Vector2DDistance(XY *pVec0, XY *pVec1);

/*
pVec0和pVec1是2维空间的两个点，计算这两个点的距离的平方，避免平方根运算
*/
float Vector2DSquareDistance(XY *pVec0, XY *pVec1);

/*
计算pVec0和pVec1的点积
*/
float Vector2DDotProduct(XY *pVec0, XY *pVec1);

/*
极坐标到直角坐标下单位向量的转换，angle为度数，如30度
*/
void Vector2DFromAngleDeg(XY *pResult, float angle);

/*
极坐标到直角坐标下单位向量的转换，angle为弧度
*/
void Vector2DFromAngleRad(XY *pResult, float angle);

#endif