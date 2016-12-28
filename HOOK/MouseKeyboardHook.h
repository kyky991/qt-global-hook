#ifndef MOUSEKEYBOARDHOOK_H
#define MOUSEKEYBOARDHOOK_H


#ifdef HOOK_EXPORTS
#define MOUSEKEYBOARDHOOK_API __declspec(dllexport)  
#else
#define MOUSEKEYBOARDHOOK_API __declspec(dllimport)  
#endif


#include <Windows.h>

extern "C" MOUSEKEYBOARDHOOK_API int SetHook(HWND main);
extern "C" MOUSEKEYBOARDHOOK_API int UnSetHook(void);


#endif //MOUSEKEYBOARDHOOK