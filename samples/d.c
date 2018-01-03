// This program is slightly adapted from GNU cflow's manual
// [https://www.gnu.org/software/cflow/manual/cflow.html#Recursive-Calls]

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
     
/* Return true if file NAME is a directory. */
static int
isdir (char *name)
{
  struct stat st;
       
  if (stat (name, &st))
    {
      perror (name);
      return 0;
    }
  return S_ISDIR (st.st_mode);
}
     
static char *ignored_names[] = { ".", "..", NULL };
     
/* Return true if NAME should not be recursed into */
int
ignorent (char *name)
{
  char **p;
  for (p = ignored_names; *p; p++)
    if (strcmp (name, *p) == 0)
      return 1;
  return 0;
}
     
int max_level = -1;
     
/* Print contents of the directory PREFIX/NAME.
   Prefix each output line with LEVEL spaces. */
void
printdir (int level, char *name)
{
  DIR *dir;
  struct dirent *ent;
  char cwd[512];
     
  if (!getcwd(cwd, sizeof cwd)) 
    {
      perror ("cannot save cwd\n");
      _exit (1);
    }
  chdir (name);
  dir = opendir (".");
  if (!dir)
    {
      perror (name);
      _exit (1);
    }
       
  while ((ent = readdir (dir)))
    {
      printf ("%*.*s%s", level, level, "", ent->d_name);
      if (ignorent (ent->d_name))
	printf ("\n");
      else if (isdir (ent->d_name))
	{
	  printf ("/");
	  if (level + 1 == max_level)
	    putchar ('\n');
	  else
	    {
	      printf (" contains:\n");
	      printdir (level + 1, ent->d_name);
	    }
	}
      else
	printf ("\n");
    }
  closedir (dir);
  chdir (cwd);
}
     
int
main (int argc, char **argv)
{
  if (argc < 2)
    {
      fprintf (stdout, "usage: d [-MAX] DIR [DIR...]\n");
      return 1;
    }
     
  if (argv[1][0] == '-')
    {
      if (!(argv[1][1] == '-' && argv[1][2] == 0))
	max_level = atoi (&argv[1][1]);
      --argc;
      ++argv;
    }
       
  while (--argc)
    printdir (0, *++argv);
       
  return 0;
}
