
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <time.h>
#include <stdint.h>

static int verbose_flag;

void timestamp()
{
    time_t ltime; /* calendar time */
    ltime=time(NULL); /* get current cal time */
    printf("%s",asctime( localtime(&ltime) ) );
}

int main (int argc, char **argv)
{
  int c;
  char *file_name = NULL;
  char *out_file_name = NULL;


  while (1)
  {
    static struct option long_options[] =
    {
      {"verbose", no_argument,       &verbose_flag, 1},
      {"in_file",    required_argument, 0, 'i'},
      {"out_file",    required_argument, 0, 'o'},
      {0, 0, 0, 0}
    };
    /* getopt_long stores the option index here. */
    int option_index = 0;

    c = getopt_long (argc, argv, "i:o:",long_options, &option_index);
                       
    if (c == -1) break;

    switch (c)
    {
      case 0:
        /* If this option set a flag, do nothing else now. */
        if (long_options[option_index].flag != 0)  break;
        printf ("option %s", long_options[option_index].name);
        if (optarg) printf (" with arg %s", optarg);
        printf ("\n");
        break;

      case 'i':
        file_name = optarg;
        break;

      case 'o':
        out_file_name = optarg;
        break;

      case '?':
        /* getopt_long already printed an error message. */
        break;

      default:
        abort ();
    }
  }

  if(!file_name) 
  {
    printf("-i is mandatory \n");
    exit(1);
  }

  if(!out_file_name) 
  {
    printf("-o is mandatory \n");
    exit(1);
  }

  if (verbose_flag)  puts ("verbose flag is set");

  printf ("Processing %s\n", file_name);
  printf ("Writing into file %s\n", out_file_name);

  exit (0);
}

