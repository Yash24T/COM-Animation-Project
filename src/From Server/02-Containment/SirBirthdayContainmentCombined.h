#pragma once

class IContainmentCreateStructure : public IUnknown
{
public:
    virtual HRESULT __stdcall CreateStructure(HWND, HDC, INT, INT) = 0;
};

class IContainmentAnimation : public IUnknown
{
public:
    virtual HRESULT __stdcall Animate(HWND, HDC, INT, INT) = 0;
};

// CLSID of CContainmentOuterCreateStructureAnimate Component {C06D4268-D708-43EA-8814-98645EDC9002}
const CLSID CLSID_CContainmentOuterCreateStructureAnimate = { 0xc06d4268, 0xd708, 0x43ea, 0x88, 0x14, 0x98, 0x64, 0x5e, 0xdc, 0x90, 0x2 };

// IID of IContainmentCreateStructure Interface {67C5D388-40D2-4A59-851C-FC498F468B1C}
const IID IID_IContainmentCreateStructure = { 0x67c5d388, 0x40d2, 0x4a59, 0x85, 0x1c, 0xfc, 0x49, 0x8f, 0x46, 0x8b, 0x1c };

// IID of  IContainmentAnimation Interface {66E568F8-F342-4917-91F0-25F7FECA39C5}
const IID IID_IContainmentAnimation = { 0x66e568f8, 0xf342, 0x4917, 0x91, 0xf0, 0x25, 0xf7, 0xfe, 0xca, 0x39, 0xc5 };