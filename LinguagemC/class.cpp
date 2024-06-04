#include <iostream>
#include <string>
using namespace std;

#define endl '\n'
#define ll long long

class Nodo{
    private:
        int n;
        class Nodo *prox;
};

class Lista{
    private:
        int tam;
        class Nodo *prime;
        class Nodo *ult;
};

class Pessoa{
    private:
        std::string nome;
        int idade;

    public:
        Pessoa() : nome(""), idade (0) {}

        Pessoa(std::string n, int i) : nome(n), idade(i) {}

        std::string getNome() const {
            return nome;
        }

        int getIdade() const{
            return idade;
        }

        void setNome(std::string n){
            nome = n;
        }

        void setIdade(int i){
            idade = i;
        }

        ~Pessoa() {
        std::cout << "Destrutor chamado!" << endl;
    }
};

int main(){
    string s;
    int n;
    Pessoa p1("João", 30);
    Pessoa *p2 = new Pessoa();

    // Acessando dados via métodos
    std::cout << "Nome: " << p1.getNome() << endl;
    std::cout << "Idade: " << p1.getIdade() << endl;

    std::cout << "Novo nome: ";
    std::cin >> s;

    std::cout << "Nova idade: ";
    std::cin >> n;

    // Modificando dados via métodos
    p2->setNome(s);
    p2->setIdade(n);

    // Acessando dados modificados via métodos
    std::cout << "Nome: " << p2->getNome() << endl;
    std::cout << "Idade: " << p2->getIdade() << endl;

    delete p2;

    return 0;  
}