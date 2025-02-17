//@file kernel.c
//@brief entry point of ceanos kernel
//@author ceanvalds

/* SYSTEM */

#include <sys/call/syscall.h>
#include <sys/proc/process.h>
#include <sys/proc/scheduler.h>
#include <multiboot.h>
#include <timer.h>
#include "kernel.h" 

/* DESCRIPTOR TABLES */

#include <gdt.h>
#include <idt.h>

/* DRIVERS  */

#include <drivers/storage/ata.h>
#include <drivers/video/vga/vga.h>
#include <drivers/kb/kbps2.h>
#include <drivers/video/vga/vga_types.h>

#include <drivers/devices/serial.h>
#include <drivers/devices/dev.h>

// #include <drivers/generic/pci.h>

/* MEMORY */

#include <mm/malloc.h>
#include <mm/paging.h>
#include <mm/mem.h>

/* FILE SYSTEMS */

#include <fs/fat.h>
#include <fs/vfs.h>
#include <fs/tmpfs.h>

/* STDLIB */

#include <stdlib/stdio.h>
#include <stdlib/string.h>

/* UTILS */

#include <stdint.h>
#include <util.h>
#include <io.h>

/* OPTIONS */
#include <compiler.h>
#include "config.h"

// actual code

void main(uint32_t magic, struct multiboot_info* boot);
char prompt[2] = "% ";
int safe_mode = 0;

bool debug_mode;

void check_boot_params(struct multiboot_info *boot)
{
	struct multiboot_info *mbi = (struct multiboot_info *) boot;

	if (mbi->flags & 0x00000002) {
		char *cmdline = (char *) mbi->cmdline;
		if (__strstr(cmdline, "safe_mode=1")) {
			debugf("[boot] safe_mode=1\n");
			safe_mode = 1;
		} else {
			debugf("[boot] safe_mode=0\n");
		}
	}
}

// Initialize all the important stuff, like idt, gdt, etc

static void init_mm(struct multiboot_info* boot)
{
	//calculate physical memory start for kernel heap
	uint32_t mod1 = *(uint32_t*)(boot->mods_addr + 4);
	uint32_t physicalAllocStart = (mod1 + 0xFFF) & ~0xFFF;
	initMemory(boot->mem_upper * 1024, physicalAllocStart);
	kmallocInit(0x4000);
    	debugf("[mm] memory done!\n");
}

static void init_tables()
{
	gdt_init();
	idt_init();
}

static void init_all(struct multiboot_info* boot)
{
	#ifdef DEBUG
	debug_mode = true;
	#endif

	vga_disable_cursor();
        
        init_tables();

	check_boot_params(boot);

	timer_init();
	keyboard_init();
	init_mm(boot);

	vfs_init();
	init_tmpfs();

        init_devices(); 

	__printf("[ceanos] OK\n");

	sleep(750000);
	Reset();
}

void enable_default(struct multiboot_info* boot)
{
	init_all(boot);

	__printf("                               CeanOS V%s\n", VERSION);       // This part will probably be cleared and replaced with something
	__printf("                        Public Domain Operating System\n\n"); // else in the future, like loading a shell executable, but for now
        
        __printf("Do 'help' for more info \n");
        __printf("ceanos%s", prompt);		                                // it will just print a message and initialize the "shell"

	set_screen_color(0x0F);
}

void enable_safe(struct multiboot_info* boot)
{
	init_all(boot);

	__printf("##welcome to ceanos##\n");
	__printf("SAFE MODE\n");
	__printf("current os version: %s\n", VERSION);
	__printf("safemode%s", prompt);

	set_screen_color(0x0F);
}

public void main(uint32_t magic, struct multiboot_info* boot)
{
        #define __ceanos__
	if (safe_mode == 1) {
		__printf("safe mode is enabled !\n");
		enable_safe(boot);
	} else {
		enable_default(boot);
	}
                
	while(1) {
		// TODO: Add a way to check for stack overflows and other errors that the ISR can't handle
	};
}
