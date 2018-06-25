#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"

// funciones privadas
int resizeUp(ArrayList* this);
int expand(ArrayList* this,int index);
int contract(ArrayList* this,int index);

#define AL_INCREMENT      10
#define AL_INITIAL_VALUE  10
//___________________

/** \brief Allocate a new arrayList with AL_INITIAL_VALUE elements.
 * \param void
 * \return ArrayList* Return (NULL) if Error [if can't allocate memory]
 *                  - (pointer to new arrayList) if ok
 */
ArrayList* al_newArrayList(void)
{
    ArrayList* this;
    ArrayList* returnAux = NULL;
    void* pElements;
    this = (ArrayList *)malloc(sizeof(ArrayList));

    if(this != NULL)
    {
        pElements = malloc(sizeof(void *)*AL_INITIAL_VALUE );
        if(pElements != NULL)
        {
            this->size=0;
            this->pElements=pElements;
            this->reservedSize=AL_INITIAL_VALUE;
            this->add=al_add;
            this->len=al_len;
            this->set=al_set;
            this->remove=al_remove;
            this->clear=al_clear;
            this->clone=al_clone;
            this->get=al_get;
            this->contains=al_contains;
            this->push=al_push;
            this->indexOf=al_indexOf;
            this->isEmpty=al_isEmpty;
            this->pop=al_pop;
            this->subList=al_subList;
            this->containsAll=al_containsAll;
            this->deleteArrayList = al_deleteArrayList;
            this->sort = al_sort;
            returnAux = this;
        }
        else
        {
            free(this);
        }
    }

    return returnAux;
}


/** \brief  Add an element to arrayList and if is
 *          nessesary resize the array
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (0) if Ok
 *
 */
int al_add(ArrayList* this, void* pElement)
{
    int returnAux = -1;

    if(this != NULL && pElement != NULL)
    {
        if (this->size < this->reservedSize)
        {
            this->pElements[this->size] = pElement;
            this->size++;
            returnAux = 0;
        }
        else
        {
            if(!resizeUp(this))
            {
                this->pElements[this->size] = pElement;
                this->size++;
                returnAux = 0;
            }
        }
    }
    return returnAux;
}

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Ok
 *
 */
int al_deleteArrayList(ArrayList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
        free(this->pElements);
        free(this);
        returnAux = 0;
    }
    return returnAux;
}

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return length of array or (-1) if Error [pList is NULL pointer]
 *
 */
int al_len(ArrayList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
        returnAux = this->size;
    }

    return returnAux;
}


/** \brief  Get an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return void* Return (NULL) if Error [pList is NULL pointer or invalid index] - (Pointer to element) if Ok
 *
 */
void* al_get(ArrayList* this, int index)
{
    void* returnAux = NULL;
    if(this != NULL && index >= 0 && index <= al_len(this))
    {
        returnAux = *(this->pElements + index);
    }
    return returnAux;
}


/** \brief  Find if pList contains at least one element pElement
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer]
 *                  - ( 0) if Ok but not found a element
 *                  - ( 1) if this list contains at least one element pElement
 *
 */
int al_contains(ArrayList* this, void* pElement)
{
    int returnAux = -1;
    int i;
    if(this != NULL && pElement != NULL)
    {
        returnAux = 0;

        for(i = 0; i < al_len(this); i++)
        {
            if(this->pElements[i] == pElement)
            {
                returnAux = 1;
                break;
            }
        }
    }
    return returnAux;
}


/** \brief  Set a element in pList at index position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 *
 */
int al_set(ArrayList* this, int index,void* pElement)
{
    int returnAux = -1;
    if(this != NULL && pElement != NULL && index >= 0 && index <= al_len(this))
    {
        *(this->pElements + index) = pElement;
        this->size++;
        returnAux = 0;
    }

    return returnAux;
}


/** \brief  Remove an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_remove(ArrayList* this,int index)
{
    int returnAux = -1;
    if(this != NULL && index >= 0 && index <= al_len(this))
    {
        if(!contract(this, index))
        {
            returnAux = 0;
        }
    }
    return returnAux;
}



/** \brief Removes all of the elements from this list
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer]
 *                  - ( 0) if Ok
 */
