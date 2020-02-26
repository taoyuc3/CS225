#include "epoch.h"

/* Your code here! */
int hours(time_t t)
{
  t = time(NULL)/3600;
  return t;
}


int days(time_t t)
{
  t = time(NULL)/86400;
  return t;
}


int years(time_t t)
{
  t = time(NULL)/31536000;
  return t;
}
