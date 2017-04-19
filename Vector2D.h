#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>

// 2ά����
typedef struct Vector2D{ //����
	float x;
	float y;
}XY;

/*
��2ά����pResult����������ֵ����Ϊ0
*/
void Vector2DZero(XY *pResult);

/*
�ֱ�2ά����pResult������ֵ����Ϊx��y
*/
void Vector2DSet(XY *pResult, float x, float y);

/*
pResult����ΪpVec0�ķ�����
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
pResult����Ϊ����pVec0�ĵ�λ����
*/
void Vector2DNormalize(XY *pResult, XY *pVec0);

/*
pResult����Ϊ����pVec0����c���Ľ��
*/
void Vector2DScale(XY *pResult, XY *pVec0, float c);

/*
pResult = ����pVec0����c�� + pVec1 
*/
void Vector2DScaleAdd(XY *pResult, XY *pVec0, XY *pVec1, float c);

/*
pResult = ����pVec0����c�� - pVec1 
*/
void Vector2DScaleSub(XY *pResult, XY *pVec0, XY *pVec1, float c);

/*
��������pVec0�ĳ���
*/
float Vector2DLength(XY *pVec0);

/*
��������pVec0���ȵ�ƽ��������ƽ��������
*/
float Vector2DSquareLength(XY *pVec0);

/*
pVec0��pVec1��2ά�ռ�������㣬������������ľ���
*/
float Vector2DDistance(XY *pVec0, XY *pVec1);

/*
pVec0��pVec1��2ά�ռ�������㣬������������ľ����ƽ��������ƽ��������
*/
float Vector2DSquareDistance(XY *pVec0, XY *pVec1);

/*
����pVec0��pVec1�ĵ��
*/
float Vector2DDotProduct(XY *pVec0, XY *pVec1);

/*
�����굽ֱ�������µ�λ������ת����angleΪ��������30��
*/
void Vector2DFromAngleDeg(XY *pResult, float angle);

/*
�����굽ֱ�������µ�λ������ת����angleΪ����
*/
void Vector2DFromAngleRad(XY *pResult, float angle);

#endif