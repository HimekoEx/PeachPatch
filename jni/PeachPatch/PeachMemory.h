#pragma once

#include "MemTools.h"
#include <vector>
#include <map>

namespace Peach
{

    // 内存Patch模块
    class PeachMemory
    {
    private:
        //基础信息
        ulong _adderss = 0;
        ulong _size = 0;

        //code信息
        std::vector<uchar> _orig;
        std::vector<uchar> _patch;

    public:
        // 标准构建
        PeachMemory(ulong absAddr, const void *patchCode, ulong patchSize);

        // Hex字符串构建
        PeachMemory(ulong absAddr, std::string hex);

        // 判断该MemoryPath否有效
        bool isValid() const { return (_adderss && _size && _orig.size() == _size && _patch.size() == _size); }

        // 获取patch地址
        ulong get_adderss() const { return _adderss; }

        // 获取code长度
        ulong get_size() const { return _size; }

        // 获取当前HEX字符串
        const std::string get_CurrHex() const;

        // Patch内存
        bool Patch();

        // 还原内存
        bool Rebase();
    };

    //全局Patch备份
    static std::map<ulong, PeachMemory *> PeachMap;

}; // namespace Peach
