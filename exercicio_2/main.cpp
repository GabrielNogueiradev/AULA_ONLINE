#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 1. CLASSE ABSTRATA 

class Personagem {
protected:
    int vida;
    string nome;

public:
    Personagem(string n, int v) : nome(n), vida(v) {}
    virtual ~Personagem() {}

    virtual void receberDano(int dano) = 0;
    virtual void causarDano(Personagem* alvo, int dano) = 0;
    
    virtual string getEquipe() const = 0;
    
    string getNome() const { return nome; }
    int getVida() const { return vida; }
};

// 2. CLASSES BASE: JOGADOR E INIMIGO

class Jogador : public Personagem {
public:
    Jogador(string n, int v) : Personagem(n, v) {}

    string getEquipe() const override { return "JOGADOR"; }

    // Só causa dano se o alvo for de outra equipe
    void causarDano(Personagem* alvo, int dano) override {
        if (alvo->getEquipe() == "INIMIGO") {
            cout << "[Ataque] " << nome << " ataca " << alvo->getNome() << "!\n";
            alvo->receberDano(dano);
        } else {
            cout << "[Aviso] " << nome << " nao pode atacar aliados da equipe " << alvo->getEquipe() << ".\n";
        }
    }

    void receberDano(int dano) override {
        vida -= dano;
        if (vida < 0) vida = 0;
        cout << "[Dano] " << nome << " recebeu " << dano << " de dano. Vida: " << vida << "\n";
    }
};

class Inimigo : public Personagem {
public:
    Inimigo(string n, int v) : Personagem(n, v) {}

    string getEquipe() const override { return "INIMIGO"; }

    // Só causa dano se o alvo for um Jogador
    void causarDano(Personagem* alvo, int dano) override {
        if (alvo->getEquipe() == "JOGADOR") {
            cout << "[Emboscada] O inimigo " << nome << " golpeia " << alvo->getNome() << "!\n";
            alvo->receberDano(dano);
        } else {
            cout << "[Inimigo] " << nome << " ignora o aliado " << alvo->getNome() << ".\n";
        }
    }

    void receberDano(int dano) override {
        vida -= dano;
        cout << "[Inimigo] " << nome << " foi atingido! Vida restante: " << vida << "\n";
    }
};

// 3. CLASSES ESPECIALIZADAS (JOGADOR)
=

class Guerreiro : public Jogador {
private:
    int armadura;
public:
    Guerreiro(string n, int v, int a) : Jogador(n, v), armadura(a) {}

    // Modifica como recebe dano
    void receberDano(int dano) override {
        int danoFinal = dano - armadura;
        if (danoFinal < 0) danoFinal = 0;
        cout << "Bloqueio de " << armadura << " pela armadura.\n";
        Jogador::receberDano(danoFinal);
    }
};

class Assassino : public Jogador {
public:
    Assassino(string n, int v) : Jogador(n, v) {}

    // Modifica como causa dano
    void causarDano(Personagem* alvo, int dano) override {
        cout << "Brutal! O Assassino foca nos pontos vitais.\n";
        Jogador::causarDano(alvo, dano * 2);
    }
};


int main() {
    Personagem* heroi = new Guerreiro("Arthur", 100, 20);
    Personagem* aliado = new Jogador("Maria", 80);
    Personagem* boss = new Inimigo("Orc Rei", 200);

    // Teste Jogador x Inimigo
    heroi->causarDano(boss, 30);
    
    cout << "\n";

    // Teste Inimigo x Jogador 
    boss->causarDano(heroi, 50);

    cout << "\n";

    // Teste Amizade
    heroi->causarDano(aliado, 10);

    delete heroi; 
    delete aliado; 
    delete boss;
    return 0;
}