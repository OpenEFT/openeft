/*
 * LICENSE
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <openssl/des.h>

#include "openeft.h"
#include "log/log.h"


int log_fp;
int log_run_level;
int err_code;



int eft_init(int argc, char* argv[]);

int main(int argc, char* argv[])
{
  if (eft_init(argc, argv) == EFT_NOK)
  {
    log(LOG_EMERG, "Error code [%d]\n", err_code);
  }
  return 0;
}


int eft_init(int argc, char* argv[])
{
  log_fp = fileno(stdout);
  log_run_level = LOG_DEBUG;
  err_code = 0;
 
  return EFT_NOK;
}

