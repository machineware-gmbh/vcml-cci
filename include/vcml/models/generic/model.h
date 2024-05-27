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

#ifndef VCML_GENERIC_MODEL_H
#define VCML_GENERIC_MODEL_H

#include "vcml/core/types.h"
#include "vcml/core/range.h"
#include "vcml/core/systemc.h"
#include "vcml/core/peripheral.h"

#include "vcml/logging/logger.h"
#include "vcml/properties/property.h"

namespace vcml {
namespace generic {

class model : public peripheral
{
private:
    u32 read_some_reg();
    u32 read_other_reg();

public:
    reg<u32> some_reg;
    reg<u32> other_reg;

    tlm_target_socket in;

    model(const sc_module_name& nm);
    virtual ~model();
    VCML_KIND(generic::model);

    virtual void reset() override;

    virtual const char* version() const override;
};

} // namespace generic
} // namespace vcml

#endif
