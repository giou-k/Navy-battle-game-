#ifndef header_h
#define header_h
#include <iostream>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <conio.h>
#include <exception>
#include <ctype.h>

using namespace std;

class Coordinates;

namespace nmspc{
    extern int getGlobalMapSize();
    extern float randNormalized(char);
    extern float eudi(int, int, int, int);
    extern int minVector(vector<Coordinates*>);
    extern int maxVector(vector<Coordinates*>);
}

class Sea;
class Port;
class Ship;



class Run{
public:
    Run();
    vector<Sea*>*getSeaBlocks();
    void createMap();
    void drawMap();
    vector<Port*>*getPorts();
    void assemblePort();
    void setWeather();
    vector<Ship*>*getShips();
    void assembleShipPirate(int);
    void assembleShipResearcher(int);
    void assembleShipCommercial(int);
    void assembleShipMechanic(int);
    void idleExpiration();
    bool terminateSimulation();
    void operateAll();
    void MENU();
};



class Sea{
private:
    char blockAppearance;
    int axisX;
    int axisY;
    float weather;
    int depositTreasure;
public:
    Sea();
    int temp;
    char getBlockAppearance();
    void setBlockAppearance(char);
    int getAxisX();
    void setAxisX(int);
    int getAxisY();
    void setAxisY(int);
    float getWeather();
    void setWeather(float);
    int getDepositTreasure();
    void setDepositTreasure(int);
};



class Port{
private:
    char hqID;
    int posHqX;
    int posHqY;
    int collectionTreasure;
    int requirementTreasure;
public:
    Port();
    char getHqID();
    void setHqID(char);
    int getPosHqX();
    void setPosHqX(int);
    int getPosHqY();
    void setPosHqY(int);
    int getCollectionTreasure();
    void setCollectionTreasure(int);
    int getRequirementTreasure();
    void setRequirementTreasure(int);
};



class Ship{
private:
    char shipID;
    int shipID2;
    int posShipX;
    int posShipY;
    int speed;
    bool broken;
    int HP;
    int maxHP;
    int idleTimer;
    int defaultIdleTimer;
    int countMove;
    int countDamage;
    int countBroken;
    int loadTreasure;
    int loadMax;
public:
    Ship();
    virtual ~Ship();
    int temp1;
    char getShipID();
    void setShipID(char);
    int getShipID2();
    void setShipID2(int);
    int getPosShipX();
    void setPosShipX(int);
    int getPosShipY();
    void setPosShipY(int);
    int getSpeed();
    void setSpeed(int);
    bool getBroken();
    void setBroken(bool);
    virtual void operation()=0;
    int getHP();
    void setHP(int);
    int getMaxHP();
    void setMaxHP(int);
    void damaging();
    int getIdleTimer();
    void setIdleTimer(int);
    void destroyShip(int);
    int getDefaultIdleTimer();
    void setDefaultIdleTimer(int);
    virtual void move8way()=0;
    int getCountMove();
    void setCountMove(int);
    int getCountDamage();
    void setCountDamage(int);
    int getCountBroken();
    void setCountBroken(int);
    virtual string operationCount()=0;
    int getLoadTreasure();
    void setLoadTreasure(int);
    int getLoadMax();
    void setLoadMax(int);
};



class ShipPirate:public Ship{
private:
    int loadRecord;
    int damagePower;
public:
    ShipPirate();
    virtual ~ShipPirate();
    static int numShipPirate;
    virtual void operation();
    virtual void move8way();
    int getLoadRecord();
    void setLoadRecord(int);
    int corpusTreasure;
    static int totalTreasure;
    virtual string operationCount();
    int getDamagePower();
    void setDamagePower(int);
};

class ShipResearcher:public Ship{
public:
    ShipResearcher();
    virtual ~ShipResearcher();
    static int numShipResearcher;
    virtual void operation();
    virtual void move8way();
    virtual string operationCount();
};

class ShipCommercial:public Ship{
private:
    int loadRecord;
public:
    ShipCommercial();
    virtual ~ShipCommercial();
    static int numShipCommercial;
    virtual void operation();
    virtual void move8way();
    int getLoadRecord();
    void setLoadRecord(int);
    int corpusTreasure;
    static int totalTreasure;
    virtual string operationCount();
};

class ShipMechanic:public Ship{
private:
    int countRepairs;
public:
    ShipMechanic();
    virtual ~ShipMechanic();
    static int numShipMechanic;
    virtual void operation();
    virtual void move8way();
    int getCountRepairs();
    void setCountRepairs(int);
    int corpusRepairs;
    static int totalRepairs;
    virtual string operationCount();
};



class Coordinates{
private:
    int cooX;
    int cooY;
    float eudiValue;
public:
    Coordinates();
    virtual ~Coordinates();
    int getCooX();
    void setCooX(int);
    int getCooY();
    void setCooY(int);
    float getEudiValue();
    void setEudiValue(float);
};

#endif

