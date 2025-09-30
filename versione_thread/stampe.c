void DefinisciColori()
{
    start_color();   

    //Definizione colori
    init_color(COLOR_FROG_BLUE, 120, 420 ,810);
    init_color(COLOR_FROG_YELLOW, 1000, 1000, 0);
    init_color(COLOR_TANA_ORANGE, 244, 70, 17);
    init_color(COLOR_PLANT_GREEN, 57, 255, 20);
    init_color(COLOR_PERK_BOX, 37, 34, 30);
    init_color(COLOR_PERK_CHARS, 169, 169, 169);
    init_color(COLOR_UNDERWATER, 195, 484, 600);
    init_color(COLOR_WATER, 50, 740, 712);
    init_color(COLOR_GREY_GUI, 255, 255, 255);
    init_color(COLOR_GOLD_PERK, 1000, 900, 8);
    init_color(COLOR_BEIGE, 840, 700, 500);
    init_color(COLOR_BROWN, 510, 240, 200);
    init_color(COLOR_CROCO, 340, 640, 340);
    init_color(COLOR_CROCO_RED, 800, 80, 80);
    init_color(COLOR_SAND, 800, 750, 400);
    init_color(COLOR_PRO_FROG, 56, 300, 955);
    init_color(COLOR_PRO_PLANT, 780, 80, 490);
    
    //Definizione coppie colore
    init_pair(1, COLOR_BROWN, COLOR_YELLOW);//Muro
    init_pair(2, COLOR_PLANT_GREEN, COLOR_SAND);//Pianta
    init_pair(3, COLOR_WATER, COLOR_WATER);//Acqua
    init_pair(4, COLOR_FROG_YELLOW, COLOR_FROG_BLUE);//Rana Con Perk
    init_pair(5, COLOR_TANA_ORANGE, COLOR_RED);//Tana da Prendere
    init_pair(6, COLOR_TANA_ORANGE, COLOR_FROG_BLUE);//Tana Presa
    init_pair(7, COLOR_PLANT_GREEN, COLOR_CROCO);//Coccodrilli Verdi
    init_pair(8, COLOR_PERK_CHARS, COLOR_YELLOW);//Perk Box
    init_pair(9, COLOR_TANA_ORANGE, COLOR_UNDERWATER);//Coccodrilli Immersi
    init_pair(10, COLOR_GREY_GUI, COLOR_BEIGE);//Scritte GUI
    init_pair(11, COLOR_GOLD_PERK, COLOR_YELLOW);//Perk In Game
    init_pair(12, COLOR_GOLD_PERK, COLOR_BEIGE);//Perk GUI
    init_pair(13, COLOR_PLANT_GREEN, COLOR_SAND);//Pianta
    init_pair(14, COLOR_BLACK, COLOR_CROCO_RED);//Coccodrilli Rossi
    init_pair(15, COLOR_WHITE, COLOR_PRO_FROG);//Proiettili Rana
    init_pair(16, COLOR_WHITE, COLOR_PRO_PLANT);//Proiettili Pianta
    init_pair(17, COLOR_PLANT_GREEN, COLOR_BLACK);//GUI
    init_pair(18, COLOR_WHITE, COLOR_FROG_BLUE);//Rana Senza Perk
    init_pair(19, COLOR_WHITE, COLOR_BLACK);//GUI Pausa
}

