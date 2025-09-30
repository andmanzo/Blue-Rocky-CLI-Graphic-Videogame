void NuovaRana(struct CommRana* comunicazione)
{
    char buffer;

    //Loop del thread
    while(true)
    {
        if(comunicazione->scritto == false)
        {
            if(comunicazione->termina == true)
            {
                return;
            }

            //Acquisizione carattere
            buffer = getch();

            comunicazione->carattere = buffer;

            comunicazione->scritto = true;
        }
        
    }
}


void NuovaTana(struct CommTana* comunicazione)
{
    //Loop del thread
    while(1)
    {
        if(comunicazione->termina == true)
        {
            return;
        }

        usleep(50000);
    }
}

void NuovaPianta(struct CommPianta* comunicazione)
{
    //Loop del thread
    while(1)
    {
        pthread_mutex_lock(&(comunicazione->mutex));

        if(comunicazione->termina == true)
        {
            return;
        }

        //Comunica segnale di sparo
        comunicazione->messaggio = true;
    }
 
}

void NuovoCoccodrillo(struct CommCoccodrillo* comunicazione)
{
    //Inizializzazione variabili
    float randomvalue;

    //Loop del thread
    while(true)
    {
        //Mutex lock
        pthread_mutex_lock(&(comunicazione->mutex));

        if(comunicazione->termina == true)
        {
            return;
        }

        
        //Eventuale immersione coccodrilli cattivi
        if(comunicazione->buono == false)
        {
            randomvalue = (float)(rand() % 1000) / 1000;

            if(randomvalue > 0.975 && comunicazione->messaggio.y > 0)
            {
                comunicazione->messaggio.y = comunicazione->messaggio.y - 100;

                //Riproduzione effetto sonoro
                system("aplay -q -t wav Sounds/immersion.wav & >/dev/null 2> /dev/null");
            }

            randomvalue = (float)(rand() % 1000) / 1000;

            if(randomvalue > 0.975 && comunicazione->messaggio.y < 0)
            {
                comunicazione->messaggio.y = comunicazione->messaggio.y + 100;
            }
        }
            
        //Movimento coccodrillo
        if(comunicazione->direzione == 1)
        {

            if(comunicazione->messaggio.x == MAX_X - 1)
            {
                comunicazione->messaggio.x = 0;
            }
            else
            {
                comunicazione->messaggio.x = comunicazione->messaggio.x + 1;
            }
        }
        else if(comunicazione->direzione == 0)
        {
            if(comunicazione->messaggio.x == 0)
            {
                comunicazione->messaggio.x = MAX_X - 1;
            }
            else
            {
                comunicazione->messaggio.x = comunicazione->messaggio.x - 1;
            }
        }
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

void NuovoProiettile(struct CommProiettile* comunicazione)
{
    //Loop del thread
    while(true)
    {
        pthread_mutex_lock(&(comunicazione->mutex));

        if(comunicazione->termina == true)
        {
            return;
        }

        //Movimento proiettile

        if(/*comunicazione->scritto == false && */comunicazione->termina == false)
        {
            if(comunicazione->fazione == true)
            {
                if(comunicazione->messaggio.y > MIN_Y)
                {
                    comunicazione->messaggio.y = comunicazione->messaggio.y - 1;
                }
                
            }
            else
            {
                if(comunicazione->messaggio.y < MAX_Y + 1)
                {
                    comunicazione->messaggio.y = comunicazione->messaggio.y + 1;
                }
            }

            //comunicazione->scritto = true;
        }
    }
}