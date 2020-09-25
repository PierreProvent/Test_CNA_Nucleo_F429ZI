#include "mbed.h"
#include "USBHostMSD.h"

Serial pc(USBTX,USBRX) ;

void Sauve_USB(float *tab,int taille)  
{
  USBHostMSD msd("usb");

   pc.printf("Connectez la clef USB sur le connecteur prevu a cet effet\n"); // Waiting for USB connection 
   while(!msd.connect())  // try to connect a MSD device
   {
   }
    pc.printf("Clef USB connectee ne pas debrancher\n");
    pc.printf("Ecriture des donnees sur la clef USB dans le fichier data.txt\n");
    FILE *fp = fopen("/usb/data.txt","w"); 
    if (fp != NULL) 
    {
        // Ecriture en format texte éditable sous Notepad
        /* for (int i = 0 ; i < taille; i++) 
            fprintf(fp,"%f\n", tab[i]);
        fclose(fp);     */
        
        // Ecriture en binaire pour lecture avec Octave ou Matlab
        fwrite(tab,sizeof(tab[0]),taille,fp);
        fclose(fp); 
        pc.printf("Ecriture terminee, vous pouvez debrancher la clef USB\n");
    }
    else 
        pc.printf("Impossible d'ouvrir le fichier data.txt\n");
}