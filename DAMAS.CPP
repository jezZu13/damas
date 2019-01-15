//Programa realizado por:
	//MANUEL VICENTE ALMAGRO AREVALO
	//JESUS ROJAS CABRERA

#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <string.h>
#include <libre.h>
#include <dos.h>
#include <texto.h>
#include <raton1.h>
#include <stdlib.h>

class Sonidos{
   int frecuencia;

   public:

   Sonidos(){
      frecuencia=1000;
   }

   Sonidos(const int hz){
      frecuencia=hz;
   }

   void cargaBarra();
   void sonar();
   void ganar();
   void coronar();

};

void Sonidos::cargaBarra(){
   sound(frecuencia);
   frecuencia=frecuencia+2;
}

void Sonidos::sonar(){
   sound(frecuencia);
   delay(50);
   nosound();
}

void Sonidos::ganar(){
   sound(frecuencia);
   delay(100);
   nosound();
   delay(100);

   sound(frecuencia-500);
   delay(100);
   nosound();
   delay(100);

   sound(frecuencia+1000);
   delay(100);
   nosound();
}

void Sonidos::coronar(){
   sound(frecuencia);
   delay(50);
   nosound();
   delay(100);
   sound(frecuencia);
   delay(50);
   nosound();
}

struct jugadores{
   char nombre[25];
   int fichas;
}player[2];

void rellenarCasillas();
void rellenarMatriz();
void colocarFichasEnMatriz();
void pintarFichasEnTablero();
int pedirPosicion();
void moverFicha();
void cambioTurno();
void limpiar();
void sacarDama();
void recontarFichas();
void movPeonJ1(int,int);
void movDamaJ1(int,int);
void movPeonJ2(int,int);
void movDamaJ2(int,int);
void pintarInfoEjes();
void saltoMultiplePeonJ1();
void saltoMultiplePeonJ2();
void saltoMultipleDamaJ1();
void saltoMultipleDamaJ2();
void pintarBotones();
void guardarPartida();
void CargarBarra();
void dibujarMenu();
void dibujarTablero();
void CargarBarra();
void recargarPartida();
int comprobarAhogo();

/**********VARIABLES GLOBALES**********/
int matriz[8][8];//Matriz principal del juego.
int i=NULL, j=NULL;//Para definir las posiciones en la matriz.
int finpartida=1;//Variable para determinar el fin de la partida.

//Las siguientes tres variables (turno, cambio y finjugada) se emplean para el turno del jugador.
int turno=0;//Turno de jugador.Se usara para cambiarnos de posicion en el vector player.
int cambio=1;//Para provocar o no el cambio de turno.
int finjugada=1;//El ciclo de la jugada termina (valor 0), aunque puede que el turno no haya variado.

int opcion=0;//Para permanecer o salir del bucle que pinta el men£ principal.
int finprograma=1;//Se utiliza para finalizar la ejecuci¢n del bucle principal y salirnos del programa.
int comprobarRecarga=1;

//Las siguientes cuatro variables se emplean para mostrar las estadisticas al final de la partida.
int movimientoj1=0; //Variable para contar los movimientos realizados por el jugador 1
int movimientoj2=0; //Variable para contar los movimientos realizados por el jugador 2
int comidaj1=0; //Variable para contar las fichas comidas por el jugador 1
int comidaj2=0; //Variable para contar las fichas comidas por el jugador 1

/**********COMIENZO DEL MAIN**********/
void main(){

   //Inicializar graficos:
   int gdriver = DETECT, gmode, errorcode;
   initgraph(&gdriver, &gmode, "T:\\BGI");

   mver();//Visualizamos el cursor del raton.
   msituar(1,1,1);//Situar el raton en un punto de la pantalla.

   while(finprograma==1){

      while(opcion==0){
	   setcolor(WHITE);
	   dibujarMenu();//Dibuja el menu con graficos.
      }
      setcolor(WHITE);

      mver();
      msituar(1,1,1);

      //Establecemos los valores por defecto de las varibles globales del juego:
      finpartida=1;
      i=NULL;
      j=NULL;
      cambio=1;
      finjugada=1;
      opcion=0;
      //Fin reseteo de las globales.

      cleardevice();//Comenzamos el programa limpiando la pantalla.

      drawpanel(8,8,40,160,20);//filas, columnas, dimension, izquierda, arriba.

      rellenarCasillas();//Para rellenar graficamente las casillas.

      if(comprobarRecarga==1){//Si la partida NO es nueva, sino recargada, NO entra en este bucle.

	 rellenarMatriz();//Para rellenar la matriz (motor) del juego.
	 //Para resetear las estadisticas:
	 movimientoj1=0;
	 movimientoj2=0;
	 comidaj1=0;
	 comidaj2=0;

      }

      pintarInfoEjes();

      if(comprobarRecarga==1){//Si la partida NO es nueva, sino recargada, NO entra en este bucle.

	 colocarFichasEnMatriz();//Definir en la matriz (motor) la colocacion de las fichas.

      }

      pintarFichasEnTablero();//Segun los valores de la matriz, se pintan con graficos las fichas en pantalla.
      pintarBotones();//Pintamos con graficos en pantalla los botones de "guardar y salir" y "salir".


      //A partir de este punto es donde comienza en s¡ el propio juego:
      if(comprobarRecarga==1){//Si la partida NO es nueva, sino recargada, NO entra en este bucle.

	 turno=0;//Empieza a mover el primer jugador.

      }

      gotoxy(1,23);
      printf("Turno %s",player[turno].nombre);

      while(finpartida==1){//Bucle utilizado para determinar cuando finaliza la partida en curso.

	 if(comprobarAhogo()==1){//Si "comprobarAhogo" vale 0, significa que el jugador al que le corresponde mover est  bloqueado y por lo tanto pierde la partida y se finaliza.

	    moverFicha();//Funcion que solicita al jugador mover ficha. Es la funcion mas compleja del juego, la cual llama a su vez a otras funciones.

	    sacarDama();//Utilizada, tras finalizar el movimiento del jugador, si ha llegado "al final" del tablero con alguna ficha. En ese caso el peon correspondiente se convierte en dama.

	    msituar(1,140,200);//Volvemos a situar el raton en un punto de la pantalla para que no moleste a la hora de repintar las fichas

	    pintarFichasEnTablero();//Repintamos las fichas en el tablero tras el ultimo movimiento.

	    limpiar();//Unicamente limpia el texto escrito en pantalla.

	    cambioTurno();//Para determinar si se cambia o no de turno.

	    recontarFichas();//Hace un recuento de las fichas que les queda a ambos jugadores. Si alguno de ellos ya no tiene fichas, FIN DE PARTIDA.

	 }

      }//Fin partida

      //PINTAMOS EL RANKING AL FINALIZAR LA PARTIDA
      mocultar();
      cleardevice();
      gotoxy(23,10);
      printf("Movimientos realizados por %s: %d",player[0].nombre,movimientoj1);
      gotoxy(23,12);
      printf("Movimientos realizados por %s: %d",player[1].nombre,movimientoj2);
      gotoxy(23,14);
      printf("Capturas realizadas por %s: %d",player[0].nombre,comidaj1);
      gotoxy(23,16);
      printf("Capturas realizadas por %s: %d",player[1].nombre,comidaj2);
      fflush(stdin);
      getch();
      mver();
      msituar(1,1,1);

   }//Fin del programa
}//Fin del main

/*****************************/
/**********FUNCIONES**********/
/*****************************/

