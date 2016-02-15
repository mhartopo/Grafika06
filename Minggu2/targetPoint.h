#ifndef targetPoint_H
#define targetPoint_H

typedef struct {
	int x;
	int y;
} targetPoint;

void initTargetPoint(targetPoint *TP);
int getTargetPosX(targetPoint TP);
int getTargetPosY(targetPoint TP);
void moveTarget(targetPoint *TP, int x, int y);
void setTarget(targetPoint *TP, int x, int y);

#endif
