#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <pthread.h>


#define TERMINAL_MAX_X 80
#define MAX_X 56
#define MIN_Y 6
#define MAX_Y 42
#define FRAMERATE 90
#define INIZIO_ACQUA_Y 15
#define FINE_ACQUA_Y 36
#define OFFSET_X 5
#define MIN_X_GUI 57
#define GUI_X_SIZE 23
#define PAGINA_MAIN 1
#define PAGINA_GIOCA 2
#define PAGINA_COMANDI 3
#define PAGINA_PERK 4
#define PAGINA_RESOCONTO 5



#define COLOR_FROG_BLUE 8
#define COLOR_FROG_YELLOW 9
#define COLOR_TANA_ORANGE 10
#define COLOR_PLANT_GREEN 11
#define COLOR_PERK_BOX 12
#define COLOR_PERK_CHARS 13
#define COLOR_UNDERWATER 14
#define COLOR_WATER 15
#define COLOR_GREY_GUI 16
#define COLOR_GOLD_PERK 17
#define COLOR_BEIGE 18
#define COLOR_BROWN 19
#define COLOR_CROCO 20
#define COLOR_SAND 21
#define COLOR_CROCO_RED 22
#define COLOR_PRO_FROG 23
#define COLOR_PRO_PLANT 24

#define NUMERO_CORSIE 8
#define NUMERO_COCCO 3
#define NUMERO_PIANTE 3
#define ALTEZZA_PIANTE 12
#define NUMERO_TANE 5
#define VITE_RANA 5
#define VITE_PIANTA 3
#define DIMENSIONE_X_COCCO 8
#define RANGE_PIANTA_SINISTRO 3
#define RANGE_PIANTA_DESTRO 5
#define RANGE_TANA_SINISTRO 1
#define RANGE_TANA_DESTRO 4

#define MALUS_TEMPO_TANA 0.07
#define MOLTIPLICATORE_FACILE 1.2
#define MOLTIPLICATORE_NORMALE 1
#define MOLTIPLICATORE_DIFFICILE 0.8
#define COCCODRILLI_TRASF_FACILE 3
#define COCCODRILLI_TRASF_NORMALE 5
#define COCCODRILLI_TRASF_DIFFICILE 7
#define TEMPO_FACILE 60
#define TEMPO_NORMALE 50
#define TEMPO_DIFFICILE 40


#define START_X 27
#define START_Y 40

#define NUMERO_PERKS 10

#define PUNTI_SU_COCCODRILLO 2
#define PUNTI_TRASFORMAZIONE_COCCODRILLO 10
#define PUNTI_TANA_PRESA 50
#define PUNTI_VITTORIA 100
#define PUNTI_DISTRUZIONE_PROIETTILE 15
#define PUNTI_HIT_PIANTA 10
#define PUNTI_KILL_PIANTA 25
#define PUNTI_PERDITA_VITA 30

//Funzione di calcolo tempo (precisione in millisecondi)
double SecondiDaEpoch()
{
    struct timeval tp;

    gettimeofday(&tp, NULL);

    double ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    return ms / 1000;
}

typedef enum {NESSUNO, TRAPASSA_COCCODRILLI, SCUDO, HP_UP, AMMAZZA_PIANTE, ONE_SHOT,
                PIANTE_IMMUNI, DOPPIO_DANNO, PERDI_TANA, PISTOLA_ROTTA, FULL_RAMBO} Perk;

typedef enum {FACILE, NORMALE, DIFFICILE} Difficolta;


struct Coordinate
{
    int x;
    int y;
};

struct CommRana //Struttura su cui opera il thread
{
    char carattere;
    bool scritto;
    bool termina;
};

struct Rana
{
    struct Coordinate coordinate;
    int vite;
    pthread_t tid;
    struct CommRana* comunicazione;
    Perk perk;
};

struct CommTana
{
    bool termina;
};

struct Tana
{
    struct Coordinate coordinate;
    bool done;
    pthread_t tid;
    Perk perk;
    struct CommTana* comunicazione;
};

struct CommPianta //Struttura su cui opera il thread
{
    bool messaggio;
    pthread_mutex_t mutex;
    bool termina;
};

struct Pianta
{
    struct Coordinate coordinate;
    int vite;
    pthread_t tid;
    struct CommPianta* comunicazione;
};

struct CommCoccodrillo //Struttura su cui opera il thread
{
    struct Coordinate messaggio;
    bool buono;
    bool direzione;
    bool termina;
    pthread_mutex_t mutex;
};

struct Coccodrillo
{
    struct Coordinate coordinate;
    bool buono;
    bool direzione;
    float velocita;
    pthread_t tid;
    struct CommCoccodrillo * comunicazione;
};

struct CommProiettile //Struttura su cui opera il thread
{   
    struct Coordinate messaggio;
    bool fazione;
    bool termina;
    pthread_mutex_t mutex;
};

struct Proiettile
{
    struct Coordinate coordinate;
    bool fazione;
    pthread_t tid;
    struct CommProiettile* comunicazione;
};

struct RisultatoPartita
{
    Difficolta difficolta;
    int punteggio;
    bool vittoria;
};
