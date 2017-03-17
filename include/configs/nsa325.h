/*
 * (C) Copyright 2016 bodhi <mibodhi@gmail.com>
 *
 * Based on
 * Copyright (C) 2014 Jason Plum <jplum@archlinuxarm.org>
 * Based on 
 * Copyright (C) 2012  Peter Schildmann <linux@schildmann.info>
 *
 * Based on guruplug.h originally written by
 * Siddarth Gore <gores@marvell.com>
 * (C) Copyright 2009
 * Marvell Semiconductor <www.marvell.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA
 */

#ifndef _CONFIG_NSA325_H
#define _CONFIG_NSA325_H

/*
 * Version number information
 */
#define CONFIG_IDENT_STRING	"\nZyXEL NSA325 2-Bay Power Media Server"

/*
 * High Level Configuration Options (easy to change)
 */
#define CONFIG_FEROCEON_88FR131	1	/* CPU Core subversion */
#define CONFIG_KIRKWOOD		1	/* SOC Family Name */
#define CONFIG_KW88F6281	1	/* SOC Name */
#define CONFIG_MACH_NSA325		/* Machine type */
#define CONFIG_MACH_TYPE	MACH_TYPE_NSA325
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
#define CONFIG_SYS_PROMPT	"NSA325> "	/* Command Prompt */

/*
 *  Environment variables configurations
 */
#define CONFIG_ENV_IS_NOWHERE		1		/* if env in SDRAM */
/*
 * max 4k env size is enough, but in case of nand
 * it has to be rounded to sector size
 */
#define CONFIG_ENV_SIZE			0x20000		/* 128k */

/*
 * Default environment variables
 */
#define CONFIG_BOOTCOMMAND \
	"echo '==========================================================='; " \
	"echo 'This u-boot makes restoring different firmware images easy.'; " \
	"echo 'DO NOT FLASH TO NAND, ONLY FOR SERIAL BOOT WITH KWBOOT !!!'; " \
	"echo 'More info here: http://fff.com/fffff' ; " \
	"echo '==========================================================='; " \
	"echo 'Commands:'; " \
	"echo 'run flash.factory - will reflash factory firmware from USB'; " \
	"echo '                    * /mtd folder must exist in USB drive root and'; " \
	"echo '                      contain the mtd0 to mtd5 dumps'; " \
	"echo '                    * Recovery files from Zyxel should also reside'; " \
	"echo '                      in the USB drive root'; " \
	"echo '                    * This command will flash all the parts and then'; " \
	"echo '                      reboot in the stock u-boot/kernel'; " \
	"echo '                    * During first stock boot, recovery files from USB'; " \
	"echo '                      will be used to properly restore kernel and rootfs parts'; " \
	"echo '                    * After first stock boot, issue the bellow command via serial '; " \
	"echo '                      to restore correct MAC address: fw_setenv ethaddr [co:re:ct:ma:ca:dd]'; " \
	"echo '                      The original MAC should be on a label on the back of the device chassis'; " \
	"echo 'run flash.uboot - will flash uboot.img from USB'; " \
	"echo '                   * /uboot.img must exist in USB drive root'; " \
	"echo '                   * image will be written @0x00000000'; " \
	"echo 'run flash.uenv  - will flash uenv.img  from USB'; " \
	"echo '                   * /uenv.img must exist in USB drive root'; " \
	"echo '                   * image will be written @0x000c0000'; " \
	"echo 'help            - display u-boot help'; " \
	"echo 'printenv        - display environment - readonly'; " \
	"echo 'boot            - display this help again'; echo; " \
	"echo '==========================================================='; " \
	"echo '!!!!!!!!WARNING!!!!!!!!!WARNING!!!!!!!!!!WARNING!!!!!!!!!!!'; " \
	"echo '==========================================================='; " \
	"echo; " \
	"echo '        Bellow are the bad blocks of this flash. '; " \
	"echo '        DO NOT FLASH IF THERE ARE BAD BLOCKS'; " \
	"echo '        BETWEEN 0x00000000 and 0x00100000 !!!'; " \
	"nand bad; echo; " \
	"echo '==========================================================='; echo "


#define CONFIG_EXTRA_ENV_SETTINGS \
	"bootdelay=0\0" \
	"baudrate=115200\0" \
	"ethact=egiga0\0" \
	"ethaddr=00:19:cb:00:51:81\0" \
	"mtdids=nand0=orion_nand\0" \
	"mtdparts=mtdparts=orion_nand:0x100000(uboot),0x80000(stock_uboot_env),0x80000(key_store)," \
	"0x80000(info),0xA00000(etc),0xA00000(kernel_1),0x2FC0000(rootfs1),0xA00000(kernel_2),0x2FC0000(rootfs2)\0"\
	"stderr=serial\0" \
	"stdin=serial\0" \
	"stdout=serial\0" \
	"init_usb=usb start\0" \
	"flash.uboot=run init_usb; sleep 5; if load usb 0:1 0x0800000 uboot.img; then nand erase 0x0 0xc0000; nand write 0x0800000 0x0 0xc0000; fi \0" \
	"flash.uenv=run init_usb; sleep 5; if load usb 0:1 0x0800000 uenv.img; then nand erase 0xc0000 0x20000; nand write 0x0800000 0xc0000 0x20000; fi \0" \
	"flash.factory=run init_usb; sleep 5; " \
	"if load usb 0:1 0xc80000 /mtd/mtd0; then " \
	"nand erase.part uboot; nand write 0xc80000 uboot; " \
	"if load usb 0:1 0xc80000 /mtd/mtd1; then nand erase.part stock_uboot_env; nand write 0xc80000 stock_uboot_env; fi; " \
	"nand erase.part key_store; " \
	"if load usb 0:1 0xc80000 /mtd/mtd3; then nand erase.part info; nand write 0xc80000 info; fi; " \
	"nand erase.part etc; " \
	"if load usb 0:1 0xc80000 /mtd/mtd5; then " \
	"nand erase.part kernel_1; nand write 0xc80000 kernel_1; " \
	"nand erase.part kernel_2; nand write 0xc80000 kernel_2; fi; " \
	"nand erase.part rootfs1; nand erase.part rootfs2; reset; " \
	"else echo '/mtd/mtd0 not found on USB drive!!!'; fi\0"

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

#endif /* _CONFIG_NSA325_H */
