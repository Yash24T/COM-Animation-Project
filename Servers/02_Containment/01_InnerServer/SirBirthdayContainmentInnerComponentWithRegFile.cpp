#define UNICODE 
#include <windows.h>
#include "SirBirthdayContainmentInnerComponentWithRegFile.h"

//Class Declaration
class CContainmentCreateStructureAnimate :public IContainmentAnimation
{
private:
	long m_cRef;

public:
	//Constructor Method Declaration
	CContainmentCreateStructureAnimate(void);

	//Destructor Method declaration
	~CContainmentCreateStructureAnimate(void);

	//IUnknown specific method declaration (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IContainmentAnimate specific method declaration (inherited)
	HRESULT __stdcall Animate(HWND, HDC, INT, INT);
	
};

class CContainmentCreateStructureAnimateClassFactory : public IClassFactory
{
private:
	long m_cRef;

public:
	//Constructor method declarations 
	CContainmentCreateStructureAnimateClassFactory(void);

	//Destructor method declarations
	~CContainmentCreateStructureAnimateClassFactory(void);

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

CContainmentCreateStructureAnimate::CContainmentCreateStructureAnimate(void)
{
	m_cRef = 1;

	InterlockedIncrement(&glNumberOfActiveComponents);
}

CContainmentCreateStructureAnimate::~CContainmentCreateStructureAnimate(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT CContainmentCreateStructureAnimate::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IContainmentAnimation*>(this);
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

ULONG CContainmentCreateStructureAnimate::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CContainmentCreateStructureAnimate::Release(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete(this);
		return (0);
	}

	return(m_cRef);
}

HRESULT CContainmentCreateStructureAnimate::Animate(HWND hWnd, HDC hdc, INT cxsize, INT cysize)
{
    DWORD dwPenStyle = PS_SOLID;
    COLORREF colPenColor = RGB(255, 255, 255);
    COLORREF colBlackPenColor = RGB(0, 0, 0);
    HPEN hPen = CreatePen(dwPenStyle, 5, colPenColor);
    HPEN hPen2 = CreatePen(PS_DASH, 0, colPenColor);
    HPEN hPen3 = CreatePen(PS_DASH, 0, colBlackPenColor);
    HPEN hBluePen = CreatePen(dwPenStyle, 5, RGB(0, 0, 255));
    HPEN hBlackPen = CreatePen(dwPenStyle, 5, RGB(0, 0, 0));

    HPEN holdPen = (HPEN)SelectObject(hdc, hPen);

    HBRUSH hHighlightBrush = (HBRUSH)CreateSolidBrush(RGB(255, 158, 0));
    HBRUSH hDefaultBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));

    POINT ptIMultiplyDashLine[] = { {cxsize / 2 - 300, cysize / 2 + 50},
                                    {cxsize / 2, cysize / 2 + 50} };

    POINT ptIDivisionDashLine[] = { {cxsize / 2 - 300, cysize / 2 + 50 + 100},
                                    {cxsize / 2, cysize / 2 + 50 + 100} };

    RECT rcInnerCoClassLayoutRect = { cxsize / 2 + 5, cysize / 2 + 30, cxsize / 2 + 300 - 5, cysize / 2 + 200 - 5 };
    RECT rcOuterCoClassLayoutRect1 = { cxsize / 2 - 300 + 5, cysize / 2 - 200 + 30, cxsize / 2 - 300 + 600 - 5, cysize / 2 };
    RECT rcOuterCoClassLayoutRect2 = { cxsize / 2 - 300 + 5, cysize / 2 - 200 + 30, cxsize / 2, cysize / 2 + 200 - 5 };

    POINT ptInnerIUnknownLine[] = { {cxsize / 2 + 150, cysize / 2},
                                {cxsize / 2 + 150, cysize / 2 - 100} };

    TCHAR lpszString[256];
    SetBkMode(hdc, TRANSPARENT);

    /*
    //ISum
    Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25, cxsize / 2 - 400, cysize / 2 - 200 + 75);
    //ISubtract
    Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25 + 100, cxsize / 2 - 400, cysize / 2 - 200 + 75 + 100);
    //IMultiply
    Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25 + 200, cxsize / 2 - 400, cysize / 2 - 200 + 75 + 200);
    //IDivision
    Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25 + 300, cxsize / 2 - 400, cysize / 2 - 200 + 75 + 300);
    //IUnknown
    Ellipse(hdc, cxsize / 2 + 125, cysize / 2 - 300, cxsize / 2 + 175, cysize / 2 - 350);
    //Inner IUnknown
    Ellipse(hdc, cxsize / 2 + 125, cysize / 2 - 100, cxsize / 2 + 175, cysize / 2 - 150);
    */

    Sleep(1000);

    // Go to IUnknown
    SelectObject(hdc, hHighlightBrush);
    //IUnknown
    Ellipse(hdc, cxsize / 2 + 125, cysize / 2 - 300, cxsize / 2 + 175, cysize / 2 - 350);
    /*======================================================*/

    Sleep(1000);

    // Get the ISum
    SelectObject(hdc, hDefaultBrush);
    //IUnknown
    Ellipse(hdc, cxsize / 2 + 125, cysize / 2 - 300, cxsize / 2 + 175, cysize / 2 - 350);
    SelectObject(hdc, hHighlightBrush);
    //ISum
    Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25, cxsize / 2 - 400, cysize / 2 - 200 + 75);
    /*======================================================*/

    Sleep(1000);

    // Execute the Outer Component
    SelectObject(hdc, hDefaultBrush);
    //ISum
    Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25, cxsize / 2 - 400, cysize / 2 - 200 + 75);
    FillRect(hdc, &rcOuterCoClassLayoutRect1, hHighlightBrush);
    FillRect(hdc, &rcOuterCoClassLayoutRect2, hHighlightBrush);
    /*======================================================*/

    Sleep(1000);

    // Done with Outer Execution
    holdPen = (HPEN)SelectObject(hdc, hPen2);
    FillRect(hdc, &rcOuterCoClassLayoutRect1, hDefaultBrush);
    FillRect(hdc, &rcOuterCoClassLayoutRect2, hDefaultBrush);
    Polyline(hdc, ptIMultiplyDashLine, 2);
    Polyline(hdc, ptIDivisionDashLine, 2);
    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hDefaultBrush);
    //Inner IUnknown
    Ellipse(hdc, cxsize / 2 + 125, cysize / 2 - 100, cxsize / 2 + 175, cysize / 2 - 150);
    holdPen = (HPEN)SelectObject(hdc, hPen);
    Polyline(hdc, ptInnerIUnknownLine, 2);
    /*======================================================*/

    Sleep(1000);

    // Go to IUnknown

    SelectObject(hdc, hHighlightBrush);
    //IUnknown
    Ellipse(hdc, cxsize / 2 + 125, cysize / 2 - 300, cxsize / 2 + 175, cysize / 2 - 350);
    /*======================================================*/

    Sleep(1000);

    // Get the ISubtract
    SelectObject(hdc, hDefaultBrush);
    //IUnknown
    Ellipse(hdc, cxsize / 2 + 125, cysize / 2 - 300, cxsize / 2 + 175, cysize / 2 - 350);
    SelectObject(hdc, hHighlightBrush);
    //ISubtract
    Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25 + 100, cxsize / 2 - 400, cysize / 2 - 200 + 75 + 100);
    /*======================================================*/

    Sleep(1000);

    // Execute the Outer Component
    SelectObject(hdc, hDefaultBrush);
    //ISubtract
    Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25 + 100, cxsize / 2 - 400, cysize / 2 - 200 + 75 + 100);
    FillRect(hdc, &rcOuterCoClassLayoutRect1, hHighlightBrush);
    FillRect(hdc, &rcOuterCoClassLayoutRect2, hHighlightBrush);

    /*======================================================*/

    Sleep(1000);

    // Done with Outer Execution
    holdPen = (HPEN)SelectObject(hdc, hPen2);
    FillRect(hdc, &rcOuterCoClassLayoutRect1, hDefaultBrush);
    FillRect(hdc, &rcOuterCoClassLayoutRect2, hDefaultBrush);
    Polyline(hdc, ptIMultiplyDashLine, 2);
    Polyline(hdc, ptIDivisionDashLine, 2);
    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hDefaultBrush);
    //Inner IUnknown
    Ellipse(hdc, cxsize / 2 + 125, cysize / 2 - 100, cxsize / 2 + 175, cysize / 2 - 150);
    holdPen = (HPEN)SelectObject(hdc, hPen);
    Polyline(hdc, ptInnerIUnknownLine, 2);
    /*======================================================*/

    Sleep(1000);

    // Go to IUnknown
    SelectObject(hdc, hHighlightBrush);
    //IUnknown
    Ellipse(hdc, cxsize / 2 + 125, cysize / 2 - 300, cxsize / 2 + 175, cysize / 2 - 350);
    /*======================================================*/

    Sleep(1000);

    // Get the IMultiply
    SelectObject(hdc, hDefaultBrush);
    //IUnknown
    Ellipse(hdc, cxsize / 2 + 125, cysize / 2 - 300, cxsize / 2 + 175, cysize / 2 - 350);
    SelectObject(hdc, hHighlightBrush);
    //IMultiply
    Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25 + 200, cxsize / 2 - 400, cysize / 2 - 200 + 75 + 200);
    /*======================================================*/

    Sleep(1000);

    // Execute the Outer + Inner Component
    SelectObject(hdc, hDefaultBrush);
    //IMultiply
    Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25 + 200, cxsize / 2 - 400, cysize / 2 - 200 + 75 + 200);
    FillRect(hdc, &rcOuterCoClassLayoutRect1, hHighlightBrush);
    FillRect(hdc, &rcOuterCoClassLayoutRect2, hHighlightBrush);
    holdPen = (HPEN)SelectObject(hdc, hPen3);
    Polyline(hdc, ptIMultiplyDashLine, 2);
    Polyline(hdc, ptIDivisionDashLine, 2);
    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hDefaultBrush);
    //Inner IUnknown
    Ellipse(hdc, cxsize / 2 + 125, cysize / 2 - 100, cxsize / 2 + 175, cysize / 2 - 150);
    holdPen = (HPEN)SelectObject(hdc, hBlackPen);
    Polyline(hdc, ptInnerIUnknownLine, 2);
    holdPen = (HPEN)SelectObject(hdc, hPen);
    Sleep(500);
    FillRect(hdc, &rcInnerCoClassLayoutRect, hHighlightBrush);
    /*======================================================*/

    Sleep(1000);

    // Done with Outer + Inner Execution
    holdPen = (HPEN)SelectObject(hdc, hPen2);
    FillRect(hdc, &rcOuterCoClassLayoutRect1, hDefaultBrush);
    FillRect(hdc, &rcOuterCoClassLayoutRect2, hDefaultBrush);
    FillRect(hdc, &rcInnerCoClassLayoutRect, hDefaultBrush);
    Polyline(hdc, ptIMultiplyDashLine, 2);
    Polyline(hdc, ptIDivisionDashLine, 2);
    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hDefaultBrush);
    //Inner IUnknown
    Ellipse(hdc, cxsize / 2 + 125, cysize / 2 - 100, cxsize / 2 + 175, cysize / 2 - 150);
    holdPen = (HPEN)SelectObject(hdc, hPen);
    Polyline(hdc, ptInnerIUnknownLine, 2);
    /*======================================================*/

    Sleep(1000);

    // Go to IUnknown
    SelectObject(hdc, hHighlightBrush);
    //IUnknown
    Ellipse(hdc, cxsize / 2 + 125, cysize / 2 - 300, cxsize / 2 + 175, cysize / 2 - 350);
    /*======================================================*/

    Sleep(1000);

    // Get the IDivision
    SelectObject(hdc, hDefaultBrush);
    //IUnknown
    Ellipse(hdc, cxsize / 2 + 125, cysize / 2 - 300, cxsize / 2 + 175, cysize / 2 - 350);
    SelectObject(hdc, hHighlightBrush);
    //IDivision
    Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25 + 300, cxsize / 2 - 400, cysize / 2 - 200 + 75 + 300);
    /*======================================================*/

    Sleep(1000);

    // Execute the Outer + Inner Component
    SelectObject(hdc, hDefaultBrush);
    //IDivision
    Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25 + 300, cxsize / 2 - 400, cysize / 2 - 200 + 75 + 300);
    FillRect(hdc, &rcOuterCoClassLayoutRect1, hHighlightBrush);
    FillRect(hdc, &rcOuterCoClassLayoutRect2, hHighlightBrush);
    holdPen = (HPEN)SelectObject(hdc, hPen3);
    Polyline(hdc, ptIMultiplyDashLine, 2);
    Polyline(hdc, ptIDivisionDashLine, 2);
    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hDefaultBrush);
    //Inner IUnknown
    Ellipse(hdc, cxsize / 2 + 125, cysize / 2 - 100, cxsize / 2 + 175, cysize / 2 - 150);
    holdPen = (HPEN)SelectObject(hdc, hBlackPen);
    Polyline(hdc, ptInnerIUnknownLine, 2);
    holdPen = (HPEN)SelectObject(hdc, hPen);
    Sleep(500);
    FillRect(hdc, &rcInnerCoClassLayoutRect, hHighlightBrush);
    /*======================================================*/

    Sleep(1000);

    // Done with Outer + Inner Execution
    holdPen = (HPEN)SelectObject(hdc, hPen2);
    FillRect(hdc, &rcOuterCoClassLayoutRect1, hDefaultBrush);
    FillRect(hdc, &rcOuterCoClassLayoutRect2, hDefaultBrush);
    FillRect(hdc, &rcInnerCoClassLayoutRect, hDefaultBrush);
    Polyline(hdc, ptIMultiplyDashLine, 2);
    Polyline(hdc, ptIDivisionDashLine, 2);
    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hDefaultBrush);
    //Inner IUnknown
    Ellipse(hdc, cxsize / 2 + 125, cysize / 2 - 100, cxsize / 2 + 175, cysize / 2 - 150);
    holdPen = (HPEN)SelectObject(hdc, hPen);
    Polyline(hdc, ptInnerIUnknownLine, 2);
    /*======================================================*/

    DeleteObject(hHighlightBrush);
    DeleteObject(hDefaultBrush);
    DeleteObject(hPen);

	return S_OK;
}


