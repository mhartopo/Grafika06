#include <stdlib.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "bomb.h"
#include "enemy.h"
#include "targetPoint.h"
#include <termios.h>
typedef struct {
	int x;
	int y;
} Point;

//Variable
int stop = 0;
static struct termios old_termios, new_termios;
int fbfd = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
long int screensize = 0;
char *fbp = 0;
int x = 0, y = 0;
long int location = 0;
targetPoint TP;
Bomb B;

//termios I/O
/* detect keyboard press */
int kbhit(){
    struct timeval tv = {0L,0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0,&fds);
    return select(1,&fds,NULL,NULL,&tv);
}
char getch(){
    char ch;
    ch = getchar();
    return ch;
}
void resetTermios(){
    tcsetattr(0,TCSANOW,&old_termios);
}
/* initialize new terminal i/o settings */
void initTermios(){
    tcgetattr(0,&old_termios); // store old terminal
    new_termios = old_termios; // assign to new setting
    new_termios.c_lflag &= ~ICANON; // disable buffer i/o
    new_termios.c_lflag &= ~ECHO; // disable echo mode
    tcsetattr(0,TCSANOW,&new_termios); // use new terminal setting
}

//declare other procedure
void Paint(int x, int y, int R, int G, int B);
void PaintBackground();
void init();
void PaintEnemy(int x, int y, int R, int G, int B);
void PaintBomb(int x, int y, int R, int G, int B);
int detectCollision(Bomb B, Enemy E);
void drawTarget(int x, int y, int R, int G, int B);
void clearEnemy(int x, int y);
void clearTarget(int x, int y);
void *inputHandler(void *vargp);
void *drawGun(void *args);
void drawTank();

int main() {
 	
 	int numEnemy = 5;
 	Enemy E[8];
 	pthread_t tid;
    //inisialisasi
    init();
    PaintBackground();   	
    initTargetPoint(&TP);
    setTarget(&TP,140,600); //pindahkan target
    
    int i;
    for(i = 0 ; i < numEnemy; i++) {
    	makeEnemy(1300, i*60+30, &(E[i]));
    }
    
    pthread_create(&tid, NULL, inputHandler, NULL);
    drawTank();
    while(stop == 0) {
		//cek collision
		int i;
		for(i = 0; i < numEnemy; i++) {
			int collide = detectCollision(B, E[i]);
			if(collide) {
				PaintEnemy(getEnemyPosX(E[i]), getEnemyPosY(E[i]), 0, 0, 0);
				PaintBomb(getPosX(B), getPosY(B), 0,0,0);
				setActive(&B, 0);
				makeEnemy(1300, i*60+30, &(E[i]));
					
			}  
		}
		//gerakkan objek & gambar
		//enemy
		for(i = 0; i < numEnemy; i++) {
			moveEnemy(&E[i]);
			if(getEnemyPosX(E[i]) <= 10) {
				PaintEnemy(getEnemyPosX(E[i]), getEnemyPosY(E[i]), 0, 0, 0);
				makeEnemy(1300, i*60+30, &(E[i]));
			} else {
				PaintEnemy(getEnemyPosX(E[i]), getEnemyPosY(E[i]), 230, 80, 30);
			}
		}
		//gerakkan & gambar bom jika bom aktif
		if(isActive(B)) {
			nextStep(&B);
			if(getPosX(B) < 0 || getPosX(B) > 1340 || getPosY(B) < 10 || getPosY(B) > 740) {
				setActive(&B,0);
				PaintBomb(getPosX(B), getPosY(B), 0,0,0);	
			} else {
				PaintBomb(getPosX(B), getPosY(B), 211,211,211);	
			}
		}
		
		//render gambar
		usleep(1000);
		for(i = 0; i < numEnemy; i++) {
			clearEnemy(getEnemyPosX(E[i]), getEnemyPosY(E[i]));
		}
		if(isActive(B)) {
			PaintBomb(getPosX(B), getPosY(B), 0,0,0);
		}
		usleep(1000);
    }
	pthread_join(tid, NULL);  
    //mapping memory
    munmap(fbp, screensize);
    close(fbfd);
    return 0;
 }

