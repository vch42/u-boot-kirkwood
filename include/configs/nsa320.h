/*
 * Copyright (C) 2015-2016  bodhi <mibodhi@gmail.com>
 *
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

#ifndef _CONFIG_NSA320_H
#define _CONFIG_NSA320_H

/*
 * Version number information
 */
#define CONFIG_IDENT_STRING	"\nZyXEL NSA320 2-Bay Power Media Server"

/*
 * High Level Configuration Options (easy to change)
 */
#define CONFIG_FEROCEON_88FR131	1	/* CPU Core subversion */
#define CONFIG_KIRKWOOD		1	/* SOC Family Name */
#define CONFIG_KW88F6281	1	/* SOC Name */
#define CONFIG_MACH_NSA320		/* Machine type */
#define CONFIG_MACH_TYPE	MACH_TYPE_NSA320
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
#define CONFIG_SYS_PROMPT	"NSA320> "	/* Command Prompt */

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
#define CONFIG_ENV_ADDR			0x100000
#define CONFIG_ENV_OFFSET		0x100000	/* env starts here */

/*
 * Default environment variables
 */
#define CONFIG_BOOTCOMMAND \
	"nand read.e 0x2000000 $(kernel_addr) 0xA00000; bootm 0x2000000"

#define CONFIG_EXTRA_ENV_SETTINGS \
	"bootargs=console=ttyS0,115200 mtdparts=nand_mtd:0x100000(uboot),0x80000(uboot_env),0x80000(key_store),0x80000(info),0xA00000(etc),0xA00000(kernel_1),0x2FC0000(rootfs1),0xA00000(kernel_2),0x2FC0000(rootfs2) root=/dev/nfs rw init=/init\0" \
	"bootdelay=2\0" \
	"baudrate=115200\0" \
	"loads_echo=0\0" \
	"run_diag=yes\0" \
	"eth1addr=00:19:CB:00:51:82\0" \
	"ipaddr=10.4.50.165\0" \
	"serverip=10.4.50.5\0" \
	"netmask=255.255.255.0\0" \
	"rootpath=/mnt/ARM_FS/\0" \
	"nandEcc=1bit\0" \
	"MODEL_ID=DD01\0" \
	"PRODUCT_NAME=NSA-320\0" \
	"FEATURE_BIT=00\0" \
	"CONTRY_TYPE=FF\0" \
	"VENDOR_NAME=ZyXEL Communications Corp.\0" \
	"ethaddr=00:19:CB:00:51:81\0" \
	"stdin=serial\0" \
	"stdout=serial\0" \
	"stderr=serial\0" \
	"console=console=ttyS0,115200 mtdparts=nand_mtd:0xc0000@0(uboot)ro,0x7f00000@0x100000(root)\0" \
	"mainlineLinux=no\0" \
	"CASset=min\0" \
	"enaMonExt=no\0" \
	"enaCpuStream=no\0" \
	"enaWrAllo=no\0" \
	"pexMode=RC\0" \
	"disL2Cache=no\0" \
	"setL2CacheWT=yes\0" \
	"disL2Prefetch=yes\0" \
	"enaICPref=yes\0" \
	"enaDCPref=yes\0" \
	"sata_dma_mode=yes\0" \
	"ethprime=egiga1\0" \
	"netbsd_en=no\0" \
	"vxworks_en=no\0" \
	"bootargs_root=root=/dev/nfs rw\0" \
	"bootargs_end=:::DB88FXX81:eth0:none\0" \
	"image_name=uImage\0" \
	"standalone=fsload 0x2000000 $(image_name);setenv bootargs $(console) root=/dev/mtdblock0 rw ip=$(ipaddr):$(serverip)$(bootargs_end) $(mvPhoneConfig); bootm 0x2000000;\0" \
	"disaMvPnp=no\0" \
	"ethmtu=1500\0" \
	"eth1mtu=1500\0" \
	"mvPhoneConfig=mv_phone_config=dev0:fxs,dev1:fxs\0" \
	"mvNetConfig=mv_net_config=(00:11:88:0f:62:81,0:1:2:3),mtu=1500\0" \
	"usb0Mode=host\0" \
	"yuk_ethaddr=00:00:00:EE:51:81\0" \
	"hddPowerCtrl=no\0" \
	"netretry=no\0" \
	"rcvrip=169.254.100.100\0" \
	"loadaddr=0x02000000\0" \
	"autoload=no\0" \
	"enaAutoRecovery=yes\0" \
	"pcieTune=no\0" \
	"ethact=egiga1\0" \
	"kernel_addr=0xc80000"

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

#endif /* _CONFIG_NSA320_H */
