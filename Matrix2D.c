#include "Matrix2D.h"
#define pi 3.14159265

MX CreatMx(float data[], int R, int C, int z){ //��������dataΪһά���ݣ������ͣ����б�����RΪ������CΪ������zΪ����������0ʱ�򴴽�0���󣬵���1��data�����ݴ�����
	MX M;
	M.R = R; M.C = C;

	M.pMx = (float **)malloc(R*sizeof(float*));
	for (int i = 0; i<R; i++){
		M.pMx[i] = (float *)malloc(C*sizeof(float));
	}//��������ռ�

	for (int i = 0, n = 0; i<R; i++){ //��ֵ���ô������ģ���Ϊʵ�����ݿ��ܲ���һ��һά����
		for (int j = 0; j<C; j++, n++){
			if (z == 0) M.pMx[i][j] = 0.0; //�Ƿ񴴽�0����
			else M.pMx[i][j] = data[n];
		}
	}
	return M; //���ظþ���
}

void FreeMx(float **p, int R){ //�ͷž���pΪ�׵�ַ��RΪ����
	for (int i = 0; i < R; i++){
		free(p[i]);//���ͷ�һάָ��
		p[i] = NULL;
	}
	free(p);//����ͷŶ�άָ��
	p = NULL;
}

/*
��pResult����Ϊ��λ����
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
��pResult��������Ϊ��ת��
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
����һ��ƽ�ƾ��󲢷���
*/
MX CreatTranslateMx(float x, float y)
{
	float data[9] = { 1, 0, x, 0, 1, y, 0, 0, 1 };
	return CreatMx(data, 3, 3, 1);
}

// ---------------------------------------------------------------------------

/*
����һ�����ž��󲢷��أ�x,yΪ��׼�㣬sx��sy�ֱ�Ϊˮƽ�ʹ�ֱ��������ű�����
*/
MX CreatScaleMx(float x, float y,float sx,float sy)
{
	float data[9] = { sx, 0, x*(1-sx), 0, sy, sy*(1-y), 0, 0, 1 };
	return CreatMx(data, 3, 3, 1);
}

// ---------------------------------------------------------------------------

/*
����һ����ת���󲢷��أ�x,yΪ��׼�㣬AngleΪ�Ƕȣ���λΪ��
*/
MX CreatRotateMx(float x, float y, float Angle)
{
	float a = pi*Angle / 180.0;
	float data[9] = { cos(a), -sin(a), x*(1 - cos(a)) + y*sin(a), sin(a), cos(a), y*(1 - cos(a)) - x*sin(a), 0, 0, 1 };
	return CreatMx(data, 3, 3, 1);
}

// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------

MX MultiMx(MX X, MX Y){ //����˷���M=X*Y���Դ�����M����
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
	return M; //����������
}

// ---------------------------------------------------------------------------
XY MultiVec(MX T, XY P) //�任��������������ر任���������
{
	XY P0;
	P0.x = T.pMx[0][0] * P.x + T.pMx[0][1] * P.y + T.pMx[0][2];
	P0.y = T.pMx[1][0] * P.x + T.pMx[1][1] * P.y + T.pMx[1][2];
	return P0;
}

/*
//����
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
FreeMx(M.pMx, M.R); //����˷����

//---------------------------------------------

MX T = CreatTranslateMx(1, 1);
XY pos;
pos.x = 1; pos.y = 2;
XY pos0 = MultiVec(T, pos);

printf("%f\n", pos0.x);
printf("%f\n", pos0.y); //ƽ���������

}
*/