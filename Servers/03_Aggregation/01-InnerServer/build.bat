del *.exp
del *.dll
del *.lib
del *.obj

cls

cl /EHsc /c SirBirthdayAggregationInnerComponentWithRegFile.cpp

link.exe SirBirthdayAggregationInnerComponentWithRegFile.obj /DLL /DEF:SirBirthdayAggregationInnerComponentWithRegFile.def Ole32.lib User32.lib Kernel32.lib Gdi32.lib 
