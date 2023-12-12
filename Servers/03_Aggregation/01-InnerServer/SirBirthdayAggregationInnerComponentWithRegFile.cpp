#define UNICODE 
#include <windows.h>
#include "SirBirthdayAggregationInnerComponentWithRegFile.h"

// interface declaration (for internal use only i.e. not to be included in .h file!!
interface INoAggregationIUnknown
{
	virtual HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void**) = 0;
	virtual ULONG __stdcall AddRef_NoAggregation(void) = 0;
	virtual ULONG __stdcall Release_NoAggregation(void) = 0;
};

//Class Declaration
class CAggregationCreateStructureAnimate :public INoAggregationIUnknown, IAggregationAnimation
{
private:
	long m_cRef;
	IUnknown* m_pIUnknownOuter;

public:
	//Constructor Method Declaration
	CAggregationCreateStructureAnimate(IUnknown*);

	//Destructor Method declaration
	~CAggregationCreateStructureAnimate(void);

	//IUnknown specific method declaration (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//INoAggregationIUnknown Specific methods
	HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void**);
	ULONG __stdcall AddRef_NoAggregation(void);
	ULONG __stdcall Release_NoAggregation(void);

	//IAggregationAnimation specific method declaration (inherited)
	HRESULT __stdcall Animate(HWND, HDC, INT, INT);
	
};

class CAggregationCreateStructureAnimateClassFactory : public IClassFactory
{
private:
	long m_cRef;

public:
	//Constructor method declarations 
	CAggregationCreateStructureAnimateClassFactory(void);

