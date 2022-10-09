
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <time.h>
#include <stdint.h>

static int verbose_flag;
static char **variable_names = NULL;

void timestamp()
{
    time_t ltime; /* calendar time */
    ltime=time(NULL); /* get current cal time */
    printf("%s",asctime( localtime(&ltime) ) );
}

void report_and_out()
{
  printf("Error: Out of Memory \n");
  exit(1);
}

char **get_comma_separated_values(char *str1)
{
  int i;
  int j=0;
  int ctr=0;
  char **cs_values = (char**) malloc (10 * sizeof (char*));
  if (cs_values == NULL) report_and_out();

  for (i=0;i<4;i++) 
  {
    cs_values[i] = (char*) malloc (24 * sizeof(char));
    if (ts_values[i] == NULL) report_and_out();
  }

  for(i=0;i<=(strlen(str1));i++)
  {
    // if tabe or NULL found, assign NULL into newString[ctr]
    if(str1[i]=='\t'||str1[i]=='\0')
    {
      ts_values[ctr][j]='\0';
      ctr++;  //for next word
      j=0;    //for next word, init index to 0
    }
    else
    {
      ts_values[ctr][j]=str1[i];
      j++;
    }
  }

  number_of_variables = ctr;

  return ts_values;
}

void process_csv_file (char *fname)
{
  char *line     = NULL;
  FILE *fp;
  size_t len;
  ssize_t nread;
  int i = 0;

  fp = fopen(fname,"r");
  if (fp==NULL) 
  {
    printf("Can't open %s\n", fname);
    exit(EXIT_FAILURE);
  } 

  while ((nread = getline(&line, &len, fp)) != -1) 
  {
    line[strcspn(line, "\n")] = 0;

    if (i==0)
    {
      printf("line is '%s'\n", line);
    }
    ++i;
  }
 
  free(line);
  fclose(fp);
}

int main (int argc, char **argv)
{
  int c; // used to getopt_long

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
  process_csv_file(file_name);

  printf ("Writing into file %s\n", out_file_name);

  exit (0);
}

