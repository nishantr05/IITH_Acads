/*
 *
 * Authors : Sumadhva Sridhar and S.Nishant Reddy
 * Roll no : ES18BTECH11018, ES18BTECH11013
 *
 */

#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/mm.h>

#include <mydev.h>

MODULE_DESCRIPTION("My kernel module - mykmod");
MODULE_AUTHOR("maruthisi.inukonda [at] gmail.com");
MODULE_LICENSE("GPL");

// Dynamically allocate major no
#define MYKMOD_MAX_DEVS 256
#define MYKMOD_DEV_MAJOR 0
#define MYSHYM_LEN 1048576

static int mykmod_init_module(void);
static void mykmod_cleanup_module(void);

static int mykmod_open(struct inode *inode, struct file *filp);
static int mykmod_close(struct inode *inode, struct file *filp);
static int mykmod_mmap(struct file *filp, struct vm_area_struct *vma);

module_init(mykmod_init_module);
module_exit(mykmod_cleanup_module);

static struct file_operations mykmod_fops = {
	.owner = THIS_MODULE,	/* owner (struct module *) */
	.open = mykmod_open,	/* open */
	.release = mykmod_close,	/* release */
	.mmap = mykmod_mmap,	/* mmap */
};

static void mykmod_vm_open(struct vm_area_struct *vma);
static void mykmod_vm_close(struct vm_area_struct *vma);
//static int mykmod_vm_fault(struct vm_fault *vmf);
static int mykmod_vm_fault(struct vm_area_struct *vma, struct vm_fault *vmf);

//Data-structure to keep per device info:
struct mykmod_dev_info {
	char *data;
	int size;
};

//Device table data-structure to keep all devices:
struct mykmod_dev_info *info[MYKMOD_MAX_DEVS];

//Data-structure to keep per VMA info :
struct vma_info {
	struct mykmod_dev_info *info_ptr;
	long unsigned int npgfaults;
};

static const struct vm_operations_struct mykmod_vm_ops = {
	.open = mykmod_vm_open,
	.close = mykmod_vm_close,
	.fault = mykmod_vm_fault
};

int mykmod_major, mykmod_minor, i;	//Declaring few useful variables

static int mykmod_init_module(void)
{
	printk("mykmod loaded\n");
	printk("mykmod initialized at=%p\n", init_module);

	if ((mykmod_major =
	     register_chrdev(MYKMOD_DEV_MAJOR, "mykmod", &mykmod_fops)) < 0) {
		printk(KERN_WARNING "Failed to register character device\n");
		return 1;
	} else {
		printk("register character device %d\n", mykmod_major);
	}

	return 0;
}

static void mykmod_cleanup_module(void)
{
	printk("mykmod unloaded\n");
	unregister_chrdev(mykmod_major, "mykmod");
	// TODO free device info structures from device table
	for (i = 0; i < MYKMOD_MAX_DEVS && info[i] != NULL; i++) {
		if (info[i]->data) {
			kfree(info[i]->data);
		}
		kfree(info[i]);
	}
	return;
}

static int mykmod_open(struct inode *inodep, struct file *filep)
{
	printk("mykmod_open: filep=%p f->private_data=%p "
	       "inodep=%p i_private=%p i_rdev=%x maj:%d min:%d\n",
	       filep, filep->private_data,
	       inodep, inodep->i_private, inodep->i_rdev, MAJOR(inodep->i_rdev),
	       MINOR(inodep->i_rdev));

	//Allocating memory for devinfo and storing in the device table and i_private.
	if (inodep->i_private == NULL) {
		mykmod_minor = MINOR(inodep->i_rdev);
		info[mykmod_minor] =
		    kmalloc(sizeof(struct mykmod_dev_info), GFP_KERNEL);
		printk("mykmod_open: virt_to_phys = 0x%llx\n",
		       (unsigned long long)virt_to_phys((void *)info));
		info[mykmod_minor]->data =
		    (char *)kzalloc(MYSHYM_LEN, GFP_KERNEL);
		info[mykmod_minor]->size = MYSHYM_LEN;
		inodep->i_private = info[mykmod_minor];
	}
	// Store device info in file's private_data aswell
	filep->private_data = inodep->i_private;

	return 0;
}

static int mykmod_close(struct inode *inodep, struct file *filep)
{
	printk("mykmod_close: inodep=%p filep=%p\n", inodep, filep);
	return 0;
}

static int mykmod_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct vma_info *vm_inf = kzalloc(sizeof(struct vma_info), GFP_KERNEL);
	unsigned long map_len, offset;
	printk("mykmod_mmap: filp=%p vma=%p flags=%lx\n", filp, vma,
	       vma->vm_flags);

	//saving private data (devinfo, npagefaults) in vm_private_data
	vm_inf->info_ptr = (struct mykmod_dev_info *)filp->private_data;
	vma->vm_private_data = vm_inf;
	//setting up vma's flags:
	vma->vm_ops = &mykmod_vm_ops;
	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;

	//Checking if the mapping exceeds the file bounds:
	map_len = vma->vm_end - vma->vm_start;
	offset = vma->vm_pgoff << PAGE_SHIFT;
	if ((offset + map_len) > MYSHYM_LEN) {
		//The mapping exceeds the file bounds,
		return EINVAL;
	}

	mykmod_vm_open(vma);

	return 0;
}

static void mykmod_vm_open(struct vm_area_struct *vma)
{
	((struct vma_info *)vma->vm_private_data)->npgfaults = 0;
	printk("mykmod_vm_open: vma=%p npagefaults:%lu\n", vma,
	       ((struct vma_info *)vma->vm_private_data)->npgfaults);
}

static void mykmod_vm_close(struct vm_area_struct *vma)
{
	printk("mykmod_vm_close: vma=%p npagefaults:%lu\n", vma,
	       ((struct vma_info *)vma->vm_private_data)->npgfaults);
	kfree(vma->vm_private_data);
}

static int mykmod_vm_fault(struct vm_area_struct *vma, struct vm_fault *vmf)
{
	//creating virt to physical mappings
	struct page *page;
	//We first calculate the appropriate offset, so we know the location of the fault address in our kernel VAS:
	unsigned long offset =
	    ((unsigned long)vmf->virtual_address - vma->vm_start) +
	    (vma->vm_pgoff << PAGE_SHIFT);
	//We then add this offset to the 'data' pointer, to get the actual fault address
	unsigned long fault_address =
	    (unsigned long)((struct vma_info *)vma->vm_private_data)->info_ptr->
	    data + offset;

	((struct vma_info *)vma->vm_private_data)->npgfaults++;	//Increment pgfault count.

	//update the page pointer
	page = virt_to_page(fault_address);
	get_page(page);		//update the reference count of the page
	vmf->page = page;

	return 0;
}
