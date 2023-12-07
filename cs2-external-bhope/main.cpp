#include <Windows.h>
#include <iostream>

#include <thread>
#include <chrono>

#include "wmemory.h"
#include "offsets.h"

using namespace std;

int main()
{
    // get procces id
    uintptr_t processID = Wmemory::GetProcessID(L"cs2.exe");
    if (processID == NULL)
        return 0;

    // open procces
    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
    if (processHandle == NULL)
        return 0;

    // get addres client.dll
    uintptr_t moduleBaseAddress = Wmemory::GetModuleBaseAddress(processID, L"client.dll");

    // get localPlayerPawn
    uintptr_t localPlayerPawn = Wmemory::ReadMemory<uintptr_t>(processHandle, moduleBaseAddress + offsets::dwLocalPlayerPawn);

    while (true)
    {
        // read flags
        int flags = Wmemory::ReadMemory<int>(processHandle, localPlayerPawn + offsets::m_fFlags);

        // if pressed spacebar
        if (GetAsyncKeyState(VK_SPACE) < 0)
        {
            // if stanging and crouching
            if (flags == 65665 || flags == 65667)
            {
                // if no dalay cant jump
                this_thread::sleep_for(chrono::microseconds(512));

                Wmemory::WriteMemory<int>(processHandle, moduleBaseAddress + offsets::dwForceJump, 65537);  // +jump
            }
            else
            {
                Wmemory::WriteMemory<int>(processHandle, moduleBaseAddress + offsets::dwForceJump, 255);    // -jump
            }

        }

        // save cpu
        this_thread::sleep_for(chrono::microseconds(2));
    }

    CloseHandle(processHandle);
    return 0;
}