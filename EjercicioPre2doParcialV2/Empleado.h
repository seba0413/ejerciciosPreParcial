#ifndef EMPLEADO_H_INCLUDED
#define EMPLEADO_H_INCLUDED

typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
}S_Empleado;

S_Empleado* Empleado_new();
void Empleado_delete();

int Empleado_setId(S_Empleado* this,int id);
int Empleado_getId(S_Empleado* this,int* id);

int Empleado_setNombre(S_Empleado* this,char* nombre);
int Empleado_getNombre(S_Empleado* this,char* nombre);

int Empleado_setHorasTrabajadas(S_Empleado* this,int horasTrabajadas);
int Empleado_getHorasTrabajadas(S_Empleado* this,int* horasTrabajadas);

int Empleado_setSueldo(S_Empleado* this,int sueldo);
int Empleado_getSueldo(S_Empleado* this,int* sueldo);

void Empleado_calcularSueldo(void* empleado);

void Empleado_imprimirEmpleados(void* empleado);

int Empleado_compararPorNombre(void* empleado1, void* empleado2);

int Empleado_compararPorHorasTrabajadas(void* empleado1, void* empleado2);

#endif // EMPLEADO_H_INCLUDED
