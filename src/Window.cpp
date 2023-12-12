/*
    @author :       Yash Thakare
    @goal   :       Gift to Gokhale Sir
    @Technology :   Win32SDK, COM, and Multi-Threading
    @Language :     C/C++
*/

#include <Windows.h>
#include <assert.h>
#include <gdiplus.h>

#include "Window.h"
#include "TitleScene.h"

#include "ServerHeaders/SirBirthdayClassFactoryDllServerWithRegFile.h"
#include "ServerHeaders/SirBirthdayContainmentCombined.h"
#include "ServerHeaders/SirBirthdayAggregationCombined.h"

#define CLASS_FACTORY_ANIMATION     1
#define CONTAINMENT_ANIMATION       2
#define AGGREGATION_ANIMATION       3

using namespace Gdiplus;

/*
    * Global Callback Declaration.
*/
LRESULT CALLBACK wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/* Global variables */
/* Fullscreen variables */
WINDOWPLACEMENT gpPreviousWindowPlacement;
HWND ghWnd = NULL;
BOOL gbFullScreen = FALSE;
DWORD dwWindowStyle;

/* Interface Pointers */
IClassFactoryAnimate* pIClassFactoryAnimate = NULL;
IClassFactoryCreateStruture* pIClassFactoryCreateStruture = NULL;

IContainmentAnimation* pIContainmentAnimation = NULL;
IContainmentCreateStructure* pIContainmentCreateStructure = NULL;

IAggregationAnimation* pIAggregationAnimation = NULL;
IAggregationCreateStructure* pIAggregationCreateStructure = NULL;

/* Windows sizes */
INT cxsize = 0;
INT cysize = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR CmdLine, int nShowCmd)
{
    WNDCLASSEX wndClass;
    HWND hWnd;
    MSG msg;
    HRESULT hr = S_OK;

    TCHAR szClassName[] = TEXT("My Window Class");
    TCHAR szWindowName[] = TEXT("HelloWin");

    hr = CoInitialize(NULL);

    if (FAILED(hr))
    {
        MessageBox(NULL, TEXT("COM Initialization Failed. Exiting."), TEXT("COM Error"), MB_ICONASTERISK | MB_OK);
        exit(0);
    }

    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;

    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    wndClass.cbSize = sizeof(wndClass);
    wndClass.style = CS_VREDRAW | CS_HREDRAW;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(YT_ICON));
    wndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(YT_ICON));
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.lpfnWndProc = wndProc;
    wndClass.lpszClassName = szClassName;
    wndClass.lpszMenuName = NULL;

    ATOM bRet = RegisterClassEx(&wndClass);
    assert(bRet);

    hWnd = CreateWindow(szClassName,
                        szWindowName,
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);
    

    
    ShowWindow(hWnd, nShowCmd);

    UpdateWindow(hWnd);

    ghWnd = hWnd;

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    Gdiplus::GdiplusShutdown(gdiplusToken);
    CoUninitialize();

    return ((int)msg.wParam);
}

