 #include <math.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <stdio.h>
 #include <fcntl.h>
 #include <linux/fb.h>
 #include <sys/mman.h>
 #include <sys/ioctl.h>


struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
void tes (int r,int g,int b, int x, int y, char *fbp) ;
void printLine(int xi, int yi, int xt, int yt, int r, int g, int b, char *fbp) ;
void floodFill(int x, int y, int or, int og, int ob, int nr, int ng, int nb, char *fbp);
void DrawCircle(int r, int g, int b, int x0, int y0, int radius, char *fbp);
void printplane(int x, int y, char *fbp,int size);
void printbaling(int x, int y, int rot, int size, char* fbp);
void printledak(int x, int y, int size, char* fbp);
void printPayung(int x0, int y0, int size, char* fbp);

int main(int argc, char* argv[])
 {
     int fbfd = 0;
     long int screensize = 0;
     char *fbp = 0;
     int x = 0, y = 0;
     long int location = 0;

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

     x = 700; y = 350;       // Where we are going to put the pixel

     // Figure out where in memory to put the pixel	

	int i,j,k,l;


	int rot = 0;
	for (i = 1; i<=5;i++) {
		for (l=0;l<5;l++)  {
			for (j=0;j<1200;j++) {
				for (k=0;k<700;k++) {
					tes(0,0,0,j,k,fbp);
				}
			}
			printplane(x,y,fbp,i);	
			printbaling(x,y,rot,i,fbp);
			usleep(16000);
			rot++;
		}

	}
	for (i=5; i<20;i++) {
		printledak(x,y,i,fbp);
			usleep(16000);
	}
		for (l=0;l<5;l++)  {
			for (j=0;j<1200;j++) {
				for (k=0;k<700;k++) {
					tes(0,0,0,j,k,fbp);
				}
			}
		}
	int z = 150;
    while (z < 700) {
		for (l=0;l<5;l++)  {
			for (j=0;j<1200;j++) {
				for (k=0;k<700;k++) {
					tes(0,0,0,j,k,fbp);
				}
			}
		}
		printPayung(700, z, 100, fbp);
		z = z+5;
		usleep(16000);
	}
/*	
	for (i=40; i>=5;i--) {
		printledak(x,y,i,fbp);
			usleep(16000);
		for (l=0;l<5;l++)  {
			for (j=0;j<1200;j++) {
				for (k=0;k<700;k++) {
					tes(0,0,0,j,k,fbp);
				}
			}
		}
	}*/

//printledak(700,500,i,fbp);
		//DrawCircle(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),x,y,5,fbp);
		//floodFill(x,y,0,0,0,atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),fbp);
     munmap(fbp, screensize);
     close(fbfd);
     return 0;
}

void tes (int r,int g,int b, int x, int y, char *fbp) {
	int location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                        (y+vinfo.yoffset) * finfo.line_length;

                 *(fbp + location) = r;        // Some blue
                 *(fbp + location + 1) = g;     // A little green
                 *(fbp + location + 2) = b;    // A lot of red
                 *(fbp + location + 3) = 0;      // No transparency

}
/*
void printLine(int xi, int yi, int xt, int yt, int r, int g, int b, char *fbp) {
	int x0,xl,y0,yl;
	float deltax = xt-xi;
	float deltay = yt-yi;
	float error = 0;
	float deltaerr;
    int x,y;
	if (deltax!=0) {
		if (deltax>=0) {
			x0=xi;xl=xt;y0=yi;yl=yt;
		} else {
			x0=xt;xl=xi;y0=yt;yl=yi;
		}
		y = y0;
		deltaerr = abs(deltay/deltax);
		for (x=x0; x<xl; x++) {
			tes(r,g,b,x,y,fbp);
		//printf("%d %d %f\n",x,y,error);
			error += deltaerr;
			while (error >= 0.5) {
				tes(r,g,b,x,y,fbp);
		//printf("%d %d %f\n",x,y,error);
				if (yl>y0,fbp)
					y += 1;
				else if (yl<y0,fbp)
					y -= 1;
				error -= 1;
			}
		}
	} else {
		if (deltay>=0) {
			y0=yi;yl=yt;x0=xi;xl=xt;
		} else {
			y0=yt;yl=yi;x0=xi;xl=xt;
		}
		x=x0;
		for (y=y0;y<yl;y++) {
			tes(r,g,b,x,y,fbp);			
		}
	}

}
*/
void printPayung(int x0, int y0, int size, char *fbp) {
		int x,y;
		int t = x0+size;
		int titikPusat = x0 + size;
		int titikBawahY = y0 + size*2;
		int h = (y0 % (size / 1)) - (size/2);
		
		//size div 8
		
		if (h > (size/4)){
			h = size/4 - (h-size/4);
		}
		
		//payung
	    for (y = y0; y < y0+(size*2); y++) {
        	for (x = x0; x < x0+(size*2); x++) {
				if (((x-x0-size)*(x-x0-size))+((y-y0-size)*(y-y0-size)) <= (size*size)){
					int h2 = ((x-titikPusat)*h/(x0-titikPusat));
					if (y <= (y0 + size + h2)){
						tes(100,100,100, x,y, fbp);
					}
				}
	        }
	    }
	    //pilot
	    int xPilot, yPilot;
	    xPilot = titikPusat + h;
	    yPilot = titikBawahY + h;
	    for(x = (xPilot-7); x<=(xPilot+7); x++){
			for(y = titikBawahY; y<=titikBawahY+50; y++){
				tes(100,100,100,x,y,fbp);
			}
		} 
		printLine(xPilot, titikBawahY, x0, y0+size+h, 100, 100, 100, fbp);
		printLine(xPilot, titikBawahY, x0+size*2, y0+size-h, 100, 100, 100, fbp);
	}
	
