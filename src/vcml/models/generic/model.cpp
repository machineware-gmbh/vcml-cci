/******************************************************************************
 *                                                                            *
 * Copyright 2022 MachineWare GmbH                                            *
 * All Rights Reserved                                                        *
 *                                                                            *
 * This is unpublished proprietary work and may not be used or disclosed to   *
 * third parties, copied or duplicated in any form, in whole or in part,      *
 * without prior written permission of the authors.                           *
 *                                                                            *
 ******************************************************************************/

#include "vcml/models/generic/model.h"
#include "vcml/models/generic/model_version.h"

namespace vcml {
namespace generic {

u32 model::read_some_reg() {
    return 1234;
}

model::model(const sc_module_name& nm):
    peripheral(nm),
    some_reg("some_reg", 0x0, 0xffffffff),
    other_reg("other_reg", 0x4, 0),
    in("in") {
    some_reg.sync_always();
    some_reg.allow_read_only();
    some_reg.on_read(&model::read_some_reg);

    other_reg.sync_always();
    other_reg.allow_write_only();
}

model::~model() {
    // cleanup
}

const char* model::version() const {
    return TEMPLATE_MODEL_VERSION_STRING;
}

void model::reset() {
    // reset model
}

} // namespace generic
} // namespace vcml
