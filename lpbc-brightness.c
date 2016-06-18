#include <stdio.h>
#include <stdlib.h>

#include "lpbc-brightness.h"

long
lpbc_brightness_get (void)
{
  FILE *fp;
  char brightness[1035];
  fp = popen ("xbacklight", "r");

  if (NULL == fp) {
    printf ("Failed to run command\n" );
    return 0;
  }

  if (fgets(brightness, sizeof(brightness) - 1, fp) == NULL) {
    printf ("Failed to get brightness\n");
    return 0;
  }

  long val = strtol(brightness, NULL, 10);

  pclose (fp);

  return val;
}

void
lpbc_brightness_raise (bool async)
{
  char *command;
  if (async) {
    command = "xbacklight -inc 7 &";
  } else {
    command = "xbacklight -inc 7";
  }

  FILE *f = popen (command, "r");
  if (NULL == f) {
    return;
  }
  pclose (f);
}

void
lpbc_brightness_lower (bool async)
{
  char *command;
  if (async) {
    command = "xbacklight -dec 6 &";
  } else {
    command = "xbacklight -dec 6";
  }

  FILE *f = popen (command, "r");
  if (NULL == f) {
    return;
  }
  pclose (f);
}

void
lpbc_brightness_set (double brightness, bool async)
{
  char brightness_str[30] = {'\0'};
  char *command;
  if (async) {
    command = "xbacklight -set %f &";
  } else {
    command = "xbacklight -set %f";
  }

  snprintf(brightness_str, sizeof(brightness_str), command, brightness);

  FILE *f = popen (brightness_str, "r");
  if (NULL == f) {
    return;
  }
  pclose (f);
}
