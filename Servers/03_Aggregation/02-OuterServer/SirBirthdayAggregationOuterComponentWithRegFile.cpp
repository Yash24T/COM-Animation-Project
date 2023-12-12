#include <windows.h>
#include "SirBirthdayAggregationInnerComponentWithRegFile.h"
#include "SirBirthdayAggregationOuterComponentWithRegFile.h"

//class declaration
class CAggregationOuterCreateStructureAnimate : public IAggregationCreateStructure
{
private:
	long m_cRef;
	IUnknown* m_pIUnknownInner;

public:
	//constructor
	CAggregationOuterCreateStructureAnimate(void);

	//Destructor
	~CAggregationOuterCreateStructureAnimate(void);

	//IUnknown Specific Methods
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IAggregationCreateStructure specific methods
	HRESULT __stdcall CreateStructure(HWND, HDC, INT, INT);

	//Custom method for inner component creation
	HRESULT __stdcall InitializeInnerComponent(void);
};

class CAggregationOuterCreateStructureAnimateClassFactory : public IClassFactory
{
private:
	long m_cRef;

public:
	//Constructor method declarations 
	CAggregationOuterCreateStructureAnimateClassFactory(void);

	//Destructor method declarations
	~CAggregationOuterCreateStructureAnimateClassFactory(void);

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

/* CAggregationOuterCreateStructureAnimate methods implementation */

CAggregationOuterCreateStructureAnimate::CAggregationOuterCreateStructureAnimate(void)
{
	m_pIUnknownInner = NULL;
	m_cRef = 1;

	InterlockedIncrement(&glNumberOfActiveComponents);
}

CAggregationOuterCreateStructureAnimate::~CAggregationOuterCreateStructureAnimate(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);

	if (m_pIUnknownInner)
	{
		m_pIUnknownInner->Release();
		m_pIUnknownInner = NULL;
	}
}

HRESULT CAggregationOuterCreateStructureAnimate::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IAggregationCreateStructure*> (this);
	else if (riid == IID_IAggregationCreateStructure)
		*ppv = static_cast<IAggregationCreateStructure*>(this);
	else if (riid == IID_IAggregationAnimation)
		return(m_pIUnknownInner->QueryInterface(riid, ppv));
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CAggregationOuterCreateStructureAnimate::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CAggregationOuterCreateStructureAnimate::Release(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete(this);
		return (0);
	}

	return(m_cRef);
}

