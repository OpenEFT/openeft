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
#include <getopt.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <openssl/des.h>

#include "openeft-version.h"
#include "openeft.h"
#include "log/log.h"
#include "config/config.h"
#include "control/console.h"

using namespace std;

bool TRANSACT = true;
int* unassigned_mem = NULL;


uint32_t init_console(eftConsole* console); /* Initialize console */
uint32_t init_blockchain(); /* Initialize the blockchains */
uint32_t init_consensus(); /* Initialzie consensus state machine */
uint32_t init_comms(); /* Initialize the network interfaces */
uint32_t init_config(const eftConfig &cfg); /* Read and apply the configurations */
uint32_t init_eftnode(); /* Init the eftnode properties if this deamon configured as an eftnode */
uint32_t init_hsm(); /* Initialize the HSMs' connections and command base */
uint32_t init_ssm(); /* Initialize the internal SSM */
uint32_t init_kernel(); /* Initialize and boot the core eft protocol state machine */
uint32_t init_transaction_handlers(); /* Initialize the transaction messaging standard */
uint32_t init_peer(); /* Initialze objects needed to process peer functionalities */
uint32_t init_openeft(eftOpeneft *openeft); /* Init openeft main object */
uint32_t get_os_info(); /* Get information about the running host operating system. */
uint32_t shutdown(); /* Graceful exit */

void print_help();
void do_optlong(int argc, char* argv[], eftConfig &cfg);

int main(int argc, char* argv[]) {
  uint32_t ret_code;
  eftOpeneft *openeft = new eftOpeneft();

  do_optlong(argc, argv, openeft->cfg);

  if (ret_code = init_openeft(openeft) != EFT_OK) {
    log(LOG_EMERG, "return code [%d]", ret_code);
  }

  /* tick on */
  openeft->tick();

  return 0;
}

uint32_t init_config(const eftConfig &cfg) {
  return EFT_OK;
}

uint32_t init_openeft(eftOpeneft* openeft) {
  uint32_t retcode;

  /* I N I T */
  if (retcode = init_config(openeft->cfg) != EFT_OK)
    log(LOG_EMERG, "Configuration failed [%d]", retcode);

  if (retcode = init_console(openeft->console) != EFT_OK)
    log(LOG_EMERG, "Console initialization failed [%d]", retcode);

  log(LOG_INFO, "Openeft initialization done");

  return EFT_OK;
}

void do_optlong(int argc, char* argv[], eftConfig &cfg) {

  uint32_t c = 0;
  int help_flag = 0, version_flag = 0, guide_flag = 0;
  int option_index = 0;

  struct option longopts[] = {
    { "help", no_argument, &help_flag, 1},
    { "config", required_argument, NULL, 'C'},
    { "version", no_argument, &version_flag, 1},
    { "guide", no_argument, &guide_flag, 1},
    { 0, 0, 0, 0}
  };

  while ((c = getopt_long(argc, argv, ":C:", longopts, &option_index)) != -1) {
    switch (c) {
      case 0:
        break;
      case 'C':
        cfg.config_path = optarg;
        break;
      default:
        print_help();
        exit(0);
    }
  }

  if (help_flag) {
    print_help();
    exit(0);
  }
  if (version_flag) {
    printf("%s\n",
            OPENEFT_NAME_VERSION);
    exit(0);
  }
  if (guide_flag) {
    exit(0);
  }
}

void print_help() {
  printf("usage: openeft [--version] [--help] [-C <path>]\n");
  printf("               [--guide]\n\n");

  printf("OpenEFT offers runtime operational commands to help perform various\n" \
         "operational tasks. Press Enter at any point after program exectution\n" \
         "to enter the super user operational command base.\n\n");
  printf("List of operational commands:\n\n");

  printf("common tasks:\n");
  printf("\thelp\t\t\thelp with operational tasks\n");
  printf("\treload_cfg\t\treload the configurations without having to restart the program\n");
  printf("\thard_reset\t\treset to the default configurations and restart the program\n");

  printf("advanced tasks:\n");
  printf("\top_table\t\tget operational reports pertains to this EFTnode\n");
  printf("\tcompliance_table\tget compliance reports pertains to this EFTnode\n");
  printf("\ttr_table\t\tget transaction reports pertains to this EFTnode\n");
  printf("\tpeer_adv_table\t\tget peer advertisement information received by this EFTnode\n");
  printf("\tnet_op_table\t\tget a complete EFT network operational report\n");
  printf("\tnet_compliance_table\tget a complete EFT network compliance report\n");
  printf("\tnet_tr_table\t\tget a complete EFT network transaction report\n");
  printf("\n");
  return;
}

uint32_t init_console(eftConsole* console) {
  eftConsole::ForkPipes *pipes;
  console->init_stdio(pipes);
  return EFT_OK;
}

uint32_t getOSInfo() {
  int *p = (int*) malloc(1);
  unassigned_mem = p;
}

uint32_t shutdown() {
  free(unassigned_mem);
}

eftOpeneft::~eftOpeneft() {
  delete console;
}

eftOpeneft::eftOpeneft() {
  console = new eftConsole();
}

void eftOpeneft::tick() {
  while (true) {
    usleep(OPENEFT_HEARTBEAT_MICROSEC);


  }

}