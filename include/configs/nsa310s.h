/*
 * Copyright (C) 2016 bodhi <mibodhi@gmail.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 *
 */

#ifndef _CONFIG_NSA310S_H
#define _CONFIG_NSA310S_H

/*
 * Version number information
 */
#define CONFIG_IDENT_STRING	"\nZyXEL NSA310S/320S 1/2-Bay Power Media Server"

/*
 * High Level Configuration Options (easy to change)
 */
#define CONFIG_FEROCEON_88FR131	1	/* CPU Core subversion */
#define CONFIG_KIRKWOOD		1	/* SOC Family Name */
#define CONFIG_KW88F6192        1       /* Compatible SOC Name */
#define CONFIG_KW88F6702        1       /* SOC Name */
#define CONFIG_MACH_NSA310S		/* Machine type */
#define CONFIG_MACH_TYPE	MACH_TYPE_NSA310S
#define CONFIG_SKIP_LOWLEVEL_INIT	/* disable board lowlevel_init */

/*
 * Misc Configuration Options
 */
#define CONFIG_SHOW_BOOT_PROGRESS 1	/* boot progess display (LED's) */

/*
 * Commands configuration
 */
#define CONFIG_SYS_NO_FLASH             /* Declare no flash (NOR/SPI) */
#define CONFIG_SYS_MVFS                 /* Picks up Filesystem from mv-common.h */
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_ENV
#define CONFIG_CMD_IDE
#define CONFIG_CMD_MII
#define CONFIG_CMD_NAND
#define CONFIG_CMD_PING
#define CONFIG_CMD_USB
#define CONFIG_CMD_DATE
#define CONFIG_SYS_LONGHELP
#define CONFIG_PREBOOT
#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2 "> "

/*
 * mv-common.h should be defined after CMD configs since it used them
 * to enable certain macros
 */
#include "mv-common.h"

#undef CONFIG_SYS_PROMPT	/* previously defined in mv-common.h */
#define CONFIG_SYS_PROMPT	"NSA3x0S> "	/* Command Prompt */

/*
 *  Environment variables configurations
 */
#ifdef CONFIG_CMD_NAND
#define CONFIG_ENV_IS_IN_NAND		1
#define CONFIG_ENV_SECT_SIZE		0x20000		/* 128K */
#else
#define CONFIG_ENV_IS_NOWHERE		1		/* if env in SDRAM */
#endif
/*
 * max 4k env size is enough, but in case of nand
 * it has to be rounded to sector size
 */
#define CONFIG_ENV_SIZE			0x20000		/* 128k */
#define CONFIG_ENV_ADDR			0xc0000
#define CONFIG_ENV_OFFSET		0xc0000	/* env starts here */

/*
 * Default environment variables
 */
#define CONFIG_BOOTCOMMAND \
	"mw 0x800000 0 1; run set_init_devices; run scan_disk; run bootcmd_uenv; run set_bootargs; run bootcmd_exec; sleep 5; reset"