LRESULT CALLBACK wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    void ToggleFullScreen(void);
    void AnimateClassFactory(HWND hWnd, HDC hdc);
    void AnimateContainment(HWND hWnd, HDC hdc);
    void AnimateAggregation(HWND hWnd, HDC hdc);
    
    /* Local variables */
    HDC hdc;
    PAINTSTRUCT ps;

    static HANDLE hThreadCentralFlame = NULL;
    static HANDLE hThreadRightFlame = NULL;
    static HANDLE hThreadLeftFlame = NULL;
    static HANDLE hThreadTextAstroMediComp = NULL;
    static HANDLE hThreadCreditScene = NULL;
    static HANDLE hThreadStartScene = NULL;

    static UINT uAnimationCounter = 0;

    static BOOL bRet;

    /* Code */
  
    switch(uMsg)
    {
        case WM_CREATE:
            break;

        case WM_SIZE:
            cysize = HIWORD(lParam);
            cxsize = LOWORD(lParam);
            break;

        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);

            switch (uAnimationCounter)
            {
            case CLASS_FACTORY_ANIMATION:
                AnimateClassFactory(hWnd, hdc);
                uAnimationCounter = 0;
                break;
            case CONTAINMENT_ANIMATION:
                AnimateContainment(hWnd, hdc);
                uAnimationCounter = 0;
                break;
            case AGGREGATION_ANIMATION:
                AnimateAggregation(hWnd, hdc);
                uAnimationCounter = 0;
                break;
            default :
                break;
            }

            EndPaint(hWnd, &ps);
            break;

        case WM_CHAR:
            switch (LOWORD(wParam))
            {
            case '1':
                if (gbFullScreen == FALSE)
                {
                    ToggleFullScreen();
                    gbFullScreen = TRUE;
                }
                else
                {
                    ToggleFullScreen();
                    gbFullScreen = FALSE;
                }
                break;

            case '2':
                uAnimationCounter = 0;
                InvalidateRect(hWnd, NULL, TRUE);
                hThreadCentralFlame = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcCentralFlame, (LPVOID)hWnd, 0, NULL);
                hThreadLeftFlame = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcLeftFlame, (LPVOID)hWnd, 0, NULL);
                hThreadRightFlame = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcRightFlame, (LPVOID)hWnd, 0, NULL);
                hThreadTextAstroMediComp = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTextAstroMediComp, (LPVOID)hWnd, 0, NULL);
                break;

            case '3':
                if (hThreadCentralFlame)
                {
                    bRet = TerminateThread(hThreadCentralFlame, 0);
                    if (!bRet)
                    {
                        MessageBox(hWnd, TEXT("Failed to Terminate Thread."), TEXT("Error"), MB_ICONASTERISK | MB_OK);
                        DestroyWindow(hWnd);
                    }
                }

                if (hThreadLeftFlame)
                {
                    bRet = TerminateThread(hThreadLeftFlame, 0);
                    if (!bRet)
                    {
                        MessageBox(hWnd, TEXT("Failed to Terminate Thread."), TEXT("Error"), MB_ICONASTERISK | MB_OK);
                        DestroyWindow(hWnd);
                    }
                }

                if (hThreadRightFlame)
                {
                    bRet = TerminateThread(hThreadRightFlame, 0);
                    if (!bRet)
                    {
                        MessageBox(hWnd, TEXT("Failed to Terminate Thread."), TEXT("Error"), MB_ICONASTERISK | MB_OK);
                        DestroyWindow(hWnd);
                    }
                }

                if (hThreadTextAstroMediComp)
                {
                    bRet = TerminateThread(hThreadTextAstroMediComp, 0);
                    if (!bRet)
                    {
                        MessageBox(hWnd, TEXT("Failed to Terminate Thread."), TEXT("Error"), MB_ICONASTERISK | MB_OK);
                        DestroyWindow(hWnd);
                    }
                }

                uAnimationCounter = 0;
                InvalidateRect(hWnd, NULL, TRUE);
                hThreadStartScene = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcStartScene, (LPVOID)hWnd, 0, NULL);
                break;

            case '4':
                if (hThreadStartScene)
                {
                    bRet = TerminateThread(hThreadStartScene, 0);
                    if (!bRet)
                    {
                        MessageBox(hWnd, TEXT("Failed to Terminate Thread."), TEXT("Error"), MB_ICONASTERISK | MB_OK);
                        DestroyWindow(hWnd);
                    }
                }
                uAnimationCounter = CLASS_FACTORY_ANIMATION;
                InvalidateRect(hWnd, NULL, TRUE);
                break;

            case '5':
                uAnimationCounter = CONTAINMENT_ANIMATION;
                InvalidateRect(hWnd, NULL, TRUE);
                break;

            case '6':
                uAnimationCounter = AGGREGATION_ANIMATION;
                InvalidateRect(hWnd, NULL, TRUE);
                break;

            case '7':
                uAnimationCounter = 0;
                InvalidateRect(hWnd, NULL, TRUE);
                hThreadCreditScene = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcCreditScene, (LPVOID)hWnd, 0, NULL);
                break;

            default:
                break;
            }
            break;

        case WM_KEYDOWN:
            switch (wParam)
            {
            case VK_ESCAPE:
                DestroyWindow(hWnd);
                break;   
            }
            break;

        case WM_DESTROY:

            if (hThreadCreditScene)
            {
                CloseHandle(hThreadCreditScene);
                hThreadCreditScene = NULL;
            }

            if (hThreadStartScene)
            {
                CloseHandle(hThreadStartScene);
                hThreadStartScene = NULL;
            }

            if (hThreadTextAstroMediComp)
            {
                CloseHandle(hThreadTextAstroMediComp);
                hThreadTextAstroMediComp = NULL;
            }

            if (hThreadRightFlame)
            {
                CloseHandle(hThreadRightFlame);
                hThreadRightFlame = NULL;
            }

            if (hThreadLeftFlame)
            {
                CloseHandle(hThreadLeftFlame);
                hThreadLeftFlame = NULL;
            }

            if (hThreadCentralFlame)
            {
                CloseHandle(hThreadCentralFlame);
                hThreadCentralFlame = NULL;
            }

            PostQuitMessage(0);
            break;

        default:
            break;
    }

    return (DefWindowProc(hWnd, uMsg, wParam, lParam));
}

