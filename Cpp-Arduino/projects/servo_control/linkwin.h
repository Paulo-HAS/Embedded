#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>    //classe para conexao Windows-Arduino
#include "protocol.h"

class Link {
    private:
        HANDLE hSerial;
    
    public:
        explicit Link(const char* port) // para o arduino, geralmente seria "\\\\.\\COM3"
            : hSerial(CreateFileA(port, GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr)) {
            DCB d{};
            d.DCBlength = sizeof d;
            GetCommState(hSerial, &d);
            d.BaudRate = CBR_115200;
            d.ByteSize = 8;
            d.Parity = NOPARITY;
            d.StopBits = ONESTOPBIT;
            SetCommState(hSerial, &d);
        }

        ~Link() { CloseHandle(hSerial);}

        Link(const Link&) = delete;
        Link& operator = (const Link&) = delete;

        void send(const proto::Msg& m) {
            DWORD n;
            WriteFile(hSerial, &m, sizeof m, &n, nullptr);
        }
};
