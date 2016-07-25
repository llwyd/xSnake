#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
//xSnake.c
//T.Lloyd 2016
 
typedef struct{
	//int * x;
	//int * y;
	int x,y;
	int size;
}
snake;
typedef struct{
	int x;
	int y;
	char score[5];
}
gui;
typedef struct{
	int x,y;
}
food;


void updateGame(Display *d,Window w,GC gc,snake boa,food f,gui g){
	//Clear Window
	XClearWindow(d,w);
	//Draw Snake
	XFillRectangle(d,w,gc,boa.x,boa.y,50,50);
	//Draw Food
	XFillRectangle(d,w,gc,f.x+10,f.y+10,30,30);

}
int main(void){
	//=====================gui Initialisation=====================
	gui g;
	g.x=800;
	g.y=600;
	//=====================Window Initialisation=====================
	GC gc;
	XEvent e;
	unsigned long black,white;
	Display * d = XOpenDisplay(NULL);
	int s = DefaultScreen(d);
	black=BlackPixel(d,s);
	white=WhitePixel(d,s);
	Window w=XCreateSimpleWindow(d,RootWindow(d,s), 10, 10, g.x, g.y, 1, white, black);
	XSetStandardProperties(d,w,"xSnake","xSnake",None,NULL,0,NULL);
	XSelectInput(d,w, ExposureMask | KeyPressMask);	
	gc=XCreateGC(d,w,0,0);
	XSetBackground(d,gc,black);
	XSetForeground(d,gc,white);
	XMapWindow(d,w);
	XFlush(d);
	//=====================Keyboard Initialisation=====================
	KeySym key;
	int ksize=8;
	char keys[ksize];
	keys[0]=0;
	int flag=0;
	snprintf(g.score,sizeof(g.score),"%d-%d",0,0);
	//=====================Player Initialisation=====================
	snake boa;
	boa.size=1;
	boa.x=0;
	boa.y=0;
	//=====================food Initialisation=====================
	food f;
	f.x=0;
	f.y=0;
	//=====================Physics Initialisation=====================
	int dy=0;
	int dx=1;
	int speed=1;
	//=====================Main Event Loop=====================
	XNextEvent(d,&e);
	while(1){
		if(XPending(d)){
			XNextEvent(d,&e);
			if(e.type==Expose&&flag==0){
				updateGame(d,w,gc,boa,f,g);
				flag=1;
			}
			if(e.type==KeyPress){
				XLookupString(&e.xkey,keys,ksize,&key,NULL);
				switch(keys[0]){
					case 119://up
						dy=-1;
						dx=0;
						break;
					case 115://down
						dy=1;
						dx=0;
						break;
					case 97://left
						dy=0;
						dx=-1;
						break;
					case 100://right
						dy=0;
						dx=1;
						break;
				}
				updateGame(d,w,gc,boa,f,g);
			}
		}
		else{
			boa.x+=(50*dx);
			boa.y+=(50*dy);
			if((boa.x==f.x)&&(boa.y==f.y)){
				f.x=(rand()%16)*50;
				f.y=(rand()%12)*50;
				boa.size++;
			}
			updateGame(d,w,gc,boa,f,g);
		
		usleep(((100*100)/2)*10*2);//Sleep
	}
	}
	return 0;
}