	//Destructor method declarations
	~CAggregationCreateStructureAnimateClassFactory(void);

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

CAggregationCreateStructureAnimate::CAggregationCreateStructureAnimate(IUnknown* pIUnknownOuter)
{
	m_cRef = 1;

	InterlockedIncrement(&glNumberOfActiveComponents);

	if (pIUnknownOuter != NULL)
		m_pIUnknownOuter = pIUnknownOuter;
	else
		m_pIUnknownOuter = reinterpret_cast<IUnknown*>(static_cast<INoAggregationIUnknown*>(this));
}

CAggregationCreateStructureAnimate::~CAggregationCreateStructureAnimate(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
	if(m_pIUnknownOuter)
	{
		m_pIUnknownOuter->Release();
		m_pIUnknownOuter = NULL;
	}
}

HRESULT __stdcall CAggregationCreateStructureAnimate::QueryInterface_NoAggregation(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<INoAggregationIUnknown*>(this);
	else if (riid == IID_IAggregationAnimation)
		*ppv = static_cast<IAggregationAnimation*>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();

	return(S_OK);
}

ULONG __stdcall CAggregationCreateStructureAnimate::AddRef_NoAggregation(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG __stdcall CAggregationCreateStructureAnimate::Release_NoAggregation(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete(this);
		return (0);
	}

	return(m_cRef);
}

HRESULT CAggregationCreateStructureAnimate::QueryInterface(REFIID riid, void** ppv)
{
	return(m_pIUnknownOuter->QueryInterface(riid, ppv));
}

ULONG CAggregationCreateStructureAnimate::AddRef(void)
{
	return(m_pIUnknownOuter->AddRef());
}

ULONG CAggregationCreateStructureAnimate::Release(void)
{
	return(m_pIUnknownOuter->Release());
}

HRESULT __stdcall CAggregationCreateStructureAnimate::Animate(HWND hWnd, HDC hdc, INT cxsize, INT cysize)
{
    DWORD dwPenStyle = PS_SOLID;
    COLORREF colPenColor = RGB(255, 255, 255);
    COLORREF colBlackPenColor = RGB(0, 0, 0);
    HPEN hPen = CreatePen(dwPenStyle, 5, colPenColor);
    HPEN hPen2 = CreatePen(dwPenStyle, 5, colBlackPenColor);
    HPEN hRedPen = CreatePen(dwPenStyle, 5, RGB(255, 0, 0));
    HPEN hBluePen = CreatePen(dwPenStyle, 5, RGB(0, 0, 255));

    TCHAR lpszString[256];

    RECT rcTitleRect = { 100, cysize - 150, cxsize - 100, cysize - 50 };
    HFONT hFont2 = CreateFont(80, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Impact"));

    SelectObject(hdc, hFont2);

    wsprintf(lpszString, TEXT("Aggregation"));
    DrawText(hdc, lpszString, -1, &rcTitleRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


    HPEN holdPen = (HPEN)SelectObject(hdc, hPen);

    HBRUSH hHighlightBrush = (HBRUSH)CreateSolidBrush(RGB(255, 158, 0));
    HBRUSH hDefaultBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));

    POINT ptIMultiplyInnerLine[] = { {cxsize / 2 - 300, cysize / 2 + 50},
                                    {cxsize / 2, cysize / 2 + 50} };

    POINT ptIDivisionInnerLine[] = { {cxsize / 2 - 300, cysize / 2 + 50 + 100},
                                    {cxsize / 2, cysize / 2 + 50 + 100} };

    POINT ptInnerIUnknownLine[] = { {cxsize / 2 + 75, cysize / 2},
                                     {cxsize / 2 + 75, cysize / 2 - 100} };

    POINT ptInnerNoAggregationIUnknownLine[] = { {cxsize / 2 + 225, cysize / 2},
                                                 {cxsize / 2 + 225, cysize / 2 - 100} };

    RECT rcInnerCoClassLayoutRect = { cxsize / 2 + 5, cysize / 2 + 30, cxsize / 2 + 300 - 5, cysize / 2 + 200 - 5 };
    RECT rcOuterCoClassLayoutRect1 = { cxsize / 2 - 300 + 5, cysize / 2 - 200 + 30, cxsize / 2 - 300 + 600 - 5, cysize / 2 };
    RECT rcOuterCoClassLayoutRect2 = { cxsize / 2 - 300 + 5, cysize / 2 - 200 + 30, cxsize / 2, cysize / 2 + 200 - 5 };

    /* Steps for Aggregation */
    Sleep(2000);

    /* Go to Outer IUnknown */
    SelectObject(hdc, hHighlightBrush);
    //Outer IUnknown
    Ellipse(hdc, cxsize / 2 - 175, cysize / 2 - 300, cxsize / 2 - 125, cysize / 2 - 350);

    Sleep(1000);

    /* Get the ISum*/
    SelectObject(hdc, hDefaultBrush);
    //Outer IUnknown
    Ellipse(hdc, cxsize / 2 - 175, cysize / 2 - 300, cxsize / 2 - 125, cysize / 2 - 350);
    SelectObject(hdc, hHighlightBrush);
    //ISum
    Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25, cxsize / 2 - 400, cysize / 2 - 200 + 75);

    Sleep(1000);

