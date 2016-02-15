#include "enemy.h"

void makeEnemy(int a, int b, Enemy *E) {
	(*E).x = a;
	(*E).y = b;
}

void moveEnemy(Enemy *E) {
	(*E).x -= 1; 
}

int getEnemyPosX(Enemy E) {
	return E.x;
}

int getEnemyPosY(Enemy E) {
	return E.y;
}

void setEnemyPosX(Enemy *E, int x) {
	(*E).x = x;
}

void setEnemyPosY(Enemy *E, int y) {
	(*E).y = y;
}

