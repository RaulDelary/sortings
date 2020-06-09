#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
//#include "ansi-color-codes.h"

#define HRED "\e[0;91m"
#define HGRN "\e[0;92m"
#define HMAG "\e[0;95m"
#define HBLE "\e[38;5;21m"
#define HCYN "\e[38;5;45m"
#define HPUR "\e[38;5;55m"
#define reset "\e[0m"

long int * alocar_vetor (long int tamanho, int opt);
void mostrar_vetor_C (long int * vetor, long int tamanho);
void mostrar_vetor (long int * vetor, long int tamanho);
void bubble_sort (long int * vetor, long int tamanho);
void insertion_sort (long int * vetor, long int tamanho);
void selection_sort (long int * vetor, long int tamanho);
void merge_sort (long int * vetor, long int inicio, long int fim);
void merge (long int * vetor, long int inicio, long int meio, long int fim);
void quick_sort (long int * vetor, long int esq, long int dir);
void mostrar_tabela_final (float temposA [], float temposB [], float temposC []);
void get_times (float tempos []);
void criar_output (FILE * file, float * times, char * type, long int tam);

int main () {
    
    printf (HRED" ____      _   _   _ _       ____  _____ _        _    ______   __\n"
            "|  _ \\    / \\ | | | | |     |  _ \\| ____| |      / \\  |  _ \\ \\ / /\n"
            "| |_) |  / _ \\| | | | |     | | | |  _| | |     / _ \\ | |_) \\ V / \n"
            "|  _ <  / ___ \\ |_| | |___  | |_| | |___| |___ / ___ \\|  _ < | |  \n"
            "|_| \\_\\/_/   \\_\\___/|_____| |____/|_____|_____/_/   \\_\\_| \\_\\|_|  \n\n"reset);
    
    long int * vetorA, * vetorB, * vetorC;
    long int tamA, tamB, tamC, i;
    float temposA [8], temposB [8], temposC [8]; //os vetores de tempo guardam o tempos de exec dos 5 altoritmos nas poicoes de 0 a 4
    double start, end;                           //guardam a soma desses tempos na posicao 5, guarda o maior tempo na posicao 6 e o menor na posicao 7

    //Opções para alocação do vetor:
    // alocar_vetor (int tamanho, int opt);
    //  valores de opt:
    //  Vetor A = 1 - Totalmente desordenado
    //  Vetor B = 2 - Vetor ordenado
    //  Vetor C = 3 - Vetor com apenas 1 item desordenado
    printf ("Este programa tem o objetivo de medir o tempo de algoritmos de ordenação\nem deferentes vetores, com tamanho informado pelo usuário.\n\n");
    printf ("O ["HBLE"Vetor A"reset"] será um vetor totalmente desordenado, com valores em posições aleatórias.\n");
    printf ("O ["HCYN"Vetor B"reset"] será um vetor ordenado.\n");
    printf ("O ["HPUR"Vetor C"reset"] será um vetor parcialmente ordenado, com apenas 1 valor fora de posição.\n\n");
    printf ("["HMAG"info"reset"] A cada vez que este programa é executado, o arquivo de saída \"output\" é populado com os dados da execução desse programa.\n");
    printf ("["HMAG"info"reset"] Esses dados serão usados por um script em Python para plotagem do gráfico comparativo de tempos.\n\n");
    printf ("Informe o tamanho do vetor A: ");
    scanf ("%ld", &tamA);
    printf ("Informe o tamanho do vetor B: ");
    scanf ("%ld", &tamB);
    printf ("Informe o tamanho do vetor C: ");
    scanf ("%ld", &tamC);
    printf ("\n==== ["HGRN"Tempo de Alocação e Preenchimento"reset"] ====\n");
    
    //inicia a alocação dos vetores A, B e C
    start = omp_get_wtime ();               //recebe tempo antes da alocação
    vetorA = alocar_vetor (tamA, 1);
    end = omp_get_wtime ();                 //recebe tempo depois da alocação
    printf ("Vetor A: %f sec\n", end - start);  //imprime a diferença de tempo
    
    start = omp_get_wtime ();
    vetorB = alocar_vetor (tamB, 2);
    end = omp_get_wtime ();
    printf ("Vetor B: %f sec\n", end - start);

    start = omp_get_wtime ();
    vetorC = alocar_vetor (tamC, 3);
    end = omp_get_wtime ();
    printf ("Vetor C: %f sec\n", end - start);
    printf ("=============================================\n\n");
    printf ("["HMAG"info"reset"] Criando cópia dos vetores...\n");

    //Criando cópia dos vetores para serem ordenados por todas os sorts.
    //Cada vetor será ordenado por todos os sorts
    //Ex.: o vetor A será ordenado pelo bubble, insertion, selection, merge e quick
    //E assim acontecerá também para o vetor B e vetor C
    start = omp_get_wtime (); //medindo tempo para copiar todos os vetores
    long int *  vetA_sorted_by_bubble = (long int *) malloc (sizeof (long int ) * tamA);
    long int *  vetA_sorted_by_insertion = (long int *) malloc (sizeof (long int) * tamA);
    long int *  vetA_sorted_by_selection = (long int *) malloc (sizeof (long int) * tamA);
    long int *  vetA_sorted_by_merge = (long int *) malloc (sizeof (long int) * tamA);
    long int *  vetA_sorted_by_quick = (long int *) malloc (sizeof (long int) * tamA);
    
    long int *  vetB_sorted_by_bubble = (long int *) malloc (sizeof (long int) * tamB);
    long int *  vetB_sorted_by_insertion = (long int *) malloc (sizeof (long int) * tamB);
    long int *  vetB_sorted_by_selection = (long int *) malloc (sizeof (long int) * tamB);
    long int *  vetB_sorted_by_merge = (long int *) malloc (sizeof (long int) * tamB);
    long int *  vetB_sorted_by_quick = (long int *) malloc (sizeof (long int) * tamB);
    
    long int *  vetC_sorted_by_bubble = (long int *) malloc (sizeof (long int) * tamC);
    long int *  vetC_sorted_by_insertion = (long int *) malloc (sizeof (long int) * tamC);
    long int *  vetC_sorted_by_selection = (long int *) malloc (sizeof (long int) * tamC);
    long int *  vetC_sorted_by_merge = (long int *) malloc (sizeof (long int) * tamC);
    long int *  vetC_sorted_by_quick = (long int *) malloc (sizeof (long int) * tamC);

    for (i = 0; i < tamA; i ++) {
        vetA_sorted_by_bubble [i] = vetorA [i];
        vetA_sorted_by_insertion [i] = vetorA [i];
        vetA_sorted_by_selection [i] = vetorA [i];
        vetA_sorted_by_merge [i] = vetorA [i];
        vetA_sorted_by_quick [i] = vetorA [i];
    }

    for (i = 0; i < tamB; i ++) {
        vetB_sorted_by_bubble [i] = vetorB [i];
        vetB_sorted_by_insertion [i] = vetorB [i];
        vetB_sorted_by_selection [i] = vetorB [i];
        vetB_sorted_by_merge [i] = vetorB [i];
        vetB_sorted_by_quick [i] = vetorB [i];
    }

    for (i = 0; i < tamC; i ++) {
        vetC_sorted_by_bubble [i] = vetorC [i];
        vetC_sorted_by_insertion [i] = vetorC [i];
        vetC_sorted_by_selection [i] = vetorC [i];
        vetC_sorted_by_merge [i] = vetorC [i];
        vetC_sorted_by_quick [i] = vetorC [i];
    }

    //serão feitas 5 cópias de cada vetor
    end = omp_get_wtime (); //medindo tempo para copiar todos os vetores
    printf ("["HMAG"info"reset"] Tempo para cópia dos vetores: %f sec\n", end - start);

    printf ("["HMAG"info"reset"] Aplicando algoritmos de ordenação...\n");
    printf ("["HRED"warning"reset"] Esse processo pode demorar dependendo do tamanho do vetor, do algoritmo utilizado e do seu computador. Por favor, aguarde...\n");
    
    //aplicando os algoritmos de ordenação em cada vetor e guardando o tempo nos vetores.

    //VETOR A
    start = omp_get_wtime ();
    bubble_sort (vetA_sorted_by_bubble, tamA);
    end = omp_get_wtime ();
    temposA [0] = end - start;
    printf ("["HGRN"success"reset"] ("HBLE"Vetor A"reset") Bubble Sort: \t%f sec\n", temposA [0]);

    start = omp_get_wtime ();
    insertion_sort (vetA_sorted_by_insertion, tamA);
    end = omp_get_wtime ();
    temposA [1] = end - start;
    printf ("["HGRN"success"reset"] ("HBLE"Vetor A"reset") Insertion Sort: \t%f sec\n", temposA [1]);

    start = omp_get_wtime ();
    selection_sort (vetA_sorted_by_selection, tamA);
    end = omp_get_wtime ();
    temposA [2] = end - start;
    printf ("["HGRN"success"reset"] ("HBLE"Vetor A"reset") Selection Sort: \t%f sec\n", temposA [2]);
    
    start = omp_get_wtime ();
    merge_sort (vetA_sorted_by_merge, 0, tamA - 1);
    end = omp_get_wtime ();
    temposA [3] = end - start;
    printf ("["HGRN"success"reset"] ("HBLE"Vetor A"reset") Merge Sort: \t%f sec\n", temposA [3]);

    start = omp_get_wtime ();
    quick_sort (vetA_sorted_by_quick, 0, tamA - 1);
    end = omp_get_wtime ();
    temposA [4] = end - start;
    printf ("["HGRN"success"reset"] ("HBLE"Vetor A"reset") Quick Sort: \t%f sec\n", temposA [4]);
    
    //preenchendo agora as informacoes de soma dos tempos, valor maior [6] e menor [7]
    for (i = 0; i < 5; i ++) {
        if (i == 0) {
            temposA [6] = temposA [0]; 
            temposA [7] = temposA [0];
        }
        if (temposA [i] > temposA [6]) {
            temposA [6] = temposA [i];
        }
        if (temposA [i] < temposA [7]) {
            temposA [7] = temposA [i];
        }
        temposA [5] += temposA [i];
    }

    //FIM VETOR A
    
    //VETOR B
    start = omp_get_wtime ();
    bubble_sort (vetB_sorted_by_bubble, tamB);
    end = omp_get_wtime ();
    temposB [0] = end - start;
    printf ("["HGRN"success"reset"] ("HCYN"Vetor B"reset") Bubble Sort: \t%f sec\n", temposB [0]);

    start = omp_get_wtime ();
    insertion_sort (vetB_sorted_by_insertion, tamB);
    end = omp_get_wtime ();
    temposB [1] = end - start;
    printf ("["HGRN"success"reset"] ("HCYN"Vetor B"reset") Insertion Sort: \t%f sec\n", temposB [1]);

    start = omp_get_wtime ();
    selection_sort (vetB_sorted_by_selection, tamB);
    end = omp_get_wtime ();
    temposB [2] = end - start;
    printf ("["HGRN"success"reset"] ("HCYN"Vetor B"reset") Selection Sort: \t%f sec\n", temposB [2]);
    
    start = omp_get_wtime ();
    merge_sort (vetB_sorted_by_merge, 0, tamB - 1);
    end = omp_get_wtime ();
    temposB [3] = end - start;
    printf ("["HGRN"success"reset"] ("HCYN"Vetor B"reset") Merge Sort: \t%f sec\n", temposB [3]);

    start = omp_get_wtime ();
    quick_sort (vetB_sorted_by_quick, 0, tamB - 1);
    end = omp_get_wtime ();
    temposB [4] = end - start;
    printf ("["HGRN"success"reset"] ("HCYN"Vetor B"reset") Quick Sort: \t%f sec\n", temposB [4]);
    
    for (i = 0; i < 5; i ++) {
        if (i == 0) {
            temposB [6] = temposB [0]; 
            temposB [7] = temposB [0];
        }
        if (temposB [i] > temposB [6]) {
            temposB [6] = temposB [i];
        }
        if (temposB [i] < temposB [7]) {
            temposB [7] = temposB [i];
        }
        temposB [5] += temposB [i];
    }
    //FIM VETOR B

    //VETOR C
    start = omp_get_wtime ();
    bubble_sort (vetC_sorted_by_bubble, tamC);
    end = omp_get_wtime ();
    temposC [0] = end - start;
    printf ("["HGRN"success"reset"] ("HPUR"Vetor C"reset") Bubble Sort: \t%f sec\n", temposC [0]);

    start = omp_get_wtime ();
    insertion_sort (vetC_sorted_by_insertion, tamC);
    end = omp_get_wtime ();
    temposC [1] = end - start;
    printf ("["HGRN"success"reset"] ("HPUR"Vetor C"reset") Insertion Sort: \t%f sec\n", temposC [1]);

    start = omp_get_wtime ();
    selection_sort (vetC_sorted_by_selection, tamC);
    end = omp_get_wtime ();
    temposC [2] = end - start;
    printf ("["HGRN"success"reset"] ("HPUR"Vetor C"reset") Selection Sort: \t%f sec\n", temposC [2]);
    
    start = omp_get_wtime ();
    merge_sort (vetC_sorted_by_merge, 0, tamC - 1);
    end = omp_get_wtime ();
    temposC [3] = end - start;
    printf ("["HGRN"success"reset"] ("HPUR"Vetor C"reset") Merge Sort: \t%f sec\n", temposC [3]);

    start = omp_get_wtime ();
    quick_sort (vetC_sorted_by_quick, 0, tamC - 1);
    end = omp_get_wtime ();
    temposC [4] = end - start;
    printf ("["HGRN"success"reset"] ("HPUR"Vetor C"reset") Quick Sort: \t%f sec\n", temposC [4]);
    
    for (i = 0; i < 5; i ++) {
        if (i == 0) {
            temposC [6] = temposC [0]; 
            temposC [7] = temposC [0];
        }
        if (temposC [i] > temposC [6]) {
            temposC [6] = temposC [i];
        }
        if (temposC [i] < temposC [7]) {
            temposC [7] = temposC [i];
        }
        temposC [5] += temposC [i];
    }
    //FIM VETOR C

    printf ("["HMAG"info"reset"] Ordenação dos vetores finalizada.\n");
    printf ("["HMAG"info"reset"] Tabela Final:\n");
    
    //mostra uma tabela para melhor visualização dos tempos e algoritmos.
    mostrar_tabela_final (temposA, temposB, temposC);

    //abre o arquivo de output que será usado depois para criação dos gráficos comparativos
    //o arquivo está no formato CSV, e os dados estão sendo inserido também dessa forma.
    FILE * file = fopen ("output.csv", "a");

    //coloca os dados dentro do arquivo
    if (file) {
        criar_output (file, temposA, "desordenado", tamA);
        criar_output (file, temposB, "ordenado", tamB);
        criar_output (file, temposC, "parcialmente desordenado", tamC);
        fclose (file);
        printf ("["HMAG"info"reset"] Arquivo de output gerado...\n");
    } else {
        printf ("["HRED"warning"reset"] O programa não conseguiu gerar o JSON de output, verifique as permissões do programa...\n");
        fclose (file);
    }

    //perguna se deseja mostrar os vetores
    do {
        printf ("["HMAG"info"reset"] Deseja mostrar os vetores? [1 - Sim/0 - Nao]: ");
        scanf ("%ld", &i);

        if (i != 1 && i != 0) {
            printf ("["HRED"warning"reset"] Opção inválida!\n");
        }
    } while (i != 1 && i != 0);

    //mostra os vetores caso o usuário deseje
    if (i) {
        printf ("["HMAG"info"reset"] Mostrando "HBLE"Vetor A"reset" ORIGINAL:\n");
        mostrar_vetor (vetorA, tamA);
        printf ("["HMAG"info"reset"] Mostrando "HBLE"Vetor A"reset" ORDENADO:\n");
        mostrar_vetor (vetA_sorted_by_quick, tamA);
        printf ("["HMAG"info"reset"] Mostrando "HCYN"Vetor B"reset" ORIGINAL:\n");
        mostrar_vetor (vetorB, tamB);
        printf ("["HMAG"info"reset"] Mostrando "HCYN"Vetor B"reset" ORDENADO:\n");
        mostrar_vetor (vetB_sorted_by_quick, tamB);
        printf ("["HMAG"info"reset"] Mostrando "HPUR"Vetor C"reset" ORIGINAL:\n");
        mostrar_vetor_C (vetorC, tamC);
        printf ("["HMAG"info"reset"] Mostrando "HPUR"Vetor C"reset" ORDENADO:\n");
        mostrar_vetor (vetC_sorted_by_quick, tamC);
    }

    printf ("["HMAG"info"reset"] Para visualizar o gráfico comparativo do tempo em relação ao tamanho do vetor, execute o arquivo em Python\n");
    printf ("["HMAG"info"reset"] Finalizando programa...\n");

    return 0;
}