#define CONFIG_EXTRA_ENV_SETTINGS \
	"arcNumber=4931\0" \
	"preboot=setenv stderr serial; setenv stdin serial; setenv stdout serial; setenv baudrate 115200; setenv console ttyS0,$baudrate; setenv bootdelay 10\0" \
	"stderr=serial\0" \
	"stdin=serial\0" \
	"stdout=serial\0" \
	"baudrate=115200\0" \
	"console=ttyS0,$baudrate\0" \
	"bootdelay=10\0" \
	"led_error=orange blinking\0" \
	"led_exit=green off\0" \
	"led_init=green blinking\0" \
	"ethact=egiga0\0" \
	"ethaddr=00:19:cb:00:51:81\0" \
	"mtdids=nand0=orion_nand\0" \
	"mtdparts=mtdparts=orion_nand:0x100000(uboot),0x80000(stock_uboot_env),0x80000(key_store),0x80000(info),0xA00000(etc),0xA00000(kernel_1),0x2FC0000(rootfs1),0xA00000(kernel_2),0x2FC0000(rootfs2)\0" \
	"partition=nand0,2\0" \
	"file_uimage=/boot/uImage\0" \
	"file_uinitrd=/boot/uInitrd\0" \
	"file_uenv=/boot/uEnv\0" \
	"addr_uimage=0x0800000\0" \
	"addr_uenv=0x0810000\0" \
	"addr_uinitrd=0x1100000\0" \
	"addr_dtb=0x1c00000\0" \
	"devices=usb ide\0" \
	"disks=0 1 2 3\0" \
	"device=0:1\0" \
	"bootdev=usb\0" \
	"usb_ready_retry=15\0" \
	"rootdelay=10\0" \
	"uenv_loaded=0\0" \
	"scan_done=0\0" \
	"set_init_devices=setenv init_usb \"usb start\"; setenv init_ide \"ide reset\"\0" \
	"flash_new_uboot=run set_init_devices; run init_usb; sleep 5; if load usb 0:1 $addr_uimage uboot.img; then nand erase 0x0 0xc0000; nand write $addr_uimage 0x0 0x80000; reset; fi\0" \
	"flash_new_uenv=run set_init_devices; run init_usb; sleep 5; if load usb 0:1 $addr_uimage uenv000000000000.img; then nand erase 0xc0000 0x20000; nand write $addr_uimage 0xc0000 0x20000; reset;	fi\0" \
	"load_dtb=echo \"LOADING DTB $file_dtb ...\"; load $bootdev $device $addr_dtb $file_dtb; echo \"_________________________________________________\"\0" \
	"load_uimage=echo \"LOADING uImage $file_uimage ...\"; load $bootdev $device $addr_uimage $file_uimage; echo \"_________________________________________________\"\0" \
	"load_uinitrd=echo \"LOADING uInitrd $file_uinitrd ...\" ; load $bootdev $device $addr_uinitrd $file_uinitrd; echo \"_________________________________________________\"\0" \
	"set_bootargs=setenv bootargs console=$console root=$rootfs rootdelay=$rootdelay rootfstype=$rootfstype $mtdparts $initsystem $custom_params\0" \
	"scan_disk=echo \"_________________________________________________\"; echo \"  SCANNING FOR BOOT DRIVE...\"; echo \"  BOOT PRIORITY: $devices \"; run set_init_devices; for dev in $devices; do if test $scan_done -eq 0; then echo \"_________________________________________________\"; echo \"  SCAN DEVICE $dev\"; run init_$dev; for disknum in $disks; do if test $scan_done -eq 0; then echo \"_________________________________________________\"; echo \"  DEVICE $dev $disknum:1\"; if load $dev $disknum:1 $addr_uimage $file_uimage 1; then setenv scan_done 1; echo \"  FOUND BOOTABLE DRIVE ON $dev $disknum\"; echo \"_________________________________________________\"; setenv device $disknum:1; setenv bootdev $dev; fi; fi; done; fi; done; sleep 3\0" \
	"bootcmd_exec=run load_uimage; if run load_uinitrd; then if run load_dtb; then bootm $addr_uimage $addr_uinitrd $addr_dtb; else bootm $addr_uimage $addr_uinitrd; fi; else if run load_dtb; then bootm $addr_uimage - $addr_dtb; else bootm $addr_uimage; fi; fi\0" \
	"bootcmd_uenv=echo \"_________________________________________________\"; echo \"  LOOKING FOR EXTRA ENV FILE: $file_uenv\"; echo \"  ON BOOT PARTITION: $bootdev $device \"; echo \"                                                 \"; if load $bootdev $device $addr_uenv $file_uenv; then setenv uenv_loaded 1; echo \"                                                 \"; echo \"  LOADED EXTRA ENVS FROM $bootdev $device ... \"; echo \"                                                 \"; fi; if test $uenv_loaded -eq 1; then echo \"  IMPORTING EXTRA ENVS...\"; echo \"_________________________________________________\"; env import -t $addr_uenv $filesize; fi; sleep 3"


/*
 * Ethernet Driver configuration
 */
#ifdef CONFIG_CMD_NET
#define CONFIG_MVGBE_PORTS		{1, 0}	/* enable port 0 only */
#define CONFIG_PHY_BASE_ADR		0x1
#define CONFIG_PHY_GIGE
#define CONFIG_NETCONSOLE
#endif /* CONFIG_CMD_NET */

/*
 * SATA Driver configuration
 */
#ifdef CONFIG_MVSATA_IDE
#define CONFIG_SYS_ATA_IDE0_OFFSET      MV_SATA_PORT0_OFFSET
#define CONFIG_SYS_ATA_IDE1_OFFSET      MV_SATA_PORT1_OFFSET
#endif /* CONFIG_MVSATA_IDE */

/*
 * File system
 */
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_EXT4
#define CONFIG_CMD_FAT
#define CONFIG_CMD_JFFS2
#define CONFIG_JFFS2_NAND
#define CONFIG_JFFS2_LZO
#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS
#define CONFIG_RBTREE
#define CONFIG_MTD_DEVICE               /* needed for mtdparts commands */
#define CONFIG_MTD_PARTITIONS
#define CONFIG_CMD_MTDPARTS
#define CONFIG_LZO

/*
 * EFI partition
 */
#define CONFIG_EFI_PARTITION

/*
 *  Date Time
 */
#ifdef CONFIG_CMD_DATE
#define CONFIG_RTC_MV
#define CONFIG_CMD_SNTP
#define CONFIG_CMD_DNS
#endif /* CONFIG_CMD_DATE */

#endif /* _CONFIG_NSA310S_H */
