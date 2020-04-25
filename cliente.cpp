#include "socketmulticast.h"
#include "SocketDatagrama.h"


int main(int argc, char const *argv[])
{

    if (argc != 3)
    {
        printf("Uso: ./%s [DIRECCIÓN MULTICAST] [PUERTO DE ESCUCHA]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char direccionMulticast[16];
    sprintf(direccionMulticast, "%s", argv[1]);

    int puertoRecepcion = atoi(argv[2]);

    SocketMulticast socket(puertoRecepcion);
    socket.unirseGrupo(direccionMulticast);

    // Se prepara un paquete para recibir y se imprime origen.
    PaqueteDatagrama pd(MAX_LONGITUD_DATOS);
    if (socket.recibe(pd) < 0) {
        printf("Error al recibir paquete\n");
        exit(1);
    }
    char dirFuente[16];
    sprintf(dirFuente, "%s", pd.obtieneDireccion());

    printf("\nSe recibió un paquete.\n");
    printf("Mensaje: %s",pd.obtieneDatos());
    printf("\nDireccion: %s\n", dirFuente);
    printf("Puerto: %d\n", pd.obtienePuerto());
    
    socket.salirseGrupo(direccionMulticast);

    // Se abre socket.
    SocketDatagrama socketUnicast(7000);

    // Se genera paquete y se envía.

    PaqueteDatagrama pdUnicast("Si recibi dato \n", strlen("Si recibi dato \n"), dirFuente, 6000);


    socketUnicast.envia(pdUnicast);
    return 0;
}
