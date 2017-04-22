

// ---------------------------------------------------------------------------
// includes

#include "AEEngine.h"
#include "Vector2D.h"

// ---------------------------------------------------------------------------

// Libraries
#pragma comment (lib, "Alpha_Engine.lib")

#define FIX(x) (x-AEGfxGetWinMaxX()*3.0 / 8.0) //由于右边有计分板，所以要对横坐标左移。点（FIX(0.0)，0.0）就相当于左边画面的中心。不要对已经FIX赋值过的变量使用，不然就是移两次了，比如a=FIX(b)，那么以后a就直接用。

// ---------------------------------------------------------------------------
// globals

int gGameRunning = 1;

typedef struct Object{ //对象
	XY xy; //对象中心坐标
	AEGfxVertexList*	pMesh; //指向对象的指针
}OB;

typedef enum StepOfMove //控制运动函数步骤
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
OB CreatPoint(float x, float y, float size);//创建一个点，x，y为坐标，size为尺寸，返回OB结构体
XY MovePoint(float x0, float y0, float x1, float y1, float x2, float y2, float rate);//移动一个点，x0，y0是移动的点的坐标；x1,y1是移动的起点坐标；x2，y2是终点坐标；rate控制速度，越大运动速度越慢，最小为1（瞬移），无最大，小数部分建议为0，否则有误差。返回坐标结构体，调用时赋值给要移动的点以更新坐标。
// ---------------------------------------------------------------------------



LRESULT CALLBACK MyWinCallBack(HWND hWin, UINT msg, WPARAM wp, LPARAM lp);


// ---------------------------------------------------------------------------
// main


int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	// Variable declaration	
	OB dot;									// 点对象
	OB board;								//计分板对象
	float obj1texX = 0, obj1texY = 0;		// 贴图坐标
	AEGfxTexture *pTex;						// 贴图指针
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

	float wx1 = AEGfxGetWinMinX(), wx2 = AEGfxGetWinMaxX(), wy1 = AEGfxGetWinMinY(), wy2 = AEGfxGetWinMaxY();//窗口四边坐标

	//创建计分板
	board.xy.x = wx2*5.0 / 8.0; board.xy.y = 0.0;
	//两个三角形组成一个正方形
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

	dot = CreatPoint(FIX(0.0), 0.0, 10.0); //创建一个点对象

	// 创建一个贴图对象
	pTex = AEGfxTextureLoad("PlanetTexture.png");
	AE_ASSERT_MESG(pTex, "Failed to create texture1!!");
	
	AEGfxSetBackgroundColor(0.5f, 0.5f, 0.5f); //设置背景色


	STEP eLineStep = Step1; //运动步骤控制
	// Game Loop
	while(gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		// 方向键移动点。现在这个程序的方向键移动对象和运动函数移动对象是同一个，都是dot，所以有冲突。
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

		if (AEInputCheckCurr('R')){ //按R键重置位置
			dot.xy.x = FIX(0.0); dot.xy.y = 0.0;
		}

		// Blending mode
		AEGfxSetBlendMode(AE_GFX_BM_ADD); //对象透明

		//绘制网格
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
		
		//绘制一个点
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(dot.xy.x, dot.xy.y); //中心坐标
		AEGfxTextureSet(pTex, obj1texX, obj1texY); //设置贴图
		AEGfxSetTransparency(1.0f);
		AEGfxSetBlendColor(1.0f, 0.0f, 0.0f, 1.0f);//混色
		AEGfxMeshDraw(dot.pMesh, AE_GFX_MDM_TRIANGLES);//绘制

		//绘制计分板
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetPosition(board.xy.x, board.xy.y); //中心坐标
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetTransparency(alpha);
		AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
		AEGfxMeshDraw(board.pMesh, AE_GFX_MDM_TRIANGLES);//绘制

		AESysFrameEnd();//绘制结束


		// ---------------------------------------------------------------------------
		// 运动函数写在这里，在Game Loop外声明控制步骤的变量。
		// 封装成函数则要在Game Loop外声明指向步骤控制变量的枚举变量指针，传递给函数。

		switch (eLineStep){
			case Step1: 
				dot.xy = MovePoint(dot.xy.x, dot.xy.y, FIX(0.0f), 0.0f, FIX(100.0f), 200.0f, 25.0f); //把点移动到（100.0，200.0）
				if (fabs(dot.xy.x - FIX(100.0)) < 0.1 && fabs(dot.xy.y - 200.0) < 0.1) eLineStep = Step2;//移动到终点结束 
				break;
			case Step2:
				dot.xy = MovePoint(dot.xy.x, dot.xy.y, FIX(100.0f), 200.0f, FIX(0.0f), 0.0f, 25.0f); //把点移动到（0.0，0.0）
				if (fabs(dot.xy.x - FIX(0.0)) < 0.1 && fabs(dot.xy.y - 0.0) < 0.1) eLineStep = Step3;//移动到终点结束 
				break;
			default: 
				eLineStep = Step1;  //步骤2（最后一步）完成后重置
				break;
		}

		// ---------------------------------------------------------------------------

		// 检查退出，按Esc或关闭窗口退出
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
	//两个三角形组成一个正方形
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

	//如果未移动到终点则继续移动
	if (fabs(x2 - x0) > 0.1){
		x0 += (x2 - x1) / rate;
	}
	if (fabs(y2 - y0) > 0.1){
		y0 += (y2 - y1) / rate;
	}
	xy.x = x0; xy.y = y0;
	return xy;
}