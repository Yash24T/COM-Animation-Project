del *.exp
del *.dll
del *.lib
del *.obj

cl /EHsc /c SirBirthdayContainmentOuterComponentWithRegFile.cpp

link.exe SirBirthdayContainmentOuterComponentWithRegFile.obj /DLL /DEF:SirBirthdayContainmentOuterComponentWithRegFile.def User32.lib Kernel32.lib Gdi32.lib Ole32.lib