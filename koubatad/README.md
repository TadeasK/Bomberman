# Classic Bomberman Game  
Created for subject Programming and Algorithmics 2 at FIT, CTU. Focus of this assignment was to asses our ability to design and implement a bigger multi-file multi-class object-oriented program in C++.  
(Original description in Czech [below](#klasická-hra-bomberman))

## Assignment Specification:

The game will follow the standard rules of the original game.

Players will place bombs that can destroy crates, from which a bonus item may drop upon destruction. At the same time, bombs will be able to kill monsters, other players, and even the player who placed the bomb.

It will be possible to play both single-player 'campaign' mode against AI-controlled enemies (monsters) and multiplayer mode against another player on a single keyboard.

Both single-player and multiplayer game modes will be of the "king of the hill" type, meaning the last survivor wins.

Individual campaign levels will be saved in files, and their object layout will be read when generating the map. When starting the game, players will be able to select the map to play on (single-player and multiplayer modes).

Players will be able to move only orthogonally along the X and Y axes. Movement and bomb placement controls for both players will be preset.

Furthermore, the file will store the best achieved score on each map in single-player mode, which players earn by killing monsters and collecting bonuses. When achieving the best score, the player will be prompted to enter a name, which will be displayed with their score. Finally, the configuration file will store settings for game objects (chance of bonus item drop, score for destroying individual objects [monsters/crates], score for collecting bonuses).

When launching the game, the player will be able to choose the type of game they want to play (player vs. monsters, player vs. player), display the score table, or view controls. Navigation within the menu will be done using arrow keys.

## Game Description

- Modes:
  - Player vs. Computer (Player represented as '@' in green, monsters as '$' in yellow)
  - Player vs. Player on the same computer (Player 1 in green, Player 2 in blue, both represented as '@')
- Functionalities:
  - AI moves toward the player and behaves similarly to monsters in Bomberman (moving in circles/straights).
  - Crates ('#') are destructible and drop bonuses.
  - Walls ('X') cannot be destroyed.
- Bonuses:
  - Increase the number of bombs ('B').
  - Increase the blast radius ('R').
  - Levitation ('L') - The player can walk through monsters/players/bombs without taking damage, but explosions can still harm them.
  - Detonator ('D') - If the player has a detonator and places a bomb again, it will detonate previously placed bombs.
  - Increase the player's life count ('H').
- Configuration from Files:
  - The game loads map configurations from files.
  - The game loads the table of high scores from files.
  - The game loads probabilities of bonus drops, scores for monsters/bonus collection from files.
- The game allows displaying the best result on each map, and when achieving a better result, it prompts the player to save their name.

## Application of Polymorphism

All game objects will inherit from a class that holds information about their current position since each of them needs to know their position. Furthermore, it will implement basic methods for displaying on the game board and interacting with other objects. Static object display classes in the game environment will directly inherit from this class.

Another parent class (which itself will inherit from the main class) will cover objects capable of actions (movement, bomb placement) in addition to basic functionalities. From this class, a class for monsters will inherit, divided into subclasses for various types of monsters. Another class will be for players, which will also store data about collected bonuses.

The last polymorphic class, also inheriting from the main class, will encapsulate special objects. These special objects may include various bonuses for the player who collects them.

Another level of polymorphism is applied in classes representing the game menu. The parent class implements window menu rendering and other basic properties, such as behavior when resizing the terminal and reading user input. Each subclass then implements its own actions that can be performed in response to user input in that particular menu.

You can find a class diagram in the doc/ folder, which contains all the documentation generated using the Doxygen utility. You are likely familiar with it, but just to be sure, the generated HTML page can be found in the "Classes/Class Hierarchy" menu.

--------------------------
-------------------------
# Klasická hra Bomberman

## Specifikace zadání:

Hra Bomberman se bude řídit standartními pravidly původní hry.  

Hráč bude pokládat bomby, které budou schopné rozbít bedny, ze kterých při rozbití může vypadnout
nějaký bonus, zároveň bomby budou schopné zabít monstra, jiné hráče, ale i
hráče, který sám bombu položil.  

Bude možné hrát jak singleplayer 'kampaň' proti AI kontrolovaným nepřátelům (monstra), tak
multiplayer proti dalšímu hráči na jedné klávesnici.  

Singleplayer i multiplayer herní módy budou typu king of the hill tzn. poslední přeživší vyhrává.  

Jednotlivé levely kampaně budou uloženy v souborech a z nich bude čteno rozložení objektů na mapě 
při její generaci. Při spuštění hry pro si bude možné vybrat mapu na které se bude hrát (singleplayer i multiplayer mód).  

Hráč se bude moci pohybovat pouze kolmo na osy X a Y. Ovládání pohybu a pokládaní bomb obou hráčů
bude předem nastaveno.  

Dále se v souboru bude ukládat nejlepš dosažené skóre na každé mapě v rámci singleplazer módu, které získává hráč za
zabíjení monster a sbírání bonusů. Při dosažení nejlepšího skóre bude hráč vyzván k zadání jména, které se u jeho
skóre zobrazí. Nakonec bude v konfiguračním souboru uloženo nastavení herních objektů (šance na spadnutí bonusu, skóre za
zničení jednotlivých objektů (monster/beden), skóre za sebrání bonusů).  

Při spuštění hry si hráč bude moci zvolit jaký typ hry chce hrát (hráč proti monstrům, hráč proti hráči), zobrazit
tabulku skóre nebo ovládání, samotná navigace menu bude provedena pomocí 'šipek' (arrow keys).  

## Popis hry

- Režimy:  
  - Hráč proti počítači. (Hráč je zelený zavináč '@', monstra žluté dolary '$')  
  - Hráč proti hráči na jednom počítači. (Hráč1 je zelený, Hráč2 modrý zavináč '@')  
- Funkcionality:  
  - AI se hýbe směrem ke hráči, když nemůže hýbe se podobně jako monstra v Bombermanovi (dokola/přímky)  
  - Bedny ('#') jsou ničitelné a padají z nich bonusy  
  - Zdi ('X') nelze zničit.  
- Bonusy:  
  - Zvětšení počtu bomb ('B')  
  - Zvětšení dosahu výbuchu ('R')  
  - Levitace ('L') - Hráč může chodit skrz monstra/hráče/bomby aniž by utrpěl poškození, výbuchy ho ale stále zraní  
  - Detonator ('D') - Pokud hráč má detonátor a položí bombu opětovný pokus o položení bomby odpálí již položené bomby  
  - Zvýšení počtu životů hráče ('H')  
- Konfigurace ze souborů:  
  - Hra načítá konfigurace map ze souboru  
  - Hra načítá tabulku nejlepších skŕe ze souboru  
  - Hra načítá pravděpodobnosti pádu bonusů, skóre za monstra/sbírání bonusů ze souboru  
- Hra umožňuje zobrazit nejlepší výsledek na každé mapě a při dosažení lepšího výsledku vyzve hráče k uložení svého jména  

## Uplatnění polymorfismu

Všechny herní objekt budou dědit ze třídy, která bude držet informaci o své současné pozici,
    jelikož tu o sobě musí vědět každý z nich. Dále bude implementovat základní metody pro
    zobrazování na herní ploše a interakce s ostatními objekty. Z ní přímo budou čerpat třídy zobrazující statické
    objekty herního prostředí.  

Další mateřskou třídou (která však sama bude dědit z již zmíněné hlavní třídy) bude třída,
    která bude zastřešovat objekty, které jsou navíc schopné nějakých akcí (pohyb, pokládání bomb).  
    Z této třídy bude dědit třída pro monstra, která bude dělena do dalších podtříd pro různé druhy
    monstrer.  
    Další třída bude třída hráče, která bude o sobě navíc ukládat údaje o sebraných bonusech.  
    
Poslední polymorfní třída rovněž dědící z hlavní třídy bude obalovat spceiální objekty.
    Tyto speciální objekty budou například různé bonusy pro hráče, který je sebere.

Další úroveň polymorfismu je aplikována v třídách reprezentujících menu hry. Mateřská třída
    implementuje vykreslování oken menu a další základní vlastnosti, jako třeba chování při 
    změně velikosti terminálu a načítání uživatelského vstupu, každá podtřída si pak implementuje
    vlastní akce, kterých v daném menu lze dosáhnout v reakci na uživatelův vstup.  
    
Třídní diagram lze nalézt ve složce doc/, která obsahuje veškerou dokumentaci vygenerovanou pomocí 
    utility Doxygen. S tím jste pravděpodobně seznámeni, nicméně pro jistotu uvádím, že na vygenerované
    HTML stránce se nachází v menu "Classes/Class Hiearchy".  