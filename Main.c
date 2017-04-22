

// ---------------------------------------------------------------------------
// includes

#include "AEEngine.h"
#include "Vector2D.h"

// ---------------------------------------------------------------------------

// Libraries
#pragma comment (lib, "Alpha_Engine.lib")

#define FIX(x) (x-AEGfxGetWinMaxX()*3.0 / 8.0) //�����ұ��мƷְ壬����Ҫ�Ժ��������ơ��㣨FIX(0.0)��0.0�����൱����߻�������ġ���Ҫ���Ѿ�FIX��ֵ���ı���ʹ�ã���Ȼ�����������ˣ�����a=FIX(b)����ô�Ժ�a��ֱ���á�

// ---------------------------------------------------------------------------
// globals

int gGameRunning = 1;

typedef struct Object{ //����
	XY xy; //������������
	AEGfxVertexList*	pMesh; //ָ������ָ��
}OB;

typedef enum StepOfMove //�����˶���������
{
	Step1,
	Step2,
	Step3,
	Step4,
	Step5,
	Step6,
	Step7,
	Step8,
} STEP; 
// ---------------------------------------------------------------------------
// Static function protoypes
OB CreatPoint(float x, float y, float size);//����һ���㣬x��yΪ���꣬sizeΪ�ߴ磬����OB�ṹ��
XY MovePoint(float x0, float y0, float x1, float y1, float x2, float y2, float rate);//�ƶ�һ���㣬x0��y0���ƶ��ĵ�����ꣻx1,y1���ƶ���������ꣻx2��y2���յ����ꣻrate�����ٶȣ�Խ���˶��ٶ�Խ������СΪ1��˲�ƣ��������С�����ֽ���Ϊ0������������������ṹ�壬����ʱ��ֵ��Ҫ�ƶ��ĵ��Ը������ꡣ
// ---------------------------------------------------------------------------



LRESULT CALLBACK MyWinCallBack(HWND hWin, UINT msg, WPARAM wp, LPARAM lp);


// ---------------------------------------------------------------------------
// main


