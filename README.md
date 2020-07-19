# PEACH PATCH

自用的 Android Patch 模块

自带 map 用于快速获取 Patch 实例

以 `绝对地址` 为 Key 进行优化性能, 减少不必要的操作

## ABI 支持

- [x] armeabi-v7a
- [ ] arm64-v8a
- [ ] x86

## 使用方法

```c++
#include <PeachPatch/Peach.h>

//armeabi-v7a 的 NOP 指令
const ulong NOP = 0xE320F000;

//假定地址
ulong addr = 0x00000000;

//标准构建方式
auto patch = PeachPatch(addr, (const void *)&NOP, 4);
auto patch = PeachPatch(addr, "\x00\xF0\x20\xE3", 4);

//Hex字符串构建
auto patch = PeachPatch(addr, "00F020E3");
auto patch = PeachPatch(addr, "00 F0 20 E3");//可以带空格

//执行patch
patch.Patch();

//获取目标地址当前Hex字符串
patch.get_CurrHex();

//还原修改
patch.Rebase();
```

> 本项目借鉴于 [KittyMemory](https://github.com/MJx0/KittyMemory)