//thread
void *inputHandler(void *vargp) {
    initTermios();
    char cc;
    pthread_t tid2;
    pthread_create(&tid2, NULL, drawGun, NULL);
    drawTarget(getTargetPosX(TP),getTargetPosY(TP),50,220,10);
    while(stop == 0) {
    	drawTarget(getTargetPosX(TP),getTargetPosY(TP),50,220,10);
    	usleep(1000);
    	
    	if (kbhit()) {
			cc = getch();resetTermios();
			switch (cc) {
				case 'w': case 'W' :
					clearTarget(getTargetPosX(TP),getTargetPosY(TP));
    				moveTarget(&TP,0,-15);
					break;
				case 'a': case 'A' :
					clearTarget(getTargetPosX(TP),getTargetPosY(TP));
    				moveTarget(&TP,-15,0);
					break;
				case 's': case 'S' :
					clearTarget(getTargetPosX(TP),getTargetPosY(TP));
    				moveTarget(&TP,0,15);
					break;
				case 'd': case 'D' :
					clearTarget(getTargetPosX(TP),getTargetPosY(TP));
    				moveTarget(&TP,15,0);
					break;
				case 'q' : case 'Q' :
					stop = 1;
					break;
				case 'i' : case 'I' :
					if(! isActive(B)) {
    					makeBomb(getTargetPosX(TP),getTargetPosY(TP),&B);
    					setActive(&B,1);
    				}
			}
			initTermios();
		}
    }
    pthread_join(tid2, NULL); 
}
//drawGun
void *drawGun(void *args) {
	while (stop == 0) {
		int x0 = 0; int y0 = 670;
		int x1 = getTargetPosX(TP); int y1 = getTargetPosY(TP);
		int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
		int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
		int err = (dx>dy ? dx : -dy)/2, e2;
	
		for(;;){
			int xi;
			for(xi = x0; xi < x0+30; xi++) {
				Paint(xi,y0,100,100,100);
			}
			if (x0*x0 + (y0-655)*(y0-655) >= 10000) break;
			e2 = err;
			if (e2 > -dx) { 
				err -= dy; x0 += sx;
			}
			if (e2 < dy) { 
				err += dx; y0 += sy; 
			}
		}
		usleep(1500);
		x0 = 0; y0=670;
		for(;;){
			int xi;
			for(xi = x0-10; xi < x0+40; xi++) {
				Paint(xi,y0,0,0,0);
			}
			if (x0*x0 + (y0-655)*(y0-655) >= 10000) break;
			e2 = err;
			if (e2 > -dx) { 
				err -= dy; x0 += sx;
			}
			if (e2 < dy) { 
				err += dx; y0 += sy; 
			}
		}
	}
}

void PaintBackground() {
	int i,j;
	for (i = 0; i < 1360; i++) {
		for (j = 0; j < 760; j++) {
			Paint(i,j,0,0,0);
		}
	}
}


void Paint(int _x, int _y, int R, int G, int B) {
	 location = (_x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
		            (_y+vinfo.yoffset) * finfo.line_length;
	 *(fbp + location) = B;        // Some blue
	 *(fbp + location + 1) = G;     // A little green
	 *(fbp + location + 2) = R;    // A lot of red
	 *(fbp + location + 3) = 0;      // No transparency
}

void PaintEnemy(int x, int y, int R, int G, int B) {
	int i,j;
	for(i = x; i < 60 + x; i++) {
		for(j = y; j < 30 + y; j++) {
			Paint (i,j,R,G,B);
		}
    }
}
void clearEnemy(int x, int y) {
	int j;
	for(j = y; j < 30 + y; j++) {
			Paint (x+60,j,0,0,0);
			Paint (x+59,j,0,0,0);
	}
}

void PaintBomb(int x, int y, int R, int G, int B) {
	int i,j;
	for(i = x; i < 15 + x; i++) {
    		for(j = y; j < 15 + y; j++) {
    			Paint (i,j,R,G,B);
    		}
    	}
}

void init() {
	 // Open the file for reading and writing
     fbfd = open("/dev/fb0", O_RDWR);
     if (fbfd == -1) {
         perror("Error: cannot open framebuffer device");
         exit(1);
     }
     printf("The framebuffer device was opened successfully.\n");

     // Get fixed screen information
     if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
         perror("Error reading fixed information");
         exit(2);
     }

     // Get variable screen information
     if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
         perror("Error reading variable information");
         exit(3);
     }

     printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

     // Figure out the size of the screen in bytes
     screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

     // Map the device to memory
     fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
                        fbfd, 0);
     if ((int)fbp == -1) {
         perror("Error: failed to map framebuffer device to memory");
         exit(4);
     }
     printf("The framebuffer device was mapped to memory successfully.\n");

     x = 300; y = 100;       // Where we are going to put the pixel
}


int detectCollision(Bomb B, Enemy E) {
	int a,b,c,d;
	a = getEnemyPosX(E);
	b = getEnemyPosY(E);
	c = getPosX(B);
	d = getPosY(B);
	return (((a-15 <= c) && (a+60 >= c)) && ((b-15 <= d) && (b+30 >= d)) && isActive(B));
}

void drawTarget(int x, int y, int R, int G, int B) {
	int i;
	for(i = x+7; i < x+15; i++) {
		Paint(i,y+7,R,G,B);
	}
	for(i = x+7; i > x; i--) {
		Paint(i,y+7,R,G,B);
	}
	for(i = y+7; i < y+15; i++) {
		Paint(x+7,i,R,G,B);
	}
	for(i = y+7; i > y; i--) {
		Paint(x+7,i,R,G,B);
	}
	
}
void clearTarget(int x, int y) {
	int i,j;
	for(i = x-5; i < x+15; i++) {
		for(j = y -5; j < y+15; j++) {
			Paint(i,j,0,0,0);
		}
	}
}

void drawTank() {
	int i,j;
	for (i = 0; i < 200;i++) {
		for (j = 700; j <740;j++) {
			Paint(i,j,100,100,100);
		}
	}
	for (i = 0; i < 50;i++) {
		for (j = 670; j <700;j++) {
			Paint(i,j,100,100,100);
		}
	}
}
