// Copyright (c) 2020 The PIVX developers
// Copyright (c) 2021 The INFAQCOIN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://www.opensource.org/licenses/mit-license.php.

#ifndef INFAQCOIN_SAPLING_TEST_FIXTURE_H
#define INFAQCOIN_SAPLING_TEST_FIXTURE_H

#include "test/test_infaqcoin.h"

/**
 * Testing setup that configures a complete environment for Sapling testing.
 */
struct SaplingTestingSetup : public TestingSetup {
    SaplingTestingSetup();
    ~SaplingTestingSetup();
};


#endif //INFAQCOIN_SAPLING_TEST_FIXTURE_H
