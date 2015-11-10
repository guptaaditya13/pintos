#include <stdio.h>
#include <syscall.h>

int
main (int argc, char **argv)
{
  int i;

  /* for (i = 0; i < argc; i++) */
    /* printf ("%s ", argv[i]); */
  printf ("\n\nARINDAM\n\n");
  fork();

  return EXIT_SUCCESS;
}
