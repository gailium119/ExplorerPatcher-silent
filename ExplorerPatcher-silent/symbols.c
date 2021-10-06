#include "symbols.h"

const char* twinui_pcshell_SN[TWINUI_PCSHELL_SB_CNT] = {
    TWINUI_PCSHELL_SB_0,
    TWINUI_PCSHELL_SB_1,
    TWINUI_PCSHELL_SB_2,
    TWINUI_PCSHELL_SB_3,
    TWINUI_PCSHELL_SB_4,
    TWINUI_PCSHELL_SB_5,
    TWINUI_PCSHELL_SB_6,
    TWINUI_PCSHELL_SB_7
};
const char* startdocked_SN[STARTDOCKED_SB_CNT] = {
    STARTDOCKED_SB_0,
    STARTDOCKED_SB_1,
    STARTDOCKED_SB_2,
    STARTDOCKED_SB_3,
    STARTDOCKED_SB_4
};



DWORD DownloadSymbols(DownloadSymbolsParams* params)
{
    HKEY hKey;
    DWORD dwDisposition;

    HMODULE hModule = params->hModule;

    Sleep(3000);

    printf("Started \"Download symbols\" thread.\n");

    RTL_OSVERSIONINFOW rovi;
    DWORD32 ubr = VnGetOSVersionAndUBR(&rovi);
    TCHAR szReportedVersion[MAX_PATH + 1];
    ZeroMemory(
        szReportedVersion,
        (MAX_PATH + 1) * sizeof(TCHAR)
    );
    wsprintf(
        szReportedVersion,
        L"%d.%d.%d.%d",
        rovi.dwMajorVersion,
        rovi.dwMinorVersion,
        rovi.dwBuildNumber,
        ubr
    );

    


    char szSettingsPath[MAX_PATH];
    ZeroMemory(
        szSettingsPath,
        MAX_PATH * sizeof(char)
    );
    SHGetFolderPathA(
        NULL,
        SPECIAL_FOLDER,
        NULL,
        SHGFP_TYPE_CURRENT,
        szSettingsPath
    );
    strcat_s(
        szSettingsPath,
        MAX_PATH,
        APP_RELATIVE_PATH
    );
    CreateDirectoryA(szSettingsPath, NULL);
    strcat_s(
        szSettingsPath,
        MAX_PATH,
        "\\"
    );
    printf("Downloading to \"%s\".\n", szSettingsPath);

    symbols_addr symbols_PTRS;
    ZeroMemory(
        &symbols_PTRS,
        sizeof(symbols_addr)
    );




    char twinui_pcshell_sb_dll[MAX_PATH];
    ZeroMemory(
        twinui_pcshell_sb_dll,
        (MAX_PATH) * sizeof(char)
    );
    GetSystemDirectoryA(
        twinui_pcshell_sb_dll,
        MAX_PATH
    );
    strcat_s(
        twinui_pcshell_sb_dll,
        MAX_PATH,
        "\\"
    );
    strcat_s(
        twinui_pcshell_sb_dll,
        MAX_PATH,
        TWINUI_PCSHELL_SB_NAME
    );
    strcat_s(
        twinui_pcshell_sb_dll,
        MAX_PATH,
        ".dll"
    );
    printf("Downloading symbols for \"%s\"...\n", twinui_pcshell_sb_dll);
    if (VnDownloadSymbols(
        NULL,
        twinui_pcshell_sb_dll,
        szSettingsPath,
        MAX_PATH
    ))
    {
        FreeLibraryAndExitThread(
            hModule,
            4
        );
        return 4;
    }
    printf("Reading symbols...\n");
    if (VnGetSymbols(
        szSettingsPath,
        symbols_PTRS.twinui_pcshell_PTRS,
        twinui_pcshell_SN,
        TWINUI_PCSHELL_SB_CNT
    ))
    {
        printf("Hooking Win+C is not available for this build.\n");
        if (VnGetSymbols(
            szSettingsPath,
            symbols_PTRS.twinui_pcshell_PTRS,
            twinui_pcshell_SN,
            TWINUI_PCSHELL_SB_CNT - 1
        ))
        {
            FreeLibraryAndExitThread(
                hModule,
                5
            );
            return 5;
        }
    }
    RegCreateKeyExW(
        HKEY_CURRENT_USER,
        TEXT(REGPATH) L"\\" TEXT(TWINUI_PCSHELL_SB_NAME),
        0,
        NULL,
        REG_OPTION_NON_VOLATILE,
        KEY_WRITE,
        NULL,
        &hKey,
        &dwDisposition
    );
    if (!hKey)
    {
        FreeLibraryAndExitThread(
            hModule,
            9
        );
        return 9;
    }
    RegSetValueExW(
        hKey,
        TEXT(TWINUI_PCSHELL_SB_0),
        0,
        REG_DWORD,
        &(symbols_PTRS.twinui_pcshell_PTRS[0]),
        sizeof(DWORD)
    );
    RegSetValueExW(
        hKey,
        TEXT(TWINUI_PCSHELL_SB_1),
        0,
        REG_DWORD,
        &(symbols_PTRS.twinui_pcshell_PTRS[1]),
        sizeof(DWORD)
    );
    RegSetValueExW(
        hKey,
        TEXT(TWINUI_PCSHELL_SB_2),
        0,
        REG_DWORD,
        &(symbols_PTRS.twinui_pcshell_PTRS[2]),
        sizeof(DWORD)
    );
    RegSetValueExW(
        hKey,
        TEXT(TWINUI_PCSHELL_SB_3),
        0,
        REG_DWORD,
        &(symbols_PTRS.twinui_pcshell_PTRS[3]),
        sizeof(DWORD)
    );
    RegSetValueExW(
        hKey,
        TEXT(TWINUI_PCSHELL_SB_4),
        0,
        REG_DWORD,
        &(symbols_PTRS.twinui_pcshell_PTRS[4]),
        sizeof(DWORD)
    );
    RegSetValueExW(
        hKey,
        TEXT(TWINUI_PCSHELL_SB_5),
        0,
        REG_DWORD,
        &(symbols_PTRS.twinui_pcshell_PTRS[5]),
        sizeof(DWORD)
    );
    RegSetValueExW(
        hKey,
        TEXT(TWINUI_PCSHELL_SB_6),
        0,
        REG_DWORD,
        &(symbols_PTRS.twinui_pcshell_PTRS[6]),
        sizeof(DWORD)
    );
    RegSetValueExW(
        hKey,
        TEXT(TWINUI_PCSHELL_SB_7),
        0,
        REG_DWORD,
        &(symbols_PTRS.twinui_pcshell_PTRS[7]),
        sizeof(DWORD)
    );
    RegCloseKey(hKey);



    char startdocked_sb_dll[MAX_PATH];
    ZeroMemory(
        startdocked_sb_dll,
        (MAX_PATH) * sizeof(char)
    );
    GetWindowsDirectoryA(
        startdocked_sb_dll,
        MAX_PATH
    );
    strcat_s(
        startdocked_sb_dll,
        MAX_PATH,
        "\\SystemApps\\Microsoft.Windows.StartMenuExperienceHost_cw5n1h2txyewy\\"
    );
    strcat_s(
        startdocked_sb_dll,
        MAX_PATH,
        STARTDOCKED_SB_NAME
    );
    strcat_s(
        startdocked_sb_dll,
        MAX_PATH,
        ".dll"
    );
    printf("Downloading symbols for \"%s\"...\n", startdocked_sb_dll);
    if (VnDownloadSymbols(
        NULL,
        startdocked_sb_dll,
        szSettingsPath,
        MAX_PATH
    ))
    {
        FreeLibraryAndExitThread(
            hModule,
            6
        );
        return 6;
    }
    printf("Reading symbols...\n");
    if (VnGetSymbols(
        szSettingsPath,
        symbols_PTRS.startdocked_PTRS,
        startdocked_SN,
        STARTDOCKED_SB_CNT
    ))
    {
        printf("error...\n");
        FreeLibraryAndExitThread(
            hModule,
            7
        );
        return 7;
    }
    RegCreateKeyExW(
        HKEY_CURRENT_USER,
        TEXT(REGPATH) L"\\" TEXT(STARTDOCKED_SB_NAME),
        0,
        NULL,
        REG_OPTION_NON_VOLATILE,
        KEY_WRITE,
        NULL,
        &hKey,
        &dwDisposition
    );
    if (!hKey)
    {
        FreeLibraryAndExitThread(
            hModule,
            8
        );
        return 8;
    }
    RegSetValueExW(
        hKey,
        TEXT(STARTDOCKED_SB_0),
        0,
        REG_DWORD,
        &(symbols_PTRS.startdocked_PTRS[0]),
        sizeof(DWORD)
    );
    RegSetValueExW(
        hKey,
        TEXT(STARTDOCKED_SB_1),
        0,
        REG_DWORD,
        &(symbols_PTRS.startdocked_PTRS[1]),
        sizeof(DWORD)
    );
    RegSetValueExW(
        hKey,
        TEXT(STARTDOCKED_SB_2),
        0,
        REG_DWORD,
        &(symbols_PTRS.startdocked_PTRS[2]),
        sizeof(DWORD)
    );
    RegSetValueExW(
        hKey,
        TEXT(STARTDOCKED_SB_3),
        0,
        REG_DWORD,
        &(symbols_PTRS.startdocked_PTRS[3]),
        sizeof(DWORD)
    );
    RegSetValueExW(
        hKey,
        TEXT(STARTDOCKED_SB_4),
        0,
        REG_DWORD,
        &(symbols_PTRS.startdocked_PTRS[4]),
        sizeof(DWORD)
    );
    RegCloseKey(hKey);






    RegCreateKeyExW(
        HKEY_CURRENT_USER,
        TEXT(REGPATH),
        0,
        NULL,
        REG_OPTION_NON_VOLATILE,
        KEY_WRITE,
        NULL,
        &hKey,
        &dwDisposition
    );
    if (!hKey)
    {
        FreeLibraryAndExitThread(
            hModule,
            10
        );
        return 10;
    }
    RegSetValueExW(
        hKey,
        TEXT("OSBuild"),
        0,
        REG_SZ,
        szReportedVersion,
        wcslen(szReportedVersion) * sizeof(TCHAR)
    );
    RegCloseKey(hKey);


    if (symbols_PTRS.twinui_pcshell_PTRS[0])
    {
        
    }
    else
    {


    }

    Sleep(4000);

    exit(0);
}