int pedirPosicion(){
//El objetivo de esta funcion es que el jugador unicamente pueda seleccionar una de las 64 (tablero 8x8) posiciones validas del tablero pintado en pantalla.
//Saldr  del bucle principal unicamente si ha hecho click con el rat¢n en alguna de las posiciones validas (recuadros del tablero) de pantalla.

   int left=160, top=20, right=200, bottom=60; //Se utilizan para delimitar cada uno de los recuadritos de la matriz grafica.
   int salir=1;
   int sum=40;//Se utiliza para programar los limites de la matriz grafica.
   int retrasar=200;//Este valor se emplea en el delay para evitar que se realice m s de un click cuando se clickea con el raton.

   while(salir==1){
      /**********PRIMERA FILA**********/
      if((mclick()==1)&&(inbox(left+(sum*0),top+(sum*0),right+(sum*0),bottom+(sum*0),mposx(1),mposy(1))==1)){
	 i=0;
	 j=0;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*1),top+(sum*0),right+(sum*1),bottom+(sum*0),mposx(1),mposy(1))==1)){
	 i=0;
	 j=1;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*2),top+(sum*0),right+(sum*2),bottom+(sum*0),mposx(1),mposy(1))==1)){
	 i=0;
	 j=2;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*3),top+(sum*0),right+(sum*3),bottom+(sum*0),mposx(1),mposy(1))==1)){
	 i=0;
	 j=3;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*4),top+(sum*0),right+(sum*4),bottom+(sum*0),mposx(1),mposy(1))==1)){
	 i=0;
	 j=4;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*5),top+(sum*0),right+(sum*5),bottom+(sum*0),mposx(1),mposy(1))==1)){
	 i=0;
	 j=5;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*6),top+(sum*0),right+(sum*6),bottom+(sum*0),mposx(1),mposy(1))==1)){
	 i=0;
	 j=6;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*7),top+(sum*0),right+(sum*7),bottom+(sum*0),mposx(1),mposy(1))==1)){
	 i=0;
	 j=7;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      /**********SEGUNDA FILA**********/
      if((mclick()==1)&&(inbox(left+(sum*0),top+(sum*1),right+(sum*0),bottom+(sum*1),mposx(1),mposy(1))==1)){
	 i=1;
	 j=0;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*1),top+(sum*1),right+(sum*1),bottom+(sum*1),mposx(1),mposy(1))==1)){
	 i=1;
	 j=1;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*2),top+(sum*1),right+(sum*2),bottom+(sum*1),mposx(1),mposy(1))==1)){
	 i=1;
	 j=2;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*3),top+(sum*1),right+(sum*3),bottom+(sum*1),mposx(1),mposy(1))==1)){
	 i=1;
	 j=3;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*4),top+(sum*1),right+(sum*4),bottom+(sum*1),mposx(1),mposy(1))==1)){
	 i=1;
	 j=4;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*5),top+(sum*1),right+(sum*5),bottom+(sum*1),mposx(1),mposy(1))==1)){
	 i=1;
	 j=5;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*6),top+(sum*1),right+(sum*6),bottom+(sum*1),mposx(1),mposy(1))==1)){
	 i=1;
	 j=6;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*7),top+(sum*1),right+(sum*7),bottom+(sum*1),mposx(1),mposy(1))==1)){
	 i=1;
	 j=7;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      /**********TERCERA FILA**********/
      if((mclick()==1)&&(inbox(left+(sum*0),top+(sum*2),right+(sum*0),bottom+(sum*2),mposx(1),mposy(1))==1)){
	 i=2;
	 j=0;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*1),top+(sum*2),right+(sum*1),bottom+(sum*2),mposx(1),mposy(1))==1)){
	 i=2;
	 j=1;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*2),top+(sum*2),right+(sum*2),bottom+(sum*2),mposx(1),mposy(1))==1)){
	 i=2;
	 j=2;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*3),top+(sum*2),right+(sum*3),bottom+(sum*2),mposx(1),mposy(1))==1)){
	 i=2;
	 j=3;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*4),top+(sum*2),right+(sum*4),bottom+(sum*2),mposx(1),mposy(1))==1)){
	 i=2;
	 j=4;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*5),top+(sum*2),right+(sum*5),bottom+(sum*2),mposx(1),mposy(1))==1)){
	 i=2;
	 j=5;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*6),top+(sum*2),right+(sum*6),bottom+(sum*2),mposx(1),mposy(1))==1)){
	 i=2;
	 j=6;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*7),top+(sum*2),right+(sum*7),bottom+(sum*2),mposx(1),mposy(1))==1)){
	 i=2;
	 j=7;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      /**********CUARTA FILA**********/
      if((mclick()==1)&&(inbox(left+(sum*0),top+(sum*3),right+(sum*0),bottom+(sum*3),mposx(1),mposy(1))==1)){
	 i=3;
	 j=0;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*1),top+(sum*3),right+(sum*1),bottom+(sum*3),mposx(1),mposy(1))==1)){
	 i=3;
	 j=1;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*2),top+(sum*3),right+(sum*2),bottom+(sum*3),mposx(1),mposy(1))==1)){
	 i=3;
	 j=2;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*3),top+(sum*3),right+(sum*3),bottom+(sum*3),mposx(1),mposy(1))==1)){
	 i=3;
	 j=3;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*4),top+(sum*3),right+(sum*4),bottom+(sum*3),mposx(1),mposy(1))==1)){
	 i=3;
	 j=4;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*5),top+(sum*3),right+(sum*5),bottom+(sum*3),mposx(1),mposy(1))==1)){
	 i=3;
	 j=5;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*6),top+(sum*3),right+(sum*6),bottom+(sum*3),mposx(1),mposy(1))==1)){
	 i=3;
	 j=6;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*7),top+(sum*3),right+(sum*7),bottom+(sum*3),mposx(1),mposy(1))==1)){
	 i=3;
	 j=7;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      /**********QUINTA FILA**********/
      if((mclick()==1)&&(inbox(left+(sum*0),top+(sum*4),right+(sum*0),bottom+(sum*4),mposx(1),mposy(1))==1)){
	 i=4;
	 j=0;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*1),top+(sum*4),right+(sum*1),bottom+(sum*4),mposx(1),mposy(1))==1)){
	 i=4;
	 j=1;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*2),top+(sum*4),right+(sum*2),bottom+(sum*4),mposx(1),mposy(1))==1)){
	 i=4;
	 j=2;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*3),top+(sum*4),right+(sum*3),bottom+(sum*4),mposx(1),mposy(1))==1)){
	 i=4;
	 j=3;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*4),top+(sum*4),right+(sum*4),bottom+(sum*4),mposx(1),mposy(1))==1)){
	 i=4;
	 j=4;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*5),top+(sum*4),right+(sum*5),bottom+(sum*4),mposx(1),mposy(1))==1)){
	 i=4;
	 j=5;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*6),top+(sum*4),right+(sum*6),bottom+(sum*4),mposx(1),mposy(1))==1)){
	 i=4;
	 j=6;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*7),top+(sum*4),right+(sum*7),bottom+(sum*4),mposx(1),mposy(1))==1)){
	 i=4;
	 j=7;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }
      /**********SEXTA FILA**********/
      if((mclick()==1)&&(inbox(left+(sum*0),top+(sum*5),right+(sum*0),bottom+(sum*5),mposx(1),mposy(1))==1)){
	 i=5;
	 j=0;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*1),top+(sum*5),right+(sum*1),bottom+(sum*5),mposx(1),mposy(1))==1)){
	 i=5;
	 j=1;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*2),top+(sum*5),right+(sum*2),bottom+(sum*5),mposx(1),mposy(1))==1)){
	 i=5;
	 j=2;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*3),top+(sum*5),right+(sum*3),bottom+(sum*5),mposx(1),mposy(1))==1)){
	 i=5;
	 j=3;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*4),top+(sum*5),right+(sum*4),bottom+(sum*5),mposx(1),mposy(1))==1)){
	 i=5;
	 j=4;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*5),top+(sum*5),right+(sum*5),bottom+(sum*5),mposx(1),mposy(1))==1)){
	 i=5;
	 j=5;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*6),top+(sum*5),right+(sum*6),bottom+(sum*5),mposx(1),mposy(1))==1)){
	 i=5;
	 j=6;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*7),top+(sum*5),right+(sum*7),bottom+(sum*5),mposx(1),mposy(1))==1)){
	 i=5;
	 j=7;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      /**********SEPTIMA FILA**********/
      if((mclick()==1)&&(inbox(left+(sum*0),top+(sum*6),right+(sum*0),bottom+(sum*6),mposx(1),mposy(1))==1)){
	 i=6;
	 j=0;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*1),top+(sum*6),right+(sum*1),bottom+(sum*6),mposx(1),mposy(1))==1)){
	 i=6;
	 j=1;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*2),top+(sum*6),right+(sum*2),bottom+(sum*6),mposx(1),mposy(1))==1)){
	 i=6;
	 j=2;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*3),top+(sum*6),right+(sum*3),bottom+(sum*6),mposx(1),mposy(1))==1)){
	 i=6;
	 j=3;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*4),top+(sum*6),right+(sum*4),bottom+(sum*6),mposx(1),mposy(1))==1)){
	 i=6;
	 j=4;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*5),top+(sum*6),right+(sum*5),bottom+(sum*6),mposx(1),mposy(1))==1)){
	 i=6;
	 j=5;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*6),top+(sum*6),right+(sum*6),bottom+(sum*6),mposx(1),mposy(1))==1)){
	 i=6;
	 j=6;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*7),top+(sum*6),right+(sum*7),bottom+(sum*6),mposx(1),mposy(1))==1)){
	 i=6;
	 j=7;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      /**********OCTAVA FILA**********/
      if((mclick()==1)&&(inbox(left+(sum*0),top+(sum*7),right+(sum*0),bottom+(sum*7),mposx(1),mposy(1))==1)){
	 i=7;
	 j=0;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*1),top+(sum*7),right+(sum*1),bottom+(sum*7),mposx(1),mposy(1))==1)){
	 i=7;
	 j=1;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*2),top+(sum*7),right+(sum*2),bottom+(sum*7),mposx(1),mposy(1))==1)){
	 i=7;
	 j=2;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*3),top+(sum*7),right+(sum*3),bottom+(sum*7),mposx(1),mposy(1))==1)){
	 i=7;
	 j=3;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*4),top+(sum*7),right+(sum*4),bottom+(sum*7),mposx(1),mposy(1))==1)){
	 i=7;
	 j=4;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*5),top+(sum*7),right+(sum*5),bottom+(sum*7),mposx(1),mposy(1))==1)){
	 i=7;
	 j=5;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*6),top+(sum*7),right+(sum*6),bottom+(sum*7),mposx(1),mposy(1))==1)){
	 i=7;
	 j=6;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      if((mclick()==1)&&(inbox(left+(sum*7),top+(sum*7),right+(sum*7),bottom+(sum*7),mposx(1),mposy(1))==1)){
	 i=7;
	 j=7;
	 salir=0;
	 delay(retrasar);
	 return(0);
      }

      //Si se produce click con el boton derecho del raton en cualquier parte de la pantalla, salimos del bucle principal, y por tanto de la funcion sin valores i y j.
      //Se emplea para permitir al jugador "rectificar" su movimiento.
      if(mclick()==2){
	 salir=0;
	 delay(retrasar);
	 return(1);
      }

      //Guardar y salir:
      if( (mclick()==1) && (inbox(10,25,100,50,mposx(1),mposy(1))==1) ){
	 salir=0;
	 guardarPartida();//Funcion que guarda la partida(contenido de la matriz).
	 cambio=0;
	 finjugada=0;
	 finpartida=0;
	 comprobarRecarga=1;
	 delay(retrasar);
	 fflush(stdin);
	 return(0);
      }


      //Salir sin guardar:
      if( (mclick()==1) && (inbox(10,75,100,100,mposx(1),mposy(1))==1) ){
	 salir=0;
	 cambio=0;
	 finjugada=0;
	 finpartida=0;
	 comprobarRecarga=1;
	 delay(retrasar);
	 fflush(stdin);
	 return(0);
      }

   }//Fin del bucle

   return(99);//No tiene ning£n uso. El compilador requiere de un return fuera del if.
}

