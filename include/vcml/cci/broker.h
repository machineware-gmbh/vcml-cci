/******************************************************************************
 *                                                                            *
 * Copyright 2024 MachineWare GmbH                                            *
 * All Rights Reserved                                                        *
 *                                                                            *
 * This is unpublished proprietary work owned by MachineWare GmbH. It may be  *
 * used, modified and distributed in accordance to the license specified by   *
 * the license file in the root directory of this project.                    *
 *                                                                            *
 ******************************************************************************/

#ifndef VCML_CCI_BROKER_H
#define VCML_CCI_BROKER_H

#include "vcml/cci/types.h"

namespace vcml {
namespace cci {

class broker : public vcml::broker
{
private:
    cci_originator m_cci_orig;
    cci_broker_handle m_cci_handle;

public:
    broker(const string& name);
    virtual ~broker();

    virtual bool lookup(const string& key, string& value) override;
    virtual bool defines(const string& key) const override;
};

} // namespace cci
} // namespace vcml

#endif
