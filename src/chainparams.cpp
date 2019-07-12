// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The bitcoinpay developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "bignum.h"
#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

static uint32_t fGenTime = 1560808800; //Monday, 17 June 2019 23:00:00 GMT+01:00

void MineGenesis(CBlock genesis) {

	printf("Searching for main net genesis block...\n");
	uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
	uint256 thash;

	while (true)
	{
	thash = genesis.GetHash();
	if (thash <= hashTarget)
	    break;
	if ((genesis.nNonce & 0xFFF) == 0)
	{
	    printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
	}
	++genesis.nNonce;
	if (genesis.nNonce == 0)
	{
	    printf("NONCE WRAPPED, incrementing time\n");
	    ++genesis.nTime;
	}
	}
	printf("genesis.nTime = %u \n", genesis.nTime);
	printf("genesis.nNonce = %u \n", genesis.nNonce);
	printf("genesis.nVersion = %u \n", genesis.nVersion);
	printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str()); //first this, then comment this line out and uncomment the one under.
	printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str()); //improvised. worked for me, to find merkle root


}


/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
	(0, uint256("0x00000cb1d8c42b59b495d1b46f7b202b3623c1c78a9e796c604f9134f47675d8"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1560808800, // * UNIX timestamp of last checkpoint block
    1,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
	(0, uint256("0x00000c69bcbe76f8bd800c04728c0f22f1bd6eb1c14ecfbae6bb869de3389312"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1560808800,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
	(0, uint256("0x22343e4b610a54eb65e9a35c578eed3264a821209b2b2a124d4b08768dfa5b41"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1560808800,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        
		pchMessageStart[0] = 0xa2;
        pchMessageStart[1] = 0x23;
        pchMessageStart[2] = 0xc5;
        pchMessageStart[3] = 0x46;
        vAlertPubKey = ParseHex("04397ef02c67dd66fce78fdd72cd58d26c2f5a7da23f15c029463297ca776d2e6b5e123280b9970fd060d2e5a89154334978ec8d250ad6d7afa809b833b22cbaaa");
        nDefaultPort = 12568;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // bitcoinpay starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 9999999;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // bitcoinpay: 
        nTargetSpacing = 1 * 60;  // bitcoinpay: 1 minute
        nLastPOWBlock = 1000; // extend PoW run to help setup the network
        nMaturity = 30;
        nStakeMinAge = 60 * 60 * 8;
        nMasternodeCountDrift = 20;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 21000000 * COIN;
        nModifierInterval = 60;
        nModifierIntervalRatio = 3;
        nRequiredMasternodeCollateral = 10000 * COIN;

        const char* pszTimestamp = "BBC News 17th June 2019: Egypt's ousted president Mohammed Morsi dies during trial";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("040860819ec4501e4c8df9588d79fd1653302cf6a3758bb75f7b9055cbf5aafa360b9dec03d171aaa0bd0eea195534f38784b80c76520ff214d6769ca312e18d79") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = fGenTime;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 7536146;
		
        hashGenesisBlock = genesis.GetHash();
	 	//MineGenesis(genesis);
        assert(hashGenesisBlock == uint256("00000cb1d8c42b59b495d1b46f7b202b3623c1c78a9e796c604f9134f47675d8"));
        assert(genesis.hashMerkleRoot == uint256("0902e0dc146fd0f6c6bceac1e1f0106e5314ac3767278ccda808670ae44fbdb9"));


        //vFixedSeeds.clear();
        //vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("seed1.bitcoin-pay.io", "seed1.bitcoin-pay.io"));
        vSeeds.push_back(CDNSSeedData("seed2.bitcoin-pay.io", "seed2.bitcoin-pay.io"));


        // BitcoinPay addresses start with '1'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 0); // 1
        // BitcoinPay script addresses start with '3'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 6);
        // BitcoinPay private keys start with 'K'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 128);
        // BitcoinPay BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // BitcoinPay BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // BitcoinPay BIP44 coin type is '222' (0x800000de)
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xde).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04A9DCD59BE57EA44E65E672DF6F32C25B0671AE19C21B08C068C7DCFD2CF1639FF132E8FF1269D74D7448712CBC1D168761EC70F9F39E756086C9BDBA159B407E";
        strObfuscationPoolDummyAddress = "BpBXVv2LMB6pRUboFqCYwUACCa8oKHQyqn";
        nStartMasternodePayments = 2403728576;
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x16;
        pchMessageStart[1] = 0x55;
        pchMessageStart[2] = 0x34;
        pchMessageStart[3] = 0x23;
        vAlertPubKey = ParseHex("04bc5ca756ed2fb7faf5998d68f196f951b79880e186324e80f92cf1f9ae70bfd8bbac8d74c62eb83927d2ccc0cfe8c193ba3408cd577a5214019ac156643eeb75");
        nDefaultPort = 22568;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // BitcoinPay: 1 day
        nTargetSpacing = 2 * 60;  // BitcoinPay: 1 minute
        nLastPOWBlock = 200;
        nStakeMinAge = 10 * 60;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 21000000 * COIN;
        nRequiredMasternodeCollateral = 10000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = fGenTime;
        genesis.nNonce = 23455158;

		//MineGenesis(genesis);

		hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("00000c69bcbe76f8bd800c04728c0f22f1bd6eb1c14ecfbae6bb869de3389312"));
        assert(genesis.hashMerkleRoot == uint256("0902e0dc146fd0f6c6bceac1e1f0106e5314ac3767278ccda808670ae44fbdb9"));


        vFixedSeeds.clear();
        vSeeds.clear();

        // Testnet BitcoinPay addresses start with 'g'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 98);
        // Testnet BitcoinPay script addresses start with '5' or '6'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 12);
        // Testnet private keys start with 'k'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 233);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet BitcoinPay BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet BitcoinPay BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet bitcoinpay BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "049823802EFB8A72D9C677AFD111ADD147E1D9066D01096DD092ED1166BB49EE56BE80DF1D6826E316D0C3908C1FC3EDA929C18CA56941A251EEFCB6A18D23B608";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nStartMasternodePayments = 1420837558; //
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa2;
        pchMessageStart[1] = 0xc7;
        pchMessageStart[2] = 0x74;
        pchMessageStart[3] = 0xa6;
        nSubsidyHalvingInterval = 150;
		nDefaultPort = 32568;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Pivx: 1 day
        nTargetSpacing = 1 * 60;        // Pivx: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = fGenTime;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 12346;

        // MineGenesis(genesis);
        hashGenesisBlock = genesis.GetHash();
		assert(hashGenesisBlock == uint256("22343e4b610a54eb65e9a35c578eed3264a821209b2b2a124d4b08768dfa5b41"));
        assert(genesis.hashMerkleRoot == uint256("0902e0dc146fd0f6c6bceac1e1f0106e5314ac3767278ccda808670ae44fbdb9"));
        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
