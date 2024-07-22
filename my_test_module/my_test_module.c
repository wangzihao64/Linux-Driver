#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
//描述一个字符设备：应该有哪些属性：
//1.设备名称，2.设备号：主设备好，次设备号，3.对设备进行操作的结构体struct file_operations
#define MYDEV_NAME "xxx_sample_chardev"
//入口函数：
struct xxx_sample_chardev
{
    const char* dev_name;
    int major;
    int minor;
    struct file_operations fops;
};
//1.在全局中定义的 xxx_sample_charde的对象
struct xxx_sample_chardev my_chrdev;

//在内核定义对应的函数接口：
//与文件read对应的函数指针
ssize_t xxx_sample_chardev_read (struct file * file, char __user *userbuf, size_t size, loff_t * offset)
{
    printk("内核中的xxx_sample_chardev_read执行了\n");
    return size;
}
//与write对应的函数指针
ssize_t xxx_sample_chardev_write (struct file *file, const char __user *usrbuf, size_t size, loff_t *offset)
{
    printk("内核中的xxx_sample_chardev_write执行了\n");
    return size;
}

//与open对应的函数指针
int xxx_sample_chardev_open (struct inode *inode, struct file *file)
{
    printk("内核中的xxx_sample_chardev_open执行了\n");
    return 0;
}
//与close对应函数指针：
int xxx_sample_chardev_release (struct inode *inode, struct file *file)
{
    printk("内核中的xxx_sample_chardev_release执行了\n");
    return 0;
}
int __init my_test_module_init(void)
{
    printk("入口函数执行了\n");
    //申请资源，初始化并配置资源。
    //2.初始化对象（对这个设备对象中的属性进行初始化）
    //2.1设备的名字：
    my_chrdev.dev_name = MYDEV_NAME;
    //2.2设备操作时的回调方法：
    my_chrdev.fops.open = xxx_sample_chardev_open;
    my_chrdev.fops.read = xxx_sample_chardev_read;
    my_chrdev.fops.write = xxx_sample_chardev_write;
    my_chrdev.fops.release = xxx_sample_chardev_release;
    //2.3 申请内核中的设备号：申请主设备号，并且关联对此设备的操作方法：
    my_chrdev.major = register_chrdev(0,MYDEV_NAME,&my_chrdev.fops);
    if(my_chrdev.major < 0)
    {
        printk("申请设备号失败，及关联操作方法失败\n");
        return my_chrdev.major;
    }
    printk("申请到的设备号=%d\n",my_chrdev.major);
    return 0;
}


//出口函数：
void __exit my_test_module_exit(void)
{
    printk("出口口函数执行了\n");//把调试信息放在了日志文件
    //清理资源。
    unregister_chrdev(my_chrdev.major,MYDEV_NAME);
}


//指定许可：
MODULE_LICENSE("GPL");
MODULE_AUTHOR("wangzihao, email:w185892713@163.com");
//指定入口及出口函数：
module_init(my_test_module_init);
module_exit(my_test_module_exit);
