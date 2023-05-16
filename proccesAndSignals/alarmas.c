#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handlerSIGALRM(int sig);

int main()
{
  int secRestantes;
  char *entrada;
  entrada = malloc(10 * sizeof(char)); // Asignación de memoria
  signal(SIGALRM, handlerSIGALRM);     // Redefine handler de SIGALRM
  printf("Espero una cadena de entrada con enter hasta 10 segundos\n");
  secRestantes = alarm(10); // Espera hasta 10 segundos la entrada
  printf("Segundos Restantes: " + secRestantes);
  if (secRestantes > 0)
  {
    printf("Existía una alarma previa con %d segundos restantes", secRestantes);
  }
  scanf("%10s", entrada); // El proceso se detendrá aquí
  printf("Se recibe la entrada de usuario: %s", entrada);
  return 0;
}
// Rutina de atención de la señal, notifica señal que se recibió
void handlerSIGALRM(int sig)
{
  printf("\nSe recibe la señal de la alarma #%d\n", sig);
  exit(0);
}