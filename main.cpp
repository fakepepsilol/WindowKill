#include<Windows.h>
#include<TlHelp32.h>
#include<iostream>
#include<tchar.h>
#include<vector>
#include<stdlib.h>
#include<thread>
#include<random>
#include<sstream>

HANDLE process = NULL;
DWORD id = 0;



uintptr_t GetModuleAddress(const char* moduleName) {
    MODULEENTRY32 entry;
    entry.dwSize = sizeof(MODULEENTRY32);
    const auto snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, id);
    uintptr_t result = 0;
    while (Module32Next(snapShot, &entry)) {
        if (!strcmp(moduleName, entry.szModule)) {
            result = reinterpret_cast<uintptr_t>(entry.modBaseAddr);
            break;
        }
    }
    if (snapShot) {
        CloseHandle(snapShot);
    }
    return result;
}
long long int getAddress(HANDLE process, long long int base, long int offset) {
    long long int offsets[6] = { 0x03453100, 0x348, 0x1C0, 0x10, 0x68, 0x28};
    long long int var = base;
    long long int currentAddress = base;
    for (int i = 0; i < 6; i++) {
        ReadProcessMemory(process, (LPCVOID)(currentAddress + offsets[i]), &var, sizeof(long long int), 0);
        currentAddress = var;
    }
    return var + offset;
}
long long int Read(long long int address) {
    long long int var = 0;
    ReadProcessMemory(process, (LPCVOID)(address), &var, sizeof(long long int), 0);
    return var;
}

bool Write(long long int address, long long int var) {
    return WriteProcessMemory(process, (LPVOID)(address), &var, sizeof(long long int), 0);

}
int main() {
    
    
    const char* processName = "windowkill-vulkan.exe";
    
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);


    const auto snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    while (Process32Next(snapShot, &entry)){
        if (!strcmp(processName, entry.szExeFile)) {
            id = entry.th32ProcessID;
            process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id);
            break;
        }
    }
    if (snapShot){
        CloseHandle(snapShot);
    }
    if (!process) {
        char temp;
        std::cout << "No process found!";
        std::cin >> temp;
        return 0;
    }
    std::printf("The process id: %d \n", id);
    long long int offset = 0;
    if (id) {
        const auto base = GetModuleAddress("windowkill-vulkan.exe");
        offset = getAddress(process, base, 0);
    }
    else { std::cout << "No process found!\n";  return 0; }
    long long int moneyAddress = offset + 0x260;
    long long int starsAddress = offset + 0x278;
    long long int restockCountAddress = offset + 0x2A8; 
    long long int speedAddress = offset + 0x2D8; 
    long long int fireRateAddress = offset + 0x2F0; 
    long long int multishotAddress = offset + 0x308; 
    long long int homingAddress = offset + 0x320; 
    long long int wealthAddress = offset + 0x338; 
    long long int wallPunchAddress = offset + 0x350; 
    long long int healAddress = offset + 0x368; 
    long long int maxHealthAddress = offset + 0x380; 
    long long int freezingAddress = offset + 0x398; 
    long long int piercingAddress = offset + 0x3B0; 
    long long int splashDamageAddress = offset + 0x3C8; 
    long long int healthAddress = offset + 0x470; 




 
    Write(healthAddress, 2934750247);
    std::cout << Read(healthAddress);
    char temp;
    std::cin >> temp;

}