#include "header.h"

namespace nmspc{
    int MapSize=20;
    int getGlobalMapSize(){
        return MapSize;
    }
    float randNormalized(char c){
        if (c=='r'){
            float x=(float)rand()/(float)RAND_MAX;
            x=floor( (float)10 * x ) / (float)10;
            if (x<0.1){x=0.1;}
            else if (x>1){x=1;}
            return x;
        }
        else if (c=='z'){
            float x=(float)rand()/(float)RAND_MAX;
            x=floor( (float)10 * x ) / (float)10;
            if (x<0){x=0;}
            else if (x>0.9){x=0.9;}
            return x;
        }
    }
    float eudi(int x,int y,int X,int Y){
        return sqrt((float)pow(abs(x-X),2)+(float)pow(abs(y-Y),2));
    }
    int minVector(vector<Coordinates*>x){
        int m=x.at(0)->getEudiValue();
        int index=0;
        for (int i=1;i<x.size();i++){
            if (m<x.at(i)->getEudiValue()){
                index=index;
            }
            else if (m==x.at(i)->getEudiValue()){
                index=i;
            }
            else {
                m=x.at(i)->getEudiValue();
                index=i;
            }
        }
        return index;
    }
    int maxVector(vector<Coordinates*>x){
        int m=x.at(0)->getEudiValue();
        int index=0;
        for (int i=1;i<x.size();i++){
            if (m>x.at(i)->getEudiValue()){
                index=index;
            }
            else if (m==x.at(i)->getEudiValue()){
                index=index;
            }
            else {
                m=x.at(i)->getEudiValue();
                index=i;
            }
        }
        return index;
    }
}

using namespace nmspc;



Sea::Sea(){
    setWeather(0);

    temp=rand()%10;
    if (temp<2){
        setDepositTreasure( floor( exp(temp) / temp -1 )*10 );
    }
    else {
        setDepositTreasure(0);
    }
}

vector<Sea*>seaBlocks;
char Sea::getBlockAppearance(){return blockAppearance;}
void Sea::setBlockAppearance(char x){blockAppearance=x;}
int Sea::getAxisX(){return axisX;}
void Sea::setAxisX(int x){axisX=x;}
int Sea::getAxisY(){return axisY;}
void Sea::setAxisY(int x){axisY=x;}
float Sea::getWeather(){return weather;}
void Sea::setWeather(float x){weather=x;}
int Sea::getDepositTreasure(){return depositTreasure;}
void Sea::setDepositTreasure(int x){depositTreasure=x;}



Port::Port(){
    setPosHqX( (rand()%(getGlobalMapSize()-6))+3 );
    setPosHqY( (rand()%(getGlobalMapSize()-6))+3 );
    setCollectionTreasure(0);
    setRequirementTreasure(4000);
}

vector<Port*>ports;
char Port::getHqID(){return hqID;}
void Port::setHqID(char x){hqID=x;}
int Port::getPosHqX(){return posHqX;}
void Port::setPosHqX(int x){posHqX=x;}
int Port::getPosHqY(){return posHqY;}
void Port::setPosHqY(int x){posHqY=x;}
int Port::getCollectionTreasure(){return collectionTreasure;}
void Port::setCollectionTreasure(int x){collectionTreasure=x;}
int Port::getRequirementTreasure(){return requirementTreasure;}
void Port::setRequirementTreasure(int x){requirementTreasure=x;}



Ship::Ship(){
    setShipID('R');
    setBroken(false);
    setIdleTimer(20);
    setDefaultIdleTimer(20);
    setCountMove(0);
    setCountDamage(0);
    setCountBroken(0);
}
Ship::~Ship(){}

vector<Ship*>ships;
char Ship::getShipID(){return shipID;}
void Ship::setShipID(char x){shipID=x;}
int Ship::getPosShipX(){return posShipX;}
void Ship::setPosShipX(int x){posShipX=x;}
int Ship::getPosShipY(){return posShipY;}
void Ship::setPosShipY(int x){posShipY=x;}
int Ship::getSpeed(){return speed;}
void Ship::setSpeed(int x){speed=x;}
bool Ship::getBroken(){return broken;}
void Ship::setBroken(bool x){broken=x;}
int Ship::getHP(){return HP;}
void Ship::setHP(int x){HP=x;}
int Ship::getMaxHP(){return maxHP;}
void Ship::setMaxHP(int x){maxHP=x;}
int Ship::getIdleTimer(){return idleTimer;}
void Ship::setIdleTimer(int x){idleTimer=x;}
int Ship::getDefaultIdleTimer(){return defaultIdleTimer;}
void Ship::setDefaultIdleTimer(int x){defaultIdleTimer=x;}
int Ship::getCountMove(){return countMove;}
void Ship::setCountMove(int x){countMove=x;}
int Ship::getCountDamage(){return countDamage;}
void Ship::setCountDamage(int x){countDamage=x;}
int Ship::getShipID2(){return shipID2;}
void Ship::setShipID2(int x){shipID2=x;}
int Ship::getCountBroken(){return countBroken;}
void Ship::setCountBroken(int x){countBroken=x;}
int Ship::getLoadTreasure(){return loadTreasure;}
void Ship::setLoadTreasure(int x){loadTreasure=x;}
int Ship::getLoadMax(){return loadMax;}
void Ship::setLoadMax(int x){loadMax=x;}

void Ship::damaging(){
    int x=getPosShipX();
    int y=getPosShipY();
    int damage=(int)(seaBlocks.at(x*getGlobalMapSize()+y)->getWeather());
    try {
        int remainingHP=getHP()-damage;
        if (remainingHP>=0){
            setHP(remainingHP);
            setCountDamage(getCountDamage()+1);
            cout<<"\t "<<damage<<"/"<<remainingHP<<"\t     "<<false;
        }
        else {
            throw 1;
        }
    }
    catch(int e){
        setHP(0);
        setCountDamage(getCountDamage()+1);
        setBroken(true);
        setCountBroken(1+getCountBroken());
        cout<<"\t\t     "<<true;
    }
}

void Ship::destroyShip(int x){
    if (ships.size()>0){
        ships.erase(ships.begin()+x);
    }
}



ShipPirate::ShipPirate(){
    setShipID('P');
    setSpeed(1);
    setDamagePower(30+10*rand()%6);
    temp1=40*(rand()%6)+800-1;
    setHP(temp1);
    setMaxHP(temp1);
    numShipPirate++;
    setShipID2(numShipPirate);
}
ShipPirate::~ShipPirate(){}

int ShipPirate::numShipPirate=0;
int ShipPirate::getDamagePower(){return damagePower;}
void ShipPirate::setDamagePower(int x){damagePower=x;}

void ShipPirate::operation(){
    try {
        if (getBroken()==false){
            int x=getPosShipX();
            int y=getPosShipY();
            int cx;
            int cy;
            int rx;
            int ry;
            int qpq;
            vector<Coordinates*>coordinates;
            try {
                for (int i=-1;i<2;i++){
                    for (int j=-1;j<2;j++){
                        if ((i==0) & (j==0)){

                        }
                        else {
                            if ( (x+i>=0) & (x+i<getGlobalMapSize()) & (y+j>=0) & (y+j<getGlobalMapSize()) ){
                                if ( (seaBlocks.at( (x+i)*getGlobalMapSize()+(y+j) )->getBlockAppearance()!='_') & (seaBlocks.at( (x+i)*getGlobalMapSize()+(y+j) )->getBlockAppearance()!='X') ){
                                    coordinates.push_back(new Coordinates);
                                    coordinates.at(coordinates.size()-1)->setCooX(x+i);
                                    coordinates.at(coordinates.size()-1)->setCooY(y+j);
                                }
                            }
                        }
                    }
                }
                if (coordinates.size()==0){
                    throw 1;
                }
                for (int z=0;z<coordinates.size();z++){
                    cx=coordinates.at(z)->getCooX();
                    cy=coordinates.at(z)->getCooY();
                        int k=0;
                        rx=ships.at(k)->getPosShipX();
                        ry=ships.at(k)->getPosShipY();
                        if ( (cx==rx) & (cy==ry) ){
                            if (!(ships.at(k)->getBroken())){
                                if (ships.at(k)->getHP()<1){

                                }
                                else {
                                    qpq=ships.at(k)->getHP()-getDamagePower();
                                    if (qpq<0){
                                        qpq=0;
                                    }
                                    ships.at(k)->setHP(qpq);
                                }
                                cout<<"\t   Attacked "<<ships.at(k)->getShipID()<<ships.at(k)->getShipID2() <<" for "<<getDamagePower();
                            }
                        }

                }
            }
            catch(int e){

            }
        }
        else {
            throw 'x';
        }
    }
    catch(char cc){

    }
}

