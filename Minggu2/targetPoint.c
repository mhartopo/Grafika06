#include "targetPoint.h"

void initTargetPoint(targetPoint *TP) {
	(*TP).x = 140;
	(*TP).y = 600;
}
int getTargetPosX(targetPoint TP) {
	return TP.x;
}
int getTargetPosY(targetPoint TP) {
	return TP.y;
}
void moveTarget(targetPoint *TP, int x, int y) {
	(*TP).x += x;
	(*TP).y += y;
}

void setTarget(targetPoint *TP, int x, int y) {
	(*TP).x = x;
	(*TP).y = y;
}
