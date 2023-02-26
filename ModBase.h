#ifndef _MODEBASE_
#define _MODEBASE_
#include "ModBase.c"

#define INITALIZE_DESC_MODULE(NAME, DESC) MODULE_AUTHOR(NAME); MODULE_DESCRIPTION(DESC);
#define INITALIZE_MODULE(NAME) MODULE_AUTHOR(NAME); MODULE_DESCRIPTION("Default module description");

MODULE_LICENSE("GPL");



int Init_chrdev(void);

int CreateDevice(void);



static int closeDRiv(struct inode *node, struct file *filee);
static int openDRiv(struct inode *node, struct file *filee);
static ssize_t writeDRiv(struct file *File, const char *UserBuffer, size_t ammount, loff_t *offs);
static ssize_t readDRiv(struct file *File, char *UserBuffer, size_t ammount, loff_t *offs);



#endif