#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>

int my_dev_driver_probe(struct platform_device * my_platform_dev)
{
    printk("my_dev_driver_probe函数执行了\n");
    return 0;
}

int my_dev_driver_remove(struct platform_device *my_platform_dev)
{
    printk("my_dev_driver_remover函数执行了\n");
    return 0;
}

//1.定义一个平台驱动对象：
struct platform_driver my_platform_driver = {
    .probe = my_dev_driver_probe,
    .remove = my_dev_driver_remove,
    .driver = {
        .name = "gaowanxi,my_device_001",
    },
};

//入口函数：
int __init my_test_module_init(void)
{
    int ret = 0;
    ret = platform_driver_register(&my_platform_driver);
    if(ret < 0)
    {
        return -1;
    }
    return 0;
}

//出口函数：
void __exit my_test_module_exit(void)
{
    platform_driver_unregister(&my_platform_driver);
}

//指定许可：
MODULE_LICENSE("GPL");
MODULE_AUTHOR("wangzihao, email:wangzihao@163.com");
//指定入口及出口函数：
module_init(my_test_module_init);
module_exit(my_test_module_exit);
