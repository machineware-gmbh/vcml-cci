/******************************************************************************
 *                                                                            *
 * Copyright (C) 2024 MachineWare GmbH                                        *
 * All Rights Reserved                                                        *
 *                                                                            *
 * This is work is licensed under the terms described in the LICENSE file     *
 * found in the root directory of this source tree.                           *
 *                                                                            *
 ******************************************************************************/

#include "testing.h"
#include "vcml-cci.h"

TEST(cci, broker) {
    cci_utils::broker cci_broker("cci_broker");
    cci::cci_register_broker(cci_broker);
    cci::cci_value cci_value(cci::cci_value::from_json("123"));
    cci::cci_originator cci_orig("my_orig");

    vcml::cci::broker vcml_broker("vcml_broker");

    // define a CCI value and test that the vcml broker sees it
    cci_broker.set_preset_cci_value("my_param", cci_value, cci_orig);
    ASSERT_TRUE(vcml_broker.defines("my_param"));

    // test that we can also get the value of the CCI param
    std::string my_param;
    ASSERT_TRUE(vcml_broker.lookup("my_param", my_param));
    ASSERT_EQ(my_param, "123");
}
