#include "Note.h"
#include "AUDIO_DISCO_F746NG.h"
#include "SDRAM_DISCO_F746NG.h"

    
    extern Serial PC;               //Serial PC
    int sinus[AUDIO_BLOCK_SIZE];    //Buffer calcul du sinus
    int i,j = 0;                    //variable d'incrémentation
    int x = 0;                      //taille du buffer
    int16_t tabt[AUDIO_BLOCK_SIZE]; //Buffer points de la sinusoïde à jouer
    /* Tableau des fréquences correspondant aux notes du piano */
    double Freq[84] = {32.703,34.648,36.708,38.891,41.203,43.654,46.249,48.999,51.913,55,58.270,61.735,65.406,69.296,73.416,
                        77.782,82.407,83.307,92.499,97.999,103.83,110,116.54,123.47,130.81,138.59,146.83,155.56,164.81,174.61,185,196,207.65,220,233.08,
                        246.94,261.63,277.18,293.67,311.13,329.63,349.23,369.99,392,415.30,440,466.16,493.8,523.25,554.37,587.33,622.25,659.26,698.46,739.99,
                        783.99,830.61,880,923.33,987.77,1046.5,1108.7,1174.7,1244.5,1318.5,1396.9,1480,1568,1661.2,1760,1864.7,1975.5,2093,2217.5,2349.3,
                        2489,2637,2793,2960,3136,3322.4,3520,3729.3,3951.1};
