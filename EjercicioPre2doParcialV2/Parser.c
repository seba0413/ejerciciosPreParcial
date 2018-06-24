#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"
#include "Empleado.h"

int parser_parseEmpleados(char* fileName, ArrayList* listaEmpleados)
{
    int retorno = -1;
    char id[128];
    char nombre[128];
    char horasTrabajadas[128];

    S_Empleado* auxiliarEmpleado;

    FILE* fp = fopen(fileName, "r");
    if(fp!= NULL)
    {
        retorno = 0;

        fscanf(fp,"%[^,],%[^,],%[^\n]\n", id, nombre, horasTrabajadas);
        while(!feof(fp))
        {
            fscanf(fp,"%[^,],%[^,],%[^\n]\n", id, nombre, horasTrabajadas);
            auxiliarEmpleado = Empleado_new();
            Empleado_setId(auxiliarEmpleado, atoi(id));
            Empleado_setNombre(auxiliarEmpleado, nombre);
            Empleado_setHorasTrabajadas(auxiliarEmpleado, atoi(horasTrabajadas));
            al_add(listaEmpleados, auxiliarEmpleado);
        }
        retorno = 1;

        fclose(fp);
    }


    return retorno;
}