    /* Execute Outer Component */
    SelectObject(hdc, hDefaultBrush);
    //ISum
    Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25, cxsize / 2 - 400, cysize / 2 - 200 + 75);
    FillRect(hdc, &rcOuterCoClassLayoutRect1, hHighlightBrush);
    FillRect(hdc, &rcOuterCoClassLayoutRect2, hHighlightBrush);
    holdPen = (HPEN)SelectObject(hdc, hPen2);
    Polyline(hdc, ptIMultiplyInnerLine, 2);
    Polyline(hdc, ptIDivisionInnerLine, 2);
    Polyline(hdc, ptInnerIUnknownLine, 2);
    Polyline(hdc, ptInnerNoAggregationIUnknownLine, 2);
    //Inner IUnknown
    holdPen = (HPEN)SelectObject(hdc, hRedPen);
    Ellipse(hdc, cxsize / 2 + 50, cysize / 2 - 100, cxsize / 2 + 100, cysize / 2 - 150);
    //Inner NoAggregation IUnknown
    holdPen = (HPEN)SelectObject(hdc, hBluePen);
    Ellipse(hdc, cxsize / 2 + 200, cysize / 2 - 100, cxsize / 2 + 250, cysize / 2 - 150);
    holdPen = (HPEN)SelectObject(hdc, hPen);

    Sleep(1000);


    /* Release ISum */
    FillRect(hdc, &rcOuterCoClassLayoutRect1, hDefaultBrush);
    FillRect(hdc, &rcOuterCoClassLayoutRect2, hDefaultBrush);
    Polyline(hdc, ptIMultiplyInnerLine, 2);
    Polyline(hdc, ptIDivisionInnerLine, 2);
    Polyline(hdc, ptInnerIUnknownLine, 2);
    Polyline(hdc, ptInnerNoAggregationIUnknownLine, 2);
    //Inner IUnknown
    holdPen = (HPEN)SelectObject(hdc, hRedPen);
    Ellipse(hdc, cxsize / 2 + 50, cysize / 2 - 100, cxsize / 2 + 100, cysize / 2 - 150);
    //Inner NoAggregation IUnknown
    holdPen = (HPEN)SelectObject(hdc, hBluePen);
    Ellipse(hdc, cxsize / 2 + 200, cysize / 2 - 100, cxsize / 2 + 250, cysize / 2 - 150);
    holdPen = (HPEN)SelectObject(hdc, hPen);

    Sleep(1000);

    /* Go to Outer IUnknown */
    SelectObject(hdc, hHighlightBrush);
    //Outer IUnknown
    Ellipse(hdc, cxsize / 2 - 175, cysize / 2 - 300, cxsize / 2 - 125, cysize / 2 - 350);

    Sleep(1000);

    /* Get the ISubtract */
    SelectObject(hdc, hDefaultBrush);
    //Outer IUnknown
    Ellipse(hdc, cxsize / 2 - 175, cysize / 2 - 300, cxsize / 2 - 125, cysize / 2 - 350);
    SelectObject(hdc, hHighlightBrush);
    //ISubtract
    Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25 + 100, cxsize / 2 - 400, cysize / 2 - 200 + 75 + 100);

    Sleep(1000);


    /* Execute Outer Component */
    SelectObject(hdc, hDefaultBrush);
    //ISubtract
    Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25 + 100, cxsize / 2 - 400, cysize / 2 - 200 + 75 + 100);
    FillRect(hdc, &rcOuterCoClassLayoutRect1, hHighlightBrush);
    FillRect(hdc, &rcOuterCoClassLayoutRect2, hHighlightBrush);
    holdPen = (HPEN)SelectObject(hdc, hPen2);
    Polyline(hdc, ptIMultiplyInnerLine, 2);
    Polyline(hdc, ptIDivisionInnerLine, 2);
    Polyline(hdc, ptInnerIUnknownLine, 2);
    Polyline(hdc, ptInnerNoAggregationIUnknownLine, 2);
    //Inner IUnknown
    holdPen = (HPEN)SelectObject(hdc, hRedPen);
    Ellipse(hdc, cxsize / 2 + 50, cysize / 2 - 100, cxsize / 2 + 100, cysize / 2 - 150);
    //Inner NoAggregation IUnknown
    holdPen = (HPEN)SelectObject(hdc, hBluePen);
    Ellipse(hdc, cxsize / 2 + 200, cysize / 2 - 100, cxsize / 2 + 250, cysize / 2 - 150);

    holdPen = (HPEN)SelectObject(hdc, hPen);

    Sleep(1000);

    /* Release ISubtract */
    FillRect(hdc, &rcOuterCoClassLayoutRect1, hDefaultBrush);
    FillRect(hdc, &rcOuterCoClassLayoutRect2, hDefaultBrush);
    Polyline(hdc, ptIMultiplyInnerLine, 2);
    Polyline(hdc, ptIDivisionInnerLine, 2);
    Polyline(hdc, ptInnerIUnknownLine, 2);
    Polyline(hdc, ptInnerNoAggregationIUnknownLine, 2);
    //Inner IUnknown
    holdPen = (HPEN)SelectObject(hdc, hRedPen);
    Ellipse(hdc, cxsize / 2 + 50, cysize / 2 - 100, cxsize / 2 + 100, cysize / 2 - 150);
    //Inner NoAggregation IUnknown
    holdPen = (HPEN)SelectObject(hdc, hBluePen);
    Ellipse(hdc, cxsize / 2 + 200, cysize / 2 - 100, cxsize / 2 + 250, cysize / 2 - 150);
    holdPen = (HPEN)SelectObject(hdc, hPen);

    Sleep(1000);

    /* Go to Outer IUnknown */
    SelectObject(hdc, hHighlightBrush);
    //Outer IUnknown
    Ellipse(hdc, cxsize / 2 - 175, cysize / 2 - 300, cxsize / 2 - 125, cysize / 2 - 350);

    Sleep(1000);

    /* To to Inner NoAggregation_IUnknown */
    SelectObject(hdc, hDefaultBrush);
    //Outer IUnknown
    Ellipse(hdc, cxsize / 2 - 175, cysize / 2 - 300, cxsize / 2 - 125, cysize / 2 - 350);
    SelectObject(hdc, hHighlightBrush);
    //Inner NoAggregation IUnknown
    holdPen = (HPEN)SelectObject(hdc, hBluePen);
    Ellipse(hdc, cxsize / 2 + 200, cysize / 2 - 100, cxsize / 2 + 250, cysize / 2 - 150);

    Sleep(1000);

    /* Get the IMultiply */
    SelectObject(hdc, hDefaultBrush);
    //Inner NoAggregation IUnknown
    Ellipse(hdc, cxsize / 2 + 200, cysize / 2 - 100, cxsize / 2 + 250, cysize / 2 - 150);
    holdPen = (HPEN)SelectObject(hdc, hPen);
    SelectObject(hdc, hHighlightBrush);
    //IMultiply
    Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25 + 200, cxsize / 2 - 400, cysize / 2 - 200 + 75 + 200);

    Sleep(1000);

    /* Execute Inner Component */
    SelectObject(hdc, hDefaultBrush);
    //IMultiply
    Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25 + 200, cxsize / 2 - 400, cysize / 2 - 200 + 75 + 200);
    FillRect(hdc, &rcInnerCoClassLayoutRect, hHighlightBrush);

    Sleep(1000);

    /* Release IMultiply */
    FillRect(hdc, &rcInnerCoClassLayoutRect, hDefaultBrush);

    Sleep(1000);

    /* Go to Inner IUnknown */
    SelectObject(hdc, hHighlightBrush);
    //Inner IUnknown
    holdPen = (HPEN)SelectObject(hdc, hRedPen);
    Ellipse(hdc, cxsize / 2 + 50, cysize / 2 - 100, cxsize / 2 + 100, cysize / 2 - 150);
    Sleep(1000);

    /* Go to Outer IUnknown */
    SelectObject(hdc, hDefaultBrush);
    //Inner IUnknown
    Ellipse(hdc, cxsize / 2 + 50, cysize / 2 - 100, cxsize / 2 + 100, cysize / 2 - 150);
    holdPen = (HPEN)SelectObject(hdc, hPen);
    SelectObject(hdc, hHighlightBrush);
    //Outer IUnknown
    Ellipse(hdc, cxsize / 2 - 175, cysize / 2 - 300, cxsize / 2 - 125, cysize / 2 - 350);

    Sleep(1000);

    /* Go to Inner NoAggregation_IUnknown */
    SelectObject(hdc, hDefaultBrush);
    //Outer IUnknown
    Ellipse(hdc, cxsize / 2 - 175, cysize / 2 - 300, cxsize / 2 - 125, cysize / 2 - 350);
    SelectObject(hdc, hHighlightBrush);
    //Inner NoAggregation IUnknown
    holdPen = (HPEN)SelectObject(hdc, hBluePen);
    Ellipse(hdc, cxsize / 2 + 200, cysize / 2 - 100, cxsize / 2 + 250, cysize / 2 - 150);

    Sleep(1000);

    /* Get the IDivision */
    SelectObject(hdc, hDefaultBrush);
    //Inner NoAggregation IUnknown
    Ellipse(hdc, cxsize / 2 + 200, cysize / 2 - 100, cxsize / 2 + 250, cysize / 2 - 150);
    SelectObject(hdc, hHighlightBrush);
    holdPen = (HPEN)SelectObject(hdc, hPen);
    //IDivision
    Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25 + 300, cxsize / 2 - 400, cysize / 2 - 200 + 75 + 300);

    Sleep(1000);

    /* Execute the Inner Component */
    SelectObject(hdc, hDefaultBrush);
    //IDivision
    Ellipse(hdc, cxsize / 2 - 450, cysize / 2 - 200 + 25 + 300, cxsize / 2 - 400, cysize / 2 - 200 + 75 + 300);
    FillRect(hdc, &rcInnerCoClassLayoutRect, hHighlightBrush);

    Sleep(1000);

    /* Release IDivision */
    FillRect(hdc, &rcInnerCoClassLayoutRect, hDefaultBrush);

    Sleep(1000);

    DeleteObject(hHighlightBrush);
    DeleteObject(hDefaultBrush);
    DeleteObject(hPen);

    return (S_OK);
}

