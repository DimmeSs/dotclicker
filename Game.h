#ifndef header_name_h
#define header_name_h

#include <map>
#include <string>
#include <thread>
#include <vector>

/**
 * Stany, w jakich gra moze byc
 */
enum GameState {
    ULEPSZENIA = 4,
    AUTORZY = 3,
    GAME = 2,
    MENU = 1,
    START = 0
};

enum UlepszeniaState {
    MAIN,
    EQ,
    KUP
};

class Game;
class Ulepszenie;

/**
 * Gracz
 */
class Player {
private:
    /** pieniadze gracza */
    int money;
    /** ulepszenia ktore posiada gracz */
    std::vector<Ulepszenie *> ulepszenia;
    /* dane calej gry */
    Game *Gra;
    /** Znaki, ktore mozna uzywac */
    std::map<std::string, int> characters;

public:
    /** ile ma pieniedzy */
    int getMoney();
    int calculateBaseMoney(std::string s);
    std::map<std::string, int> getCharacters();
    /** Dodaj / Odejmin pieniedzy */
    void addMoney(int x);
    std::vector<Ulepszenie *> getUlepszenia() { return this->ulepszenia; }
    /** Sprawdz czy ma ulepszenie */
    bool maUlepszenie(int uid);
    /** Kup Ulepszenie */
    bool kupUlepszenie(int uid);
    /** Uzyj ulepszenia */
    void useUlepszenie(int uid);
    /** Zaloz ulepszenie */
    void equipUlepszenie(int uid);
    /** Dodaj znak, do wpisania */
    void addFeedableCharacter(std::string c, int i);
    /** Daj playerowi string */
    void feedString(std::string s);
    /** Konstruktor */
    Player(Game *g);
};

class Game {
private:
    bool running;
    GameState state;
    UlepszeniaState ulstate;

public:
    bool commandNotFoundError;
    bool notEnoughMoneyError;
    bool outOfRangeError;
    bool notIntegerError;
    std::string lastInput;
    Ulepszenie *getUlepszenie(int uid);
    GameState getState();
    UlepszeniaState getUlState();
    bool isRunning();
    void Draw();
    std::vector<Ulepszenie *> mozliweUlepszenia;
    Player *player;
    void start();
    Game();
    void userInput(std::string s);
    void stop();
};

/// ============================ ULEPSZENIA

/**
 * Wszystkie ulepszenia musza miec:
 */
class Ulepszenie {
private:
    /** cena ulepszenia */
    int cost;
    /** id ulepszenia */
    int id;
    /** Czy jest wlaczone */
    bool equipped;

public:
    /** Daj ID */
    int getId();
    /** daj mi cene */
    int getCost();
    /** Czy jest zalozone */
    bool isEquipped() { return this->equipped; }
    /** zdejmij / zaloz ulepszenie */
    void toggleEquip() { this->equipped = !this->equipped; }
    /** opis getter */
    virtual std::string getOpis() { return "Ulepszenie#" + std::__cxx11::to_string(this->id); };
    /** co robi zaraz po kupieniu */
    virtual void buy(Game *p, std::string s){};
    /** co robi przy uzyciu */
    virtual int use(Game *p) { return 0; };
    /** Konstruktor */
    Ulepszenie(int id, int cost);
};

class PodwojnePieniadze1 : public Ulepszenie {
public:
    std::string getOpis();
    /** co robi tuz po kupnie */
    void buy(Game *p);
    /** co robi przy uzyciu */
    int use(Game *p, std::string s);
    PodwojnePieniadze1(int cost);
};

class UzycieSlowaOwoc : public Ulepszenie {
public:
    std::string getOpis();
    void buy(Game *p);
    int use(Game *p, std::string s);
    UzycieSlowaOwoc(int cost);
};

#endif
