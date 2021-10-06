#ifndef _H_HOOKING_H_
#define _H_HOOKING_H_
#ifndef _M_AMD64
#ifndef _M_ARM64
#error This application only supports the amd64 or ARM64 architectures. Compilation aborted.
#endif
#endif
#define STRAT_REPLACE_ANY_TYPE_OF_JUMP_WITH_NOP 0
#define STRAT_REPLACE_ANY_TYPE_OF_JUMP_WITH_ALWAYS_JUMP 1
#define HOOK_WITH_FUNCHOOK 0
#define HOOK_WITH_DETOURS 1
#define HOW_TO_HOOK HOOK_WITH_DETOURS
#if HOW_TO_HOOK == HOOK_WITH_FUNCHOOK
#ifdef _M_ARM64
#error Cannot compile for ARM64 using funchook. Change the source to hook with Detours and try again. Compilation aborted.
#endif
#include <funchook.h>
#include <distorm.h>
#pragma comment(lib, "funchook.lib")
#pragma comment(lib, "Psapi.lib") // required by funchook
#pragma comment(lib, "distorm.lib")
#elif HOW_TO_HOOK == HOOK_WITH_DETOURS
#include <detours.h>
#pragma comment(lib, "detours.lib")
void* funchook_create(void)
{
    return 1;
}
int funchook_uninstall(
    void* _this,
    int flags
)
{
    return 0;
}
int funchook_destroy(void* _this)
{
    return 0;
}
int funchook_prepare(
    void* funchook,
    void** target_func,
    void* hook_func
)
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(target_func, hook_func);
    return DetourTransactionCommit();
}
int funchook_install(
    void* funchook,
    int flags
)
{
    return 0;
}
#endif
#if HOW_TO_HOOK == HOOK_WITH_FUNCHOOK
funchook_t* funchook = 0;
#elif HOW_TO_HOOK == HOOK_WITH_DETOURS
void* funchook = 0;
#endif
#endif