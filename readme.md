# rt_kprintf 线程安全版本

原版RT-Thread `kserver.c `文件中的`rt_kprintf()`函数是线程不安全的，如果同时有两个线程同时使用`rt_kprintf()`打印数据，可能会导致数据被冲刷掉或者一方的信息根本没有打印出来等一系列奇奇怪怪的问题。

如果需要`rt_kprintf()`线程安全版本，请使用本代码替换掉RT-Thread原`rt_kprintf()`函数。

