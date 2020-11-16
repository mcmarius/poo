#include <ctime>
#include "Simulare.h"
#include "simulation_error.h"

int main() {
//    srand((unsigned int) time(nullptr));
//    /*for (unsigned char i = 0; i < 255; ++i) {
//        std::cout<<(int)i<<' '<<i<<'\t';
//    }
//    std::cout<<'\n';*/
//    Simulare s(21, 10, 10);        // ox: coloane; oy: linii
//    std::string input;
//    int runde = 0;
//    do {
//        std::cout << "> ";
////        std::cin >> input;
//    } while/*(input.find("da") != std::string::npos && */(s.simuleaza(0) && ++runde);
//    s.afisare();
//
//    std::cout << "Au fost simulate " << runde;
//    if((runde % 100) / 10 > 1)
//        std::cout << " de";
//    std::cout << " runde.\nProgramul se inchide in 5 secunde...\n";
//    time_t t=time(NULL);
//    while(t+5>=time(NULL));


    try {
        Simulare s(1, 2, 3);
        s.simuleaza();
        s.afisare();
    }
    catch(simulation_error& err) {
        std::cout << err.what();
    }

//    AgentFoarfeca a1({1, 2}), a2({3, 4});
//    a1 = a1;
//    std::cout << a1 << "\nsi altceva\n" << a2;
    return 0;
}
