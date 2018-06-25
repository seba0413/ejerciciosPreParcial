#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Destinatario.h"
#include "ArrayList.h"

int parcer_cargarDestinatarios(char* fileName, ArrayList* listaDestinatarios)
{
    int retorno = -1;
    char nombre[128];
    char mail[128];

    Destinatario* auxDestinatario;

    if(fileName != NULL && listaDestinatarios != NULL)
    {
        FILE* fp = fopen(fileName, "r");

        if(fp != NULL)
        {
            while(!feof(fp))
            {
                fscanf(fp, "%[^,],%[^\n]\n", nombre, mail);
                auxDestinatario = destinatario_newParametros(nombre, mail);
                al_add(listaDestinatarios, auxDestinatario);
            }

            retorno = 0;
            fclose(fp);
        }
    }
     return retorno;
}
