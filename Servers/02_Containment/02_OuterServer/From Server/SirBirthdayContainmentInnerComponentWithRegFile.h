#pragma once

class IContainmentAnimation : public IUnknown
{
    public:
        virtual HRESULT __stdcall Animate(HWND, HDC, INT, INT) = 0;
};

// CLSID of CContainmentCreateStructureAnimate Component {982E93C9-456D-4553-A125-C663B03C3391}
const CLSID CLSID_CContainmentCreateStructureAnimate = { 0x982e93c9, 0x456d, 0x4553, 0xa1, 0x25, 0xc6, 0x63, 0xb0, 0x3c, 0x33, 0x91 };

// IID of  IContainmentAnimation Interface {66E568F8-F342-4917-91F0-25F7FECA39C5}
const IID IID_IContainmentAnimation = { 0x66e568f8, 0xf342, 0x4917, 0x91, 0xf0, 0x25, 0xf7, 0xfe, 0xca, 0x39, 0xc5 };

/*
// {982E93C9-456D-4553-A125-C663B03C3391}
DEFINE_GUID(<<name>>,
0x982e93c9, 0x456d, 0x4553, 0xa1, 0x25, 0xc6, 0x63, 0xb0, 0x3c, 0x33, 0x91);



// {66E568F8-F342-4917-91F0-25F7FECA39C5}
DEFINE_GUID(<<name>>,
0x66e568f8, 0xf342, 0x4917, 0x91, 0xf0, 0x25, 0xf7, 0xfe, 0xca, 0x39, 0xc5);


*/

