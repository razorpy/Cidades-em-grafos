#include <iostream>

using namespace std;

int matriz[10000][10000];

void quantEstradas (int x, int cid){
    int saem = 0, chegam = 0;
    for (int i = 0; i < x; ++i){
        if (matriz[i][cid]) chegam++;
        if (matriz[cid][i]) saem++;
    }
    cout << chegam << " estradas chegam a " << cid << endl
         << saem   << " estradam saem de "  << cid << endl;
}

void maxNumEstradasQueSaem (int x){
    int cids[x];
    for (int i = 0; i < x; ++i){
        int a = 0;
        for (int j = 0; j < x; ++j){
            a += matriz[i][j];
        }
        cids[i] = a;
    }
    int maior = 0;
    for (int i = 1; i < x; ++i){
        if (cids[i] > cids[maior]){
            maior = i;
        }
    }
    cout << "A cidade " << maior << " possui o maior numero de estradas que saem: " << cids[maior] << " estradas.\n";
}

bool haLigacao (int x, int cid){
    bool flag = 1;
    for (int i = 0; i < x; ++i){
        if (matriz[i][cid] and matriz[cid][i] and cid != i){
            cout << "Ha ligacao de ida e volta entre " << i << " e " << cid << endl; 
        }else if (cid != i) flag = 0;
    }
    return flag;
}

bool seqPossivel (int m, int x, int seq[]){
    bool flag = 1;
    for (int i = 0; i < m-1; ++i){
        if (matriz[seq[i]][seq[i+1]] == 0){flag = 0; break;}
    }return flag;
}


void busca(int x, int y, int *vis, int n){
    vis[x] = 1;
    for (int i = 0; i < n; ++i){
        if (matriz[x][i] == 1 and vis[i] == 0){
            vis[i] = 1;
            if (i == y) return;
            busca(i, y, vis, n);
        }
    }return;
}

int main () {
    int n;
    cout << "Digite o numero de cidades: "; cin >> n;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (j == i) matriz[i][j] = 0; 
            else{
                cout << "Ha caminho de " << i << " para " << j << "? (1 - Sim, 0 - Nao) "; cin >> matriz[i][j];  
            }
        }
    }
    while (true){
        int escolha;
        while (true){
            cout<< "O que deseja fazer?\n"
                << "1 - Determinar quantas estradas saem e chegam a tal cidade\n"
                << "2 - Determinar qual cidade possui o maior numero de estradas que saem da mesma\n"
                << "3 - Determinar se ha ligacao de uma cidade a todas as outras\n"
                << "4 - Verificar se existe caminho entre determinadas cidades\n"
                << "5 - Verificar se eh possivel ir de uma cidade para outra\n"
                << "6 - Sair do programa\n";
            cin >> escolha;
            if (escolha == 1){
                int cid;
                cout << "Digite a cidade: "; cin >> cid;
                quantEstradas(n, cid);
            }else if (escolha == 2){
                maxNumEstradasQueSaem(n);
            }else if (escolha == 3){
                int cid;
                cout << "Digite a cidade: "; cin >> cid;
                bool f = haLigacao(n, cid);
                cout << "A cidade " << cid;
                if (f) cout << " possui ligacao de ida e volta com todas as outras\n";
                else   cout << " nao possui ligacao de ida e volta com as outras\n";
            }else if (escolha == 4){
                int m; bool repete = 0;
                do{
                    repete = 0;
                    cout << "Digite quantas cidades deseja verificar: "; cin >> m;
                    int cidss[m];
                    cout << "Digite uma sequencia de cidades: ";
                    for (int i = 0; i < m; ++i){
                        cin >> cidss[i];
                        if (cidss[i] >= n){
                            cout << "Entrada Invalida!\n";
                            repete = 1; break;
                        }
                    }
                    if (repete == 0){
                        bool f = seqPossivel(m, n, cidss);
                        cout << "O caminho ";
                        if (f) cout << "pode acontecer\n";
                        else   cout << "nao pode acontecer\n";
                        break;
                    }else continue;
                }while (true);
            }else if (escolha == 5){
                int visitado[n], cid1, cid2;
                for (int i = 0; i < n; ++i){
                    visitado[i] = 0; 
                }
                cout << "Digite a cidade de partida e a de chegada: "; cin >> cid1 >> cid2;
                busca(cid1, cid2, visitado, n);
                if (visitado[cid2]) cout << "eh possivel ir de ";
                else                cout << "nao eh possivel ir de ";
                                    cout << cid1 << " a " << cid2 << endl;
            }

            else return 0;
        }
    }
}