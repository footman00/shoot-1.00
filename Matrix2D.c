#include "Matrix2D.h"
#define pi 3.14159265

MX CreatMx(float data[], int R, int C, int z){ //创建矩阵，data为一维数据，浮点型，按行遍历。R为行数，C为列数。z为参数，等于0时则创建0矩阵，等于1则按data中数据创建。
	MX M;
	M.R = R; M.C = C;

	M.pMx = (float **)malloc(R*sizeof(float*));
	for (int i = 0; i<R; i++){
		M.pMx[i] = (float *)malloc(C*sizeof(float));
	}//以上申请空间

	for (int i = 0, n = 0; i<R; i++){ //赋值，该处待更改，因为实际数据可能不是一个一维数组
		for (int j = 0; j<C; j++, n++){
			if (z == 0) M.pMx[i][j] = 0.0; //是否创建0矩阵
			else M.pMx[i][j] = data[n];
		}
	}
	return M; //返回该矩阵
}

void FreeMx(float **p, int R){ //释放矩阵，p为首地址，R为列数
	for (int i = 0; i < R; i++){
		free(p[i]);//先释放一维指针
		p[i] = NULL;
	}
	free(p);//最后释放二维指针
	p = NULL;
}

/*
将pResult设置为单位矩阵
*/
void SetIdentityMx(MX *pResult)
{
	int i;
	int j;
	for (i = 0; i<(*pResult).R; i++)
	for (j = 0; j<(*pResult).C; j++)
	{
		if (i == j) (*pResult).pMx[i][j] = 1;
		else (*pResult).pMx[i][j] = 0;
	}
}

// ---------------------------------------------------------------------------

/*
把pResult矩阵设置为其转置
*/
void SetTransposeMx(MX *pResult)
{
	int i;
	int j;
	int temp;
	for (i = 0; i<(*pResult).R; i++)
	for (j = 0; j<(*pResult).C - i; j++)
	{
		temp = (*pResult).pMx[j][i];
		(*pResult).pMx[j][i] = (*pResult).pMx[i][j];
		(*pResult).pMx[i][j] = temp;
	}
}



/*
生成一个平移矩阵并返回
*/
MX CreatTranslateMx(float x, float y)
{
	float data[9] = { 1, 0, x, 0, 1, y, 0, 0, 1 };
	return CreatMx(data, 3, 3, 1);
}

// ---------------------------------------------------------------------------

/*
生成一个缩放矩阵并返回，x,y为基准点，sx和sy分别为水平和垂直方向的缩放比例，
*/
MX CreatScaleMx(float x, float y,float sx,float sy)
{
	float data[9] = { sx, 0, x*(1-sx), 0, sy, sy*(1-y), 0, 0, 1 };
	return CreatMx(data, 3, 3, 1);
}

// ---------------------------------------------------------------------------

/*
生成一个旋转矩阵并返回，x,y为基准点，Angle为角度，单位为度
*/
MX CreatRotateMx(float x, float y, float Angle)
{
	float a = pi*Angle / 180.0;
	float data[9] = { cos(a), -sin(a), x*(1 - cos(a)) + y*sin(a), sin(a), cos(a), y*(1 - cos(a)) - x*sin(a), 0, 0, 1 };
	return CreatMx(data, 3, 3, 1);
}

// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------

MX MultiMx(MX X, MX Y){ //矩阵乘法，M=X*Y，自带创建M矩阵
	float ar[1];
	MX M = CreatMx(ar, X.R, Y.C, 0);

	for (int i = 0; i < X.R; ++i){
		for (int k = 0; k < X.C; ++k){
			float r = X.pMx[i][k];
			for (int j = 0; j < Y.C; ++j){
				M.pMx[i][j] += r*Y.pMx[k][j];
			}
		}
	}
	return M; //返回运算结果
}

// ---------------------------------------------------------------------------
XY MultiVec(MX T, XY P) //变换矩阵乘向量，返回变换后的向量。
{
	XY P0;
	P0.x = T.pMx[0][0] * P.x + T.pMx[0][1] * P.y + T.pMx[0][2];
	P0.y = T.pMx[1][0] * P.x + T.pMx[1][1] * P.y + T.pMx[1][2];
	return P0;
}

/*
//测试
void main()
{
float A[6] = { 1.0,2.0,3.0,4.0,5.0,6.0};
float B[6] = { 100.0,10.0,10.0,100.0,1.0,1000.0 };

MX X = CreatMx(A, 2, 3, 1);
MX Y = CreatMx(B, 3, 2, 1);
MX M = MultiMx(X, Y);

printf("%f\n", M.pMx[0][0]);
printf("%f\n", M.pMx[1][1]);
FreeMx(X.pMx, X.R);
FreeMx(Y.pMx, Y.R);
FreeMx(M.pMx, M.R); //矩阵乘法结果

//---------------------------------------------

MX T = CreatTranslateMx(1, 1);
XY pos;
pos.x = 1; pos.y = 2;
XY pos0 = MultiVec(T, pos);

printf("%f\n", pos0.x);
printf("%f\n", pos0.y); //平移向量结果

}
*/