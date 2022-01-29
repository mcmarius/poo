#include <iostream>

class trotineta {
    std::string culoare;
    int nr_roti;
public:
    trotineta(const std::string &culoare = "verde", int nrRoti = 2) : culoare(culoare), nr_roti(nrRoti) {
        std::cout << "constr trotineta\n";
    }

    ~trotineta() {
        std::cout << "destr trotineta\n";
    }
};

class bicicleta {
    std::string culoare;
    int nr_roti_ajutatoare;
public:
    bicicleta(const std::string &culoare = "galben", int nrRoti = 2) : culoare(culoare), nr_roti_ajutatoare(nrRoti) {
        std::cout << "constr bicla\n";
    }

    ~bicicleta() {
        std::cout << "destr bicla\n";
    }
};

class motor {
    int cai_putere;
public:
    void run() {
        std::cout << "motor goes brr\n";
    }

    motor(int caiPutere) : cai_putere(caiPutere) {
        std::cout << "constr motor " << cai_putere << "\n";
    }

    motor(const motor& copie) : cai_putere(copie.cai_putere - 10) {
        std::cout << "cc motor\n";
    }

    ~motor() {
        std::cout << "destr motor " << cai_putere << "\n";
    }
};

class vehicul_electric {
    motor m;
    int capacitate_baterie;
    bool se_incarca;
    static int nr;
public:
    vehicul_electric(motor m = motor(50)) : m(m) {
        ++nr;
        std::cout << "constr v electric\n";
    }

    virtual ~vehicul_electric() = 0;

    static int getNr() {
        return nr;
    }
};

int vehicul_electric::nr;

vehicul_electric::~vehicul_electric() {
--nr;
std::cout << "destr v electric\n";
}

class trotineta_electrica : trotineta, public vehicul_electric {
public:
    trotineta_electrica() {
        std::cout << "constr trotineta electrica\n";
    }

    virtual ~trotineta_electrica() { {
        std::cout << "destr trotineta electrica\n";
    }
    }
};

class bicicleta_electrica : bicicleta, public vehicul_electric {
public:
    bicicleta_electrica() {}
};



int main() {
    trotineta_electrica t;
    vehicul_electric& v = t;
    std::cout << t.getNr() << "\n";
    bicicleta_electrica b;
    std::cout << v.getNr() << "\n";
//    t.~trotineta_electrica();
    {
        trotineta tr;
    }
    return 0;
}
