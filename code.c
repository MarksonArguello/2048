//Header
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ANSI_COLOR "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define TABULEIRO 4  
#define VITORIA 2048 

void incializar(int matriz[][TABULEIRO], int cor[][TABULEIRO]);
void mostrar(int matriz[][TABULEIRO], int cor[][TABULEIRO]);
void inserir_num(int matriz[][TABULEIRO], int aleatorio, int cor[][TABULEIRO]);
int contar_vazios(int matriz[][TABULEIRO]);
int aleatorio(int vazios);
int verificar_movimento(int matriz[][TABULEIRO]);
int verificar_movimento_cima(int matriz[][TABULEIRO]);
int verificar_movimento_baixo(int matriz[][TABULEIRO]);
int verificar_movimento_esquerda(int matriz[][TABULEIRO]);
int verificar_movimento_direita(int matriz[][TABULEIRO]);
int verificar_vitoria(int matriz[][TABULEIRO]);
void mover_esquerda (int matriz[][TABULEIRO]); 
void mover_direita (int matriz[][TABULEIRO]);  
void mover_cima (int matriz[][TABULEIRO]);     
void mover_baixo (int matriz[][TABULEIRO]);    
//---------



int main(void){
    system("clear");
    //Inicialização das variáveis
    int matriz[TABULEIRO][TABULEIRO], jogo = 0;
    int cor[TABULEIRO][TABULEIRO]; 
    unsigned short vazios = 0, n, i, movimento;
    char jogada = ' ';
    srand(clock());
    //---------------------------
    
    //Menu de Inicialização
    printf("Deseja jogar?\n1 - sim\n2 - não\n");
    scanf("%d",&jogo);
    while(jogo != 2 && jogo != 1){
        printf("\nDigite apenas 1 ou 2\n");
        printf("Deseja jogar?\n1 - sim\n2 - não\n");
        scanf("%d",&jogo);
    }
    //---------------------

    incializar(matriz, cor);

    //Esvazia o buffer
    while(getchar() !=  '\n');
    
    while(jogo == 1){

        //Inserir numeros
        vazios = contar_vazios(matriz);
        if(vazios > 2){

            //Sorteia se vão ser inseridos 1 ou dois numeros
            n = (rand()%2)+1;
            for(i = 0; i < n; i++){
                inserir_num(matriz, aleatorio(vazios), cor);
            }

        //Caso exista 2 ou menos casas vazias então insere apenas 1
        }else if(vazios == 1 || vazios == 2){
            inserir_num(matriz, aleatorio(vazios), cor);
        }

        //Printa na tela o tabuleiro
        mostrar(matriz, cor);

        // Verifica se há possibilidade de movimento
        if(!verificar_movimento(matriz)){
            printf("Você perdeu\n");
            break;
        }

        //Verifica se já alcançou o número máximo(normalmente o 2048)
        if(verificar_vitoria(matriz)){
            printf("Parabéns você ganhou!!!!\n");
            break;
        }
        
        movimento = 0;
        /*
        Esse while serve pra saber se o usuário fez um movimento
        Caso tenha pedido um movimento inválido a variavel movimento recebe 0
        Caso tenha feito um movimento válido a variavel movimento recebe 1 e sai do loop
         */
        while(movimento == 0){
            //Ler a jogada
            scanf("%c", &jogada);
            while(getchar() != '\n'); // Esvazia o buffer
            while(jogada != 'w' && jogada != 'W' && jogada != 's' && jogada != 'S' && jogada != 'd' && jogada != 'D' && jogada != 'a' && jogada != 'A'){
                printf("Apenas w a s d\n");
                scanf("%c", &jogada);
                while(getchar() != '\n');//Esvazia o buffer
            }
            //-----------

            switch(jogada){
        
                case 'W':
                case 'w':
                    if(verificar_movimento_cima(matriz)){
                        mover_cima(matriz);
                        movimento = 1;
                    }else{
                        printf("Você não pode jogar para cima\n");
                    }           
                break;
                case 'A':
                case 'a':
                    if(verificar_movimento_esquerda(matriz)){
                        mover_esquerda(matriz);
                        movimento = 1;
                    }else{
                        printf("Você não pode jogar para a esquerda\n");
                    }
                break;
                case 'S':
                case 's':         
                    if(verificar_movimento_baixo(matriz)){
                        mover_baixo(matriz);
                        movimento = 1;
                    }else{
                        printf("Você não pode jogar para baixo\n");
                    }
                break;
                case 'D':
                case 'd':
                    if(verificar_movimento_direita(matriz)){
                        mover_direita(matriz);
                        movimento = 1;
                    }else{
                        printf("Você não pode jogar para a direita\n");
                    }
                break;
                default:
                break;
            }
        }
    } 


    return 0; // Fim da função main
}