HRESULT __stdcall CAggregationOuterCreateStructureAnimate::CreateStructure(HWND hWnd, HDC hdc, INT cxsize, INT cysize)
{
	DWORD dwPenStyle = PS_SOLID;
	COLORREF colPenColor = RGB(255, 255, 255);
	HPEN hPen = CreatePen(dwPenStyle, 5, colPenColor);
	HPEN hRedPen = CreatePen(dwPenStyle, 5, RGB(255, 0, 0));
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

	POINT ptOuterIUnknownLine[] = { {cxsize / 2 - 150, cysize / 2 - 200},
								{cxsize / 2 - 150, cysize / 2 - 300} };

	POINT ptInnerIUnknownLine[] = { {cxsize / 2 + 75, cysize / 2},
									{cxsize / 2 + 75, cysize / 2 - 100} };

	POINT ptInnerNoAggregationIUnknownLine[] = { {cxsize / 2 + 225, cysize / 2},
												 {cxsize / 2 + 225, cysize / 2 - 100} };

	POINT ptIMultiplyInnerLine[] = { {cxsize / 2 - 300, cysize / 2 + 50},
									{cxsize / 2, cysize / 2 + 50} };

	POINT ptIDivisionInnerLine[] = { {cxsize / 2 - 300, cysize / 2 + 50 + 100},
									{cxsize / 2, cysize / 2 + 50 + 100} };
	HPEN holdPen = (HPEN)SelectObject(hdc, hPen);
	HBRUSH hDefaultBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, hDefaultBrush);

	//ISum
	Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25, cxsize / 2 - 400, cysize / 2 - 200 + 75);
	//ISubtract
	Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25 + 100, cxsize / 2 - 400, cysize / 2 - 200 + 75 + 100);
	//IMultiply
	Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25 + 200, cxsize / 2 - 400, cysize / 2 - 200 + 75 + 200);
	//IDivision
	Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25 + 300, cxsize / 2 - 400, cysize / 2 - 200 + 75 + 300);
	//Outer IUnknown
	Ellipse(hdc, cxsize / 2 - 175, cysize / 2 - 300, cxsize / 2 - 125, cysize / 2 - 350);
	holdPen = (HPEN)SelectObject(hdc, hRedPen);
	//Inner IUnknown
	Ellipse(hdc, cxsize / 2 + 50, cysize / 2 - 100, cxsize / 2 + 100, cysize / 2 - 150);
	Ellipse(hdc, cxsize / 2 + 550, cysize / 2 - 120, cxsize / 2 + 600, cysize / 2 - 170);
	holdPen = (HPEN)SelectObject(hdc, hBluePen);
	//Inner NoAggregation IUnknown
	Ellipse(hdc, cxsize / 2 + 200, cysize / 2 - 100, cxsize / 2 + 250, cysize / 2 - 150);
	Ellipse(hdc, cxsize / 2 + 550, cysize / 2 + 50, cxsize / 2 + 600, cysize / 2 + 100);
	holdPen = (HPEN)SelectObject(hdc, hPen);
	Polyline(hdc, ptOuterCoClassRect, 5);
	Polyline(hdc, ptInnerCoClassRect, 5);
	Polyline(hdc, ptISumLine, 2);
	Polyline(hdc, ptISubtractLine, 2);
	Polyline(hdc, ptIMultiplyLine, 2);
	Polyline(hdc, ptIDivisionLine, 2);
	Polyline(hdc, ptOuterIUnknownLine, 2);
	Polyline(hdc, ptInnerIUnknownLine, 2);
	Polyline(hdc, ptInnerNoAggregationIUnknownLine, 2);
	Polyline(hdc, ptIMultiplyInnerLine, 2);
	Polyline(hdc, ptIDivisionInnerLine, 2);

	// Add Text to Interfaces

	HFONT hFont = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Impact"));

	SelectObject(hdc, hFont);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 158, 0));

	TCHAR lpszString[256];

	RECT rcISumLayoutRect = { cxsize / 2 - 600, cysize / 2 - 200 + 85, cxsize / 2 - 600 + 300, cysize / 2 - 200 + 85 + 30 };
	RECT rcISubtractLayoutRect = { cxsize / 2 - 600, cysize / 2 - 200 + 185, cxsize / 2 - 600 + 300, cysize / 2 - 200 + 185 + 30 };
	RECT rcIMultiplicationLayoutRect = { cxsize / 2 - 600, cysize / 2 - 200 + 285, cxsize / 2 - 600 + 300, cysize / 2 - 200 + 285 + 30 };
	RECT rcIDivisionLayoutRect = { cxsize / 2 - 600, cysize / 2 - 200 + 385, cxsize / 2 - 600 + 300, cysize / 2 - 200 + 385 + 30 };
	RECT rcOuterIUnknownLayoutRect = { cxsize / 2 - 200, cysize / 2 - 400, cxsize / 2 - 100, cysize / 2 - 400 + 50 };
	RECT rcInnerIUnknownLayoutRect = { cxsize / 2 + 500, cysize / 2 - 100, cxsize / 2 + 150 + 500, cysize / 2 - 50 };
	RECT rcInnerNoAggregationIUnknownLayoutRect = { cxsize / 2 + 500, cysize / 2 + 120, cxsize / 2 + 500 + 150, cysize / 2 + 120 + 50 };
	RECT rcInnerCoClassLayoutRect = { cxsize / 2, cysize / 2, cxsize / 2 + 300, cysize / 2 + 30 };
	RECT rcOuterCoClassLayoutRect = { cxsize / 2 - 300, cysize / 2 - 200, cxsize / 2 - 300 + 600, cysize / 2 - 200 + 30 };

	wsprintf(lpszString, "ISum Interface");
	DrawText(hdc, lpszString, -1, &rcISumLayoutRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	wsprintf(lpszString, "ISubtract Interface");
	DrawText(hdc, lpszString, -1, &rcISubtractLayoutRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	wsprintf(lpszString, "IMultiplication Interface");
	DrawText(hdc, lpszString, -1, &rcIMultiplicationLayoutRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	wsprintf(lpszString, "IDivision Interface");
	DrawText(hdc, lpszString, -1, &rcIDivisionLayoutRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	wsprintf(lpszString, "Outer\nIUnknown");
	DrawText(hdc, lpszString, -1, &rcOuterIUnknownLayoutRect, DT_CENTER | DT_VCENTER);

	wsprintf(lpszString, "Inner\nIUnknown");
	DrawText(hdc, lpszString, -1, &rcInnerIUnknownLayoutRect, DT_CENTER | DT_VCENTER);

	wsprintf(lpszString, "NoAggregation\nIUnknown");
	DrawText(hdc, lpszString, -1, &rcInnerNoAggregationIUnknownLayoutRect, DT_CENTER | DT_VCENTER);

	wsprintf(lpszString, "Outer Component");
	DrawText(hdc, lpszString, -1, &rcOuterCoClassLayoutRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	wsprintf(lpszString, "Inner Component");
	DrawText(hdc, lpszString, -1, &rcInnerCoClassLayoutRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	DeleteObject(holdPen);

	return S_OK;
}

HRESULT CAggregationOuterCreateStructureAnimate::InitializeInnerComponent(void)
{
	//variable declaration
	HRESULT hr;

	hr = CoCreateInstance(CLSID_CAggregationCreateStructureAnimate, reinterpret_cast<IUnknown*>(this), CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&m_pIUnknownInner);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IUnknown Interface cannot be obtained from inner component."), TEXT("Error"), MB_OK);
		return(E_FAIL);
	}

	return(S_OK);
}


/*===================================================================================================================================================*/

// CAggregationOuterCreateStructureAnimateClassFactory method implementation

CAggregationOuterCreateStructureAnimateClassFactory::CAggregationOuterCreateStructureAnimateClassFactory(void)
{
	m_cRef = 1;
}

CAggregationOuterCreateStructureAnimateClassFactory::~CAggregationOuterCreateStructureAnimateClassFactory(void)
{
	// no code
}

HRESULT CAggregationOuterCreateStructureAnimateClassFactory::QueryInterface(REFIID riid, void** ppv)
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

ULONG CAggregationOuterCreateStructureAnimateClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);

	return (m_cRef);
}

ULONG CAggregationOuterCreateStructureAnimateClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete (this);
		return (0);
	}

	return (m_cRef);
}

