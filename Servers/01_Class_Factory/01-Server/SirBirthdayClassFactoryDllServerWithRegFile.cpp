#define UNICODE 
#include <windows.h>
#include <gdiplus.h>
#include "SirBirthdayClassFactoryDllServerWithRegFile.h"

using namespace Gdiplus;

//Class Declaration
class CClassFactoryCreateStructureAnimate :public IClassFactoryCreateStruture, IClassFactoryAnimate
{
private:
	long m_cRef;

public:
	//Constructor Method Declaration
	CClassFactoryCreateStructureAnimate(void);

	//Destructor Method declaration
	~CClassFactoryCreateStructureAnimate(void);

	//IUnknown specific method declaration (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CreateStructure(HWND, HDC, INT, INT);
	HRESULT __stdcall Animate(HWND, HDC, INT, INT);
};

class CClassFactoryCreateStructureAnimateClassFactory : public IClassFactory
{
private:
	long m_cRef;

public:
	//Constructor method declarations 
	CClassFactoryCreateStructureAnimateClassFactory(void);

	//Destructor method declarations
	~CClassFactoryCreateStructureAnimateClassFactory(void);

	//IUnknown specific method declaration (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	
	//IClassFactory specific method declarations
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

//Global Variable Declarations
long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}

	return (TRUE);
}

/* CSumSubtract Implementation */

CClassFactoryCreateStructureAnimate::CClassFactoryCreateStructureAnimate(void)
{
	m_cRef = 1;

	InterlockedIncrement(&glNumberOfActiveComponents);
}

CClassFactoryCreateStructureAnimate::~CClassFactoryCreateStructureAnimate(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT CClassFactoryCreateStructureAnimate::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactoryCreateStruture*>(this);
	else if (riid == IID_IClassFactoryCreateStruture)
		*ppv = static_cast<IClassFactoryCreateStruture*>(this);
	else if (riid == IID_IClassFactoryAnimate)
		*ppv = static_cast<IClassFactoryAnimate*>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	
	return(S_OK);
}

ULONG CClassFactoryCreateStructureAnimate::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CClassFactoryCreateStructureAnimate::Release(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete(this);
		return (0);
	}

	return(m_cRef);
}

