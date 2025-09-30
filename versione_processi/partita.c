struct RisultatoPartita Partita(Difficolta difficolta, int framerate, int highscore) 
{
    //Pulizia dello schermo
    clear();
    refresh();

    //Inizializzazione seed casuale
    srand(time(NULL));

    //Inizializzazione flags
    bool pausa = false;
    bool fine = false;
    bool sparo = false;
    bool cooldown = true;
    bool ranainacqua = false;
    bool tana_tolta = false;

    //Inizializzazione variabili
    int taneprese = 0;
    double tempotrascorso;
    double tempomax;
    char ranashoot;
    float randomvalue;
    float randomvalue2;
    int punteggio = 0;
    int contatore = 0;
    float moltiplicatore_diff;
    int coccodrilli_da_trasformare;
    int appoggio;
    char killstring[50];

    //Inizializzazione variabili dipendenti da difficolta
    switch(difficolta)
    {
        case FACILE:
                    moltiplicatore_diff = MOLTIPLICATORE_FACILE;
                    coccodrilli_da_trasformare = COCCODRILLI_TRASF_FACILE;
                    tempomax = TEMPO_FACILE;
                    
                    break;
        case NORMALE:
                    moltiplicatore_diff = MOLTIPLICATORE_NORMALE;
                    coccodrilli_da_trasformare = COCCODRILLI_TRASF_NORMALE;
                    tempomax = TEMPO_NORMALE;

                    break;
        case DIFFICILE:
                    moltiplicatore_diff = MOLTIPLICATORE_DIFFICILE;
                    coccodrilli_da_trasformare = COCCODRILLI_TRASF_DIFFICILE;
                    tempomax = TEMPO_DIFFICILE;

                    break;
        default:
                    break;
    }

    //Inizializzazione struttura di ritorno
    struct RisultatoPartita risultato;
    risultato.difficolta = difficolta;

    //Inizializzazione timers
    double tempo_start;
    double tempo_end;
    double timer_start_cocco[NUMERO_CORSIE];
    double timer_end_cocco[NUMERO_CORSIE];
    double timer_start_plant;
    double timer_end_plant;
    double timer_start_proiettile;
    double timer_end_proiettile;
    double timer_start_su_cocco_rosso;
    double timer_end_su_cocco_rosso;
    double timer_start_respawn;
    double timer_end_respawn;
    double timer_start_cooldown;
    double timer_end_cooldown;
    double timer_start_frame;
    double timer_end_frame;

    //Setting tempo di gioco
    tempotrascorso = 0;
    tempo_start = SecondiDaEpoch();
    timer_start_frame = SecondiDaEpoch();

    //Inizializzazione rana
    struct Rana rana;
    
    rana.pid = NuovaRana(rana.pipe, rana.backpipe, rana.pipesparo);
    rana.vite = VITE_RANA;
    rana.perk = NESSUNO;

    timer_start_cooldown = SecondiDaEpoch();

    //Inizializzazione tane
    struct Tana tana[5];

    for(int i = 0; i < NUMERO_TANE; i++)
    {
        tana[i].pid = NuovaTana(); //Creazione processo

        tana[i].done = false;
        tana[i].coordinate.y = 6;
        tana[i].coordinate.x = 3 + OFFSET_X;
        
        switch(difficolta)
        {
            case FACILE:
                        randomvalue = (rand() % 5) + 1;
                        tana[i].perk = randomvalue; 
                        break;
            case NORMALE:
                        if(i < 3)
                        {
                            randomvalue = (rand() % 5) + 1; //Assegna perk buono
                        }
                        else
                        {
                            randomvalue = (rand() % 5) + 6; //Assegna perk cattivo
                        }

                        tana[i].perk = randomvalue; 
                        break;
            case DIFFICILE:
                        if(i < 3)
                        {
                            randomvalue = (rand() % 5) + 1; //Assegna perk buono
                        }
                        else
                        {
                            randomvalue = (rand() % 5) + 6; //Assegna perk cattivo
                        }

                        tana[i].perk = randomvalue; 
                        break;
            default:
                        break;
        }
    }

    //Mescolamento perks
    for(int i = 0; i < NUMERO_TANE; i++)
    {
        appoggio = tana[i].perk;
        randomvalue = rand() % 5;
        tana[i].perk = tana[(int)randomvalue].perk;
        tana[(int)randomvalue].perk = appoggio;
    }

    for(int i = 1; i < NUMERO_TANE; i++)
    {
        tana[i].coordinate.x = tana[i - 1].coordinate.x + 9; //Posizionamento tane
    }

    //Inizializzazione piante
    struct Pianta pianta[NUMERO_PIANTE];

    for(int i = 0; i < NUMERO_PIANTE; i++)
    {
        pianta[i].pid = NuovaPianta(pianta[i].pipe); //Creazione processo

        pianta[i].vite = VITE_PIANTA;

        pianta[i].coordinate.y = ALTEZZA_PIANTE;

        randomvalue = (rand() % 3) + 8;
        pianta[i].coordinate.x = randomvalue;
    }

    pianta[0].coordinate.x += OFFSET_X;

    for(int i = 1; i < NUMERO_PIANTE; i++)
    {
        randomvalue = (rand() % 8) + 9;

        pianta[i].coordinate.x = pianta[i - 1].coordinate.x + randomvalue; //Posizionamento piante
    }

    timer_start_plant = SecondiDaEpoch();

    //Inizializzazione coccodrilli
    struct Coccodrillo coccodrillo[NUMERO_CORSIE][NUMERO_COCCO];

    for(int i = 0; i < NUMERO_CORSIE; i++)
    {
        randomvalue = (float)(rand() % 15) / 100 + 0.25;

        coccodrillo[i][0].velocita = randomvalue;
        coccodrillo[i][1].velocita = randomvalue;
        coccodrillo[i][2].velocita = randomvalue;

        for(int j = 0; j < NUMERO_COCCO; j++)
        {
            if(i % 2 == 0)
            {
                coccodrillo[i][j].direzione = 1;
            }
            else
            {
                coccodrillo[i][j].direzione = 0;
            }
            

            if(j == 0)
            {
                coccodrillo[i][j].coordinate.x = (rand() % 3) + DIMENSIONE_X_COCCO + OFFSET_X;
            }
            else
            {
                coccodrillo[i][j].coordinate.x = 
                    coccodrillo[i][j - 1].coordinate.x + (rand() % DIMENSIONE_X_COCCO) + 9; //Posizionamento coccodrilli
            }
            
            
            coccodrillo[i][j].coordinate.y = (i * 3);
            coccodrillo[i][j].coordinate.y = coccodrillo[i][j].coordinate.y + 15;

            randomvalue = (float)(rand() % 10) / 10;

            if(randomvalue > 0.33)
            {
                coccodrillo[i][j].buono = true;
            }
            else
            {
                coccodrillo[i][j].buono = false;
            }

            coccodrillo[i][j].pid = NuovoCoccodrillo(&(coccodrillo[i][j])); //Creazione processo
        }
    }

    for(int i = 0; i < NUMERO_CORSIE; i++)
    {
        timer_start_cocco[i] = SecondiDaEpoch();
    }
    

    //Inizializzazione vettore dei proiettili
    int numeroProiettili = 0;
    struct Proiettile* proiettile;
    proiettile = (struct Proiettile*) malloc(sizeof(struct Proiettile) * numeroProiettili); //Allocazione

    timer_start_proiettile = SecondiDaEpoch();

    //Inizializzazione timer di respawn piante
    timer_start_respawn = SecondiDaEpoch();

    //Riproduzione OST
    system("aplay -q -t wav Sounds/ost.wav --process-id-file temp.bin >/dev/null 2> /dev/null &");

    //Delay pre-game
    usleep(300000);

    //Costruzione stringa di uccisione processo dell'OST
    strcpy(killstring, "killall aplay -q -s SIGKILL &");

    //While di gioco
    while(fine == false)
    {
        if(pausa == false) //Se non in pausa
        {

        //Implementazione loop dell'ost
        if (access("temp.bin", F_OK) != 0) 
        {
            system("aplay -q -t wav Sounds/ost.wav --process-id-file temp.bin >/dev/null 2> /dev/null &");

            usleep(150000); //Pausa anti-doppia riproduzione
        }
        
        //Aggiornamento tempo
        tempo_end = SecondiDaEpoch();
        tempotrascorso += tempo_end - tempo_start;
        tempo_start = SecondiDaEpoch();
        
        //Recupero coordinate aggiornate rana
        read(rana.pipe[0], &rana.coordinate, sizeof(struct Coordinate));
        
        //Recupero coordinate aggiornate coccodrilli
        for(int i = 0; i < NUMERO_CORSIE; i++)
        {
            timer_end_cocco[i] = SecondiDaEpoch();
        }
        
        for(int i = 0; i < NUMERO_CORSIE; i++)
        {
        if((timer_end_cocco[i]-timer_start_cocco[i]) > coccodrillo[i][0].velocita * moltiplicatore_diff)
        {
            timer_start_cocco[i] = SecondiDaEpoch();

            for(int j = 0; j < NUMERO_COCCO; j++)
            {
                //Movimento rana con coccodrillo
                if(rana.coordinate.y == coccodrillo[i][j].coordinate.y)
                {
                    if(rana.coordinate.x >= coccodrillo[i][j].coordinate.x &&
                        rana.coordinate.x < coccodrillo[i][j].coordinate.x + DIMENSIONE_X_COCCO ||
                        (coccodrillo[i][j].coordinate.x > (MAX_X - DIMENSIONE_X_COCCO) && 
                        (
                        rana.coordinate.x >= coccodrillo[i][j].coordinate.x ||
                        rana.coordinate.x <= (coccodrillo[i][j].coordinate.x + DIMENSIONE_X_COCCO) % (MAX_X + 1)
                        )))
                        {
                            if(coccodrillo[i][j].direzione == 1 )
                            {
                                rana.coordinate.x = rana.coordinate.x + 1;
                            }
                            else
                            {
                                rana.coordinate.x = rana.coordinate.x - 1;
                            }

                            //Aggiunta punteggio
                            if(coccodrillo[i][j].buono == true)
                            {
                                punteggio += PUNTI_SU_COCCODRILLO;
                            }
                            else
                            {
                                punteggio += PUNTI_SU_COCCODRILLO * 2;
                            }
                                
                        }
                 }

                //Riscrittura valore buono del coccodrillo sul suo processo
                write(coccodrillo[i][j].backpipe[1], &(coccodrillo[i][j].buono), sizeof(bool));

                //Riscrittura valore direzione del coccodrillo sul suo processo
                write(coccodrillo[i][j].backpipe2[1], &(coccodrillo[i][j].direzione), sizeof(bool));
                    
                //Recupero nuove coordinate coccodrillo
                read(coccodrillo[i][j].pipe[0], &(coccodrillo[i][j].coordinate),
                        sizeof(struct Coordinate));


            }
            
        }
        }

        //Recupero segnale di sparo da parte delle piante
        timer_end_plant = SecondiDaEpoch();

        if((timer_end_plant-timer_start_plant) > 1 * moltiplicatore_diff)
        {
            timer_start_plant = SecondiDaEpoch();

            for(int i = 0; i < NUMERO_PIANTE; i++)
            {
                if(pianta[i].vite > 0 && 
                    (rana.coordinate.x >= pianta[i].coordinate.x - RANGE_PIANTA_SINISTRO &&
                    rana.coordinate.x <= pianta[i].coordinate.x + RANGE_PIANTA_DESTRO &&
                    rana.coordinate.y > pianta[i].coordinate.y) 
                    || (rana.perk == FULL_RAMBO && pianta[i].vite > 0))
                {
                    system("aplay -q -t wav Sounds/plantbullet.wav & >/dev/null 2> /dev/null");

                    read(pianta[i].pipe[0], &sparo, sizeof(bool));

                    //Aggiungi proiettile
                    numeroProiettili = numeroProiettili + 1;

                    proiettile = (struct Proiettile*)
                                    realloc(proiettile, sizeof(struct Proiettile) * numeroProiettili);

                    proiettile[numeroProiettili - 1].coordinate = pianta[i].coordinate;
                    proiettile[numeroProiettili - 1].coordinate.x = proiettile[numeroProiettili - 1].coordinate.x + 2;
                    proiettile[numeroProiettili - 1].fazione = false;
                    proiettile[numeroProiettili - 1].pid = NuovoProiettile(proiettile[numeroProiettili - 1].pipe,
                                                                          proiettile[numeroProiettili - 1].coordinate,
                                                                          proiettile[numeroProiettili - 1].fazione);
                }                
            }
        }

        //Recupero coordinate proiettili
        timer_end_proiettile = SecondiDaEpoch();

        if((timer_end_proiettile-timer_start_proiettile) > 0.05 * moltiplicatore_diff)
        {
            timer_start_proiettile = SecondiDaEpoch();

            for(int i = 0; i < numeroProiettili; i++)
            {
                read(proiettile[i].pipe[0], &(proiettile[i].coordinate), sizeof(struct Coordinate));
            }
        }

        //Distruzione proiettili fuori schermo
        for(int i = 0; i < numeroProiettili; i++)
        {
            if(proiettile[i].coordinate.y == MIN_Y || proiettile[i].coordinate.y == MAX_Y)
            {
                UccidiProcesso(proiettile[i].pid);

                for(int j = i; j < numeroProiettili - 1; j++)
                {
                    proiettile[j] = proiettile[j + 1];
                }

                numeroProiettili = numeroProiettili - 1;

                proiettile = (struct Proiettile*)
                                realloc(proiettile, sizeof(struct Proiettile) * numeroProiettili);

                i--;
            }
        }

        //Verifica collisione proiettilli nemici con rana
        for(int i = 0; i < numeroProiettili; i++)
        {
            if(proiettile[i].coordinate.y == rana.coordinate.y &&
                 (proiettile[i].coordinate.x >= rana.coordinate.x &&
                    proiettile[i].coordinate.x <= rana.coordinate.x + 2) &&
                    proiettile[i].fazione == false)
            {
                //Distruzione proiettile
                UccidiProcesso(proiettile[i].pid);

                close(proiettile[i].pipe[0]);

                for(int j = i; j < numeroProiettili - 1; j++)
                {
                    proiettile[j] = proiettile[j + 1];
                }

                numeroProiettili = numeroProiettili - 1;

                proiettile = (struct Proiettile*)
                                realloc(proiettile, sizeof(struct Proiettile) * numeroProiettili);

                i--;
                
                if(rana.perk == SCUDO)
                {
                    rana.perk = NESSUNO;
                }
                else if(rana.vite > 0)
                {
                    //Danneggia rana
                    if(rana.perk == DOPPIO_DANNO)
                    {
                        rana.vite = rana.vite - 2;
                    }
                    else
                    {
                        rana.vite = rana.vite - 1;
                    }

                    //Riproduzione effetto sonoro
                    system("aplay -q -t wav Sounds/frogdamage.wav & >/dev/null 2> /dev/null");

                    //Riporta rana a posizione iniziale
                    rana.coordinate.x = START_X;
                    rana.coordinate.y = START_Y;

                    //Cancellazione perk
                    rana.perk = NESSUNO;

                    punteggio -= PUNTI_PERDITA_VITA;                   
                }
            }
        }

        //Verifica rana in acqua
        ranainacqua = true;

        if(rana.coordinate.y >= INIZIO_ACQUA_Y && rana.coordinate.y <= FINE_ACQUA_Y)
        {
            for(int i = 0; i < NUMERO_CORSIE; i++)
            {
                for(int j = 0; j < NUMERO_COCCO; j++)
                {
                    if(rana.coordinate.y == coccodrillo[i][j].coordinate.y && 
                        rana.coordinate.x >= 0 && rana.coordinate.x < MAX_X - 2)
                    {
                        if(rana.coordinate.x >= coccodrillo[i][j].coordinate.x &&
                            rana.coordinate.x <= coccodrillo[i][j].coordinate.x + DIMENSIONE_X_COCCO ||
                            (coccodrillo[i][j].coordinate.x > MAX_X - DIMENSIONE_X_COCCO && 
                            (
                            rana.coordinate.x >= coccodrillo[i][j].coordinate.x ||
                            rana.coordinate.x <= (coccodrillo[i][j].coordinate.x + DIMENSIONE_X_COCCO) % (MAX_X + 1)
                            )))
                            {
                                ranainacqua = false;
                            }
                    }
                }
            }
        }
        else
        {
            ranainacqua = false;
        }

        if(ranainacqua == true)
        {
            //Danneggia e riporta rana a posizione iniziale
            rana.coordinate.x = START_X;
            rana.coordinate.y = START_Y;

            rana.vite = rana.vite - 1;

            //Cancellazione perk
            rana.perk = NESSUNO;

            punteggio -= PUNTI_PERDITA_VITA;

            //Riproduzione effetto sonoro
            system("aplay -q -t wav Sounds/dive.wav & >/dev/null 2> /dev/null");
        }

        //Verifica collisione rana con pianta
        for(int i = 0; i < NUMERO_PIANTE; i++)
        {
            if(rana.coordinate.x >= pianta[i].coordinate.x - 1 &&
                rana.coordinate.x <= pianta[i].coordinate.x + 2 &&
                rana.coordinate.y >= pianta[i].coordinate.y &&
                rana.coordinate.y <= pianta[i].coordinate.y + 2 && pianta[i].vite > 0)
            {
                //Danneggia e riporta rana a posizione iniziale
                rana.coordinate.x = START_X;
                rana.coordinate.y = START_Y;

                rana.vite = rana.vite - 1;

                //Riproduzione effetto sonoro
                system("aplay -q -t wav Sounds/frogdamage.wav & >/dev/null 2> /dev/null");

                //Cancellazione perk
                rana.perk = NESSUNO;

                punteggio -= PUNTI_PERDITA_VITA;
            }
        }

        //Sparo rana
        read(rana.pipesparo[0], &ranashoot, sizeof(char));

        //Check cooldown
        timer_end_cooldown = SecondiDaEpoch();

        if((timer_end_cooldown-timer_start_cooldown) > 0.2)
        {
            timer_start_cooldown = SecondiDaEpoch();

            cooldown = true;
        }

        if(ranashoot == ' ' && cooldown == true && rana.perk != PISTOLA_ROTTA)
        {
            //Reset cooldown
            cooldown = false;

            //Aggiungi proiettile sinistro
            numeroProiettili = numeroProiettili + 1;

            proiettile = (struct Proiettile*)
                            realloc(proiettile, sizeof(struct Proiettile) * numeroProiettili);

            proiettile[numeroProiettili - 1].coordinate = rana.coordinate;
            proiettile[numeroProiettili - 1].coordinate.y = proiettile[numeroProiettili - 1].coordinate.y - 1;
            proiettile[numeroProiettili - 1].coordinate.x = proiettile[numeroProiettili - 1].coordinate.x;
            proiettile[numeroProiettili - 1].fazione = true;
            proiettile[numeroProiettili - 1].pid = NuovoProiettile(proiettile[numeroProiettili - 1].pipe,
                                                            proiettile[numeroProiettili - 1].coordinate,
                                                            proiettile[numeroProiettili - 1].fazione);

            //Aggiungi proiettile destro
            numeroProiettili = numeroProiettili + 1;

            proiettile = (struct Proiettile*)
                            realloc(proiettile, sizeof(struct Proiettile) * numeroProiettili);

            proiettile[numeroProiettili - 1].coordinate = rana.coordinate;
            proiettile[numeroProiettili - 1].coordinate.y = proiettile[numeroProiettili - 1].coordinate.y - 1;
            proiettile[numeroProiettili - 1].coordinate.x = proiettile[numeroProiettili - 1].coordinate.x + 2;
            proiettile[numeroProiettili - 1].fazione = true;
            proiettile[numeroProiettili - 1].pid = NuovoProiettile(proiettile[numeroProiettili - 1].pipe,
                                                            proiettile[numeroProiettili - 1].coordinate,
                                                            proiettile[numeroProiettili - 1].fazione);

            //Riproduzione effetto sonoro
            system("aplay -q -t wav Sounds/frogbullet.wav & >/dev/null 2> /dev/null");
        }
        else if(ranashoot == 'p')
        {
            //Implementazione pausa
            pausa = true;

            //Riproduzione effetto sonoro
            system("aplay -q -t wav Sounds/pause.wav & >/dev/null 2> /dev/null");
        }

        //Verifica collisione proiettili rana con nemici
        for(int i = 0; i < numeroProiettili; i++)
        {
            for(int j = 0; j < NUMERO_CORSIE && numeroProiettili > 0; j++)
            {
                for(int k = 0; k < NUMERO_COCCO && numeroProiettili > 0; k++)
                {
                    if((proiettile[i].coordinate.y >= coccodrillo[j][k].coordinate.y &&
                        proiettile[i].coordinate.y <= coccodrillo[j][k].coordinate.y + 1) &&
                        (proiettile[i].coordinate.x >= coccodrillo[j][k].coordinate.x &&
                        proiettile[i].coordinate.x < coccodrillo[j][k].coordinate.x + DIMENSIONE_X_COCCO ||
                        (coccodrillo[j][k].coordinate.x > (MAX_X - DIMENSIONE_X_COCCO) && 
                        (
                            proiettile[i].coordinate.x >= coccodrillo[j][k].coordinate.x ||
                            proiettile[i].coordinate.x <= (coccodrillo[j][k].coordinate.x + DIMENSIONE_X_COCCO) % (MAX_X + 1)
                        ))) &&
                        proiettile[i].fazione == true)
                    {
                        //Distruzione proiettile
                        if(rana.perk != TRAPASSA_COCCODRILLI)
                        {
                            UccidiProcesso(proiettile[i].pid);

                            close(proiettile[i].pipe[0]);

                            numeroProiettili = numeroProiettili - 1;

                            for(int l = i; l < numeroProiettili; l++)
                            {
                               proiettile[l] = proiettile[l + 1];
                            }

                            proiettile = (struct Proiettile*)
                                    realloc(proiettile, sizeof(struct Proiettile) * numeroProiettili);

                            i--;

                            //Riproduzione effetto sonoro
                            system("aplay -q -t wav Sounds/step.wav & >/dev/null 2> /dev/null");
                        }
                        
                        //Trasforma coccodrillo
                        if(coccodrillo[j][k].buono == false)
                        {
                            coccodrillo[j][k].buono = true;

                            punteggio += PUNTI_TRASFORMAZIONE_COCCODRILLO;
                        }
                    }
                }
            }

            for(int k = 0; k < NUMERO_PIANTE && numeroProiettili > 0; k++)
            {
                if((proiettile[i].coordinate.y >= pianta[k].coordinate.y &&
                    proiettile[i].coordinate.y <= pianta[k].coordinate.y + 2) &&
                    (proiettile[i].coordinate.x >= pianta[k].coordinate.x &&
                    proiettile[i].coordinate.x <= pianta[k].coordinate.x + 2) &&
                    proiettile[i].fazione == true)
                {
                    //Distruzione proiettile
                    UccidiProcesso(proiettile[i].pid);

                    close(proiettile[i].pipe[0]);

                    numeroProiettili = numeroProiettili - 1;

                    for(int l = i; l < numeroProiettili; l++)
                    {
                       proiettile[l] = proiettile[l + 1];
                    }

                    proiettile = (struct Proiettile*)
                                realloc(proiettile, sizeof(struct Proiettile) * numeroProiettili);

                    i--;
                    
                    //Danneggiamento pianta
                    if(rana.perk == ONE_SHOT && pianta[k].vite > 0)
                    {
                        pianta[k].vite = 0;

                        //Riproduzione effetto sonoro
                        system("aplay -q -t wav Sounds/plantdeath.wav & >/dev/null 2> /dev/null");
                    }
                    else if(pianta[k].vite > 0 && rana.perk != PIANTE_IMMUNI)
                    {
                        pianta[k].vite = pianta[k].vite - 1;

                        if(pianta[k].vite == 0)
                        {
                            punteggio += PUNTI_KILL_PIANTA;
                        }

                        //Riproduzione effetto sonoro
                        if(pianta[k].vite > 0)
                        {
                            system("aplay -q -t wav Sounds/plantdamage.wav & >/dev/null 2> /dev/null");
                        }
                        else
                        {
                            system("aplay -q -t wav Sounds/plantdeath.wav & >/dev/null 2> /dev/null");
                        }
                    }
                }
            }

            for(int k = 0; k < numeroProiettili; k++)
            {
                if(proiettile[i].coordinate.y <= proiettile[k].coordinate.y &&
                    (proiettile[i].coordinate.x == proiettile[k].coordinate.x &&
                    proiettile[i].fazione == true && proiettile[k].fazione == false))
                {
                    //Distruzione proiettile amico
                    UccidiProcesso(proiettile[i].pid);

                    close(proiettile[i].pipe[0]);

                    numeroProiettili = numeroProiettili - 1;

                    for(int l = i; l < numeroProiettili; l++)
                    {
                       proiettile[l] = proiettile[l + 1];
                    }

                    proiettile = (struct Proiettile*)
                                realloc(proiettile, sizeof(struct Proiettile) * numeroProiettili);

                    i--;

                    if(k > i)
                    {
                        k--;
                    }
                        
                    //Distruzione proiettile nemico
                    UccidiProcesso(proiettile[k].pid);

                    close(proiettile[k].pipe[0]);

                    numeroProiettili = numeroProiettili - 1;

                    for(int l = k; l < numeroProiettili; l++)
                    {
                       proiettile[l] = proiettile[l + 1];
                    }

                    proiettile = (struct Proiettile*)
                                realloc(proiettile, sizeof(struct Proiettile) * numeroProiettili);

                    k--;

                    //Aggiunta punteggio
                    punteggio += PUNTI_DISTRUZIONE_PROIETTILE;

                    //Riproduzione effetto sonoro
                    system("aplay -q -t wav Sounds/step.wav & >/dev/null 2> /dev/null");
                    
                }
            }
        }

        //Verifica collisione rana con tana
        for(int i = 0; i < NUMERO_TANE; i++)
        {
            if(rana.coordinate.x >= tana[i].coordinate.x - RANGE_TANA_SINISTRO &&
                rana.coordinate.x <= tana[i].coordinate.x + RANGE_TANA_DESTRO &&
                rana.coordinate.y == tana[i].coordinate.y + 1)
                {
                    if(tana[i].done == false)
                    {
                        tana[i].done = true;

                        taneprese = taneprese + 1;

                        //Riaggiustamento moltiplicatore
                        moltiplicatore_diff -= MALUS_TEMPO_TANA;

                        punteggio += PUNTI_TANA_PRESA;

                        //Assegnazione perk
                        if(tana[i].perk == HP_UP)
                        {
                            if(rana.vite < 5)
                            {
                                rana.vite += 1;
                            }

                            //Riproduzione effetto sonoro
                            system("aplay -q -t wav Sounds/hpup.wav & >/dev/null 2> /dev/null");
                        }
                        else if(tana[i].perk == AMMAZZA_PIANTE)
                        {
                            for(int j = 0; j < NUMERO_PIANTE; j++)
                            {
                                pianta[j].vite = 0;
                            }

                            //Riproduzione effetto sonoro
                            system("aplay -q -t wav Sounds/plantdeath.wav & >/dev/null 2> /dev/null");
                        }
                        else if(tana[i].perk == PERDI_TANA)
                        {
                            tana_tolta = false;

                            //Annullamento malus tempo
                            moltiplicatore_diff += MALUS_TEMPO_TANA;

                            contatore = 0;

                            while(tana_tolta == false)
                            {
                                if(tana[contatore].done == true)
                                {
                                    tana[contatore].done = false;
                                    taneprese--;
                                    tana_tolta = true;
                                }

                                contatore++;
                            }

                            //Riproduzione effetto sonoro
                            system("aplay -q -t wav Sounds/loseagate.wav & >/dev/null 2> /dev/null");
                        }
                        else
                        {
                            rana.perk = tana[i].perk;

                            //Riproduzione effetto sonoro
                            if(rana.perk == SCUDO)
                            {
                                system("aplay -q -t wav Sounds/shield.wav & >/dev/null 2> /dev/null");
                            }
                            else if(rana.perk == PISTOLA_ROTTA)
                            {
                                system("aplay -q -t wav Sounds/gunbroken.wav & >/dev/null 2> /dev/null");
                            }
                            else if(rana.perk == DOPPIO_DANNO)
                            {
                                system("aplay -q -t wav Sounds/doubledamage.wav & >/dev/null 2> /dev/null");
                            }
                            else if(rana.perk == PIANTE_IMMUNI)
                            {
                                system("aplay -q -t wav Sounds/immuneplants.wav & >/dev/null 2> /dev/null");
                            }
                            else if(rana.perk == ONE_SHOT)
                            {
                                system("aplay -q -t wav Sounds/oneshot.wav & >/dev/null 2> /dev/null");
                            }
                            else if(rana.perk == TRAPASSA_COCCODRILLI)
                            {
                                system("aplay -q -t wav Sounds/nocrocohit.wav & >/dev/null 2> /dev/null");
                            }
                            else if(rana.perk == FULL_RAMBO)
                            {
                                system("aplay -q -t wav Sounds/fullrambo.wav & >/dev/null 2> /dev/null");
                            }
                            
                        }

                        tana[i].perk = NESSUNO;

                        //Randomizzazione direzione coccodrilli
                        randomvalue = ((rand() % 10) + 1);

                        for(int i = 0; i < NUMERO_CORSIE; i++)
                        {
                            for(int j = 0; j < NUMERO_COCCO; j++)
                            {
                                //Switch direzione coccodrilli
                                if(randomvalue < 5)
                                {
                                    if(coccodrillo[i][j].direzione == 0)
                                    {
                                        coccodrillo[i][j].direzione = 1;
                                    }
                                    else
                                    {
                                        coccodrillo[i][j].direzione = 0;
                                    }                                    
                                }
                            }
                        }

                    }
                    else
                    {
                        //Danneggia rana
                        rana.vite = rana.vite - 1;

                        //Diminuzione punteggio
                        punteggio -= PUNTI_PERDITA_VITA;

                        //Cancellazione perk
                        rana.perk = NESSUNO;

                        //Riproduzione effetto sonoro
                        system("aplay -q -t wav Sounds/gatetaken.wav & >/dev/null 2> /dev/null");
                    }

                    //Trasformazione casuale coccodrilli cattivi
                    for(int j = 0; j < coccodrilli_da_trasformare; j++)
                    {
                        randomvalue = rand() % NUMERO_CORSIE;
                        randomvalue2 = rand() % NUMERO_COCCO;

                        coccodrillo[(int)randomvalue][(int)randomvalue2].buono = false;
                    }
                
                    //Riporta rana a posizione iniziale
                    rana.coordinate.x = START_X;
                    rana.coordinate.y = START_Y;

                    //Reset tempo
                    punteggio += tempomax - tempotrascorso;
                    tempotrascorso = 0;
                }
        }
        
        //Verifica respawn piante
        timer_end_respawn = SecondiDaEpoch();

        if((timer_end_respawn-timer_start_respawn) > 20 * moltiplicatore_diff)
        {
            timer_start_respawn = SecondiDaEpoch();

            for(int i = 0; i < NUMERO_PIANTE; i++)
            {
                if(pianta[i].vite <= 0)
                {
                    //Reset vite piante
                    pianta[i].vite = VITE_PIANTA;
                }
            }

            system("aplay -q -t wav Sounds/plantrespawn.wav & >/dev/null 2> /dev/null");
        }

        //Controllo sconfitta
        if(rana.vite <= 0 || tempotrascorso >= tempomax)
        {
            //Impostazione valore di ritorno (sconfitta)
            risultato.punteggio = punteggio;
            risultato.vittoria = false;
            fine = true;
        }

        //Riscrittura coordinate rana sul suo processo
        write(rana.backpipe[1], &rana.coordinate, sizeof(struct Coordinate));

        //Stampa schermo
        timer_end_frame = SecondiDaEpoch();
        
        if((timer_end_frame-timer_start_frame) > (float) 1 / framerate)
        {
            timer_start_frame = SecondiDaEpoch();

            Stampa(&rana, tana, pianta, coccodrillo, proiettile, numeroProiettili, pausa,
                    tempotrascorso, tempomax, punteggio, difficolta, highscore);
        }   

        
        //Verifica condizioni di vittoria
        if(taneprese == NUMERO_TANE)
        {
            //Aggiunta punteggio
            punteggio += PUNTI_VITTORIA;
            
            fine = true;

            risultato.punteggio = punteggio;
            risultato.vittoria = true;
        }

        }
        else //Se in pausa
        {
            //Verifica ripressione tasto P
            ranashoot = getch();

            if(ranashoot == 'p')
            {
                pausa = false;

                //Riproduzione effetto sonoro
                system("aplay -q -t wav Sounds/pause.wav & >/dev/null 2> /dev/null");
            }

            tempo_start = SecondiDaEpoch();

            //Stampa schermo
            Stampa(&rana, tana, pianta, coccodrillo, proiettile, numeroProiettili, pausa,
                    tempotrascorso, tempomax, punteggio, difficolta, highscore);

            //Implementazione loop dell'ost
            if (access("temp.bin", F_OK) != 0) 
            {
                system("aplay -q -t wav Sounds/ost.wav --process-id-file temp.bin >/dev/null 2> /dev/null &");

                usleep(150000); //Pausa anti-doppia riproduzione
            }
        }
    }

    //Kill dei processi
    UccidiProcesso(rana.pid);

    for(int i = 0; i < NUMERO_TANE; i++)
    {
        UccidiProcesso(tana[i].pid);
    }

    for(int i = 0; i < NUMERO_PIANTE; i++)
    {
        UccidiProcesso(pianta[i].pid);
    }

    for(int i = 0; i < NUMERO_CORSIE; i++)
    {
        for(int j = 0; j < NUMERO_COCCO; j++)
        {
            UccidiProcesso(coccodrillo[i][j].pid);
        }
    }

    for(int i = 0; i < numeroProiettili; i++)
    {
        UccidiProcesso(proiettile[i].pid);
    }

    //Chiusura di tutti i fd
    close(rana.pipe[0]);
    close(rana.backpipe[1]);
    close(rana.pipesparo[0]);

    for(int i = 0; i < NUMERO_PIANTE; i++)
    {
        close(pianta[i].pipe[0]);
    }

    for(int i = 0; i < NUMERO_CORSIE; i++)
    {
        for(int j = 0; j < NUMERO_COCCO; j++)
        {
            close(coccodrillo[i][j].pipe[0]);
            close(coccodrillo[i][j].backpipe[1]);
        }
    }

    for(int i = 0; i < numeroProiettili; i++)
    {
        close(proiettile[i].pipe[0]);
    }

    //Uccisione processo dell'OST
    system(killstring);

    usleep(150000);

    system("rm temp.bin");

    //Pulizia dello schermo
    clear();

    return risultato;
}