void ShipPirate::move8way(){
    try{
        if (getBroken()==false){
            int x=getPosShipX();
            int y=getPosShipY();
            int X;
            int Y;
            int indexC=0;
            vector<Coordinates*>coordinates;
            for (int i=-1;i<2;i++){
                for (int j=-1;j<2;j++){
                    if ((i==0) & (j==0)){

                    }
                    else if ( (x+i<0) | (x+i>getGlobalMapSize()-1) | (y+j<0) | (y+j>getGlobalMapSize()-1) ){

                    }
                    else if (seaBlocks.at((x+i)*getGlobalMapSize()+(y+j))->getBlockAppearance()=='_'){
                        coordinates.push_back(new Coordinates);
                        coordinates.at(coordinates.size()-1)->setCooX(x+i);
                        coordinates.at(coordinates.size()-1)->setCooY(y+j);
                    }
                    else {

                    }
                }
            }
            if (coordinates.size()==0){
                throw 1;
            }
            else {
                    indexC=rand()%coordinates.size();
                    X=coordinates.at(indexC)->getCooX();
                    Y=coordinates.at(indexC)->getCooY();
                    setPosShipX(X);
                    setPosShipY(Y);
                    seaBlocks.at(x*getGlobalMapSize()+y)->setBlockAppearance('_');
                    seaBlocks.at(X*getGlobalMapSize()+Y)->setBlockAppearance(getShipID());
                    setCountMove(getCountMove()+1);
                    cout<<" "<<getShipID()<<getShipID2()<<"\t"<<"["<<x<<","<<y<<"]"<<"\t"<<"["<<X<<","<<Y<<"]";
                    damaging();
                    operation();
            }
        }
    }
    catch(int e){

    }
    cout<<endl;
}

string ShipPirate::operationCount(){

}



ShipResearcher::ShipResearcher(){
    setShipID('R');
    setSpeed(1);
    temp1=40*(rand()%6)+300-1;
    setHP(temp1);
    setMaxHP(temp1);
    numShipResearcher++;
    setShipID2(numShipResearcher);
}
ShipResearcher::~ShipResearcher(){}

int ShipResearcher::numShipResearcher=0;

void ShipResearcher::operation(){
    try {
        if (getBroken()==false){
            int x=getPosShipX();
            int y=getPosShipY();
            int cx;
            int cy;
            int rx;
            int ry;
            vector<Coordinates*>coordinates;
            try {
                for (int i=-1;i<2;i++){
                    for (int j=-1;j<2;j++){
                        if ((i==0) & (j==0)){

                        }
                        else {
                            if ( (x+i>=0) & (x+i<getGlobalMapSize()) & (y+j>=0) & (y+j<getGlobalMapSize()) ){
                                if ( (seaBlocks.at( (x+i)*getGlobalMapSize()+(y+j) )->getBlockAppearance()!='_') & (seaBlocks.at( (x+i)*getGlobalMapSize()+(y+j) )->getBlockAppearance()!='X') ){
                                    coordinates.push_back(new Coordinates);
                                    coordinates.at(coordinates.size()-1)->setCooX(x+i);
                                    coordinates.at(coordinates.size()-1)->setCooY(y+j);
                                }
                            }
                        }
                    }
                }
                if (coordinates.size()==0){
                    throw 1;
                }
                for (int z=0;z<coordinates.size();z++){
                    cx=coordinates.at(z)->getCooX();
                    cy=coordinates.at(z)->getCooY();
                    for (int k=0;k<ships.size();k++){
                        rx=ships.at(k)->getPosShipX();
                        ry=ships.at(k)->getPosShipY();
                        if ( (cx==rx) & (cy==ry) & (ships.at(k)->getShipID()=='P')){

                            cout<<"\t   Pirate at ["<<cx<<","<<cy<<"]";

                        }
                    }
                }
            }
            catch(int e){

            }
        }
        else {
            throw 'x';
        }
    }
    catch(char cc){

    }
}

void ShipResearcher::move8way(){
    int x=getPosShipX();
    int y=getPosShipY();
    if (getBroken()==false){
        vector<Coordinates*>coordinates;
        vector<Coordinates*>coordinatesSorted;
        vector<Coordinates*>coordinatesWeatherZones;
        vector<Coordinates*>coordinatesWeatherZonesSorted;
        try {
            for (int i=0;i<seaBlocks.size();i++){
                if ((seaBlocks.at(i)->getWeather()>=.6) & (seaBlocks.at(i)->getBlockAppearance()=='_')){
                    coordinatesWeatherZones.push_back(new Coordinates);
                    coordinatesWeatherZones.at(coordinatesWeatherZones.size()-1)->setCooX(seaBlocks.at(i)->getAxisX());
                    coordinatesWeatherZones.at(coordinatesWeatherZones.size()-1)->setCooY(seaBlocks.at(i)->getAxisY());
                }
            }
            if (coordinatesWeatherZones.size()==0){
                throw 1;
            }
            try{
                for (int i=-1;i<2;i++){
                    for (int j=-1;j<2;j++){
                        if ((i==0) & (j==0)){

                        }
                        else if ( (x+i<0) | (x+i>getGlobalMapSize()-1) | (y+j<0) | (y+j>getGlobalMapSize()-1) ){

                        }
                        else if (seaBlocks.at((x+i)*getGlobalMapSize()+(y+j))->getBlockAppearance()=='_'){
                            coordinates.push_back(new Coordinates);
                            coordinates.at(coordinates.size()-1)->setCooX(x+i);
                            coordinates.at(coordinates.size()-1)->setCooY(y+j);
                        }
                    }
                }
                if (coordinates.size()==0){
                    throw 1;
                }
                else {
                    int index;
                    int X;
                    int Y;
                    int xx;
                    int yy;
                    int XX;
                    int YY;
                    for (int i=0;i<coordinatesWeatherZones.size();i++){
                        X=coordinatesWeatherZones.at(i)->getCooX();
                        Y=coordinatesWeatherZones.at(i)->getCooY();
                        coordinatesWeatherZones.at(i)->setEudiValue(eudi(x,y,X,Y));
                    }
                    for (int j=coordinatesWeatherZones.size()-1;j>=0;j--){
                        index=minVector(coordinatesWeatherZones);
                        coordinatesSorted.push_back(new Coordinates);
                        coordinatesSorted.at(coordinatesSorted.size()-1)->setCooX(coordinatesWeatherZones.at(index)->getCooX());
                        coordinatesSorted.at(coordinatesSorted.size()-1)->setCooY(coordinatesWeatherZones.at(index)->getCooY());
                        coordinatesWeatherZones.erase(coordinatesWeatherZones.begin()+index);
                    }
                    XX=coordinatesSorted.at(0)->getCooX();
                    YY=coordinatesSorted.at(0)->getCooY();
                    for (int i=0;i<coordinates.size();i++){
                        xx=coordinates.at(i)->getCooX();
                        yy=coordinates.at(i)->getCooY();
                        coordinates.at(i)->setEudiValue(eudi(xx,yy,XX,YY));
                    }
                    for (int i=coordinates.size()-1;i>=0;i--){
                        coordinatesWeatherZonesSorted.push_back(new Coordinates);
                        index=minVector(coordinates);
                        coordinatesWeatherZonesSorted.at(coordinatesWeatherZonesSorted.size()-1)->setCooX(coordinates.at(index)->getCooX());
                        coordinatesWeatherZonesSorted.at(coordinatesWeatherZonesSorted.size()-1)->setCooY(coordinates.at(index)->getCooY());
                        coordinates.erase(coordinates.begin()+index);
                    }
                    bool flag=true;
                    index=0;
                    try {
                        if (coordinatesWeatherZonesSorted.size()==0){
                            throw 1;
                        }
                        while (flag){
                            try {
                                X=coordinatesWeatherZonesSorted.at(index)->getCooX();
                                Y=coordinatesWeatherZonesSorted.at(index)->getCooY();
                                if (seaBlocks.at(X*getGlobalMapSize()+Y)->getBlockAppearance()=='_'){
                                    setPosShipX(X);
                                    setPosShipY(Y);
                                    seaBlocks.at(X*getGlobalMapSize()+Y)->setBlockAppearance(getShipID());
                                    seaBlocks.at(x*getGlobalMapSize()+y)->setBlockAppearance('_');
                                    setCountMove(getCountMove()+1);
                                    flag=false;
                                    cout<<" "<<getShipID()<<getShipID2()<<"\t"<<"["<<x<<","<<y<<"]"<<"\t"<<"["<<X<<","<<Y<<"]";
                                    damaging();
                                    operation();
                                }
                                else {
                                    if (index+1>coordinatesWeatherZonesSorted.size()){
                                        throw 1;
                                    }
                                    else {
                                        index++;
                                    }
                                }
                            }
                            catch(int e){

                            }
                        }
                    }
                    catch(int e){

                    }
                }
            }
            catch(int e){

            }
        }
        catch(int e){
            int x=getPosShipX();
            int y=getPosShipY();
            int indexC;
            int X;
            int Y;
            vector<Coordinates*>coordinates;
            try{
                for (int k=-1;k<2;k++){
                    for (int l=-1;l<2;l++){
                        if ((k!=0) & (l!=0)){
                            if ( (x+k<0) | (x+k>getGlobalMapSize()-1) | (y+l<0) | (y+l>getGlobalMapSize()-1) ){

                            }
                            else if ( seaBlocks.at((x+k)*getGlobalMapSize()+y+l)->getBlockAppearance()=='_' ) {
                                coordinates.push_back(new Coordinates);
                                coordinates.at(coordinates.size()-1)->setCooX(x+k);
                                coordinates.at(coordinates.size()-1)->setCooY(y+l);
                            }
                            else {

                            }
                        }
                    }
                }
                if (coordinates.size()==0){
                    throw 1;
                }
                indexC=rand()%coordinates.size();
                X=coordinates.at(indexC)->getCooX();
                Y=coordinates.at(indexC)->getCooY();
                setPosShipX(X);
                setPosShipY(Y);
                if (seaBlocks.at(x*getGlobalMapSize()+y)->getBlockAppearance()=='X'){

                }
                else{
                    seaBlocks.at(x*getGlobalMapSize()+y)->setBlockAppearance('_');
                }
                seaBlocks.at(X*getGlobalMapSize()+Y)->setBlockAppearance(getShipID());
            }
            catch(int e){

            }
            setCountMove(getCountMove()+1);
            cout<<" "<<getShipID()<<getShipID2()<<"\t"<<"["<<x<<","<<y<<"]"<<"\t"<<"["<<X<<","<<Y<<"]";
            damaging();
            operation();
        }
    }
    else {

    }
    cout<<endl;
}

