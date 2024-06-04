#include <bits/stdc++.h>
using namespace std;

int main (){
    double nota1, nota2, nota3, nota4, media, exame, media_final;
    cin >> nota1 >> nota2 >> nota3 >> nota4;
    media = (nota1 * 2 + nota2 * 3 + nota3 * 4 + nota4 * 1) / 10;
    cout << fixed << setprecision (1);
    cout << "Media: " << media << '\n';
    if (media < 5.0){
        cout << "Aluno reprovado.\n";
    }else if(media < 7.0){
            cout << "Aluno em exame.\n";
            cin >> exame;
            cout << "Nota do exame: " << exame << '\n';
            media_final = (exame + media) / 2;
            if (media_final >= 5.0){
                cout << "Aluno aprovado.\n";
            }else{
                cout << "Aluno reprovado.\n";
            }
            cout << "Media final: " << media_final << '\n';
        }else{
            cout << "Aluno aprovado.\n";
    }
}