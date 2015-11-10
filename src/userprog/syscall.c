#include "userprog/syscall.h"
#include "userprog/process.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/synch.h"

#include "userprog/process.h"
#include <debug.h>
#include <inttypes.h>
#include <round.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userprog/gdt.h"
#include "userprog/pagedir.h"
#include "userprog/tss.h"
#include "filesys/directory.h"
#include "filesys/file.h"
#include "filesys/filesys.h"
#include "threads/flags.h"
#include "threads/init.h"
#include "threads/interrupt.h"
#include "threads/palloc.h"
#include "threads/thread.h"
#include "threads/vaddr.h"

static void syscall_handler (struct intr_frame *);
static void syscall_exit(int);
static void syscall_write(struct intr_frame*);
static void syscall_halt(void);
static void syscall_fork(struct intr_frame*);
static void syscall_wait(void);

static void syscall_handler (struct intr_frame *);
//static struct lock file_lock;

/* Process identifier. */
typedef int pid_t;
typedef int (*handler) (uint32_t, uint32_t, uint32_t);
static handler syscall_map[32];
static void *param_esp;

void
syscall_init (void)
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED)
{
  int* i = (int*)(f->esp);
  //hex_dump(0,f->esp,40,false);
  //printf ("system call! by %d\n",*i);
  switch(*i){
   case SYS_EXIT:
     syscall_exit(*(i+1));
     break;
    case SYS_FORK:
      syscall_fork(f);
      break;
   default:
     printf("default\n");
  }

  return;
}

static void
syscall_exit(int status){
 printf("exit(%d) [NOT IMPLEMENTED]\n",status);
 thread_exit ();
 }

 static void
syscall_fork(struct intr_frame *f){
  process_fork(thread_current()->name);
}
