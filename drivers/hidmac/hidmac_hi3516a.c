#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/time.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/slab.h>
#include <linux/io.h>

#define SYS_CRG_BASE    IO_ADDRESS(0x20030000)
#define REG_PERI_CRG54  0xd8
#define DMAC_CLK_EN     (1 << 5)
#define DMAC_SRST_REQ   (1 << 4)

void hidmac_clk_en(void)
{
	unsigned int tmp;

	tmp = readl(SYS_CRG_BASE + REG_PERI_CRG54);
	tmp |= DMAC_CLK_EN;
	writel(tmp, SYS_CRG_BASE + REG_PERI_CRG54);
}

void hidmac_unreset(void)
{
	unsigned int tmp;

	tmp = readl(SYS_CRG_BASE + REG_PERI_CRG54);
	tmp &= ~DMAC_SRST_REQ;
	writel(tmp, SYS_CRG_BASE + REG_PERI_CRG54);
}
