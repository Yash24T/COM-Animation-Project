del *.dll
del *.obj
del *.exp
del *.lib

cl /c /EHsc SirBirthdayClassFactoryDllServerWithRegFile.cpp

link.exe SirBirthdayClassFactoryDllServerWithRegFile.obj /DLL /DEF:SirBirthdayClassFactoryDllServerWithRegFile.def User32.lib Gdi32.lib Kernel32.lib