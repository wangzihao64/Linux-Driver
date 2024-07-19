#include <linux/module.h>
#include <linux/init.h>

//入口函数：
int __init my_test_module_init(void)
{
    printk("入口函数执行了\n");
    //申请资源，初始化并配置资源。
    return 0;
}


//出口函数：
void __exit my_test_module_exit(void)
{
    printk("出口口函数执行了\n");//把调试信息放在了日志文件
    //清理资源。
}


//指定许可：
MODULE_LICENSE("GPL");
MODULE_AUTHOR("wangzihao, email:w185892713@163.com");
//指定入口及出口函数：
module_init(my_test_module_init);
module_exit(my_test_module_exit);
