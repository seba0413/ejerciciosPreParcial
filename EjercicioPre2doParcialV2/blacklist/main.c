#include <stdio.h>
#include <stdlib.h>
#include "Destinatario.h"
#include "ArrayList.h"
#include "parcer.h"
#include "utn.h"

int generarArchivo(char* fileName, ArrayList* lista);

int main()
{
    int i, index;

    ArrayList* listaDestinatarios;
    listaDestinatarios = al_newArrayList();

    ArrayList* listaNegra;
    listaNegra = al_newArrayList();

    int opcion;

    do
    {
        getValidInt("\n1.Cargar Destinatarios\n2.Cargar lista negra\n3.Depurar\n4.Listar\n5.Salir\n", "\nOpcion invalida\n", &opcion,1,5,2);

        switch(opcion)
        {
            case 1:
                if(!parcer_cargarDestinatarios("destinatarios.csv",listaDestinatarios))
                    printf("\nLista destinatarios cargada correctamente\n");
                else
                    printf("\nError al cargar la lista de destinatarios\n");
                break;

            case 2:
                if(!parcer_cargarDestinatarios("black_list2.csv",listaNegra))
                    printf("\nLista negra cargada correctamente\n");
                else
                    printf("\nError al cargar la lista negra\n");
                break;

            case 3:
                for(i = 0; i < al_len(listaNegra); i++)
                {
                    Destinatario* destNegra = al_get(listaNegra, i);
                    index = al_indexOfElement(listaDestinatarios, destNegra, destinatario_compararDestinatarios);
                    al_remove(listaDestinatarios, index);
                }

                ArrayList* nuevaLista = al_newArrayList();
                nuevaLista = al_clone(listaDestinatarios);

                for(i = 0; i < al_len(listaDestinatarios); i++)
                {
                    Destinatario* destDuplicado = al_get(listaDestinatarios, i);
                    index = al_indexOfElementDuplicated(nuevaLista, destDuplicado, destinatario_compararDestinatarios);
                    //printf("%d\n", index);
                    al_remove(nuevaLista, index);
                }

                if(nuevaLista != NULL)
                    printf("\nNueva lista generada\n");
                else
                    printf("\nError al depurar la lista\n");

                break;
            case 4:
                if(!generarArchivo("listaFinal.csv", nuevaLista))
                    printf("\nArchivo generado exitosamente\n");
                else
                    printf("\nError en la generacion del archivo\n");

                break;
        }

    }while(opcion != 5);

    return 0;
}

int generarArchivo(char* fileName, ArrayList* lista)
{
    int retorno = -1;
    int i;
    char nombre[128];
    char mail[128];
    Destinatario* auxDest;

    if(fileName != NULL && lista != NULL)
    {
        FILE* fp = fopen(fileName, "w");

        if(fp != NULL)
        {
            for(i = 0; i < al_len(lista); i++)
            {
                auxDest = al_get(lista, i);
                destinatario_getName(auxDest, nombre);
                destinatario_getEmail(auxDest, mail);
                fprintf(fp, "%s - %s\n", nombre, mail);
            }
            retorno = 0;
            fclose(fp);
        }
    }
    return retorno;
}
