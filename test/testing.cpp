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

test_base::test_base(const sc_core::sc_module_name& nm):
    component(nm),
    m_tracer(),
    m_logger(),
    m_reset("reset"),
    m_clock("clock", 100 * mwr::MHz) {
    m_reset.rst.bind(rst);
    m_clock.clk.bind(clk);
    SC_HAS_PROCESS(test_base);
    SC_THREAD(run);
}

test_base::~test_base() {
    finalize_test();
}

void test_base::run() {
    wait(sc_core::SC_ZERO_TIME);
    run_test();
    sc_core::sc_stop();
}

void test_base::finalize_test() {
    ASSERT_EQ(sc_core::sc_get_status(), sc_core::SC_STOPPED)
        << "simulation incomplete";
}

static void systemc_report_handler(const sc_core::sc_report& r,
                                   const sc_core::sc_actions& a) {
    // To disable a report manually during testing, use:
    //     sc_report_handler::set_actions(SC_ID_<name>, SC_DO_NOTHING);
    if (a == sc_core::SC_DO_NOTHING)
        return;

    switch (r.get_severity()) {
    case sc_core::SC_INFO:
        break;

    case sc_core::SC_FATAL:
    case sc_core::SC_ERROR:
    case sc_core::SC_WARNING:
    default:
        // pass on any report we got from SystemC (warning, error, fatal)
        // to googletest; this catches SystemC things we do not want, like
        // sc_stop being called twice, duplicate module names, etc.
        ADD_FAILURE() << r.what();
        break;
    }

    sc_core::sc_report_handler::default_handler(r, a);
}

std::vector<std::string> args;

std::string get_resource_path(const std::string& name) {
    if (args.size() < 2) {
        ADD_FAILURE() << "test resource path information not provided";
        std::abort();
    }

    std::string res_dir = args[1];
    if (!mwr::file_exists(res_dir)) {
        ADD_FAILURE() << "test resource path does not exist: " << res_dir;
        std::abort();
    }

    std::string res = args[1] + "/" + name;
    EXPECT_TRUE(mwr::file_exists(res)) << "resource " << name << " not found";
    return res;
}

extern "C" int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    mwr::report_segfaults();
    vcml::broker_arg broker(argc, argv);
    sc_core::sc_report_handler::set_handler(systemc_report_handler);
    for (int i = 0; i < argc; i++)
        args.push_back(argv[i]);

    return sc_core::sc_elab_and_sim(argc, argv);
}

extern "C" int sc_main(int argc, char** argv) {
    return RUN_ALL_TESTS();
}
