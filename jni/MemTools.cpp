#include "PeachPatch/MemTools.h"
#include <sys/mman.h>
#include <unistd.h>
#include <algorithm>
#include <sstream>

#define _SYS_PAGE_SIZE_ (sysconf(_SC_PAGE_SIZE))
#define _PAGE_START_OF_(x) ((ulong)x & ~(ulong)(_SYS_PAGE_SIZE_ - 1))
#define _PAGE_END_OF_(x, len) (_PAGE_START_OF_((ulong)x + len - 1))
#define _PAGE_LEN_OF_(x, len) (_PAGE_END_OF_(x, len) - _PAGE_START_OF_(x) + _SYS_PAGE_SIZE_)
#define _PAGE_OFFSET_OF_(x) ((ulong)x - _PAGE_START_OF_(x))
#define _PROT_RWX_ (PROT_READ | PROT_WRITE | PROT_EXEC)
#define _PROT_RX_ (PROT_READ | PROT_EXEC)

using namespace Peach;

// 更改目标地址权限
bool MemTools::SetProtectAddr(const void *addr, const ulong len, const int prot)
{
    ulong pageStart = _PAGE_START_OF_(addr);
    ulong pageLen = _PAGE_LEN_OF_(addr, len);
    return (mprotect((void *)pageStart, pageLen, prot) != -1);
}

// 写入内存
MemTools::Status MemTools::Write(void *addr, const void *buffer, const ulong len)
{
    if (addr == nullptr || buffer == nullptr || len == 0)
        return INV_DATA;

    if (!SetProtectAddr(addr, len, _PROT_RWX_))
        return INV_PROT;

    if (memcpy(addr, buffer, len) && SetProtectAddr(addr, len, _PROT_RX_))
        return SUCCESS;

    return FAILED;
}

// 读取内存
MemTools::Status MemTools::Read(const void *addr, void *buffer, const ulong len)
{
    if (addr == nullptr || buffer == nullptr || len == 0)
        return INV_DATA;

    if (memcpy(buffer, addr, len))
        return SUCCESS;

    return FAILED;
}

// 读取内存通过Hex字符串
void MemTools::Read4Hex(const std::string &xstr, void *const buffer)
{
    auto byte = (uchar *)buffer;

    std::stringstream stream;
    stream >> std::hex;
    for (ulong i = 0, j = 0; i < xstr.length(); ++j)
    {
        const char tmp[3] = {xstr[i++], xstr[i++], 0};

        stream.clear();
        stream.str(tmp);

        ulong value = 0;
        stream >> value;
        byte[j] = (uchar)value;
    }
}

// 读取内存到Hex字符串
std::string MemTools::Read2Hex(const void *addr, const ulong len)
{
    char tmp[len];
    memset(tmp, 0, len);

    char buffer[len * 2 + 1];
    memset(buffer, 0, len * 2 + 1);

    if (Read(addr, tmp, len) != SUCCESS)
        return std::string("0xInvalid");

    for (ulong i = 0; i < len; ++i)
        snprintf(&buffer[i * 2], 3, "%02X", tmp[i]);

    return std::string(buffer);
}

// 验证字符串是否为Hex
bool MemTools::IsHexStr(std::string &xstr)
{
    if (xstr.length() < 2)
        return false;

    //清除字符串内的空格
    xstr.erase(std::remove_if(xstr.begin(), xstr.end(), [](char c) { return c == ' '; }));

    if (xstr.length() % 2 != 0)
        return false;

    for (uchar c : xstr)
        if (!std::isxdigit(c))
            return false;

    return true;
}