string ShipResearcher::operationCount(){

}



ShipCommercial::ShipCommercial(){
    setShipID('C');
    setSpeed(1);
    temp1=20*(rand()%6)+200-1;
    setHP(temp1);
    setMaxHP(temp1);
    setLoadTreasure(0);
    setLoadMax(10000);
    setLoadRecord(0);
    numShipCommercial++;
    setShipID2(numShipCommercial);
    corpusTreasure=0;
}
ShipCommercial::~ShipCommercial(){}

int ShipCommercial::numShipCommercial=0;
int ShipCommercial::getLoadRecord(){return loadRecord;}
void ShipCommercial::setLoadRecord(int x){loadRecord=x;}
int ShipCommercial::totalTreasure=0;

void ShipCommercial::operation(){
    try {
        if (getBroken()==false){
            int x=getPosShipX();
            int y=getPosShipY();
            int d=getLoadTreasure();

            try {
                if (d>=getLoadMax()){
                    throw 1;
                }
                else{
                    if (
                        (seaBlocks.at(x*getGlobalMapSize()+y)->getDepositTreasure()>0)
                        ){
                        cout<<"\t   Salvaged";
                    }
                    int pd=seaBlocks.at(x*getGlobalMapSize()+y)->getDepositTreasure()+d;
                    if (seaBlocks.at(x*getGlobalMapSize()+y)->getDepositTreasure()>0){
                        if (pd<getLoadMax()){
                            setLoadTreasure(pd);
                            setLoadRecord(getLoadRecord()+pd);
                            corpusTreasure+=pd;
                            totalTreasure+=pd;
                            cout<<" "<<pd-d<<" Treasure Points";
                            seaBlocks.at(x*getGlobalMapSize()+y)->setDepositTreasure(0);
                        }
                        else {
                            int qq=getLoadMax()-(d);
                            pd=qq+d;
                            setLoadTreasure(pd);
                            corpusTreasure+=pd;
                            totalTreasure+=pd;
                            setLoadRecord(getLoadRecord()+pd);
                            cout<<" "<<pd-d<<" Treasure Points";
                            seaBlocks.at(x*getGlobalMapSize()+y)->setDepositTreasure(seaBlocks.at(x*getGlobalMapSize()+y)->getDepositTreasure()-qq);
                        }
                    }
                }
            }
            catch(int e){
                int X=ports.at(0)->getPosHqX();
                int Y=ports.at(0)->getPosHqY();

                try {
                    vector<Coordinates*>coordinates;
                    for (int i=-2;i<3;i++){
                        for (int j=-2;j<3;j++){
                            if (seaBlocks.at((X+i)*getGlobalMapSize()+(Y+j))->getBlockAppearance()=='_'){
                                coordinates.push_back(new Coordinates);
                                coordinates.at(coordinates.size()-1)->setCooX(X+i);
                                coordinates.at(coordinates.size()-1)->setCooY(Y+j);
                            }
                        }
                    }
                    if (coordinates.size()==0){
                        throw 1.0;
                    }
                    int indexC=rand()%coordinates.size();
                    int xxx=coordinates.at(indexC)->getCooX();
                    int yyy=coordinates.at(indexC)->getCooY();
                    seaBlocks.at(x*getGlobalMapSize()+y)->setBlockAppearance('_');
                    setPosShipX(xxx);
                    setPosShipY(yyy);
                    seaBlocks.at(xxx*getGlobalMapSize()+yyy)->setBlockAppearance(getShipID());
                    ports.at(0)->setCollectionTreasure(ports.at(0)->getCollectionTreasure()+getLoadTreasure());
                    cout<<"\t   Deposited "<<getLoadTreasure()<<"Pd";
                    setLoadTreasure(0);
                }
                catch(float ee){

                }
            }
        }
        else {
            throw 'x';
        }
    }
    catch(char cc){

    }
}

