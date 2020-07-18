#include "PeachPatch/Peach.h"
using namespace Peach;

// 地址获取Patch实例 用于快速提取还原内存
PeachMemory &PeachPatch(ulong absAddr)
{
    return *PeachMap.at(absAddr);
}

// 标准Patch构建
PeachMemory &PeachPatch(ulong absAddr, const void *patchCode, ulong patchSize)
{
    auto patch = new PeachMemory(absAddr, patchCode, patchSize);
    PeachMap.insert_or_assign(absAddr, patch); //懒得写判断是否已经存在, 性能要紧
    return *patch;
}

// Hex字符串构建
PeachMemory &PeachPatch(ulong absAddr, std::string hex)
{
    auto patch = new PeachMemory(absAddr, hex);
    PeachMap.insert_or_assign(absAddr, patch);
    return *patch;
}
