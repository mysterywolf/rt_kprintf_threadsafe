/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-15     Meco Man    first version
 */

#include <rtthread.h>
#include <rthw.h>

#ifdef RT_USING_CONSOLE
/**
 * This function will print a formatted string on system console (thread safe)
 *
 * @param fmt the format
 */
void rt_kprintf(const char *fmt, ...)
{
    va_list args;
    rt_size_t length;
    rt_device_t console_dev;
    static char rt_log_buf[RT_CONSOLEBUF_SIZE];

#ifdef RT_USING_MUTEX
    static unsigned char kprintf_init_flag = RT_FALSE;
    static struct rt_mutex kprintf_mutex;

    if(rt_interrupt_get_nest() == 0u && rt_thread_self() != RT_NULL)
    {
        if(kprintf_init_flag == RT_FALSE)
        {
            rt_mutex_init(&kprintf_mutex, "kprintf", RT_IPC_FLAG_FIFO);
            kprintf_init_flag = RT_TRUE;
        }
        rt_mutex_take(&kprintf_mutex, RT_WAITING_FOREVER);
    }
#endif

    console_dev = rt_console_get_device();
    
    va_start(args, fmt);
    /* the return value of vsnprintf is the number of bytes that would be
     * written to buffer had if the size of the buffer been sufficiently
     * large excluding the terminating null byte. If the output string
     * would be larger than the rt_log_buf, we have to adjust the output
     * length. */
    length = rt_vsnprintf(rt_log_buf, sizeof(rt_log_buf) - 1, fmt, args);
    if (length > RT_CONSOLEBUF_SIZE - 1)
        length = RT_CONSOLEBUF_SIZE - 1;
#ifdef RT_USING_DEVICE
    if (console_dev == RT_NULL)
    {
        rt_hw_console_output(rt_log_buf);
    }
    else
    {
        rt_uint16_t old_flag = console_dev->open_flag;

        console_dev->open_flag |= RT_DEVICE_FLAG_STREAM;
        rt_device_write(console_dev, 0, rt_log_buf, length);
        console_dev->open_flag = old_flag;
    }
#else
    rt_hw_console_output(rt_log_buf);
#endif
    va_end(args);

#ifdef RT_USING_MUTEX
    if(rt_interrupt_get_nest() == 0u && rt_thread_self() != RT_NULL && kprintf_init_flag == RT_TRUE)
    {
        rt_mutex_release(&kprintf_mutex);
    }
#endif
}
#endif