void ShipCommercial::move8way(){
    try{
        if (getBroken()==false){
            int x=getPosShipX();
            int y=getPosShipY();
            int X;
            int Y;
            int indexC=0;
            int dd;
            vector<Coordinates*>coordinates;
            for (int i=-1;i<2;i++){
                for (int j=-1;j<2;j++){
                    if ((i==0) & (j==0)){

                    }
                    else if ( (x+i<0) | (x+i>getGlobalMapSize()-1) | (y+j<0) | (y+j>getGlobalMapSize()-1) ){

                    }
                    else if (seaBlocks.at((x+i)*getGlobalMapSize()+(y+j))->getBlockAppearance()=='_'){
                        coordinates.push_back(new Coordinates);
                        coordinates.at(coordinates.size()-1)->setCooX(x+i);
                        coordinates.at(coordinates.size()-1)->setCooY(y+j);
                        dd=seaBlocks.at((x+i)*getGlobalMapSize()+(y+j))->getDepositTreasure();
                        coordinates.at(coordinates.size()-1)->setEudiValue(dd);
                    }
                    else {

                    }
                }
            }
            if (coordinates.size()==0){
                throw 1;
            }
            else {
                int cc=0;
                for (int i=0;i<coordinates.size();i++){
                    cc=cc+coordinates.at(i)->getEudiValue();
                }
                if (cc==0){
                    indexC=rand()%coordinates.size();
                    X=coordinates.at(indexC)->getCooX();
                    Y=coordinates.at(indexC)->getCooY();
                    setPosShipX(X);
                    setPosShipY(Y);
                    seaBlocks.at(x*getGlobalMapSize()+y)->setBlockAppearance('_');
                    seaBlocks.at(X*getGlobalMapSize()+Y)->setBlockAppearance(getShipID());
                    setCountMove(getCountMove()+1);
                    cout<<" "<<getShipID()<<getShipID2()<<"\t"<<"["<<x<<","<<y<<"]"<<"\t"<<"["<<X<<","<<Y<<"]";
                    damaging();
                    operation();
                }
                else {
                    indexC=maxVector(coordinates);
                    X=coordinates.at(indexC)->getCooX();
                    Y=coordinates.at(indexC)->getCooY();
                    setPosShipX(X);
                    setPosShipY(Y);
                    seaBlocks.at(x*getGlobalMapSize()+y)->setBlockAppearance('_');
                    seaBlocks.at(X*getGlobalMapSize()+Y)->setBlockAppearance(getShipID());
                    setCountMove(getCountMove()+1);
                    cout<<" "<<getShipID()<<getShipID2()<<"\t"<<"["<<x<<","<<y<<"]"<<"\t"<<"["<<X<<","<<Y<<"]";
                    damaging();
                    operation();
                }
            }
        }
    }
    catch(int e){

    }
    cout<<endl;
}

string ShipCommercial::operationCount(){
    string tpd = static_cast<ostringstream*>( &(ostringstream() << corpusTreasure) )->str();
    return "   Treasure: "+tpd;
}



ShipMechanic::ShipMechanic(){
    setShipID('M');
    setSpeed(2);
    temp1=80*(rand()%6)+600-1;
    setHP(temp1);
    setMaxHP(temp1);
    setCountRepairs(0);
    numShipMechanic++;
    setShipID2(numShipMechanic);
    corpusRepairs=0;
}
ShipMechanic::~ShipMechanic(){}

int ShipMechanic::numShipMechanic=0;
int ShipMechanic::getCountRepairs(){return countRepairs;}
void ShipMechanic::setCountRepairs(int x){countRepairs=x;}
int ShipMechanic::totalRepairs=0;

void ShipMechanic::operation(){
    try {
        if (getBroken()==false){
            int x=getPosShipX();
            int y=getPosShipY();
            int cx;
            int cy;
            int rx;
            int ry;
            vector<Coordinates*>coordinates;
            try {
                for (int i=-1;i<2;i++){
                    for (int j=-1;j<2;j++){
                        if ( (x+i>=0) & (x+i<getGlobalMapSize()) & (y+j>=0) & (y+j<getGlobalMapSize()) ){
                            if ( (seaBlocks.at( (x+i)*getGlobalMapSize()+(y+j) )->getBlockAppearance()!='_') & (seaBlocks.at( (x+i)*getGlobalMapSize()+(y+j) )->getBlockAppearance()!='X') ){
                                coordinates.push_back(new Coordinates);
                                coordinates.at(coordinates.size()-1)->setCooX(x+i);
                                coordinates.at(coordinates.size()-1)->setCooY(y+j);
                            }
                        }
                    }
                }
                if (coordinates.size()==0){
                    throw 1;
                }
                for (int z=0;z<coordinates.size();z++){
                    cx=coordinates.at(z)->getCooX();
                    cy=coordinates.at(z)->getCooY();
                    for (int k=0;k<ships.size();k++){
                        rx=ships.at(k)->getPosShipX();
                        ry=ships.at(k)->getPosShipY();
                        if ( (cx==rx) & (cy==ry) ){
                            if (ships.at(k)->getBroken()){
                                ships.at(k)->setBroken(false);
                                ships.at(k)->setHP(getMaxHP());
                                ships.at(k)->setIdleTimer(getDefaultIdleTimer());
                                setCountRepairs(getCountRepairs()+1);
                                corpusRepairs++;
                                totalRepairs++;
                                cout<<"\t   Repaired "<<ships.at(k)->getShipID()<<ships.at(k)->getShipID2();
                            }
                        }
                    }
                }
            }
            catch(int e){

            }
        }
        else {
            throw 'x';
        }
    }
    catch(char cc){

    }
}

void ShipMechanic::move8way(){
    int x=getPosShipX();
    int y=getPosShipY();
    if (getBroken()==false){
        vector<Coordinates*>coordinates;
        vector<Coordinates*>coordinatesSorted;
        vector<Coordinates*>coordinatesWeatherZones;
        vector<Coordinates*>coordinatesWeatherZonesSorted;
        try {
            for (int i=0;i<ships.size();i++){
                if ( ( ships.at(i)->getPosShipX()==x ) & ( ships.at(i)->getPosShipY()==y ) ){

                }
                else if (ships.at(i)->getBroken()==true){
                    coordinatesWeatherZones.push_back(new Coordinates);
                    coordinatesWeatherZones.at(coordinatesWeatherZones.size()-1)->setCooX(ships.at(i)->getPosShipX());
                    coordinatesWeatherZones.at(coordinatesWeatherZones.size()-1)->setCooY(ships.at(i)->getPosShipY());
                }
            }
            if (coordinatesWeatherZones.size()==0){
                throw 1;
            }
            try{
                for (int i=-1;i<2;i++){
                    for (int j=-1;j<2;j++){
                        if ((i==0) & (j==0)){

                        }
                        else if ( (x+i<0) | (x+i>getGlobalMapSize()-1) | (y+j<0) | (y+j>getGlobalMapSize()-1) ){

                        }
                        else if (seaBlocks.at((x+i)*getGlobalMapSize()+(y+j))->getBlockAppearance()=='_'){
                            coordinates.push_back(new Coordinates);
                            coordinates.at(coordinates.size()-1)->setCooX(x+i);
                            coordinates.at(coordinates.size()-1)->setCooY(y+j);
                        }
                    }
                }
                if (coordinates.size()==0){
                    throw 1;
                }
                else {
                    int index;
                    int X;
                    int Y;
                    int xx;
                    int yy;
                    int XX;
                    int YY;
                    for (int i=0;i<coordinatesWeatherZones.size();i++){
                        X=coordinatesWeatherZones.at(i)->getCooX();
                        Y=coordinatesWeatherZones.at(i)->getCooY();
                        coordinatesWeatherZones.at(i)->setEudiValue(eudi(x,y,X,Y));
                    }
                    for (int j=coordinatesWeatherZones.size()-1;j>=0;j--){
                        index=minVector(coordinatesWeatherZones);
                        coordinatesSorted.push_back(new Coordinates);
                        coordinatesSorted.at(coordinatesSorted.size()-1)->setCooX(coordinatesWeatherZones.at(index)->getCooX());
                        coordinatesSorted.at(coordinatesSorted.size()-1)->setCooY(coordinatesWeatherZones.at(index)->getCooY());
                        coordinatesWeatherZones.erase(coordinatesWeatherZones.begin()+index);
                    }
                    XX=coordinatesSorted.at(0)->getCooX();
                    YY=coordinatesSorted.at(0)->getCooY();
                    for (int i=0;i<coordinates.size();i++){
                        xx=coordinates.at(i)->getCooX();
                        yy=coordinates.at(i)->getCooY();
                        coordinates.at(i)->setEudiValue(eudi(xx,yy,XX,YY));
                    }
                    for (int i=coordinates.size()-1;i>=0;i--){
                        coordinatesWeatherZonesSorted.push_back(new Coordinates);
                        index=minVector(coordinates);
                        coordinatesWeatherZonesSorted.at(coordinatesWeatherZonesSorted.size()-1)->setCooX(coordinates.at(index)->getCooX());
                        coordinatesWeatherZonesSorted.at(coordinatesWeatherZonesSorted.size()-1)->setCooY(coordinates.at(index)->getCooY());
                        coordinates.erase(coordinates.begin()+index);
                    }
                    bool flag=true;
                    index=0;
                    try {
                        if (coordinatesWeatherZonesSorted.size()==0){
                            throw 1;
                        }
                        while (flag){
                            try {
                                X=coordinatesWeatherZonesSorted.at(index)->getCooX();
                                Y=coordinatesWeatherZonesSorted.at(index)->getCooY();
                                if (seaBlocks.at(X*getGlobalMapSize()+Y)->getBlockAppearance()=='_'){
                                    setPosShipX(X);
                                    setPosShipY(Y);
                                    seaBlocks.at(X*getGlobalMapSize()+Y)->setBlockAppearance(getShipID());
                                    seaBlocks.at(x*getGlobalMapSize()+y)->setBlockAppearance('_');
                                    setCountMove(getCountMove()+1);
                                    cout<<" "<<getShipID()<<getShipID2()<<"\t"<<"["<<x<<","<<y<<"]"<<"\t"<<"["<<X<<","<<Y<<"]";
                                    damaging();
                                    operation();
                                    flag=false;
                                }
                                else {
                                    if (index+1>coordinatesWeatherZonesSorted.size()){
                                        throw 1;
                                    }
                                    else {
                                        index++;
                                    }
                                }
                            }
                            catch(int e){

                            }
                        }
                    }
                    catch(int e){

                    }
                }
            }
            catch(int e){

            }
        }
        catch(int e){
            int x=getPosShipX();
            int y=getPosShipY();
            int indexC;
            int X = x;
            int Y = y;
            vector<Coordinates*>coordinates;
            try{
                for (int k=-1;k<2;k++){
                    for (int l=-1;l<2;l++){
                        if ((k!=0) & (l!=0)){
                            if ( (x+k<0) | (x+k>getGlobalMapSize()-1) | (y+l<0) | (y+l>getGlobalMapSize()-1) ){

                            }
                            else if ( seaBlocks.at((x+k)*getGlobalMapSize()+y+l)->getBlockAppearance()=='_' ) {
                                coordinates.push_back(new Coordinates);
                                coordinates.at(coordinates.size()-1)->setCooX(x+k);
                                coordinates.at(coordinates.size()-1)->setCooY(y+l);
                            }
                            else {

                            }
                        }
                    }
                }
                if (coordinates.size()==0){
                    throw 1;
                }
                indexC=rand()%coordinates.size();
                X=coordinates.at(indexC)->getCooX();
                Y=coordinates.at(indexC)->getCooY();
                setPosShipX(X);
                setPosShipY(Y);
                if (seaBlocks.at(x*getGlobalMapSize()+y)->getBlockAppearance()=='X'){

                }
                else{
                    seaBlocks.at(x*getGlobalMapSize()+y)->setBlockAppearance('_');
                }
                seaBlocks.at(X*getGlobalMapSize()+Y)->setBlockAppearance(getShipID());
            }
            catch(int e){

            }
            setCountMove(getCountMove()+1);
            cout<<" "<<getShipID()<<getShipID2()<<"\t"<<"["<<x<<","<<y<<"]"<<"\t"<<"["<<X<<","<<Y<<"]";
            damaging();
            operation();
        }
    }
    else {

    }
    cout<<endl;
}