void rellenarCasillas(){
//Esta funcion se emplea unicamente para rellenar el color del fondo de las casillas.
   int posX=161, posY=21;//para las posiciones de cada recuadro.
   int ilocal=0, jlocal=0;//para recorrer los dos bucles anidados.

   while(ilocal<8){
      while(jlocal<8){
	 if((jlocal+ilocal)%2==0){
	     //Si j+i es par, le corresponde ser blanca a la casilla, y si no es par no se hace nada (se queda en negro).
	     setcolor(WHITE);
	     setfillstyle(SOLID_FILL,WHITE);
	     floodfill(posX,posY,WHITE);
	 }
	 posX=posX+40;
	 jlocal++;
      }
      posX=161;
      jlocal=0;
      posY=posY+40;
      ilocal++;
   }
}

void rellenarMatriz(){
//Con esta funcion rellenamos la matriz determinando las casillas validas (0) y las no validas (1).
//Aqu¡ aun no se rellena la matriz con las fichas.

   int ilocal=0,jlocal=0;//para recorrer los dos bucles anidados.

   while(ilocal<8){
      while(jlocal<8){
	 if((jlocal+ilocal)%2==0){
	    matriz[ilocal][jlocal]=1;//Se corresponde con las casillas claras, a las cuales no se puede mover la ficha.
	 }
	    else{
	       matriz[ilocal][jlocal]=0;//Son las casillas oscuras, las cuales en un principio estan vacias. Es donde se desarrolla el juego.
	    }
	 jlocal++;
      }
      jlocal=0;
      ilocal++;
   }
}

void colocarFichasEnMatriz(){
//Ahora s¡ posicionamos en la matriz los valores correspondientes con cada ficha.

   int ilocal=0,jlocal=0; //para recorrer los bucles anidados.

   //Con este bucle rellenamos en la matriz(motor) las fichas con valor 3, que ser n los peones oscuros (rojos).
   while(ilocal<8){
      while(jlocal<8){
	 if((ilocal<3)&&(matriz[ilocal][jlocal]==0)){
	    matriz[ilocal][jlocal]=3;
	 }
	 jlocal++;
      }
      jlocal=0;
      ilocal++;
   }

   //Reinicializamos a 0 la i y la j.
   ilocal=0;
   jlocal=0;

   //Con este bucle rellenamos en la matriz(motor) las fichas con valor 2, que ser n los peones claros (verdes).
   while(ilocal<8){
      while(jlocal<8){
	 if((ilocal>4)&&(matriz[ilocal][jlocal]==0)){
	    matriz[ilocal][jlocal]=2;
	 }
	 jlocal++;
      }
      jlocal=0;
      ilocal++;
   }
}

void pintarFichasEnTablero(){
//Funcion que pinta GRAFICAMENTE las FICHAS en la MATRIZ GRAFICA.

   int posX=180, posY=40;
   int ilocal=0, jlocal=0;

   while(ilocal<8){
      while(jlocal<8){
	 if(matriz[ilocal][jlocal]==3){
	      //Pintamos el PEON oscuro
	       setcolor(LIGHTRED);
	       setfillstyle(SOLID_FILL,LIGHTRED);
	       fillellipse(posX,posY,13,13);
	 }

	 if(matriz[ilocal][jlocal]==6){
	      //Pintamos la DAMA oscura
	       setcolor(LIGHTRED);
	       setfillstyle(SOLID_FILL,LIGHTRED);
	       fillellipse(posX,posY,13,13);
	       setcolor(BLACK);
	       setfillstyle(SOLID_FILL,YELLOW);
	       fillellipse(posX,posY,5,5);
	 }

	 if(matriz[ilocal][jlocal]==2){
	       //Pintamos el PEON claro
	       setcolor(LIGHTGREEN);
	       setfillstyle(SOLID_FILL,LIGHTGREEN);
	       fillellipse(posX,posY,13,13);
	 }

	 if(matriz[ilocal][jlocal]==4){
	       //Pintamos la DAMA clara
	       setcolor(LIGHTGREEN);
	       setfillstyle(SOLID_FILL,LIGHTGREEN);
	       fillellipse(posX,posY,13,13);
	       setcolor(BLACK);
	       setfillstyle(SOLID_FILL,YELLOW);
	       fillellipse(posX,posY,5,5);
	 }

	 if(matriz[ilocal][jlocal]==0){
	    //En esta ocasion lo que hacemos es repintar en negro las casillas vacias
	    setcolor(BLACK);
	    setfillstyle(SOLID_FILL,BLACK);
	    fillellipse(posX,posY,13,13);
	 }

	 posX=posX+40;
	 jlocal++;
      }
      posX=180;
      jlocal=0;
      posY=posY+40;
      ilocal++;
   }
}

void moverFicha(){
//En esta funcion es donde se desarrolla el juego.

   int iori=NULL, jori=NULL;//varibles i y j locales.
   Sonidos pitido;//creamos el objeto "pitido" de la clase "sonidos".

   finjugada=1;

   pedirPosicion();//Se llama a la funcion pedirPosicion para que el jugador seleccione la ficha a mover.

   while(finjugada==1){

      if(turno==0){
	 //JUGADOR 1:

	 if((matriz[i][j]==2)||(matriz[i][j]==4)){

	    pitido.sonar();//suena un pitido agudo al seleccionar la ficha.
	    gotoxy(1,24);
	    printf("Ha seleccionado la ficha x%d / y%d\n",j+1,i+1);
	    printf("Haz click con el boton derecho del raton para rectificar");
	    //Copiamos los valores de i y de j de la ficha seleccionada para no perderlos.
	    iori=i;
	    jori=j;
	    while(finjugada==1){

	       //Seleccionar destino de la ficha seleccionada:
	       if(pedirPosicion()==1){//si retornamos 1 es que el jugador ha hecho click con el boton derecho del rat¢n para "soltar" la ficha seleccionada.
		  finjugada=0;//Se finaliza la jugada,
		  cambio=0;//pero NO se cambia de turno.
	       }

	       if(matriz[iori][jori]==2){//movimiento peon
		  movPeonJ1(iori,jori);//llamamos a la funcion que comprobar  si el movimiento que intenta realizar el jugador es valido.
	       }
	       else{//movimiento dama
		  movDamaJ1(iori,jori);//llamamos a la funcion que comprobar  si el movimiento que intenta realizar el jugador es valido.
	       }
	    }//FIN seleccionar destino.
	 }//FIN if seleccionar ficha a mover.
	 else{
	    //La casilla donde ha clicado el jugador NO es valida, es decir, no hay posicionada ah¡ una ficha que le corresponda.
	    pedirPosicion();//Se solicita de nuevo al jugador que seleccione una ficha.
	 }
      }//Fin jugador1.

      else{
	 //JUGADOR 2:
	 //No detallamos el codigo del jugador 2 puesto que son las mismas instrucciones que se usan en el jugador1. Unicamente cambian los valores de las condiciones (los correspondientes al J2).
	 if((matriz[i][j]==3)||(matriz[i][j]==6)){
	    pitido.sonar();
	    gotoxy(1,24);
	    printf("Ha seleccionado la ficha x%d / y%d\n",j+1,i+1);
	    printf("Haz click con el boton derecho del raton para rectificar");
	    iori=i;
	    jori=j;
	    while(finjugada==1){

	       if(pedirPosicion()==1){
		  finjugada=0;
		  cambio=0;
	       }

	       if(matriz[iori][jori]==3){
		  movPeonJ2(iori,jori);
	       }
	       else{
		  movDamaJ2(iori,jori);
	       }
	    }
	 }
	 else{
	    pedirPosicion();
	 }

      }//Fin jugador2.

   }//FIN de la jugada actual.
}

