#include <iostream>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>
#include <csignal>

/* ABS */
bool abs_ativado = false;
bool roda_travada = false;

/* Vidro */
bool vidro_fechado = false;

/* Airbag */
bool airbag = false;

/* Cinto de Segurança */
bool passageiro_sem_cinto_de_seguranca = false;

/* Farol */
bool farol_ligado = false;

/* Travas */
bool carro_travado = false;

/* Injeção Eletrônica*/
bool injecao_eletronica = false;

/* Temperatura */
int temperatura = 0;

/* Consumo*/
float consumo = 20.01;
bool mostrar_consumo = false;

using namespace std;

pthread_mutex_t em = PTHREAD_MUTEX_INITIALIZER;
pthread_mutexattr_t  mutexattr_prioceiling;

void display() {
    while (1)
    {
        sleep(1);
        system("clear");
    }
    
}

void thr_le_teclado(void) {
    char tecla;
    while (1) {
        if (kbhit()) {
            tecla = getch();
            if ((int)tecla == 118 || (int)tecla == 86){ //v ou V
                pthread_mutex_lock(&em);
                if (vidro_fechado == false) {
                    vidro_fechado = true;
                }
                pthread_mutex_unlock(&em);
            }
            else if ((int)tecla == 70 || (int)tecla == 102) { //f ou F
                pthread_mutex_lock(&em);
                roda_travada = true;
                pthread_mutex_unlock(&em);
            }
            else if ((int)tecla == 65 || (int)tecla == 97) { //a ou A
                pthread_mutex_lock(&em);
                airbag = true;
                pthread_mutex_unlock(&em);
                raise(SIGABRT);
            }
            else if((int)tecla == 76 || (int)tecla == 108) { //l ou L
                pthread_mutex_lock(&em);
                farol_ligado = true;
                pthread_mutex_unlock(&em);
            }
            else if ((int)tecla == 84 || (int)tecla == 116) {
                pthread_mutex_lock(&em);
                if (carro_travado == false) {
                    carro_travado = true;
                }
                pthread_mutex_unlock(&em);
            } //t ou T
            else if ((int)tecla == 67 || (int)tecla == 99) {
                pthread_mutex_lock(&em);
                if (passageiro_sem_cinto_de_seguranca == false) {
                    passageiro_sem_cinto_de_seguranca = true;
                }
                pthread_mutex_unlock(&em);
            } //c ou
            else if ((int)tecla == 73 || (int)tecla == 105) {
                pthread_mutex_lock(&em);
                injecao_eletronica = true;
                pthread_mutex_unlock(&em);
            } //i ou I
            else if ((int)tecla == 77 || (int)tecla == 109) {
                pthread_mutex_lock(&em);
                mostrar_consumo = true;
                pthread_mutex_unlock(&em);
            } //m ou M
        }
    }
}

void controlador_abs(bool forca_do_pedal) {
    if (forca_do_pedal == true) {
        sleep(0.005);
        abs_ativado = true;
        printf("ABS Ativado\n");
        roda_travada = false;
        abs_ativado = false;
    }
}

void sensor_freio() {
    while(1){
        clock_t inicial;
        inicial = clock();
        sleep(0.001);
        pthread_mutex_lock(&em);
        if(roda_travada == true){
            controlador_abs(roda_travada);
            double tempo = (double)(clock() - inicial)/CLOCKS_PER_SEC;
            printf("Tempo de execução: %lf\n", tempo);
        }
        pthread_mutex_unlock(&em);
    }
}

void sensor_airbag() {
    while(1){
        sleep(0.001);
        pthread_mutex_lock(&em);
        if(airbag == true){
            controlador_abs(airbag);
        }
        pthread_mutex_unlock(&em);
    }
}

void controlador_airbag(bool comando) {
    if (comando == true) {
        sleep(0.005);
        printf("Carro Batido!\n");
    }
}

void controlador_cinto_de_seguranca(bool comando) {
    if (comando == true) {
        sleep(0.005);
        printf("Cinto acionado\n");
        passageiro_sem_cinto_de_seguranca = false;
    }
}

void sensor_cinto_de_seguranca() {
    while(1){
        clock_t inicial;
        inicial = clock();
        sleep(0.001);
        pthread_mutex_lock(&em);
        if(passageiro_sem_cinto_de_seguranca == true){
            controlador_cinto_de_seguranca(passageiro_sem_cinto_de_seguranca);
            double tempo = (double)(clock() - inicial)/CLOCKS_PER_SEC;
            printf("Tempo de execução: %lf\n", tempo);
        }
        pthread_mutex_unlock(&em);
    }
}

void controlador_farol(bool comando) {
    if (comando == true) {
        sleep(0.005);
        printf("Farol acionado\n");
        farol_ligado = false;
    }
}

void sensor_farol(int comando) {
    while(1){
        clock_t inicial;
        inicial = clock();
        sleep(0.001);
        pthread_mutex_lock(&em);
        if(farol_ligado == true){
            controlador_farol(farol_ligado);
            double tempo = (double)(clock() - inicial)/CLOCKS_PER_SEC;
            printf("Tempo de execução: %lf\n", tempo);
        }
        pthread_mutex_unlock(&em);
    }
}

