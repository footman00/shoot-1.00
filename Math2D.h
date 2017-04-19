#ifndef MATH2D_H
#define MATH2D_H

#include "Vector2D.h"

/*
����pP�Ƿ���Բ��Բ��pCenter���뾶pRadius��������ײ
*/
int StaticPointToStaticCircle(XY *pP, XY *pCenter, float Radius);

/*
����pPos�Ƿ�����Σ�����pRect�����Width���߶�Height��������ײ
*/
int StaticPointToStaticRect(XY *pPos, XY *pRect, float Width, float Height);

/*
�������Բ�Ƿ�����ײ
Circle0: Բ��pCenter0���뾶pRadius0
Circle1: Բ��pCenter1���뾶pRadius1
*/
int StaticCircleToStaticCircle(XY *pCenter0, float Radius0, XY *pCenter1, float Radius1);

/*
������������Ƿ�����ײ
Rectangle0: ����pRect0�����Width0���߶�Height0
Rectangle1: ����pRect1�����Width1���߶�Height1
*/
int StaticRectToStaticRect(XY *pRect0, float Width0, float Height0, XY *pRect1, float Width1, float Height1);


#endif