string ShipMechanic::operationCount(){
    string tr = static_cast<ostringstream*>( &(ostringstream() << corpusRepairs) )->str();
    return "   Repairs: "+tr;
}



Coordinates::Coordinates(){}
Coordinates::~Coordinates(){}

int Coordinates::getCooX(){return cooX;}
void Coordinates::setCooX(int x){cooX=x;}
int Coordinates::getCooY(){return cooY;}
void Coordinates::setCooY(int x){cooY=x;}
float Coordinates::getEudiValue(){return eudiValue;}
void Coordinates::setEudiValue(float x){eudiValue=x;}



Run::Run(){}

vector<Sea*>*Run::getSeaBlocks(){return &seaBlocks;}

void Run::createMap(){
    for (int i=0;i<getGlobalMapSize();i++){
        for (int j=0;j<getGlobalMapSize();j++){
            getSeaBlocks()->push_back(new Sea);
            getSeaBlocks()->at(i*getGlobalMapSize()+j)->setAxisX(i);
            getSeaBlocks()->at(i*getGlobalMapSize()+j)->setAxisY(j);
            getSeaBlocks()->at(i*getGlobalMapSize()+j)->setBlockAppearance('_');
        }
    }
    cout<<"An array of ["<<getGlobalMapSize()<<", "<<getGlobalMapSize()<<"] is created."<<endl;
}

void Run::drawMap(){

    cout<<endl<<"Drawing the Sea..."<<endl;
    HANDLE hConsole;
    hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i=0;i<getGlobalMapSize();i++){
        for (int j=0;j<getGlobalMapSize();j++){
            if (
                getSeaBlocks()->at(i*getGlobalMapSize()+j)->getBlockAppearance()=='Q'
                ){
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);
                }
            else{
                    try{
                        if (getSeaBlocks()->at(i*getGlobalMapSize()+j)->getBlockAppearance()!='X'){
                            if (        (getSeaBlocks()->at(i*getGlobalMapSize()+j)->getWeather()>=0) &&
                                        (getSeaBlocks()->at(i*getGlobalMapSize()+j)->getWeather()<4)
                            ){
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_RED);
                            }
                            else if (   (getSeaBlocks()->at(i*getGlobalMapSize()+j)->getWeather()>=4) &&
                                        (getSeaBlocks()->at(i*getGlobalMapSize()+j)->getWeather()<8)
                                     ){
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_RED);
                            }
                            else if (   (getSeaBlocks()->at(i*getGlobalMapSize()+j)->getWeather()>=8) &&
                                        (getSeaBlocks()->at(i*getGlobalMapSize()+j)->getWeather()<=10)
                                     ){
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY | BACKGROUND_RED);
                            }
                            else{
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY);
                            }
                        }
                        else{
                            throw 1;
                        }
                    }
                    catch(int e){
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY | BACKGROUND_BLUE);
                    }
            }
            cout<<getSeaBlocks()->at(i*getGlobalMapSize()+j)->getBlockAppearance();
            cout<<'|';
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE| FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_RED);
        cout<<i<<endl;
    }
    for (int i=0;i<getGlobalMapSize();i++){
        if (i<10){
            cout<<i<<' ';
        }
        else {
            cout<<i%10<<' ';
        }
    }
    cout<<endl;
    Sleep(400);
}

vector<Port*>*Run::getPorts(){return &ports;}

void Run::assemblePort(){
    getPorts()->push_back(new Port);
    int x=getPorts()->at(getPorts()->size()-1)->getPosHqX();
    int y=getPorts()->at(getPorts()->size()-1)->getPosHqY();
    for (int i=-1;i<2;i++){
        for (int j=-1;j<2;j++){
            getSeaBlocks()->at( (x+i)*getGlobalMapSize() + (y+j) )->setBlockAppearance('Q');
        }
    }
    cout<<"Assembling the Ports at ["<<x<<", "<<y<<"]."<<endl;
    cout<<"The Requirements are "<<getPorts()->at(0)->getRequirementTreasure()<<"Pd."<<endl;
}

void Run::setWeather(){
    float x;
    float y;
    int q;
    float p;
    for (int i=0;i<getGlobalMapSize();i++){
        for (int j=0;j<getGlobalMapSize();j++){
            try{
                if (    !(  getSeaBlocks()->at(i*getGlobalMapSize()+j)->getBlockAppearance()=='Q'
                         )
                    ){
                        x=1+rand()%10;
                        getSeaBlocks()->at(i*getGlobalMapSize()+j)->setWeather(x);
                    }
                    else{
                        throw 1;
                    }
            }
            catch(int e){
                getSeaBlocks()->at(i*getGlobalMapSize()+j)->setWeather(0);
            }
        }
    }
}

vector<Ship*>*Run::getShips(){return &ships;}

