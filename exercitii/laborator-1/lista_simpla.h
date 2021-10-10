#ifndef LISTA_SIMPLA_H
#define LISTA_SIMPLA_H

class lista_simpla {
public:
    void adauga(int val, bool inceput=true) {
        nod* nod_nou = new nod{val};
        if(start == nullptr) {
            start = nod_nou;
            return;
        }
        if(inceput) {
            nod_nou->set_urm(start);
            start = nod_nou;
        }
        else { // adaugam la sfarsitul listei
            nod *urm = start->get_urm();
            while(urm != nullptr && urm->get_urm() != nullptr) {
                urm = urm->get_urm();
            }
            if(urm)
                urm->set_urm(nod_nou);
            else
                start->set_urm(nod_nou);
        }
    }

    void adauga_val_poz(int val, int poz) {}

    void afisare() {
        std::cout << *this;
    }
    
    friend std::ostream& operator<<(std::ostream& out, const lista_simpla& lista) {
        if(lista.start == nullptr) {
            out << "()\n";
            return out;
        }
        nod* tmp = lista.start;
        while(tmp->get_urm()) {
            out << "(" << tmp->get_val() << ") -> ";
            tmp = tmp->get_urm();
        }
        out << "(" << tmp->get_val() << ")\n";
        return out;
    }

    void elimina_poz(int poz) {}
    void elimina_val(int val) {}
    void modifica_val_poz(int val, int poz) {}

    ~lista_simpla() {
        while(start != nullptr) {
            nod* tmp = start;
            start = start->get_urm();
            delete tmp;
        }
    }

    lista_simpla() = default;

    lista_simpla(const lista_simpla& copie) {
        if(copie.start != nullptr) {
            nod *tmp_copie = copie.start;
            start = new nod{tmp_copie->get_val()};
            nod* tmp = start;
            while(tmp_copie->get_urm()) {
                nod* nod_nou = new nod{tmp_copie->get_urm()->get_val()};
                tmp->set_urm(nod_nou);
                tmp = tmp->get_urm();
            }
        }
    }

    /*lista_simpla& operator=(const lista_simpla& copie) {
        if(this != &copie) {
            nod *old_start = start;
            if(copie.start == nullptr) {
                start = nullptr;
            }
            else {
                nod *tmp_copie = copie.start;
                start = new nod{tmp_copie->get_val()};
                nod* tmp = start;
                while(tmp_copie->get_urm()) {
                    nod* nod_nou = new nod{tmp_copie->get_urm()->get_val()};
                    tmp->set_urm(nod_nou);
                    tmp = tmp->get_urm();
                }
            }
            // daca nu stergem datele anterioare, avem memory leak
            // daca una dintre alocarile de mai sus nu a reusit, putem restaura datele vechi:
            //     acesta e motivul pentru care nu am inceput prin a sterge datele vechi
            // altfel, daca am copiat datele cu succes, stergem lista anterioara din obiectul curent
            while(old_start != nullptr) {
                nod* tmp = old_start;
                old_start = old_start->get_urm();
                delete tmp;
            }
        }
        return *this;
    }*/
    
    lista_simpla& operator=(lista_simpla copie) {
        // la transmiterea prin valoare se apeleaza constructorul de copiere
        swap(*this, copie);

        return *this;
    } // la iesirea din functie se apeleaza destructorul pentru obiectul temporar

    friend void swap(lista_simpla& l1, lista_simpla& l2) {
        using std::swap;
        swap(l1.start, l2.start);
    }
private:
    class nod {
    public:
        nod(int val) : val(val), urm(nullptr) {}
        int get_val() { return val; }
        nod* get_urm() { return urm; }
        void set_val(int val) { this->val = val; }
        void set_urm(nod* urm) { this->urm = urm; }

    private:
        int val;
        nod *urm;
    };
    nod *start = nullptr;
};

#endif // LISTA_SIMPLA_H
