#include "header.h"

using namespace nmspc;

void MaximizeOutputWindow(void){ // for full screen
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_MAXIMIZE);
} //

void RestoreOutputWindow(void){ // for full screen
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_RESTORE);
} //

int main(){
    ShipResearcher::numShipResearcher=0;
    ShipCommercial::numShipCommercial=0;
    ShipMechanic::numShipMechanic=0;
    srand(time(NULL));
    system("color 0");
    system("pause");
    MaximizeOutputWindow(); // for full screen
    Run runSimulation;
    runSimulation.createMap();
    for (int i=0;i<3;i++){
        runSimulation.assemblePort();
    }
    runSimulation.setWeather();
    runSimulation.assembleShipPirate(2);
    runSimulation.assembleShipResearcher(2);
    runSimulation.assembleShipCommercial(2);
    runSimulation.assembleShipMechanic(2);
    system("pause");
    runSimulation.drawMap();

    while (runSimulation.terminateSimulation()){
        //system("pause");
        runSimulation.MENU();
        cout<<"Ship\t| From\t| To\t| Damage | Broken | Operation"<<endl;
        runSimulation.setWeather();
        runSimulation.operateAll();
        runSimulation.idleExpiration();
        runSimulation.drawMap();
        //system("pause");
    }
    RestoreOutputWindow(); // for full screen
    return 0;
}
