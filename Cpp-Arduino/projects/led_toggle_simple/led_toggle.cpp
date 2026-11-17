#include <iostream>
#include <windows.h>

using namespace std;

int main(){
    HANDLE hSerial = CreateFileA("\\\\.\\COM3", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(hSerial == INVALID_HANDLE_VALUE) {
        cerr << "Erro ao abrir a comunicacao serial." << endl;
        return 1;
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    GetCommState(hSerial, &dcbSerialParams);
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    SetCommState(hSerial, &dcbSerialParams);
    // Arduino nesse momento

    cout << "Conectando ao Arduino..." << endl;
    Sleep(2000);

    char op;
    DWORD bytesEnviados;

    while(true){
        cout << "Digite 1 (ligar), 0 (desligar) ou s (sair):" << endl;
        cin >> op;

        if(op == 's' || op == 'S') break;
        else if(op == '1' || op == '0') WriteFile(hSerial, &op, 1, &bytesEnviados, NULL);
    }

    CloseHandle(hSerial);
    return 0;
}