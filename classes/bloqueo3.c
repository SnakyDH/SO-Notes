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

pthread_t proxy(int num)
{
  void *arg;
  int val_ret;
  arg = (void *)&id; // Obtenemos dirección de la variable
  pthread_t id_h;
  pthread_mutex_lock(&id_mutex);
  // Inicia región crítica, hemos tomado el mutex
  id = num;
  val_ret = pthread_create(&id_h, NULL, &salidaContador, arg);
  if (val_ret)
  {
    exit(1);
  }
  // Fin de la region critica
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
  val_ret = pthread_mutex_init(&id_mutex, NULL);
  id_h1 = proxy(1); // Invocamos proxy para generar 1ro hilo
  id_h2 = proxy(2); // Invocamos proxy para generar 2do hilo
  printf("\n Se crearon hilos \n");
  // Esperamos a la terminación del hilo
  val_ret = pthread_join(id_h1, NULL);
  if (val_ret)
  {
    printf("Error en la terminación del hilo: %d\n", val_ret);
  }
  val_ret = pthread_join(id_h2, NULL);
  if (val_ret)
  {
    printf("Error en la terminación del hilo: %d\n", val_ret);
  }
  val_ret = pthread_mutex_destroy(&id_mutex);
  if (val_ret)
  {
    printf("Error al terminar mutex o semáforo: %d\n", val_ret);
  }
  printf("\n Se termina el hilo y el programa \n");
  printf("Contador 1: %07ld, Contador 2: %07ld\n", contador[0], contador[1]);

  exit(0);
}