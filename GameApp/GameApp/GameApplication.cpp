// GameApplication.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#undef GetClassName
#undef PostMessage
#include "GameApplication.h"
#define MAX_LOADSTRING 100

#include "GL/glew.h"
//#include "GL/glew.h"


//	=====================================================================

#define _MATHTOOL_IMPORT
#define _BASE_IMPORT
#define _FILE_IMPORT
#define _CORE_IMPORT
#define _MODEL_IMPORT
#define _RENDERER_IMPORT
#define _THREAD_IMPORT
#define _DLL_IMPORT_API __declspec(dllimport)
#define _DLL_EXPORT_API __declspec(dllimport)


////#include "../Base/Type.h"
////#include "../Base/Base.h"
////#define _ARRAY_API _DLL_IMPORT_API
////#include "../Base/Array.h"
////#include "../Base/RefArray.h"
////#include "../Core/BaseImport.h"
////#include "../Core/MathToolImport.h"
////#include "../Core/ModelImport.h"
////#include "../Core/RendererImport.h"
////#include "../Core/FileImport.h"
////#include "../Thread/Thread.h"
////#include "../CoreV/CoreImport.h"

//#include "../_MGEv1_Test/TempModel.h"
#include "../_MGEv1_Test/RendererOutput.h"

//	=====================================================================

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
static LPCTSTR lpszAppName = _T("Text3D");
// Palette Handle
HPALETTE hPalette = NULL;

// 此代码模块中包含的函数的前向声明:
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: 在此放置代码。
	MSG			msg;		// Windows message structure
	WNDCLASS	wc;			// Windows class structure
	HWND		hWnd;		// Storeage for window handle
	HWND		hDesktopWnd;// Storeage for desktop window handle
	HDC			hDesktopDC; // Storeage for desktop window device context
	int			nScreenX, nScreenY; // Screen Dimensions

	// Register Window style
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= (WNDPROC) WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance 		= hInstance;
	wc.hIcon			= NULL;
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	
	// No need for background brush for OpenGL window
	wc.hbrBackground	= NULL;		
	
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= lpszAppName;

	// Register the window class
	if(RegisterClass(&wc) == 0)
		return FALSE;

    // Get he Window handle and Device context to the desktop
	hDesktopWnd = GetDesktopWindow();
	hDesktopDC = GetDC(hDesktopWnd);

    // Get the screen size
	nScreenX = GetDeviceCaps(hDesktopDC, HORZRES);
	nScreenY = GetDeviceCaps(hDesktopDC, VERTRES);

    // Release the desktop device context
    ReleaseDC(hDesktopWnd, hDesktopDC);

	// Create the main application window
	hWnd = CreateWindow(
				lpszAppName,
				lpszAppName,
				
				// OpenGL requires WS_CLIPCHILDREN and WS_CLIPSIBLINGS
				WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
	
				// Window position and size
				0, 0,
				nScreenX, nScreenY,
				NULL,
				NULL,
				hInstance,
				NULL);


	// If window was not created, quit
	if(hWnd == NULL)
		return FALSE;


	// Display the window
	ShowWindow(hWnd,SW_SHOW);
	UpdateWindow(hWnd);

	// Process application messages until the application closes
	while( GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}


// If necessary, creates a 3-3-2 palette for the device context listed.
HPALETTE GetOpenGLPalette(HDC hDC) {
	HPALETTE hRetPal = NULL;	// Handle to palette to be created
	PIXELFORMATDESCRIPTOR pfd;	// Pixel Format Descriptor
	LOGPALETTE *pPal;			// Pointer to memory for logical palette
	int nPixelFormat;			// Pixel format index
	int nColors;				// Number of entries in palette
	int i;						// Counting variable
	BYTE RedRange,GreenRange,BlueRange;
								// Range for each color entry (7,7,and 3)


	// Get the pixel format index and retrieve the pixel format description
	nPixelFormat = GetPixelFormat(hDC);
	DescribePixelFormat(hDC, nPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	// Does this pixel format require a palette?  If not, do not create a
	// palette and just return NULL
	if(!(pfd.dwFlags & PFD_NEED_PALETTE))
		return NULL;

	// Number of entries in palette.  8 bits yeilds 256 entries
	nColors = 1 << pfd.cColorBits;	

	// Allocate space for a logical palette structure plus all the palette entries
	pPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) +nColors*sizeof(PALETTEENTRY));

	// Fill in palette header 
	pPal->palVersion = 0x300;		// Windows 3.0
	pPal->palNumEntries = nColors; // table size

	// Build mask of all 1's.  This creates a number represented by having
	// the low order x bits set, where x = pfd.cRedBits, pfd.cGreenBits, and
	// pfd.cBlueBits.  
	RedRange = (1 << pfd.cRedBits) -1;
	GreenRange = (1 << pfd.cGreenBits) - 1;
	BlueRange = (1 << pfd.cBlueBits) -1;

	// Loop through all the palette entries
	for(i = 0; i < nColors; i++) {
		// Fill in the 8-bit equivalents for each component
		pPal->palPalEntry[i].peRed = (i >> pfd.cRedShift) & RedRange;
		pPal->palPalEntry[i].peRed = (unsigned char)(
			(double) pPal->palPalEntry[i].peRed * 255.0 / RedRange);

		pPal->palPalEntry[i].peGreen = (i >> pfd.cGreenShift) & GreenRange;
		pPal->palPalEntry[i].peGreen = (unsigned char)(
			(double)pPal->palPalEntry[i].peGreen * 255.0 / GreenRange);

		pPal->palPalEntry[i].peBlue = (i >> pfd.cBlueShift) & BlueRange;
		pPal->palPalEntry[i].peBlue = (unsigned char)(
			(double)pPal->palPalEntry[i].peBlue * 255.0 / BlueRange);

		pPal->palPalEntry[i].peFlags = (unsigned char) NULL;
	}
		

	// Create the palette
	hRetPal = CreatePalette(pPal);

	// Go ahead and select and realize the palette for this device context
	SelectPalette(hDC,hRetPal,FALSE);
	RealizePalette(hDC);

	// Free the memory used for the logical palette structure
	free(pPal);

	// Return the handle to the new palette
	return hRetPal;
}