void Run::assembleShipPirate(int O){
    int x;
    int y;
    int hqX=getPorts()->at(rand()%(getPorts()->size()))->getPosHqX();
    int hqY=getPorts()->at(rand()%(getPorts()->size()))->getPosHqY();
    bool flag;
    int dice;
    int counter=0;
    for (int z=0;z<O;z++){
            flag=true;
            int shipNum=getShips()->size();
            try {
                if (shipNum>0){
                    //int X[shipNum];
					int* X = (int*)malloc(shipNum*sizeof(int));
                    //int Y[shipNum];
					int* Y = (int*)malloc(shipNum*sizeof(int));
                    for (int i=0;i<shipNum;i++){
                        X[i]=getShips()->at(i)->getPosShipX();
                        Y[i]=getShips()->at(i)->getPosShipY();
                    }
                    dice=1+rand()%3;
                    switch(dice){
                    case 1:
                        x=hqX-2;
                        y=hqY-pow(-1,rand()%2)*(rand()%3);
                        break;
                    case 2:
                        x=hqX+2;
                        y=hqY-pow(-1,rand()%2)*(rand()%3);
                        break;
                    case 3:
                        x=hqX-pow(-1,rand()%2)*(rand()%3);
                        y=hqY-2;
                        break;
                    default:
                        x=hqX-pow(-1,rand()%2)*(rand()%3);
                        y=hqY+2;
                    }
                    while (flag){
                        for (int i=0;i<shipNum;i++){
                            if (x==X[i] && y==Y[i]){
                                counter++;
                            }
                        }
                        if (counter==0){
                            flag=false;
                        }
                        else {
                            dice=1+rand()%3;
                            switch(dice){
                            case 1:
                                x=hqX-2;
                                y=hqY-pow(-1,rand()%2)*(rand()%3);
                                break;
                            case 2:
                                x=hqX+2;
                                y=hqY-pow(-1,rand()%2)*(rand()%3);
                                break;
                            case 3:
                                x=hqX-pow(-1,rand()%2)*(rand()%3);
                                y=hqY-2;
                                break;
                            default:
                                x=hqX-pow(-1,rand()%2)*(rand()%3);
                                y=hqY+2;
                            }
                        }counter=0;
                    }
                    getShips()->push_back(new ShipPirate);
                    getShips()->at(getShips()->size()-1)->setPosShipX(x);
                    getShips()->at(getShips()->size()-1)->setPosShipY(y);
                    getSeaBlocks()->at(x*getGlobalMapSize()+y)->setBlockAppearance(getShips()->at(getShips()->size()-1)->getShipID());

					free(X);
					free(Y);
                }
                else {
                    throw 1;
                }

            }
            catch(int e){
                dice=1+rand()%3;
                switch(dice){
                case 1:
                    x=hqX-2;
                    y=hqY-pow(-1,rand()%2)*(rand()%3);
                    break;
                case 2:
                    x=hqX+2;
                    y=hqY-pow(-1,rand()%2)*(rand()%3);
                    break;
                case 3:
                    x=hqX-pow(-1,rand()%2)*(rand()%3);
                    y=hqY-2;
                    break;
                default:
                    x=hqX-pow(-1,rand()%2)*(rand()%3);
                    y=hqY+2;
                }
                getShips()->push_back(new ShipPirate);
                getShips()->at(getShips()->size()-1)->setPosShipX(x);
                getShips()->at(getShips()->size()-1)->setPosShipY(y);
                getSeaBlocks()->at(x*getGlobalMapSize()+y)->setBlockAppearance(getShips()->at(getShips()->size()-1)->getShipID());
            }
    }
    cout<<"Assembling "<<O<<" pirate ships."<<endl;
}

void Run::assembleShipResearcher(int O){
    int x;
    int y;
    int hqX=getPorts()->at(rand()%(getPorts()->size()))->getPosHqX();
    int hqY=getPorts()->at(rand()%(getPorts()->size()))->getPosHqY();
    bool flag;
    int dice;
    int counter=0;
    for (int z=0;z<O;z++){
            flag=true;
            int shipNum=getShips()->size();
            try {
                if (shipNum>0){
                    //int X[shipNum];
					int* X = (int*)malloc(shipNum*sizeof(int));
                    //int Y[shipNum];
					int* Y = (int*)malloc(shipNum*sizeof(int));
                    for (int i=0;i<shipNum;i++){
                        X[i]=getShips()->at(i)->getPosShipX();
                        Y[i]=getShips()->at(i)->getPosShipY();
                    }
                    dice=1+rand()%3;
                    switch(dice){
                    case 1:
                        x=hqX-2;
                        y=hqY-pow(-1,rand()%2)*(rand()%3);
                        break;
                    case 2:
                        x=hqX+2;
                        y=hqY-pow(-1,rand()%2)*(rand()%3);
                        break;
                    case 3:
                        x=hqX-pow(-1,rand()%2)*(rand()%3);
                        y=hqY-2;
                        break;
                    default:
                        x=hqX-pow(-1,rand()%2)*(rand()%3);
                        y=hqY+2;
                    }
                    while (flag){
                        for (int i=0;i<shipNum;i++){
                            if (x==X[i] && y==Y[i]){
                                counter++;
                            }
                        }
                        if (counter==0){
                            flag=false;
                        }
                        else {
                            dice=1+rand()%3;
                            switch(dice){
                            case 1:
                                x=hqX-2;
                                y=hqY-pow(-1,rand()%2)*(rand()%3);
                                break;
                            case 2:
                                x=hqX+2;
                                y=hqY-pow(-1,rand()%2)*(rand()%3);
                                break;
                            case 3:
                                x=hqX-pow(-1,rand()%2)*(rand()%3);
                                y=hqY-2;
                                break;
                            default:
                                x=hqX-pow(-1,rand()%2)*(rand()%3);
                                y=hqY+2;
                            }
                        }counter=0;
                    }
                    getShips()->push_back(new ShipResearcher);
                    getShips()->at(getShips()->size()-1)->setPosShipX(x);
                    getShips()->at(getShips()->size()-1)->setPosShipY(y);
                    getSeaBlocks()->at(x*getGlobalMapSize()+y)->setBlockAppearance(getShips()->at(getShips()->size()-1)->getShipID());

					free(X);
					free(Y);
                }
                else {
                    throw 1;
                }

            }
            catch(int e){
                dice=1+rand()%3;
                switch(dice){
                case 1:
                    x=hqX-2;
                    y=hqY-pow(-1,rand()%2)*(rand()%3);
                    break;
                case 2:
                    x=hqX+2;
                    y=hqY-pow(-1,rand()%2)*(rand()%3);
                    break;
                case 3:
                    x=hqX-pow(-1,rand()%2)*(rand()%3);
                    y=hqY-2;
                    break;
                default:
                    x=hqX-pow(-1,rand()%2)*(rand()%3);
                    y=hqY+2;
                }
                getShips()->push_back(new ShipResearcher);
                getShips()->at(getShips()->size()-1)->setPosShipX(x);
                getShips()->at(getShips()->size()-1)->setPosShipY(y);
                getSeaBlocks()->at(x*getGlobalMapSize()+y)->setBlockAppearance(getShips()->at(getShips()->size()-1)->getShipID());
            }
    }
    cout<<"Assembling "<<O<<" researcher ships."<<endl;
}

