/*
 * chardev.c: Crea un chardev que se le envia datos y se los puede leer luego. 
 *
 * Basado en chardev.c desde TLDP.org's LKMPG book.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h> /* for put_user */


int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "UNGS"
#define BUF_LEN 80

/*
 * Global variables are declared as static, so are global within the file.
 */

static int Major;
static int Device_Open = 0;
static char msg[BUF_LEN];
static struct file_operations fops = {
	.owner = THIS_MODULE,
	/* OPS ??? */
  .release = device_release,
  .read    = device_read,
  .write   = device_write,
  .open    = device_open,
};

/*
 * This function is called when the module is loaded
 */
int init_module(void)
{
    Major = register_chrdev(0, DEVICE_NAME, &fops);

    if (Major < 0) {
        printk(KERN_ALERT "Registrando char device con %d\n", Major);
        return Major;
    }

    printk(KERN_INFO "Tengo major number %d.Hablarle al driver ", Major);
    printk(KERN_INFO ", crear un dev_file con \n");
    printk(KERN_INFO "sudo rm /dev/%s\n", DEVICE_NAME);
    printk(KERN_INFO "sudo mknod /dev/%s c %d 0\n", DEVICE_NAME, Major);
    printk(KERN_INFO "sudo chmod 666 /dev/%s\n", DEVICE_NAME);
    printk(KERN_INFO "Probá varios minor numbers. Probar cat y echo\n");
    printk(KERN_INFO "al device file.\n");
    printk(KERN_INFO "Eliminar el /dev y el modulo al termina.\n");

    return SUCCESS;
}

/*
 * This function is called when the module is unloaded
 */
void cleanup_module(void)
{
    /*
     * Unregister the device
     */
    unregister_chrdev(Major, DEVICE_NAME);
}

/*
 * Methods
 */

/*
 * Called when a process tries to open the device file, like
 * "cat /dev/chardev
 */
static int device_open(struct inode *inode, struct file *filp)
{
    if (Device_Open) {
        return -EBUSY;
    }

    return SUCCESS;
}

/*
 * Called when a process closes the device file.
 */
static int device_release(struct inode *inode, struct file *filp)
{
    return SUCCESS;
}

/*
 * Called when a process, which already opened the dev file, attempts to read
 * from it.
 */
static ssize_t device_read(struct file *filp, /* see include/linux/fs.h   */
                           char *buffer,      /* buffer to fill with data */
                           size_t length,     /* length of the buffer     */
                           loff_t *offset)
{
    int msg_length;

    msg_length = length;
    /* If position is behind the end of a file we have nothing to read */
    if( *offset >= sizeof(msg) ) {
        return 0;
    }
    
    /* If a user tries to read more than we have, read only as many bytes as we have */
    if( *offset + length > sizeof(msg) ) {
        msg_length = sizeof(msg) - *offset;
    }

    if( copy_to_user(buffer, msg + *offset, msg_length) != 0 ) {
        return -EFAULT;    
    }

    /* Move reading position */
    *offset += msg_length;
    return msg_length;
}

/*
 * Called when a process writes to dev file: echo "hi" > /dev/UNGS
 */
static ssize_t device_write(struct file *filp, const char *tmp, size_t length, loff_t *offset) {
    int msg_length;

    msg_length = length;
    /* overwrite buffer protection */
    if(length > sizeof(msg)){
        msg_length = sizeof(msg);
    }

    if (copy_from_user(msg, tmp, msg_length))
        return -EFAULT;

    *offset += msg_length;
    return msg_length;
}