void Stampa(struct Rana* rana, struct Tana* tana, struct Pianta* pianta,
            struct Coccodrillo coccodrillo[8][3], struct Proiettile* proiettile, int nProiettili,
            bool pausa, float tempotrascorso, float tempomax, int punteggio, Difficolta difficolta,
            int highscore)
{
    char appoggio_coccodrillo[2][9];

    //Stampa sfondo
    attron(COLOR_PAIR(1));

    mvaddstr(0, 0, "             |___|                       ___            ");//56 spazi
    mvaddstr(1, 0, "___                                |___|           ___  ");//56 spazi
    mvaddstr(2, 0, "___| ___               _             _       ___        ");//56 spazi
    mvaddstr(3, 0, "    |___|                                   |___|       ");//56 spazi
    mvaddstr(4, 0, "    ___              _        _                   ___   ");//56 spazi
    mvaddstr(5, 0, "   |___|         _   _   ___         _   _       |___|  ");//56 spazi
    mvaddstr(6, 0, "        |    |___|              |    |___|              ");//56 spazi
    mvaddstr(7, 0, "___                                                     ");//56 spazi
    mvaddstr(8, 0, "___|         __                 |   _      _        ___ ");//56 spazi
    mvaddstr(9, 0, "                      __                           |___|");//56 spazi




    attron(COLOR_PAIR(2));
    mvaddstr(10, 0, "     ~           ~               ~        ~        ~    ");//56 spazi
    mvaddstr(10, 0, "                ~          ~      ~             ~       ");//56 spazi
    mvaddstr(11, 0, " ~       ~           ~             ~    ~          ~    ");//56 spazi
    mvaddstr(12, 0, "    ~       ~                ~             ~            ");//56 spazi
    mvaddstr(13, 0, "     ~      ~     ~            ~              ~         ");//56 spazi
    mvaddstr(14, 0, "                                                        ");//56 spazi
    mvaddstr(38, 0, "   ~               ~                ~                   ");//56 spazi
    mvaddstr(39, 0, "             ~           ~               ~         ~    ");//56 spazi
    mvaddstr(40, 0, "                          ~                             ");//56 spazi
    mvaddstr(41, 0, "   ~        ~                 ~            ~       ~    ");//56 spazi

    attron(COLOR_PAIR(3));
    for ( int i = INIZIO_ACQUA_Y; i < FINE_ACQUA_Y + 2; i++)
    {
        mvaddstr(i, 0, "                                                        ");//56 spazi
    }

    //Stampa tane
    for(int i = 0; i < NUMERO_TANE; i++)
    {
        if(tana[i].done == false)
        {
            attron(COLOR_PAIR(5));
        }
        else
        {
            attron(COLOR_PAIR(6));
        }

        mvaddstr(tana[i].coordinate.y, tana[i].coordinate.x, "|''|");
        mvaddstr(tana[i].coordinate.y + 1, tana[i].coordinate.x, "|  |");
        mvaddstr(tana[i].coordinate.y + 2, tana[i].coordinate.x, "|  |");
        mvaddstr(tana[i].coordinate.y + 3, tana[i].coordinate.x, "|  |");

        attron(COLOR_PAIR(8));


        mvprintw(tana[i].coordinate.y - 6, tana[i].coordinate.x - 2, " ~~~~~~ ");
        mvprintw(tana[i].coordinate.y - 5, tana[i].coordinate.x - 2, "{      }");
        mvprintw(tana[i].coordinate.y - 4, tana[i].coordinate.x - 2, "{      }");
        mvprintw(tana[i].coordinate.y - 3, tana[i].coordinate.x - 2, "{      }");
        mvprintw(tana[i].coordinate.y - 2, tana[i].coordinate.x - 2, " ~~~~~~ ");

        attron(COLOR_PAIR(11));


        if(difficolta == DIFFICILE && tana[i].perk != NESSUNO)
        {
                mvprintw(tana[i].coordinate.y - 5, tana[i].coordinate.x - 1, "'?' ? ");
                mvprintw(tana[i].coordinate.y - 4, tana[i].coordinate.x - 1, "?  ' ?");
                mvprintw(tana[i].coordinate.y - 3, tana[i].coordinate.x - 1, "' ?' '");
        }
        else
        {
            switch(tana[i].perk)
            {
                case NESSUNO:
                                break;
                case TRAPASSA_COCCODRILLI:

                                mvprintw(tana[i].coordinate.y - 5, tana[i].coordinate.x - 1, "NO' ' ");
                                mvprintw(tana[i].coordinate.y - 4, tana[i].coordinate.x - 1, " CROCO");
                                mvprintw(tana[i].coordinate.y - 3, tana[i].coordinate.x - 1, " ' HIT");

                                break;
                case SCUDO:
                                mvprintw(tana[i].coordinate.y - 5, tana[i].coordinate.x - 1, " '  ' ");
                                mvprintw(tana[i].coordinate.y - 4, tana[i].coordinate.x - 1, "SHIELD");
                                mvprintw(tana[i].coordinate.y - 3, tana[i].coordinate.x - 1, "' ' ' ");

                                break;
                case HP_UP:
                                mvprintw(tana[i].coordinate.y - 5, tana[i].coordinate.x - 1, " ' 1 '");
                                mvprintw(tana[i].coordinate.y - 4, tana[i].coordinate.x - 1, "HP   '");
                                mvprintw(tana[i].coordinate.y - 3, tana[i].coordinate.x - 1, "'  UP'");

                                break; 
                case AMMAZZA_PIANTE:
                                mvprintw(tana[i].coordinate.y - 5, tana[i].coordinate.x - 1, " KILL'");
                                mvprintw(tana[i].coordinate.y - 4, tana[i].coordinate.x - 1, "ALL ' ");
                                mvprintw(tana[i].coordinate.y - 3, tana[i].coordinate.x - 1, "PLANTS");

                                break;
                case ONE_SHOT:
                                mvprintw(tana[i].coordinate.y - 5, tana[i].coordinate.x - 1, "ONE' '");
                                mvprintw(tana[i].coordinate.y - 4, tana[i].coordinate.x - 1, "'SHOT ");
                                mvprintw(tana[i].coordinate.y - 3, tana[i].coordinate.x - 1, "PLANTS");

                                break;
                case PIANTE_IMMUNI:
                                mvprintw(tana[i].coordinate.y - 5, tana[i].coordinate.x - 1, "'   ' ");
                                mvprintw(tana[i].coordinate.y - 4, tana[i].coordinate.x - 1, "IMMUNE");
                                mvprintw(tana[i].coordinate.y - 3, tana[i].coordinate.x - 1, "PLANTS");

                                break;
                case DOPPIO_DANNO:
                                mvprintw(tana[i].coordinate.y - 5, tana[i].coordinate.x - 1, "  ' ' ");
                                mvprintw(tana[i].coordinate.y - 4, tana[i].coordinate.x - 1, "DOUBLE");
                                mvprintw(tana[i].coordinate.y - 3, tana[i].coordinate.x - 1, "DAMAGE");

                                break;
                case PERDI_TANA:
                                mvprintw(tana[i].coordinate.y - 5, tana[i].coordinate.x - 1, "LOSE '");
                                mvprintw(tana[i].coordinate.y - 4, tana[i].coordinate.x - 1, " ' 'A ");
                                mvprintw(tana[i].coordinate.y - 3, tana[i].coordinate.x - 1, " GATE'");

                                break;
                case PISTOLA_ROTTA:
                                mvprintw(tana[i].coordinate.y - 5, tana[i].coordinate.x - 1, "  ' ''");
                                mvprintw(tana[i].coordinate.y - 4, tana[i].coordinate.x - 1, "NO '  ");
                                mvprintw(tana[i].coordinate.y - 3, tana[i].coordinate.x - 1, " ' GUN");

                                break;
                case FULL_RAMBO:
                                mvprintw(tana[i].coordinate.y - 5, tana[i].coordinate.x - 1, " ' ' ");
                                mvprintw(tana[i].coordinate.y - 4, tana[i].coordinate.x - 1, "FULL '");
                                mvprintw(tana[i].coordinate.y - 3, tana[i].coordinate.x - 1, "'RAMBO");

                                break;
                default:
                                break;
            }
        }
        
    }

    //Stampa piante

    attron(COLOR_PAIR(13));
    for(int i = 0; i < NUMERO_PIANTE; i++)
    {
        if(pianta[i].vite == 3)
        {
            mvaddstr(pianta[i].coordinate.y, pianta[i].coordinate.x, " |0");
            mvaddstr(pianta[i].coordinate.y + 1, pianta[i].coordinate.x, "l|/");
            mvaddstr(pianta[i].coordinate.y + 2, pianta[i].coordinate.x, "-| ");
        }
        else if(pianta[i].vite == 2)
        {
            mvaddstr(pianta[i].coordinate.y, pianta[i].coordinate.x, " |0");
            mvaddstr(pianta[i].coordinate.y + 1, pianta[i].coordinate.x, " |/");
            mvaddstr(pianta[i].coordinate.y + 2, pianta[i].coordinate.x, "-| ");
        }
        else if(pianta[i].vite == 1)
        {
            mvaddstr(pianta[i].coordinate.y, pianta[i].coordinate.x, " |0");
            mvaddstr(pianta[i].coordinate.y + 1, pianta[i].coordinate.x, " |/");
            mvaddstr(pianta[i].coordinate.y + 2, pianta[i].coordinate.x, " | ");
        }
        else
        {
            mvaddstr(pianta[i].coordinate.y, pianta[i].coordinate.x, "   ");
            mvaddstr(pianta[i].coordinate.y + 1, pianta[i].coordinate.x, "  ");
            mvaddstr(pianta[i].coordinate.y + 2, pianta[i].coordinate.x, " l ");
        }
        
    }

    attron(COLOR_PAIR(1));

    //Stampa coccodrilli
    for(int i = 0; i < NUMERO_CORSIE; i++)
    {
        for(int j = 0; j < NUMERO_COCCO; j++)
        {
            //Blocco di scelta colore
            if(coccodrillo[i][j].buono == true)
            {
                attron(COLOR_PAIR(7));
            }
            else
            {
                attron(COLOR_PAIR(14));
            }

            //Blocco di scelta sprite
            if(coccodrillo[i][j].direzione == 1)
            {
                if(coccodrillo[i][j].coordinate.y <= 0)
                {
                    attron(COLOR_PAIR(9));

                    strcpy(appoggio_coccodrillo[0], "        ");
                    strcpy(appoggio_coccodrillo[1], " -^--^- ");
                }
                else
                {
                    strcpy(appoggio_coccodrillo[0], "-^--^--^");
                    strcpy(appoggio_coccodrillo[1], "^--^--^-");
                }
            }
            else
            {
                if(coccodrillo[i][j].coordinate.y <= 0)
                {
                    attron(COLOR_PAIR(9));

                    strcpy(appoggio_coccodrillo[0], "        ");
                    strcpy(appoggio_coccodrillo[1], " -^--^- ");
                }
                else
                {
                    strcpy(appoggio_coccodrillo[0], "^--^--^-");//0-^--^-
                    strcpy(appoggio_coccodrillo[1], "-^--^--^");//C-U---U-
                }
            }

            //Stampa coccodrillo con effetto pacman
            for(int k = 0; k < DIMENSIONE_X_COCCO; k++)
            {
                if(appoggio_coccodrillo[0][k] != ' ')
                {
                    mvaddch(coccodrillo[i][j].coordinate.y, (coccodrillo[i][j].coordinate.x + k) % MAX_X,
                         appoggio_coccodrillo[0][k]);
                }
                
                if(appoggio_coccodrillo[1][k] != ' ')
                {
                    if(coccodrillo[i][j].coordinate.y <= 0)
                    {
                        mvaddch(coccodrillo[i][j].coordinate.y + 101, (coccodrillo[i][j].coordinate.x + k) % MAX_X,
                         appoggio_coccodrillo[1][k]);
                    }
                    else
                    {
                        mvaddch(coccodrillo[i][j].coordinate.y + 1, (coccodrillo[i][j].coordinate.x + k) % MAX_X,
                         appoggio_coccodrillo[1][k]);
                    }
                }
            }
        }
    }

    for(int i = 0; i < nProiettili; i++)
    {
        if(proiettile[i].fazione == true)
        {
            attron(COLOR_PAIR(15));
        }
        else
        {
            attron(COLOR_PAIR(16));
        }

        mvaddch(proiettile[i].coordinate.y, proiettile[i].coordinate.x, '`');
    }

    //Stampa rana
    if(rana->perk != NESSUNO)
    {
        attron(COLOR_PAIR(4));
    }
    else
    {
        attron(COLOR_PAIR(18));
    }
    
    mvaddstr(rana->coordinate.y, rana->coordinate.x, "0 0");
    mvaddstr(rana->coordinate.y + 1, rana->coordinate.x, "}R{");
    
    //Stampa GUI

    attron(COLOR_PAIR(10));

    for(int i = MIN_X_GUI; i < MIN_X_GUI + GUI_X_SIZE; i++)
    {
        for(int j = 0; j < MAX_Y; j++)
        {
            mvaddch(j, i, ' ');
        }
    }

    mvaddstr(0, MIN_X_GUI + 2, "~~~~~~~~~~~~~~~~~~~");//righe iniziali
    mvaddstr(10, MIN_X_GUI + 2, "~~~~~~~~~~~~~~~~~~~");//righe perk
    mvaddstr(26, MIN_X_GUI + 2, "~~~~~~~~~~~~~~~~~~~");//righe vita
    mvaddstr(21, MIN_X_GUI + 2, "~~~~~~~~~~~~~~~~~~~");//righe pausa
    mvaddstr(41, MIN_X_GUI + 2, "~~~~~~~~~~~~~~~~~~~");//righe chiusura
    mvaddstr(6, MIN_X_GUI + 2, "~~~~~~~~~~~~~~~~~~~");//righe tempo

    mvprintw(27, MIN_X_GUI + 8, "VITE: ");

    if(rana->perk != NESSUNO)
    {
        attron(COLOR_PAIR(4));
    }
    else
    {
        attron(COLOR_PAIR(18));
    }

    for(int i = 0; i < rana->vite && i < 3; i++){
        mvaddstr(30, MIN_X_GUI + 5 + (i * 5), "0 0");
        mvaddstr(31, MIN_X_GUI + 5 + (i * 5), "}R{");
    }

    for(int i = 3; i < rana->vite; i++)
    {
        mvaddstr(33, MIN_X_GUI + 7 + ((i - 3) * 5), "0 0");
        mvaddstr(34, MIN_X_GUI + 7 + ((i - 3) * 5), "}R{");
    }

    attron(COLOR_PAIR(10));
    mvprintw(1, MIN_X_GUI + 6, "PUNTEGGIO:" );
    mvprintw(2, MIN_X_GUI + 5, "  %5.d", punteggio);
    mvprintw(4, MIN_X_GUI + 6, "HIGH SCORE: ");
    mvprintw(5, MIN_X_GUI + 10, "%d", highscore);
    mvprintw(7, MIN_X_GUI + 8, "TEMPO:");
    mvprintw(9, MIN_X_GUI + 8, "%3.2f", tempomax - tempotrascorso);

    mvprintw(11, MIN_X_GUI + 8, "PERK: ");

    mvprintw(14, MIN_X_GUI + 7, " ~~~~~~ ");
    mvprintw(15, MIN_X_GUI + 7, "{      }");
    mvprintw(16, MIN_X_GUI + 7, "{      }");
    mvprintw(17, MIN_X_GUI + 7, "{      }");
    mvprintw(18, MIN_X_GUI + 7, " ~~~~~~ ");

    //Stampa difficolta
    switch(difficolta)
    {
        case FACILE:
                    mvprintw(23, MIN_X_GUI + 7, "Difficolta:");
                    mvprintw(24, MIN_X_GUI + 7, "Facile");
                    break;
        case NORMALE:
                    mvprintw(23, MIN_X_GUI + 7, "Difficolta:");
                    mvprintw(24, MIN_X_GUI + 7, "Normale");
                    break;
        case DIFFICILE:
                    mvprintw(23, MIN_X_GUI + 7, "Difficolta:");
                    mvprintw(24, MIN_X_GUI + 7, "Difficile");
                    break;
        default:
                    break;
    }

    attron(COLOR_PAIR(12));

    switch(rana->perk)
        {
            case NESSUNO:
                            break;
            case TRAPASSA_COCCODRILLI:

                            mvprintw(12, MIN_X_GUI + 6, "TRAPASSA");
                            mvprintw(13, MIN_X_GUI + 6, "COCCODRILLI");
            
                            mvprintw(15, MIN_X_GUI + 8, "NO' ' ");
                            mvprintw(16, MIN_X_GUI + 8, " CROCO");
                            mvprintw(17, MIN_X_GUI + 8, " ' HIT");

                            mvprintw(20, MIN_X_GUI + 6, "Finalmente.");

                            break;
            case SCUDO:
                            mvprintw(13, MIN_X_GUI + 8, "SCUDO");

                            mvprintw(15, MIN_X_GUI + 8, " '  ' ");
                            mvprintw(16, MIN_X_GUI + 8, "SHIELD");
                            mvprintw(17, MIN_X_GUI + 8, "' ' ' ");

                            mvprintw(20, MIN_X_GUI + 8, "Comodo!");

                            break;
            case HP_UP:
                            mvprintw(15, MIN_X_GUI + 8, " ' 1 '");
                            mvprintw(16, MIN_X_GUI + 8, "HP   '");
                            mvprintw(17, MIN_X_GUI + 8, "'  UP'");

                            break;
            case AMMAZZA_PIANTE:
                            mvprintw(15, MIN_X_GUI + 8, " KILL'");
                            mvprintw(16, MIN_X_GUI + 8, "ALL ' ");
                            mvprintw(17, MIN_X_GUI + 8, "PLANTS");

                            break;
            case ONE_SHOT:
                            mvprintw(13, MIN_X_GUI + 7, "ONE SHOT");

                            mvprintw(15, MIN_X_GUI + 8, "ONE' '");
                            mvprintw(16, MIN_X_GUI + 8, "'SHOT ");
                            mvprintw(17, MIN_X_GUI + 8, "PLANTS");

                            mvprintw(20, MIN_X_GUI + 4, "Se lo meritano.");

                            break;
            case PIANTE_IMMUNI:
                            mvprintw(13, MIN_X_GUI + 5, "PIANTE IMMUNI");

                            mvprintw(15, MIN_X_GUI + 8, "'   ' ");
                            mvprintw(16, MIN_X_GUI + 8, "IMMUNE");
                            mvprintw(17, MIN_X_GUI + 8, "PLANTS");

                            mvprintw(20, MIN_X_GUI + 8, "OH NO!");

                            break;
            case DOPPIO_DANNO:
                            mvprintw(13, MIN_X_GUI + 5, "DOPPIO DANNO");

                            mvprintw(15, MIN_X_GUI + 8, "  ' ' ");
                            mvprintw(16, MIN_X_GUI + 8, "DOUBLE");
                            mvprintw(17, MIN_X_GUI + 8, "DAMAGE");

                            mvprintw(20, MIN_X_GUI + 5, "Stai attento!");

                            break;
            case PERDI_TANA:
                            mvprintw(15, MIN_X_GUI + 8, "LOSE '");
                            mvprintw(16, MIN_X_GUI + 8, " ' 'A ");
                            mvprintw(17, MIN_X_GUI + 8, " GATE'");

                            break;
            case PISTOLA_ROTTA:
                            mvprintw(13, MIN_X_GUI + 5, "PISTOLA ROTTA");

                            mvprintw(15, MIN_X_GUI + 8, "  ' ''");
                            mvprintw(16, MIN_X_GUI + 8, "NO '  ");
                            mvprintw(17, MIN_X_GUI + 8, " ' GUN");

                            mvprintw(20, MIN_X_GUI + 8, "E ora?");

                            break;
            case FULL_RAMBO:
                            mvprintw(13, MIN_X_GUI + 6, "FULL RAMBO");

                            mvprintw(15, MIN_X_GUI + 8," ' ' ");
                            mvprintw(16, MIN_X_GUI + 8, "FULL '");
                            mvprintw(17, MIN_X_GUI + 8, "'RAMBO");

                            mvprintw(20, MIN_X_GUI + 8, "AIUTO!");

                            break;
            default:
                            break;
        }

    if(pausa == true)
    {
        attron(COLOR_PAIR(10));
        for(int i = 10; i < 35; i++)
        {
            mvaddstr(i,17,"|                    |");//22 spazi
        }

        mvaddstr(10,17,"======================");//22 spazi
        mvaddstr(34,17,"======================");//22 spazi
            

        mvprintw(14, 21, "GIOCO IN PAUSA");
        mvprintw(25, 24 , "RIPOSATI!"); 
    }

    refresh();
}