void Run::assembleShipCommercial(int O){
    int x;
    int y;
    int hqX=getPorts()->at(rand()%(getPorts()->size()))->getPosHqX();
    int hqY=getPorts()->at(rand()%(getPorts()->size()))->getPosHqY();
    bool flag;
    int dice;
    int counter=0;
    for (int z=0;z<O;z++){
            flag=true;
            int shipNum=getShips()->size();
            try {
                if (shipNum>0){
                    //int X[shipNum];
					int* X = (int*)malloc(shipNum*sizeof(int));
                    //int Y[shipNum];
					int* Y = (int*)malloc(shipNum*sizeof(int));
                    for (int i=0;i<shipNum;i++){
                        X[i]=getShips()->at(i)->getPosShipX();
                        Y[i]=getShips()->at(i)->getPosShipY();
                    }
                    dice=1+rand()%3;
                    switch(dice){
                    case 1:
                        x=hqX-2;
                        y=hqY-pow(-1,rand()%2)*(rand()%3);
                        break;
                    case 2:
                        x=hqX+2;
                        y=hqY-pow(-1,rand()%2)*(rand()%3);
                        break;
                    case 3:
                        x=hqX-pow(-1,rand()%2)*(rand()%3);
                        y=hqY-2;
                        break;
                    default:
                        x=hqX-pow(-1,rand()%2)*(rand()%3);
                        y=hqY+2;
                    }
                    while (flag){
                        for (int i=0;i<shipNum;i++){
                            if (x==X[i] && y==Y[i]){
                                counter++;
                            }
                        }
                        if (counter==0){
                            flag=false;
                        }
                        else {
                            dice=1+rand()%3;
                            switch(dice){
                            case 1:
                                x=hqX-2;
                                y=hqY-pow(-1,rand()%2)*(rand()%3);
                                break;
                            case 2:
                                x=hqX+2;
                                y=hqY-pow(-1,rand()%2)*(rand()%3);
                                break;
                            case 3:
                                x=hqX-pow(-1,rand()%2)*(rand()%3);
                                y=hqY-2;
                                break;
                            default:
                                x=hqX-pow(-1,rand()%2)*(rand()%3);
                                y=hqY+2;
                            }
                        }counter=0;
                    }
                    getShips()->push_back(new ShipCommercial);
                    getShips()->at(getShips()->size()-1)->setPosShipX(x);
                    getShips()->at(getShips()->size()-1)->setPosShipY(y);
                    getSeaBlocks()->at(x*getGlobalMapSize()+y)->setBlockAppearance(getShips()->at(getShips()->size()-1)->getShipID());

					free(X);
					free(Y);
                }
                else {
                    throw 1;
                }
            }
            catch(int e){
                dice=1+rand()%3;
                switch(dice){
                case 1:
                    x=hqX-2;
                    y=hqY-pow(-1,rand()%2)*(rand()%3);
                    break;
                case 2:
                    x=hqX+2;
                    y=hqY-pow(-1,rand()%2)*(rand()%3);
                    break;
                case 3:
                    x=hqX-pow(-1,rand()%2)*(rand()%3);
                    y=hqY-2;
                    break;
                default:
                    x=hqX-pow(-1,rand()%2)*(rand()%3);
                    y=hqY+2;
                }
                getShips()->push_back(new ShipCommercial);
                getShips()->at(getShips()->size()-1)->setPosShipX(x);
                getShips()->at(getShips()->size()-1)->setPosShipY(y);
                getSeaBlocks()->at(x*getGlobalMapSize()+y)->setBlockAppearance(getShips()->at(getShips()->size()-1)->getShipID());
            }
    }
    cout<<"Assembling "<<O<<" commercial ships."<<endl;
}

void Run::assembleShipMechanic(int O){
    int x;
    int y;
    int hqX=getPorts()->at(rand()%(getPorts()->size()))->getPosHqX();
    int hqY=getPorts()->at(rand()%(getPorts()->size()))->getPosHqY();
    bool flag;
    int dice;
    int counter=0;
    for (int z=0;z<O;z++){
            flag=true;
            int shipNum=getShips()->size();
            try {
                if (shipNum>0){
                    //int X[shipNum];
					int* X = (int*)malloc(shipNum*sizeof(int));
                    //int Y[shipNum];
					int* Y = (int*)malloc(shipNum*sizeof(int));
                    for (int i=0;i<shipNum;i++){
                        X[i]=getShips()->at(i)->getPosShipX();
                        Y[i]=getShips()->at(i)->getPosShipY();
                    }
                    dice=1+rand()%3;
                    switch(dice){
                    case 1:
                        x=hqX-2;
                        y=hqY-pow(-1,rand()%2)*(rand()%3);
                        break;
                    case 2:
                        x=hqX+2;
                        y=hqY-pow(-1,rand()%2)*(rand()%3);
                        break;
                    case 3:
                        x=hqX-pow(-1,rand()%2)*(rand()%3);
                        y=hqY-2;
                        break;
                    default:
                        x=hqX-pow(-1,rand()%2)*(rand()%3);
                        y=hqY+2;
                    }
                    while (flag){
                        for (int i=0;i<shipNum;i++){
                            if (x==X[i] && y==Y[i]){
                                counter++;
                            }
                        }
                        if (counter==0){
                            flag=false;
                        }
                        else {
                            dice=1+rand()%3;
                            switch(dice){
                            case 1:
                                x=hqX-2;
                                y=hqY-pow(-1,rand()%2)*(rand()%3);
                                break;
                            case 2:
                                x=hqX+2;
                                y=hqY-pow(-1,rand()%2)*(rand()%3);
                                break;
                            case 3:
                                x=hqX-pow(-1,rand()%2)*(rand()%3);
                                y=hqY-2;
                                break;
                            default:
                                x=hqX-pow(-1,rand()%2)*(rand()%3);
                                y=hqY+2;
                            }
                        }counter=0;
                    }
                    getShips()->push_back(new ShipMechanic);
                    getShips()->at(getShips()->size()-1)->setPosShipX(x);
                    getShips()->at(getShips()->size()-1)->setPosShipY(y);
                    getSeaBlocks()->at(x*getGlobalMapSize()+y)->setBlockAppearance(getShips()->at(getShips()->size()-1)->getShipID());

					free(X);
					free(Y);
                }
                else {
                    throw 1;
                }
            }
            catch(int e){
                dice=1+rand()%3;
                switch(dice){
                case 1:
                    x=hqX-2;
                    y=hqY-pow(-1,rand()%2)*(rand()%3);
                    break;
                case 2:
                    x=hqX+2;
                    y=hqY-pow(-1,rand()%2)*(rand()%3);
                    break;
                case 3:
                    x=hqX-pow(-1,rand()%2)*(rand()%3);
                    y=hqY-2;
                    break;
                default:
                    x=hqX-pow(-1,rand()%2)*(rand()%3);
                    y=hqY+2;
                }
                getShips()->push_back(new ShipMechanic);
                getShips()->at(getShips()->size()-1)->setPosShipX(x);
                getShips()->at(getShips()->size()-1)->setPosShipY(y);
                getSeaBlocks()->at(x*getGlobalMapSize()+y)->setBlockAppearance(getShips()->at(getShips()->size()-1)->getShipID());
            }
    }
    cout<<"Assembling "<<O<<" mechanic ships."<<endl;
}

void Run::idleExpiration(){
    for (int i=ships.size()-1;i>=0;i--){
        if (getShips()->at(i)->getBroken()==true){
            getShips()->at(i)->setIdleTimer(getShips()->at(i)->getIdleTimer()-1);
        }
        try {
            if (getShips()->at(i)->getIdleTimer()>0){

            }
            else {
                throw 1;
            }
        }
        catch(int e){
            int x=getShips()->at(i)->getPosShipX();
            int y=getShips()->at(i)->getPosShipY();
            getSeaBlocks()->at(x*getGlobalMapSize()+y)->setDepositTreasure(getShips()->at(i)->getLoadTreasure());
            getSeaBlocks()->at(x*getGlobalMapSize()+y)->setBlockAppearance('X');
            getShips()->at(i)->destroyShip(i);
        }
    }
}

bool Run::terminateSimulation(){
    int x=0;
    try {
        if (getShips()->size()<1){
            cout<<"All Ships were destroyed. Simulation terminated as a failure."<<endl;
            throw 1;
        }
        for (int i=0;i<getShips()->size();i++){
            if (getShips()->at(i)->getLoadTreasure()==150){
                cout<<"Ship "<<getShips()->at(i)->getShipID()<<getShips()->at(i)->getShipID2()<<" collected lots of treasures. Simulation terminated as a success."<<endl;
                throw 1;
            }
        }
        for (int i=0;i<getShips()->size();i++){
            if (getShips()->at(i)->getBroken()==true){
                x++;
            }
        }
        if (x>=getShips()->size()){
            cout<<"All Ships were broken and cannot be repaired. Simulation terminated as a failure."<<endl;
            throw 1;
        }
        return true;
    }
    catch(int e){
        return false;
    }
}

void Run::operateAll(){
    int t;
    for (int i=0;i<getShips()->size();i++){
        t=getShips()->at(i)->getSpeed();
        for (int j=0;j<t;j++){
            getShips()->at(i)->move8way();
        }
    }
}

