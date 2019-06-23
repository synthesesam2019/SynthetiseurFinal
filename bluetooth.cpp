#include "mbed.h"
#include "bluetooth.h"
#include "Note.h"
#include "AUDIO_DISCO_F746NG.h"
#include "SDRAM_DISCO_F746NG.h"

Serial HC06(PF_7,PF_6, 115200); //Init BT
char data[7]={0,0,0,0,0,0};     //Tab reception
int Note = 0;                   //Note MIDI
char cc;                        //Concaténation reception BT => Valeur MIDI 
extern AUDIO_DISCO_F746NG audio;
extern SDRAM_DISCO_F746NG sdram;
Serial PC(USBTX, USBRX,115200); //Init série PC
extern double Freq[84];         //Tableau des fréquences du piano
extern int16_t tabt[AUDIO_BLOCK_SIZE];//Buffer des points de la sinusoïde
extern int x;                   //taille du buffer


/* Callback appelée sur recpetion sur la liaison série bluetooth*/
void callback(){                
    int z;
    while(HC06.readable()){         //Si reception BT
        for(z = 0; z<6;z++){
            data[z] = HC06.getc();  //On récupère le buffer de reception si le caractère est \n, on a atteint la fin du message
            if (data[z] == '\n'){   
                break;
            }
        }

        PC.printf("%s",data);       //On affiche sur le PC le message
        if (data[3] == '\r'){       //Si la note MIDI est inférieure à 100, on décale d'une case tout le message
            data[3] = data[2];
            data[2] = data[1];
            data[1] = 0;
            cc = (((int)data[1] - 48)*0) + (((int)data[2]-48) * 10) + ((int)data[3]-48); // Calcul de la note
            Note = (int)cc;
            if (Note <= 24) Note = 24; //Force la note à 24 si hors tableau
        }
        else    //Si la note MIDI est supérieure à 100, on calcule directement sa valeur
        {
            cc = (((int)data[1] - 48)*100) + (((int)data[2]-48) * 10) + ((int)data[3]-48);
            Note = (int)cc;
            if (Note >= 107) Note = 107;
        }
        envoie_note(Note, data[0]);     //Envoie les informations reçues à la fonction de lecture
    }
}

/* Fonction de lecture des notes*/
void envoie_note(int Noteajouer, char Header){ //Joue la note contenue dans Noteajouer si Header = 'A' ou arrête de jouer si Header = 'R'
    x = note(Freq[Noteajouer-24]);     
    
    if (Header == 'A'){
    audio.OUT_Play((uint16_t*)AUDIO_BUFFER_OUT, (x*2));
    }
    if(Header == 'R'){
        audio.OUT_Stop(CODEC_PDWN_SW);
    }
}

/* Attache la fonction callback à l'interruption sur reception BT*/
void read(){
    HC06.attach(&callback, Serial::RxIrq);
    }
    