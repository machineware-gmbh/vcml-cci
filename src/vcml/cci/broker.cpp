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

#include "vcml/cci/broker.h"

namespace vcml {
namespace cci {

broker::broker(const string& name):
    vcml::broker(name),
    m_cci_orig(name.c_str()),
    m_cci_handle(cci_get_global_broker(m_cci_orig)) {
}

broker::~broker() {
    // nothing to do
}

bool broker::lookup(const string& key, string& value) {
    m_cci_handle.ignore_unconsumed_preset_values(
        [key](const std::pair<string, cci_value>& iv) -> bool {
            return iv.first == key;
        });

    m_cci_handle.lock_preset_value(key);

    if (m_cci_handle.get_preset_cci_value(key).try_get<string>(value))
        return true;

    // non-string cci-values cannot easily be converted to string
    // without templates unless you make use of rapidjson
    string json = m_cci_handle.get_preset_cci_value(key).to_json();
    if (json == "null")
        return false;

    value = json;
    return true;
}

bool broker::defines(const string& key) const {
    return m_cci_handle.has_preset_value(key);
}

} // namespace cci
} // namespace vcml