void AnimateClassFactory(HWND hWnd, HDC hdc)
{
    HRESULT hr = S_OK;

    hr = CoCreateInstance(CLSID_CClassFactoryCreateStructureAnimate, NULL, CLSCTX_INPROC_SERVER, IID_IClassFactoryCreateStruture, (void**)&pIClassFactoryCreateStruture);
    if (FAILED(hr))
    {
        MessageBox(hWnd, TEXT("IClassFactoryCreateStructure Interface cannot be obtained."), TEXT("COM Error"), MB_ICONASTERISK | MB_OK);
        DestroyWindow(hWnd);
    }

    pIClassFactoryCreateStruture->CreateStructure(hWnd, hdc, cxsize, cysize);

    hr = pIClassFactoryCreateStruture->QueryInterface(IID_IClassFactoryAnimate, (void**)&pIClassFactoryAnimate);

    if (FAILED(hr))
    {
        MessageBox(hWnd, TEXT("IClassFactoryAnimate Interface cannot be obtained."), TEXT("COM Error"), MB_ICONASTERISK | MB_OK);
        DestroyWindow(hWnd);
    }

    if (pIClassFactoryCreateStruture)
    {
        pIClassFactoryCreateStruture->Release();
        pIClassFactoryCreateStruture = NULL;
    }

    Sleep(1000);

    pIClassFactoryAnimate->Animate(hWnd, hdc, cxsize, cysize);

    if (pIClassFactoryAnimate)
    {
        pIClassFactoryAnimate->Release();
        pIClassFactoryAnimate = NULL;
    }
}

void AnimateContainment(HWND hWnd, HDC hdc)
{
    HRESULT hr;

    hr = CoCreateInstance(CLSID_CContainmentOuterCreateStructureAnimate, NULL, CLSCTX_INPROC_SERVER, IID_IContainmentCreateStructure, (void**)&pIContainmentCreateStructure);

    if (FAILED(hr))
    {
        MessageBox(hWnd, TEXT("IContainmentCreateStruture Interface cannot be obtained."), TEXT("COM Error"), MB_ICONASTERISK | MB_OK);
        DestroyWindow(hWnd);
    }

    pIContainmentCreateStructure->CreateStructure(hWnd, hdc, cxsize, cysize);

    pIContainmentCreateStructure->QueryInterface(IID_IContainmentAnimation, (void**)&pIContainmentAnimation);

    if (pIContainmentCreateStructure)
    {
        pIContainmentCreateStructure->Release();
        pIContainmentCreateStructure = NULL;
    }

    Sleep(1000);

    pIContainmentAnimation->Animate(hWnd, hdc, cxsize, cysize);

    if (pIContainmentAnimation)
    {
        pIContainmentAnimation->Release();
        pIContainmentAnimation = NULL;
    }
}

void AnimateAggregation(HWND hWnd, HDC hdc)
{
    HRESULT hr;

    hr = CoCreateInstance(CLSID_CAggregationOuterCreateStructureAnimate, NULL, CLSCTX_INPROC_SERVER, IID_IAggregationCreateStructure, (void**)&pIAggregationCreateStructure);
    
    if (FAILED(hr))
    {
        MessageBox(hWnd, TEXT("IAggregationCreateStructure Interface cannot be obtained."), TEXT("COM Error"), MB_ICONASTERISK | MB_OK);
        DestroyWindow(hWnd);
    }

    pIAggregationCreateStructure->CreateStructure(hWnd, hdc, cxsize, cysize);

    pIAggregationCreateStructure->QueryInterface(IID_IAggregationAnimation, (void**)&pIAggregationAnimation);

    if (pIAggregationCreateStructure)
    {
        pIAggregationCreateStructure->Release();
        pIAggregationCreateStructure = NULL;
    }

    Sleep(1000);

    pIAggregationAnimation->Animate(hWnd, hdc, cxsize, cysize);

    if (pIAggregationAnimation)
    {
        pIAggregationAnimation->Release();
        pIAggregationAnimation = NULL;
    }
}

