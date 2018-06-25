#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Destinatario.h"

static int isValidName(char* name);
static int isValidEmail(char* email);


Destinatario* destinatario_new(void)
{
    Destinatario* returnAux = (Destinatario*) malloc(sizeof(Destinatario));
    return returnAux;
}

Destinatario* destinatario_newParametros(char* name, char* email)
{
    Destinatario* this;
    this = destinatario_new();
    if( !destinatario_setName(this,name) &&
        !destinatario_setEmail(this,email) )
    {
        return this;
    }
    destinatario_delete(this);
    return NULL;
}


void destinatario_delete(Destinatario* this)
{
    if(this != NULL)
        free(this);
}


int destinatario_setName(Destinatario* this, char* name)
{
    int retorno = -1;
    if(this != NULL && name != NULL && isValidName(name))
    {
        retorno = 0;
        strcpy(this->name,name);
    }
    return retorno;
}

int destinatario_getName(Destinatario* this, char* name)
{
    int retorno = -1;
    if(this != NULL && name != NULL)
    {
        retorno = 0;
        strcpy(name,this->name);
    }
    return retorno;
}

int destinatario_setEmail(Destinatario* this, char* email)
{
    int retorno = -1;
    if(this != NULL && email != NULL && isValidEmail(email))
    {
        retorno = 0;
        strcpy(this->email,email);
    }
    return retorno;
}

int destinatario_getEmail(Destinatario* this, char* email)
{
    int retorno = -1;
    if(this != NULL && email != NULL)
    {
        retorno = 0;
        strcpy(email,this->email);
    }
    return retorno;
}

int destinatario_compararDestinatarios(void* destinatario1, void* destinatario2)
{
    char nombre1[128];
    char nombre2[128];

    if(destinatario1 != NULL && destinatario2 != NULL)
    {
        Destinatario* auxiliar1 = (Destinatario*) destinatario1;
        Destinatario* auxiliar2 = (Destinatario*) destinatario2;

        destinatario_getName(auxiliar1, nombre1);
        destinatario_getName(auxiliar2, nombre2);
    }
    return strcmp(nombre1, nombre2);
}

static int isValidName(char* name)
{
    return 1;
}

static int isValidEmail(char* email)
{
    return 1;
}

