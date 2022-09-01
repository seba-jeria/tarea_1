#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct{
    char tipo_item[30];
    char nombre_obj[30];
    int nivel_o_cantidad;
    char tipo_personaje[30];
}Item;

//Funcion para leer el k-esimo elemento de un string (separado por comas)
char *get_csv_field(char *linea, int indice)
{
    char *campo = (char *) malloc(100 * sizeof(char *)); // Guarda el string a retornar
    int i = 0; // Recorre la linea
    int k = 0; // Cuenta las comas
    int n = 0; // Recorre el campo
    bool comillas = false;

    while(linea[i] != '\0'){
        if(linea[i] == '\"'){
            comillas = !comillas;
        }

        if(k == indice){
            if(linea[i] != '\"'){
                campo[n] = linea[i];
                n++;
            }
        }

        i++;

        if(linea[i] == ',' && !comillas){
            k++;
            i++;
        }

        if(k > indice || linea[i] == '\0' || linea[i] == '\n'){
            campo[n] = '\0';
            return campo;
        }
    }

    return NULL;
}


Item* buscarItem(char*, char*);
Item* buscarPersonajes(List*);
List* datos;

int main(){
    int num=0, ing_niv_can;
    char ing_tipo[30], ing_nombre_obj[30], ing_personaje[30];
    bool flag=true;
    printf("1. Importar un csv\n");
    printf("2. Exportar un csv\n");
    printf("3. Agregar item a un personaje\n");
    printf("4. Mostrar item equipables de un personaje\n");
    printf("5. Mostrar item consumibles de un personaje\n");
    printf("6. Eliminar item de un personaje\n");
    printf("7. Eliminar item de todos los personajes\n");
    printf("8. Mostrar nombres de los personajes\n");
    printf("9. Mostrar todos los items\n");
    printf("0. Salir\n");
    printf("Introdusca un numero: ");
    scanf("%d", &num);
    while(num<0||num>9){
        printf("Introduzca un numero valido: ");
        scanf("%d", &num);
    }
    Item* I=(Item*)malloc(sizeof(Item));
    datos=createList();
    List* listapersonajes=createList();
    while (flag){
        switch (num){
            case 0:{
                printf("Programa finalizado");
                flag=false;
                break;
            }
            case 1:{
                /*List* personaje=createList();*/
                /*printf("Ingrese el nombre del arhivo: ");*/
                /*scanf("%c", &nombre_archivo);*/
                    // Se abre el archivo de mundos csv en modo lectura "r"
                /*scanf("%[^\n]", nombre_archivo);*/
                int k=0;
                FILE *fp = fopen ("Items.csv", "r");
                // Cadena para guardar la linea completa del archivo csv
                char linea[1024];
                fgets (linea, 1023, fp);
                while (fgets (linea, 1023, fp) != NULL) { // Se lee la linea 

                    strcpy(I->tipo_item, get_csv_field(linea, 0)); // Se obtiene el tipo de objeto
                    strcpy(I->nombre_obj, get_csv_field(linea, 1)); //se obtiene el nombre del objeto
                    I->nivel_o_cantidad = atoi(get_csv_field(linea, 2));//se obtiene el nivel o la cantidad del objeto
                    strcpy(I->tipo_personaje, get_csv_field(linea, 3)); //se obtiene el personaj
                    pushBack(datos,I);
                    I=(Item*)malloc(sizeof(Item));
                    k++; 
                    if(k==99) break;
                }
                break;
            }
            case 3:{
                printf("Ingrese tipo: ");
                fflush(stdin);
                scanf("%[^\n]", ing_tipo);
                printf("Ingrese nombre del objeto: ");
                fflush(stdin);
                scanf("%[^\n]", ing_nombre_obj);
                printf("Ingrese nivel o cantidad: ");
                fflush(stdin);
                scanf("%d", &ing_niv_can);
                printf("Ingrese personaje: ");
                fflush(stdin);
                scanf("%[^\n]", ing_personaje);

                I = buscarItem(ing_nombre_obj, ing_personaje);
                if (I == NULL || (strcmp(I->tipo_item, "Equipable") == 0)) {
                    I = (Item*) malloc(sizeof(Item));
                    strcpy(I->tipo_item, ing_tipo);
                    strcpy(I->nombre_obj, ing_nombre_obj);
                    I->nivel_o_cantidad = ing_niv_can;
                    strcpy(I->tipo_personaje, ing_personaje);
                    pushBack(datos, I);
                }
                else
                    I->nivel_o_cantidad=I->nivel_o_cantidad+ing_niv_can;
                break;
            }
            case 8:{
                int cont;
                listapersonajes = buscarPersonajes(listapersonajes);
                /*listaarmas = buscarArmas(listaarmas);
                Item* aux2 = firstList(listapersonajes);
                Item* d = firstList(datos);
                Item* armas=firstList(listaarmas);
                while(aux2!=NULL){
                    printf("%s", aux2->tipo_personaje);
                    cont=0;
                    while(d!=NULL){
                        if(strcmp(d->tipo_personaje, aux2->tipo_personaje) == 0 && strcmp(d->tipo_item, "Consumible")==0)
                            printf("%s", d->nombre_obj);
                        else{
                        while(armas!=NULL){
                            if (strcmp(armas->nombre_obj, d->nombre_obj)==0)
                                cont++;
                            d=nextList(datos);
                        }
                        printf("%s %d", armas->nombre_obj, cont);
                        armas=nextList(listarmas);
                        }
                    }
                    d=firstList(datos);
                    aux2=nextList(listapersonajes);
                }*/  
                break;
            }
            case 9:{
                Item* aux = firstList(datos);
                while(aux!=NULL){
                    printf("%s / %s / %d\n",aux->tipo_item, aux->nombre_obj, aux->nivel_o_cantidad);
                    aux=nextList(datos);
                }
                break;
            }
        }
        if (num==0){
            break;
        }
        printf("Ingrese otro valor: ");
        scanf("%d", &num);
        while(num<0||num>9){
            printf("Introdusca un numero valido: ");
            scanf("%d", &num);
        }
    }
    return 0;
}

Item* buscarItem(char* nombre_obj, char* personaje){
    Item* I = firstList(datos);
    while (I != NULL){
        if(strcmp(nombre_obj, I->nombre_obj) == 0 && strcmp(personaje, I->tipo_personaje) == 0)
            return I;
        I = nextList(datos);
    }
    return NULL;
}

Item* buscarPersonajes(List* listapersonajes){
    int cont=0;
    Item* I=firstList(datos);
    Item* P=firstList(listapersonajes);
    while (I!=NULL){
        if (P == NULL){
            pushBack(listapersonajes, I->tipo_personaje);
        }
        while (P!=NULL){
            P=firstList(listapersonajes);
            if (strcmp(I->tipo_personaje, P->tipo_personaje) != 0){
                P=nextList(listapersonajes);
            }
            else{
                P=nextList(listapersonajes);
            }    
        }
        I=nextList(datos);
    }
    return listapersonajes;

}