void cambioTurno(){
   if(cambio==1){//Si la variable "cambio" es 1, se hace efectivo el cambio de turno, sino pues continua moviendo el mismo jugador.
      if(turno==0){
	 turno=1;
      }
      else{
	 turno=0;
      }
   }
   gotoxy(1,23);
   printf("Turno %s",player[turno].nombre);
}

void limpiar(){
//Funcion empleada para limpiar el texto en pantalla.

   int posfil=23,poscol=1;

   while(posfil<26){
      while(poscol<80){
	 gotoxy(poscol,posfil);
	 printf(" ");
	 poscol++;
      }
      poscol=1;
      posfil++;
   }
}

void sacarDama(){
//Funcion utilizada para comprobar si existe algun peon, ya sea del J1 o del J2, en el limite correspondiente.
//Los limite son fila 7 para el J2 y fila 0 para el J1.

   Sonidos objeto(5000);//creamos el objeto pasandole parametros.
   int ipos=0, jpos=0;

   //Comprobaci¢n J1:
   while(jpos<8){
      if(matriz[ipos][jpos]==2){
	 matriz[ipos][jpos]=4;//El peon se transforma en dama.
	 objeto.coronar();//Suena un pitido.
      }
      jpos++;
   }

   jpos=0;
   ipos=7;

   //Comprobacion J2:
   while(jpos<8){
      if(matriz[ipos][jpos]==3){
	 matriz[ipos][jpos]=6;
	 objeto.coronar();
      }
      jpos++;
   }
}

void recontarFichas(){
//Funci¢n utilizada para comprobar si alguno de los dos jugadores se ha quedado sin fichas, y por lo tanto pierde la partida.

   Sonidos objeto(1000);
   int ilocal=0, jlocal=0;

   player[0].fichas=0;
   player[1].fichas=0;

   //Recuento J1
   while(ilocal<8){
      while(jlocal<8){
	 if((matriz[ilocal][jlocal]==2)||(matriz[ilocal][jlocal]==4)){
	    player[0].fichas++;
	 }
	 jlocal++;
      }
      jlocal=0;
      ilocal++;
   }

   ilocal=0;
   jlocal=0;

   //Recuento J2
   while(ilocal<8){
      while(jlocal<8){
	 if((matriz[ilocal][jlocal]==3)||(matriz[ilocal][jlocal]==6)){
	    player[1].fichas++;
	 }
	 jlocal++;
      }
      jlocal=0;
      ilocal++;
   }

   //Comprobacion del J1
   if(player[0].fichas==0){
      objeto.ganar();//Combinacion de sonidos que indican el final de la partida.
      gotoxy(1,25);
      printf("­­Ganador %s!!. Pulse INTRO para fin",player[1].nombre);
      fflush(stdin);
      getch();
      finpartida=0;
      comprobarRecarga=1;
   }

   //Comprobacion del J2
   if(player[1].fichas==0){
      objeto.ganar();
      gotoxy(1,25);
      printf("­­Ganador %s!!. Pulse INTRO para fin.",player[0].nombre);
      fflush(stdin);
      getch();
      finpartida=0;
      comprobarRecarga=1;
   }
}

/*Funciones de movimientos de fichas*/
//Se desarrollan a continuacion cuatro funciones, las cuales se encargan de realizar las comprobaciones oportunas
//para determinar si el movimiento de una ficha es o no es v lido.

void movPeonJ1(int iori, int jori){
   Sonidos grave(500);

   //Mover sin comer
   if( (matriz[i][j]==0)&&(i==iori-1)&&((j==jori+1)||(j==jori-1)) ){
      matriz[iori][jori]=0;//Vaciamos la casilla actual, donde se posicionaba la ficha a mover.
      matriz[i][j]=2;//Rellenamos con el valor correspondiente la casilla donde hemos movido la ficha (2 es el valor del peon del jugador1).
      finjugada=0;//Fin de la jugada
      cambio=1;//Permitimos que se produzca el cambio del turno
      movimientoj1++;//Contabilizamos el movimiento del jugador para mostrar las estadisticas al final de la partida.
   }

   //Mover comiendo a derechas
   if( (matriz[i][j]==0)&&(i==iori-2)&&(j==jori+2)&&( (matriz[iori-1][jori+1]==3)||(matriz[iori-1][jori+1]==6)) ){
      grave.sonar();
      matriz[iori][jori]=0;//Vaciamos la casilla actual, donde se posicionaba la ficha a mover.
      matriz[iori-1][jori+1]=0;//Nos comemos la ficha rival.
      matriz[i][j]=2;//Rellenamos con el valor correspondiente la casilla donde hemos movido nuestra ficha (2 es el valor del peon del jugador1).

      //A esta funcion £nicamente se le llama en el caso de que se produzca una captura, por ello en el if anterior ("mover sin comer") no aparece.
      saltoMultiplePeonJ1();//Se utiliza para comprobar si esta ficha, con la cual hemos realizado la captura, puede seguir comiendo (captura m£ltiple).

      finjugada=0;//Fin de la jugada.
      cambio=1;//Permitimos que se produzca el cambio de turno.
      movimientoj1++;//Contabilizamos el movimiento del jugador para mostrar las estadisticas al final de la partida.
      comidaj1++;//Contabilizamos la captura para mostrarla en las estadisticas del final de partida.
   }

   //Mover comiendo a izquierdas
   if( (matriz[i][j]==0)&&(i==iori-2)&&(j==jori-2)&&( (matriz[iori-1][jori-1]==3)||(matriz[iori-1][jori-1]==6)) ){
      grave.sonar();
      matriz[iori][jori]=0;
      matriz[iori-1][jori-1]=0;
      matriz[i][j]=2;
      saltoMultiplePeonJ1();
      finjugada=0;
      cambio=1;
      movimientoj1++;
      comidaj1++;
   }
}


void movDamaJ1(int iori, int jori){
   Sonidos grave(500);

   //Mover sin comer
   if( (matriz[i][j]==0)&&((i==iori-1)||(i==iori+1))&&((j==jori+1)||(j==jori-1)) ){
      matriz[iori][jori]=0;
      matriz[i][j]=4;//4 es el valor de la dama del jugador1
      finjugada=0;
      cambio=1;
      movimientoj1++;
   }

   //Mover comiendo a derechas-superior
   if( (matriz[i][j]==0)&&(i==iori-2)&&(j==jori+2)&&( (matriz[iori-1][jori+1]==3)||(matriz[iori-1][jori+1]==6)) ){
      grave.sonar();
      matriz[iori][jori]=0;
      matriz[iori-1][jori+1]=0;
      matriz[i][j]=4;//4 es el valor de la dama del jugador1
      saltoMultipleDamaJ1();
      finjugada=0;
      cambio=1;
      movimientoj1++;
      comidaj1++;
   }

   //Mover comiendo a izquierdas-superior
   if( (matriz[i][j]==0)&&(i==iori-2)&&(j==jori-2)&&( (matriz[iori-1][jori-1]==3)||(matriz[iori-1][jori-1]==6)) ){
      grave.sonar();
      matriz[iori][jori]=0;
      matriz[iori-1][jori-1]=0;
      matriz[i][j]=4;//4 es el valor de la dama del jugador1
      saltoMultipleDamaJ1();
      finjugada=0;
      cambio=1;
      movimientoj1++;
      comidaj1++;
   }

   //Mover comiendo a derechas-inferior
   if( (matriz[i][j]==0)&&(i==iori+2)&&(j==jori+2)&&( (matriz[iori+1][jori+1]==3)||(matriz[iori+1][jori+1]==6)) ){
      grave.sonar();
      matriz[iori][jori]=0;
      matriz[iori+1][jori+1]=0;
      matriz[i][j]=4;//4 es el valor de la dama del jugador1
      saltoMultipleDamaJ1();
      finjugada=0;
      cambio=1;
      movimientoj1++;
      comidaj1++;
   }

   //Mover comiendo a izquierdas-inferior
   if( (matriz[i][j]==0)&&(i==iori+2)&&(j==jori-2)&&( (matriz[iori+1][jori-1]==3)||(matriz[iori+1][jori-1]==6)) ){
      grave.sonar();
      matriz[iori][jori]=0;
      matriz[iori+1][jori-1]=0;
      matriz[i][j]=4;//4 es el valor de la dama del jugador1
      saltoMultipleDamaJ1();
      finjugada=0;
      cambio=1;
      movimientoj1++;
      comidaj1++;
   }
}

