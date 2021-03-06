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
#include "control/control_service.h"

bool transact = true;
int* unassigned_mem = NULL;

void print_help();
void do_optlong(int argc, char* argv[], eftConfig &cfg);
void get_os_info();

int main(int argc, char* argv[]) {
  uint32_t ret_code;
  eftOpeneft *openeft = new eftOpeneft();

  do_optlong(argc, argv, openeft->cfg);

  if (ret_code = openeft->init() != EFT_OK) {
    log(LOG_EMERG, "return code [%d]", ret_code);
  }

  openeft->tick();
  
  openeft->shutdown();
  delete openeft;

  return 0;
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
  return;
}

void getOSInfo() {
  int *p = (int*) malloc(1);
  unassigned_mem = p;
}

eftOpeneft::~eftOpeneft() {
  delete control;
  delete control_service;
}

eftOpeneft::eftOpeneft() {
  control = new eftControl();
  control_service = new eftControlService(control,
                eftConfig::cli_ipaddr,
                eftConfig::cli_port,
                eftConfig::cli_server_crt,
                eftConfig::cli_server_key,
                eftConfig::cli_cafile);
}

uint32_t eftOpeneft::init() {
  uint32_t retcode;

  /* I N I T */
  if (retcode = init_config() != EFT_OK)
    log(LOG_EMERG, "Configuration failed [%d]", retcode);
  if (retcode = init_control() != EFT_OK)
    log(LOG_EMERG, "Configuration failed [%d]", retcode);
  if (retcode = init_eft_services() != EFT_OK)
    log(LOG_EMERG, "Configuration failed [%d]", retcode);

  log(LOG_INFO, "openeft initialization done");

  return EFT_OK;
}

uint32_t eftOpeneft::init_eft_services() {
  EFTOBJ_TICK_ON(eftControlService, control_service);
  return EFT_OK;
}

uint32_t eftOpeneft::init_config() {
  return EFT_OK;
}

uint32_t eftOpeneft::init_control() {
  EFTOBJ_TICK_ON(eftControl, control);
  return EFT_OK;
}

uint32_t eftOpeneft::shutdown() {
  EFTOBJ_TICK_OFF(eftControl, control);
  EFTOBJ_TICK_OFF(eftControlService, control_service);
  free(unassigned_mem);
}

void eftOpeneft::tick() {
  while (transact) {
    usleep(OPENEFT_HEARTBEAT_MICROSEC);
  }
}