int al_clear(ArrayList* this)
{
    int returnAux = -1;
    if (this != NULL)
    {
        this->size = 0;
        this->reservedSize = AL_INITIAL_VALUE;
        this->pElements = realloc(this->pElements, sizeof(void*)*AL_INITIAL_VALUE);
        returnAux = 0;
    }

    return returnAux;
}


/** \brief Returns an array containing all of the elements in this list in proper sequence
 * \param pList ArrayList* Pointer to arrayList
 * \return ArrayList* Return  (NULL) if Error [pList is NULL pointer]
 *                          - (New array) if Ok
 */
ArrayList* al_clone(ArrayList* this)
{
    ArrayList* returnAux;
    int i;
    if (this != NULL)
    {
        returnAux = al_newArrayList();
        returnAux->size = this->size;
        returnAux->reservedSize = this->reservedSize;
        for(i = 0; i<al_len(this); i++)
        {
            *(returnAux->pElements + i) = *(this->pElements + i);
        }
    }
    else
    {
        returnAux = NULL;
    }
    return returnAux;
}




/** \brief Inserts the element at the specified position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_push(ArrayList* this, int index, void* pElement)
{
    int returnAux = -1;

    if(this != NULL && pElement != NULL && index >= 0 && index <= al_len(this))
    {
        if(!expand(this, index))
        {
            *(this->pElements + index) = pElement;
            returnAux = 0;
        }
    }
    return returnAux;
}



/** \brief Returns the index of the first occurrence of the specified element
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (index to element) if Ok
 */
int al_indexOf(ArrayList* this, void* pElement)
{
    int returnAux = -1;
    int i;
    if(this != NULL && pElement != NULL)
    {
        for(i = 0; i <= al_len(this); i++)
        {
            if(this->pElements[i] == pElement)
            {
                returnAux = i;
                break;
            }
        }
    }

    return returnAux;
}



/** \brief Returns true if this list contains no elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Not Empty - (1) if is Empty
 */
int al_isEmpty(ArrayList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
        if(al_len(this) > 0)
        {
            returnAux = 0;
        }
        else
        {
            returnAux = 1;
        }
    }
    return returnAux;
}




/** \brief Remove the item at the given position in the list, and return it.
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid index]
 *                  - ( element pointer) if Ok
 */
void* al_pop(ArrayList* this,int index)
{
    void* returnAux;
    void* elementAux;

    if(this != NULL && index >= 0 && index < al_len(this))
    {
        elementAux = this->pElements[index];
        if(!contract(this, index))
        {
            returnAux = elementAux;
        }
    }
    else
        returnAux = NULL;

    return returnAux;
}


/** \brief Returns a new arrayList with a portion of pList between the specified
 *         fromIndex, inclusive, and toIndex, exclusive.
 * \param pList ArrayList* Pointer to arrayList
 * \param from int Initial index of the element (inclusive)
 * \param to int Final index of the element (exclusive)
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid 'from' or invalid 'to']
 *                  - ( pointer to new array) if Ok
 */
ArrayList* al_subList(ArrayList* this,int from,int to)
{
    void* returnAux;
    ArrayList* listAux;
    int i;

    if(this!=NULL && from >= 0 && from <= al_len(this) && to >= 0 && to <= al_len(this) && to >= from)
    {
        listAux = al_newArrayList();

        if(listAux != NULL)
        {
            for(i = from; i<= to; i++)
            {
                al_add(listAux, al_get(this, i));
            }
            returnAux = listAux;
        }

        else
            returnAux = listAux;
    }
    else
        returnAux = NULL;

    return returnAux ;
}





/** \brief Returns true if pList list contains all of the elements of pList2
 * \param pList ArrayList* Pointer to arrayList
 * \param pList2 ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList or pList2 are NULL pointer]
 *                  - (0) if Not contains All - (1) if is contains All
 */
int al_containsAll(ArrayList* this,ArrayList* this2)
{
    int returnAux = -1;
    int sizeAux;
    int i, j;

    if(this != NULL && this2 != NULL)
    {
        returnAux = 0;

        if(this->size == this2->size)
        {
            sizeAux = this->size;

            for(i = 0; i < al_len(this); i++)
            {
                for(j = 0; j < al_len(this); j++)
                {
                    if(this->pElements[i] == this2->pElements[j])
                    {
                        sizeAux--;
                        break;
                    }
                }
            }

            if(!sizeAux)
            {
                returnAux = 1;
            }
        }
    }

    /*int returnAux = -1;
    int sizeAux;
    int i;

    if(this != NULL && this2 != NULL)
    {
        returnAux = 0;

        if(this->size == this2->size)
        {
            sizeAux = this->size;

            for(i = 0; i < al_len(this); i++)
            {
                if(this->pElements[i] == this2->pElements[i])
                    sizeAux--;
            }

            if(!sizeAux)
            {
                returnAux = 1;
            }
        }
    }*/

    return returnAux;
}

