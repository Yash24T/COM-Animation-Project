#include <windows.h>
#include "SirBirthdayContainmentInnerComponentWithRegFile.h"
#include "SirBirthdayContainmentOuterComponentWithRegFile.h"

//class declaration
class CContainmentOuterCreateStructureAnimate : public IContainmentCreateStructure, IContainmentAnimation
{
private:
	long m_cRef;
	IContainmentAnimation* m_pIContainmentAnimation;

public:
	//constructor
	CContainmentOuterCreateStructureAnimate(void);

	//Destructor
	~CContainmentOuterCreateStructureAnimate(void);

	//IUnknown Specific Methods
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall Animate(HWND, HDC, INT, INT);

	HRESULT __stdcall CreateStructure(HWND, HDC, INT, INT);

	//Custom method for inner component creation
	HRESULT __stdcall InitializeInnerComponent(void);
};

class CContainmentOuterCreateStructureAnimateClassFactory : public IClassFactory
{
private:
	long m_cRef;

public:
	//Constructor method declarations 
	CContainmentOuterCreateStructureAnimateClassFactory(void);

	//Destructor method declarations
	~CContainmentOuterCreateStructureAnimateClassFactory(void);

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

/* CContainmentOuterCreateStructureAnimate methods implementation */

CContainmentOuterCreateStructureAnimate::CContainmentOuterCreateStructureAnimate(void)
{
	m_pIContainmentAnimation = NULL;
	m_cRef = 1;

	InterlockedIncrement(&glNumberOfActiveComponents);
}

CContainmentOuterCreateStructureAnimate::~CContainmentOuterCreateStructureAnimate(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);

	if (m_pIContainmentAnimation)
	{
		m_pIContainmentAnimation->Release();
		m_pIContainmentAnimation = NULL;
	}
}

HRESULT CContainmentOuterCreateStructureAnimate::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IContainmentCreateStructure*> (this);
	else if (riid == IID_IContainmentCreateStructure)
		*ppv = static_cast<IContainmentCreateStructure*>(this);
	else if (riid == IID_IContainmentAnimation)
		*ppv = static_cast<IContainmentAnimation*>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CContainmentOuterCreateStructureAnimate::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CContainmentOuterCreateStructureAnimate::Release(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete(this);
		return (0);
	}

	return(m_cRef);
}

HRESULT CContainmentOuterCreateStructureAnimate::Animate(HWND hWnd, HDC hdc, INT cxsize, INT cysize)
{
	HRESULT hr;

	hr = m_pIContainmentAnimation->Animate(hWnd, hdc, cxsize, cysize);
	
	return hr;
}

