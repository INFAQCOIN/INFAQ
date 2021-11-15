// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021 The INFAQCOIN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "chainparamsseeds.h"
#include "consensus/merkle.h"
#include "tinyformat.h"
#include "utilstrencodings.h"

#include <assert.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.vtx.push_back(std::make_shared<const CTransaction>(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.nVersion = nVersion;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

void CChainParams::UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
    assert(IsRegTestNet()); // only available for regtest
    assert(idx > Consensus::BASE_NETWORK && idx < Consensus::MAX_NETWORK_UPGRADES);
    consensus.vUpgrades[idx].nActivationHeight = nActivationHeight;
}

/**
 * Build the genesis block. Note that the output of the genesis coinbase cannot
 * be spent as it did not originally exist in the database.
 *
 * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
 *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
 *   vMerkleTree: e0028e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "The rest of the cryptocurrency market remain watchful of the moves in BTC and ETH";
    const CScript genesisOutputScript = CScript() << ParseHex("04c10e83c3713ccf322a7dbd62da5815ac7c10db055814ce121ba72607d572b8810c02c05b2aed05b4dab9c4b77b26d92428c61256cd42774abbea0a037b2ed0c4") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
static Checkpoints::MapCheckpoints mapCheckpoints = {
     {0, uint256S("00000e595337ec9d495e4ca45b5db833ffec3e70ac639d06e3c003e90e5b14b0")}, 
     {1, uint256S("000006a0f2d96723b45b6d3cbd76a442227b0c0e882fc5f78a5530931665b0c5")}, 
     {849, uint256S("000001de5bb2c81e78f06dc2adb29f3ac087642c5ef489c05101cf5f45d470cc")}, 
     {1806, uint256S("6a9d31e6c98a00e2c0a3d903ee0d8576feaef67489a708eec6b5521e9d85803d")}, 
     {2517, uint256S("0f8dc57a97329f4a2ce671ec0a369e642110751784694352a3eb79ace7c84ea5")}, 
     {4253, uint256S("ead97e99fdb9ab769bd13e714676d4ac360bbb104ae464821149e3ed70cfee9f")}, 
     {5964, uint256S("a5371d9960e94b10ec3c2ecd899d1f51aba7d5dd6f763a6323aa4c7406a12c9d")}, 
     {7731, uint256S("bbd86f53ccc7ed096f2361e5dac2bef53b414ad587f396bc6df39f5fa5bb81ee")}, 
     {8469, uint256S("cf24d32693898f063e17170f6b6496c91aa619d9584c6ee6de76e6aaacedb412")}, 
     {10581, uint256S("4987781a7df32ee75578bb05f3480b2a5370c6cdb76ed128316e2826a8206521")}, 
     {12759, uint256S("3d91a19814f3c2431cdfe5b8b99d497343ceb901c665b7484223195625e4f135")}, 

};

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1636936620, // * UNIX timestamp of last checkpoint block
    25022,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    3000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet = {
    {0, uint256S("0x")},

};

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1627545600,
    0,
    3000};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest = {{0, uint256S("0x001")}};
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        strNetworkID = "main";

         genesis = CreateGenesisBlock(1635325200, 558844, 0x1e0ffff0, 1, 0);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000e595337ec9d495e4ca45b5db833ffec3e70ac639d06e3c003e90e5b14b0"));
        assert(genesis.hashMerkleRoot == uint256S("0xe8d8813be69b6f0cd3193d8ee007539bf57c0cbee108635ea8d28ad7a9b60579")); 

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // INFAQCOIN starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 43200;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 60;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 100000000000 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 60;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 2 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.nMaxProposalPayments = 6;


        // spork keys
        consensus.strSporkPubKey = "04c71695ae0b584bf78bc5118e3553defd6d2fa58c8d4c642da0fc0056a0dff428a9420be51a0ea5a77b880cfda72c1bde18a7f7a753ca4dad2cd10ff7e09971b0";
        consensus.strSporkPubKeyOld = "04c71695ae0b584bf78bc5118e3553defd6d2fa58c8d4c642da0fc0056a0dff428a9420be51a0ea5a77b880cfda72c1bde18a7f7a753ca4dad2cd10ff7e09971b0";
        consensus.nTime_EnforceNewSporkKey = 1635400800;    //!> Thursday, 28 October 2021 6:00:00 AM GMT
        consensus.nTime_RejectOldSporkKey = 1635494400;     //!> Friday, 29 October 2021 8:00:00 AM GMT


        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 1;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         = 1300;
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight          = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight          = 1100;
        consensus.vUpgrades[Consensus::UPGRADE_V5_0].nActivationHeight          = 1300;
        consensus.vUpgrades[Consensus::UPGRADE_V5_2].nActivationHeight          = 1300;

        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock =
                uint256S("0x");
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].hashActivationBlock =
                uint256S("0x");
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].hashActivationBlock =
                uint256S("0x");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcb;
        pchMessageStart[2] = 0x4d;
        pchMessageStart[3] = 0xc7;
        nDefaultPort = 17060;

        // Note that of those with the service bits flag, most only support a subset of possible options
         vSeeds.emplace_back("192.95.46.160", "192.95.46.160", true); 
         vSeeds.emplace_back("2607:5300:60:72b5::160", "2607:5300:60:72b5::160", true);   
         vSeeds.emplace_back("192.95.46.161", "192.95.46.161", true);   
         vSeeds.emplace_back("2607:5300:60:72b5::161", "2607:5300:60:72b5::161", true);   
         vSeeds.emplace_back("192.95.46.162", "192.95.46.162", true);   
         vSeeds.emplace_back("2607:5300:60:72b5::162", "2607:5300:60:72b5::162", true);   
         vSeeds.emplace_back("192.95.46.164", "192.95.46.164", true);   
         vSeeds.emplace_back("2607:5300:60:72b5::164", "2607:5300:60:72b5::164", true);   
         vSeeds.emplace_back("192.95.46.165", "192.95.46.165", true);   
         vSeeds.emplace_back("2607:5300:60:72b5::165", "2607:5300:60:72b5::165", true);   
         vSeeds.emplace_back("192.95.46.166", "192.95.46.166", true);   
         vSeeds.emplace_back("2607:5300:60:72b5::166", "2607:5300:60:72b5::166", true);   
         vSeeds.emplace_back("192.95.46.167", "192.95.46.167", true);   
         vSeeds.emplace_back("2607:5300:60:72b5::167", "2607:5300:60:72b5::167", true);   
         vSeeds.emplace_back("192.95.46.168", "192.95.46.168", true);   
         vSeeds.emplace_back("2607:5300:60:72b5::168", "2607:5300:60:72b5::168", true);   
         vSeeds.emplace_back("192.95.46.169", "192.95.46.169", true);   
         vSeeds.emplace_back("2607:5300:60:72b5::169", "2607:5300:60:72b5::169", true);   
         vSeeds.emplace_back("192.95.46.170", "192.95.46.170", true);   
         vSeeds.emplace_back("2607:5300:60:72b5::170", "2607:5300:60:72b5::170", true);   
         vSeeds.emplace_back("192.95.46.171", "192.95.46.171", true);   
         vSeeds.emplace_back("2607:5300:60:72b5::171", "2607:5300:60:72b5::171", true);   
         vSeeds.emplace_back("192.95.46.172", "192.95.46.172", true);   
         vSeeds.emplace_back("2607:5300:60:72b5::172", "2607:5300:60:72b5::172", true);   
         vSeeds.emplace_back("192.95.46.173", "192.95.46.173", true);   
         vSeeds.emplace_back("2607:5300:60:72b5::173", "2607:5300:60:72b5::173", true);   
         vSeeds.emplace_back("192.95.46.174", "192.95.46.174", true);   
         vSeeds.emplace_back("2607:5300:60:72b5::174", "2607:5300:60:72b5::174", true);   
         vSeeds.emplace_back("192.95.46.175", "192.95.46.175", true);   
         vSeeds.emplace_back("2607:5300:60:72b5::175", "2607:5300:60:72b5::175", true);   
 

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 103);		// starting with 'i'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 58);     // starting with 'Q'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x02, 0x2D, 0x25, 0x33};
        base58Prefixes[EXT_SECRET_KEY] = {0x02, 0x21, 0x31, 0x2B};
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = {0x80, 0x00, 0x00, 0x77};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        // Sapling
        bech32HRPs[SAPLING_PAYMENT_ADDRESS]      = "is";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY]     = "iviews";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "iqcks";
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY]   = "i-secret-spending-key-main";
        bech32HRPs[SAPLING_EXTENDED_FVK]         = "ixviews";
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }

};

/**
 * Testnet (v5)
 */
