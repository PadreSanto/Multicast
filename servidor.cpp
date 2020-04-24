#include "SocketDatagrama.h"
#include "socketmulticast.h"

int main(int argc, char const *argv[])
{   
    if (argc != 4)
    {
        printf("Uso: ./%s [DIRECCIÓN MULTICAST] [PUERTO PARA ENVIAR] [CADENA A ENVIAR]\n",
               argv[0]);
        exit(EXIT_FAILURE);
    }

    // Extracción de parámetros.

    char direccionMulticast[16];
    sprintf(direccionMulticast, "%s", argv[1]);

    int puertoTransmision = atoi(argv[2]);

    unsigned char ttl = (unsigned char)1;

    int longitudCadena = strlen(argv[3]);
    char *cadenaParaEnviar = new char[longitudCadena];
    sprintf(cadenaParaEnviar, "%s", argv[3]);

    // Se abre socket.
    SocketMulticast socket(puertoTransmision);
    //socket.unirAlGrupo(direccionMulticast);

    // Se genera paquete y se envía.

    PaqueteDatagrama pd(cadenaParaEnviar, longitudCadena, direccionMulticast, puertoTransmision);
    if (socket.envia(pd, ttl) < 0)
    {
        printf("Error al enviar paquete\n");
        exit(1);
    }
    printf("El mensaje ha sido enviado un correctamente al grupo.\n");


    SocketDatagrama socketUnicast(6000);
    PaqueteDatagrama request(MAX_LONGITUD_DATOS);

    for (int i = 0; i < 5; ++i)
    {
        socketUnicast.recibe(request);
        printf("Se recibio respuesta de la direccion: %s\n",request.obtieneDireccion());
        printf("Respuesta del grupo: ",request.obtieneDatos());
    }
        

    return 0;
}