void movPeonJ2(int iori, int jori){
   Sonidos grave(500);

   //Movemos sin comer
   if( (matriz[i][j]==0)&&(i==iori+1)&&((j==jori+1)||(j==jori-1)) ){
      matriz[iori][jori]=0;
      matriz[i][j]=3;//3 es el valor del peon del jugador2
      finjugada=0;
      cambio=1;
      movimientoj2++;
   }

   //Mover comiendo a derechas
   if( (matriz[i][j]==0)&&(i==iori+2)&&(j==jori+2)&&( (matriz[iori+1][jori+1]==2)||(matriz[iori+1][jori+1]==4)) ){
      grave.sonar();
      matriz[iori][jori]=0;
      matriz[iori+1][jori+1]=0;
      matriz[i][j]=3;//3 es el valor dle peon del jugador2
      saltoMultiplePeonJ2();
      finjugada=0;
      cambio=1;
      movimientoj2++;
      comidaj2++;
   }

   //Mover comiendo a izquierdas
   if( (matriz[i][j]==0)&&(i==iori+2)&&(j==jori-2)&&( (matriz[iori+1][jori-1]==2)||(matriz[iori+1][jori-1]==4)) ){
      grave.sonar();
      matriz[iori][jori]=0;
      matriz[iori+1][jori-1]=0;
      matriz[i][j]=3;//3 es el valor dle peon del jugador2
      saltoMultiplePeonJ2();
      finjugada=0;
      cambio=1;
      movimientoj2++;
      comidaj2++;
   }
}

void movDamaJ2(int iori, int jori){
   Sonidos grave(500);

   //Movemos sin comer.
   if( (matriz[i][j]==0)&&((i==iori-1)||(i==iori+1))&&((j==jori+1)||(j==jori-1)) ){
      matriz[iori][jori]=0;
      matriz[i][j]=6;//6 es el valor de la dama del jugador2
      finjugada=0;
      cambio=1;
      movimientoj2++;
   }

   //Mover comiendo a derechas-inferior
   if( (matriz[i][j]==0)&&(i==iori-2)&&(j==jori+2)&&( (matriz[iori-1][jori+1]==2)||(matriz[iori-1][jori+1]==4)) ){
      grave.sonar();
      matriz[iori][jori]=0;
      matriz[iori-1][jori+1]=0;
      matriz[i][j]=6;//6 es el valor de la dama del jugador2
      saltoMultipleDamaJ2();
      finjugada=0;
      cambio=1;
      movimientoj2++;
      comidaj2++;
   }

   //Mover comiendo a izquierdas-inferior
   if( (matriz[i][j]==0)&&(i==iori-2)&&(j==jori-2)&&( (matriz[iori-1][jori-1]==2)||(matriz[iori-1][jori-1]==4)) ){
      grave.sonar();
      matriz[iori][jori]=0;
      matriz[iori-1][jori-1]=0;
      matriz[i][j]=6;//6 es el valor de la dama del jugador2
      saltoMultipleDamaJ2();
      finjugada=0;
      cambio=1;
      movimientoj2++;
      comidaj2++;
   }

   //Mover comiendo a derechas-superior
   if( (matriz[i][j]==0)&&(i==iori+2)&&(j==jori+2)&&( (matriz[iori+1][jori+1]==2)||(matriz[iori+1][jori+1]==4)) ){
      grave.sonar();
      matriz[iori][jori]=0;
      matriz[iori+1][jori+1]=0;
      matriz[i][j]=6;//6 es el valor de la dama del jugador2
      saltoMultipleDamaJ2();
      finjugada=0;
      cambio=1;
      movimientoj2++;
      comidaj2++;
   }

   //Mover comiendo a izquierdas-superior
   if( (matriz[i][j]==0)&&(i==iori+2)&&(j==jori-2)&&( (matriz[iori+1][jori-1]==2)||(matriz[iori+1][jori-1]==4)) ){
      grave.sonar();
      matriz[iori][jori]=0;
      matriz[iori+1][jori-1]=0;
      matriz[i][j]=6;//6 es el valor de la dama del jugador2
      saltoMultipleDamaJ2();
      finjugada=0;
      cambio=1;
      movimientoj2++;
      comidaj2++;
   }
}
/*Fin funciones movimientos*/

void pintarInfoEjes(){
//Pintamos graficamente "la leyenda" de los ejes vertical y horizontal.
   int fil=40, col=175;
   char y[3];
   char x[3];

   strcpy(y,"y1");
   strcpy(x,"x1");

   for(int i=0;i<8;i++){
      settextstyle(2,1,4);
      outtextxy(145,fil,y);
      fil=fil+40;
      y[1]=y[1]+1;
   }

   for(int j=0;j<8;j++){
      settextstyle(2,0,4);
      outtextxy(col,5,x);
      col=col+40;
      x[1]=x[1]+1;
   }
}

/***Funciones de capturas multiples***/

//A estas funciones unicamente se les llama a cada una de ellas dentro de las funciones de movimientos, siempre y cuando se haya producido una captura en lugar de un desplazamiento simple.
//Cada funcion de movimiento llama exclusivamente a SU funcion correspondiente de "saltoMultiple".

void saltoMultiplePeonJ1(){
   int seguir=1;
   Sonidos grave(500);//Creamos el objeto.

   while(seguir==1){

      seguir=0;

      //Comer a derechas
      if( ((matriz[i-1][j+1]==3)||(matriz[i-1][j+1]==6)) && (i>=2) && (j<=5) && (matriz[i-2][j+2]==0) ){
	 msituar(1,140,200);//Se situa el puntero del raton en un punto de la pantalla que no moleste.
	 pintarFichasEnTablero();//Se repinta el tablero.
	 delay(600);//Necesitamos de este delay para poder visualizar como cambia graficamente la ficha en el tablero.
	 matriz[i][j]=0;//Vaciamos la casilla actual.
	 matriz[i-1][j+1]=0;//Comemos la ficha del rival
	 matriz[i-2][j+2]=2;//Situamos nuestra ficha en la nueva posicion

	 //Los nuevos valores de i y j son aquellos donde hemos movido nuestra ficha, para partir de esta posicion a la hora de realizar una nueva comprobacion.
	 i=i-2;
	 j=j+2;

	 seguir=1;//Puesto que hemos hecho una captura, debemos tener la posibilidad de comprobar de nuevo si se puede realizar otra captura partiendo de la nueva posici¢n.
	 grave.sonar();//Se produce un sonido cuando nos comemos una ficha.
	 comidaj1++;//Contabilizamos, para las estadisticas, una captura de ficha.
      }

      //Comer a izquierdas
      if(((matriz[i-1][j-1]==3)||(matriz[i-1][j-1]==6))&&(i>=2)&&(j>=2)&&(matriz[i-2][j-2]==0)){
	 msituar(1,140,200);
	 pintarFichasEnTablero();
	 delay(600);
	 matriz[i][j]=0;
	 matriz[i-1][j-1]=0;
	 matriz[i-2][j-2]=2;
	 pintarFichasEnTablero();
	 i=i-2;
	 j=j-2;
	 seguir=1;
	 grave.sonar();
	 comidaj1++;
      }
   }
}


void saltoMultiplePeonJ2(){
   int seguir=1;
   Sonidos grave(500);

   while(seguir==1){

      seguir=0;

      //Comer a derechas
      if( ((matriz[i+1][j+1]==2)||(matriz[i+1][j+1]==4)) && (i<=5) && (j<=5) && (matriz[i+2][j+2]==0) ){
	 msituar(1,140,200);//situar el raton
	 pintarFichasEnTablero();//repintar el tablero
	 delay(600);//espera de 600ms
	 matriz[i][j]=0;
	 matriz[i+1][j+1]=0;
	 matriz[i+2][j+2]=3;
	 i=i+2;
	 j=j+2;
	 seguir=1;
	 grave.sonar();
	 comidaj2++;
      }
	 //Comer a izquierdas
      if(((matriz[i+1][j-1]==2)||(matriz[i+1][j-1]==4))&&(i<=5)&&(j>=2)&&(matriz[i+2][j-2]==0)){
	 msituar(1,140,200);
	 pintarFichasEnTablero();
	 delay(600);
	 matriz[i][j]=0;
	 matriz[i+1][j-1]=0;
	 matriz[i+2][j-2]=3;
	 pintarFichasEnTablero();
	 i=i+2;
	 j=j-2;
	 seguir=1;
	 grave.sonar();
	 comidaj2++;
      }
   }
}


void saltoMultipleDamaJ1(){
   int seguir=1;
   Sonidos grave(500);

   while(seguir==1){

      seguir=0;

      //Comer a arriba-derecha
      if( ((matriz[i-1][j+1]==3)||(matriz[i-1][j+1]==6)) && (i>=2) && (j<=5) && (matriz[i-2][j+2]==0) ){
	 msituar(1,140,200);
	 pintarFichasEnTablero();
	 delay(600);
	 matriz[i][j]=0;
	 matriz[i-1][j+1]=0;
	 matriz[i-2][j+2]=4;
	 i=i-2;
	 j=j+2;
	 seguir=1;
	 grave.sonar();
	 comidaj1++;
      }
	 //Comer arriba-izquierda
      if(((matriz[i-1][j-1]==3)||(matriz[i-1][j-1]==6))&&(i>=2)&&(j>=2)&&(matriz[i-2][j-2]==0)){
	 msituar(1,140,200);
	 pintarFichasEnTablero();
	 delay(600);
	 matriz[i][j]=0;
	 matriz[i-1][j-1]=0;
	 matriz[i-2][j-2]=4;
	 pintarFichasEnTablero();
	 i=i-2;
	 j=j-2;
	 seguir=1;
	 grave.sonar();
	 comidaj1++;
      }

      //Comer abajo-derechas
      if( ((matriz[i+1][j+1]==3)||(matriz[i+1][j+1]==6)) && (i<=5) && (j<=5) && (matriz[i+2][j+2]==0) ){
	 msituar(1,140,200);//situar el raton
	 pintarFichasEnTablero();//repintar el tablero
	 delay(600);//espera de 500ms
	 matriz[i][j]=0;
	 matriz[i+1][j+1]=0;
	 matriz[i+2][j+2]=4;
	 i=i+2;
	 j=j+2;
	 seguir=1;
	 grave.sonar();
	 comidaj1++;
      }
	 //Comer abajo-izquierdas
      if(((matriz[i+1][j-1]==3)||(matriz[i+1][j-1]==6))&&(i<=5)&&(j>=2)&&(matriz[i+2][j-2]==0)){
	 msituar(1,140,200);
	 pintarFichasEnTablero();
	 delay(600);
	 matriz[i][j]=0;
	 matriz[i+1][j-1]=0;
	 matriz[i+2][j-2]=4;
	 pintarFichasEnTablero();
	 i=i+2;
	 j=j-2;
	 seguir=1;
	 grave.sonar();
	 comidaj1++;
      }

   }
}

