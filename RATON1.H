#include<stdio.h>
#include<dos.h>
#include"protos.h"
union REGS reg;

int mtest(void)
{
reg.x.ax=0x0;
int86(0x33,&reg,&reg);
if (reg.x.ax>0) return reg.x.bx;
else return 0;
}

void mver(void)
{
reg.x.ax=0x1;
int86(0x33,&reg,&reg);
}

void mocultar(void)
{
reg.x.ax=0x2;
int86(0x33,&reg,&reg);
}

int mposx(int modo)
{
reg.x.ax=0x3;
int86(0x33,&reg,&reg);
return reg.x.cx/modo;
}

int mposy(int modo)
{
reg.x.ax=0x3;
int86(0x33,&reg,&reg);
return reg.x.dx/modo;
}

void msituar(int modo, int x, int y)
{
reg.x.ax=0x4;
reg.x.cx=x*modo;
reg.x.dx=y*modo;
int86(0x33,&reg,&reg);
}

int mclick(void)
{
int r=0;
reg.x.ax=0x5;
reg.x.bx=0;
int86(0x33,&reg,&reg);
if ((reg.x.ax)&1) r=1;
else if(reg.x.ax>>1) r=2;
return r;
}

void mlimitar(int modo,int x1, int y1, int x2, int y2)
{
reg.x.ax=0x7;
reg.x.cx=x1*modo;
reg.x.dx=x2*modo;
int86(0x33,&reg,&reg);
reg.x.ax=0x8;
reg.x.cx=y1*modo;
reg.x.dx=y2*modo;
int86(0x33,&reg,&reg);
}

int inbox(int left, int top, int right, int bottom, int x, int y)
{

return ((x>=left&&x<=right&&y>=top&&y<=bottom)?1:0);
}
