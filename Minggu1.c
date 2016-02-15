#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

int main() {
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize = 0;
    char *fbp = 0;
    int x = 0, y = 0, z=0;
    long int location = 0;

	void Print(int R, int G, int B) {
		location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (y+vinfo.yoffset) * finfo.line_length;

                *(fbp + location) = B;        //Blue
                *(fbp + location + 1) = G;     //Green
                *(fbp + location + 2) = R;    //Red
                *(fbp + location + 3) = 0;      //Transparency
	}

	void PrintHitam() {
		for (y = 0; y < 760; y++) {
			for (x = 0; x < 1360; x++) {
				Print(0,0,0);
			}
		}
	}

	void PrintHurufNofan(int x0, int y0) {
	//Huruf N
	    for (y = y0; y < y0+200; y++) {
        	for (x = x0; x < x0+30; x++) {
			Print(204+y-x,0+x-y,102+x+y);
        	}
	    }
	    for (y = y0; y < y0+200; y++) {
        	for (x = x0+30; x < x0+30+0.6*(y-y0); x++) {
			Print(204+y-x,0+x-y,102+x+y);
        	}
	    }	
	    for (y = y0+60; y < y0+200; y++) {
	        for (x = x0+30; x < x0+30+0.6*(y-y0-60); x++) {
			Print(0,0,0);
	        }
	    }
	    for (y = y0; y < y0+200; y++) {
	        for (x = x0+120; x < x0+150; x++) {
			Print(204+y-x,0+x-y,102+x+y);
	        }
	    }

	//Huruf O
	    for (y = y0; y < y0+200; y++) {
        	for (x = x0+180; x < x0+380; x++) {
			if (((x-x0-280)*(x-x0-280))+((y-y0-100)*(y-y0-100)) <= 10000)
			Print(204+y-x,0+x-y,102+x+y);
	        }
	    }
	    for (y = y0+30; y < y0+170; y++) {
        	for (x = x0+210; x < x0+350; x++) {
			if (((x-x0-280)*(x-x0-280))+((y-y0-100)*(y-y0-100)) <= 4900)
			Print(0,0,0);
	        }
	    }

	//Huruf F
	    for (y = y0; y < y0+200; y++) {
        	for (x = x0+410; x < x0+440; x++) {
			Print(204+y-x,0+x-y,102+x+y);
        	}
	    }
	    for (y = y0; y < y0+30; y++) {
	        for (x = x0+440; x < x0+540; x++) {
			Print(204+y-x,0+x-y,102+x+y);
	        }
	    }
	    for (y = y0+85; y < y0+115; y++) {
        	for (x = x0+440; x < x0+540; x++) {
			Print(204+y-x,0+x-y,102+x+y);
        	}
	    }

	//Huruf A
	    for (y = y0; y < y0+200; y++) {
	        for (x = x0+650; x > x0+650-0.5*(y-y0); x--) {
			Print(204+y-x,0+x-y,102+x+y);
        	}
	    }
	    for (y = y0; y < y0+200; y++) {
        	for (x = x0+650; x < x0+650+0.5*(y-y0); x++) {
			Print(204+y-x,0+x-y,102+x+y);
	        }
	    }
	    for (y = y0+60; y < y0+200; y++) {
        	for (x = x0+650; x > x0+650-0.5*(y-y0-60); x--) {
			Print(0,0,0);
        	}
	    }
	    for (y = y0+60; y < y0+200; y++) {
        	for (x = x0+650; x < x0+650+0.5*(y-y0-60); x++) {
			Print(0,0,0);
        	}
	    }
	    for (y = y0+110; y < y0+140; y++) {
	        for (x = x0+600; x < x0+700; x++) {
			Print(204+y-x,0+x-y,102+x+y);
	        }
	    }

	//Huruf N
	    for (y = y0; y < y0+200; y++) {
	        for (x = x0+780; x < x0+810; x++) {
			Print(204+y-x,0+x-y,102+x+y);
	        }
	    }
	    for (y = y0; y < y0+200; y++) {
	        for (x = x0+810; x < x0+810+0.6*(y-y0); x++) {
			Print(204+y-x,0+x-y,102+x+y);
	        }
	    }
	    for (y = y0+60; y < y0+200; y++) {
	        for (x = x0+810; x < x0+810+0.6*(y-y0-60); x++) {
			Print(0,0,0);
	        }
	    }
	    for (y = y0; y < y0+200; y++) {
	        for (x = x0+900; x < x0+930; x++) {
			Print(204+y-x,0+x-y,102+x+y);
	        }
	    }
	
	}

	void PrintHurufBen(int x0, int y0) {

	//Huruf B
	    for (y = y0; y < y0+200; y++) {
	        for (x = x0; x < x0+30; x++) {
			Print(0+y-x,102+x-y,204+x+y);
	        }
	    }
	    for (y = y0; y < y0+100; y++) {
        	for (x = x0+30; x < x0+130; x++) {
			if (((x-x0-30)*(x-x0-30))+((y-y0-50)*(y-y0-50)) <= 2500)
			Print(0+y-x,102+x-y,204+x+y);
	        }
	    }
	    for (y = y0+10; y < y0+90; y++) {
        	for (x = x0+30; x < x0+110; x++) {
			if (((x-x0-30)*(x-x0-30))+((y-y0-50)*(y-y0-50)) <= 900)
			Print(0,0,0);
	        }
	    }

	    for (y = y0+100; y < y0+200; y++) {
        	for (x = x0+30; x < x0+130; x++) {
			if (((x-x0-30)*(x-x0-30))+((y-y0-150)*(y-y0-150)) <= 2500)
			Print(0+y-x,102+x-y,204+x+y);
	        }
	    }
	    for (y = y0+110; y < y0+190; y++) {
        	for (x = x0+30; x < x0+130; x++) {
			if (((x-x0-30)*(x-x0-30))+((y-y0-150)*(y-y0-150)) <= 900)
			Print(0,0,0);
	        }
	    }

	    

	//Huruf E
	    for (y = y0; y < y0+200; y++) {
        	for (x = x0+120; x < x0+150; x++) {
			Print(0+y-x,102+x-y,204+x+y);
        	}
	    }
	    for (y = y0; y < y0+30; y++) {
	        for (x = x0+150; x < x0+250; x++) {
			Print(0+y-x,102+x-y,204+x+y);
	        }
	    }
	    for (y = y0+85; y < y0+115; y++) {
        	for (x = x0+150; x < x0+250; x++) {
			Print(0+y-x,102+x-y,204+x+y);
        	}
	    }
	    for (y = y0+170; y < y0+200; y++) {
        	for (x = x0+150; x < x0+250; x++) {
			Print(0+y-x,102+x-y,204+x+y);
        	}
	    }

	//Huruf N
	    for (y = y0; y < y0+200; y++) {
	        for (x = x0+280; x < x0+310; x++) {
			Print(0+y-x,102+x-y,204+x+y);
	        }
	    }
	    for (y = y0; y < y0+200; y++) {
	        for (x = x0+310; x < x0+310+0.6*(y-y0); x++) {
			Print(0+y-x,102+x-y,204+x+y);
	        }
	    }
	    for (y = y0+60; y < y0+200; y++) {
	        for (x = x0+310; x < x0+310+0.6*(y-y0-60); x++) {
			Print(0,0,0);
	        }
	    }
	    for (y = y0; y < y0+200; y++) {
	        for (x = x0+400; x < x0+430; x++) {
			Print(0+y-x,102+x-y,204+x+y);
	        }
	    }

	}

	void PrintHurufFikri(int x0, int y0) {
	//Huruf F
	    for (y = y0; y < y0+200; y++) {		
        	for (x = x0; x < x0+30; x++) {
			Print(255+y-x,128+x-y,0+x+y);
        	}
	    }
	    for (y = y0; y < y0+30; y++) {
	        for (x = x0+30; x < x0+130; x++) {
			Print(255+y-x,128+x-y,0+x+y);
	        }
	    }
	    for (y = y0+85; y < y0+115; y++) {
        	for (x = x0+30; x < x0+130; x++) {
			Print(255+y-x,128+x-y,0+x+y);
        	}
	    }
	//Huruf I
		for(y = y0; y < y0+200; y++){
			for(x = x0+190; x < x0+220; x++){
				Print(255+y-x,128+x-y,0+x+y);
			}
		}
	//Huruf K
		for(y = y0; y < y0+200; y++){
			for(x = x0+270; x < x0+300; x++){
				Print(255+y-x,128+x-y,0+x+y);
			}
		}
		for(y = y0; y < y0+100; y++){
			for(x = x0+385; x > x0+353-0.6*(y-y0); x=x-1){
				Print(255+y-x,128+x-y,0+x+y);
			}
		}
		for(y = y0; y < y0+100; y++){
			for(x = x0+385; x > x0+353-0.6*(y-y0-60); x=x-1){
				Print(0,0,0);
			}
		}
		
		for(y = y0+100; y < y0+200; y++){
			for(x = x0+280; x < x0+270+0.6*(y-y0); x++){
				Print(255+y-x,128+x-y,0+x+y);
			}
		}
		for(y = y0+100; y < y0+200; y++){
			for(x = x0+300; x < x0+270+0.6*(y-y0-60); x++){
				Print(0,0,0);
			}
		}
	//Huruf R
		for(y = y0; y < y0+200; y++){
			for(x = x0+435; x < x0+465; x++){
				Print(255+y-x,128+x-y,0+x+y);
			}
		}	
		
	    for (y = y0; y < y0+120; y++) {
        	for (x = x0+460; x < x0+595; x++) {
				if (((x-x0-460)*(x-x0-460))+((y-y0-60)*(y-y0-60)) <= 3600)
					Print(255+y-x,128+x-y,0+x+y);
				}
	    }
	    
	    for (y = y0+20; y < y0+100; y++) {
        	for (x = x0+460; x < x0+555; x++) {
				if (((x-x0-460)*(x-x0-460))+((y-y0-60)*(y-y0-60)) <= 1300)
					Print(0,0,0);
				}
	    }
		for(y = y0+100; y < y0+200; y++){
			for(x = x0+445; x < x0+405+0.6*(y-y0); x++){
				Print(255+y-x,128+x-y,0+x+y);
			}
		}
		for(y = y0+100; y < y0+200; y++){
			for(x = x0+465; x < x0+375+0.6*(y-y0); x++){
				Print(0,0,0);
			}
		}	
	//Huruf I
		for(y = y0; y < y0+200; y++){
			for(x = x0+570; x < x0+600; x++){
				Print(255+y-x,128+x-y,0+x+y);
			}
		}
	}

	void printMuhtar(int xin, int yin) {
	//Huruf M
	int x0 = xin;
	int y0 = yin;

	for (y = y0; y < y0+200; y++) {
		for (x = x0; x < x0+30; x++) {
			Print(0+y-x,102+x-y,204+x+y);
		}
	}
	float slopeM = 100/60+1;
	for(x = x0+30; x < x0+150/2; x++) {
		for(y = y0+slopeM*(x-x0-30); y < y0 + slopeM*(x-x0-30)+70; y++ ) {
			Print(0+y-x,102+x-y,204+x+y);
		}	    
	}

	for(x = x0+120; x >= x0 + 150/2; x--) {
		 for(y = y0-slopeM*(x-x0-120); y < y0 - slopeM*(x-x0-120)+70; y++ ) {
			Print(0+y-x,102+x-y,204+x+y);
		}   
	}

	for (y = y0; y < y0+200; y++) {
		for (x = x0+120; x < x0+150; x++) {
			Print(0+y-x,102+x-y,204+x+y);
		}
	}

	x0 += 180;
	//huruf U
	for(y = y0; y < y0+200; y++) {
		for(x = x0;x < x0 + 30; x++) {
			Print(0+y-x,102+x-y,204+x+y);
		}
	}
	for(y = y0 + 200-30; y < y0+200; y++) {
		for(x = x0; x < x0 + 150; x++) {
			Print(0+y-x,102+x-y,204+x+y);
		}
	}
	for(y = y0; y < y0+200; y++) {
		for(x = x0+150-30;x < x0+150; x++) {
			Print(0+y-x,102+x-y,204+x+y);
		}
	}
	x0 += 180;
	//huruf H
	for(y = y0; y < y0+200; y++) {
		for(x = x0; x < x0+30; x++) {
			Print(0+y-x,102+x-y,204+x+y);
		}
	}
	for(y = y0 + 100-15; y < y0+100+15; y++) {
		for(x = x0; x < x0 + 150; x++) {
			Print(0+y-x,102+x-y,204+x+y);
		}
	}
	for(y = y0; y < y0+200; y++) {
		for(x = x0+150-30;x < x0+150; x++) {
			Print(0+y-x,102+x-y,204+x+y);
		}
	}
	x0 += 180;
	//Huruf T
	for(y = y0; y < y0+30; y++) {
		for(x = x0; x < x0 +150; x++) {
			Print(0+y-x,102+x-y,204+x+y);
		}		
	}
	for(y = y0+30; y < y0+200; y++){			
		for(x = x0 + 60; x < x0+60+30; x++){
			Print(0+y-x,102+x-y,204+x+y);
		}
	}
	x0 += 180+60;
	//Huruf A
	for (y = y0; y < y0+200; y++) {
		for (x = x0; x > x0-0.5*(y-y0); x--) {
			Print(0+y-x,102+x-y,204+x+y);
		}
		}
	for (y = y0; y < y0+200; y++) {
		for (x = x0; x < x0+0.5*(y-y0); x++) {
			Print(0+y-x,102+x-y,204+x+y);
		}
	}
	for (y = y0+60; y < y0+200; y++) {
		for (x = x0; x > x0-0.5*(y-y0-60); x--) {
			Print(0,0,0);
		}
	}
	for (y = y0+60; y < y0+200; y++) {
		for (x = x0; x < x0+0.5*(y-y0-60); x++) {
			Print(0,0,0);
		}
	}
	for (y = y0+110; y < y0+140; y++) {
		for (x = x0-50; x < x0+50; x++) {
			Print(0+y-x,102+x-y,204+x+y);
		}
	}
	//Huruf R
	x0 += 130;
	for(y = y0; y < y0 + 200; y++) {
		for(x = x0; x < x0 + 30; x++) {
			Print(0+y-x,102+x-y,204+x+y);
		}
	}

	for(y = y0; y < y0 + 100; y++) {
		for(x = x0+120; x < x0 +150; x++) {
			Print(0+y-x,102+x-y,204+x+y);
		}
	}
	for(y = y0; y < y0 + 30; y++) {
		for(x = x0+30; x < x0 +120; x++) {
			Print(0+y-x,102+x-y,204+x+y);
		}
	}
	for(y = y0 + 100 - 15; y < y0 + 100+15; y++) {
		for(x = x0+30; x < x0 +150; x++) {
			Print(0+y-x,102+x-y,204+x+y);
		}
	}

	float slope = (150-60)/(200 - 110);
	for (y = y0 + 100+15 ; y < y0+200; y++) {
		for(x = x0+60+slope*(y-(y0+115)); x < x0 +42+60 +slope*(y-(y0+115)); x++) {
			Print(0+y-x,102+x-y,204+x+y);
		}
	}

	}

		void tes (int r,int g,int b, int x, int y, char *fbp) {
	int location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                        (y+vinfo.yoffset) * finfo.line_length;

                 *(fbp + location) = r;        // Some blue
                 *(fbp + location + 1) = g;     // A little green
                 *(fbp + location + 2) = b;    // A lot of red
                 *(fbp + location + 3) = 0;      // No transparency

}

	void pA(int xpos,int ypos, char *fbp) {
	int vthick = 5;
	int hthick = 5;
	int count;
	int x,y,a;
	count = 0;
	y = ypos;
	x = xpos + 50;

	for (y = ypos ; y< ypos + 100; y++) {
		for (a=0;a<vthick;a++) {
			tes(255+y-x,128+x-y,0+x+y, x-2+a+count/3, y, fbp);
			tes(255+y-x,128+x-y,0+x+y, x+2-a-count/3, y, fbp);
		}
	
		count++;	
	}
	
	for (x=xpos+33; x< xpos+68; x++) {
		for (y= ypos+50; y < ypos + 50 + hthick; y++) {
			tes(255+y-x,128+x-y,0+x+y, x, y, fbp);
		}
	}
}

void pN(int xpos,int ypos, char *fbp) {
	int vthick = 6;
	int hthick = 4;
	int count;
	int x,y;

	for (x = xpos; x < xpos+vthick; x++)
		for (y = ypos; y< ypos + 100; y++)
			tes(255+y-x,128+x-y,0+x+y, x, y, fbp);
	for (x = xpos+50; x < xpos+50+vthick; x++)
		for (y = ypos; y< ypos + 100; y++)
			tes(255+y-x,128+x-y,0+x+y, x, y, fbp);
	count = 0;
	y = 0;
	x = xpos+vthick-2;
    while (y<ypos+100) {
		for (y = ypos+2*count; y<ypos+2*hthick+2*count; y++) {
			tes(255+y-x,128+x-y,0+x+y, x, y, fbp);
		}
		x++;
		count++;
	}
	
}
void pH(int xpos,int ypos, char *fbp) {
	int vthick = 6;
	int hthick = 4;
	int count;
	int x,y;

	for (x = xpos; x < xpos+vthick; x++)
		for (y = ypos; y< ypos + 100; y++)
			tes(255+y-x,128+x-y,0+x+y, x, y, fbp);
	for (x = xpos+50; x < xpos+50+vthick; x++)
		for (y = ypos; y< ypos + 100; y++)
			tes(255+y-x,128+x-y,0+x+y, x, y, fbp);
	for (x = xpos; x < xpos+50+vthick; x++)
		for (y = ypos+49; y< ypos+49 + hthick; y++)
			tes(255+y-x,128+x-y,0+x+y, x, y, fbp);

}

void pI(int xpos,int ypos, char *fbp) {
	int vthick = 6;
	int hthick = 3;
	int count;
	int x,y;
	for (x = xpos+20; x < xpos+20+ vthick; x++)
		for (y = ypos; y< ypos + 100; y++)
			tes(255+y-x,128+x-y,0+x+y, x, y, fbp);

	
}
void pR(int xpos,int ypos, char *fbp) {
	int vthick = 5;
	int hthick = 8;
	int count;
	int x,y;
	for (x = xpos; x<xpos+vthick; x++)
		for (y = ypos; y<ypos+100; y++)
			tes(255+y-x,128+x-y,0+x+y, x, y, fbp);
	count = 0;
	y = 0;
    while (y<ypos+100) {
		for (y = ypos+40+count; y<ypos+40+hthick+count; y++) {
			tes(255+y-x,128+x-y,0+x+y, x, y, fbp);
		}
		x++;
		count++;
	}
	
	for (x = xpos; x<xpos+45; x++)
		for (y = ypos; y<ypos+vthick ; y++) {
			tes(255+y-x,128+x-y,0+x+y, x, y, fbp);
			tes(255+y-x,128+x-y,0+x+y, x, y+40, fbp);
		}
	count = 0;
	for (x = xpos+45; x<xpos+45+vthick; x++) {
		for (y = ypos+count; y<ypos+45-count; y++)
			tes(255+y-x,128+x-y,0+x+y, x, y, fbp);
		count++;
	}

}



	void Main() {

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
	    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
	    if ((int)fbp == -1) {
	        perror("Error: failed to map framebuffer device to memory");
	        exit(4);
	    }
	    printf("The framebuffer device was mapped to memory successfully.\n");
	
	    // Figure out where in memory to put the pixel
	    z = 500;
            while (z > 20) {
		PrintHitam();
		PrintHurufNofan(150,z);//NOFAN
		usleep(100000);
		z = z-20;
	    }
	    z = 500;
            while (z > 20) {
		PrintHitam();
		PrintHurufBen(250,z);//BEN
		usleep(100000);
		z = z-20;
	    }
	    z = 500;
            while (z > 20) {
		PrintHitam();
		PrintHurufFikri(150,z);//FIKRI
		usleep(100000);
		z = z-20;
	    }
	    z = 500;
            while (z > 20) {
		PrintHitam();
		printMuhtar(125,z);//MUHTAR
		usleep(100000);
		z = z-20;
	    }
	    x = 500;
	    for ( y = 500; y > 20; y-=20) {
		//RAIHAN
		int ax,ay;
		for (ax = 0; ax<1360;ax++) {
			for (ay = 0; ay < 760; ay++)
				tes(0,0,0, ax, ay, fbp);
		}
		pR(x,y, fbp);
		pA(x+50,y, fbp);
		pI(x+130,y, fbp);
		pH(x+180,y, fbp);
		pA(x+230,y, fbp);
		pN(x+330,y, fbp);
		usleep(100000);
	    }

	    munmap(fbp, screensize);
	    close(fbfd);
	}

	Main();
	return 0;
}
