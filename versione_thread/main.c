#include "header.h"
#include "threads.c"
#include "stampe.c"
#include "partita.c"
  
int main()
{
    //Resize window
    system("printf \"\033[8;42;80t\"");

    //Inizializzazione ncurses
    initscr();
    
    noecho();
    timeout(0);
    curs_set(0);
    cbreak();
    attron(A_BOLD);

    //Definizione colori
    DefinisciColori();

    //Inizializzazione struct risultato partita
    struct RisultatoPartita risultato;

    //Inizializzazione variabili
    bool fine = false;
    int selezione = 1;
    int pagina = PAGINA_MAIN;
    char buffer;
    double timer_start_cursore = SecondiDaEpoch();
    double timer_end_cursore;
    double timer_start_frame;
    double timer_end_frame;
    bool lampeggio_cursore = false;
    char killstring[50];
    int framerate = FRAMERATE;
    int highscore[3];
    FILE* fp;

    //Inizializzazione highscore
    if(access("highscores.bin", F_OK) != 0)
    {
        fp = fopen("highscores.bin", "wb");

        highscore[FACILE] = 0;
        highscore[NORMALE] = 0;
        highscore[DIFFICILE] = 0;

        for(int i = 0; i < 3; i++)
        {
            fwrite(&(highscore[i]), sizeof(int), 1, fp);
        }

        fclose(fp);
    }
    else
    {
        fp = fopen("highscores.bin", "rb");

        for(int i = 0; i < 3; i++)
        {
            fread(&(highscore[i]), sizeof(int), 1, fp);
        }

        fclose(fp);
    }

    timer_start_frame = SecondiDaEpoch(); //

    //Riproduzione OST
    system("aplay -q -t wav Sounds/mainmenu.wav --process-id-file temp.bin >/dev/null 2> /dev/null &");

    usleep(300000);

    //Costruzione stringa di uccisione processo dell'OST
    strcpy(killstring, "killall aplay -q -s SIGKILL &");

    //Loop del menu
    while(fine == false)
    {
        //Acquisizione carattere
        buffer = getch();

        //Movimento del cursore
        if(buffer == 'w' && selezione > 1 && pagina != PAGINA_COMANDI && pagina != PAGINA_PERK)
        {
            selezione--;

            system("aplay -q -t wav Sounds/menuselezione.wav &");
        }
        else if(buffer == 's' && (selezione < 3 && pagina != PAGINA_COMANDI && pagina != PAGINA_PERK ||
                                    selezione < 4 && pagina == PAGINA_MAIN))
        {
            selezione++;

            system("aplay -q -t wav Sounds/menuselezione.wav &");
        }

        //Pressione tasto di conferma
        if(buffer == ' ') 
        {
            switch(pagina) //Switch sulle varie pagine
            {
                case PAGINA_MAIN: //Pagina principale

                                switch(selezione)//Switch sulla selezione
                                {
                                    case 1: 
                                            selezione = 1;

                                            system("aplay -q -t wav Sounds/menupagina.wav &");

                                            pagina = PAGINA_GIOCA;
                        
                                            break;
                                    case 2: 
                                            selezione = 1;

                                            system("aplay -q -t wav Sounds/menupagina.wav -q &");

                                            pagina = PAGINA_COMANDI;
                        
                                            break;
                                    case 3: 
                                            selezione = 1;

                                            system("aplay -q -t wav Sounds/menupagina.wav -q &");

                                            pagina = PAGINA_PERK;

                                            break;
                                    case 4: 
                                            system(killstring); //Interruzione riproduzione ost

                                            system("rm temp.bin");

                                            endwin(); //Chiusura finestra

                                            system("clear"); //Pulizia schermo

                                            return 0;

                                            break;
                                    default:
                                            break;
                                }

                                break;
                case PAGINA_GIOCA: //Pagina di selezione difficolta

                                switch(selezione)//Switch sulla selezione
                                {
                                    case 1: 
                                            selezione = 1;

                                            system(killstring); //Interruzione riproduzione ost

                                            system("rm temp.bin");

                                            risultato = Partita(FACILE, framerate, highscore[0]);

                                            pagina = PAGINA_RESOCONTO;
                        
                                            break;
                                    case 2: 
                                            selezione = 1;

                                            system(killstring); //Interruzione riproduzione ost

                                            system("rm temp.bin");

                                            risultato = Partita(NORMALE, framerate, highscore[1]);

                                            pagina = PAGINA_RESOCONTO;
                        
                                            break;
                                    case 3: 
                                            selezione = 1;

                                            system(killstring); //Interruzione riproduzione ost

                                            system("rm temp.bin");

                                            risultato = Partita(DIFFICILE, framerate, highscore[2]);

                                            pagina = PAGINA_RESOCONTO;

                                            break;
                                    default:
                                            break;
                                }

                                break;
                case PAGINA_RESOCONTO: //Pagina di resoconto
                                //Aggiornamento highscore
                                if(risultato.punteggio > highscore[risultato.difficolta] &&
                                    risultato.vittoria == true)
                                {
                                    highscore[risultato.difficolta] = risultato.punteggio;
                                }

                                fp = fopen("highscores.bin", "wb");

                                for(int i = 0; i < 3; i++)
                                {
                                    fwrite(&(highscore[i]), sizeof(int), 1, fp);
                                }

                                fclose(fp);

                                pagina = PAGINA_MAIN; //Torna al menu

                                break;
                default:
                                break;
            }
        }

        //Pressione tasto per tornare indietro
        if(buffer == 'f' && pagina != PAGINA_MAIN)
        {
            selezione = 1;

            system("aplay -q -t wav Sounds/menupagina.wav &");

            pagina = PAGINA_MAIN;
        }

        //Lampeggio cursore
        timer_end_cursore = SecondiDaEpoch();

        if((timer_end_cursore-timer_start_cursore) > 0.445)
        {
            timer_start_cursore = SecondiDaEpoch();

            if(lampeggio_cursore == false)
            {
                lampeggio_cursore = true;
            }
            else
            {
                lampeggio_cursore = false;
            }
        }
        
        //Stampa
        timer_end_frame = SecondiDaEpoch();
        
        if((timer_end_frame-timer_start_frame) > (float) 1 / framerate)
        {
            timer_start_frame = SecondiDaEpoch();

            StampaMenu(pagina, selezione, lampeggio_cursore, risultato, highscore);
        }   

        //Implementazione loop dell'ost
        if (access("temp.bin", F_OK) != 0) 
        {
            system("aplay -q -t wav Sounds/mainmenu.wav --process-id-file temp.bin >/dev/null 2> /dev/null &");

            usleep(300000); //Pausa anti-doppia riproduzione
        }
    }

    return 0;
}