/** \brief Sorts objects of list, use compare pFunc
 * \param pList ArrayList* Pointer to arrayList
 * \param pFunc (*pFunc) Pointer to fuction to compare elements of arrayList
 * \param order int  [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [pList or pFunc are NULL pointer]
 *                  - (0) if ok
 */
int al_sort(ArrayList* this, int (*pFunc)(void* ,void*), int order)
{
    int i,j;
    int returnAux = -1;
    void* elementAux;

    if(this != NULL && pFunc != NULL && (order == 0 || order == 1))
    {
        if(order)
        {
            for(i = 1;i < al_len(this); i++)
            {
                elementAux = al_get(this, i);
                j = i-1;

                while(j >= 0 && (pFunc(elementAux, this->pElements[j])) == 1)
                {
                    this->pElements[j+1] = this->pElements[j];
                    j--;
                }
                 this->pElements[j+1] = elementAux;
            }
        }
        else
        {
            for(i = 1;i < al_len(this);i++)
            {
                elementAux = al_get(this, i);
                j = i-1;

                while(j >= 0 && (pFunc(elementAux, this->pElements[j])) == -1)
                {
                    this->pElements[j+1] = this->pElements[j];
                    j--;
                }
                this->pElements[j+1] = elementAux;
            }
        }
        returnAux = 0;
    }

    return returnAux;
}

int al_indexOfElement(ArrayList* this, void* item, int (*pFunc)(void* item1, void* item2))
{
    int retorno = -1;
    int i;

    if(this != NULL && item != NULL && pFunc != NULL)
    {
        for(i = 0; i < al_len(this); i++)
        {
            if(!pFunc(this->pElements[i], item))
                return i;
        }
    }
    return retorno;
}

int al_indexOfElementDuplicated(ArrayList* this, void* item, int (*pFunc)(void* item1, void* item2))
{
    int retorno = -1;
    int i;
    int contador = 0;

    if(this != NULL && item != NULL && pFunc != NULL)
    {
        for(i = 0; i < al_len(this); i++)
        {
            if(!pFunc(this->pElements[i], item))
                contador++;
            if(contador > 1)
                return i;
        }
    }
    return retorno;
}



/** \brief Increment the number of elements in pList in AL_INCREMENT elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer or if can't allocate memory]
 *                  - (0) if ok
 */
int resizeUp(ArrayList* this)
{
    int returnAux = -1;
    void* auxiliar;

    if(this != NULL)
    {
        auxiliar = realloc(this->pElements, sizeof(void*)*(this->reservedSize + AL_INCREMENT));
        if(auxiliar != NULL)
        {
            this->pElements = auxiliar;
            this->reservedSize = this->reservedSize+AL_INCREMENT;
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief  Expand an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int expand(ArrayList* this,int index)
{
    int returnAux = -1;
    int i;

    if(this != NULL && index >= 0 && index <= al_len(this))
    {
        this->size++;
        if(this->size <= this->reservedSize)
        {
            for(i = this->size; i > index; i--)
            {
               *(this->pElements+i) = *(this->pElements+(i-1));
            }
            returnAux = 0;
        }
        else
        {
            if(!resizeUp(this))
            {
                for(i = this->size; i > index; i--)
                {
                    *(this->pElements+i) = *(this->pElements+(i-1));
                }
                returnAux = 0;
            }
        }
    }
    return returnAux;
}

/** \brief  Contract an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int contract(ArrayList* this,int index)
{
    int returnAux = -1;
    int i;
    if(this != NULL && index >= 0 && index < al_len(this))
    {
        for(i = index; i < al_len(this); i++)
        {
            this->pElements[i] = this->pElements[i+1];
        }
        returnAux = 0;
        this->size--;
    }
    return returnAux;
}
