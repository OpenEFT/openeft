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
#include "global.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <openssl/des.h>

#include "openeft-version.h"
#include "log/log.h"
#include "config/config.h"
#include "control/console.h"

using namespace std;

bool TRANSACT = true;
int* unassignedMem = NULL;


uint32_t init_console(); /* Initialize console */
uint32_t init_blockchain(); /* Initialize the blockchains */
uint32_t init_consensus(); /* Initialzie consensus state machine */
uint32_t init_comms(); /* Initialize the network interfaces */
uint32_t init_config(const CEftConfig &cfg); /* Read the configurations and apply them to the core OpenEFT deamon */
uint32_t init_eftnode(); /* Init the eftnode properties if this deamon configured as an eftnode */
uint32_t init_hsm(); /* Initialize the HSMs' connections and command base */
uint32_t init_ssm(); /* Initialize the internal SSM */
uint32_t init_kernel(); /* Initialize and boot the core eft protocol state machine */
uint32_t init_transaction_handlers(); /* Initialize the transaction messaging standard */
uint32_t init_peer(); /* Initialze objects needed to process peer functionalities */
uint32_t init_openeft(int argc, char* argv[]); /* Init openeft main object */
uint32_t getOSInfo(); /* Get information about the running host operating system. */
uint32_t shutdown(); /* Graceful exit */

void print_help();

int main(int argc, char* argv[])
{
  uint32_t ret_code;
  if (ret_code = init_openeft(argc, argv) != EFT_OK) {
    log(LOG_EMERG, "return code [%d]", ret_code);
  }
  return 0;
}


uint32_t init_openeft(int argc, char* argv[])
{
  CEftConfig cfg;
  
  uint32_t retcode;
  uint32_t c = 0;
  
  cfg.config_path = "openeft.conf";
  
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
        exit(0);
    }
  }
  
  /* I N I T */
  if(retcode = init_config(cfg) != EFT_OK)
    log(LOG_EMERG, "Configuration failed [%d]", retcode);
  
  if(retcode = init_console() != EFT_OK)
    log(LOG_EMERG, "Console initialization failed [%d]", retcode);

  
  log(LOG_INFO, "Openeft initialization done");
  
  return EFT_OK;
}

void print_help()
{
  printf("Command line parameters:\n");
  printf("Vv" MOV_COL_RIGHT_CMD "print server version.\n");
  printf("c [config path] " MOV_COL_RIGHT_CMD "specify the configuration file path to use.\n");
  
  return;
}


uint32_t getOSInfo() {
  int *p = (int*)malloc(1);
  unassignedMem = p;
}

uint32_t shutdown() {
  free(unassignedMem);
}