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

#include "testing.h"

#include "vcml/models/generic/model.h"

class test_bench : public test_base
{
public:
    generic::model model;

    tlm_initiator_socket out;

    test_bench(const sc_module_name& nm):
        test_base(nm), model("model"), out("out") {
        out.bind(model.in);

        rst.bind(model.rst);
        clk.bind(model.clk);
    }

    enum addresses : u64 {
        ADDR_SOME_REG = 0x0,
        ADDR_OTHER_REG = 0x4,
    };

    virtual void run_test() override {
        u32 data;
        EXPECT_OK(out.readw(ADDR_SOME_REG, data)) << "failed to read some";
        EXPECT_EQ(data, 1234u) << "some_reg reported wrong value";

        EXPECT_OK(out.writew(ADDR_OTHER_REG, data)) << "failed to write other";
        EXPECT_EQ(model.other_reg, 1234u) << "other_reg reported wrong value";

        EXPECT_CE(out.writew(ADDR_SOME_REG, data)) << "writing readonly reg";
    }
};

TEST(model, simulate) {
    test_bench bench("bench");
    sc_core::sc_start();
}
