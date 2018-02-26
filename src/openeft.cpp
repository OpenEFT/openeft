//----------------------------------------------------------------------
// Copyright (C) 2018  openeft.org
// Copyright (C) Reza Schadmani <reza.schadmani@openeft.org>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <openssl/des.h>

#include "openeft.h"
#include "openeft-version.h"
#include "log/log.h"
#include "config/config.h"
#include "console/console.h"


uint32_t log_fp;
uint32_t log_run_level;




uint32_t eft_init(int argc, char* argv[]);
void print_help();

int main(int argc, char* argv[])
{
  uint32_t ret_code;
  if (ret_code = eft_init(argc, argv) != EFT_OK) {
    log(LOG_EMERG, "return code [%d]\n", ret_code);
  }
  return 0;
}


uint32_t eft_init(int argc, char* argv[])
{
  log_fp = fileno(stdout);
  log_run_level = LOG_DEBUG;

  uint32_t c = 0;
  CEftConfig cfg;
  
  if(argc == 1) {
    print_help();
    return EFT_OK;
  }
  
  /* check for revision before any system logics. */
  while ((c = getopt(argc, argv, "Vvc:")) != EOF) {
    switch (c) {
      case 'V':
      case 'v':
        printf("%s\n",
                OPENEFT_NAME_VERSION);

        exit(0);
        break;
      case 'c':
        cfg.config_path = optarg;
        break;
      default:
        /* in case of any other arguments */
        print_help();
        
        return EFT_ARG_ERR;
        break;
    }
  }
 
  return EFT_OK;
}

void print_help()
{
  printf("Command line parameters:\n");
  printf("Vv" MOV_COL_RIGHT_CMD "print server version.\n");
  printf("c [config path] " MOV_COL_RIGHT_CMD "specify the configuration file path to use.\n");
  
  return;
}