void ToggleFullScreen(void)
{
    MONITORINFO mi;
    HMONITOR hMonitor;
    BOOL bVar;

    if (gbFullScreen == FALSE)
    {
        dwWindowStyle = GetWindowLong(ghWnd, GWL_STYLE);
        if (dwWindowStyle & WS_OVERLAPPEDWINDOW)
        {
            gpPreviousWindowPlacement.length = sizeof(WINDOWPLACEMENT);
            bVar = GetWindowPlacement(ghWnd, &gpPreviousWindowPlacement);
            mi.cbSize = sizeof(MONITORINFO);
            hMonitor = MonitorFromWindow(ghWnd, MONITORINFOF_PRIMARY);
            GetMonitorInfo(hMonitor, &mi);
            if (bVar && hMonitor)
            {
                SetWindowLong(ghWnd, GWL_STYLE, dwWindowStyle & ~WS_OVERLAPPEDWINDOW);
                SetWindowPos(ghWnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top,
                    mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top,
                    SWP_NOZORDER | SWP_FRAMECHANGED);
            }
        }
        ShowCursor(FALSE);
    }
    else
    {
        SetWindowLong(ghWnd, GWL_STYLE, dwWindowStyle & WS_OVERLAPPEDWINDOW);
        gpPreviousWindowPlacement.length = sizeof(WINDOWPLACEMENT);
        SetWindowPlacement(ghWnd, &gpPreviousWindowPlacement);
        SetWindowPos(ghWnd, HWND_TOP, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
        ShowCursor(TRUE);
    }
}

DWORD WINAPI ThreadProcCentralFlame(LPVOID lpParam)
{
    HDC hdc;

    hdc = GetDC((HWND)lpParam);
    ShowCentralFlame(hdc);

    ReleaseDC((HWND)lpParam, hdc);
    return 0;
}

DWORD WINAPI ThreadProcLeftFlame(LPVOID lpParam)
{
    HDC hdc;

    hdc = GetDC((HWND)lpParam);
    ShowLeftFlame(hdc);

    ReleaseDC((HWND)lpParam, hdc);
    return 0;
}

DWORD WINAPI ThreadProcRightFlame(LPVOID lpParam)
{
    HDC hdc;

    hdc = GetDC((HWND)lpParam);
    ShowRightFlame(hdc);

    ReleaseDC((HWND)lpParam, hdc);
    return 0;
}

DWORD WINAPI ThreadProcTextAstroMediComp(LPVOID lpParam)
{
    HDC hdc;

    hdc = GetDC((HWND)lpParam);
    ShowTextAstroMediComp(hdc);

    ReleaseDC((HWND)lpParam, hdc);
    return 0;
}

DWORD WINAPI ThreadProcCreditScene(LPVOID lpParam)
{
    HDC hdc;

    hdc = GetDC((HWND)lpParam);
    ShowCreditScene(hdc);

    ReleaseDC((HWND)lpParam, hdc);
    return 0;
}

DWORD WINAPI ThreadProcStartScene(LPVOID lpParam)
{
    HDC hdc;

    hdc = GetDC((HWND)lpParam);
    ShowStartScene(hdc);

    ReleaseDC((HWND)lpParam, hdc);
    return 0;
}

void ShowCentralFlame(HDC hdc)
{
    Graphics graphics(hdc);

    Color pixelColor;
    COLORREF colorRef;
    int counter = 1, condition = 0;


    Sleep(DIYA_SLEEP_TIME);

    Image diya(L"..\\Resources\\Diya.png");
    Bitmap bmpCentralFlame(L"..\\Resources\\CentralFlame.png");

    PlaySound(TEXT("..\\Resources\\NewMusic.wav"), NULL, SND_ASYNC);


    const UINT uCentralFlameX = COORDINATE_DIYA_X + 215;
    const UINT uCentralFlameY = COORDINATE_DIYA_Y + 155 - bmpCentralFlame.GetHeight();

    Rect rc((INT)(COORDINATE_DIYA_X), (INT)(COORDINATE_DIYA_Y), (INT)(diya.GetWidth()), (INT)(diya.GetHeight()));

    graphics.DrawImage(&diya, rc);


    while (counter < 50)
    {
        if (counter == 1)
        {
            for (UINT col = bmpCentralFlame.GetHeight(); col > 0; col--)
            {
                for (UINT row = 0; row <= bmpCentralFlame.GetWidth(); row++)
                {
                    bmpCentralFlame.GetPixel(row, col, &pixelColor);
                    colorRef = pixelColor.ToCOLORREF();
                    if (GetRValue(colorRef) == 0 || GetGValue(colorRef) == 0 || GetBValue(colorRef) == 0)
                        continue;
                    SetPixel(hdc, row + uCentralFlameX, col + uCentralFlameY, colorRef);
                }
                Sleep(10);
            }
            counter++;
            continue;
        }

        switch (condition)
        {
        case 0:
            FLAME_LOOPS(bmpCentralFlame, uCentralFlameX, uCentralFlameY, 20)
                condition++;
            break;

        case 1:

            FLAME_LOOPS(bmpCentralFlame, uCentralFlameX, uCentralFlameY, 70)
                condition++;
            break;

        case 2:
            FLAME_LOOPS(bmpCentralFlame, uCentralFlameX, uCentralFlameY, 55)
                condition++;
            break;

        case 3:
            FLAME_LOOPS(bmpCentralFlame, uCentralFlameX, uCentralFlameY, 30)
                condition++;
            break;

        case 4:
            FLAME_LOOPS(bmpCentralFlame, uCentralFlameX, uCentralFlameY, 10)
                condition = 0;
            break;
        }
    }
}

void ShowLeftFlame(HDC hdc)
{
    Graphics graphics(hdc);

    Color pixelColor;
    COLORREF colorRef;
    int counter = 1, condition = 0;


    Sleep(DIYA_SLEEP_TIME);

    Image diya(L"..\\Resources\\Diya.png");
    Bitmap bmpLeftFlame(L"..\\Resources\\SideFlames.png");

    const UINT uLeftFlameX = COORDINATE_DIYA_X + 90;
    const UINT uLeftFlameY = COORDINATE_DIYA_Y + 123 - bmpLeftFlame.GetHeight();


    while (counter < 50)
    {
        if (counter == 1)
        {
            for (UINT col = bmpLeftFlame.GetHeight(); col > 0; col--)
            {
                for (UINT row = 0; row <= bmpLeftFlame.GetWidth(); row++)
                {
                    bmpLeftFlame.GetPixel(row, col, &pixelColor);
                    colorRef = pixelColor.ToCOLORREF();
                    if (GetRValue(colorRef) == 0 || GetGValue(colorRef) == 0 || GetBValue(colorRef) == 0)
                        continue;
                    SetPixel(hdc, row + uLeftFlameX, col + uLeftFlameY, colorRef);
                }
                Sleep(10);
            }
            counter++;
            continue;
        }

        switch (condition)
        {
        case 0:
            FLAME_LOOPS(bmpLeftFlame, uLeftFlameX, uLeftFlameY, 20)
                condition++;
            break;

        case 1:

            FLAME_LOOPS(bmpLeftFlame, uLeftFlameX, uLeftFlameY, 70)
                condition++;
            break;

        case 2:
            FLAME_LOOPS(bmpLeftFlame, uLeftFlameX, uLeftFlameY, 55)
                condition++;
            break;

        case 3:
            FLAME_LOOPS(bmpLeftFlame, uLeftFlameX, uLeftFlameY, 30)
                condition++;
            break;

        case 4:
            FLAME_LOOPS(bmpLeftFlame, uLeftFlameX, uLeftFlameY, 10)
                condition = 0;
            break;
        }
    }
}

void ShowRightFlame(HDC hdc)
{
    Graphics graphics(hdc);

    Color pixelColor;
    COLORREF colorRef;
    int counter = 1, condition = 0;


    Sleep(DIYA_SLEEP_TIME);

    Image diya(L"..\\Resources\\Diya.png");
    Bitmap bmpRightFlame(L"..\\Resources\\SideFlames.png");

    const UINT uRightFlameX = COORDINATE_DIYA_X + 365;
    const UINT uRightFlameY = COORDINATE_DIYA_Y + 123 - bmpRightFlame.GetHeight();

    Rect rc((INT)(cxsize / 2 - (diya.GetWidth()) / 2), (INT)(cysize / 2 - (diya.GetHeight()) / 2), (INT)(diya.GetWidth()), (INT)(diya.GetHeight()));


    while (counter < 50)
    {
        if (counter == 1)
        {
            for (UINT col = bmpRightFlame.GetHeight(); col > 0; col--)
            {
                for (UINT row = 0; row <= bmpRightFlame.GetWidth(); row++)
                {
                    bmpRightFlame.GetPixel(row, col, &pixelColor);
                    colorRef = pixelColor.ToCOLORREF();
                    if (GetRValue(colorRef) == 0 || GetGValue(colorRef) == 0 || GetBValue(colorRef) == 0)
                        continue;
                    SetPixel(hdc, row + uRightFlameX, col + uRightFlameY, colorRef);
                }
                Sleep(10);
            }
            counter++;
            continue;
        }

        switch (condition)
        {
        case 0:
            FLAME_LOOPS(bmpRightFlame, uRightFlameX, uRightFlameY, 20)
                condition++;
            break;

        case 1:

            FLAME_LOOPS(bmpRightFlame, uRightFlameX, uRightFlameY, 70)
                condition++;
            break;

        case 2:
            FLAME_LOOPS(bmpRightFlame, uRightFlameX, uRightFlameY, 5)
                condition++;
            break;

        case 3:
            FLAME_LOOPS(bmpRightFlame, uRightFlameX, uRightFlameY, 30)
                condition++;
            break;

        case 4:
            FLAME_LOOPS(bmpRightFlame, uRightFlameX, uRightFlameY, 10)
                condition = 0;
            break;
        }
    }
}

void ShowTextAstroMediComp(HDC hdc)
{
    Graphics graphics(hdc);
    UINT i = 0;
    UINT j = 0;
    UINT k = 0;

    WCHAR lpszString[] =
        L"ASTROMEDICOMP";

    // Initialize arguments.
    Font myFont(L"Impact", 120, FontStyleBold);
    RectF layoutRect(100.0f, 300.0f, ((REAL)cxsize) - 200.0f, 180.0f);
    StringFormat format;
    format.SetAlignment(StringAlignmentCenter);
    SolidBrush textBrush(Color(255, 255, 158, 0));
    SolidBrush blackBrush(Color(255, 0, 0, 0));

    Sleep(TITLE_ASTROMEDICOMP_SLEEP_TIME);

    for (i = 1; i <= 14; i++)
    {
        graphics.DrawString(lpszString, i - 1, &myFont, layoutRect, &format, &blackBrush);
        for (j = 0; j <= 255; j += 2)
        {
            textBrush.SetColor(Color(255, j, k, 0));
            graphics.DrawString(lpszString, i, &myFont, layoutRect, &format, &textBrush);
            k++;
            Sleep(1);
        }
        textBrush.SetColor(Color(255, 0, 0, 0));
        k = 0;
    }
}

void ShowCreditScene(HDC hdc)
{
    Graphics graphics(hdc);

    INT i;

    Image scene(L"..\\Resources\\CreditScene.png");
    SolidBrush mySolidBrush(Color(255, 255, 255, 255));

    WCHAR lpszBirthdayString[] = L"Happy Birthday Sir.";
    WCHAR lpszQuoteString[] = L"Knowledge is Interrelated.";
    WCHAR lpszDedicatedString[] = L"Dedicated to\n\n Dr. Vijay D. Gokhale Sir";
    WCHAR lpszTeachingString[] = L"Guidance and Teaching by\n\n Pradnya V. Gokhale Ma'am\n Yogeshwar Shukla Sir";
    WCHAR lpszThanksString[] = L"Special Thanks to\n\n Aishwarya Kendle\n Prateek Thakare";
    WCHAR lpszCreatedString[] = L"Created by\n\n Yash Thakare";
    WCHAR lpszEndString[] = L"Thank You";

    RectF rc(895.0f, 255.0f, 940.0f, 570.0f);

    graphics.DrawImage(&scene, 0, 0);
    graphics.FillRectangle(&mySolidBrush, rc);

    Font fBiggerFont(L"Impact", 50);
    Font fSmallerFont(L"Impact", 30);

    StringFormat format;
    format.SetAlignment(StringAlignmentCenter);
    format.SetLineAlignment(StringAlignmentCenter);
    SolidBrush blackBrush(Color(255, 0, 0, 0));
    SolidBrush textBrush(Color(255, 0,0,0));

    // Happy Birthday Text
    for (i = 255; i >= 0; i--)
    {
        textBrush.SetColor(Color(255, i, i, i));
        graphics.DrawString(lpszBirthdayString, -1, &fBiggerFont, rc, &format, &textBrush);
        Sleep(1);

    }

    Sleep(2000);

    for (i = 0; i <= 255; i++)
    {
        textBrush.SetColor(Color(255, i, i, i));
        graphics.DrawString(lpszBirthdayString, -1, &fBiggerFont, rc, &format, &textBrush);
        Sleep(1);
    }

    // Quote Text

    for (i = 255; i >= 0; i--)
    {
        textBrush.SetColor(Color(255, i, i, i));
        graphics.DrawString(lpszQuoteString, -1, &fBiggerFont, rc, &format, &textBrush);
        Sleep(1);

    }

    Sleep(2000);

    for (i = 0; i <= 255; i++)
    {
        textBrush.SetColor(Color(255, i, i, i));
        graphics.DrawString(lpszQuoteString, -1, &fBiggerFont, rc, &format, &textBrush);
        Sleep(1);
    }

    // Dedicated to Text

    for (i = 255; i >= 0; i--)
    {
        textBrush.SetColor(Color(255, i, i, i));
        graphics.DrawString(lpszDedicatedString, -1, &fSmallerFont, rc, &format, &textBrush);
        Sleep(1);

    }

    Sleep(2000);

    for (i = 0; i <= 255; i++)
    {
        textBrush.SetColor(Color(255, i, i, i));
        graphics.DrawString(lpszDedicatedString, -1, &fSmallerFont, rc, &format, &textBrush);
        Sleep(1);
    }

    // Guidance by Text

    for (i = 255; i >= 0; i--)
    {
        textBrush.SetColor(Color(255, i, i, i));
        graphics.DrawString(lpszTeachingString, -1, &fSmallerFont, rc, &format, &textBrush);
        Sleep(1);

    }

    Sleep(2000);

    for (i = 0; i <= 255; i++)
    {
        textBrush.SetColor(Color(255, i, i, i));
        graphics.DrawString(lpszTeachingString, -1, &fSmallerFont, rc, &format, &textBrush);
        Sleep(1);
    }

    // Special Thanks to Text
    for (i = 255; i >= 0; i--)
    {
        textBrush.SetColor(Color(255, i, i, i));
        graphics.DrawString(lpszThanksString, -1, &fSmallerFont, rc, &format, &textBrush);
        Sleep(1);

    }

    Sleep(2000);

    for (i = 0; i <= 255; i++)
    {
        textBrush.SetColor(Color(255, i, i, i));
        graphics.DrawString(lpszThanksString, -1, &fSmallerFont, rc, &format, &textBrush);
        Sleep(1);
    }

    // Create by Text

    for (i = 255; i >= 0; i--)
    {
        textBrush.SetColor(Color(255, i, i, i));
        graphics.DrawString(lpszCreatedString, -1, &fSmallerFont, rc, &format, &textBrush);
        Sleep(1);

    }

    Sleep(2000);

    for (i = 0; i <= 255; i++)
    {
        textBrush.SetColor(Color(255, i, i, i));
        graphics.DrawString(lpszCreatedString, -1, &fSmallerFont, rc, &format, &textBrush);
        Sleep(1);
    }

    // Thank You text

    for (i = 255; i >= 0; i--)
    {
        textBrush.SetColor(Color(255, i, i, i));
        graphics.DrawString(lpszEndString, -1, &fBiggerFont, rc, &format, &textBrush);
        Sleep(1);

    }
}

void ShowStartScene(HDC hdc)
{
    Graphics graphics(hdc);

    RectF rc((REAL)(cxsize/2 - 500), (REAL)(cysize / 2 - 250), 1000.00f, 500.00f);

    WCHAR lpszCOMString[] = L"COM is Never Outdated.";

    Font fBiggerFont(L"Impact", 70);

    StringFormat format;
    format.SetAlignment(StringAlignmentCenter);
    format.SetLineAlignment(StringAlignmentCenter);
    SolidBrush textBrush(Color(255, 0, 0, 0));

    for (int i = 0; i <= 255; i++)
    {
        textBrush.SetColor(Color(255, i, i, i));
        graphics.DrawString(lpszCOMString, -1, &fBiggerFont, rc, &format, &textBrush);
        Sleep(1);
    }

    Sleep(2000);

    for(int i = 255; i >= 0; i--)
    {
        textBrush.SetColor(Color(255, i, i, i));
        graphics.DrawString(lpszCOMString, -1, &fBiggerFont, rc, &format, &textBrush);
        Sleep(1);
    }
}