long int * alocar_vetor (long int tamanho, int opt) {
    //Os possíveis valores de OPT estão descritos na primeira chamada da função.
    long int * novo_vetor = (long int *) malloc (sizeof (long int) * tamanho);
    long int aux, index_aux;

    for (long int i = 0; i < tamanho; i ++) {
        novo_vetor [i] = i + 1;
    }

    switch (opt) {
        case 1:
            srand (time (NULL));

            for (long int i = 0; i < tamanho; i ++) {
                index_aux = rand () % tamanho;              //rand () % tamanho significa que a variavel sempre terá um número no range do tamanho do vetor, o módulo garante isso.
                aux = novo_vetor [i];                       //aux segura o meu valor no indice atual;
                novo_vetor [i] = novo_vetor [index_aux];    //posição atual recebe um valor de uma posição aleatória
                novo_vetor [index_aux] = aux;               //aquela posição aleatória recebe o valor 'holdado' por aux;
            }                                               //no caso, houve apenas uma troca entre vetor [i] com vetor [rand];

            return novo_vetor;
        break;

        case 2:
            return novo_vetor;
        break;

        case 3:
            if (tamanho < 1) {
                return novo_vetor;
            } else {
                srand (time (NULL));
                aux = rand () % tamanho;
                srand (rand () % 10);
                novo_vetor [aux] = rand () % 999;
                return novo_vetor;
            }
        break;
    }
}

