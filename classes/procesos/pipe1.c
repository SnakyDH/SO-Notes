#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Define una Macro: Son pedazos de código, mejores para definir constantes para tener un mejor espacio de memoria
#define P_WRITE 1
#define P_READ 0
// Constantes: Ocupan menos espacio de memoria
// const int pWrite = 1;
// const int pRead = 0;
// Constantes
// int pWrite = 1;
// int pRead = 0;

int main (void){
    int fd[2];
    int num_ch; //numero de characters
    pid_t pidC; // proceso hijo
    char buf[10]; // bufer para enviar texto
    
    pipe(fd); //Crea una tuberia, pasandole el descriptor de archivo

    pidC = fork(); // puede ser 0, -1 (error), >0 (mayor que cero, id del proceso padre)

    switch (pidC)
    {
    case 0:
        // Hace el hijo
        close(fd[P_READ]);
        // buf, lo que quiero enviar, #de bytes que envio
        // /0, hasta aqui va, corta los otros 4
        write(fd[P_WRITE], "Hola!\0", 6);
        close(fd[P_WRITE]);
        exit(0);
        break;
    case -1:
        // error
        printf("Ha ocurrido un error :c al crear el proceso");
        exit(1);
        break;
    default: // Mayor a 0
        // lo que hace el padre
        //Padre 
        close(fd[P_WRITE]);
        num_ch = read(fd[P_READ],buf,sizeof(buf));
        printf("Se han leido %d bytes con el mensaje: %s\n");
        close(fd[P_READ]);
        exit(0);
        break;
    }
    return 0;
}
// run gcc <file> -0 <archivo_compilado>