void controlador_travas(bool comando) {
    if (comando == true) {
        sleep(0.005);
        printf("Travas acionadas\n");
        carro_travado = false;
    }
}

void sensor_travas() {
    while(1){
        clock_t inicial;
        inicial = clock();
        sleep(0.001);
        pthread_mutex_lock(&em);
        if(carro_travado == true){
            controlador_travas(carro_travado);
            double tempo = (double)(clock() - inicial)/CLOCKS_PER_SEC;
            printf("Tempo de execução: %lf\n", tempo);
        }
        pthread_mutex_unlock(&em);
    }
}

void controlador_vidros(bool comando) {
    if (comando == true) {
        sleep(0.005);
        printf("Vidro acionado\n");
        vidro_fechado = false;
    }
}

void sensor_vidro() {
    while(1){
        clock_t inicial;
        inicial = clock();
        sleep(0.001);
        pthread_mutex_lock(&em);
        if(vidro_fechado == true){
            controlador_vidros(vidro_fechado);
            double tempo = (double)(clock() - inicial)/CLOCKS_PER_SEC;
            printf("Tempo de execução: %lf\n", tempo);
        }
        pthread_mutex_unlock(&em);
    }
}

void controlador_injecao_eletronica(bool comando) {
    if (comando == true) {
        sleep(0.005);
        printf("Carro acelerando\n");
        injecao_eletronica = false;
    }
}

void sensor_injecao_eletronica() {
    while(1){
        clock_t inicial;
        inicial = clock();
        sleep(0.001);
        pthread_mutex_lock(&em);
        if(injecao_eletronica == true){
            controlador_injecao_eletronica(injecao_eletronica);
            double tempo = (double)(clock() - inicial)/CLOCKS_PER_SEC;
            printf("Tempo de execução: %lf\n", tempo);
        }
        pthread_mutex_unlock(&em);
    }
}

void controlador_temperatura(int comando) {
    if (comando >= 100) {
        sleep(0.005);
        temperatura = temperatura - 2;
        printf("Arrefecimento acionado e resfriando o motor\n");
    }
}

void sensor_temperatura() {
    while(1) {
        clock_t inicial;
        inicial = clock();
        sleep(0.001);
        pthread_mutex_lock(&em);
        if (injecao_eletronica == true) {
            temperatura++;
            controlador_temperatura(temperatura);
            double tempo = (double)(clock() - inicial)/CLOCKS_PER_SEC;
            printf("Tempo de execução: %lf\n", tempo);
        }
        pthread_mutex_unlock(&em);
    }
}

void controlador_consumo() {
    sleep(0.005);
    printf("Consumo médio: %f\n", consumo);
}

int aux = 0;
void sensor_consumo() {
    while(1) {
        sleep(0.001);
        pthread_mutex_lock(&em);
        if (injecao_eletronica == true) {
            aux++;
            if(aux % 10 == 0) {
                consumo = consumo - 0.01;
            }
        }
        pthread_mutex_unlock(&em);

        pthread_mutex_lock(&em);
        if (mostrar_consumo == true) {
            controlador_consumo();
            mostrar_consumo = false;
        }
        pthread_mutex_unlock(&em);
    }
}



int main() {
    pthread_t t_le_teclado, t_vidro, t_ABS, t_airbag, t_cinto, t_farol, t_travas, t_injecao, t_temperatura, t_display, t_consumo;
    

    //criação das threads
    //pthread_create(&t_display, NULL, (void *) display, NULL);
    pthread_create(&t_le_teclado, NULL, (void *) thr_le_teclado, NULL);
    pthread_create(&t_vidro, NULL, (void *) sensor_vidro, NULL);
    pthread_create(&t_ABS, NULL, (void *) sensor_freio, NULL);
    pthread_create(&t_airbag, NULL, (void *) sensor_airbag, NULL);
    pthread_create(&t_cinto, NULL, (void *) sensor_cinto_de_seguranca, NULL);
    pthread_create(&t_farol, NULL, (void *) sensor_farol, NULL);
    pthread_create(&t_travas, NULL, (void *) sensor_travas, NULL);
    pthread_create(&t_injecao, NULL, (void *) sensor_injecao_eletronica, NULL);
    pthread_create(&t_temperatura, NULL, (void *) sensor_temperatura, NULL);
    pthread_create(&t_consumo, NULL, (void *) sensor_consumo, NULL);
    
    
	//espera as threads para finalizar o programa
	pthread_join(t_le_teclado, NULL);
    //pthread_join(t_display, NULL);
    pthread_join(t_vidro, NULL);
    pthread_join(t_ABS, NULL);
    pthread_join(t_airbag, NULL);
    pthread_join(t_cinto, NULL);
    pthread_join(t_farol, NULL);
    pthread_join(t_travas, NULL);
    pthread_join(t_injecao, NULL);
    pthread_join(t_temperatura, NULL);
    pthread_join(t_consumo, NULL);

    return 0;
}