void mostrar_vetor_C (long int * vetor, long int tamanho) {
    int flag = 1;

    for (long int i = 0; i < tamanho; i ++) {
        if (flag && vetor [i] != i + 1) {
            printf (HRED "%ld " reset, vetor [i]);
            flag = 0;
        } else {
            printf ("%ld ", vetor [i]);
        }
    }
    printf ("\n");
}

void mostrar_vetor (long int * vetor, long int tamanho) {
    for (long int i = 0; i < tamanho; i ++) {
        printf ("%ld ", vetor [i]);
    }
    printf ("\n");
}

void bubble_sort (long int * vetor, long int tamanho) {
    /*
    Complexidade melhor caso: O(n)
    Complexidade pior caso: O(n²)
    É bom quando:
    É ruim quando:
    */
    int flag = 1;
    long int i, j, aux;

    for (i = 0; i < tamanho - 1 && flag; i ++) {    //for percorrerá até o fim do vetor -1, pois não precisará acessar a ultima posição
        flag = 0;                                   //flag para indicar se houve swap
        for (j = 0; j < tamanho - 1 - i; j ++) {    //as ultimas posições do vetor já estarão ordenada, por isso não se deve acessá-las: tamanho - 1 - j resolve isso
            if (vetor [j] > vetor [j + 1]) {        //verificar se o elemento atual é maior que o proximo
                aux = vetor [j];                    //guarda o aual
                vetor [j] = vetor [j + 1];          //faz o indice atual receber o proximo
                vetor [j + 1] = aux;                //faz o proximo indice receber o antigo atual
                flag = 1;                           //poe flag em 1 pra indicar que houve swap
            }                                       //caso swap permaneça com 0, significa que não houve nehuma troca e que o vetor já está ordenado.
        }
    }

}

