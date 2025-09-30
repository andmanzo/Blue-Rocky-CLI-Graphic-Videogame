
Progetto di Sistemi Operativi di :
Andrea Manzo (66310) e Alex Melis (66360).

● Il progetto è stato realizzato utilizzando solamente la libreria Ncurses.
● L'audio di gioco viene gestito mediante delle system() invocanti il comando "aplay" di ALSA, libreria audio default di Linux.

● Per interagire con il makefile:
    "make" -> se necessario compila sovrascrivendo il .o precedente ed esegui
    "make esegui" -> esegui
    "make clean" -> rimuovi il .o precedente

● Nel menù iniziale sono presenti delle pagine che illustrano nel dettaglio i comandi e la nostra meccanica di gioco: i Perk. 

● Le specifiche opzionali che abbiamo aggiunto sono:

    -Piante che non muoiono al primo colpo
        ~Le piante perdono un carattere ogni hit ricevuto. Hanno tre vite totali.

    -Diverse difficoltà di gioco
        ~Le difficoltà si differenziano in Facile, Normale e Difficile. Le differenze vengono 				spiegate nella scelta della difficoltà.

    -Livelli multipli di gioco
        ~Ogni tana presa, il gioco accelera.
        ~Dopo aver preso una tana alcuni coccodrilli vengono trasformati in cattivi (in base alla difficoltà). 
            Facile -> 3 coccodrilli 
            Normale -> 5 coccodrilli
            Difficile -> 7 coccodrilli
           *C'è una chance per cui i coccodrilli cambiano direzione

    -Suoni e/o musiche di gioco
        ~Il gioco ha suoni e musiche originali, curate interamente da noi.

    -Gestione di un menù di gioco
        ~Il gioco ha una GUI principale all'avvio, una in-game e una di pausa.

    -Particolare cura della grafica:
        ~Volendo attenerci ad Ncurses abbiamo cercato di creare una grafica chiara, semplice, pulita e dinamica.
        ~Lo schermo in-game si divide in partita e GUI, che illustra ciò che serve.

    -Pausa:
        ~La pausa è presente in entrambe le versioni.

    -Creatività:
        ~L'apporto creativo del nostro progetto è la meccanica dei Perk.

● Il calcolo dei punteggi avviene secondo la seguente lista:

    -rana rimane sopra un coccodrillo buono     = +2 pt/movimento
    -rana rimane sopra un coccodrillo cattivo   = +4 pt/movimento
    -rana trasforma un coccodrillo              = +10 pt
    -rana prende una tana                       = +50 pt
    -rana vince la partita                      = +100 pt
    -rana distrugge un proiettile               = +15 pt
    -rana colpisce una pianta                   = +10 pt
    -rana distrugge pianta                      = +25 pt
    -rana perde una vita                        = -30 pt 

    -il tempo bonus della manche viene convertito in punteggio 

~i punteggi vengono salvati nel file binario highscores.bin solo se il giocatore vince la partita e saranno disponibili 
	sia nel menù seleziona difficoltà sia nella GUI del gioco in base alla difficoltà scelta.
	
● Importante:
	~Il cambio direzione dei coccodrilli, per via della natura poco affidabile della srand(), tendeva saltuariamente a far andare tutti i coccodrilli nella stessa direzione. Questo causava una sconfitta quasi certa in quanto, nonostante le diverse velocità, risultava impossibile trovare le giuste coincidenze per attraversare il fiume. Abbiamo optato per far tendere tutte le corsie in direzioni alternate, occasionalmente invertite ogni fine manche per attenerci alle specifiche del progetto.

	~La logica di stampa si basa su framerate: una macro in "header.h" chiamata FRAMERATE consente di impostarlo.
