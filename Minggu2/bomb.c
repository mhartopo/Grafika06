#include "bomb.h"

void makeBomb(int x1, int y1, Bomb *B) {
	int x0 = 0; int y0 = 670-15;
	(*B).x = x0;
	(*B).y = y0;
	(*B).x1 = x1;
	(*B).y1 = y1;
	(*B).dx = abs(x1-x0), (*B).sx = x0<x1 ? 4 : -4;
	(*B).dy = abs(y1-y0), (*B).sy = y0<y1 ? 4 : -4; 
	(*B).err = ((*B).dx>(*B).dy ? (*B).dx : -(*B).dy)/2, (*B).e2;
	(*B).active = 0;
}
int getPosX(Bomb B) {
	return B.x;
}
int getPosY(Bomb B) {
	return B.y;
}

void setX(int x, Bomb *B) {
	(*B).x = x;
}
void setY(int y, Bomb *B) {
	(*B).y = y;
}
void setActive(Bomb *B,int act) {
	(*B).active = act;
}

int isActive(Bomb B) {
	return B.active;
}

void nextStep(Bomb *B) {
	(*B).e2 = (*B).err;
	if ((*B).e2 > -1*(*B).dx) { 
		(*B).err -= (*B).dy;
		(*B).x += (*B).sx;
	}
	if ((*B).e2 < (*B).dy) { 
		(*B).err += (*B).dx;
		(*B).y += (*B).sy; 
	}
}
