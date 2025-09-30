int NuovaRana(int* pipecoord, int* backpipe, int* pipesparo)
{
    //Inizializzazione variabili
    char buffer;
    struct Coordinate coordinate;
    coordinate.x = START_X;
    coordinate.y = START_Y;
    pid_t pid;

    //Creazione pipes
    pipe(pipecoord);
    pipe(backpipe);
    pipe(pipesparo);

    //Fork
    pid = fork();

    if(pid == 0) //Figlio
    {
        //Chiusura pipes
        close(pipecoord[0]);
        close(backpipe[1]);
        close(pipesparo[0]);

        //Loop del processo
        while(true)
        {
            //Acquisizione carattere
            buffer = getch();
            
            switch(buffer)
            {
                case 'w':                             
                            if(coordinate.y > 7)
                            {
                                if(coordinate.y >= INIZIO_ACQUA_Y + 1 && coordinate.y <= FINE_ACQUA_Y)
                                {
                                    coordinate.y = coordinate.y - 3;
                                }
                                else
                                {
                                    coordinate.y = coordinate.y - 2;
                                }
                            }

                            break;
                case 's': 
                            if(coordinate.y < 39)
                            {
                                if(coordinate.y >= INIZIO_ACQUA_Y && coordinate.y <= FINE_ACQUA_Y - 1)
                                {
                                    coordinate.y = coordinate.y + 3;
                                }
                                else
                                {
                                    coordinate.y = coordinate.y + 2;
                                }
                            }

                            break;
                case 'a': 
                            if(coordinate.x > 0)
                            {
                                coordinate.x = coordinate.x - 1;
                            }

                            break;
                case 'd': 
                            if(coordinate.x < MAX_X - 3)
                            {
                                coordinate.x = coordinate.x + 1;
                            }

                            break;     
                default:
                            break;

                
            }

            //Interazioni con le pipes
            write(pipesparo[1], &buffer, sizeof(char));

            
            write(pipecoord[1], &coordinate, sizeof(struct Coordinate));
            
            
            read(backpipe[0], &coordinate, sizeof(struct Coordinate));
        }
    }
    else if(pid > 0) //Padre
    {
        //Chiusura pipes
        close(pipecoord[1]);
        close(backpipe[0]);
        close(pipesparo[1]);

        //Restituzione pid
        return pid;
    }
    else
    {
        //Errore
        exit(-1);
    }
}

int NuovaTana()
{
    //Inizializzazione variabile
    pid_t pid;

    //Fork
    pid = fork();

    if(pid == 0) //Figlio
    {
        //Loop del processo
        while(1)
        {
            usleep(10000000);
        }
    }
    else if(pid > 0) //Padre
    {
        //Restituzione pid
        return pid;
    }
    else
    {
        //Errore
        exit(-1);
    }
}

int NuovaPianta(int* pipesparo)
{
    //Inizializzazione variabili
    pid_t pid;
    bool sparo = true;

    //Creazione pipe
    pipe(pipesparo);
    
    //Fork
    pid = fork();

    if(pid == 0) //Figlio
    {
        //Chiusura pipe
        close(pipesparo[0]);

        //Loop del processo
        while(1)
        {
            //Manda segnale di sparo sulla pipe
            write(pipesparo[1], &sparo, sizeof(bool));
        }
    }
    else if(pid > 0) //Padre
    {
        //Chiusura pipe
        close(pipesparo[1]);

        //Restituzione pid
        return pid;
    }
    else
    {
        //Errore
        exit(-1);
    }
}

int NuovoCoccodrillo(struct Coccodrillo* coccodrillo)
{
    //Inizializzazione variabili
    struct Coordinate coordinate;
    coordinate = coccodrillo->coordinate;
    bool direzione = coccodrillo->direzione;
    pid_t pid;
    float randomvalue;
    bool bravo;

    //Creazione pipes
    pipe(coccodrillo->pipe);
    pipe(coccodrillo->backpipe);
    pipe(coccodrillo->backpipe2);

    //Fork
    pid = fork();

    if(pid == 0) //Figlio
    {
        //Chiusura pipes
        close(coccodrillo->pipe[0]);
        close(coccodrillo->backpipe[1]);
        close(coccodrillo->backpipe2[1]);

        //Setting del valore buono
        bravo = coccodrillo->buono;

        //Loop del processo
        while(true)
        {
            //Lettura valore buono dalla pipe
            read(coccodrillo->backpipe[0], &bravo, sizeof(bool));

            //Lettura direzione dalla pipe
            read(coccodrillo->backpipe2[0], &direzione, sizeof(bool));
            
            //Eventuale immersione coccodrilli cattivi
            if(bravo == false)
            {
                randomvalue = (float)(rand() % 1000) / 1000;

                if(randomvalue > 0.975 && coordinate.y > 0)
                {
                    coordinate.y = coordinate.y - 100;

                    //Riproduzione effetto sonoro
                    system("aplay -q -t wav Sounds/immersion.wav & >/dev/null 2> /dev/null");
                }

                randomvalue = (float)(rand() % 1000) / 1000;

                if(randomvalue > 0.975 && coordinate.y < 0)
                {
                    coordinate.y = coordinate.y + 100;
                }
            }
            
            //Movimento coccodrillo
            if(direzione == 1)
            {

                if(coordinate.x == MAX_X - 1)
                {
                    coordinate.x = 0;
                }
                else
                {
                    coordinate.x = coordinate.x + 1;
                }
            }
            else if(direzione == 0)
            {
                if(coordinate.x == 0)
                {
                    coordinate.x = MAX_X - 1;
                }
                else
                {
                    coordinate.x = coordinate.x - 1;
                }
            }

            //Scrittura nuove coordinate sulla pipe
            write(coccodrillo->pipe[1], &coordinate, sizeof(struct Coordinate));
        }
    }
    else if(pid > 0) //Padre
    {
        //Chiusura pipe
        close(coccodrillo->pipe[1]);
        close(coccodrillo->backpipe[0]);
        close(coccodrillo->backpipe2[0]);

        //Restituzione pid
        return pid;
    }
    else
    {
        //Errore
        exit(-1);
    }
}

void UccidiProcesso(int pid)
{
    int statloc;

    //Kill del processo
    kill(pid, SIGKILL);

    //Attesa
    waitpid(pid, &statloc, 0);
}

int NuovoProiettile(int* pipep, struct Coordinate coordinate, bool fazione)
{
    //Inizializzazione variabili
    pid_t pid;

    //Creazione pipe
    pipe(pipep);

    //Fork
    pid = fork();

    if(pid == 0) //Figlio
    {
        //Chiusura pipe
        close(pipep[0]);

        //Loop del processo
        while(true)
        {
            //Movimento proiettile
            if(fazione == true)
            {
                if(coordinate.y > MIN_Y)
                {
                    coordinate.y = coordinate.y - 1;
                }
                
            }
            else
            {
                if(coordinate.y < MAX_Y + 1)
                {
                    coordinate.y = coordinate.y + 1;
                }
            }

            //Scrittura nuove coordinate in pipe
            write(pipep[1], &coordinate, sizeof(struct Coordinate));
        }
    }
    else if (pid > 0) //Padre
    {
        //Chiusura pipe
        close(pipep[1]);

        //Restituzione pid
        return pid;
    }
    else
    {
        //Errore
        exit(-1);
    }
}