/**
 * io.h - DesignWare USB3 DRD IO Header
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com
 *
 * Authors: Felipe Balbi <balbi@ti.com>,
 *	    Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 *
 * Taken from Linux Kernel v3.19-rc1 (drivers/usb/dwc3/io.h) and ported
 * to uboot.
 *
 * commit 2c4cbe6e5a : usb: dwc3: add tracepoints to aid debugging
 *
 * SPDX-License-Identifier:     GPL-2.0
 *
 */

#ifndef __DRIVERS_USB_DWC3_IO_H
#define __DRIVERS_USB_DWC3_IO_H

#include <asm/io.h>

#define	CACHELINE_SIZE		CONFIG_SYS_CACHELINE_SIZE
static inline u32 dwc3_readl(void __iomem *base, u32 offset)
{
	u32 offs = offset - DWC3_GLOBALS_REGS_START;
	u32 value;

	/*
	 * We requested the mem region starting from the Globals address
	 * space, see dwc3_probe in core.c.
	 * However, the offsets are given starting from xHCI address space.
	 */
	offs += (unsigned long)base;
	value = readl((unsigned long)offs);

	return value;
}

static inline void dwc3_writel(void __iomem *base, u32 offset, u32 value)
{
	u32 offs = offset - DWC3_GLOBALS_REGS_START;

	/*
	 * We requested the mem region starting from the Globals address
	 * space, see dwc3_probe in core.c.
	 * However, the offsets are given starting from xHCI address space.
	 */
	offs += (unsigned long)base;
	writel(value, (unsigned long)offs);
}

static inline void dwc3_flush_cache(int addr, int length)
{
	flush_dcache_range(addr, addr + ROUND(length, CACHELINE_SIZE));
}
#endif /* __DRIVERS_USB_DWC3_IO_H */
