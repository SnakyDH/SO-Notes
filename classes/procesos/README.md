# 
Necesitamos crear una tuberia para conectar los procesos, el cual es un archivo virtual (ocupa un espacio de memoria), El archivo tendra 2 identificadores: 
fd[0] => File Descriptor[lectura]
fd[1] => File Descriptor[escritura]
Lo creara en ambos lados o en ambos procesos.
Si queremos manejar un flujo de proceso 1 a proceso 2, se cerraria fd[0] y fd[1], en 