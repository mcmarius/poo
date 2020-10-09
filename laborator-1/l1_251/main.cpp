#include <iostream>

class umbrela {
protected:
    std::string culoare;
public:
    umbrela(std::string cul = "n/a") : culoare(cul) {
        std::cout << "constructor baza " << culoare << "\n";
    }

    umbrela(umbrela& u) : culoare(u.culoare + " copie") {
        std::cout << "constructor copiere baza " << u.culoare << "\n";
    }

    umbrela& operator=(const umbrela &rhs) {
        std::cout << "op= baza " << culoare << " " << rhs.culoare << "\n";
        culoare = rhs.culoare;
        return *this;
    }

    ~umbrela() {
        std::cout << "destructor baza " << culoare << "\n";
    }

    friend std::ostream &operator<<(std::ostream &os, const umbrela &umbrela) {
        os << "culoare: " << umbrela.culoare << "\n";
        return os;
    }
};

class umbrela_terasa : umbrela {
public:
    umbrela_terasa(const std::string &cul = "alba") : umbrela(cul) {
        std::cout << "constructor derivata " << "\n";
    }

    friend std::ostream &operator<<(std::ostream &os, const umbrela_terasa &terasa) {
        os << "umbrela terasa: " << static_cast<const umbrela &>(terasa);
        return os;
    }

    ~umbrela_terasa() {
        std::cout << "destructor derivata " << "\n";
    }
};

class bautura {
    int cantitate = 100;
    umbrela u;
public:
    bautura(int cantitate, umbrela& u) : cantitate(cantitate), u(u) {
        std::cout << "constructor b " << "\n";
    }

    friend std::ostream &operator<<(std::ostream &os, const bautura &bautura) {
        os << "cantitate: " << bautura.cantitate << " u: " << bautura.u;
        return os;
    }

    virtual ~bautura() {
        std::cout << "destructor b " << "\n";
    }
};

void f1() {
    umbrela u("rosie");
    {
        umbrela u2("verde");
//        u2.~umbrela();        // foarte rar
    }
    umbrela u3("albastra");
    umbrela u4(u);
    u = u3;
    std::cout << u << u3 << u4;
}

int main() {
    umbrela_terasa t("gri");
    std::cout << t;
    umbrela u("portocalie");
    bautura b(500, u);
    std::cout << b;
    return 0;
}
