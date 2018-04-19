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
#include "control.h"

#include "comms/rpc_server_ssl.h"
#include "control_service.h"


void eftControlService::run() {
  RegisterService(&srv);
  RunService();
  HandleRpcs();
}

void eftControlService::HandleRpcs() {
  void* tag = NULL;
  bool ok = false;

  /* Add data objects here */
  new eftCallDataHelp(&srv, cq.get(), this->ctrl);

  while (true) {
    GPR_ASSERT(cq->Next(&tag, &ok));
    GPR_ASSERT(ok);
    static_cast<eftRpcCallData*> (tag)->Proceed();
  }
}



eftCallDataHelp::eftCallDataHelp(::grpc::Service* service, ServerCompletionQueue* cq, eftControl* control) :
eftRpcCallData(service, cq),
responder(&ctx),
ctrl(control){
  Proceed();
}

void eftCallDataHelp::Proceed() {
  if (status == CREATE) {
    status = PROCESS;

    ((ControlSrv::AsyncService*)srv)->Requesthelp(&ctx, &request, &responder, cq, cq,
            this);
  } else if (status == PROCESS) {
    
    /* Respawn itself for the next query */
    new eftCallDataHelp(srv, cq, ctrl);

    /* Process the reply here and set the reply object accordingly */
    HelpResult ret;
    ctrl->help(ret);
    reply.set_eft_checkup(ret.eft_checkup);
    
    status = FINISH;
    responder.Finish(reply, Status::OK, this);
  } else {
    GPR_ASSERT(status == FINISH);
    delete this;
  }
}
