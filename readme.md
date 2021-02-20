# 线程安全版本的`rt_kprintf()`

原版RT-Thread `kserver.c `文件中的`rt_kprintf()`函数是线程不安全的，如果同时有两个线程同时使用`rt_kprintf()`打印数据，可能会导致数据被冲刷掉或者一方的信息根本没有打印出来等一系列奇奇怪怪的问题。比如：https://club.rt-thread.org/ask/question/429525.html

RT-Thread官方清楚非线程安全所带来的后果，但是为了确保`rt_kprintf()`函数与标准C库的`printf`函数标准一致以及足够精炼有意而为之。

本安全版本`rt_kprintf()`函数会自动判断当前所处环境：

1. 若RT-Thread尚未启动调度器，则采用没有任何保护的方式；

2. 若在中断中调用`rt_kprintf()`，则采用没有任何保护的方式；

3. 若在线程中调用`rt_kprintf()`，方可采用线程安全保护措施。

   1) 若RT-Thread启用互斥量则使用互斥量保护；

   2) 若RT-Thread没有启用互斥量则退而求其次使用信号量保护；

   3) 若RT-Thread连信号量都没有启用，则采用关调度器的方式进行保护。

总之，线程安全版本`rt_kprintf()`函数会和原版函数一样可以在任何环境下调用，不会受到影响，使用时和原版`rt_kprintf`无任何区别，用户无感。**无需屏蔽原版`rt_kprintf`**，因为原版`rt_kprintf`为弱函数，本软件包会自动覆盖原版`rt_kprintf`。


## 适用版本
4.0.4 版本以上


## 如何添加该软件包

```
RT-Thread online packages
    system packages --->
        [*] rt_kprintf_threadsafe: thread-safe version of rt_kprintf --->
                Version (latest)  --->
```




## 维护

Meco Man

jiantingman@foxmail.com