/*====================================================================================*/

/* Implementation of CSumSubtractClassFactory methods */

CContainmentCreateStructureAnimateClassFactory::CContainmentCreateStructureAnimateClassFactory(void)
{
	m_cRef = 1;
}

CContainmentCreateStructureAnimateClassFactory::~CContainmentCreateStructureAnimateClassFactory(void)
{
	// no code
}

HRESULT CContainmentCreateStructureAnimateClassFactory::QueryInterface(REFIID riid, void** ppv)
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

ULONG CContainmentCreateStructureAnimateClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);

	return (m_cRef);
}

ULONG CContainmentCreateStructureAnimateClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete (this);
		return (0);
	}

	return (m_cRef);
}

HRESULT CContainmentCreateStructureAnimateClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	CContainmentCreateStructureAnimate* pCContainmentCreateStructureAnimate = NULL;
	HRESULT hr = S_OK;

	pCContainmentCreateStructureAnimate = new CContainmentCreateStructureAnimate;

	if (pCContainmentCreateStructureAnimate == NULL)
		return (E_OUTOFMEMORY);

	hr = pCContainmentCreateStructureAnimate->QueryInterface(riid, ppv);

	pCContainmentCreateStructureAnimate->Release();
	return(hr);
}

HRESULT CContainmentCreateStructureAnimateClassFactory::LockServer(BOOL fLock)
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

	CContainmentCreateStructureAnimateClassFactory* pCContainmentCreateStructureAnimateClassFactory = NULL;
	HRESULT hr = S_OK;

	if (rclsid != CLSID_CContainmentCreateStructureAnimate)
		return(CLASS_E_CLASSNOTAVAILABLE);

	pCContainmentCreateStructureAnimateClassFactory = new CContainmentCreateStructureAnimateClassFactory;

	if (pCContainmentCreateStructureAnimateClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCContainmentCreateStructureAnimateClassFactory->QueryInterface(riid, ppv);
	pCContainmentCreateStructureAnimateClassFactory->Release();

	return (hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return (S_OK);
	else
		return (S_FALSE);
}