class CTestNetParams : public CChainParams
{
public:
    CTestNetParams()
    {
        strNetworkID = "test";

        genesis = CreateGenesisBlock(1454124731, 2402015, 0x1e0ffff0, 1, 250 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
      //  assert(consensus.hashGenesisBlock == uint256S("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));
      //  assert(genesis.hashMerkleRoot == uint256S("0x1b2ef6e2f28be914103a277377ae7729dcd125dfeb8bf97bd5964ba72b6dc39b"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // INFAQCOIN starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on testnet)
        consensus.nCoinbaseMaturity = 60;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 20000000 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;  // at least 5 min old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 60;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 2 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.nMaxProposalPayments = 6;

        // spork keys
        consensus.strSporkPubKey = "04677c34726c491117265f4b1c83cef085684f36c8df5a97a3a42fc499316d0c4e63959c9eca0dba239d9aaaf72011afffeb3ef9f51b9017811dec686e412eb504";
        consensus.strSporkPubKeyOld = "04E88BB455E2A04E65FCC41D88CD367E9CCE1F5A409BE94D8C2B4B35D223DED9C8E2F4E061349BA3A38839282508066B6DC4DB72DD432AC4067991E6BF20176127";
        consensus.nTime_EnforceNewSporkKey = 1608512400;    //!> December 21, 2020 01:00:00 AM GMT
        consensus.nTime_RejectOldSporkKey = 1614560400;     //!> March 1, 2021 01:00:00 AM GMT


        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 1;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         = 1300;
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight          = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight          = 1100;
        consensus.vUpgrades[Consensus::UPGRADE_V5_0].nActivationHeight          = 1300;
        consensus.vUpgrades[Consensus::UPGRADE_V5_2].nActivationHeight          = 1300;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa4;
        pchMessageStart[1] = 0xe1;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0x5a;
        nDefaultPort = 11012;

        // nodes with support for servicebits filtering should be at the top
       /* vSeeds.emplace_back(""fuzzbawls.pw", "infaqcoin-testnet.seed.fuzzbawls.pw", true);
        vSeeds.emplace_back(""fuzzbawls.pw", "infaqcoin-testnet.seed.fuzzbawls.pw", true);*/

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet IQC addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 73);     // starting with 'W'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c'
        // Testnet infaqcoin BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = {0x3a, 0x80, 0x61, 0xa0};
        // Testnet infaqcoin BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = {0x3a, 0x80, 0x58, 0x37};
        // Testnet infaqcoin BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = {0x80, 0x00, 0x00, 0x01};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        // Sapling
        bech32HRPs[SAPLING_PAYMENT_ADDRESS]      = "ptestsapling";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY]     = "pviewtestsapling";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "iqcktestsapling";
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY]   = "p-secret-spending-key-test";
        bech32HRPs[SAPLING_EXTENDED_FVK]         = "pxviewtestsapling";
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams
{
public:
    CRegTestParams()
    {
        strNetworkID = "regtest";

        genesis = CreateGenesisBlock(1454124731, 2402015, 0x1e0ffff0, 1, 250 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
   //     assert(consensus.hashGenesisBlock == uint256S("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));
    //    assert(genesis.hashMerkleRoot == uint256S("0x1b2ef6e2f28be914103a277377ae7729dcd125dfeb8bf97bd5964ba72b6dc39b"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // INFAQCOIN starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on regtest)
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 4;        // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
        consensus.nStakeMinAge = 0;
        consensus.nStakeMinDepth = 2;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.nMaxProposalPayments = 20;

        /* Spork Key for RegTest:
        WIF private key: 932HEevBSujW2ud7RfB1YF91AFygbBRQj3de3LyaCRqNzKKgWXi
        private key hex: bd4960dcbd9e7f2223f24e7164ecb6f1fe96fc3a416f5d3a830ba5720c84b8ca
        Address: yCvUVd72w7xpimf981m114FSFbmAmne7j9
        */
        consensus.strSporkPubKey = "043969b1b0e6f327de37f297a015d37e2235eaaeeb3933deecd8162c075cee0207b13537618bde640879606001a8136091c62ec272dd0133424a178704e6e75bb7";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 251;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight          = 251;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight          =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_V5_0].nActivationHeight          = 300;
        consensus.vUpgrades[Consensus::UPGRADE_V5_2].nActivationHeight          = 300;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nDefaultPort = 51476;

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet infaqcoin addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet infaqcoin script addresses start with '8' or '9'
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 73);     // starting with 'W'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet infaqcoin BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = {0x3a, 0x80, 0x61, 0xa0};
        // Testnet infaqcoin BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = {0x3a, 0x80, 0x58, 0x37};
        // Testnet infaqcoin BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = {0x80, 0x00, 0x00, 0x01};

        // Sapling
        bech32HRPs[SAPLING_PAYMENT_ADDRESS]      = "ptestsapling";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY]     = "pviewtestsapling";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "iqcktestsapling";
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY]   = "p-secret-spending-key-test";
        bech32HRPs[SAPLING_EXTENDED_FVK]         = "pxviewtestsapling";
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params()
{
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
    globalChainParams->UpdateNetworkUpgradeParameters(idx, nActivationHeight);
}