BOOL LoadSymbols(symbols_addr* symbols_PTRS)
{
    HKEY hKey;
    DWORD dwDisposition;
    DWORD dwSize = sizeof(DWORD);
    RTL_OSVERSIONINFOW rovi;
    DWORD32 ubr = VnGetOSVersionAndUBR(&rovi);
    switch (rovi.dwBuildNumber) {
    case 22000: {
        switch (ubr) {
        case 1: break;
        case 194: {
            symbols_PTRS->twinui_pcshell_PTRS[0] = 0x214f76;
            symbols_PTRS->twinui_pcshell_PTRS[1] = 0x5ca7b0;
            symbols_PTRS->twinui_pcshell_PTRS[2] = 0x5f40c8;
            symbols_PTRS->twinui_pcshell_PTRS[3] = 0x5f48d0;
            symbols_PTRS->twinui_pcshell_PTRS[4] = 0x5d8e48;
            symbols_PTRS->twinui_pcshell_PTRS[5] = 0x5d8b04;
            symbols_PTRS->twinui_pcshell_PTRS[6] = 0x5cbc00;
            symbols_PTRS->twinui_pcshell_PTRS[7] = 0x4c8a0;
            symbols_PTRS->startdocked_PTRS[0] = 0x188ebc;
            symbols_PTRS->startdocked_PTRS[1] = 0x188ebc;
            symbols_PTRS->startdocked_PTRS[2] = 0x187120;
            symbols_PTRS->startdocked_PTRS[3] = 0x3c10;
            symbols_PTRS->startdocked_PTRS[4] = 0x160aec;
            return FALSE;
            break;
        }
        default:break;
        }
        break;
    }
    default:break;
    }
    RegCreateKeyExW(
        HKEY_CURRENT_USER,
        TEXT(REGPATH) L"\\" TEXT(TWINUI_PCSHELL_SB_NAME),
        0,
        NULL,
        REG_OPTION_NON_VOLATILE,
        KEY_READ,
        NULL,
        &hKey,
        &dwDisposition
    );
    RegQueryValueExW(
        hKey,
        TEXT(TWINUI_PCSHELL_SB_0),
        0,
        NULL,
        &(symbols_PTRS->twinui_pcshell_PTRS[0]),
        &dwSize
    );
    RegQueryValueExW(
        hKey,
        TEXT(TWINUI_PCSHELL_SB_1),
        0,
        NULL,
        &(symbols_PTRS->twinui_pcshell_PTRS[1]),
        &dwSize
    );
    RegQueryValueExW(
        hKey,
        TEXT(TWINUI_PCSHELL_SB_2),
        0,
        NULL,
        &(symbols_PTRS->twinui_pcshell_PTRS[2]),
        &dwSize
    );
    RegQueryValueExW(
        hKey,
        TEXT(TWINUI_PCSHELL_SB_3),
        0,
        NULL,
        &(symbols_PTRS->twinui_pcshell_PTRS[3]),
        &dwSize
    );
    RegQueryValueExW(
        hKey,
        TEXT(TWINUI_PCSHELL_SB_4),
        0,
        NULL,
        &(symbols_PTRS->twinui_pcshell_PTRS[4]),
        &dwSize
    );
    RegQueryValueExW(
        hKey,
        TEXT(TWINUI_PCSHELL_SB_5),
        0,
        NULL,
        &(symbols_PTRS->twinui_pcshell_PTRS[5]),
        &dwSize
    );
    RegQueryValueExW(
        hKey,
        TEXT(TWINUI_PCSHELL_SB_6),
        0,
        NULL,
        &(symbols_PTRS->twinui_pcshell_PTRS[6]),
        &dwSize
    );
    RegQueryValueExW(
        hKey,
        TEXT(TWINUI_PCSHELL_SB_7),
        0,
        NULL,
        &(symbols_PTRS->twinui_pcshell_PTRS[7]),
        &dwSize
    );
    RegCloseKey(hKey);

    RegCreateKeyExW(
        HKEY_CURRENT_USER,
        TEXT(REGPATH) L"\\" TEXT(STARTDOCKED_SB_NAME),
        0,
        NULL,
        REG_OPTION_NON_VOLATILE,
        KEY_READ,
        NULL,
        &hKey,
        &dwDisposition
    );
    RegQueryValueExW(
        hKey,
        TEXT(STARTDOCKED_SB_0),
        0,
        NULL,
        &(symbols_PTRS->startdocked_PTRS[0]),
        &dwSize
    );
    RegQueryValueExW(
        hKey,
        TEXT(STARTDOCKED_SB_1),
        0,
        NULL,
        &(symbols_PTRS->startdocked_PTRS[1]),
        &dwSize
    );
    RegQueryValueExW(
        hKey,
        TEXT(STARTDOCKED_SB_2),
        0,
        NULL,
        &(symbols_PTRS->startdocked_PTRS[2]),
        &dwSize
    );
    RegQueryValueExW(
        hKey,
        TEXT(STARTDOCKED_SB_3),
        0,
        NULL,
        &(symbols_PTRS->startdocked_PTRS[3]),
        &dwSize
    );
    RegQueryValueExW(
        hKey,
        TEXT(STARTDOCKED_SB_4),
        0,
        NULL,
        &(symbols_PTRS->startdocked_PTRS[4]),
        &dwSize
    );
    RegCloseKey(hKey);

    BOOL bNeedToDownload = FALSE;
    for (UINT i = 0; i < sizeof(symbols_addr) / sizeof(DWORD); ++i)
    {
        if (!((DWORD*)symbols_PTRS)[i] &&
            (((DWORD*)symbols_PTRS) + i) != symbols_PTRS->twinui_pcshell_PTRS + TWINUI_PCSHELL_SB_CNT - 1
            )
        {
            bNeedToDownload = TRUE;
        }
    }

    TCHAR szReportedVersion[MAX_PATH + 1];
    ZeroMemory(
        szReportedVersion,
        (MAX_PATH + 1) * sizeof(TCHAR)
    );
    TCHAR szStoredVersion[MAX_PATH + 1];
    ZeroMemory(
        szStoredVersion,
        (MAX_PATH + 1) * sizeof(TCHAR)
    );
    wsprintf(
        szReportedVersion,
        L"%d.%d.%d.%d",
        rovi.dwMajorVersion,
        rovi.dwMinorVersion,
        rovi.dwBuildNumber,
        ubr
    );
    RegCreateKeyExW(
        HKEY_CURRENT_USER,
        TEXT(REGPATH),
        0,
        NULL,
        REG_OPTION_NON_VOLATILE,
        KEY_READ,
        NULL,
        &hKey,
        &dwDisposition
    );
    dwSize = MAX_PATH;
    RegQueryValueExW(
        hKey,
        TEXT("OSBuild"),
        0,
        NULL,
        szStoredVersion,
        &dwSize
    );
    RegCloseKey(hKey);
    if (!bNeedToDownload)
    {
        bNeedToDownload = wcscmp(szReportedVersion, szStoredVersion);
    }
    return bNeedToDownload;
}