/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <cmath>
#include "gwindow.h"
#include "simpio.h"
#include "gtypes.h"
using namespace std;

void drawSierpinski(GWindow &gw,int n, double x1,double y1,double x2,double y2,double x3,double y3);

int main() {
		int edge=getInteger("edge size: ");
		int n=getInteger("order: ");
		GWindow gw;
		double x1=gw.getWidth()/2;
		double x2=x1+edge/2;
		double x3=x1-edge/2;
		double h=edge*sqrt(3.0)/2;
		double y1=(gw.getHeight()-h)/2;
		double y2=y1+h;
		double y3=y1+h;
		gw.drawLine(x1,y1,x2,y2);
		drawSierpinski(gw,n,x1,y1,x2,y2,x3,y3);
    return 0;
}

void drawSierpinski(GWindow &gw, int n, double x1,double y1,double x2,double y2,double x3,double y3){
	if(n<0)return;
	else{
		gw.drawLine(x1,y1,x2,y2);
		gw.drawLine(x2,y2,x3,y3);
		gw.drawLine(x3,y3,x1,y1);
		//drawSierpinski(gw,n-1,x1,y2,x1-(x2-x3)/4,y1+(y2-y1)/2,x1+(x2-x3)/4,y1+(y2-y1)/2);
		drawSierpinski(gw,n-1,x1,y1,x1+(x2-x3)/4,y1+(y2-y1)/2,x1-(x2-x3)/4,y1+(y2-y1)/2);
		drawSierpinski(gw,n-1,x1+(x2-x3)/4,y1+(y2-y1)/2,x2,y2,x1,y2);
		drawSierpinski(gw,n-1,x1-(x2-x3)/4,y1+(y2-y1)/2,x1,y2,x3,y3);
	}
}