#include "PeachPatch/PeachMemory.h"
using namespace Peach;

// 标准构建
PeachMemory::PeachMemory(ulong absAddr, const void *patchCode, ulong patchSize)
{
    if (absAddr == 0 || patchCode == nullptr || patchSize == 0)
        return;

    this->_adderss = absAddr;
    this->_size = patchSize;

    this->_orig.resize(patchSize);
    this->_patch.resize(patchSize);

    MemTools::Read(patchCode, &this->_patch[0], patchSize);
    MemTools::Read(absAddr, &this->_orig[0], patchSize);
}

// 字符串HEX构建
PeachMemory::PeachMemory(ulong abs_addr, std::string xstr)
{
    if (abs_addr == 0 || !MemTools::IsHexStr(xstr))
        return;

    this->_adderss = abs_addr;
    this->_size = xstr.length() / 2;

    this->_orig.resize(_size);
    this->_patch.resize(_size);

    MemTools::Read4Hex(xstr, &this->_patch[0]);
    MemTools::Read(abs_addr, &this->_orig[0], _size);
}

// 获取当前HEX字符串
const std::string PeachMemory::get_CurrHex() const
{
    if (!isValid())
        return std::string("0xInvalid");
    else
        return MemTools::Read2Hex(this->_adderss, this->_size);
}

// Patch内存
bool PeachMemory::Patch()
{
    if (!isValid())
        return false;

    return MemTools::Write(this->_adderss, &this->_patch[0], this->_size) == MemTools::SUCCESS;
}

// 还原内存
bool PeachMemory::Rebase()
{
    if (!isValid())
        return false;

    return MemTools::Write(this->_adderss, &this->_orig[0], this->_size) == MemTools::SUCCESS;
}
