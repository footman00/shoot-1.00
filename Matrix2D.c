#include "Matrix2D.h"


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
void Matrix2DIdentity(MX *pResult)
{

}

// ---------------------------------------------------------------------------

/*
����pMtx��ת�ã���������ŵ�pResult
*/
void Matrix2DTranspose(MX *pResult, MX *pMtx)
{

}

// ---------------------------------------------------------------------------

/*
Result = Mtx0*Mtx1
*/
void Matrix2DConcat(MX *pResult, MX *pMtx0, MX *pMtx1)
{

}

// ---------------------------------------------------------------------------

/*
��pResult����Ϊƽ�ƾ���ƽ��λ��Ϊx��y
*/
void Matrix2DTranslate(MX *pResult, float x, float y)
{

}

// ---------------------------------------------------------------------------

/*
��pResult����Ϊ���ž���x��y�ֱ�Ϊˮƽ�ʹ�ֱ��������ű���
*/
void Matrix2DScale(MX *pResult, float x, float y)
{

}

// ---------------------------------------------------------------------------

/*
��pResult����Ϊ��ת������ת��ΪAngle��Ϊ����
*/
void Matrix2DRotDeg(MX *pResult, float Angle)
{

}

// ---------------------------------------------------------------------------

/*
��pResult����Ϊ��ת������ת��ΪAngle��Ϊ����
*/
void Matrix2DRotRad(MX *pResult, float Angle)
{

}

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


/*����˷�����
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
}
*/