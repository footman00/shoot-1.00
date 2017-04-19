#include "Math2D.h"
#include "stdio.h"

/*
检测点pP是否与圆（圆心pCenter，半径pRadius）发生碰撞
*/
int StaticPointToStaticCircle(XY *pP, XY *pCenter, float Radius)
{
	return 0;
}


/*
检测点pPos是否与矩形（中心pRect，宽度Width，高度Height）发生碰撞
*/
int StaticPointToStaticRect(XY *pPos, XY *pRect, float Width, float Height)
{
  return 0;
}

/*
Circle0: 圆心pCenter0，半径pRadius0
Circle1: 圆心pCenter1，半径pRadius1
*/
int StaticCircleToStaticCircle(XY *pCenter0, float Radius0, XY *pCenter1, float Radius1)
{
  return 0;
}

/*
检测两个矩形是否发生碰撞
Rectangle0: 中心pRect0，宽度Width0，高度Height0
Rectangle1: 中心pRect1，宽度Width1，高度Height1
*/
int StaticRectToStaticRect(XY *pRect0, float Width0, float Height0, XY *pRect1, float Width1, float Height1)
{
  return 0;
}