// inicio das funções 
void incializar(int matriz[][TABULEIRO], int cor[][TABULEIRO]){ ////Função para incializar todos os elementos da matriz com 0
    for(int l = 0; l < TABULEIRO; l++){
        for(int c = 0; c < TABULEIRO; c++){
            matriz[l][c] = 0;
            cor[l][c] = 0;
        }
    }
}

void mostrar(int matriz[][TABULEIRO], int cor[][TABULEIRO]){ //Função para printar o tabuleiro com os numeros
    system("clear");
    printf("/------");
    for(int i = 0; i < TABULEIRO-1; i++)
        printf("|------");
    puts("\\");
    for(int l = 0; l < TABULEIRO; l++){
        for(int c = 0; c < TABULEIRO; c++){
            if(matriz[l][c] == 0) printf("|      ");// Note que não printamos o numero 0
            if(matriz[l][c] > 0 && matriz[l][c] < 10) (cor[l][c] == 0)? printf("|     %d", matriz[l][c]): printf("|" ANSI_COLOR "     %d" ANSI_COLOR_RESET "", matriz[l][c]);
            // A linha acima muda a cor dos ultimos numeros adicionados
            if(matriz[l][c] > 10 && matriz[l][c] < 100) printf("|    %d",matriz[l][c]);
            if(matriz[l][c] > 100 && matriz[l][c] < 1000) printf("|   %d",matriz[l][c]);
            if(matriz[l][c] > 1000) printf("|   %d",matriz[l][c]);
            cor[l][c] = 0;
        }
        printf("|\n");
        if(l != TABULEIRO-1 ){
            for(int i = 0; i < TABULEIRO;i++)
                printf("|------");
            printf("|\n");
        }
    }
    printf("\\------");
    for(int i = 0; i < TABULEIRO-1; i++)
        printf("|------");
    puts("/");
}

int contar_vazios(int matriz[][TABULEIRO]){//Função para contar quantas casas estao com o numero 0
    int vazios = 0;
    for(int l = 0; l < TABULEIRO; l++){
        for(int c = 0; c < TABULEIRO; c++){
            if(matriz[l][c] == 0) vazios ++; 
        } 
    }
    return vazios;   
}

void inserir_num(int matriz[][TABULEIRO], int aleatorio, int cor[][TABULEIRO]){//Função para adicionar o numero 2 numa casa aleatoria 
    for(int l = 0; l < TABULEIRO; l++){
        for(int c = 0; c < TABULEIRO; c++){
            
            if(matriz[l][c] == 0){
                if(aleatorio == 0){
                    matriz[l][c] = 2;
                    cor[l][c] = 1;
                    return ;
                }else{
                    aleatorio--;
                }
            } 
        }
    }
}

int aleatorio(int vazios){//Função retorna um número aleatório
    return rand()%vazios;
}

void mover_esquerda (int matriz[][TABULEIRO]) {//Função para mover os numeros para a esquerda
    int soma[TABULEIRO];
    for(int i = 0; i < TABULEIRO; i++) soma[i] = 0;
    for(int l = 0; l < TABULEIRO; l++){
    	for(int c = 1; c < TABULEIRO;){ 
			if(c == 0) c++;
            else if(matriz[l][c] != 0 && matriz[l][c-1] == 0){
                matriz[l][c-1] = matriz[l][c];
                matriz[l][c] = 0;
                if(soma[c] == 1){
                    soma[c] = 0;
                    soma[c-1] = 0; 
                }
                c--;
            }else if(soma[c] == 0 && soma[c-1] == 0 && matriz[l][c] != 0 && matriz[l][c] == matriz[l][c-1]){
                matriz[l][c-1] *=2;
                soma[c-1] = 1;
                matriz[l][c] = 0;
                c++;
            }else{
                c++;
            }
		}
        for(int i = 0; i < TABULEIRO; i++) soma[i] = 0;
	}
}

void mover_direita (int matriz[][TABULEIRO]) { //Função para mover os numeros para a direita
    int soma[TABULEIRO];
    for(int i = 0; i < TABULEIRO; i++) soma[i] = 0;
	for(int l = 0; l < TABULEIRO; l++){
    	for(int c = TABULEIRO-2; c >= 0;){ 
			if(c == TABULEIRO-1) c--;
            else if(matriz[l][c] != 0 && matriz[l][c+1] == 0){
                matriz[l][c+1] = matriz[l][c];
                matriz[l][c] = 0;
                if(soma[c] == 1){
                    soma[c] = 0;
                    soma[c+1] = 1;
                }
                c++;
            }else if(soma[c] == 0 && soma[c+1] == 0 && matriz[l][c] != 0 && matriz[l][c] == matriz[l][c+1]){
                matriz[l][c+1] *=2;
                matriz[l][c] = 0;
                soma[c+1] = 1;
                c--;
            }else{
                c--;    
            }
		}
        for(int i = 0; i < TABULEIRO; i++) soma[i] = 0;
	}
}

