#include "mbed.h"

Serial pc(USBTX, USBRX);

AnalogIn Ve(PA_3); // CAN sur A0 connecteur Arduino
AnalogOut Vs(PA_5); // CNA sur D13 connecteur Arduino

int main()
{
    pc.printf("Test du convertisseur numerique/analogique\n");
    pc.printf("Relier D13 (CNA) a A0 (CAN) du connecteur Arduino\n");
    Vs.write(0.5);
    pc.printf("Valeur envoyee sur D13 = %f \n", 0.5);
    pc.printf("Valeur lue sur A0     = %f \n", Ve.read());
    while(1) {
    }
}
