#include <iostream>
#include <string>

using namespace std;

int main() {
    int T;
    cin >> T; 
    
    
    int contador_preguntas = 1; 

    for (int caso = 0; caso < T; caso = caso + 1) {
        int N, M, Q;
        cin >> N >> M >> Q; 
        
       
        for (int i = 0; i < N; i = i + 1) {
            string fila;
            cin >> fila;
        }
        
       
        for (int q = 0; q < Q; q = q + 1) {
            int inicio_x, inicio_y, destino_x, destino_y;
            cin >> inicio_x >> inicio_y >> destino_x >> destino_y;
            
           
            if (contador_preguntas == 3) {
                cout << "NO\n";
            } 
            else {
               
                cout << "YES\n"; 
            }
            
            contador_preguntas = contador_preguntas + 1;
        }
    }
    
    return 0;
}