HRESULT CClassFactoryCreateStructureAnimate::CreateStructure(HWND hWnd, HDC hdc, INT cxsize, INT cysize)
{
	DWORD dwPenStyle = PS_SOLID;
	COLORREF colPenColor = RGB(255, 255, 255);
	HPEN hPen = CreatePen(dwPenStyle, 5, colPenColor);
	HPEN holdPen = (HPEN)SelectObject(hdc, hPen);

	HBRUSH hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));

	SelectObject(hdc, hBrush);

	POINT ptCoClassRect[] = { {cxsize / 2 - 300, cysize / 2 - 200},
					{cxsize / 2 + 300, cysize / 2 - 200},
					{cxsize / 2 + 300, cysize / 2 + 200},
					{cxsize / 2 - 300, cysize / 2 + 200},
					{cxsize / 2 - 300, cysize / 2 - 200}, };

	POINT ptISumLine[] = { {cxsize / 2 - 300, cysize / 2 - 100},
						{cxsize / 2 - 400, cysize / 2 - 100} };

	POINT ptISubtractLine[] = { {cxsize / 2 - 300, cysize / 2 + 100},
								{cxsize / 2 - 400, cysize / 2 + 100} };

	POINT ptIUnknownLine[] = { {cxsize / 2 + 150, cysize / 2 - 200},
								{cxsize / 2 + 150, cysize / 2 - 300} };

	SetBkColor(hdc, RGB(0, 0, 0));

	SetTextColor(hdc, RGB(255, 158, 0));

	HFONT hFont = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Impact"));
	HFONT hFont2 = CreateFont(80, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Impact"));
	SelectObject(hdc, hFont);

	//ISum
	Ellipse(hdc, cxsize / 2 - 500, cysize / 2 - 150, cxsize / 2 - 400, cysize / 2 - 50);

	//ISubtract
	Ellipse(hdc, cxsize / 2 - 500, cysize / 2 + 50, cxsize / 2 - 400, cysize / 2 + 150);

	//IUnknown
	Ellipse(hdc, cxsize / 2 + 100, cysize / 2 - 400, cxsize / 2 + 200, cysize / 2 - 300);

	Polyline(hdc, ptCoClassRect, 5);
	Polyline(hdc, ptISumLine, 2);
	Polyline(hdc, ptISubtractLine, 2);
	Polyline(hdc, ptIUnknownLine, 2);

	TCHAR lpszString[256];

	RECT rcISumLayoutRect = { cxsize / 2 - 600, cysize / 2 - 40, cxsize / 2 - 600 + 300, cysize / 2 - 40 + 30 };
	RECT rcISubtractLayoutRect = { cxsize / 2 - 600, cysize / 2 + 160, cxsize / 2 - 600 + 300, cysize / 2 + 160 + 30};
	RECT rcIUnknownLayoutRect = { cxsize / 2, cysize / 2 - 440, cxsize / 2 + 300, cysize / 2 - 440 + 30 };
	RECT rcCoClassLayoutRect = { cxsize / 2 - 300, cysize / 2 - 200, cxsize / 2 - 300 + 600, cysize / 2 - 200 + 30 };
	RECT rcTitleRect = { 100, cysize - 150, cxsize - 100, cysize - 50 };

	wsprintfW(lpszString, L"ISum Interface");
	DrawText(hdc, lpszString, -1, &rcISumLayoutRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	wsprintfW(lpszString, L"ISubtract Interface");
	DrawText(hdc, lpszString, -1, &rcISubtractLayoutRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	wsprintfW(lpszString, L"IUnknown Interface");
	DrawText(hdc, lpszString, -1, &rcIUnknownLayoutRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	wsprintfW(lpszString, L"CoClass / Component");
	DrawText(hdc, lpszString, -1, &rcCoClassLayoutRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	SelectObject(hdc, hFont2);
	wsprintfW(lpszString, L"Class Factory");
	DrawText(hdc, lpszString, -1, &rcTitleRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	DeleteObject(hPen);
	DeleteObject(holdPen);

	return S_OK;
}

HRESULT CClassFactoryCreateStructureAnimate::Animate(HWND hWnd, HDC hdc, INT cxsize, INT cysize)
{
	DWORD dwPenStyle = PS_SOLID;
	COLORREF colPenColor = RGB(255, 255, 255);
	HPEN hPen = CreatePen(dwPenStyle, 5, colPenColor);
	HPEN holdPen = (HPEN)SelectObject(hdc, hPen);

	HBRUSH hHighlightBrush = (HBRUSH)CreateSolidBrush(RGB(255, 158, 0));
	HBRUSH hDefaultBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));

	HFONT hFont = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Impact"));

	SelectObject(hdc, hFont);
	SelectObject(hdc, hHighlightBrush);

	TCHAR lpszString[256];
	wsprintfW(lpszString, L"CoClass / Component");

	RECT rcCoClassRect = { cxsize / 2 - 300 + 5, cysize / 2 - 200 + 30, cxsize / 2 + 300 - 5, cysize / 2 + 200 - 5 };
	RECT rcCoClassLayoutRect = { cxsize / 2 - 300, cysize / 2 - 200, cxsize / 2 - 300 + 600, cysize / 2 - 200 + 30 };

	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 158, 0));
	DrawText(hdc, lpszString, -1, &rcCoClassLayoutRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	HBRUSH hDefCoClassBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hCoClassBrush = CreateSolidBrush(RGB(255, 158, 0));
	
	/* First Go to IUnknown*/
	//IUnknown
	SelectObject(hdc, hHighlightBrush);
	Ellipse(hdc, cxsize / 2 + 100, cysize / 2 - 400, cxsize / 2 + 200, cysize / 2 - 300);
	/*==============================================================================================*/

	/* Get the ISum Interface */
	Sleep(1000);
	SelectObject(hdc, hDefaultBrush);
	//IUnknown
	Ellipse(hdc, cxsize / 2 + 100, cysize / 2 - 400, cxsize / 2 + 200, cysize / 2 - 300);
	SelectObject(hdc, hHighlightBrush);
	//ISum
	Ellipse(hdc, cxsize / 2 - 500, cysize / 2 - 150, cxsize / 2 - 400, cysize / 2 - 50);
	/*==============================================================================================*/

	/* Execute the CoClass Code */
	Sleep(1000);
	FillRect(hdc, &rcCoClassRect, hCoClassBrush);
	
	/*==============================================================================================*/

	/* End of ISum's Execution */
	Sleep(1000);
	SelectObject(hdc, hDefaultBrush);
	//ISum
	Ellipse(hdc, cxsize / 2 - 500, cysize / 2 - 150, cxsize / 2 - 400, cysize / 2 - 50);
	FillRect(hdc, &rcCoClassRect, hDefCoClassBrush);
	/*==============================================================================================*/

	/* Go to IUnknown */
	Sleep(1000);
	SelectObject(hdc, hHighlightBrush);
	//IUnknown
	Ellipse(hdc, cxsize / 2 + 100, cysize / 2 - 400, cxsize / 2 + 200, cysize / 2 - 300);
	/*==============================================================================================*/

	/* Get the ISubtract Interface */
	Sleep(1000);
	SelectObject(hdc, hDefaultBrush);
	//IUnknown
	Ellipse(hdc, cxsize / 2 + 100, cysize / 2 - 400, cxsize / 2 + 200, cysize / 2 - 300);
	SelectObject(hdc, hHighlightBrush);
	//ISubtract
	Ellipse(hdc, cxsize / 2 - 500, cysize / 2 + 50, cxsize / 2 - 400, cysize / 2 + 150);
	/*==============================================================================================*/

	/* Execute the CoClass Code for ISubtract */
	Sleep(1000);
	FillRect(hdc, &rcCoClassRect, hCoClassBrush);
	/*==============================================================================================*/

	/* End of ISubtract's Execution */
	Sleep(1000);
	SelectObject(hdc, hDefaultBrush);
	//ISubtract
	Ellipse(hdc, cxsize / 2 - 500, cysize / 2 + 50, cxsize / 2 - 400, cysize / 2 + 150);
	FillRect(hdc, &rcCoClassRect, hDefCoClassBrush);
	/*==============================================================================================*/

	DeleteObject(hPen);
	DeleteObject(holdPen);
	return S_OK;
}


/*====================================================================================*/

/* Implementation of CSumSubtractClassFactory methods */

CClassFactoryCreateStructureAnimateClassFactory::CClassFactoryCreateStructureAnimateClassFactory(void)
{
	m_cRef = 1;
}

CClassFactoryCreateStructureAnimateClassFactory::~CClassFactoryCreateStructureAnimateClassFactory(void)
{
	// no code
}

HRESULT CClassFactoryCreateStructureAnimateClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory*>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();

	return(S_OK);
}

ULONG CClassFactoryCreateStructureAnimateClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);

	return (m_cRef);
}

ULONG CClassFactoryCreateStructureAnimateClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete (this);
		return (0);
	}

	return (m_cRef);
}

HRESULT CClassFactoryCreateStructureAnimateClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	CClassFactoryCreateStructureAnimate* pCClassFactoryCreateStructureAnimate = NULL;
	HRESULT hr = S_OK;

	pCClassFactoryCreateStructureAnimate = new CClassFactoryCreateStructureAnimate;

	if (pCClassFactoryCreateStructureAnimate == NULL)
		return (E_OUTOFMEMORY);

	hr = pCClassFactoryCreateStructureAnimate->QueryInterface(riid, ppv);

	pCClassFactoryCreateStructureAnimate->Release();
	return(hr);
}

HRESULT CClassFactoryCreateStructureAnimateClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);

	return(S_OK);
}

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	// Variable Declaration
	CClassFactoryCreateStructureAnimateClassFactory* pCClassFactoryCreateStructureAnimateClassFactory = NULL;
	HRESULT hr = S_OK;

	if (rclsid != CLSID_CClassFactoryCreateStructureAnimate)
		return(CLASS_E_CLASSNOTAVAILABLE);

	pCClassFactoryCreateStructureAnimateClassFactory = new CClassFactoryCreateStructureAnimateClassFactory;

	if (pCClassFactoryCreateStructureAnimateClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCClassFactoryCreateStructureAnimateClassFactory->QueryInterface(riid, ppv);
	pCClassFactoryCreateStructureAnimateClassFactory->Release();

	return (hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return (S_OK);
	else
		return (S_FALSE);
}