void insertion_sort (long int * vetor, long int tamanho) {
    /*
    Complexidade melhor caso: O(n)
    Complexidade pior caso: O(n²)
    É bom quando: Possui apenas 1 número fora da ordem;
    É ruim quando: Há muitos números fora da ordem;
    */
   long int i, j, aux;

   for (i = 1; i < tamanho; i ++) {                         //coloca I em 1 e vai até o fim do vetor;
       aux = vetor [i];                                     //guardar a posição I em aux;
       for (j = i - 1; j >= 0 && vetor [j] > aux; j--) {    //coloca a posição J antes de I e decrementa J enquando for maior ou igual a zero e enquando vetor na posição J for maior que aux;
           vetor [j + 1] = vetor [j];                       //copia a posição maior para o proximo indice
       }

       vetor [j + 1] = aux;                                 //traz a posição menor para o lugar que ela deve estar
   }
}

void selection_sort (long int * vetor, long int tamanho) {
    /*
    Complexidade: O(n²)
    */
    long int i, j, menor, aux;

    for (i = 0; i < tamanho - 1; i ++) {
        menor = i;
        
        for (j = i + 1; j < tamanho; j ++) {
            if (vetor [j] < vetor [menor]) {
                menor = j;
            }
        }

        aux = vetor [i];
        vetor [i] = vetor [menor];
        vetor [menor] = aux;
    }
}

