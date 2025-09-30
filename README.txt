● The project was developed using only the Ncurses library in two versions, as project specifications: Threads and Processes.
● Game audio is handled through system() calls that run the ALSA command "aplay", the default audio library on Linux.
● Makefile usage:
- make → compiles the program, overwriting previous .o files if necessary, and runs it
- make esegui → runs the program
- make clean → removes previous .o files
● The main menu includes pages that detail the controls and explain our game mechanic: the Perks.
● Optional features implemented:
- **Plants that survive multiple hits**  
    ~Plants lose one character per hit and have a total of three lives.  

- **Multiple difficulty levels**  
    ~Difficulties include Easy, Normal, and Hard. The differences are explained in the difficulty selection menu.  

- **Multiple game levels**  
    ~The game speeds up with each captured burrow.  
    ~After capturing a burrow, some crocodiles turn evil (depending on the difficulty):  
        - Easy → 3 crocodiles  
        - Normal → 5 crocodiles  
        - Hard → 7 crocodiles  
    *Crocodiles occasionally change direction.  

- **Game sounds and music**  
    ~The game features original sounds and music, entirely created by us.  

- **Game menu system**  
    ~The game includes a main GUI at startup, an in-game GUI, and a pause menu.  

- **Attention to graphics**  
    ~Within the constraints of Ncurses, graphics are clear, simple, clean, and dynamic.  
    ~The in-game screen is divided into the gameplay area and a GUI displaying necessary information.  

- **Pause functionality**  
    ~The pause feature is included in all versions.  

- **Creativity**  
    ~The Perk mechanic is the main creative contribution of the project.  
● Scoring system:
- Frog stays on a good crocodile = +2 pts/move  
- Frog stays on an evil crocodile = +4 pts/move  
- Frog transforms a crocodile = +10 pts  
- Frog captures a burrow = +50 pts  
- Frog wins the game = +100 pts  
- Frog destroys a projectile = +15 pts  
- Frog hits a plant = +10 pts  
- Frog destroys a plant = +25 pts  
- Frog loses a life = -30 pts  

- Remaining time at the end of a round is converted into points  

~Scores are saved in the binary file highscores.bin only if the player wins and can be viewed in both the difficulty selection menu and the in-game GUI according to the chosen difficulty.
● Important notes:
- Due to the unreliable behavior of srand(), crocodile direction changes occasionally caused all crocodiles to move in the same direction, making the game nearly impossible to win. To address this, I ensured that lanes alternate directions, occasionally inverting at the end of each round to comply with project specifications.
- Rendering is frame-rate dependent: a macro in header.h called FRAMERATE allows it to be set.
