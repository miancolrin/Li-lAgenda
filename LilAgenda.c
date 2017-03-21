/*#############
# LI'L AGENDA #
###############

Pequeña agenda muy básica escrita en C.

El programa nos pedirá si deseamos crear una agenda
o abrir una ya existente. Si creamos una nueva se
creará la agenda "agenda.dat" y de ya existir otra
agenda con ese nombre se borrará y perderán los datos.

La agenda nos permite almacenar un nombre de contacto
y su número de teléfono.

Programa de momento sólo para Windows, en un futuro puede
que lo adapte a UNIX.

Todas las sugerencias y modificaciones son bien recibidas.

Creado por @miancolrin

Para usarlo simplemente abirlo en un IDE y compilar.
Para que funcione correctamente debemos tener el archivo
"agenda.dat" y el ejecutable y/o el código fuente en el
mismo directorio.

P.D.: No descarto que haya bugs, pues hice el programa en
un rato libre como diversión personal :)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

#define TRUE 1
#define FALSE 0

struct datosContacto{
	char nombre[60];
	char telefono[15];
};

void crearAgenda(char nombreFichero[]);
void listarContactos(char nombreFichero[]);
void nuevoContacto(char nombreFichero[]);
void buscarContacto(char nombreFichero[]);
void exportarContactos(char nombreFichero[]);
int totalContactos(char nombreFichero[]);
void eliminarContacto(char nombreFichero[]);

int main(){
	
	//Título de la ventana
	SetConsoleTitle("Li'lAgenda");
	
	//Colores de la consola
	system("color 80");
	
	//Idioma español
	setlocale(LC_ALL, "Spanish");
	
	char opc1;
	int opc11;
	
	do{
		system("cls");
		printf("Bienvenido a Lil'Agenda\n\n");
		printf("¿Desea abrir o crear una agenda?\n");
		printf("1. Abrir agenda\n");
		printf("2. Crear agenda\n\n");
		opc1 = getch();
		
		if(opc1 == '1'){
			opc11 = 1;
			break;
		}
		else if(opc1 == '2'){
			opc11 = 2;
			break;
		}
	} while(opc1 != '1' && opc1 != '2');
	
	switch(opc11){
		
		case 1:{
			printf("Abriendo agenda");
			break;
		}
		case 2:{
			crearAgenda("agenda.dat");
			system("pause");
			break;
		}
		
	} //Cierra Switch 1
	
	//Aquí empieza "el programa en sí"
	
	char opc;
	int opcMn;
	
	do{
		
		do{
			
			system("cls");
			printf("===============MENÚ===============");
			printf("\n1. Listar contactos\n");
			printf("2. Añadir contacto\n");
			printf("3. Buscar contacto\n");
			printf("4. Eliminar contacto\n");
			printf("5. Exportar agenda\n");
			printf("\n0. SALIR\n");
			
			printf("\nOpción: ");
			
			opc = getch();
			
			if(opc == '1'){
				opcMn = 1;
			}
			else if(opc == '2'){
				opcMn = 2;
			}
			else if(opc == '3'){
				opcMn = 3;
			}
			else if(opc == '4'){
				opcMn = 4;
			}
			else if(opc == '5'){
				opcMn = 5;
			}
			else if(opc == '0'){
				opcMn = -1;
			}
			
		}while(opc != '1' && opc != '2' && opc != '3' && opc != '4' && opc != '5' && opc != '0');
		
		switch (opcMn){
			
			case 1:{
				system("cls");
				listarContactos("agenda.dat");
				system("pause");
				break;
			}
			
			case 2:{
				system("cls");
				nuevoContacto("agenda.dat");
				system("pause");
				break;
			}
			
			case 3:{
				system("cls");
				buscarContacto("agenda.dat");
				system("pause");
				break;
			}
			
			case 4:{
				system("cls");
				eliminarContacto("agenda.dat");
				system("pause");
				break;
			}
			
			case 5:{
				system("cls");
				exportarContactos("agenda.dat");
				break;
			}
			
			
			
			
		}//Cierra Switch
		
		
		
	}while(opcMn != -1); //Cierra do-while principal
	
	system("cls");
	printf("Muchas gracias por usar este software");
	printf("\nCreado por @miancolrin");
	printf("\n\nPresione cualquier tecla para salir");
	
	system("pause > null");	
	
}

int totalContactos(char nombreFichero[]){
	
	FILE *f;
	struct datosContacto contacto;
	int contador = 0;
	
	f = fopen(nombreFichero, "rb");
	
	fread(&contacto, sizeof(contacto), 1, f);
	
	while(!feof(f)){
		contador = contador + 1;
		fread(&contacto, sizeof(contacto), 1, f);
	}
	
	fclose(f);
	
	return contador;
	
}

void eliminarContacto(char nombreFichero[]){
	
	int totalC = totalContactos(nombreFichero);
	int pos, posBorrar, encontrado, contador;
	
	FILE *f; FILE *auxBorrar;
	struct datosContacto contacto;
	
	f = fopen(nombreFichero, "r+b");
	
	char telfBorrar[15];
	
	printf("Introduce número de teléfono de contacto a borrar: "); fflush(stdin);
	scanf("%s", telfBorrar);
	
	pos = 0; encontrado = FALSE;
	
	fread(&contacto, sizeof(contacto),1, f);
	
	while(!feof(f)){
		
		if(strcmp(contacto.telefono, telfBorrar) == 0){
			encontrado = TRUE;
			posBorrar = pos;
			break;
		}
		else{
			contador = contador + 1;
		}
		
		fread(&contacto, sizeof(contacto), 1, f);
		
	}
	
	if(encontrado == FALSE){
		printf("\n\nNo hay ningún contacto con ese número");
		return;
	}
	
	auxBorrar = fopen("auxBorrar.dat", "wb");
	
	rewind(f);
	
	contador = 0;
	
	fread(&contacto, sizeof(contacto), 1, f);
	while(!feof(f)){
		
		if(contador == posBorrar){
			printf("\n\nBorrando contacto...");
		}
		else{
			fwrite(&contacto, sizeof(contacto), 1, auxBorrar);
		}
		
		contador = contador + 1;
		
		fread(&contacto, sizeof(contacto), 1, f);
		
	}
	
	fclose(auxBorrar);
	fclose(f);
	
	f = fopen(nombreFichero, "wb");
	auxBorrar = fopen("auxBorrar.dat", "rb");
	
	rewind(f);
	
	fread(&contacto, sizeof(contacto), 1, auxBorrar);
	while(!feof(auxBorrar)){
		fwrite(&contacto, sizeof(contacto), 1, f);
		fread(&contacto, sizeof(contacto), 1, auxBorrar);
	}
	
	fclose(auxBorrar);
	fclose(f);
	
}

void exportarContactos(char nombreFichero[]){
	
	FILE *f;
	f = fopen(nombreFichero, "rb");
	FILE *exp;
	exp = fopen("agenda.txt", "w");
	
	struct datosContacto contacto;
	
	fputs("Exportado de agenda.dat\n\n", exp);
	
	fread(&contacto, sizeof(contacto), 1, f);
	while(!feof(f)){
		
		fputs("Nombre: ", exp);
		fputs(contacto.nombre, exp);
		fputs("\nteléfono: ", exp);
		fputs(contacto.telefono, exp);
		fputs("\n\n", exp);
		fread(&contacto, sizeof(contacto), 1, f);
		
	}
	
	printf("Exportado completo");
	
	fclose(exp);
	fclose(f);
	
}

void buscarContacto(char nombreFichero[]){
	
	FILE *f;
	f = fopen(nombreFichero, "rb");
	
	struct datosContacto contacto;
	char nombreBuscado[60];
	
	printf("Introduce nombre a buscar: "); fflush(stdin);
	gets(nombreBuscado);
	
	fread(&contacto, sizeof(contacto), 1, f);
	while(!feof(f)){
		
		if (strcmp(strlwr(contacto.nombre), strlwr(nombreBuscado)) == 0){
			printf("\n\nNombre: %s", contacto.nombre);
			printf("\nTeléfono: %s\n\n", contacto.telefono);
			fclose(f);
			return;
		}
		
		fread(&contacto, sizeof(contacto), 1, f);	
		
	}
	
	fclose(f);	
	
}

void nuevoContacto(char nombreFichero[]){
	
	FILE *f;
	f = fopen(nombreFichero, "ab");
	
	struct datosContacto contacto;
	
	printf("Nombre: "); fflush(stdin);
	gets(contacto.nombre);
	printf("\n\nTeléfono: "); fflush(stdin);
	gets(contacto.telefono);
	
	fwrite(&contacto, sizeof(contacto), 1, f);
	
	fclose(f);	
	
}

void listarContactos(char nombreFichero[]){
	
	FILE *f;
	f = fopen(nombreFichero, "rb");
	
	struct datosContacto contacto;
	
	fread(&contacto, sizeof(contacto), 1, f);
	while(!feof(f)){
		printf("\nNombre: %s", contacto.nombre);
		printf("\nTeléfono: %s\n", contacto.telefono);
		fread(&contacto, sizeof(contacto), 1, f);
	}
	
	fclose(f);
		
}

void crearAgenda(char nombreFichero[]){
	
	char opcionBorrar;
	
	do{
		system("cls");
		printf("AVISO:\n");
		printf("En caso de tener otra agenda ya guardada se perderán todos sus datos\n");
		printf("\n¿Desea continuar? (S/N)");
	
		opcionBorrar = getch();
	} while(opcionBorrar != 's' && opcionBorrar != 'S' && opcionBorrar != 'n' && opcionBorrar != 'N');
	
	
	if (opcionBorrar == 'n' || opcionBorrar == 'N'){
		return;
	}
	
	FILE *f;
	f = fopen(nombreFichero, "wb");
	
	struct datosContacto contacto;
	
	int numContactos;
	char caracter[15];
	
	if (f == NULL){
		printf("Error al crear la agenda");
		return;
	}
	
	system("cls");
	printf("¿Cuántos contactos desea añadir?: \n");
	scanf("%d", &numContactos);
	
	int contador = 0;
	
	do{
		
		printf("\n\nNombre: "); fflush(stdin);
		gets(contacto.nombre);
		printf("\nTeléfono: "); fflush(stdin);
		gets(contacto.telefono);
		fwrite(&contacto, sizeof(contacto), 1, f);
		contador = contador + 1;
		
	}while(contador != numContactos);
	
	fclose(f);
	
	system("cls");
	printf("Agenda creada con éxito");
	return;	
	
}
