del *.exp
del *.obj
del *.dll
del *.lib

cl /c /EHsc SirBirthdayContainmentInnerComponentWithRegFile.cpp
link.exe SirBirthdayContainmentInnerComponentWithRegFile.obj /DLL /DEF:SirBirthdayContainmentInnerComponentWithRegFile.def User32.lib Kernel32.lib Gdi32.lib