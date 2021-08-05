#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "multitarefas.h"

/*
 * Prototipos das tarefas
 */
void tarefa_1(void);//produtor
void tarefa_2(void);//consumidor


/*
 * Configuracao dos tamanhos das pilhas
 */
#define TAM_PILHA_1		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_2		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_OCIOSA	(TAM_MINIMO_PILHA + 24)
#define TAM_BUFFER              5 //tamanho_buffer

/*
 * Declaracao das pilhas das tarefas
 */
uint32_t PILHA_TAREFA_1[TAM_PILHA_1];
uint32_t PILHA_TAREFA_2[TAM_PILHA_2];
uint32_t PILHA_TAREFA_OCIOSA[TAM_PILHA_OCIOSA];


semaforo_t cheio = {0, 0};
semaforo_t vazio = {TAM_BUFFER, 0};
semaforo_t mutex = {1, 0};

uint32_t buffer[TAM_BUFFER];

/*
 * Funcao principal de entrada do sistema
 */
int main(void)
{
	
	/* Criacao das tarefas */
	/* Parametros: ponteiro, nome, ponteiro da pilha, tamanho da pilha, prioridade da tarefa */
	
	CriaTarefa(tarefa_1, "Tarefa 1", PILHA_TAREFA_1, TAM_PILHA_1, 2); //produtor
	
	CriaTarefa(tarefa_2, "Tarefa 2", PILHA_TAREFA_2, TAM_PILHA_2, 1); //consumidor
        	
	/* Cria tarefa ociosa do sistema */
	CriaTarefa(tarefa_ociosa,"Tarefa ociosa", PILHA_TAREFA_OCIOSA, TAM_PILHA_OCIOSA, 0);
	
	/* Configura marca de tempo */
	ConfiguraMarcaTempo();   
	
	/* Inicia sistema multitarefas */
	IniciaMultitarefas();
	
	/* Nunca chega aqui */
	while (1)
    {
	}
}


/* Tarefa produtor*/
void tarefa_1(void)
{
    while(1){ 
    
        SemaforoAguarda(&vazio); //vazio.contador --
        SemaforoAguarda(&mutex);

        buffer[cheio.contador]=1;                              
        
        SemaforoLibera(&mutex);
        SemaforoLibera(&cheio);  //cheio.contador ++   
  }
}

/* Tarefa consumidor*/
void tarefa_2(void)
{
    while(1){
  
        SemaforoAguarda(&cheio); //cheio.contador --
        SemaforoAguarda(&mutex);

        buffer[cheio.contador] = 0;                        
        
        SemaforoLibera(&mutex);
        SemaforoLibera(&vazio); //vazio.contador ++
    }
}
