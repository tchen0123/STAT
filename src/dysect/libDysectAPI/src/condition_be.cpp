/*
Copyright (c) 2013-2014, Lawrence Livermore National Security, LLC.
Produced at the Lawrence Livermore National Laboratory.
Written by Niklas Nielsen, Gregory Lee [lee218@llnl.gov], Dong Ahn.
LLNL-CODE-645136.
All rights reserved.

This file is part of DysectAPI. For details, see https://github.com/lee218llnl/DysectAPI. Please also read dysect/LICENSE

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License (as published by the Free Software Foundation) version 2.1 dated February 1999.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the IMPLIED WARRANTY OF MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the terms and conditions of the GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include <LibDysectAPI.h>
#include <DysectAPI/Err.h>
#include <DysectAPI/Condition.h>
#include <DysectAPI/Expr.h>

using namespace std;
using namespace DysectAPI;
using namespace Dyninst;
using namespace ProcControlAPI;

DataRef::DataRef(Value::content_t type, const char *name) : type(type), name(name) {
  var = new TargetVar(name);
}

bool DataRef::getVal(Value& val, Process::const_ptr process, Thread::const_ptr thread) {

  ConditionResult condResult;

  if(!var) {
    return DYSECTWARN(false, "Target variable not available for collection");
  }

  DysectAPI::DysectErrorCode code = var->getValue(condResult, val, process, thread->getTID());
  if(code != OK) {
    return DYSECTWARN(false, "Value could not be fetched!");
  }

  if(condResult != Resolved) {
    return DYSECTINFO(false, "Value not available - probably optimized out");
  }

  return true;
}