void mover_cima (int matriz[][TABULEIRO]) {//Função para mover os numeros para cima
    int soma[TABULEIRO];
    for(int i = 0; i < TABULEIRO; i++) soma[i] = 0;
    for(int c = 0; c < TABULEIRO; c++){
    	for(int l = 1; l < TABULEIRO;){ 
			if(l == 0) l++;
            else if(matriz[l][c] != 0 && matriz[l-1][c] == 0){
                matriz[l-1][c] = matriz[l][c];
                matriz[l][c] = 0;
                if(soma[l] == 1){
                    soma[l-1] = 1;
                    soma[l] = 0;
                }
                l--;
            }else if(soma[l] == 0 && soma[l-1] == 0  && matriz[l][c] != 0 && matriz[l][c] == matriz[l-1][c]){
                matriz[l-1][c] *=2;
                matriz[l][c] = 0;
                soma[l-1] = 1;
                l++;
            }else{
                l++;
            }
		
		}
        for(int i = 0; i < TABULEIRO; i++) soma[i] = 0;
	}
}

void mover_baixo (int matriz[][TABULEIRO]) { //Função para mover os numeros para baixo
    int soma[TABULEIRO];
    for(int i = 0; i < TABULEIRO; i++) soma[i] = 0;
    for(int c = 0; c < TABULEIRO; c++){
    	for(int l = TABULEIRO-2; l >= 0;){ 
			if(l == TABULEIRO-1) l--;
            else if(matriz[l][c] != 0 && matriz[l+1][c] == 0){
                matriz[l+1][c] = matriz[l][c];
                matriz[l][c] = 0;
                if(soma[l] == 1){
                    soma[l] = 0;
                    soma[l+1] = 1;
                }
                l++;
            }else if(soma[l] == 0 &&soma[l+1] == 0 && matriz[l][c] != 0 && matriz[l][c] == matriz[l+1][c]){
                matriz[l+1][c] *=2;
                matriz[l][c] = 0;
                soma[l+1] = 1;
                l--;
            }else{
                l--;    
            }
		}
        for(int i = 0; i < TABULEIRO; i++) soma[i] = 0;
	}            
}

int verificar_movimento(int matriz[][TABULEIRO]){//Função para verificar se há movimentos possiveis  OBS: so é usada quando não existem casas vazias
    for(int l = 0; l < TABULEIRO; l++){
        for(int c = 0; c < TABULEIRO; c++){
            if(c < TABULEIRO -1 && matriz[l][c] == matriz[l][c+1]) return 1;
            if(l < TABULEIRO -1 && matriz[l][c] == matriz[l+1][c]) return 1;
        }
    }
    return 0;
}

int verificar_movimento_cima(int matriz[][TABULEIRO]){//Função para verificar se e possivel mover os numeros para cima
    for(int l = 1; l < TABULEIRO; l++){
        for(int c = 0; c < TABULEIRO; c++){
            if(matriz[l][c] != 0 && (matriz[l][c] == matriz[l-1][c] || matriz[l-1][c] == 0)) return 1;
        }
    }
    return 0;
}

int verificar_movimento_baixo(int matriz[][TABULEIRO]){ //Função para verificar se e possivel mover os numeros para baixo
    for(int l = 0; l < TABULEIRO-1; l++){
        for(int c = 0; c < TABULEIRO; c++){
            if(matriz[l][c] != 0 && (matriz[l][c] == matriz[l+1][c] || matriz[l+1][c] == 0)) return 1;
        }
    }
    return 0;
}

int verificar_movimento_esquerda(int matriz[][TABULEIRO]){//Função para verificar se e possivel mover os numeros para a esquerda
    for(int l = 0; l < TABULEIRO; l++){
        for(int c = 1; c < TABULEIRO; c++){
            if(matriz[l][c] != 0 && (matriz[l][c] == matriz[l][c-1] || matriz[l][c-1] == 0)) return 1;
        }
    }
    return 0;
}

int verificar_movimento_direita(int matriz[][TABULEIRO]){ //Função para verificar se e possivel mover os numeros para a direita
    for(int l = 0; l < TABULEIRO; l++){
        for(int c = 0; c < TABULEIRO-1; c++){
            if(matriz[l][c] != 0 && (matriz[l][c] == matriz[l][c+1] || matriz[l][c+1] == 0)) return 1;
        }
    }
    return 0;
}

int verificar_vitoria(int matriz[][TABULEIRO]){ //Função para verificar se o número maximo esta na matriz
    for(int l = 0; l < TABULEIRO; l++)
        for(int c = 0; c < TABULEIRO; c++)
            if(matriz[l][c] == VITORIA) return 1;
        
    return 0;
}
