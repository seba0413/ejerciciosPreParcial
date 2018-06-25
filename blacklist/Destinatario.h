#ifndef _DESTINATARIO_H
#define _DESTINATARIO_H
struct
{
    char name[128];
    char email[128];
}typedef Destinatario;


Destinatario* destinatario_new(void);
Destinatario* destinatario_newParametros(char* name, char* email);
void destinatario_delete(Destinatario* this);
int destinatario_setName(Destinatario* this, char* name);
int destinatario_getName(Destinatario* this, char* name);
int destinatario_setEmail(Destinatario* this, char* email);
int destinatario_getEmail(Destinatario* this, char* email);
int destinatario_compararDestinatarios(void* destinatario1, void* destinatario2);

#endif // _DESTINATARIO_H
