#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#define MYDEV_NAME "xxx_sample_chardev"
#define GPIOE_MODR 0x50006000
#define GPIOE_ODR 0x50006014
#define RCC_MP_AHB4_EN 0x50000a28 

struct resource my_device_001_res[] = {
    [0] = {
        .start = 0x50000a28,
        .end = 0x50000a28 + 0x4,
        .name = "rcc-reg",
        .flags = IORESOURCE_MEM,
        .desc = RCC_MP_AHB4_EN,
    },
    [1] = {
        .start = 0x50006000,
        .end = 0x50006000 + 0x4,
        .name = "gpioemode-reg",
        .flags = IORESOURCE_MEM,
        .desc = GPIOE_MODR,
    },
    [2] = {
        .start = 0x50006014,
        .end = 0x50006014 + 0x4,
        .name = "gpioeodr-reg",
        .flags = IORESOURCE_MEM,
        .desc = GPIOE_ODR,
    },
    [3] = {
        .start = 74,
        .end = 74,
        .flags = IORESOURCE_IRQ,
        .desc = 88
    }
};
//dev中的release方法：
void my_device_001_release(struct device *dev)
{

}
//定义一个平台设备:
struct platform_device my_platform_device = {
    .name = "WX,my_device_01",
    .id = -1,//自动分配，或者给-1;
    .resource = my_device_001_res,
    .num_resources = 4,
    .dev = {
        .release = my_device_001_release,
    }
};

//入口函数：
int __init my_test_module_init(void)
{
    int ret = 0;
    //注册：
    ret = platform_device_register(&my_platform_device);
    if(ret < 0)
    {
        return -1;
    }
    return 0;
}

//出口函数：
void __exit my_test_module_exit(void)
{
    //注销：
    platform_device_unregister(&my_platform_device);
}

//指定许可：
MODULE_LICENSE("GPL");
MODULE_AUTHOR("wangzihao, email:wangzihao@163.com");
//指定入口及出口函数：
module_init(my_test_module_init);
module_exit(my_test_module_exit);