void saltoMultipleDamaJ2(){
   int seguir=1;
   Sonidos grave(500);

   while(seguir==1){

      seguir=0;

      //Comer a abajo-derecha
      if( ((matriz[i-1][j+1]==2)||(matriz[i-1][j+1]==4)) && (i>=2) && (j<=5) && (matriz[i-2][j+2]==0) ){
	 msituar(1,140,200);
	 pintarFichasEnTablero();
	 delay(600);
	 matriz[i][j]=0;
	 matriz[i-1][j+1]=0;
	 matriz[i-2][j+2]=6;
	 i=i-2;
	 j=j+2;
	 seguir=1;
	 grave.sonar();
	 comidaj2++;
      }
	 //Comer abajo-izquierda
      if(((matriz[i-1][j-1]==2)||(matriz[i-1][j-1]==4))&&(i>=2)&&(j>=2)&&(matriz[i-2][j-2]==0)){
	 msituar(1,140,200);
	 pintarFichasEnTablero();
	 delay(600);
	 matriz[i][j]=0;
	 matriz[i-1][j-1]=0;
	 matriz[i-2][j-2]=6;
	 pintarFichasEnTablero();
	 i=i-2;
	 j=j-2;
	 seguir=1;
	 grave.sonar();
	 comidaj2++;
      }

      //Comer arriba-derechas
      if( ((matriz[i+1][j+1]==2)||(matriz[i+1][j+1]==4)) && (i<=5) && (j<=5) && (matriz[i+2][j+2]==0) ){
	 msituar(1,140,200);//situar el raton
	 pintarFichasEnTablero();//repintar el tablero
	 delay(600);//espera de 500ms
	 matriz[i][j]=0;
	 matriz[i+1][j+1]=0;
	 matriz[i+2][j+2]=6;
	 i=i+2;
	 j=j+2;
	 seguir=1;
	 grave.sonar();
	 comidaj2++;
      }
	 //Comer arriba-izquierdas
      if(((matriz[i+1][j-1]==2)||(matriz[i+1][j-1]==4))&&(i<=5)&&(j>=2)&&(matriz[i+2][j-2]==0)){
	 msituar(1,140,200);
	 pintarFichasEnTablero();
	 delay(600);
	 matriz[i][j]=0;
	 matriz[i+1][j-1]=0;
	 matriz[i+2][j-2]=6;
	 pintarFichasEnTablero();
	 i=i+2;
	 j=j-2;
	 seguir=1;
	 grave.sonar();
	 comidaj2++;
      }

   }
}
/*Fin capturas multiples*/

void pintarBotones(){
//Funcion empleada para pintar dos botones en pantalla

   setcolor(BLUE);
   settextstyle(2,0,4);/*modo de estilo de la fuente*/
   setfillstyle(SOLID_FILL,BLUE);/*modo de relleno de los botones*/
   bar3d(10,25,100,50,10,10);/*pinta el boton en posicion inicial*/
   setcolor(WHITE);
   outtextxy(12,30,"Guardar y salir");

   setcolor(BLUE);
   settextstyle(2,0,4);/*modo de estilo de la fuente*/
   setfillstyle(SOLID_FILL,BLUE);/*modo de relleno de los botones*/
   bar3d(10,75,100,100,10,10);/*pinta el boton en posicion inicial*/
   setcolor(WHITE);
   outtextxy(40,80,"Salir");

}

void guardarPartida(){
//Esta funcion se encarga de volcar los datos de las variables de la partida a un fichero.
//A esta funcion UNICAMENTE se le llama desde la funcion "pedirPosicion" cuando se hace click con el boton izq. del raton sobre el boton correspondiente pintado en pantalla.
/*Se guarda:
    -nombre de la partida (aunque no se usa)
    -nombres de los jugadores.
    -contenido de la matriz
    -turno
    -los valores de las cuatro variables de las estadisticas.
*/

   char nombrepartida[75];
   int ilc=0, jlc=0;
   FILE *f;

   //Vaciamos la cadena "nombrepartida".
   for(int i=0;i<75;i++){
      nombrepartida[i]=NULL;
   }

   //Construimos el nobmre de la partida:
   strcat(nombrepartida,player[0].nombre);
   strcat(nombrepartida,"vs");
   strcat(nombrepartida,player[1].nombre);

   //Cargamos el fichero en modo lectura/escritura.
   f=fopen("damas.dat","w+b");

   if(ferror!=0){
      fprintf(f,"%s",nombrepartida);//Guardamos el nombre de la partida.
      fputc('*',f);//A¤adimos un asterisco como delimitador
      fprintf(f,"%s",player[0].nombre);//Guardamos el nombre del Jugador 1.
      fputc('*',f);
      fprintf(f,"%s",player[1].nombre);//Guardamos el nombre del Jugador 2.
      fputc('*',f);

      //Con estos dos bucles anidados, guardamos el contenido de la matriz.
      while(ilc<8){
	 while(jlc<8){
	    fprintf(f,"%d",matriz[ilc][jlc]);
	    jlc++;
	 }
	 jlc=0;
	 ilc++;
      }

      fputc('*',f);
      fprintf(f,"%d",turno);//Guardamos el turno actual.

      //Guardamos las estadisticas:
      fputc('*',f);
      fprintf(f,"%d",movimientoj1);
      fputc('*',f);
      fprintf(f,"%d",movimientoj2);
      fputc('*',f);
      fprintf(f,"%d",comidaj1);
      fputc('*',f);
      fprintf(f,"%d",comidaj2);

      fputc('@',f);//A¤adimos la arroba como "marca" para delimitar los datos de una partida.

      fclose(f);//Cerramos el fichero
   }
   else{
      printf("Error apertura de fichero\n");
   }
}