HRESULT CContainmentOuterCreateStructureAnimate::CreateStructure(HWND hWnd, HDC hdc, INT cxsize, INT cysize)
{
	DWORD dwPenStyle = PS_SOLID;
	COLORREF colPenColor = RGB(255, 255, 255);
	HPEN hPen = CreatePen(dwPenStyle, 5, colPenColor);
	HPEN hPen2 = CreatePen(PS_DASH, 0, colPenColor);
	HPEN hBluePen = CreatePen(dwPenStyle, 5, RGB(0, 0, 255));


	POINT ptOuterCoClassRect[] = { {cxsize / 2 - 300, cysize / 2 - 200},
									{cxsize / 2 + 300, cysize / 2 - 200},
									{cxsize / 2 + 300, cysize / 2 + 200},
									{cxsize / 2 - 300, cysize / 2 + 200},
									{cxsize / 2 - 300, cysize / 2 - 200}, };

	POINT ptInnerCoClassRect[] = { {cxsize / 2 , cysize / 2},
									{cxsize / 2 + 300, cysize / 2},
									{cxsize / 2 + 300, cysize / 2 + 200},
									{cxsize / 2 , cysize / 2 + 200},
									{cxsize / 2 , cysize / 2}, };

	POINT ptISumLine[] = { {cxsize / 2 - 300, cysize / 2 - 200 + 50},
								{cxsize / 2 - 400, cysize / 2 - 200 + 50} };

	POINT ptISubtractLine[] = { {cxsize / 2 - 300, cysize / 2 - 200 + 50 + 100},
								{cxsize / 2 - 400, cysize / 2 - 200 + 50 + 100} };

	POINT ptIMultiplyLine[] = { {cxsize / 2 - 300, cysize / 2 + 50},
								{cxsize / 2 - 400, cysize / 2 + 50} };

	POINT ptIDivisionLine[] = { {cxsize / 2 - 300, cysize / 2 + 50 + 100},
								{cxsize / 2 - 400, cysize / 2 + 50 + 100} };

	POINT ptOuterIUnknownLine[] = { {cxsize / 2 + 150, cysize / 2 - 200},
								{cxsize / 2 + 150, cysize / 2 - 300} };

	POINT ptInnerIUnknownLine[] = { {cxsize / 2 + 150, cysize / 2},
								{cxsize / 2 + 150, cysize / 2 - 100} };

	POINT ptIMultiplyDashLine[] = { {cxsize / 2 - 300, cysize / 2 + 50},
									{cxsize / 2, cysize / 2 + 50} };

	POINT ptIDivisionDashLine[] = { {cxsize / 2 - 300, cysize / 2 + 50 + 100},
									{cxsize / 2, cysize / 2 + 50 + 100} };

	HBRUSH hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, hBrush);
	HPEN holdPen = (HPEN)SelectObject(hdc, hPen);

	//ISum
	Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25, cxsize / 2 - 400, cysize / 2 - 200 + 75);
	//ISubtract
	Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25 + 100, cxsize / 2 - 400, cysize / 2 - 200 + 75 + 100);
	//IMultiply
	Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25 + 200, cxsize / 2 - 400, cysize / 2 - 200 + 75 + 200);
	//IDivision
	Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25 + 300, cxsize / 2 - 400, cysize / 2 - 200 + 75 + 300);
	//Outer IUnknown
	Ellipse(hdc, cxsize / 2 + 125, cysize / 2 - 300, cxsize / 2 + 175, cysize / 2 - 350);
	holdPen = (HPEN)SelectObject(hdc, hBluePen);
	//Inner IUnknown
	Ellipse(hdc, cxsize / 2 + 125, cysize / 2 - 100, cxsize / 2 + 175, cysize / 2 - 150);
	Ellipse(hdc, cxsize / 2 + 500 + 50, cysize / 2 - 200, cxsize / 2 + 500 + 100, cysize / 2 - 150);

	holdPen = (HPEN)SelectObject(hdc, hPen);

	Polyline(hdc, ptOuterCoClassRect, 5);
	Polyline(hdc, ptInnerCoClassRect, 5);
	Polyline(hdc, ptISumLine, 2);
	Polyline(hdc, ptISubtractLine, 2);
	Polyline(hdc, ptIMultiplyLine, 2);
	Polyline(hdc, ptIDivisionLine, 2);
	Polyline(hdc, ptOuterIUnknownLine, 2);
	Polyline(hdc, ptInnerIUnknownLine, 2);

	DeleteObject(holdPen);
	DeleteObject(hPen);

	holdPen = (HPEN)SelectObject(hdc, hPen2);
	SetBkMode(hdc, TRANSPARENT);
	Polyline(hdc, ptIMultiplyDashLine, 2);
	Polyline(hdc, ptIDivisionDashLine, 2);

	// Add Text to Interfaces

	HFONT hFont = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Impact"));
	HFONT hFont2 = CreateFont(80, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Impact"));
	SelectObject(hdc, hFont);

	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 158, 0));

	TCHAR lpszString[256];

	RECT rcISumLayoutRect = { cxsize / 2 - 600, cysize / 2 - 200 + 85, cxsize / 2 - 600 + 300, cysize / 2 - 200 + 85 + 30 };
	RECT rcISubtractLayoutRect = { cxsize / 2 - 600, cysize / 2 - 200 + 185, cxsize / 2 - 600 + 300, cysize / 2 - 200 + 185 + 30 };
	RECT rcIMultiplicationLayoutRect = { cxsize / 2 - 600, cysize / 2 - 200 + 285, cxsize / 2 - 600 + 300, cysize / 2 - 200 + 285 + 30 };
	RECT rcIDivisionLayoutRect = { cxsize / 2 - 600, cysize / 2 - 200 + 385, cxsize / 2 - 600 + 300, cysize / 2 - 200 + 385 + 30 };
	RECT rcOuterIUnknownLayoutRect = { cxsize / 2, cysize / 2 - 400, cxsize / 2 + 300, cysize / 2 - 400 + 50 };
	RECT rcInnerIUnknownLayoutRect = { cxsize / 2 + 500, cysize / 2 - 130, cxsize / 2 + 500 + 150, cysize / 2 - 80 };
	RECT rcInnerCoClassLayoutRect = { cxsize / 2, cysize / 2, cxsize / 2 + 300, cysize / 2 + 30 };
	RECT rcOuterCoClassLayoutRect = { cxsize / 2 - 300, cysize / 2 - 200, cxsize / 2 - 300 + 600, cysize / 2 - 200 + 30 };
	RECT rcTitleRect = { 100, cysize - 150, cxsize - 100, cysize - 50 };


	wsprintf(lpszString, "ISum Interface");
	DrawText(hdc, lpszString, -1, &rcISumLayoutRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	wsprintf(lpszString, "ISubtract Interface");
	DrawText(hdc, lpszString, -1, &rcISubtractLayoutRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	wsprintf(lpszString, "IMultiplication Interface");
	DrawText(hdc, lpszString, -1, &rcIMultiplicationLayoutRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	wsprintf(lpszString, "IDivision Interface");
	DrawText(hdc, lpszString, -1, &rcIDivisionLayoutRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	wsprintf(lpszString, "Outer\n IUnknown");
	DrawText(hdc, lpszString, -1, &rcOuterIUnknownLayoutRect, DT_CENTER | DT_VCENTER);

	wsprintf(lpszString, "Inner\n IUnknown");
	DrawText(hdc, lpszString, -1, &rcInnerIUnknownLayoutRect, DT_CENTER | DT_VCENTER);

	wsprintf(lpszString, "Outer Component");
	DrawText(hdc, lpszString, -1, &rcOuterCoClassLayoutRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	wsprintf(lpszString, "Inner Component");
	DrawText(hdc, lpszString, -1, &rcInnerCoClassLayoutRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	SelectObject(hdc, hFont2);
	wsprintf(lpszString, "Containment");
	DrawText(hdc, lpszString, -1, &rcTitleRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	DeleteObject(hPen2);
	DeleteObject(holdPen);
	
	return S_OK;
}

HRESULT CContainmentOuterCreateStructureAnimate::InitializeInnerComponent(void)
{
	//variable declaration
	HRESULT hr;

	hr = CoCreateInstance(CLSID_CContainmentCreateStructureAnimate, NULL, CLSCTX_INPROC_SERVER, IID_IContainmentAnimation, (void**)&m_pIContainmentAnimation);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("m_pIContainmentAnimation Interface cannot be obtained from inner component."), TEXT("Error"), MB_OK);
		return(E_FAIL);
	}

	return(S_OK);
}


/*===================================================================================================================================================*/

// CContainmentOuterCreateStructureAnimateClassFactory method implementation

CContainmentOuterCreateStructureAnimateClassFactory::CContainmentOuterCreateStructureAnimateClassFactory(void)
{
	m_cRef = 1;
}

CContainmentOuterCreateStructureAnimateClassFactory::~CContainmentOuterCreateStructureAnimateClassFactory(void)
{
	// no code
}

HRESULT CContainmentOuterCreateStructureAnimateClassFactory::QueryInterface(REFIID riid, void** ppv)
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

ULONG CContainmentOuterCreateStructureAnimateClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);

	return (m_cRef);
}

ULONG CContainmentOuterCreateStructureAnimateClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete (this);
		return (0);
	}

	return (m_cRef);
}

