/* sdiaudiocore.h
 *
 * Header file for the Linux user-space audio API for
 * Linear Systems Ltd. SDI interface boards.
 *
 * Copyright (C) 2009-2010 Linear Systems Ltd.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either Version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public Licence for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Linear Systems can be contacted at <http://www.linsys.ca/>.
 *
 */

#ifndef _SDIAUDIOCORE_H
#define _SDIAUDIOCORE_H

#include <linux/fs.h> /* file_operations */
#include <linux/poll.h> /* poll_table */
#include <linux/mm.h> /* vm_area_struct */

#include "mdev.h"
#include "miface.h"
#include "mdma.h"
#include "../include/sdiaudio.h"

#define SDIAUDIO_BUFFERS_MAX (131072 / sizeof (void *))
#define SDIAUDIO_BUFSIZE_MAX (131072 / sizeof (unsigned char *) / 2 * PAGE_SIZE)

/* External function prototypes */

int sdiaudio_open (struct inode *inode, struct file *filp);
ssize_t sdiaudio_write (struct file *filp,
	const char __user *data,
	size_t length,
	loff_t *offset);
ssize_t sdiaudio_read (struct file *filp,
	char __user *data,
	size_t length,
	loff_t *offset);
unsigned int sdiaudio_txpoll (struct file *filp, poll_table *wait);
unsigned int sdiaudio_rxpoll (struct file *filp, poll_table *wait);
long sdiaudio_txioctl (struct file *filp,
	unsigned int cmd,
	unsigned long arg);
long sdiaudio_rxioctl (struct file *filp,
	unsigned int cmd,
	unsigned long arg);
int sdiaudio_mmap (struct file *filp, struct vm_area_struct *vma);
int sdiaudio_release (struct inode *inode, struct file *filp);
int sdiaudio_register_iface (struct master_dev *card,
	struct master_dma_operations *dma_ops,
	u32 data_addr,
	unsigned int direction,
	struct file_operations *fops,
	struct master_iface_operations *iface_ops,
	unsigned int cap,
	unsigned int granularity);
void sdiaudio_unregister_iface (struct master_iface *iface);

#endif