void Run::MENU(){
    bool loop=true;
    int choice;
    string ccc;
    float weather;
    int pdp;
    int x;
    int y;
    string getInput;
    if(_kbhit()&&_getch()){

        while (loop){
                cout<<endl
                <<"-----------MENU-----------"<<endl<<endl
                <<"1.Continue simulation"<<endl
                <<"2.Insert Ship"<<endl
                <<"3.Insert Port"<<endl
                <<"4.Deteriorate Ship"<<endl
                <<"5.Sea Infomartion"<<endl
                <<"6.Ship Information"<<endl
                <<"7.Restart"<<endl
                <<"8.Exit"<<endl<<endl;

                try {
                    cin>>ccc;
                    stringstream convert(ccc);
                    if ( !(convert >> choice) ){
                        throw 1;
                    }
                }
                catch( int e ) {
                    choice=1;
                }

                switch (choice){
                    case 1: {
                        loop=false;
                        break;
                    }
                    case 2: {
                        cout<<"Insert coordinates: ";
                        cin>>x;
                        cin>>y;
                        if(x>getGlobalMapSize()-1 || x<0 || y>getGlobalMapSize()-1 || y<0){
                            cout<<"The coordinates you requested are out of the bounds of the 2D array Sea Map. Please insert a different set of coordinates."<<endl;
                            break;
                        }
                        else if(seaBlocks.at(x*getGlobalMapSize()+y)->getBlockAppearance()=='_'){
                            cout<<"What type of Ship do you want to insert? Type your choice as instructed in the brackets."<<endl;
                            cout<<"Pirate [P]"<<endl;
                            cout<<"Researcher [R]"<<endl;
                            cout<<"Commercial [C]"<<endl;
                            cout<<"Mechanic [M]"<<endl;

                            cin>>getInput;
                            if(getInput=="P"){
                                ships.push_back(new ShipPirate);
                                ships.at(ships.size()-1)->setPosShipX(x);
                                ships.at(ships.size()-1)->setPosShipY(y);
                                seaBlocks.at(x*getGlobalMapSize()+y)->setBlockAppearance(ships.at(ships.size()-1)->getShipID());
                                loop=false;
                            }
                            else if(getInput=="R"){
                                ships.push_back(new ShipResearcher);
                                ships.at(ships.size()-1)->setPosShipX(x);
                                ships.at(ships.size()-1)->setPosShipY(y);
                                seaBlocks.at(x*getGlobalMapSize()+y)->setBlockAppearance(ships.at(ships.size()-1)->getShipID());
                                loop=false;
                            }
                            else if(getInput=="C"){
                                ships.push_back(new ShipCommercial);
                                ships.at(ships.size()-1)->setPosShipX(x);
                                ships.at(ships.size()-1)->setPosShipY(y);
                                seaBlocks.at(x*getGlobalMapSize()+y)->setBlockAppearance(ships.at(ships.size()-1)->getShipID());
                                loop=false;
                            }
                            else if(getInput=="M"){
                                ships.push_back(new ShipMechanic);
                                ships.at(ships.size()-1)->setPosShipX(x);
                                ships.at(ships.size()-1)->setPosShipY(y);
                                seaBlocks.at(x*getGlobalMapSize()+y)->setBlockAppearance(ships.at(ships.size()-1)->getShipID());
                                loop=false;
                            }
                            else{
                                cout<<"Unexpected Input. Please insert a character to the corresponding class."<<endl;;
                            }
                            cout<<endl;
                            break;
                        }
                        else {
                            cout<<"This location is occupied. Please insert a different set of coordinates."<<endl;
                        }
                    }
                    case 3: {
                        cout<<"Insert coordinates: ";
                        cin>>x;
                        cin>>y;
                        if(x>getGlobalMapSize()-1 || x<0 || y>getGlobalMapSize()-1 || y<0){
                            cout<<"The coordinates you requested are out of the bounds of the 2D array Sea Map. Please insert a different set of coordinates."<<endl;
                            break;
                        }
                        else {
                            ports.push_back(new Port);
                            ports.at(ports.size()-1)->setPosHqX(x);
                            ports.at(ports.size()-1)->setPosHqY(y);
                            for (int i=-1;i<2;i++){
                                for (int j=-1;j<2;j++){
                                    getSeaBlocks()->at( (x+i)*getGlobalMapSize() + (y+j) )->setBlockAppearance('Q');
                                }
                            }
                            cout<<"The port was inserted at ["<<x<<","<<y<<"]"<<endl;
                        break;
                        }
                    }
                    case 4: {
                        char choice21;
                        int choice22;
						int shipNum = ships.size();
                        //char C1[ships.size()];
						char* C1 = (char*)malloc(shipNum*sizeof(char));
                        int* C2 = (int*)malloc(shipNum*sizeof(int));
                        cout<<"The existing Ships are: "<<endl;
                        for (int i=0;i<ships.size();i++){
                            cout<<ships.at(i)->getShipID()<<ships.at(i)->getShipID2()<<endl;
                            C1[i]=ships.at(i)->getShipID();
                            C2[i]=ships.at(i)->getShipID2();
                        }
                        cout<<"Type the exact name of the Ship you wish to alter."<<endl;
                        cin>>choice21>>choice22;

                        int index=-1;
                        for (int i=0;i<ships.size();i++){
                            if ( ( choice21==C1[i] ) & ( choice22==C2[i] ) ){
                                index=i;
                            }
                        }
                        if (index==-1){
                            cout<<"The name of the Ship you inserted was invalid. No Ship will be altered this floor."<<endl;
                        }
                        else {
                            char choice3;
                            cout<<"Do you want to repair [R] "<<choice21<<choice22<<", damage [D] it, or remove [X] it from the simulation?"<<endl;
                            cin>>choice3;
                            if (choice3=='R'){
                                ships.at(index)->setBroken(0);
                                ships.at(index)->setHP(ships.at(index)->getMaxHP());
                            }
                            else if (choice3=='D'){
                                int damageHP=0;
                                cout<<"How many points of HP damage do you want to cause to "<<choice21<<choice22<<"? Your choice should be an non-negative integer."<<endl;
                                cin>>damageHP;
                                if (damageHP<0){
                                    cout<<"The value you assigned was invalid. The original remaining HP remain."<<endl;
                                }
                                else {
                                    ships.at(index)->setHP(ships.at(index)->getHP()-damageHP);
                                }
                            }
                            else if (choice3=='X'){
                                ships.at(index)->destroyShip(index);
                            }
                            else {
                                cout<<"Your choice was invalid. No Ship is going to be altered this round."<<endl;
                            }
                        }
                        cout<<endl;

						free(C1);
						free(C2);

                        break;
                    }
                    case 5: {
                        float sumWeather=0.0;
                        int countFlags=0;
                        int remainingTreasure=0;
                        int remainingIridium=0;
                        int remainingPlatinum=0;
                        for (int i=0;i<seaBlocks.size();i++){
                            sumWeather=sumWeather+seaBlocks.at(i)->getWeather();
                            remainingTreasure=remainingTreasure+seaBlocks.at(i)->getDepositTreasure();
                            if (seaBlocks.at(i)->getBlockAppearance()=='X'){
                                countFlags=countFlags+1;
                            }
                        }
                        sumWeather=sumWeather/seaBlocks.size();
                        cout<<"Sea Information."<<endl;
                        cout<<"-.-.-.-.-.-.-.-.-.-"<<endl;
                        cout<<"->Mean Weather:                "<<sumWeather<<endl;
                        cout<<"->Remaining Treasure Points: "<<remainingTreasure<<endl;
                        cout<<endl;
                        break;
                    }
                    case 6: {
                        cout<<"Ships Information."<<endl;

                        break;
                    }
                    case 7: {
                        seaBlocks.clear();
                        ships.clear();
                        ports.clear();
                        createMap();
                        assemblePort();
                        setWeather();
                        assembleShipResearcher(2);
                        assembleShipCommercial(4);
                        assembleShipMechanic(2);
                        drawMap();
                        loop=false;
                        break;
                    }
                    case 8: {
                        exit(0);
                        break;
                    }
                    default: {
						loop=false;
                        break;
                    }
                }
        }
    }
}

