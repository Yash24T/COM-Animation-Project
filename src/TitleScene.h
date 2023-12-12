#pragma once

#define FLAME_LOOPS(bmpName, X, Y, uDec)  for (UINT col = bmpName.GetHeight(); col > 0; col--)\
                                    {\
                                        for (UINT row = 0; row <= bmpName.GetWidth(); row++)\
                                        {\
                                            bmpName.GetPixel(row, col, &pixelColor);\
                                            colorRef = pixelColor.ToCOLORREF();\
                                            if (GetRValue(colorRef) == 0 || GetGValue(colorRef) == 0 || GetBValue(colorRef) == 0)\
                                                continue;\
                                            if (GetRValue(colorRef) > 240 || GetGValue(colorRef) > 240 || GetBValue(colorRef) > 240)\
                                                colorRef = (RGB(GetRValue(colorRef) -  uDec, GetGValue(colorRef) -  uDec, GetBValue(colorRef) -  uDec));\
                                            SetPixel(hdc, row + X, col + Y, colorRef);\
                                        }\
                                    }

/* Coordinates for Diya */
#define COORDINATE_DIYA_X   (cxsize / 2 - (diya.GetWidth()) / 2)
#define COORDINATE_DIYA_Y   (cysize - (diya.GetHeight()) - 100 )

#define COORDINATE_TITLE_ASTROMEDICOMP  200
#define DIYA_SLEEP_TIME                 1000
#define TITLE_ASTROMEDICOMP_SLEEP_TIME  2000

/* Function declaration */
void ShowCentralFlame(HDC hdc);
void ShowLeftFlame(HDC hdc);
void ShowRightFlame(HDC hdc);
void ShowTextAstroMediComp(HDC hdc);
void ShowCreditScene(HDC hdc);
void ShowStartScene(HDC hdc);

/* Thread Procs for Title Scene */
DWORD WINAPI ThreadProcCentralFlame(LPVOID);
DWORD WINAPI ThreadProcLeftFlame(LPVOID lpParam);
DWORD WINAPI ThreadProcRightFlame(LPVOID lpParam);
DWORD WINAPI ThreadProcTextAstroMediComp(LPVOID lpParam);
DWORD WINAPI ThreadProcCreditScene(LPVOID lpParam);
DWORD WINAPI ThreadProcStartScene(LPVOID lpParam);