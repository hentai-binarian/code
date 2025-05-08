#include <windows.h>
#include <stdio.h>
#include "MinHook.h"

typedef int (WINAPI *MESSAGEBOXA)(HWND, LPCSTR, LPCSTR, UINT);
MESSAGEBOXA Real_MessageBoxA = NULL;

int WINAPI My_MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) {
    return Real_MessageBoxA(hWnd, "fuckyou", "fuckyou", uType);
}

int main() {
    // 初期化
    if (MH_Initialize() != MH_OK) return 1;

    // フック作成
    if (MH_CreateHook(&MessageBoxA, &My_MessageBoxA, (LPVOID*)&Real_MessageBoxA) != MH_OK)
        return 1;

    // フック有効化
    if (MH_EnableHook(&MessageBoxA) != MH_OK) return 1;

    // 呼び出し（ここでフックが働く）
    MessageBoxA(NULL, "hello", "hello", MB_OK);

    // 無効化と終了処理
    MH_DisableHook(&MessageBoxA);
    MH_Uninitialize();

    return 0;
}

