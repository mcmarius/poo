#include <sstream>

#include <boost/ut.hpp>

#include "lista_simpla.h"

namespace ut = boost::ut;

ut::suite t_lista_simpla = [] {
    using namespace ut;
    using namespace std::string_literals;

    "lista goala"_test = [] {
        std::ostringstream output;
        lista_simpla lista;
        output << lista;
        expect("()\n"s == output.str());
    };

    /*auto reset = [](auto& output) {
        output.str(""s);
        output.clear();
    };*/

    // "adauga"_test = [&reset] {
    // "adauga"_test = [&] {
    "adauga"_test = [] {
        lista_simpla lista;
        std::ostringstream output;
        lista.adauga(2);
        output << lista;
        expect("(2)\n"s == output.str());

        lista_simpla l2;
        l2.adauga(2, false);
        // reset(output);
        output.str(""s);
        output.clear();
        output << l2;
        expect("(2)\n"s == output.str());

        output.str(""s);
        output.clear();
        lista.adauga(3);
        output << lista;
        expect("(3) -> (2)\n"s == output.str());

        output.str(""s);
        output.clear();
        lista.adauga(3, false);
        output << lista;
        expect("(3) -> (2) -> (3)\n"s == output.str());
    };

    "constructor de copiere"_test = [] {
        lista_simpla l1;
        l1.adauga(1);
        lista_simpla l2{l1};
        l1.adauga(3);
        l2.adauga(2);
        std::ostringstream output1;
        std::ostringstream output2;
        output1 << l1;
        output2 << l2;
        expect("(3) -> (1)\n"s == output1.str());
        expect("(2) -> (1)\n"s == output2.str());
    };

    "operator="_test = [] {
        lista_simpla l1;
        l1.adauga(1);
        lista_simpla l2;
        l2 = l1;
        l1.adauga(3);
        l2.adauga(2);
        std::ostringstream output1;
        std::ostringstream output2;
        output1 << l1;
        output2 << l2;
        expect("(3) -> (1)\n"s == output1.str());
        expect("(2) -> (1)\n"s == output2.str());
    };

    skip / "adauga_val_poz"_test = [] {
        lista_simpla l1;
        std::ostringstream output;
        l1.adauga_val_poz(1, 1);
        output << l1;
        expect("(1)\n"s == output.str());

        output.str(""s);
        output.clear();
        lista_simpla l2;
        l2.adauga_val_poz(1, 100);
        output << l2;
        expect("(1)\n"s == output.str());

        output.str(""s);
        output.clear();
        lista_simpla l3;
        l3.adauga_val_poz(1, -100);
        output << l3;
        expect("(1)\n"s == output.str());

        output.str(""s);
        output.clear();
        lista_simpla l4;
        l4.adauga_val_poz(1, 0);
        output << l4;
        expect("(1)\n"s == output.str());

        output.str(""s);
        output.clear();
        l1.adauga(0);
        l1.adauga_val_poz(2, 2);
        output << l1;
        expect("(0) -> (2) -> (1)\n"s == output.str());

        output.str(""s);
        output.clear();
        l1.adauga_val_poz(3, 1);
        output << l1;
        expect("(0) -> (3) -> (2) -> (1)\n"s == output.str());
    };

    skip / "elimina_poz"_test = [] {
        lista_simpla lista;
        std::ostringstream output;
        lista.elimina_poz(2);
        output << lista;
        expect("()\n"s == output.str());

        output.str(""s);
        output.clear();
        lista.adauga(1);
        lista.elimina_poz(0);
        output << lista;
        expect("(1)\n"s == output.str());

        output.str(""s);
        output.clear();
        lista.elimina_poz(2);
        output << lista;
        expect("(1)\n"s == output.str());

        output.str(""s);
        output.clear();
        lista.elimina_poz(1);
        output << lista;
        expect("()\n"s == output.str());

        output.str(""s);
        output.clear();
        lista.adauga(1);
        lista.adauga(2);
        lista.adauga(3);
        lista.elimina_poz(1);
        output << lista;
        expect("(2) -> (1)\n"s == output.str());

        output.str(""s);
        output.clear();
        lista.adauga(4);
        lista.elimina_poz(3);
        output << lista;
        expect("(4) -> (2)\n"s == output.str());

        output.str(""s);
        output.clear();
        lista.adauga(5);
        lista.elimina_poz(2);
        output << lista;
        expect("(5) -> (2)\n"s == output.str());
    };

    skip / "elimina_val"_test = [] {
        lista_simpla lista;
        std::ostringstream output;
        lista.elimina_val(2);
        output << lista;
        expect("()\n"s == output.str());

        output.str(""s);
        output.clear();
        lista.adauga(1);
        lista.elimina_val(0);
        output << lista;
        expect("(1)\n"s == output.str());

        output.str(""s);
        output.clear();
        lista.elimina_val(1);
        output << lista;
        expect("()\n"s == output.str());

        output.str(""s);
        output.clear();
        lista.adauga(1);
        lista.adauga(1);
        lista.elimina_val(1);
        output << lista;
        expect("()\n"s == output.str());

        output.str(""s);
        output.clear();
        lista.adauga(1);
        lista.adauga(1);
        lista.adauga(1);
        lista.elimina_val(1);
        output << lista;
        expect("()\n"s == output.str());

        output.str(""s);
        output.clear();
        lista.adauga(1);
        lista.adauga(2);
        lista.adauga(1);
        lista.elimina_val(1);
        output << lista;
        expect("(2)\n"s == output.str());

        output.str(""s);
        output.clear();
        lista.adauga(2);
        lista.adauga(2);
        lista.adauga(1);
        lista.elimina_val(1);
        output << lista;
        expect("(2) -> (2)\n"s == output.str());

        output.str(""s);
        output.clear();
        lista.adauga(1);
        lista.adauga(2);
        lista.adauga(2);
        lista.elimina_val(1);
        output << lista;
        expect("(2) -> (2)\n"s == output.str());
    };

    skip / "modifica_val_poz"_test = [] {
        lista_simpla lista;
        std::ostringstream output;
        lista.modifica_val_poz(5, 2);
        output << lista;
        expect("()\n"s == output.str());

        output.str(""s);
        output.clear();
        lista.adauga(1);
        lista.modifica_val_poz(5, 0);
        output << lista;
        expect("(1)\n"s == output.str());

        output.str(""s);
        output.clear();
        lista.modifica_val_poz(5, 1);
        output << lista;
        expect("(5)\n"s == output.str());

        output.str(""s);
        output.clear();
        lista.adauga(1);
        lista.adauga(3, false);
        lista.modifica_val_poz(4, 2);
        output << lista;
        expect("(1) -> (4) -> (3)\n"s == output.str());

        output.str(""s);
        output.clear();
        lista.modifica_val_poz(0, 3);
        output << lista;
        expect("(1) -> (4) -> (0)\n"s == output.str());
    };
};

int main() {}
