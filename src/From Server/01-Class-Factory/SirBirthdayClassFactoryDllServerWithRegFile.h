#pragma once

class IClassFactoryCreateStruture : public IUnknown
{
    public:
        virtual HRESULT __stdcall CreateStructure(HWND, HDC, INT, INT) = 0;
};

class IClassFactoryAnimate : public IUnknown
{
    public:
        virtual HRESULT __stdcall Animate(HWND, HDC, INT, INT) = 0;
};

// CLSID of SumSubtract Component {9133D8EE-6C0D-4A2D-B14E-6D2E57FE669A}
const CLSID CLSID_CClassFcatoryCreateStructureAnimate = { 0x9133d8ee, 0x6c0d, 0x4a2d, 0xb1, 0x4e, 0x6d, 0x2e, 0x57, 0xfe, 0x66, 0x9a };

// IID of ISum Interface {E2F1C315-7C5D-4AB7-8A6E-7475A7583068}
const IID IID_IClassFactoryCreateStruture = { 0xe2f1c315, 0x7c5d, 0x4ab7, 0x8a, 0x6e, 0x74, 0x75, 0xa7, 0x58, 0x30, 0x68 };

// IID of ISubtract Interface {A7CFA794-453A-404E-8810-5DCCA251F562}
const IID IID_IClassFactoryAnimate = { 0xa7cfa794, 0x453a, 0x404e, 0x88, 0x10, 0x5d, 0xcc, 0xa2, 0x51, 0xf5, 0x62 };

/*

// {9133D8EE-6C0D-4A2D-B14E-6D2E57FE669A}
DEFINE_GUID(<<name>>,
0x9133d8ee, 0x6c0d, 0x4a2d, 0xb1, 0x4e, 0x6d, 0x2e, 0x57, 0xfe, 0x66, 0x9a);

// {E2F1C315-7C5D-4AB7-8A6E-7475A7583068}
DEFINE_GUID(<<name>>,
0xe2f1c315, 0x7c5d, 0x4ab7, 0x8a, 0x6e, 0x74, 0x75, 0xa7, 0x58, 0x30, 0x68);

// {A7CFA794-453A-404E-8810-5DCCA251F562}
DEFINE_GUID(<<name>>,
0xa7cfa794, 0x453a, 0x404e, 0x88, 0x10, 0x5d, 0xcc, 0xa2, 0x51, 0xf5, 0x62);


*/