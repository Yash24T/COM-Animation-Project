cls

del *.dll
del *.exp
del *.lib
del *.obj

cls

cl /EHsc /c SirBirthdayAggregationOuterComponentWithRegFile.cpp

link.exe SirBirthdayAggregationOuterComponentWithRegFile.obj /DLL /DEF:SirBirthdayAggregationOuterComponentWithRegFile.def User32.lib Ole32.lib Kernel32.lib Gdi32.lib