void merge_sort (long int * vetor, long int inicio, long int fim) {
    long int meio;
    if (inicio < fim) {
        meio = (inicio + fim) / 2;
        merge_sort (vetor, inicio, meio);
        merge_sort (vetor, meio + 1, fim);
        merge (vetor, inicio, meio, fim);
    }
}

void merge (long int * vetor, long int inicio, long int meio, long int fim) {
    long int i, j, k, * aux = (long int *) malloc (sizeof (long int) * fim - inicio + 1);
    i = inicio;
    j = meio + 1;
    k = 0;

    while (i <= meio && j <= fim) {
        if (vetor [i] <= vetor [j]) {
            aux [k] = vetor [i];
            i ++;
        } else {
            aux [k] = vetor [j];
            j ++;
        }
        k ++;
    }

    while (i <= meio) {
        aux [k] = vetor [i];
        i ++;
        k ++;
    }

    while (j <= fim) {
        aux [k] = vetor [j];
        j ++;
        k ++;
    }

    for (i = inicio; i <= fim; i ++) {
        vetor [i] = aux [i - inicio];
    }

    free (aux);
}

void quick_sort (long int * vetor, long int esq, long int dir) {
    //ainda não consegui entender o funcionamento desse código, mas consigo entender o algoritmo em si
    //http://www.programasprontos.com/algoritmos-de-ordenacao/algortimo-quick-sort/
    long int i, j, x, y;

    i = esq;
    j = dir;
    x = vetor [(esq + dir) / 2];

    while (i <= j) {
        while (vetor [i] < x && i < dir) {
            i ++;
        }

        while (vetor [j] > x && j > esq) {
            j --;
        }

        if (i <= j) {
            y = vetor [i];
            vetor [i] = vetor [j];
            vetor [j] = y;
            i ++;
            j --;
        }
    }

    if (j > esq) {
        quick_sort (vetor, esq, j);
    }
    if (i < dir) {
        quick_sort (vetor, i, dir);
    }
}

