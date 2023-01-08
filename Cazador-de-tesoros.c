#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

struct parametros
{
    int ancho;
    int tesoros;
    int minas;
};
struct cazador
{
    int cazadorX;
    int cazadorY;
};
// Variables globales
struct parametros modo;
struct cazador posicion;
int movimientos, tesoros;
// Funciones principales
int seccionMenu();
void mostrarMenu(char menu[10][40]);
void llenarMatriz(char matriz[10][modo.ancho]);
void imprimirMatriz(char matriz[10][modo.ancho]);
//  Modos
void modoFacil();
void modoMedio();
void modoDificil();
// Movimientos
int moverDerechaMenu(char menu[10][40], int puntero);
int moverIzquierdaMenu(char menu[10][40], int puntero);
struct cazador moverDerecha(char matriz[10][modo.ancho]);
struct cazador moverIzquierda(char matriz[10][modo.ancho]);
struct cazador moverArriba(char matriz[10][modo.ancho]);
struct cazador moverAbajo(char matriz[10][modo.ancho]);

int main()
{
    int dificultad = 0, opcionMenu = seccionMenu();

    while (opcionMenu != 2)
    {
        if (opcionMenu == 1) // Jugar
        {
            dificultad = // seccionMenu();

                if (dificultad == 1)
                    modoFacil();

            if (dificultad == 2)
                modoMedio();

            if (dificultad == 3)
                modoDificil();
        
        }
        if (opcionMenu == 2) // Salir
            break;
    }
    printf("Gracias por jugar :D");
    return 0;
}
// Funciones principales
int seccionMenu()
{
    int X, Y, opcion, puntero = 8; // 8, 26
    char tecla;
    char menu[10][40] = {"*--------------------------------------*",
                         "|          CAZADOR DE TESOROS          |",
                         "|--------------------------------------|",
                         "|       >Jugar             Salir       |",
                         "|--------------------------------------|",
                         "|               REGISTRO               |",
                         "|--------------------------------------|",
                         "| Movimentos ultima partida: %d        |",
                         "| Menor cantidad de movimientos: %d    |",
                         "*--------------------------------------*"}; // Falta agregar record de movimientos y movimientos ultima partida
    mostrarMenu(menu);
    do
    {
        tecla = toupper(getch());
        fflush(stdin);

        if (tecla == 'A' && puntero == 26)
            puntero = moverIzquierdaMenu(menu, puntero);

        if (tecla == 'D' && puntero == 8)
            puntero = moverDerechaMenu(menu, puntero);

    } while (tecla != 13);

    if (puntero == 8)
        opcion = 1;
    if (puntero == 26)
        opcion = 2;

    return opcion;
}
void mostrarMenu(char menu[10][40])
{
    int X, Y;
    system("cls");
    for (Y = 0; Y < 10; Y++)
    {
        for (X = 0; X < 40; X++)
            printf("%c", menu[Y][X]);
        printf("\n");
    }
}
void llenarMatriz(char matriz[10][modo.ancho])
{
    srand(time(NULL));
    // Llenado con espacios
    int X, Y, i;
    for (Y = 0; Y < 10; Y++)
    {
        for (X = 0; X < modo.ancho; X++)
            matriz[Y][X] = ' ';
    }

    // Posicion del cazador
    matriz[0][0] = '*';

    // Llenado con tesoros
    for (i = 0; i < modo.tesoros; i++)
    {
        do
        {
            X = rand() % modo.ancho;
            Y = rand() % 10;
        } while (matriz[Y][X] != ' ');
        matriz[Y][X] = 'T';
    }

    // Llenado con minas
    for (i = 0; i < modo.minas; i++)
    {
        do
        {
            X = rand() % modo.ancho;
            Y = rand() % 10;
        } while (matriz[Y][X] != ' ');
        matriz[Y][X] = 'M';
    }
}
void imprimirMatriz(char matriz[10][modo.ancho])
{
    int X, Y;
    printf("Movimientos: %d\t   Tesoros: %d\n", movimientos, tesoros);
    for (Y = 0; Y < 10; Y++)
    {
        for (X = 0; X < modo.ancho; X++)
            printf("[%c]", matriz[Y][X]);
        printf("\n");
    }
}
// Modos
void modoFacil()
{
    system("cls");
    modo.ancho = 10;
    modo.tesoros = 5;
    modo.minas = 10;
    posicion.cazadorX = 0;
    posicion.cazadorY = 0;
    movimientos = 0;
    tesoros = modo.tesoros;

    char matriz[10][modo.ancho];
    char tecla;

    llenarMatriz(matriz);
    system("cls");
    imprimirMatriz(matriz);
    do
    {
        do
        {
            tecla = toupper(getch());
            fflush(stdin);
        } while (tecla == 'W' && posicion.cazadorY == 0 ||
                 tecla == 'A' && posicion.cazadorX == 0 ||
                 tecla == 'S' && posicion.cazadorY == 9 ||
                 tecla == 'D' && posicion.cazadorX == 9);
        switch (tecla)
        {
        case 'W':
            posicion = moverArriba(matriz);
            break;
        case 'A':
            posicion = moverIzquierda(matriz);
            break;
        case 'S':
            posicion = moverAbajo(matriz);
            break;
        case 'D':
            posicion = moverDerecha(matriz);
            break;
        }
        system("cls");
        imprimirMatriz(matriz);
    } while (tesoros != 0);
}
void modoMedio()
{
    system("cls");
    modo.ancho = 15;
    modo.tesoros = 10;
    modo.minas = 20;

    char matriz[10][modo.ancho];

    llenarMatriz(matriz);
    imprimirMatriz(matriz);
    getch();
}
void modoDificil()
{
    system("cls");
    modo.ancho = 15;
    modo.tesoros = 20;
    modo.minas = 50;

    char matriz[10][modo.ancho];

    llenarMatriz(matriz);
    imprimirMatriz(matriz);
    getch();
}
// Movimientos
int moverDerechaMenu(char menu[10][40], int puntero)
{
    menu[3][puntero] = ' ';
    puntero += 18;
    menu[3][puntero] = '>';
    mostrarMenu(menu);
    return puntero;
}
int moverIzquierdaMenu(char menu[10][40], int puntero)
{
    menu[3][puntero] = ' ';
    puntero -= 18;
    menu[3][puntero] = '>';
    mostrarMenu(menu);
    return puntero;
}
struct cazador moverArriba(char matriz[10][modo.ancho])
{
    movimientos++;
    matriz[posicion.cazadorY][posicion.cazadorX] = ' ';
    if (matriz[posicion.cazadorY - 1][posicion.cazadorX] == 'M')
    {
        matriz[posicion.cazadorY - 1][posicion.cazadorX] = ' ';
        posicion.cazadorX = 0;
        posicion.cazadorY = 0;
        matriz[0][0] = '*';
        return posicion;
    }
    if (matriz[posicion.cazadorY - 1][posicion.cazadorX] == 'T')
        tesoros--;
    matriz[posicion.cazadorY - 1][posicion.cazadorX] = '*';
    posicion.cazadorY--;
    return posicion;
}
struct cazador moverIzquierda(char matriz[10][modo.ancho])
{
    movimientos++;
    matriz[posicion.cazadorY][posicion.cazadorX] = ' ';
    if (matriz[posicion.cazadorY][posicion.cazadorX - 1] == 'M')
    {
        matriz[posicion.cazadorY][posicion.cazadorX - 1] = ' ';
        posicion.cazadorX = 0;
        posicion.cazadorY = 0;
        matriz[0][0] = '*';
        return posicion;
    }
    if (matriz[posicion.cazadorY][posicion.cazadorX - 1] == 'T')
        tesoros--;
    matriz[posicion.cazadorY][posicion.cazadorX - 1] = '*';
    posicion.cazadorX--;
    return posicion;
}
struct cazador moverAbajo(char matriz[10][modo.ancho])
{
    movimientos++;
    matriz[posicion.cazadorY][posicion.cazadorX] = ' ';
    if (matriz[posicion.cazadorY + 1][posicion.cazadorX] == 'M')
    {
        matriz[posicion.cazadorY + 1][posicion.cazadorX] = ' ';
        posicion.cazadorX = 0;
        posicion.cazadorY = 0;
        matriz[0][0] = '*';
        return posicion;
    }
    if (matriz[posicion.cazadorY + 1][posicion.cazadorX] == 'T')
        tesoros--;
    matriz[posicion.cazadorY + 1][posicion.cazadorX] = '*';
    posicion.cazadorY++;
    return posicion;
}
struct cazador moverDerecha(char matriz[10][modo.ancho])
{
    movimientos++;
    matriz[posicion.cazadorY][posicion.cazadorX] = ' ';
    if (matriz[posicion.cazadorY][posicion.cazadorX + 1] == 'M')
    {
        matriz[posicion.cazadorY][posicion.cazadorX + 1] = ' ';
        posicion.cazadorX = 0;
        posicion.cazadorY = 0;
        matriz[0][0] = '*';
        return posicion;
    }
    if (matriz[posicion.cazadorY][posicion.cazadorX + 1] == 'T')
        tesoros--;
    matriz[posicion.cazadorY][posicion.cazadorX + 1] = '*';
    posicion.cazadorX++;
    return posicion;
}