HRESULT CAggregationOuterCreateStructureAnimateClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	CAggregationOuterCreateStructureAnimate* pCAggregationOuterCreateStructureAnimate = NULL;
	HRESULT hr = S_OK;

	if (pUnkOuter != NULL)
		return (CLASS_E_NOAGGREGATION);

	pCAggregationOuterCreateStructureAnimate = new CAggregationOuterCreateStructureAnimate;

	if (pCAggregationOuterCreateStructureAnimate == NULL)
		return (E_OUTOFMEMORY);

	hr = pCAggregationOuterCreateStructureAnimate->InitializeInnerComponent();
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Failed to Initialize Inner Component"), TEXT("Error"), MB_OK);
		pCAggregationOuterCreateStructureAnimate->Release();
		return(hr);
	}

	hr = pCAggregationOuterCreateStructureAnimate->QueryInterface(riid, ppv);

	pCAggregationOuterCreateStructureAnimate->Release();
	return(hr);
}

HRESULT CAggregationOuterCreateStructureAnimateClassFactory::LockServer(BOOL fLock)
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

	CAggregationOuterCreateStructureAnimateClassFactory* pCAggregationOuterCreateStructureAnimateClassFactory = NULL;
	HRESULT hr = S_OK;

	if (rclsid != CLSID_CAggregationOuterCreateStructureAnimate)
		return(CLASS_E_CLASSNOTAVAILABLE);

	pCAggregationOuterCreateStructureAnimateClassFactory = new CAggregationOuterCreateStructureAnimateClassFactory;

	if (pCAggregationOuterCreateStructureAnimateClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCAggregationOuterCreateStructureAnimateClassFactory->QueryInterface(riid, ppv);
	pCAggregationOuterCreateStructureAnimateClassFactory->Release();

	return (hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return (S_OK);
	else
		return (S_FALSE);
}