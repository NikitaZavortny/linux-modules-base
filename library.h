
static struct class *MyClass;

static char Buffer [255];
static int BufferSize;

#define DEVICE_NAME "Default Chardev"
#define CLASS_NAME "CUM class"

int Init_chrdev();

int CreateDevice();


dev_t dev = 0;
static struct class *MyClass;

static char Buffer [255];
static int BufferSize;

#define DEVICE_NAME "Default Chardev"
#define CLASS_NAME "CUM class"

static int closeDRiv(struct inode *node, struct file *filee);
static int openDRiv(struct inode *node, struct file *filee);
static ssize_t writeDRiv(struct file *File, const char *UserBuffer, size_t ammount, loff_t *offs);
static ssize_t readDRiv(struct file *File, char *UserBuffer, size_t ammount, loff_t *offs);


static struct file_operations f_ops = {
	.owner = THIS_MODULE,
	.open = openDRiv,
	.write = writeDRiv,
	.read = readDRiv,
	.release = closeDRiv
};