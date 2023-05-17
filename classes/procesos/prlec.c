// Proceso que lee
#include <sys/stat.h> // mirar el estado
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void){
    int fd;
    char buf[1024] =;
    fd = open("/tmp/mi_fifo",O_RDONLY); // solo lectura, estoy cerrando la lectura
    int nb = read(fd,buf,sizeof(buf));
    close(fd);
    printf("Recibidos %d Bytes con el mensaje %s \n",nb,buf);
    return 0;
}
// cp prlec.c presc.c
// nano prlec.c
// en presc.c Cambiamos el bufer para no definirle un espacio y le indicamos "mensaje desde ESC"
// add mkfifo("/tmp/mififo",0666);
// Cambio o_RDONLY por O_WRONLY
// write (fd,buf,sizeof(buf)); antes del close();