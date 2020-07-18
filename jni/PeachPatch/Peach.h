#pragma once

#include "PeachMemory.h"

// 地址获取Patch实例 用于快速提取还原内存
Peach::PeachMemory &PeachPatch(ulong absAddr);

// 标准Patch构建
Peach::PeachMemory &PeachPatch(ulong absAddr, const void *patchCode, ulong patchSize);

// Hex字符串构建
Peach::PeachMemory &PeachPatch(ulong absAddr, std::string hex);
