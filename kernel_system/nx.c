#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/highmem.h>

static int __init nx_init(void) {
    unsigned long addr;
    for (addr = 0; addr < max_pfn << PAGE_SHIFT; addr += PAGE_SIZE) {
        set_memory_nx(addr, 1);
    }
    return 0;
}

static void __exit nx_exit(void) {}

module_init(nx_init);
module_exit(nx_exit);
MODULE_LICENSE("GPL"); 