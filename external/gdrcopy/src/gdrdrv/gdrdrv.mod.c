#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/compiler.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module __section(".gnu.linkonce.this_module") = {
    .name = KBUILD_MODNAME,
    .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
    .exit = cleanup_module,
#endif
    .arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const char ____versions[] __used
    __section("__versions") = "\x1c\x00\x00\x00\xa2\xb0\x96\xa4"
                              "__register_chrdev\0\0\0"
                              "\x1c\x00\x00\x00\xc0\xfb\xc3\x6b"
                              "__unregister_chrdev\0"
                              "\x18\x00\x00\x00\x31\xf4\xf0\xca"
                              "kmalloc_caches\0\0"
                              "\x18\x00\x00\x00\x59\x4c\x17\xb1"
                              "kmalloc_trace\0\0\0"
                              "\x18\x00\x00\x00\x9f\x0c\xfb\xce"
                              "__mutex_init\0\0\0\0"
                              "\x14\x00\x00\x00\xd2\xf1\xd0\x5d"
                              "pcpu_hot\0\0\0\0"
                              "\x20\x00\x00\x00\x7c\xdf\x4d\x24"
                              "address_space_init_once\0"
                              "\x14\x00\x00\x00\x4b\x8d\xfa\x4d"
                              "mutex_lock\0\0"
                              "\x18\x00\x00\x00\x38\xf0\x13\x32"
                              "mutex_unlock\0\0\0\0"
                              "\x14\x00\x00\x00\x32\xb4\x35\x8a"
                              "sme_me_mask\0"
                              "\x18\x00\x00\x00\x39\xa8\x32\x1d"
                              "remap_pfn_range\0"
                              "\x18\x00\x00\x00\xc2\x9c\xc4\x13"
                              "_copy_from_user\0"
                              "\x18\x00\x00\x00\xff\xa6\x4d\x7b"
                              "__init_rwsem\0\0\0\0"
                              "\x20\x00\x00\x00\x79\x3e\x3f\x5b"
                              "nvidia_p2p_get_pages\0\0\0\0"
                              "\x10\x00\x00\x00\x26\x30\xb3\xd6"
                              "cpu_khz\0"
                              "\x18\x00\x00\x00\xe1\xbe\x10\x6b"
                              "_copy_to_user\0\0\0"
                              "\x14\x00\x00\x00\xa1\x19\x8b\x66"
                              "down_read\0\0\0"
                              "\x10\x00\x00\x00\xa2\x54\xb9\x53"
                              "up_read\0"
                              "\x18\x00\x00\x00\xad\x23\x4c\x36"
                              "mutex_is_locked\0"
                              "\x1c\x00\x00\x00\xcb\xf6\xfd\xf0"
                              "__stack_chk_fail\0\0\0\0"
                              "\x18\x00\x00\x00\x34\x19\xdc\x8c"
                              "param_ops_int\0\0\0"
                              "\x14\x00\x00\x00\xbb\x6d\xfb\xbd"
                              "__fentry__\0\0"
                              "\x1c\x00\x00\x00\xca\x39\x82\x5b"
                              "__x86_return_thunk\0\0"
                              "\x10\x00\x00\x00\x7e\x3a\x2c\x12"
                              "_printk\0"
                              "\x14\x00\x00\x00\x25\x7a\x80\xce"
                              "up_write\0\0\0\0"
                              "\x20\x00\x00\x00\xac\x87\x24\x64"
                              "nvidia_p2p_put_pages\0\0\0\0"
                              "\x10\x00\x00\x00\xba\x0c\x7a\x03"
                              "kfree\0\0\0"
                              "\x14\x00\x00\x00\xd2\x19\xbc\x57"
                              "down_write\0\0"
                              "\x24\x00\x00\x00\x87\xa6\x2c\xf4"
                              "nvidia_p2p_free_page_table\0\0"
                              "\x1c\x00\x00\x00\x69\x8a\x0f\x7b"
                              "unmap_mapping_range\0"
                              "\x18\x00\x00\x00\xb5\x28\xc2\x17"
                              "module_layout\0\0\0"
                              "\x00\x00\x00\x00\x00\x00\x00\x00";

MODULE_INFO(depends, "nv-p2p-dummy");

MODULE_INFO(srcversion, "5FD33EAD8107E1C4EB061FD");
