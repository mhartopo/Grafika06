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
void printI(int x, int y, int r,int g,int b, char *fbp,int size);
void printH(int x, int y, int r,int g,int b, char *fbp,int size);
void printN(int x, int y, int r,int g,int b, char *fbp,int size); 
void printA(int x, int y, int r,int g,int b, char *fbp,int size);
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

     x = 500; y = 300;       // Where we are going to put the pixel

     // Figure out where in memory to put the pixel	

	int size = 80;
	for (y=650; y>0; y--) {
		printI(500+size/2,y,100,100,100,fbp,size/10);
		printH(450,y,100,100,100,fbp,size/10);
		printN(550+size/2,y,100,100,100,fbp,size/10);
		usleep(16000);
 	 	system("clear");
		size++;
	}
	//printLine(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),100,100,100,fbp);

		//printA(550,500,100,100,100,fbp,10);

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
				if (yl>y0)
					y += 1;
				else if (yl<y0)
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



void floodFill(int x, int y, int or, int og, int ob, int nr, int ng, int nb, char *fbp)
{
	int location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                        (y+vinfo.yoffset) * finfo.line_length;
	int r = *(fbp + location);
	int g = *(fbp + location + 1);
	int b = *(fbp + location + 2);
	int oldmatch = r==or && b==ob && g==og;
	int newmatch = r==nr && b==nb && g==ng;
	//printf("%d %d %d\n",r,g,b);
	//printf("old : %d |%d %d %d\n",oldmatch,or,og,ob);
	//printf("new : %d |%d %d %d\n",newmatch,nr,ng,ng);
	//printf("RES : %d\n",oldmatch && !newmatch);
    if (oldmatch && !newmatch)
    {
        tes(nr,ng,nb,x,y,fbp);
		floodFill(x+1,y,or,og,ob,nr,ng,nb,fbp);
		floodFill(x-1,y,or,og,ob,nr,ng,nb,fbp);
		floodFill(x,y+1,or,og,ob,nr,ng,nb,fbp);
		floodFill(x,y-1,or,og,ob,nr,ng,nb,fbp);           
    }    
}  

void printI(int x, int y, int r,int g,int b, char *fbp,int size) {
	printLine(x,y,x+size,y,r,g,b,fbp);
	printLine(x,y,x,y+10*size,r,g,b,fbp);
	printLine(x+size,y,x+size,y+10*size,r,g,b,fbp);
	printLine(x,y+10*size,x+size,y+10*size,r,g,b,fbp);
	floodFill(x+1,y+1,1,1,1,r,g,b,fbp);
}

void printH(int x, int y, int r,int g,int b, char *fbp,int size) {
		printLine(x,y,x+size,y,r,g,b,fbp);
		printLine(x+size,y,x+size,y+4*size,r,g,b,fbp);
		printLine(x+size,y+4*size,x+3*size,y+4*size,r,g,b,fbp);
		printLine(x+3*size,y,x+3*size,y+4*size,r,g,b,fbp);
		printLine(x+3*size,y,x+4*size,y,r,g,b,fbp);
		printLine(x,y,x,y+10*size,r,g,b,fbp);
		printLine(x+4*size,y,x+4*size,y+10*size,r,g,b,fbp);
		printLine(x+size,y+5*size,x+3*size,y+5*size,r,g,b,fbp);

		printLine(x+size,y+5*size,x+size,y+10*size,r,g,b,fbp);
		printLine(x+3*size,y+5*size,x+3*size,y+10*size,r,g,b,fbp);

		printLine(x,y+10*size,x+size,y+10*size,r,g,b,fbp);
		printLine(x+3*size,y+10*size,x+4*size,y+10*size,r,g,b,fbp);
	
		floodFill(x+1,y+1,1,1,1,r,g,b,fbp);

}

void printN(int x, int y, int r,int g,int b, char *fbp,int size) {
		printLine(x,y,x+size,y,r,g,b,fbp);  
		printLine(x+size,y,x+4*size,y+9*size,r,g,b,fbp);  
		printLine(x+4*size,y+9*size,x+4*size,y,r,g,b,fbp);  
		printLine(x+4*size,y,x+5*size,y,r,g,b,fbp);  
		printLine(x+5*size,y,x+5*size,y+10*size,r,g,b,fbp);  
		printLine(x+5*size,y+10*size,x+4*size,y+10*size,r,g,b,fbp);  
		printLine(x+4*size,y+10*size,x+size,y+size,r,g,b,fbp);  
		printLine(x+size,y+size,x+size,y+10*size,r,g,b,fbp);  
		printLine(x+size,y+10*size,x,y+10*size,r,g,b,fbp);  
		printLine(x,y+10*size,x,y,r,g,b,fbp);  
  
 
		floodFill(x+1,y+1,1,1,1,r,g,b,fbp);
}
void printA(int x, int y, int r,int g,int b, char *fbp,int size){
		printLine(x,y+10*size,x+3*size,y,r,g,b,fbp);  
		printLine(x+3*size,y,x+6*size,y+10*size,r,g,b,fbp);  
		printLine(x+6*size,y+10*size,x+5*size,y+10*size,r,g,b,fbp);  
		printLine(x+5*size,y+10*size,x+3*size,y+1*size,r,g,b,fbp);  
		printLine(x+3*size,y+1*size,x+size,y+10*size,r,g,b,fbp);  
/*
		printLine(x+size,y+5*size,x+size,y+6*size,r,g,b,fbp);  
		printLine(x+size,y+6*size,x+5*size,y+6*size,r,g,b,fbp);  
		printLine(x+5*size,y+6*size,x+size,y+5*size,r,g,b,fbp);  
		printLine(x,y,x+5*size,y+5*size,r,g,b,fbp);  */
 
}