void StampaMenu(int pagina, int selezione, bool lampeggio_cursore, struct RisultatoPartita risultato,
                int* highscore)
{
    attron(COLOR_PAIR(10));

    for(int i = 0; i < TERMINAL_MAX_X; i++)
    {
        for(int j = 0; j < MAX_Y; j++)
        {
            mvaddch(j, i, ' ');
        }
    }

    switch(pagina)
    {
        case PAGINA_MAIN:
                        char logo[9][79];

                        attron(COLOR_PAIR(10));

                        strcpy(logo[0], " ______         _     _ _______       ______  _____  _______ _     _ __   __  ");  
                        strcpy(logo[1], " |_____] |      |     | |______      |_____/ |     | |       |____/    |_|   .");
                        strcpy(logo[2], " |_____] |_____ |_____| |______      |    |_ |_____| |_____  |    |_    |    .");
                        strcpy(logo[3], "  _____   _____  _______  ______ _______ ______ _____  _____  __   _ _______  ");
                        strcpy(logo[4], " |     | |_____] |______ |_____/ |_____|  ____/   |   |     | | |  | |______  ");
                        strcpy(logo[5], " |_____| |       |______ |    |_ |     | /_____ __|__ |_____| |  |_| |______  ");
                        strcpy(logo[6], " _______ _______ __   _ _______                                               ");
                        strcpy(logo[7], "    |    |_____| | |  | |______                                               ");
                        strcpy(logo[8], "    |    |     | |  |_| |______                                               ");
    
                        for(int i = 0; i < 9; i++)
                        {
                            mvaddstr(i, 0, logo[i]);
                        }

                        mvprintw(9, 34, "PERK INCLUSI!!!");

                        mvprintw(20, 36, "GIOCA");
                        mvprintw(23, 36, "COMANDI");
                        mvprintw(26, 36, "GUIDA PERK");
                        mvprintw(29, 36, "CHIUDI");

                        if(lampeggio_cursore == true)
                        {
                            mvprintw(19, 40, "^");
                            mvprintw(18, 40, "W");

                            mvprintw(30, 40, "v");
                            mvprintw(31, 40, "S");
                        }

                        mvprintw(40, 50, "Premi SPAZIO per selezionare");

                        if(lampeggio_cursore == true)
                        {
                            attron(COLOR_PAIR(4));
                        }
                        else
                        {
                            attron(COLOR_PAIR(18));
                        }

                        switch(selezione)
                        {
                            case 1:
                                    mvaddstr(19, 32, "0 0");
                                    mvaddstr(20, 32, "}R{");
                
                                    break;
                            case 2:
                                    mvaddstr(22, 32, "0 0");
                                    mvaddstr(23, 32, "}R{");

                                    break;
                            case 3:
                                    mvaddstr(25, 32, "0 0");
                                    mvaddstr(26, 32, "}R{");

                                    break;
                            case 4:
                                    mvaddstr(28, 32, "0 0");
                                    mvaddstr(29, 32, "}R{");

                                    break;
                            default:
                                    break;
                        }
                        
                        break;
        case PAGINA_GIOCA:
                        attron(COLOR_PAIR(10));

                        mvprintw(20, 36, "FACILE");
                        mvprintw(23, 36, "NORMALE");
                        mvprintw(26, 36, "DIFFICILE");

                        mvprintw(10, 35, "Highscore: %d", highscore[selezione - 1]);

                        mvprintw(38, 50, "Premi SPAZIO per iniziare");

                        mvprintw(40, 50, "Premi F per tornare indietro");

                        if(lampeggio_cursore == true)
                        {
                            attron(COLOR_PAIR(4));
                        }
                        else
                        {
                            attron(COLOR_PAIR(18));
                        }

                        switch(selezione)
                        {
                            case 1:
                                    mvaddstr(19, 32, "0 0");
                                    mvaddstr(20, 32, "}R{");

                                    attron(COLOR_PAIR(10));

                                    mvprintw(35, 2, "Poco veloce, solo bonus fra i perk, 60 secondi per tana.");
                                    mvprintw(36, 2, "Per chi non ha molta voglia di impegnarsi.");
                
                                    break;
                            case 2:
                                    mvaddstr(22, 32, "0 0");
                                    mvaddstr(23, 32, "}R{");

                                    attron(COLOR_PAIR(10));

                                    mvprintw(35, 2, "Veloce, 3 bonus e 2 malus fra i perk, 50 secondi per tana.");
                                    mvprintw(36, 2, "Come il gioco venne inizialmente concepito.");

                                    break;
                            case 3:
                                    mvaddstr(25, 32, "0 0");
                                    mvaddstr(26, 32, "}R{");

                                    attron(COLOR_PAIR(10));

                                    mvprintw(35, 2, "Velocissimo, perk nascosti, 40 secondi per tana.");
                                    mvprintw(36, 2, "Per i matti.");

                                    break;
                            default:
                                    break;
                        }

                        break;
        case PAGINA_PERK:
                        mvprintw(2, 2, "Ogni tana ha un perk casuale assegnato.");
                        mvprintw(3, 2, "Prenderla attiva il suo effetto!");
                        mvprintw(5, 2, "I perk si dividono in:");
                        mvprintw(8, 2, "BONUS");
                        mvprintw(8, 42, "MALUS");

                        attron(COLOR_PAIR(12));

                        mvprintw(10, 2, "NO' ' ");
                        mvprintw(11, 2, " CROCO");
                        mvprintw(12, 2, " ' HIT");

                        mvprintw(15, 2, " '  ' ");
                        mvprintw(16, 2, "SHIELD");
                        mvprintw(17, 2, "' ' ' ");

                        mvprintw(20, 2, " ' 1 '");
                        mvprintw(21, 2, "HP   '");
                        mvprintw(22, 2, "'  UP'");

                        mvprintw(25, 2, " KILL'");
                        mvprintw(26, 2, "ALL ' ");
                        mvprintw(27, 2, "PLANTS");

                        mvprintw(30, 2, "ONE' '");
                        mvprintw(31, 2, "'SHOT ");
                        mvprintw(32, 2, "PLANTS");

                        mvprintw(10, 42, "'   ' ");
                        mvprintw(11, 42, "IMMUNE");
                        mvprintw(12, 42, "PLANTS");

                        mvprintw(15, 42, "  ' ' ");
                        mvprintw(16, 42, "DOUBLE");
                        mvprintw(17, 42, "DAMAGE");

                        mvprintw(20, 42, "LOSE '");
                        mvprintw(21, 42, " ' 'A ");
                        mvprintw(22, 42, " GATE'");

                        mvprintw(25, 42, "  ' ''");
                        mvprintw(26, 42, "NO '  ");
                        mvprintw(27, 42, " ' GUN");

                        mvprintw(30, 42," ' ' ");
                        mvprintw(31, 42, "FULL '");
                        mvprintw(32, 42, "'RAMBO");

                        attron(COLOR_PAIR(10));

                        mvprintw(10, 9, "I tuoi proiettili trapassano i");
                        mvprintw(11, 9, "coccodrilli. Quelli cattivi");
                        mvprintw(12, 9, "vengono comunque trasformati.");

                        mvprintw(15, 9, "Lo scudo permette alla rana");
                        mvprintw(16, 9, "di parare un singolo");
                        mvprintw(17, 9, "proiettile. Comodo!");

                        mvprintw(20, 9, "Permette alla rana di");
                        mvprintw(21, 9, "guadagnare un punto vita.");
                        mvprintw(22, 9, "Come quel famoso fungo.");

                        mvprintw(25, 9, "Uccide tutte le piante");
                        mvprintw(26, 9, "senza pensarci due");
                        mvprintw(27, 9, "volte.");

                        mvprintw(30, 9, "Basta un colpo per far");
                        mvprintw(31, 9, "fuori le piante.");
                        mvprintw(32, 9, "Se lo meritano.");

                        mvprintw(10, 49, "Le piante sono immuni.");
                        mvprintw(11, 49, "Oh no.");
                        
                        mvprintw(15, 49, "Il prossimo proiettile");
                        mvprintw(16, 49, "ti fa male il doppio.");
                        mvprintw(17, 49, "Stai attento!");

                        mvprintw(20, 49, "Perdi una tana.");
                        mvprintw(21, 49, "Che infamata.");

                        mvprintw(25, 49, "La pistola non funziona!");
                        mvprintw(26, 49, "E ora?");
                        
                        mvprintw(30, 49, "Le piante non smettono");
                        mvprintw(31, 49, "di sparare!");
                        mvprintw(32, 49, "Aiuto!");

                        mvprintw(37, 2, "Perdere una vita rimuove il perk che possiedi.");
                        mvprintw(38, 2, "Se sono buoni tieniteli stretti!");

                        mvprintw(40, 50, "Premi F per tornare indietro");

                        break;
        case PAGINA_RESOCONTO:
                        mvprintw(15, 35, "RESOCONTO");

                        if(risultato.vittoria == true)
                        {
                            mvprintw(20, 35, "Hai vinto!");

                            mvprintw(22, 35, "Punteggio: %d", risultato.punteggio);
                        }
                        else
                        {
                            mvprintw(20, 35, "Hai perso...");

                            mvprintw(22, 35, "Riprova!");
                        }

                        mvprintw(40, 47, "Premi SPAZIO per tornare al menu");

                        break;
        case PAGINA_COMANDI:

                        mvprintw(2, 36, "COMANDI");

                        mvprintw(10, 18, " ~~~~~~~ ");
                        mvprintw(11, 18, "{       }");
                        mvprintw(12, 18, "{   W   }");
                        mvprintw(13, 18, "{       }");
                        mvprintw(14, 18, " ~~~~~~~ ");
                        mvprintw(8, 21, "Su");

                        mvprintw(16, 18, " ~~~~~~~ ");
                        mvprintw(17, 18, "{       }");
                        mvprintw(18, 18, "{   S   }");
                        mvprintw(19, 18, "{       }");
                        mvprintw(20, 18, " ~~~~~~~ ");
                        mvprintw(22, 21, "Giu");

                        mvprintw(16, 8, " ~~~~~~~ ");
                        mvprintw(17, 8, "{       }");
                        mvprintw(18, 8, "{   A   }");
                        mvprintw(19, 8, "{       }");
                        mvprintw(20, 8, " ~~~~~~~ ");
                        mvprintw(22, 8, "Sinistra");

                        mvprintw(16, 28, " ~~~~~~~ ");
                        mvprintw(17, 28, "{       }");
                        mvprintw(18, 28, "{   D   }");
                        mvprintw(19, 28, "{       }");
                        mvprintw(20, 28, " ~~~~~~~ ");
                        mvprintw(22, 29, "Destra");

                        mvprintw(16, 58, " ~~~~~~~ ");
                        mvprintw(17, 58, "{       }");
                        mvprintw(18, 58, "{   P   }");
                        mvprintw(19, 58, "{       }");
                        mvprintw(20, 58, " ~~~~~~~ ");
                        mvprintw(22, 60, "Pausa");

                        mvprintw(30, 8, " ~~~~~~~~~~~~~~~~~~~~~~ ");
                        mvprintw(31, 8, "{                      }");
                        mvprintw(32, 8, "{        SPAZIO        }");
                        mvprintw(33, 8, "{                      }");
                        mvprintw(34, 8, " ~~~~~~~~~~~~~~~~~~~~~~ ");
                        mvprintw(36, 17, "Spara");

                        mvprintw(40, 50, "Premi F per tornare indietro");
                        
                        break;
        default:
                        break;
    }
    

    refresh();
}