void dibujarMenu(){
	//Esta funcion pinta en pantalla el menu principal:

	int salirMenu=1; //Variable para quedarse en el menu mientras que no clickes en una de las opciones
	int retrasar=200; //Variable para retrasar el click
	int left=420, top=176, right=430, bottom=190; //Variable para los posicionamientos de las opciones del menu.
	int sum=20; //Variable para incrementar la posicion de las opciones del menu.
	msituar(1,1,1);//Situar el raton en un punto de la pantalla.
	cleardevice(); //Limpiamos la pantalla
	settextstyle(3,0,6);
	outtextxy(240,50,"DAMAS");
	rectangle(110,140,530,400);
	settextstyle(2,0,6);
	setcolor(RED); //Establecemos el color en rojo del rectangulo.
	rectangle(left,top,right,bottom);
	outtextxy(240,170,"1- Nueva partida");
	rectangle(left,top+sum,right,bottom+sum);
	outtextxy(240,190,"2- Cargar partida");
	rectangle(left,top+(sum*2),right,bottom+(sum*2));
	outtextxy(240,210,"3- Instrucciones");
	rectangle(left,top+(sum*3),right,bottom+(sum*3));
	outtextxy(240,230,"4- Salir");
	outtextxy(150,380,"Jesus Rojas, Manuel Vicente Almagro");

	//Posicionamos el click en cada cuadrado de las opciones del menu.
	while(salirMenu==1){

	   if( (mclick()==1) && (inbox(left,top,right,bottom,mposx(1),mposy(1))==1) ){
		salirMenu=0;
		opcion=1;
		delay(retrasar);
	   }

	   if( (mclick()==1) && (inbox(left,top+sum,right,bottom+sum,mposx(1),mposy(1))==1) ){
		salirMenu=0;
		opcion=2;
		delay(retrasar);
	   }

	   if( (mclick()==1) && (inbox(left,top+(sum*2),right,bottom+(sum*2),mposx(1),mposy(1))==1) ){
		salirMenu=0;
		opcion=3;
		delay(retrasar);
	   }

	   if( (mclick()==1) && (inbox(left,top+(sum*3),right,bottom+(sum*3),mposx(1),mposy(1))==1) ){
		salirMenu=0;
		opcion=5;
		delay(retrasar);
	   }

	}

	char jugador1[20];
	char jugador2[20];

	switch(opcion){
		case 1:
			msituar(1,1,1);//Situar el raton en un punto de la pantalla.
			cleardevice();
			settextstyle(3,0,6);
			outtextxy(240,50,"DAMAS");
			rectangle(110,140,530,400);
			settextstyle(6,0,1);
			outtextxy(210,230,"Jugador 1: ");
			rectangle(300,260,410,235);
			fflush(stdin);
			gotoxy(39,16);
			gets(player[0].nombre); //Guardamos el nombre del primer jugador.
			cleardevice();
			settextstyle(3,0,6);
			outtextxy(240,50,"DAMAS");
			rectangle(110,140,530,400);
			settextstyle(6,0,1);
			outtextxy(210,230,"Jugador 2: ");
			rectangle(300,260,410,235);
			gotoxy(39,16);
			fflush(stdin);
			gets(player[1].nombre); //Guardamos el nombre del segundo jugador.
			mocultar();
			delay(100);
			cleardevice();
			setcolor(WHITE);
			outtextxy(230,240,"Jugador 1:");
			outtextxy(230,270,"Jugador 2:");
			outtextxy(330,240,player[0].nombre); //Pintamos los nombres de los jugadores.
			outtextxy(330,270,player[1].nombre);
			CargarBarra();
			dibujarTablero();
			break;
		case 2:
			recargarPartida(); //Llamada a la funcion para recargar partida.
			break;
		case 3:
			msituar(1,1,1);//Situar el raton en un punto de la pantalla.
			delay(100);
			cleardevice();
			settextstyle(3,0,6);
			outtextxy(240,50,"DAMAS");
			setcolor(WHITE);
			rectangle(40,400,600,140);
			settextstyle(2,0,5);
			outtextxy(50,150,"Bienvenido al juego de las damas,");
			outtextxy(50,165,"realizado por: Jesus Rojas y Manuel Vicente Almagro.");
			outtextxy(50,180,"Las damas es un juego para dos contrincantes");
			outtextxy(50,195,"que consiste en mover las piezas en diagonal");
			outtextxy(50,210,"con la intencion de comer las piezas");
			outtextxy(50,225,"del jugador contrario, pasando por encima de dichas piezas.");
			outtextxy(50,240,"La partida empieza con las piezas verdes.");
			outtextxy(50,255,"Con click izquierdo seleccionamos la ficha que queremos mover.");
			outtextxy(50,270,"Con click derecho liberamos la ficha que hemos elegido previamente.");
			fflush(stdin);
			getch();
			dibujarMenu();
			break;
		case 4:
			//ranking();
		case 5:
			exit(0);
			break;
	}

}

void CargarBarra(){
	//Funcion que carga graficamente una barra (animaci¢n).
	//A esta funcion se le llama unicamente desde la opcion 1 del menu.
	Sonidos suena(50);

	int i;

	setcolor(WHITE);
	settextstyle(SMALL_FONT,0,16);
	outtextxy(220,90,"CARGANDO");

	setcolor(WHITE); //Establecemos el color de la barra en blanco.
	for(i=0;i<250;i++){
		line(180+i,220,180+i,200); //Se pinta la linea del tiron al no poner un delay.
	}

	for(i=0;i<250;i++){
		setcolor(GREEN);
		line(180+i,220,180+i,200); //Se pinta la linea poco a poco al poner un delay.
		suena.cargaBarra();
		delay(10);
	}
	nosound();
	setcolor(WHITE);
	delay(10);


}

void dibujarTablero(){
	//Se trata de una funcion que realiza una animacion de dibujo del tablero pintando lineas horizontales y verticales, y rellenando las casillas resultantes.
	//A esta funcion se le llama unicamente desde la opcion 1 del menu, tras finalizar la carga de la barra.
	cleardevice();
	int i=0;
	int j=0;
	int dimension=40;
	int startTop=20;
	int startLeft=160;
	int left=startLeft, top=startTop, right=left+dimension, bottom=top+dimension;

	for(i=0;i<320;i++){ //LINEAS ARRIBA Y ABAJO
		line(160,20,160+i,20);
		line(160,340,160+i,340);
		delay(2);
	}

	for(i=0;i<320;i++){ //LINEAS LATERALES
		line(160,20,160,20+i);
		line(480,20,480,20+i);
		delay(2);
	}
	for(i=0;i<320;i++){ //Lineas laterales, arriba y abajo
		line(200,20,200,20+i);
		line(240,20,240,20+i);
		line(280,20,280,20+i);
		line(320,20,320,20+i);
		line(360,20,360,20+i);
		line(400,20,400,20+i);
		line(440,20,440,20+i);
		line(160,60,160+i,60);
		line(160,100,160+i,100);
		line(160,140,160+i,140);
		line(160,180,160+i,180);
		line(160,220,160+i,220);
		line(160,260,160+i,260);
		line(160,300,160+i,300);
		delay(2);
	}
	//Bucle para pintar los cuadrados y poder rellenarlos.
	while(i<8){
	 while(j<8){
		 rectangle(left,top,right,bottom);
		left=right;
		 right=left+dimension;
		 j++;
	      }
	      j=0;
	      i++;
	      left=startLeft;
	      right=left+dimension;
	      top=bottom;
	      bottom=top+dimension;
	    }

	int posX=161, posY=21;
	int ilocal=0, jlocal=0;

   while(ilocal<8){ //Bucle para rellenar los cuadrados pares del color blanco.
      while(jlocal<8){
	 if((jlocal+ilocal)%2==0){
	     //Si j+i es par, le corresponde ser blanca a la casilla.
	     setcolor(WHITE);
	     setfillstyle(SOLID_FILL,WHITE);
	     floodfill(posX,posY,WHITE);
	     delay(30);
	 }
	 posX=posX+40;
	 jlocal++;
      }
      posX=161;
      jlocal=0;
      posY=posY+40;
      ilocal++;
   }
}

void recargarPartida(){
   //Funcion que recarga la partida, es decir, vuelca el contenido almacenado en un fichero es sus variables correspondientes.
   //Para llamar a esta funcion se debe seleccionar la opcion 2 del menu.
   FILE *f;
   int j=0;
   int i=0;
   char c=NULL;
   int numero;
   char estadisticas[2];

   //Se abre el fichero en modo lectura.
   f=fopen("damas.dat","r");

   c=fgetc(f);//Avanzamos 1 posicion en el fichero.

   //El bucle terminar  cuando se localice el caracter de la arroba.
   while(c!='@'){

      //El uso de este bucle es descartar los caracteres del nombre de partida puesto que finalmente se ha decidido no usar "esta cadena".
      while(c!='*'){
	 c=fgetc(f);
      }

      c=fgetc(f);//Nos saltamos el asterisco.

      //Con este bucle cargamos en la variable correspondiente el nombre del primer jugador.
      while(c!='*'){
	 player[0].nombre[j]=c;
	 c=fgetc(f);
	 j++;
      }
      player[0].nombre[j]=NULL;//Guardamos un NULL en la ultima posicion de la cadena.

      c=fgetc(f);//Nos saltamos el asterisco.

      j=0;//Reseteamos el valor de J.

      //Con este bucle cargamos en la variable correspondiente el nombre del segundo jugador.
      while(c!='*'){
	 player[1].nombre[j]=c;
	 c=fgetc(f);
	 j++;
      }
      player[1].nombre[j]=NULL;//Guardamos un NULL en la ultima posicion de la cadena.

      c=fgetc(f);//Nos saltamos el asterisco.

      j=0;//Reseteamos el valor de J.

      //Con estos dos bucles anidados lo que hacemos es cargar en la matriz el contenido del fichero que le corresponde (ESTADO DE LA PARTIDA).
      while(i<8){
	 while(j<8){
	    numero=((int)c)-48;
	    matriz[i][j]=numero;
	    c=fgetc(f);
	    j++;
	 }
	 j=0;
	 i++;
      }

      c=fgetc(f);//Nos saltamos el asterisco.

      //Cargamos el turno.
      numero=((int)c)-48;//es necesario parsear el valor almacenado en el fichero antes de guardarlo como un int.
      turno=numero;//tras realizar el parseo, lo guardamos en su variable correspondiente.

      //Cargamos las estadisticas:
      estadisticas[0]=NULL;
      estadisticas[1]=NULL;
      c=fgetc(f);//ASTERISCO

      c=fgetc(f);//PRIMER NUMERO
      //numero=((int)c)-48;
      estadisticas[0]=c;
      c=fgetc(f);
      if(c!='*'){
		estadisticas[1]=c;
		numero=atoi(estadisticas);
		movimientoj1=numero;
		c=fgetc(f);//ASTERISCO
      }else{
	numero=((int)estadisticas[0])-48;
	movimientoj1=numero;
      }

      estadisticas[0]=NULL;
      estadisticas[1]=NULL;

      c=fgetc(f);//PRIMER NUMERO
      estadisticas[0]=c;
      c=fgetc(f);
      if(c!='*'){
		estadisticas[1]=c;
		numero=atoi(estadisticas);
		movimientoj2=numero;
		c=fgetc(f);//ASTERISCO
      }else{
	numero=((int)estadisticas[0])-48;
	movimientoj2=numero;
      }

      estadisticas[0]=NULL;
      estadisticas[1]=NULL;

      c=fgetc(f);//PRIMER NUMERO
      estadisticas[0]=c;
      c=fgetc(f);
      if(c!='*'){
		estadisticas[1]=c;
		numero=atoi(estadisticas);
		comidaj1=numero;
		c=fgetc(f);//ASTERISCO
      }else{
	numero=((int)estadisticas[0])-48;
		comidaj1=numero;
      }

      estadisticas[0]=NULL;
      estadisticas[1]=NULL;


      c=fgetc(f);//PRIMER NUMERO
      estadisticas[0]=c;
      c=fgetc(f);
      if(c!='@'){
		estadisticas[1]=c;
		numero=atoi(estadisticas);
		comidaj2=numero;
		c=fgetc(f);//Llegamos al final del fichero
      }else{
	numero=((int)estadisticas[0])-48;
	comidaj2=numero;
      }

      //Fin carga de estadisticas

   }//Fin

   comprobarRecarga=0; //Necesario para que, al comenzar el primer bucle, no entre en las funciones de rellenarMatriz y colocarFichasEnMatriz.

   fclose(f);

   mocultar();
}

