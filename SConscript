Import('rtconfig')
from building import *

cwd = GetCurrentDir()
src	= Glob('*.c')
CPPPATH = [cwd]

group = DefineGroup('rt_printf', src, depend = ['PKG_USING_RT_PRINTF'], CPPPATH = CPPPATH)

Return('group')
