#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_NUM 1000000

long contador[2]; // Arreglo de contadores

void *salidaContador(void *id_pt)
{
  int id = *(int *)id_pt;
  id--;
  for (contador[id] == 01; contador[id] < MAX_NUM; contador[id]++)
  {
    printf("%sContador %d: %07ld,%07ld\r", (id == 1 ? "\t\t\t\t" : ""), id + 1, contador[id], contador[id] - contador[1 - id]);
  }
  return NULL;
}

int main()
{
  pthread_t id_h1, id_h2; // indetificador del hilo
  int val_ret;
  void *arg1, *arg2;
  int id = 1, id2 = 2;
  val_ret = pthread_create(&id_hs, NULL, &salidaContador, (void *)&id);
  if (val_ret)
  {
    exit(1);
  }
  printf("Primer Hilo creado: \n");
  sleep(10); // Mala Solución
  // Proceso Principal
  id = 2;
  salidaContador((void *)&id);
  // Esperamos la terminación del hilo
  val_ret = pthread_join(id_hs, NULL);
  if (val_ret)
  {
    printf("Error en la terminación del hilo: %d\n", val_ret);
    exit(1);
  }
  printf("\n Se termina el hilo y el proceso \n");
  exit(0);
}