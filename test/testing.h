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

#ifndef VCML_CCI_TESTING_H
#define VCML_CCI_TESTING_H

#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <mwr.h>
#include <systemc>
#include <vcml.h>

using namespace ::testing;

#define ASSERT_OK(tlmcall) ASSERT_EQ(tlmcall, TLM_OK_RESPONSE)
#define ASSERT_AE(tlmcall) ASSERT_EQ(tlmcall, TLM_ADDRESS_ERROR_RESPONSE)
#define ASSERT_CE(tlmcall) ASSERT_EQ(tlmcall, TLM_COMMAND_ERROR_RESPONSE)

#define EXPECT_OK(tlmcall) EXPECT_EQ(tlmcall, TLM_OK_RESPONSE)
#define EXPECT_AE(tlmcall) EXPECT_EQ(tlmcall, TLM_ADDRESS_ERROR_RESPONSE)
#define EXPECT_CE(tlmcall) EXPECT_EQ(tlmcall, TLM_COMMAND_ERROR_RESPONSE)

#define EXPECT_SUCCESS(fn) EXPECT_TRUE(vcml::success(fn))
#define EXPECT_FAILURE(fn) EXPECT_TRUE(vcml::failure(fn))

class test_base : public vcml::component
{
private:
    vcml::tracer_term m_tracer;
    mwr::publishers::terminal m_logger;

    vcml::generic::reset m_reset;
    vcml::generic::clock m_clock;

    void run();

public:
    test_base() = delete;
    test_base(const sc_core::sc_module_name& nm);
    virtual ~test_base();

    virtual void run_test() = 0;
    virtual void finalize_test();
};

extern std::vector<std::string> args;

std::string get_resource_path(const std::string& name);

#endif
