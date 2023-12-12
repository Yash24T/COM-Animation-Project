#pragma once

class IAggregationAnimation : public IUnknown
{
    public:
        virtual HRESULT __stdcall Animate(HWND, HDC, INT, INT) = 0;
};

// CLSID of CAggregationCreateStructureAnimate Component {F05B2F1D-E4F8-4790-94C4-1064F062427A}
const CLSID CLSID_CAggregationCreateStructureAnimate = { 0xf05b2f1d, 0xe4f8, 0x4790, 0x94, 0xc4, 0x10, 0x64, 0xf0, 0x62, 0x42, 0x7a };

// IID of IAggregationAnimation Interface {EF4EE756-A314-4263-AEC8-F74EDC3C5D44}
const IID IID_IAggregationAnimation = { 0xef4ee756, 0xa314, 0x4263, 0xae, 0xc8, 0xf7, 0x4e, 0xdc, 0x3c, 0x5d, 0x44 };

/*

// {F05B2F1D-E4F8-4790-94C4-1064F062427A}
DEFINE_GUID(<<name>>,
0xf05b2f1d, 0xe4f8, 0x4790, 0x94, 0xc4, 0x10, 0x64, 0xf0, 0x62, 0x42, 0x7a);

// {EF4EE756-A314-4263-AEC8-F74EDC3C5D44}
DEFINE_GUID(<<name>>,
0xef4ee756, 0xa314, 0x4263, 0xae, 0xc8, 0xf7, 0x4e, 0xdc, 0x3c, 0x5d, 0x44);

*/