HRESULT CContainmentOuterCreateStructureAnimateClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	CContainmentOuterCreateStructureAnimate* pCContainmentOuterCreateStructureAnimate = NULL;
	HRESULT hr = S_OK;

	if (pUnkOuter != NULL)
		return (CLASS_E_NOAGGREGATION);

	pCContainmentOuterCreateStructureAnimate = new CContainmentOuterCreateStructureAnimate;

	if (pCContainmentOuterCreateStructureAnimate == NULL)
		return (E_OUTOFMEMORY);

	hr = pCContainmentOuterCreateStructureAnimate->InitializeInnerComponent();
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Failed to Initialize Inner Component"), TEXT("Error"), MB_OK);
		pCContainmentOuterCreateStructureAnimate->Release();
		return(hr);
	}

	hr = pCContainmentOuterCreateStructureAnimate->QueryInterface(riid, ppv);

	pCContainmentOuterCreateStructureAnimate->Release();
	return(hr);
}

HRESULT CContainmentOuterCreateStructureAnimateClassFactory::LockServer(BOOL fLock)
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

	CContainmentOuterCreateStructureAnimateClassFactory* pCContainmentOuterCreateStructureAnimateClassFactory = NULL;
	HRESULT hr = S_OK;

	if (rclsid != CLSID_CContainmentOuterCreateStructureAnimate)
		return(CLASS_E_CLASSNOTAVAILABLE);

	pCContainmentOuterCreateStructureAnimateClassFactory = new CContainmentOuterCreateStructureAnimateClassFactory;

	if (pCContainmentOuterCreateStructureAnimateClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCContainmentOuterCreateStructureAnimateClassFactory->QueryInterface(riid, ppv);
	pCContainmentOuterCreateStructureAnimateClassFactory->Release();

	return (hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return (S_OK);
	else
		return (S_FALSE);
}