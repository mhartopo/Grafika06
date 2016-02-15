#ifndef bomb_H
#define bomb_H
	typedef struct {
		int x, y;
		int x1,y1;
		int dx,dy,sx,sy,err,e2;
		int active;
	} Bomb;
	
	void makeBomb(int x1, int y1, Bomb *B);
	int getPosX(Bomb B);
	int getPosY(Bomb B);
	void setX(int x, Bomb *B);
	void setY(int y, Bomb *B);
	void setActive(Bomb *B, int act);
	int isActive(Bomb B);
	void nextStep(Bomb *B);
	
#endif
