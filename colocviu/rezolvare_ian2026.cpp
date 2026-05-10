/**
 * Atenție! Doar o tentativă de rezolvare, încă mai lipsesc destule (sper să le adaug... cândva).
 * Totuși, cu cele de aici ar fi nota >= 10, însă nu are punctaj maxim conform baremului.
 * Rezolvarea a fost făcută pe commit-ul din 11 mai 2026 în ~2h30m, pe baza explicațiilor (parțial eronate)
 * de pe GitHub, ocazie prin care am mai găsit erori în formularea subiectului (ups...).
 * Sper ca pe viitor (??) să încercăm să rezolvăm subiectele _înainte_ să le propunem pentru a identifica
 * de dinainte astfel de probleme (dacă tot avem AI la dispoziție.
 * Desigur, voi nu (ar trebui să) aveți acces în timpul testului).
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <queue>
#include <random>

class EroareApp : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class EroareParam : public EroareApp {
    using EroareApp::EroareApp;
};

class EroareEchipament : public EroareApp {
    using EroareApp::EroareApp;
};

class EroarePool : public EroareApp {
    using EroareApp::EroareApp;
};

class Problema;
class Echipament;
class EchipamentPool;

class GeneratorObiecte {
protected:
    EchipamentPool *pool;

public:
    explicit GeneratorObiecte(EchipamentPool *pool)
        : pool(pool) {
    }

    virtual ~GeneratorObiecte() = default;

    virtual Problema *make_problema() const = 0;

    virtual Echipament *get_echipament() const = 0;
};

class GeneratorIncalzire;


class Problema {
public:
    static const int INTERVAL = 15;

    enum class tip_prioritate { scazuta, medie, ridicata };

    double impact(int timp_curent) const {
        auto durata = get_durata(timp_curent);
        return detalii_impact(durata);
    }

    Problema(const std::string &m_nume, int m_timp_inceput, tip_prioritate m_prioritate, const GeneratorObiecte *gen)
        : m_nume(m_nume),
          m_timp_inceput(m_timp_inceput),
          m_prioritate(m_prioritate), m_generator(gen) {
    }

    virtual ~Problema() = default;

    Echipament *get_echipament() { return m_generator->get_echipament(); }

    [[nodiscard]] tip_prioritate get_prioritate() const {
        return m_prioritate;
    }

protected:
    tip_prioritate m_prioritate;

private:
    std::string m_nume;
    int m_timp_inceput;
    const GeneratorObiecte *m_generator;

    virtual double detalii_impact(int durata) const = 0;

    int get_durata(int timp_curent) const { return timp_curent - m_timp_inceput; }
};

class ProblemaIncalzire : public Problema {
public:
    ProblemaIncalzire(const std::string &m_nume, int m_timp_inceput,
                      const std::vector<int> &m_etaje, const GeneratorObiecte *gen) : Problema(m_nume, m_timp_inceput,
            tip_prioritate::medie, gen),
        m_etaje(m_etaje) {
    }

private:
    std::vector<int> m_etaje;

    double detalii_impact(int durata) const override {
        double total = 0;
        for (int i = 0; i < m_etaje.size(); i++) {
            total += m_etaje[i] * (durata - m_etaje[m_etaje.size() - i]);
        }
        return total;
    }
};

class ProblemaApa : public Problema {
public:
    ProblemaApa(const std::string &nume, int timp_inceput, int mc, const GeneratorObiecte *gen)
        : Problema(nume, timp_inceput, tip_prioritate::scazuta, gen), m_mc(mc) {
    }

private:
    double detalii_impact(int durata) const override {
        return std::pow(m_mc, durata);
    }

    int m_mc;
};

class ProblemaAer : public Problema {
public:
    ProblemaAer(const std::string &nume, int timp_inceput, int pm, int co2, const GeneratorObiecte *gen)
        : Problema(nume, timp_inceput, get_prioritate(pm, co2), gen),
          m_pm(pm),
          m_co2(co2) {
        if (m_co2 < 400) {
            throw EroareParam("CO2 trebuie sa fie >= 400, dar este" + std::to_string(m_co2));
        }
    }

private:
    int m_pm;
    int m_co2;

    static tip_prioritate get_prioritate(int pm, int co2) {
        if (pm > 30 || co2 > 2000)
            return tip_prioritate::ridicata;
        if (pm > 10 || co2 > 1000)
            return tip_prioritate::medie;
        return tip_prioritate::scazuta;
    }

    double detalii_impact(int durata) const override {
        double scor = 1;
        if (m_pm > 30)
            scor += 70;
        else if (m_pm > 10)
            scor += 16;
        if (m_co2 > 2000)
            scor += 30;
        else if (m_co2 > 1000)
            scor += 10;

        return durata * scor;
    }
};

class Echipament {
public:
    double consum() { return get_consum(); }

    virtual ~Echipament() = default;

    Echipament(double pret, const std::string &nume, const int prag)
        : m_pret(pret), m_prag(prag),
          m_nume(nume), m_id(m_id_max++) {
    }

    bool activ() const {
        return m_ind > m_prag;
    }

    virtual void pas_simulare() = 0;

protected:
    double m_pret;
    const int m_prag;
    int m_ind = 0;

private:
    std::string m_nume;
    const int m_id;
    static int m_id_max;

    virtual double get_consum() = 0;
};

int Echipament::m_id_max = 1;


class Incalzire : public Echipament {
public:
    Incalzire(double pret, const std::string &nume, int suprafata)
        : Echipament(pret, nume, 100),
          m_suprafata(suprafata) {
    }

    void pas_simulare() override {
        m_ind += std::rand() % 30;
    }

private:
    int m_suprafata;

    double get_consum() override {
        return m_suprafata * m_pret;
    }
};


class Pompa : public Echipament {
public:
    Pompa(double pret, const std::string &nume, int interval_metrou)
        : Echipament(pret, nume, 200),
          m_interval_metrou(interval_metrou) {
    }

    void pas_simulare() override {
        m_ind += std::rand() % 50;
    }

private:
    int m_interval_metrou;

    double get_consum() override {
        return 1000 / m_interval_metrou;
    }
};

class Purificator : public Echipament {
public:
    Purificator(double pret, const std::string &nume)
        : Echipament(pret, nume, 150) {
        m_utilizari = 0;
    }

    void pas_simulare() override {
        m_ind += std::rand() % 40;
    }

private:
    int m_utilizari;

    double get_consum() override {
        if (m_utilizari % 7 == 6)
            throw EroareEchipament("Defectiune purificator");
        return 100;
    }
};

class HVAC : public Echipament {
public:
    HVAC(double pret, const std::string &nume)
        : Echipament(pret, nume, 1000) {
    }

    void pas_simulare() override {
        m_ind += std::rand() % 100;
    }

private:
    double get_consum() override {
        return 10000;
    }
};


class EchipamentPool {
    std::vector<Echipament *> m_echipamente{
        new Incalzire(100, "incalzire pardoseala", 100),
        new Pompa(200, "pompa", 10),
        new Purificator(300, "purificator"),
        new HVAC(1000, "hvac")
    };

public:
    EchipamentPool() = default;

    Echipament *echipament_dupa_tip(const std::type_info &tip) {
        for (Echipament *ech: m_echipamente) {
            if (tip == typeid(*ech) && !ech->activ()) {
                return ech;
            }
        }
        throw EroarePool("nu exista echipamente disponibile");
    }

    EchipamentPool(const EchipamentPool &other) = delete;

    EchipamentPool(EchipamentPool &&other) noexcept = default;

    EchipamentPool &operator=(const EchipamentPool &other) = delete;

    EchipamentPool &operator=(EchipamentPool &&other) noexcept = default;

    ~EchipamentPool() {
        for (Echipament *ech: m_echipamente) {
            delete ech;
        }
    }
};

template<typename TipEchipament>
class GeneratorObiecteEch : public GeneratorObiecte {
public:
    Echipament *get_echipament() const override {
        // arunca EroarePool daca nu avem obiect disponibil
        return pool->echipament_dupa_tip(typeid(TipEchipament));
    }

    explicit GeneratorObiecteEch(EchipamentPool *pool)
        : GeneratorObiecte(pool) {
    }
};

class GeneratorIncalzire : public GeneratorObiecteEch<Incalzire> {
public:
    explicit GeneratorIncalzire(EchipamentPool *pool)
        : GeneratorObiecteEch(pool) {
    }

    Problema *make_problema() const override {
        std::vector<int> etaje;
        int max_etaje = std::rand() % 10 + 1;
        int timp = std::rand() % (24 * 60);
        for (int i = 0; i < max_etaje; i++)
            etaje.push_back(std::rand() % 10 + (etaje.empty() ? 1 : etaje[i - 1]) + 1);
        return new ProblemaIncalzire("avarie caldura", timp, etaje, this);
    }
};

class GeneratorApa : public GeneratorObiecteEch<Pompa> {
public:
    explicit GeneratorApa(EchipamentPool *pool)
        : GeneratorObiecteEch(pool) {
    }

    Problema *make_problema() const override {
        int timp = std::rand() % (24 * 60);
        int mc = std::rand() % 10 + 5;
        return new ProblemaApa("avarie apa", timp, mc, this);
    }
};

class GeneratorAer : public GeneratorObiecteEch<Purificator> {
public:
    explicit GeneratorAer(EchipamentPool *pool)
        : GeneratorObiecteEch(pool) {
    }

    Problema *make_problema() const override {
        int timp = std::rand() % (24 * 60);
        int pm = std::rand() % 100;
        int co2 = std::rand() % 3000 + 390;
        return new ProblemaAer("aer rau", timp, pm, co2, this);
    }
};

class CmpProbleme {
public:
    bool operator()(const Problema *p1, const Problema *p2) const {
        return p1->get_prioritate() > p2->get_prioritate();
    }
};

class Simulator {
    EchipamentPool pool;
    std::priority_queue<Problema *, std::vector<Problema *>, CmpProbleme> probleme;

public:
    void simuleaza() {
        auto generatori = std::vector<std::shared_ptr<GeneratorObiecte> >({
                std::make_shared<GeneratorIncalzire>(&pool),
                std::make_shared<GeneratorApa>(&pool),
                std::make_shared<GeneratorAer>(&pool)
            }
        );

        // din acest punct nu ne mai referim pe nicăieri la vreo derivată concretă
        // lucrăm doar cu interfețele claselor de bază
        for (auto generator: generatori) {
            if (rand() % 2 == 0) {
                probleme.push(generator->make_problema());
            }
        }

        // mai încolo când avem de rezolvat problemele
        double consum = 0;
        for (int timp = 0; timp < 24 * 60; timp += Problema::INTERVAL) {
            try {
                auto problema = probleme.top();
                auto impact = problema->impact(timp);
                std::cout << "rezolvare problema cu impact: " << impact << "\n";
                auto echipament = problema->get_echipament();
                echipament->pas_simulare();
                if (echipament->activ()) {
                    // folosește echipament în simulare
                    consum += echipament->consum();
                }
            } catch (const EroareEchipament &err) {
                // consumul este 0
            } catch (const EroarePool &err) {
                std::cout << err.what() << "\n";
            }
        }
    }
};

int main() {
    Simulator sim;
    sim.simuleaza();
}