void mostrar_tabela_final (float temposA [], float temposB [], float temposC []) {
    
    printf ("---------------------------------------------------------------------\n");
    printf ("|         |  Bubble  | Insertion | Selection |   Merge   |  Quick   |\n");
    printf ("---------------------------------------------------------------------\n");
    printf ("| "HBLE"Vetor A"reset" |");
    get_times (temposA);
    printf ("---------------------------------------------------------------------\n");
    printf ("| "HCYN"Vetor B"reset" |");
    get_times (temposB);
    printf ("---------------------------------------------------------------------\n");
    printf ("| "HPUR"Vetor C"reset" |");
    get_times (temposC);
    printf ("---------------------------------------------------------------------\n");
}

void get_times (float tempos []) {
    //Essa função serve para percorrer o vetor com os tempos e printar na tabela acima
    //printa o maior valor de um vetor em vermelho e o menor em verde
    for (int i = 0; i < 5; i ++) {
        if (tempos [i] == tempos [6]) {
            printf (" "HRED"%f"reset" |", tempos [i]);
        } else {
            if (tempos [i] == tempos [7]) {
                printf (" "HGRN"%f"reset" |", tempos [i]);
            } else {
                printf ("  %f |", tempos [i]);
            }
        }
    }
    printf ("\n");
}

void criar_output (FILE * file, float * times, char * type, long int tam) {
    //esta função insere os dados no arquivo CSV
    time_t segs = time (NULL);
    struct tm * data_hora = localtime (&segs);
    int day, month, year;
    int hour, min, sec;
    day = data_hora -> tm_mday;
    month = data_hora -> tm_mon + 1;
    year = data_hora -> tm_year + 1900;
    hour = data_hora -> tm_hour;
    min = data_hora -> tm_min;
    sec = data_hora -> tm_sec;

    fseek (file, 0, SEEK_END);
    if (!ftell (file)) {
        fprintf (file, "\"date-time\",\"type\",\"length\",\"bbs_time\",\"ins_time\",\"sel_time\",\"mer_time\",\"qui_time\"");
    }

    fprintf (file, "\n\"%d/%d/%d %d:%d:%d\",\"%s\",%ld,%f,%f,%f,%f,%f", day, month, year, hour, min, sec, type, tam, times [0], times [1], times [2], times [3], times [4]);
}