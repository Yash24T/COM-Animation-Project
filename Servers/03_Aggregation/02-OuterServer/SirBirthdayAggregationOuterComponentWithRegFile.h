#pragma once

class IAggregationCreateStructure : public IUnknown
{
    public:
        virtual HRESULT __stdcall CreateStructure(HWND, HDC, INT, INT) = 0;
};

// CLSID of CAggregationOuterCreateStructureAnimate Component {92832CC9-0CD0-40F6-AA3A-E1494CB1E671}
const CLSID CLSID_CAggregationOuterCreateStructureAnimate = { 0x92832cc9, 0xcd0, 0x40f6, 0xaa, 0x3a, 0xe1, 0x49, 0x4c, 0xb1, 0xe6, 0x71 };

// IID of IAggregationCreateStructure Interface {2AADB414-5AC2-4163-8D8C-0B219A99EFD0}
const IID IID_IAggregationCreateStructure = { 0x2aadb414, 0x5ac2, 0x4163, 0x8d, 0x8c, 0xb, 0x21, 0x9a, 0x99, 0xef, 0xd0 };

/*
// {92832CC9-0CD0-40F6-AA3A-E1494CB1E671}
DEFINE_GUID(<<name>>,
0x92832cc9, 0xcd0, 0x40f6, 0xaa, 0x3a, 0xe1, 0x49, 0x4c, 0xb1, 0xe6, 0x71);

// {2AADB414-5AC2-4163-8D8C-0B219A99EFD0}
DEFINE_GUID(<<name>>,
0x2aadb414, 0x5ac2, 0x4163, 0x8d, 0x8c, 0xb, 0x21, 0x9a, 0x99, 0xef, 0xd0);

*/