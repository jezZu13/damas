/*PROTOTIPOS*/
void drawpanel(int, int, int, int, int);


/*FUNCIONES*/

void drawpanel(int col, int fil, int dimension, int startLeft, int startTop){


   int left=startLeft, top=startTop, right=left+dimension, bottom=top+dimension;
   int j=0, i=0;

   while(i<fil){
      while(j<col){
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
}