void printLine(int x0, int y0, int x1, int y1, int r, int g, int b, char *fbp) {
 
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  for(;;){
	tes(r,g,b,x0,y0,fbp);
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}


void floodFill(int x, int y, int or, int og, int ob, int nr, int ng, int nb, char *fbp)
{
	int location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                        (y+vinfo.yoffset) * finfo.line_length;
	int r = *(fbp + location);
	int g = *(fbp + location + 1);
	int b = *(fbp + location + 2);
	int newmatch = r==nr && b==nb && g==ng;
	int oldmatch = r==or && b==ob && g==og;
	//printf("%d %d %d\n",r,g,b);
	//printf("old : %d |%d %d %d\n",oldmatch,or,og,ob);
	//printf("new : %d |%d %d %d\n",newmatch,nr,ng,ng);
	//printf("RES : %d\n",oldmatch && !newmatch);
    if (!oldmatch && !newmatch)
    {
        tes(nr,ng,nb,x,y,fbp);
		floodFill(x+1,y,or,og,ob,nr,ng,nb,fbp);
		floodFill(x-1,y,or,og,ob,nr,ng,nb,fbp);
		floodFill(x,y+1,or,og,ob,nr,ng,nb,fbp);
		floodFill(x,y-1,or,og,ob,nr,ng,nb,fbp);           
    }    
}  

void DrawCircle(int r, int g, int b, int x0, int y0, int radius, char *fbp) {

	int x = radius;
	int y = 0;
	int decision = 1 - x;
	while (y <= x) {
		tes(r,g,b, x + x0,  y + y0,fbp); // Octant 1
		tes(r,g,b, y + x0,  x + y0,fbp); // Octant 2
		tes(r,g,b,-x + x0,  y + y0,fbp); // Octant 4
		tes(r,g,b,-y + x0,  x + y0,fbp); // Octant 3
		tes(r,g,b,-x + x0, -y + y0,fbp); // Octant 5
		tes(r,g,b,-y + x0, -x + y0,fbp); // Octant 6
		tes(r,g,b, x + x0, -y + y0,fbp); // Octant 7
		tes(r,g,b, y + x0, -x + y0,fbp); // Octant 8
		y++;
		if (decision<=0) {
			decision += 2*y + 1;
		} else {
			x--;
			decision += 2*(y-x) + 1;

		}
	}

}

void printplane(int x, int y, char *fbp,int size) {
//kokpit
	
	printLine(x+5*size,y-20-2*size,x+5*size,y-20-5*size, 100, 100, 100, fbp);
	printLine(x+5*size,y-20-5*size,x+3*size,y-20-8*size, 100, 100, 100, fbp);
	printLine(x+3*size,y-20-8*size,x,y-20-8*size, 100, 100, 100, fbp);

	printLine(x-5*size,y-20-2*size,x-5*size,y-20-5*size, 100, 100, 100, fbp);
	printLine(x-5*size,y-20-5*size,x-3*size,y-20-8*size, 100, 100, 100, fbp);
	printLine(x-3*size,y-20-8*size,x,y-20-8*size, 100, 100, 100, fbp);

	printLine(x,y-20-4*size,x,y-20-10*size, 100, 100, 100, fbp);	
	printLine(x+5*size,y-20-2*size,x-5*size,y-20-2*size, 100, 100, 100, fbp);	

	floodFill(x+5*size-1,y-20-2*size-size,100,100,100,10,10,10,fbp);

//kokpit

//tengah	
	DrawCircle(100,100,100,x,y,20+size,fbp);
	DrawCircle(100,100,100,x,y,20+2*size,fbp);
	DrawCircle(100,100,100,x,y,20+4*size,fbp);

	floodFill(x+20+4*size-1,y+1,100,100,100,10,50,50,fbp);
	floodFill(x-1,y-20-4*size+1,100,100,100,10,50,50,fbp);

	floodFill(x+20+2*size-1,y+1,100,100,100,50,50,50,fbp);
	floodFill(x,y,100,100,100,30,30,30,fbp);
//tengah	

//sayap
	printLine(x+20+4*size,y,x+40+24*size,y, 100, 100, 100, fbp);
	printLine(x+20+4*size,y-size,x+20+24*size,y-size, 100, 100, 100, fbp);
	printLine(x+20+3*size,y+2*size,x+20+24*size,y+2*size, 100, 100, 100, fbp);
	printLine(x+20+24*size,y-size,x+40+24*size,y, 100, 100, 100, fbp);	
	printLine(x+20+24*size,y+2*size,x+40+24*size,y, 100, 100, 100, fbp);		

	printLine(x-20-4*size,y,x-40-24*size,y, 100, 100, 100, fbp);
	printLine(x-20-4*size,y-size,x-20-24*size,y-size, 100, 100, 100, fbp);
	printLine(x-20-3*size,y+2*size,x-20-24*size,y+2*size, 100, 100, 100, fbp);
	printLine(x-20-24*size,y+2*size,x-40-24*size,y, 100, 100, 100, fbp);	
	printLine(x-20-24*size,y-size,x-40-24*size,y, 100, 100, 100, fbp);	

	floodFill(x+20+4*size+1,y-1,100,100,100,100,100,80,fbp);
	floodFill(x-20-4*size-1,y-1,100,100,100,100,100,80,fbp);
	floodFill(x-20-4*size-1,y+1,100,100,100,10,10,50,fbp);
	floodFill(x+20+4*size+1,y+1,100,100,100,10,10,50,fbp);

//sayap

//kaki + roda
	printLine(x+size,y+20+4*size,x+5*size,y+20+8*size, 100, 100, 100, fbp);
	printLine(x+2*size,y+20+4*size,x+6*size,y+20+8*size, 100, 100, 100, fbp);
	printLine(x+5*size,y+20+8*size,x+6*size,y+20+8*size, 100, 100, 100, fbp);
	printLine(x+size,y+20+4*size,x+2*size,y+20+4*size, 100, 100, 100, fbp);

	printLine(x+5*size,y+20+8*size,x+6*size,y+20+8*size, 100, 100, 100, fbp);
	printLine(x+5*size,y+20+10*size,x+6*size,y+20+10*size, 100, 100, 100, fbp);
	printLine(x+5*size,y+20+8*size,x+5*size,y+20+10*size, 100, 100, 100, fbp);
	printLine(x+6*size,y+20+8*size,x+6*size,y+20+10*size, 100, 100, 100, fbp);
	
	printLine(x-size,y+20+4*size,x-5*size,y+20+8*size, 100, 100, 100, fbp);
	printLine(x-2*size,y+20+4*size,x-6*size,y+20+8*size, 100, 100, 100, fbp);
	printLine(x-5*size,y+20+8*size,x-6*size,y+20+8*size, 100, 100, 100, fbp);
	printLine(x-size,y+20+4*size,x-2*size,y+20+4*size, 100, 100, 100, fbp);

	printLine(x-5*size,y+20+8*size,x-6*size,y+20+8*size, 100, 100, 100, fbp);
	printLine(x-5*size,y+20+10*size,x-6*size,y+20+10*size, 100, 100, 100, fbp);
	printLine(x-5*size,y+20+8*size,x-5*size,y+20+10*size, 100, 100, 100, fbp);
	printLine(x-6*size,y+20+8*size,x-6*size,y+20+10*size, 100, 100, 100, fbp);

	//floodFill(x+2*size-1,y+20+4*size+2,100,100,100,200,200,200,fbp);
	//printLine(x+2*size-1,y-100,x+2*size-1,y+100, 00, 100, 100, fbp);	
	//printLine(x-100,y+20+4*size+2,x+100,y+20+4*size+2, 00, 100, 100, fbp);	
//kaki + roda


//ekor
	printLine(x+size,y-20-8*size,x+size,y-20-12*size, 100, 100, 100, fbp);	
	printLine(x-size,y-20-8*size,x-size,y-20-12*size, 100, 100, 100, fbp);	

	printLine(x-size,y-20-12*size,x,y-20-14*size, 100, 100, 100, fbp);	
	printLine(x+size,y-20-12*size,x,y-20-14*size, 100, 100, 100, fbp);	

	floodFill(x+size-1,y-20-12*size-1,100,100,100,100,100,80,fbp);
//ekor
}

void printbaling(int x, int y, int rot, int size, char* fbp) {
	int dx = (int) 10*size* cos (rot);
	int dy = (int) 10*size* sin (rot);
	printLine(x,y,x+dx,y+dy+size, 200, 200, 200, fbp);	
	printLine(x,y,x+dx,y+dy-size, 200, 200, 200, fbp);		
	printLine(x+dx,y+dy+size,x+dx,y+dy-size, 200, 200, 200, fbp);	
	printLine(x,y,x-dx,y-dy-size, 200, 200, 200, fbp);		
	printLine(x,y,x-dx,y-dy+size, 200, 200, 200, fbp);		
	printLine(x-dx,y-dy+size,x-dx,y-dy-size, 200, 200, 200, fbp);		

}

void printledak(int x, int y, int size, char* fbp) {
	int r=0;
	int g=100;
	int b=100;
	DrawCircle(r,g,b,x,y,size*8,fbp);
	floodFill(x+size*8-1,y,r,g,b,r,g,b,fbp);
}