/*  Remplis un buffer de points de la sinusoïde en fonction de la fréquence */
int note(double frequence)
{
        //wait(2);
    frequency = frequence;
     x = rint(2 * (1.0/frequency)*44100);       //On calcule le nombre de notes à entrer dans le buffer pour avoir une période du signal
     for(i=0; i<x; i++) {
        /* Calcul des points du sinus */
        sinus[i] = (int)20000*sin((double)6.28318530717959 * frequency * i * (1.0 / 44100.0));
     }
     /* Remplis le buffer de lecture des notes */
    for(j=0; j<(x*2); j++) {
        int z;

        z = floor((double)j/2);
        tabt[j] = sinus[z];
        tabt[j+1] = sinus[z];
       
        j++;
        
    }
    // On calcule ensuite plusieurs harmoniques de 2 à 10 avec des sinusoïdes qu'on additionne au fondamental.
    frequency = frequence *2;
    
    x = rint(2 * (1.0/frequency)*44100);
     //PC.printf("%d",x);
         //PC.printf("x = %d \r\n", x);
     for(i=0; i<x; i++) {
        
        sinus[i] = (int) 4320*sin((double)6.28318530717959 * frequency * i * (1.0 / 44100.0));
     }
    //pc.printf("Sinus done");
    for(j=0; j<(x*2); j++) {
        int z;

        z = floor((double)j/2);
        tabt[j] = tabt[j] + sinus[z];
        tabt[j+1] = tabt[j+1] + sinus[z];
       
        j++;
        
    }
    frequency = frequence *3;
    
    x = rint(2 * (1.0/frequency)*44100);
     //PC.printf("%d",x);
         //PC.printf("x = %d \r\n", x);
     for(i=0; i<x; i++) {
        
        sinus[i] = (int)4200*sin((double)6.28318530717959 * frequency * i * (1.0 / 44100.0));
     }
    //pc.printf("Sinus done");
    for(j=0; j<(x*2); j++) {
        int z;

        z = floor((double)j/2);
        tabt[j] = tabt[j] + sinus[z];
        tabt[j+1] = tabt[j+1] + sinus[z];
       
        j++;
        
    }
     frequency = frequence *4;
    
    x = rint(2 * (1.0/frequency)*44100);
     //PC.printf("%d",x);
         //PC.printf("x = %d \r\n", x);
     for(i=0; i<x; i++) {
        
        sinus[i] = (int)2600*sin((double)6.28318530717959 * frequency * i * (1.0 / 44100.0));
     }
    //pc.printf("Sinus done");
    for(j=0; j<(x*2); j++) {
        int z;

        z = floor((double)j/2);
        tabt[j] = tabt[j] + sinus[z];
        tabt[j+1] = tabt[j+1] + sinus[z];
       
        j++;
        
    }
     frequency = frequence *5;
    
    x = rint(2 * (1.0/frequency)*44100);
     //PC.printf("%d",x);
         //PC.printf("x = %d \r\n", x);
     for(i=0; i<x; i++) {
        
        sinus[i] = (int)2000*sin((double)6.28318530717959 * frequency * i * (1.0 / 44100.0));
     }
    //pc.printf("Sinus done");
    for(j=0; j<(x*2); j++) {
        int z;

        z = floor((double)j/2);
        tabt[j] = tabt[j] + sinus[z];
        tabt[j+1] = tabt[j+1] + sinus[z];
       
        j++;
        
    }
     frequency = frequence *6;
    
    x = rint(2 * (1.0/frequency)*44100);
     //PC.printf("%d",x);
         //PC.printf("x = %d \r\n", x);
     for(i=0; i<x; i++) {
        
        sinus[i] = (int)2200*sin((double)6.28318530717959 * frequency * i * (1.0 / 44100.0));
     }
    //pc.printf("Sinus done");
    for(j=0; j<(x*2); j++) {
        int z;

        z = floor((double)j/2);
        tabt[j] = tabt[j] + sinus[z];
        tabt[j+1] = tabt[j+1] + sinus[z];
       
        j++;
        
    }
     frequency = frequence *7;
    
    x = rint(2 * (1.0/frequency)*44100);
     //PC.printf("%d",x);
         //PC.printf("x = %d \r\n", x);
     for(i=0; i<x; i++) {
        
        sinus[i] = (int)2000*sin((double)6.28318530717959 * frequency * i * (1.0 / 44100.0));
     }
    //pc.printf("Sinus done");
    for(j=0; j<(x*2); j++) {
        int z;

        z = floor((double)j/2);
        tabt[j] = tabt[j] + sinus[z];
        tabt[j+1] = tabt[j+1] + sinus[z];
       
        j++;
        
    }
     frequency = frequence *8;
    
    x = rint(2 * (1.0/frequency)*44100);
     //PC.printf("%d",x);
         //PC.printf("x = %d \r\n", x);
     for(i=0; i<x; i++) {
        
        sinus[i] = (int)2000*sin((double)6.28318530717959 * frequency * i * (1.0 / 44100.0));
     }
    //pc.printf("Sinus done");
    for(j=0; j<(x*2); j++) {
        int z;

        z = floor((double)j/2);
        tabt[j] = tabt[j] + sinus[z];
        tabt[j+1] = tabt[j+1] + sinus[z];
       
        j++;
        
    }
     frequency = frequence *9;
    
    x = rint(2 * (1.0/frequency)*44100);
     //PC.printf("%d",x);
         //PC.printf("x = %d \r\n", x);
     for(i=0; i<x; i++) {
        
        sinus[i] = (int)1400*sin((double)6.28318530717959 * frequency * i * (1.0 / 44100.0));
     }
    //pc.printf("Sinus done");
    for(j=0; j<(x*2); j++) {
        int z;

        z = floor((double)j/2);
        tabt[j] = tabt[j] + sinus[z];
        tabt[j+1] = tabt[j+1] + sinus[z];
       
        j++;
        
    }
     frequency = frequence *10;
    
    x = rint(2 * (1.0/frequency)*44100);
     //PC.printf("%d",x);
         //PC.printf("x = %d \r\n", x);
     for(i=0; i<x; i++) {
        
        sinus[i] = (int)320*sin((double)6.28318530717959 * frequency * i * (1.0 / 44100.0));
     }
    //pc.printf("Sinus done");
    for(j=0; j<(x*2); j++) {
        int z;

        z = floor((double)j/2);
        tabt[j] = tabt[j] + sinus[z];
        tabt[j+1] = tabt[j+1] + sinus[z];
       
        j++;
        
    }
    frequency = frequence;
     x = rint(2 * (1.0/frequency)*44100);
    memcpy((uint16_t *) AUDIO_BUFFER_OUT, (uint16_t *)tabt, x*2); //On envoie les notes sur le buffer en SRAM pour les jouer.
    
    return x;
}


void Init_note(void)
{
    memset((uint16_t *)AUDIO_BUFFER_IN, 0, AUDIO_BLOCK_SIZE);
    memset((uint16_t *)AUDIO_BUFFER_OUT, 0, AUDIO_BLOCK_SIZE);
    memcpy((uint16_t *) AUDIO_BUFFER_IN, (uint16_t *)tabt, AUDIO_BLOCK_SIZE);
}