int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	// Variable declaration	
	OB dot;									// �����
	OB board;								//�Ʒְ����
	float obj1texX = 0, obj1texY = 0;		// ��ͼ����
	AEGfxTexture *pTex;						// ��ͼָ��
	float alpha = 1.0f;
	WNDCLASS	winClass;
	HWND winHandle;
	RECT rect;


	// Initialize the system 
	AESysInitInfo sysInitInfo;

	sysInitInfo.mAppInstance		= instanceH;
	sysInitInfo.mShow				= show;
	sysInitInfo.mWinWidth			= GetSystemMetrics(SM_CYSCREEN)*1.2;
	sysInitInfo.mWinHeight			= GetSystemMetrics(SM_CYSCREEN)*0.9;
	sysInitInfo.mCreateConsole		= 1;
	sysInitInfo.mMaxFrameRate		= 60;
	sysInitInfo.mpWinCallBack		= NULL;//MyWinCallBack;
	sysInitInfo.mClassStyle			= CS_HREDRAW | CS_VREDRAW;											
	sysInitInfo.mWindowStyle = WS_OVERLAPPEDWINDOW^WS_THICKFRAME^WS_MAXIMIZEBOX;//WS_POPUP | WS_VISIBLE | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	
	winClass.style			= sysInitInfo.mClassStyle;
	winClass.lpfnWndProc	= MyWinCallBack;//(pSysInitInfo->mpWinCallBack) ? pSysInitInfo->mpWinCallBack : winCallBack;
	winClass.cbClsExtra		= 0;
	winClass.cbWndExtra		= 0;
	winClass.hInstance		= sysInitInfo.mAppInstance;
	winClass.hIcon			= LoadIcon(NULL,IDI_EXCLAMATION);
	winClass.hCursor		= LoadCursor(NULL,IDC_ARROW);
	winClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	winClass.lpszMenuName	= NULL;
	winClass.lpszClassName	= "Shoot";

	RegisterClass(&winClass);

	rect.left = 0;
	rect.top = 0;
	rect.right = sysInitInfo.mWinWidth;//WinWidth;
	rect.bottom = sysInitInfo.mWinHeight;//WinHeight;

	AdjustWindowRect(&rect, sysInitInfo.mWindowStyle, 0);

	winHandle = CreateWindow(winClass.lpszClassName, "Shoot", sysInitInfo.mWindowStyle, 
							100, 100, rect.right - rect.left, rect.bottom - rect.top, 
							NULL, NULL, sysInitInfo.mAppInstance, NULL);

	ShowWindow	(winHandle, show);
	UpdateWindow(winHandle);
	InvalidateRect(winHandle, NULL, TRUE);

	sysInitInfo.mCreateWindow		= 0;
	sysInitInfo.mWindowHandle		= winHandle;

	if(0 == AESysInit (&sysInitInfo))
		printf("System Init Failed!\n");

	// reset the system modules
	AESysReset();
	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();

	float wx1 = AEGfxGetWinMinX(), wx2 = AEGfxGetWinMaxX(), wy1 = AEGfxGetWinMinY(), wy2 = AEGfxGetWinMaxY();//�����ı�����

	//�����Ʒְ�
	board.xy.x = wx2*5.0 / 8.0; board.xy.y = 0.0;
	//�������������һ��������
	AEGfxTriAdd(
		-wx2 *3.0 / 8.0, -wy2, 0xFFFF0000, 0.0f, 0.0f,
		wx2 *3.0 / 8.0, -wy2, 0xFFFF0000, 0.0f, 0.0f,
		-wx2 *3.0 / 8.0, wy2, 0xFFFF0000, 0.0f, 0.0f);
	AEGfxTriAdd(
		wx2 *3.0 / 8.0, -wy2, 0xFFFF0000, 0.0f, 0.0f,
		wx2 *3.0 / 8.0, wy2, 0xFFFF0000, 0.0f, 0.0f,
		-wx2 *3.0 / 8.0, wy2, 0xFFFF0000, 0.0f, 0.0f);

	board.pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(board.pMesh, "Failed to create mesh 2!!");

	dot = CreatPoint(FIX(0.0), 0.0, 10.0); //����һ�������

	// ����һ����ͼ����
	pTex = AEGfxTextureLoad("PlanetTexture.png");
	AE_ASSERT_MESG(pTex, "Failed to create texture1!!");
	
	AEGfxSetBackgroundColor(0.5f, 0.5f, 0.5f); //���ñ���ɫ


	STEP eLineStep = Step1; //�˶��������
	// Game Loop
	while(gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		// ������ƶ��㡣�����������ķ�����ƶ�������˶������ƶ�������ͬһ��������dot�������г�ͻ��
		if (AEInputCheckCurr(VK_UP))
			dot.xy.y += 3.0f;
		else
		if (AEInputCheckCurr(VK_DOWN))
			dot.xy.y -= 3.0f;

		if (AEInputCheckCurr(VK_LEFT))
			dot.xy.x -= 3.0f;
		else
		if (AEInputCheckCurr(VK_RIGHT))
			dot.xy.x += 3.0f;

		// Alpha value
		if (AEInputCheckCurr('Z'))
			alpha -= 0.01f;
		else
		if (AEInputCheckCurr('X'))
			alpha += 0.01f;

		alpha = AEClamp(alpha, 0.0f, 1.0f);

		if (AEInputCheckCurr('R')){ //��R������λ��
			dot.xy.x = FIX(0.0); dot.xy.y = 0.0;
		}

		// Blending mode
		AEGfxSetBlendMode(AE_GFX_BM_ADD); //����͸��

		//��������
		for (int i = 0; i < wx2; i = i + 25){
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxSetPosition(FIX(i), 0.0f);
			AEGfxLine(0, wy1, 0, 1.0f, 1.0f, 1.0f, 1.0,
				0, wy2, 0, 1.0, 1.0, 1.0, 1.0);
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxSetPosition(FIX(-i), 0.0f);
			AEGfxLine(0, wy1, 0, 1.0f, 1.0f, 1.0f, 1.0,
				0, wy2, 0, 1.0, 1.0, 1.0, 1.0);
		}
		for (int i = 0; i < wy2; i = i + 25){
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxSetPosition(0.0f,i);
			AEGfxLine(wx1,0, 0, 1.0f, 1.0f, 1.0f, 1.0,
				wx2,0, 0, 1.0, 1.0, 1.0, 1.0);
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxSetPosition(0.0f, -i);
			AEGfxLine(wx1, 0, 0, 1.0f, 1.0f, 1.0f, 1.0,
				wx2, 0, 0, 1.0, 1.0, 1.0, 1.0);
		}
		
		//����һ����
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(dot.xy.x, dot.xy.y); //��������
		AEGfxTextureSet(pTex, obj1texX, obj1texY); //������ͼ
		AEGfxSetTransparency(1.0f);
		AEGfxSetBlendColor(1.0f, 0.0f, 0.0f, 1.0f);//��ɫ
		AEGfxMeshDraw(dot.pMesh, AE_GFX_MDM_TRIANGLES);//����

		//���ƼƷְ�
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetPosition(board.xy.x, board.xy.y); //��������
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetTransparency(alpha);
		AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
		AEGfxMeshDraw(board.pMesh, AE_GFX_MDM_TRIANGLES);//����

		AESysFrameEnd();//���ƽ���


		// ---------------------------------------------------------------------------
		// �˶�����д�������Game Loop���������Ʋ���ı�����
		// ��װ�ɺ�����Ҫ��Game Loop������ָ������Ʊ�����ö�ٱ���ָ�룬���ݸ�������

		switch (eLineStep){
			case Step1: 
				dot.xy = MovePoint(dot.xy.x, dot.xy.y, FIX(0.0f), 0.0f, FIX(100.0f), 200.0f, 25.0f); //�ѵ��ƶ�����100.0��200.0��
				if (fabs(dot.xy.x - FIX(100.0)) < 0.1 && fabs(dot.xy.y - 200.0) < 0.1) eLineStep = Step2;//�ƶ����յ���� 
				break;
			case Step2:
				dot.xy = MovePoint(dot.xy.x, dot.xy.y, FIX(100.0f), 200.0f, FIX(0.0f), 0.0f, 25.0f); //�ѵ��ƶ�����0.0��0.0��
				if (fabs(dot.xy.x - FIX(0.0)) < 0.1 && fabs(dot.xy.y - 0.0) < 0.1) eLineStep = Step3;//�ƶ����յ���� 
				break;
			default: 
				eLineStep = Step1;  //����2�����һ������ɺ�����
				break;
		}

		// ---------------------------------------------------------------------------

		// ����˳�����Esc��رմ����˳�
		if (AEInputCheckTriggered(VK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	// Freeing the objects and textures
	AEGfxMeshFree(dot.pMesh);
	
	AEGfxTextureUnload(pTex);

	// free the system
	AESysExit();

	return 1;
}

// ---------------------------------------------------------------------------


LRESULT CALLBACK MyWinCallBack(HWND hWin, UINT msg, WPARAM wp, LPARAM lp) 
{
	HDC dc;   
	PAINTSTRUCT ps;
	RECT rect;

	switch (msg)
	{
	// when the window is created
	case WM_CREATE:
		printf("My own code in window create message!\n");

		break;

	// when the rectangle is drawn
	case WM_PAINT:
		dc = BeginPaint(hWin, &ps);
		GetClientRect(hWin, &rect);

		DrawText(dc, TEXT("Hello, this game is shoot!"), -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		// Cleans up the painting process
		EndPaint(hWin, &ps);
		break;

	// When it's time for the window to go away
	case WM_SIZE:
		
		break;

	case WM_DESTROY:
		//PostQuitMessage(0);
		//gAESysWinExists = false;
		break;

	// called any time the window is moved
	case WM_MOVE:
		// Invalidate the rect to force a redraw
		InvalidateRect(hWin, NULL, FALSE);
		break;

	case WM_ACTIVATE:
		// DO NOT REMOVE THIS
		// *(AESysGetAppActive()) = (LOWORD(wp) == WA_INACTIVE) ? 0 : 1;
		break;

	default:
		return DefWindowProc(hWin, msg, wp, lp);
	}

	return 0;
}

OB CreatPoint(float x,float y,float size){
	OB dot;
	dot.xy.x = x; dot.xy.y = y;
	//�������������һ��������
	AEGfxTriAdd(
		-size, -size, 0x00FF00FF, 0.0f, 1.0f,
		size, -size, 0x00FFFF00, 1.0f, 1.0f,
		-size, size, 0x00F00FFF, 0.0f, 0.0f);
	AEGfxTriAdd(
		size, -size, 0x00FFFFFF, 1.0f, 1.0f,
		size, size, 0x00FFFFFF, 1.0f, 0.0f,
		-size, size, 0x00FFFFFF, 0.0f, 0.0f);

	dot.pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(dot.pMesh, "Failed to create mesh 2!!");
	return dot;
}

XY MovePoint(float x0, float y0, float x1, float y1, float x2, float y2, float rate){
	XY xy;

	//���δ�ƶ����յ�������ƶ�
	if (fabs(x2 - x0) > 0.1){
		x0 += (x2 - x1) / rate;
	}
	if (fabs(y2 - y0) > 0.1){
		y0 += (y2 - y1) / rate;
	}
	xy.x = x0; xy.y = y0;
	return xy;
}