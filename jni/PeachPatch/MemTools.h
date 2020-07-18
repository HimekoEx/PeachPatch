#pragma once

#include <string>

//类型自定义
typedef unsigned long ulong;
typedef unsigned char uchar;

namespace Peach
{

    // 内存工具库
    struct MemTools
    {
        // 状态
        typedef enum
        {
            SUCCESS = 0,
            FAILED = 1,
            INV_DATA = 2,
            INV_PROT = 3
        } Status;

        // 更改目标地址权限
        static bool SetProtectAddr(const void *addr, const ulong len, const int prot);

        // 写入内存
        static Status Write(void *addr, const void *buffer, const ulong len);
        static Status Write(ulong addr, const void *buffer, const ulong len) { return Write((void *)addr, buffer, len); }

        // 读取内存
        static Status Read(const void *addr, void *buffer, const ulong len);
        static Status Read(const ulong addr, void *buffer, const ulong len) { return Read((const void *)addr, buffer, len); }

        // 读取内存通过Hex字符串
        static void Read4Hex(const std::string &xstr, void *const buffer);

        // 读取内存到Hex字符串
        static std::string Read2Hex(const void *addr, const ulong len);
        static std::string Read2Hex(const ulong addr, const ulong len) { return Read2Hex((const void *)addr, len); }

        // 验证字符串是否为Hex
        static bool IsHexStr(std::string &xstr);
    };

}; // namespace Peach
