#include "mbed.h"

extern void Sauve_USB(float *,int ) ; 
extern Serial pc ;

#define FECH 20000 // Fréquence d'échantillonnage souhaitée
                   // Maximum 40 kHz  
#define TAILLE_TAB (FECH/10) // Pour stocker 1/10 s du signal
                             // Donc fmin signal = 10 Hz

Ticker acquisition_CAN ;
AnalogIn entree(PC_3); // A2 connecteur Arduino
DigitalIn button(USER_BUTTON);

float tab[TAILLE_TAB] ;

void acquisition() {
    static int i = 0 ;
    tab[i] = 3.3f*entree.read(); // Conversion en volts
    i++;
    if (i == TAILLE_TAB) i = 0 ;
}

int main(void)
{
    pc.printf("\033[2J"); // Sequence escape qui efface la console
    pc.printf("Acquisition d'un signal sur broche PC_3(A2)\n");
    pc.printf("Et enregistrement sur clef USB\n"); 
    pc.printf("Frequence d'echantillonnage actuelle = %d Hz\n",FECH); 
    pc.printf("Veuillez connecter un signal sur cette broche \n");
    pc.printf("Appuyez sur le bouton USER de la carte pour demarrer l'acquisition\n");
    while (button.read() == 0) ;
    acquisition_CAN.attach_us(&acquisition,1000000/FECH); 
    wait(0.2) ;   // Attendre au moins 1/10 seconde pour remplir le buffer des échantillons prélevés sur PC_3
    acquisition_CAN.detach() ; // Stopper l'acquisition des échantillons
    Sauve_USB(tab,TAILLE_TAB);
    while(1) ;
}
