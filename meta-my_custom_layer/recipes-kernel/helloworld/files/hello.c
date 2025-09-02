/******************************************************************************
 Author: 
 Soyabbir Abu Hanif
 Custom loadable kernel module (LKM) that will greets when loading and unloading
 Supports a load-time parameter to personalize the default greetings 
 
 *****************************************************************************/

#include <linux/module.h> //loading lkm into the kernel
#include <linux/kernel.h> //for types macros, functions for kernel
#include <linux/init.h> //module initialization and cleanup macros

MODULE_LICENSE("GPL");
MODULE_AUTHOR ("Soyabbir Abu Hanif");
MODULE_DESCRIPTION ("A simple kernel module that greets on load and unload with a personalized parameter");
MODULE_VERSION ("0.1");

static char *name = "Hello World";
module_param(name, charp, 0444); // 0444 is the permission value for read-only
MODULE_PARM_DESC(name, "The name to display in /var/log/kern.log");

static int __init hello_init(void) {
    printk(KERN_INFO "Hello: Welcome %s to the Hello LKM\n", name);
    return 0;
}

static void __exit hello_exit(void) {
    printk(KERN_INFO "Goodbye %s from the Hello LKM\n", name);
}

module_init(hello_init);
module_exit(hello_exit);


