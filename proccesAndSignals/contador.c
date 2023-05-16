#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_NUM 1000000

long contador[2];
int id; // Recurso non_preemptive de ejemplo
pthread_mutex_t id_mutex;
pthread_cond_t cv;
void *salidaContador(void *id_pt);

pthread_t proxy(int numero)
{ // Función encargada de iniciar hilos contadores
  void *arg;
  int val_ret;
  arg = (void *)&id; // Obtenemos dirección de la variable
  pthread_t id_h;
  pthread_mutex_lock(&id_mutex);
  // Inicia región crítica, hemos tomado el mutex
  id = numero;
  // * Aqui un sleep(3); para que se vea el efecto de la espera, antes de crear el hilo
  val_ret = pthread_create(&id_h, NULL, &salidaContador, arg);
  // Región crítica terminó en salidaContador
  if (val_ret)
  {
    printf("Error en la creación del hilo%d:%d\n", numero, val_ret);
    exit(1);
  }
  return id_h;
}

void *salidaContador(void *id_pt)
{
  // Continúa región crítica iniciada en proxy
  int id = *(int *)id_pt;
  // Termina región crítica, espera de señal de CV
  pthread_cond_wait(&cv, &id_mutex);
  pthread_mutex_unlock(&id_mutex); // Finalmente libera el mutex
  id--;
  for (contador[id] = 0l; contador[id] < MAX_NUM; contador[id]++)
  {
    printf("%sContador %d: %07ld,%07ld\r", (id == 1 ? "\t\t\t\t" : ""), id + 1, contador[id], contador[id] - contador[1 - id]);
  }
  return NULL;
}

int main()
{
  pthread_t id_h1, id_h2;
  int val_ret;
  // Iniciar atributos del mutex a valores por defecto
  val_ret = pthread_mutex_init(&id_mutex, NULL);
  if (val_ret)
    printf("Error al crear mutex: %d\n", val_ret);
  // Iniciar variable de condición con atributos por defecto
  val_ret = pthread_cond_init(&cv, NULL);
  if (val_ret)
    printf("Error al crear CV: %d\n", val_ret);
  id_h1 = proxy(1); // Invocamos proxy para generar hilos
  id_h2 = proxy(2);
  printf("Se crearon hilos secundarios\n");
  // Usamos CV para indicar a ambos que deben proseguir, en RC
  pthread_mutex_lock(&id_mutex);
  val_ret = pthread_cond_signal(&cv);
  if (val_ret)
    printf("Error en señal de CV: %d\n", val_ret);
  val_ret = pthread_cond_signal(&cv);
  if (val_ret)
    printf("Error en señal de CV: %d\n", val_ret);
  pthread_mutex_unlock(&id_mutex);
  // Esperamos a que terminen las funciones de los hilos
  val_ret = pthread_join(id_h2, NULL);
  if (val_ret)
    printf("Error al término del hilo2: %d\n", val_ret);
  val_ret = pthread_join(id_h1, NULL);
  if (val_ret)
    printf("Error al término del hilo1: %d\n", val_ret);
  val_ret = pthread_mutex_destroy(&id_mutex);
  if (val_ret)
    printf("Error al término de mutex: %d\n", val_ret);
  val_ret = pthread_cond_destroy(&cv);
  if (val_ret)
    printf("Error al término de CV: %d\n", val_ret);
  printf("\nTerminaron los hilos\n");
  exit(0);
}