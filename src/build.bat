cls

del *.exe
del *.res
del *.obj

cl.exe /EHsc /c .\Window.cpp

rc.exe .\Window.rc

link.exe .\Window.obj User32.lib Kernel32.lib Gdi32.lib Gdiplus.lib Winmm.lib Ole32.lib .\Window.res

Window.exe