/*====================================================================================*/

/* Implementation of CSumSubtractClassFactory methods */

CAggregationCreateStructureAnimateClassFactory::CAggregationCreateStructureAnimateClassFactory(void)
{
	m_cRef = 1;
}

CAggregationCreateStructureAnimateClassFactory::~CAggregationCreateStructureAnimateClassFactory(void)
{
	// no code
}

HRESULT CAggregationCreateStructureAnimateClassFactory::QueryInterface(REFIID riid, void** ppv)
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

ULONG CAggregationCreateStructureAnimateClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);

	return (m_cRef);
}

ULONG CAggregationCreateStructureAnimateClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete (this);
		return (0);
	}

	return (m_cRef);
}

HRESULT CAggregationCreateStructureAnimateClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	CAggregationCreateStructureAnimate* pCAggregationCreateStructureAnimate = NULL;
	HRESULT hr = S_OK;

	if ((pUnkOuter != NULL) && (riid != IID_IUnknown))
		return(CLASS_E_NOAGGREGATION);

	pCAggregationCreateStructureAnimate = new CAggregationCreateStructureAnimate(pUnkOuter);

	if (pCAggregationCreateStructureAnimate == NULL)
		return (E_OUTOFMEMORY);

	hr = pCAggregationCreateStructureAnimate->QueryInterface_NoAggregation(riid, ppv);

	pCAggregationCreateStructureAnimate->Release_NoAggregation();
	return(hr);
}

HRESULT CAggregationCreateStructureAnimateClassFactory::LockServer(BOOL fLock)
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

	CAggregationCreateStructureAnimateClassFactory* pCAggregationCreateStructureAnimateClassFactory = NULL;
	HRESULT hr = S_OK;

	if (rclsid != CLSID_CAggregationCreateStructureAnimate)
		return(CLASS_E_CLASSNOTAVAILABLE);

	pCAggregationCreateStructureAnimateClassFactory = new CAggregationCreateStructureAnimateClassFactory;

	if (pCAggregationCreateStructureAnimateClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCAggregationCreateStructureAnimateClassFactory->QueryInterface(riid, ppv);
	pCAggregationCreateStructureAnimateClassFactory->Release();

	return (hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return (S_OK);
	else
		return (S_FALSE);
}