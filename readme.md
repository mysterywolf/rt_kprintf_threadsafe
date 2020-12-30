# `rt_printf()`函数 -- 线程安全版本的`rt_kprintf()`

原版RT-Thread `kserver.c `文件中的`rt_kprintf()`函数是线程不安全的，如果同时有两个线程同时使用`rt_kprintf()`打印数据，可能会导致数据被冲刷掉或者一方的信息根本没有打印出来等一系列奇奇怪怪的问题。比如：https://club.rt-thread.org/ask/question/429525.html

RT-Thread官方清楚非线程安全所带来的后果，但是为了确保`rt_kprintf()`函数足够精炼有意而为之。

本安全版本`rt_printf()`函数会自动判断当前所处环境：

1. 若RT-Thread尚未启动调度器，则采用没有任何保护的方式；

2. 若在中断中调用`rt_printf()`，则采用没有任何保护的方式；

3. 若在线程中调用`rt_printf()`，方可采用线程安全保护措施。

   1) 若RT-Thread启用互斥量则使用互斥量保护；

   2) 若RT-Thread没有启用互斥量则退而求其次使用信号量保护；

   3) 若RT-Thread连信号量都没有启用，则采用关调度器的方式进行保护。
   
4. 本函数支持浮点输出（原版`rt_kprintf()`不支持）

总之，`rt_printf()`函数会和原版函数一样可以在任何环境下调用，不会受到影响。

