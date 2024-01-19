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

KSYMTAB_FUNC(nvidia_p2p_init_mapping, "", "");
KSYMTAB_FUNC(nvidia_p2p_destroy_mapping, "", "");
KSYMTAB_FUNC(nvidia_p2p_get_pages, "", "");
KSYMTAB_FUNC(nvidia_p2p_put_pages, "", "");
KSYMTAB_FUNC(nvidia_p2p_free_page_table, "", "");

SYMBOL_CRC(nvidia_p2p_init_mapping, 0x45bb0ad7, "");
SYMBOL_CRC(nvidia_p2p_destroy_mapping, 0x180f4b6a, "");
SYMBOL_CRC(nvidia_p2p_get_pages, 0x5b3f3e79, "");
SYMBOL_CRC(nvidia_p2p_put_pages, 0x642487ac, "");
SYMBOL_CRC(nvidia_p2p_free_page_table, 0xf42ca687, "");

static const char ____versions[] __used
    __section("__versions") = "\x14\x00\x00\x00\xbb\x6d\xfb\xbd"
                              "__fentry__\0\0"
                              "\x1c\x00\x00\x00\xca\x39\x82\x5b"
                              "__x86_return_thunk\0\0"
                              "\x18\x00\x00\x00\xb5\x28\xc2\x17"
                              "module_layout\0\0\0"
                              "\x00\x00\x00\x00\x00\x00\x00\x00";

MODULE_INFO(depends, "");

MODULE_INFO(srcversion, "790367931CF35EA7D85F6A8");
