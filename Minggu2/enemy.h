#ifndef enemy_H
#define enemy_H
typedef struct {
	int x;
	int y;
} Enemy;

void makeEnemy(int a, int b, Enemy *E);

void moveEnemy(Enemy *E);

int getEnemyPosX(Enemy E);

int getEnemyPosY(Enemy E);

void setEnemyPosX(Enemy *E, int x);

void setEnemyPosY(Enemy *E, int y);

#endif
