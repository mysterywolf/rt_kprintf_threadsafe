Import('rtconfig')
from building import *

cwd = GetCurrentDir()
src	= Glob('*.c')
CPPPATH = [cwd]

group = DefineGroup('Kernel', src, depend = ['PKG_USING_RT_KPRINTF_THREADSAFE'], CPPPATH = CPPPATH)

Return('group')