// Select the pixel format for a given device context
void SetDCPixelFormat(HDC hDC) {
	int nPixelFormat;

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),	// Size of this structure
		1,								// Version of this structure	
		PFD_DRAW_TO_WINDOW |			// Draw to Window (not to bitmap)
		PFD_SUPPORT_OPENGL |			// Support OpenGL calls in window
		PFD_DOUBLEBUFFER,				// Double buffered mode
		PFD_TYPE_RGBA,					// RGBA Color mode
		32,								// Want 32 bit color
		0,0,0,0,0,0,					// Not used to select mode
		0,0,							// Not used to select mode
		0,0,0,0,0,						// Not used to select mode
		16,								// Size of depth buffer
		0,								// Not used to select mode
		0,								// Not used to select mode
		0,								// Draw in main plane
		0,								// Not used to select mode
		0,0,0 };						// Not used to select mode

	// Choose a pixel format that best matches that described in pfd
	nPixelFormat = ChoosePixelFormat(hDC, &pfd);

	// Set the pixel format for the device context
	SetPixelFormat(hDC, nPixelFormat, &pfd);
}

#undef PostMessage


short _x = 0;
short _y = 0;
unsigned char _syskey = 0;
unsigned char _key = 0;
unsigned short _unichar = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static HGLRC hRC;		// Permenant Rendering context
	static HDC hDC;			// Private GDI Device context
	HGLRC hRc;
	::PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormat;

	switch (message) {
	// Window creation, setup for OpenGL
	case WM_CREATE:
		{
			GLenum retVal;
			// Store the device context
			hDC = GetDC(hWnd);		

			// Select the pixel format
			SetDCPixelFormat(hDC);		

			// Create the rendering context and make it current
			hRC = wglCreateContext(hDC);
			wglMakeCurrent(hDC, hRC);

			retVal = glewInit();

			// Create the palette
			hPalette = GetOpenGLPalette(hDC);

			if ( retVal != GLEW_OK ) {
				wglDeleteContext(hRc);
				DestroyWindow(hWnd);
			}
			////
		}
		////hDC = GetDC(hWnd);
		////iPixelFormat = 1;
		////if (::SetPixelFormat(hDC,iPixelFormat,&pfd))
		////{
		////	GLenum retVal;
		////	hRc = ::wglCreateContext(hDC);
		////	if (::wglMakeCurrent(hDC,hRc))
		////	{
		////		retVal = glewInit();
		////		wglMakeCurrent(NULL,NULL);
		////		wglDeleteContext(hRc);
		////		DestroyWindow(hWnd);
		////		//retVal = GLEW_OK;
		////	}
		////	if ( retVal != GLEW_OK ) {
		////		wglDeleteContext(hRc);
		////		DestroyWindow(hWnd);
		////	}
		////}
		////else
		////{
		////	DestroyWindow(hWnd);
		////}


//		SetupRC(hDC);

		isShutDown = true;
		Initialization();

		__interval = 16.0; 
		__numCycles = 1.0;


		cs.interval = 16;
		cs.Start();
		SetTimer(hWnd, 1, 16, NULL);
		isShutDown = false;


		break;

	// Window is being destroyed, cleanup
	case WM_DESTROY:
		{
			// Kill the timer that we created
			isShutDown = true;
			int retCode = 0;
			///retCode = ant.Cancel();
			///retCode = ant.Join();
			///retCode = ant.AttribDestroy();

			///retCode = cs.Cancel();
			///retCode = cs.Join();
			///retCode = cs.AttribDestroy();

			//ac->rwLock.Unlock();
			//ac->rwLock.Destroy();
			//ac->rwLock.AttribDestroy();
			////////_mdlc->modelPrototype = NULL;
			////////_mdlc->animationController = NULL;
			////////_mdlc->renderMeshUnit = NULL;
		}
		KillTimer(hWnd, 1);

		//glDeleteLists(nFontList, 128);

		// Deselect the current rendering context and delete it
		wglMakeCurrent(hDC,NULL);
		wglDeleteContext(hRC);

		// Delete the palette
		if(hPalette != NULL)
			DeleteObject(hPalette);

		// Tell the application to terminate after the window
		// is gone.
		PostQuitMessage(0);
		break;
	// Window is resized.
	case WM_SIZE:
		// Call our function which modifies the clipping
		// volume and viewport
		ChangeSize(LOWORD(lParam), HIWORD(lParam));
		break;

		// The painting function.  This message sent by Windows 
		// whenever the screen needs updating.
	case WM_PAINT:
		{
//		ant->hWnd = hWnd;
//		ant->hDC = hDC;
//		ant->RendererHandler();
//			break;
			if (!isShutDown) {
				if (!isOneFrameFinished) {
					break;
				}
				isOneFrameFinished = false;
				// Call OpenGL drawing code
				___RenderScene();

				// Call function to swap the buffers
				SwapBuffers(hDC);

				ValidateRect(hWnd,NULL);
				isOneFrameFinished = true;
			}
			///InvalidateRect(hWnd,NULL,FALSE);
		}
		break;


	// Windows is telling the application that it may modify
	// the system palette.  This message in essance asks the 
	// application for a new palette.
	case WM_QUERYNEWPALETTE:
		// If the palette was created.
		break;
		if(hPalette) {
			int nRet;

			// Selects the palette into the current device context
			SelectPalette(hDC, hPalette, FALSE);

			// Map entries from the currently selected palette to
			// the system palette.  The return value is the number 
			// of palette entries modified.
			nRet = RealizePalette(hDC);

			// Repaint, forces remap of palette in current window
			InvalidateRect(hWnd,NULL,FALSE);

			return nRet;
		}
		break;


	// This window may set the palette, even though it is not the 
	// currently active window.
	case WM_PALETTECHANGED:
		break;
		// Don't do anything if the palette does not exist, or if
		// this is the window that changed the palette.
		if((hPalette != NULL) && ((HWND)wParam != hWnd)) {
			// Select the palette into the device context
			SelectPalette(hDC,hPalette,FALSE);

			// Map entries to system palette
			RealizePalette(hDC);

			// Remap the current colors to the newly realized palette
			UpdateColors(hDC);
			return 0;
		}
		break;

	case WM_CHAR:
		{
			_unichar = (unsigned short)wParam;
		}
		break;

	case WM_KEYDOWN:
		{
			_key = (unsigned char)wParam;
			MGEMessage tmsg;
			tmsg.message = MGEGameCore::GEM_KEYDOWN;
			tmsg.parameter = (unsigned int)_key;
			cs.PostMessage(tmsg);
		}
		break;
//	case WM_SYSKEYDOWN:
//		{
//			_syskey = (unsigned char)wParam;
//		}
//		break;
	case WM_TIMER:
		{
			MGEMessage tmsg;
			tmsg.message = MGEGameCore::MGE2MSG_TIMER;
			tmsg.parameter = 1;
			cs.PostMessage(tmsg);
			if (isOneFrameFinished) {
				___DoAnimation();
				InvalidateRect(hWnd,NULL,FALSE);
			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			_x = (short)lParam;
			_y = (short)(lParam >> 16);
			MGEMessage tmsg;
			tmsg.message = MGEGameCore::GEM_MOUSEMOVE;
			tmsg.parameter = (unsigned int)( ( ( _x << 16 ) & 0xFFFF0000 ) | ( _y & 0x0000FFFF ) );
			cs.PostMessage(tmsg);
		}
		break;
	case 0x020A:
		{
			_x = (short)lParam;
			_y = (short)(lParam >> 16);
			short _zd = (short)(wParam >> 16);
			MGEMessage tmsg;
			tmsg.message = MGEGameCore::GEM_MOUSEWHEEL;
			tmsg.parameter = (unsigned int)_zd;
			cs.PostMessage(tmsg);
		}
		break;
	case WM_CLOSE:
		{
		}
	default:   // Passes it on if unproccessed
		return (DefWindowProc(hWnd, message, wParam, lParam));

	}

	return (0L);
}
