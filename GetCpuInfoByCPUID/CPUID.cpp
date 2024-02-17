#include "CPUID.h"

static unsigned int NextLog2(long long x) {
    if (x <= 0)
        return 0;

    x--;
    unsigned count = 0;
    while (x > 0) {
        x >>= 1;
        count++;
    }

    return count;
}

InstructionSet::InstructionSet() {
    Update();
}

void InstructionSet::Update()
{
    //int cpuInfo[4] = {-1};
    std::array<int, 4> cpui;

    // Calling __cpuid with 0x0 as the function_id argument
    // gets the number of the highest valid function ID.
    __cpuid(cpui.data(), 0);
    nIds_ = cpui[0];

    for (int i = 0; i <= nIds_; ++i) {
        __cpuidex(cpui.data(), i, 0);
        data_.push_back(cpui);
    }

    // Capture vendor string
    char vendor[0x20];
    memset(vendor, 0, sizeof(vendor));
    *reinterpret_cast<int*>(vendor) = data_[0][1];
    *reinterpret_cast<int*>(vendor + 4) = data_[0][3];
    *reinterpret_cast<int*>(vendor + 8) = data_[0][2];
    vendor_ = vendor;
    if (vendor_ == "GenuineIntel") {
        isIntel_ = true;
    }
    else if (vendor_ == "AuthenticAMD") {
        isAMD_ = true;
    }

    // load bitset with flags for function 0x00000001
    if (nIds_ >= 1) {
        f_1_ECX_ = data_[1][2];
        f_1_EDX_ = data_[1][3];

        family_ = ((data_[1][0] & 0x0FF00000) >> 20) +
            ((data_[1][0] & 0x0F00) >> 8);
        model_ = ((data_[1][0] & 0x0F0000) >> 12) +
            ((data_[1][0] & 0xF0) >> 4);
        stepping_ = (data_[1][0] & 0x0F);
        apicId_ = (data_[1][1] >> 24) & 0xFF;
        type_ = (data_[1][0] & 0xF00) >> 12;

        unsigned int maxCoreAndThreadIdPerPackage = (data_[1][1] >> 16) & 0xFF;
        unsigned int maxCoreIdPerPackage = 1;
        if (nIds_ >= 4) {
            maxCoreIdPerPackage = ((data_[4][0] >> 26) & 0x3F) + 1;
        }

        unsigned int threadMaskWith =
            NextLog2(maxCoreAndThreadIdPerPackage / maxCoreIdPerPackage);
        unsigned int coreMaskWith = NextLog2(maxCoreIdPerPackage);

        processorId_ = (apicId_ >> (int)(coreMaskWith + threadMaskWith));
        coreId_ = ((apicId_ >> (int)(threadMaskWith))
            - (processorId_ << (int)(coreMaskWith)));
        threadId_ = apicId_
            - (processorId_ << (int)(coreMaskWith + threadMaskWith))
            - (coreId_ << (int)(threadMaskWith));
    }

    // load bitset with flags for function 0x00000007
    if (nIds_ >= 7) {
        f_7_EBX_ = data_[7][1];
        f_7_ECX_ = data_[7][2];
    }

    if (nIds_ >= 22) {
        basicClockSpeed_ = data_[22][0];
        maxClockSpeed_ = data_[22][1];
        busSpeed_ = data_[22][2];
    }

    // Calling __cpuid with 0x80000000 as the function_id argument
    // gets the number of the highest valid extended ID.
    __cpuid(cpui.data(), 0x80000000);
    nExIds_ = cpui[0];

    char brand[0x40];
    memset(brand, 0, sizeof(brand));

    for (int i = 0x80000000; i <= nExIds_; ++i) {
        __cpuidex(cpui.data(), i, 0);
        extdata_.push_back(cpui);
    }

    // load bitset with flags for function 0x80000001
    if (nExIds_ >= 0x80000001) {
        f_81_ECX_ = extdata_[1][2];
        f_81_EDX_ = extdata_[1][3];
    }

    // Interpret CPU brand string if reported
    if (nExIds_ >= 0x80000004) {
        memcpy(brand, extdata_[2].data(), sizeof(cpui));
        memcpy(brand + 16, extdata_[3].data(), sizeof(cpui));
        memcpy(brand + 32, extdata_[4].data(), sizeof(cpui));
        brand_ = brand;
    }
}