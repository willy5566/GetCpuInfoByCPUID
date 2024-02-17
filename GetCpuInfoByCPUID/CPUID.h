#pragma once
#include <vector>
#include <bitset>
#include <array>
#include <string>
#include <intrin.h>

class InstructionSet {
private:
    int nIds_;
    int nExIds_;
    std::string vendor_;
    std::string brand_;
    bool isIntel_;
    bool isAMD_;
    std::bitset<32> f_1_ECX_;
    std::bitset<32> f_1_EDX_;
    std::bitset<32> f_7_EBX_;
    std::bitset<32> f_7_ECX_;
    std::bitset<32> f_81_ECX_;
    std::bitset<32> f_81_EDX_;
    std::vector<std::array<int, 4>> data_;
    std::vector<std::array<int, 4>> extdata_;
    int stepping_;
    int model_;
    int family_;
    int type_;
    int apicId_;
    int basicClockSpeed_;
    int maxClockSpeed_;
    int busSpeed_;
    int processorId_;
    int coreId_;
    int threadId_;

public:
    InstructionSet();

    // getters
    std::string Vendor(void) { return vendor_; }
    std::string Brand(void) { return brand_; }

    int BasicClockSpeed(void) { return basicClockSpeed_; }
    int MaxClockSpeed(void) { return maxClockSpeed_; }
    int BusSpeed(void) { return busSpeed_; }

    int CoreId(void) { return coreId_; }
    int ProcessorId(void) { return processorId_; }
    int ThreadId(void) { return threadId_; }

    int Family(void) { return family_; }
    int Model(void) { return model_; }
    int Stepping(void) { return stepping_; }
    int ApicId(void) { return apicId_; }
    int Type(void) { return type_; }

    bool SSE3(void) { return f_1_ECX_[0]; }
    bool PCLMULQDQ(void) { return f_1_ECX_[1]; }
    bool MONITOR(void) { return f_1_ECX_[3]; }
    bool SSSE3(void) { return f_1_ECX_[9]; }
    bool FMA(void) { return f_1_ECX_[12]; }
    bool CMPXCHG16B(void) { return f_1_ECX_[13]; }
    bool SSE41(void) { return f_1_ECX_[19]; }
    bool SSE42(void) { return f_1_ECX_[20]; }
    bool MOVBE(void) { return f_1_ECX_[22]; }
    bool POPCNT(void) { return f_1_ECX_[23]; }
    bool AES(void) { return f_1_ECX_[25]; }
    bool XSAVE(void) { return f_1_ECX_[26]; }
    bool OSXSAVE(void) { return f_1_ECX_[27]; }
    bool AVX(void) { return f_1_ECX_[28]; }
    bool F16C(void) { return f_1_ECX_[29]; }
    bool RDRAND(void) { return f_1_ECX_[30]; }

    bool MSR(void) { return f_1_EDX_[5]; }
    bool CX8(void) { return f_1_EDX_[8]; }
    bool SEP(void) { return f_1_EDX_[11]; }
    bool CMOV(void) { return f_1_EDX_[15]; }
    bool CLFSH(void) { return f_1_EDX_[19]; }
    bool MMX(void) { return f_1_EDX_[23]; }
    bool FXSR(void) { return f_1_EDX_[24]; }
    bool SSE(void) { return f_1_EDX_[25]; }
    bool SSE2(void) { return f_1_EDX_[26]; }

    bool FSGSBASE(void) { return f_7_EBX_[0]; }
    bool BMI1(void) { return f_7_EBX_[3]; }
    bool HLE(void) { return isIntel_ && f_7_EBX_[4]; }
    bool AVX2(void) { return f_7_EBX_[5]; }
    bool BMI2(void) { return f_7_EBX_[8]; }
    bool ERMS(void) { return f_7_EBX_[9]; }
    bool INVPCID(void) { return f_7_EBX_[10]; }
    bool RTM(void) { return isIntel_ && f_7_EBX_[11]; }
    bool AVX512F(void) { return f_7_EBX_[16]; }
    bool RDSEED(void) { return f_7_EBX_[18]; }
    bool ADX(void) { return f_7_EBX_[19]; }
    bool AVX512PF(void) { return f_7_EBX_[26]; }
    bool AVX512ER(void) { return f_7_EBX_[27]; }
    bool AVX512CD(void) { return f_7_EBX_[28]; }
    bool SHA(void) { return f_7_EBX_[29]; }

    bool PREFETCHWT1(void) { return f_7_ECX_[0]; }

    bool LAHF(void) { return f_81_ECX_[0]; }
    bool LZCNT(void) { return isIntel_ && f_81_ECX_[5]; }
    bool ABM(void) { return isAMD_ && f_81_ECX_[5]; }
    bool SSE4a(void) { return isAMD_ && f_81_ECX_[6]; }
    bool XOP(void) { return isAMD_ && f_81_ECX_[11]; }
    bool TBM(void) { return isAMD_ && f_81_ECX_[21]; }

    bool SYSCALL(void) { return isIntel_ && f_81_EDX_[11]; }
    bool MMXEXT(void) { return isAMD_ && f_81_EDX_[22]; }
    bool RDTSCP(void) { return isIntel_ && f_81_EDX_[27]; }
    bool _3DNOWEXT(void) { return isAMD_ && f_81_EDX_[30]; }
    bool _3DNOW(void) { return isAMD_ && f_81_EDX_[31]; }
    void Update();
};