int comprobarAhogo(){
   //Esta funcion se utiliza para comprobar si el jugador al que le toca mover, tiene en realidad posibilidad de realizar un movimiento o bien esta bloqueado por completo.
   //Primero hay que comprobar a que jugador le toca (variable turno).
   //Despues recorremos la matriz preguntando en cada casilla si hay posicionada una ficha del jugador que posee el turno.
      //en el caso de que el jugador pueda mover cualquier ficha, salimos del bucle y continuamos partida.
      //en caso de que el jugador no pueda mover ninguna ficha, dicho jugador pierde y finalizamos la partida.

   Sonidos objeto(1000);
   int ahogo=1;

   int il=0, jl=0;//Variables locales para recorrer por completo toda la matriz.

   if(turno==0){//Jugador 1
      while((il<8)&&(ahogo==1)){
	 while((jl<8)&&(ahogo==1)){

	    if(matriz[il][jl]==2){//Peon J1

	       //Los siguientes 4 if (los mas externos) se utilizan para comprobar los limites de la matriz, antes de poder realizar las comprobaciones pertinentes (ifs internos).

	       if((jl-1>=0)&&(il-1>=0)){
		  if(matriz[il-1][jl-1]==0){
		     ahogo=0;
		  }
	       }

	       if((jl-2>=0)&&(il-2>=0)){
		  if( (matriz[il-2][jl-2]==0)&& ((matriz[il-1][jl-1]==3)||(matriz[il-1][jl-1]==6)) ){
		     ahogo=0;
		  }
	       }

	       if((jl+1<=7)&&(il-1>=0)){
		  if(matriz[il-1][jl+1]==0){
		     ahogo=0;
		  }
	       }

	       if((jl+2<=7)&&(il-2>=0)){
		  if((matriz[il-2][jl+2]==0)&& ((matriz[il-1][jl+1]==3)||(matriz[il-1][jl+1]==6))){
		     ahogo=0;
		  }
	       }
	    }
	    else if(matriz[il][jl]==4){ //Dama J1
	       //Los siguientes 8 if (los mas externos) se utilizan para comprobar los limites de la matriz, antes de poder realizar las comprobaciones pertinentes (ifs internos).
	       //Los primeros 4 ifs son iguales que los del peon, y a ellos se le a¤aden otros 4 ifs puesto que las damas pueden caminar hacia atras (en total 8 posibles movimientos).

	       if((jl-1>=0)&&(il-1>=0)){
		  if(matriz[il-1][jl-1]==0){
		     ahogo=0;
		  }
	       }

	       if((jl-2>=0)&&(il-2>=0)){
		  if( (matriz[il-2][jl-2]==0)&& ((matriz[il-1][jl-1]==3)||(matriz[il-1][jl-1]==6)) ){
		     ahogo=0;
		  }
	       }

	       if((jl+1<=7)&&(il-1>=0)){
		  if(matriz[il-1][jl+1]==0){
		     ahogo=0;
		  }
	       }

	       if((jl+2<=7)&&(il-2>=0)){
		  if((matriz[il-2][jl+2]==0)&& ((matriz[il-1][jl+1]==3)||(matriz[il-1][jl+1]==6))){
		     ahogo=0;
		  }
	       }

	       if((jl-1>=0)&&(il+1<=7)){
		  if(matriz[il+1][jl-1]==0){
		     ahogo=0;
		  }

	       }

	       if((jl-2>=0)&&(il+2<=7)){
		  if( (matriz[il+2][jl-2]==0) && ( (matriz[il+1][jl-1]==3) || (matriz[il+1][jl-1]==6) )){
		     ahogo=0;
		  }

	       }

	       if((jl+1<=7)&&(il+1<=7)){
		  if(matriz[il+1][jl+1]==0){
		     ahogo=0;
		  }
	       }

	       if((jl+2<=7)&&(il+2<=7)){
		  if((matriz[il+2][jl+2]==0)&&((matriz[il+1][jl+1]==3)||(matriz[il+1][jl+1]==6))){
		     ahogo=0;
		  }
	       }

	    }

	    jl++;
	 }
	 jl=0;
	 il++;
      }
   }
   else if(turno==1){//Jugador 2
      while((il<8)&&(ahogo==1)){
	 while((jl<8)&&(ahogo==1)){

	    if(matriz[il][jl]==3){//Peon J2
	       //Codigo practicamente identico al peon del jugador 1.

	       if((jl-1>=0)&&(il+1<=7)){
		  if(matriz[il+1][jl-1]==0){
		     ahogo=0;
		  }

	       }

	       if((jl-2>=0)&&(il+2<=7)){
		  if( (matriz[il+2][jl-2]==0) && ( (matriz[il+1][jl-1]==2) || (matriz[il+1][jl-1]==4) )){
		     ahogo=0;
		  }

	       }

	       if((jl+1<=7)&&(il+1<=7)){
		  if(matriz[il+1][jl+1]==0){
		     ahogo=0;
		  }
	       }

	       if((jl+2<=7)&&(il+2<=7)){
		  if((matriz[il+2][jl+2]==0)&&((matriz[il+1][jl+1]==2)||(matriz[il+1][jl+1]==4))){
		     ahogo=0;
		  }
	       }

	    }

	    else if(matriz[il][jl]==6){//Dama J2
	       //Codigo practicamente indentico a la dama del jugador 1.

	       if((jl-1>=0)&&(il+1<=7)){
		  if(matriz[il+1][jl-1]==0){
		     ahogo=0;
		  }

	       }

	       if((jl-2>=0)&&(il+2<=7)){
		  if( (matriz[il+2][jl-2]==0) && ( (matriz[il+1][jl-1]==2) || (matriz[il+1][jl-1]==4) )){
		     ahogo=0;
		  }

	       }

	       if((jl+1<=7)&&(il+1<=7)){
		  if(matriz[il+1][jl+1]==0){
		     ahogo=0;
		  }
	       }

	       if((jl+2<=7)&&(il+2<=7)){
		  if((matriz[il+2][jl+2]==0)&&((matriz[il+1][jl+1]==2)||(matriz[il+1][jl+1]==4))){
		     ahogo=0;
		  }
	       }

	       if((jl-1>=0)&&(il-1>=0)){
		  if(matriz[il-1][jl-1]==0){
		     ahogo=0;
		  }
	       }

	       if((jl-2>=0)&&(il-2>=0)){
		  if( (matriz[il-2][jl-2]==0)&& ((matriz[il-1][jl-1]==2)||(matriz[il-1][jl-1]==4)) ){
		     ahogo=0;
		  }
	       }

	       if((jl+1<=7)&&(il-1>=0)){
		  if(matriz[il-1][jl+1]==0){
		     ahogo=0;
		  }
	       }

	       if((jl+2<=7)&&(il-2>=0)){
		  if((matriz[il-2][jl+2]==0)&& ((matriz[il-1][jl+1]==2)||(matriz[il-1][jl+1]==4))){
		     ahogo=0;
		  }
	       }
	    }

	    jl++;
	 }
	 jl=0;
	 il++;
      }
   }

   if(ahogo==1){
      if(turno==0){
	 objeto.ganar();//Se produce una secuencia de sonidos que indican el fin de la partida.
	 gotoxy(1,25);
	 printf("­­%s esta bloqueado!!.%s gana. Pulse tecla para fin.",player[0].nombre,player[1].nombre);
      }
      else{
	 objeto.ganar();//Se produce una secuencia de sonidos que indican el fin de la partida.
	 gotoxy(1,25);
	 printf("­­%s esta bloqueado!!.%s gana. Pulse tecla para fin.",player[1].nombre,player[0].nombre);
      }

      finpartida=0;
      comprobarRecarga=1;
      fflush(stdin);
      getch();
      return(0);//Devolvemos 0 si alg£n jugador esta bloqueado.
   }
   else{
      return(1);//Devolvemos 1 si NO existe bloqueo.
   }
}