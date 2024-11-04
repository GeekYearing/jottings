# Driver for Linux

### 简介

驱动程序是上层软件与底层硬件打交道的桥梁，用于决定底层硬件的工作方式并协调到操作系统中，通常情况实现驱动只需要处理以下工作内容：

* 读写设备寄存器
* 处理硬件事件请求（中断）
* 实现实际硬件地址到虚拟地址的寻址

在 Linux 操作系统中开发驱动本质上就是实现一系列接口，并将驱动编译好动态加载到操作系统中启动即可。在 Linux 中万物皆文件，所以驱动完成注册后会以文件的形式呈现，可以通过读写文件的方式使用驱动实现的功能。在 Linux2.6 之后，Linux 引入了设备树的概念，设备树本质上就是为设备驱动提供的初始化配置文件，便于实现更为通用的驱动程序。

### 简单驱动实现

一般来说，驱动开发的大致流程如下：

* 通过原理图和数据手册查看硬件地址等相关定义。
* 创建驱动模块工程，实现对应的 open/close/read/write 等操作函数，如果有需要还可以实现中断服务。
* 编译模块，并使用 insmod 命令加载到内核。

以下是使用 Rockpi 4B 实现 hello 驱动的案例，它将在模块加载和卸载内核时进行打印，其中 MODULE_LICENSE 用于声明模块的许可证：

```c
#include <linux/module.h>
#include <linux/init.h>

static int __init hello_init (void) {
  printk("Hello module init\n");
  return 0; 
} 

static void __exit hello_exit (void) {
  printk("Hello module exit\n");
} 

module_init(hello_init); 
module_exit(hello_exit);

MODULE_LICENSE("GPL"); 
```

对应的编译脚本如下，这里的 KERNELDIR 属性用于定义内核文件的位置，-C 参数表示切换到内核工作路径下执行编译：

```makefile
CC = gcc-8
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

obj-m := hello.o
all:
  $(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
  $(MAKE) -C $(KERNELDIR) M=$(PWD) clean
```

程序编译完成后，就能够通过 insmod 命令将模块加载到内核中运行：

```bash
$ insmod hello.ko   # 加载模块
$ lsmod             # 列出模块
Module                  Size  Used by
hello                  16384  0
....
$ modinfo hello.ko  # 模块信息
filename:       /root/project/hello_world/hello.ko
license:        GPL
depends:        
vermagic:       4.4.154-116-rockchip-g86a614bc15b3 SMP mod_unload aarch64
$ rmmod hello.ko    # 卸载模块
$ dmesg             # 显示调试打印
[45328.344480] hello: loading out-of-tree module taints kernel.
[45328.345203] Hello module init
[45642.829343] Hello module exit
```

### 设备注册

在Linux中一切皆文件，所以硬件设备也是以文件的形式呈现，通常根据硬件的特性将对应的设备文件分为以下三类：

* 字符设备（char device），它的读写以字节为单位，例如串口驱动，能够按字节流的方式收发数据。
* 块设备（block device），通过传输固定大小的数据来访问设备，支持随机存取，例如FLASH的数据就是以页为单位存放的。
* 网络设备（net device），它是一种特殊的类型，包含字符设备和块设备的全部特点，但在文件系统中不存在对应的节点，通过配合 socket 相关函数进行使用，例如网卡设备和蓝牙设备。

接下来将在 hello 案例代码中实现字符设备，字符设备需要在驱动程序中进行注册/销毁，以下是设备注册相关函数原型：

```c
static inline int register_chrdev(unsigned int major, const char* name, const struct file_operations* fops);
static inline void unregister_chrdev(unsigned int major, const char* name);
```

可以注意到，设备的注册需要指定主设备号（major）来唯一标识该设备对象，可以使用 cat /proc/devices 命令查看当前设备号的占用情况来选择当前未被使用的设备号进行注册，但使用以上方式会一次性将后面的子设备号全部占用，对此Linux提供了以下接口用于获取当前未被使用的设备号：

```c
/* 动态申请设备号(需要给定次设备号起始地址) */
int alloc_chrdev_region(dev_t* dev, unsigned baseminor, unsigned count, const char* name);

/* 静态申请设备号(仍由驱动程序指定设备号） */
int register_chrdev_region(dev_t from, unsigned count, const char* name);
void unregister_chrdev_region(dev_t from, unsigned count);
```

通过以上接口声明不难得知，申请后的设备号由 dev_t 结构体进行存储，设备号获取完成后，就可以配合以下接口实现对字符设备的相关操作：

```c
void cdev_init(struct cdev* cdev, const struct file_operations* fops);
int cdev_add(struct cdev* p, dev_t dev, unsigned count);
void cdev_del(struct cdev* p);
```

以上接口的使用案例如下：

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/cdev.h>

static struct file_operations s_hello_file_operation = {
    .owner = THIS_MODULE,
};

static struct cdev s_hello_dev = {
    .owner = THIS_MODULE,
};

static int __init hello_init(void)
{
  printk("Hello module init\n");

  alloc_chrdev_region(&s_hello_dev.dev, 0, 1, "hello_cdev");

  cdev_init(&s_hello_dev, &s_hello_file_operation);
  cdev_add(&s_hello_dev, s_hello_dev.dev, s_hello_dev.count);

  return 0;
}

static void __exit hello_exit(void)
{
  cdev_del(&s_hello_dev);
  unregister_chrdev_region(s_hello_dev.dev, s_hello_dev.count);

  printk("Hello module exit\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
```

以上代码在 Linux 内核中注册了一个简单的字符设备：

```bash
$ cat /proc/devices
...
Character devices:
238 hello_cdev
...
```

但是这个设备还无法通过文件操作与用户程序完成交互，如果希望设备能够被应用程序访问，还需要为设备创建设备节点对象。为此 Linux 提供了 mknod 命令用来手动创建设备节点，当然也能够通过以下接口在代码中实现自动创建:

```c
struct class* class_create(struct module* owner, const char* name);
void class_destroy(struct class* cls);

struct device* device_create(struct class* class, struct device* parent, dev_t devt, void* drvdata, const char* fmt, ...);
void device_destroy(struct class* class, dev_t devt);
```

从以上代码来看，设备节点本质上是一个由具体化的类对象，通过设备号与具体设备进行绑定，本质上就是创建一个文件，所以提供了 fmt 参数用于设置文件名称，具体的使用方式如下：

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/cdev.h>

static struct class* s_hello_class = NULL;
static struct device* s_hello_device = NULL;

static struct file_operations s_hello_file_operation = {
    .owner = THIS_MODULE,
};

static struct cdev s_hello_dev = {
    .owner = THIS_MODULE,
};

static int __init hello_init(void)
{
  printk("Hello module init\n");

  alloc_chrdev_region(&s_hello_dev.dev, 0, 1, "hello_cdev");

  cdev_init(&s_hello_dev, &s_hello_file_operation);
  cdev_add(&s_hello_dev, s_hello_dev.dev, 1);

  s_hello_class = class_create(THIS_MODULE, "hello_device");
  s_hello_device = device_create(s_hello_class, NULL, s_hello_dev.dev, NULL, "hello_device");

  return 0;
}

static void __exit hello_exit(void)
{
  cdev_del(&s_hello_dev);
  unregister_chrdev_region(s_hello_dev.dev, 1);
  device_destroy(s_hello_class, s_hello_dev.dev);
  class_destroy(s_hello_class);

  printk("Hello module exit\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
```

### IO驱动实现



