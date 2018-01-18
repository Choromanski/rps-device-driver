/*
 * "Rock Paper Scissors" kernel module - /dev version
 *
 * Brian Choromanski <bjc76@pitt.edu>
 *
 */

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/random.h>

#include <asm/uaccess.h>

#include "rps_dev.h"



unsigned char get_random(){
	unsigned int c;
	get_random_bytes(&c, 1);
	if(c < 0){
		c += -1;
	}
	if(mode == 1){
		return c%1+1;
	}if(mode == 2){
		return c%1+2;
	}if(mode == 3){
		return c%1+3;
	}else{
        return c%3+1;
    }
}

/*
 * rps_read is the function called when a process calls read() on
 * /dev/rps.  It writes count bytes to the buffer passed in the
 * read() call.
 */


static ssize_t rps_read(struct file * file, char * buf, size_t count, loff_t *ppos){
	unsigned char num = get_random();
		
	/*
	 * We only support reading the whole string at once.
	 */
	if (count < sizeof(unsigned char))
		return -EINVAL;

	/*
	 * Besides copying the string to the user provided buffer,
	 * this function also checks that the user has permission to
	 * write to the buffer, that it is mapped, etc.
	 */
	if (copy_to_user(buf, &num, sizeof(num)))
		return -EINVAL;
	/*
	 * Tell the user how much data we wrote.
	 */
	*ppos = sizeof(unsigned char);

	return sizeof(unsigned char);
}

/*
 * rps_write is the function called when a process calls write() on
 * /dev/rps.  It reads count bytes from the buffer passed in the
 * write() call.
 */

static ssize_t rps_write(struct file * file, const char * buf, size_t count, loff_t *ppos){
	int index = count-2;

	if(buf[index] == '0'){
		mode = 0;
	}else if(buf[index] == '1'){
		mode = 1;
	}else if (buf[index] == '2'){
		mode = 2;
	}else if (buf[index] == '3'){
		mode = 3;
	}
	printk("%d", mode);
	return count;
}

/*
 * Now we have two file operations: read, write
 */

static const struct file_operations rps_fops = {
	.owner	= THIS_MODULE,
	.read	= rps_read,
	.write 	= rps_write,
};

static struct miscdevice rps_dev = {
	/*
	 * We don't care what minor number we end up with, so tell the
	 * kernel to just pick one.
	 */
	MISC_DYNAMIC_MINOR,
	/*
	 * Name ourselves /dev/hello.
	 */
	"rps",
	/*
	 * What functions to call when a program performs file
	 * operations on the device.
	 */
	&rps_fops
};

static int __init
rps_init(void){
	int ret;

	mode = 0;

	/*
	 * Create the "rps" device in the /sys/class/misc directory.
	 * Udev will automatically create the /dev/rps device using
	 * the default rules.
	 */
	ret = misc_register(&rps_dev);
	if (ret)
                printk(KERN_ERR "Unable to register \"Hello, world!\" misc device\n");
        else {
                printk(KERN_ERR "Registered device under <MAJOR , MINOR><%d %d>\n" , 10, rps_dev.minor);
                printk(KERN_ERR "Create device file using: mknod /dev/rps c %d %d\n", 10, rps_dev.minor);
        }

	return ret;
}

module_init(rps_init);

static void __exit
rps_exit(void)
{
	misc_deregister(&rps_dev);
}

module_exit(rps_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Valerie Henson <val@nmt.edu>");
MODULE_DESCRIPTION("\"Hello, world!\" minimal module");
MODULE_VERSION("dev");
