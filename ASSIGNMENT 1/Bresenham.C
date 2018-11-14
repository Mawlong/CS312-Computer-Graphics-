//Implementation of Bresenham's Line Drawing Algorithm
//To draw a triangle and rectangle

#include <graphics.h>
#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include <dos.h>

void draw_line(int, int, int, int);
void draw_max(int, int, int, int);
void draw_min(int, int, int, int);
int checkTri(int, int, int, int, int, int);
int checkRect(int, int, int, int, int, int, int, int);


void main()
 {
	int x1, y1, x2, y2, x3, y3, x4, y4, choice;
	int gd=DETECT,gm;

	initgraph(&gd, &gm, "C:\\turboC3\\BGI");

	printf("Enter the first point(x1,y1): ");
	scanf("%d%d",&x1,&y1);

    printf("\nEnter the first point(x2,y2): ");
	scanf("%d%d",&x2,&y2);

    printf("\nEnter the first point(x3,y3): ");
    scanf("%d%d",&x3,&y3);

    printf("\nEnter the first point(x4,y4): ");
    scanf("%d%d",&x4,&y4);

     printf("\n\nChose one of the following:\n1.Triangle\n2.Rectangle");
     scanf("%d",&choice);

     switch(choice)
     {
	 case 1:
	     if (checkTri(x1, y1, x2, y2, x3, y3))
	     {
		 draw_line(x1, y1, x2, y2);
		 draw_line(x2, y2, x3, y3);
		 draw_line(x3, y3, x1, y1);
	     }
	     else
	     {
		 printf("A triangle can't be drawn from the given points\n");
			 exit(0);
	     }
	     break;

	 case 2:
	     if(checkRect(x1, y1, x2, y2, x3, y3, x4, y4))
	     {
		 draw_line(x1, y1, x2, y2);
		 draw_line(x2, y2, x3, y3);
		 draw_line(x3, y3, x4, y4);
		 draw_line(x4, y4, x1, y1);
	     }
	     else
	     {
		 printf("A rectangle can't be drawn from the given points\n");
		 exit(0);
	     }
	     break;

	 default:
	     printf("\nWrong choice! Abort");
	     exit(0);
     }
	getch();
	closegraph();
}

void draw_line(int x1, int y1, int x2, int y2)
{
	if (abs(y2 - y1) < abs(x2 - x1))
	{
		if (x1 > x2)
		{
			draw_min(x2, y2, x1, y1);
		}
		else
		{
			draw_min(x1, y1, x2, y2);
		}
	}
	else
	{
		if (y1 > y2)
		{
			draw_max(x2, y2, x1, y1);
		}
		else
		{
			draw_max(x1, y1, x2, y2);
		}
	}
}


void draw_min(int x1, int y1, int x2, int y2)
{
	int dx, dy, x, y, y_in, pk;

	dx = x2 - x1;
	dy = y2 - y1;
	y_in = 1;

	if ( dy < 0)
	{
		y_in = -1;
		dy = -dy;
	}

	pk = 2*dy - dx;
	y = y1;

	for (x = x1; x <= x2; x++)
	{
		putpixel(x, y, 7);
		if ( pk > 0)
		{
			y = y + y_in;
			pk = pk + 2*dy - 2*dx;
		}
		else{
			pk = pk + 2*dy;
		}

	}
}


void draw_max(int x1, int y1, int x2, int y2)
{
	int x, y, dx, dy, pk, x_in;

	dx = x2 - x1;
	dy = y2 - y1;
	x_in = 1;

	if ( dx < 0)
	{
		x_in = -1;
		dx = -dx;
	}

	pk = 2*dx - dy;
	x = x1;

	for( y = y1; y <= y2; y++)
	{
		putpixel(x, y, 7);
		if( pk > 0)
		{
			x = x + x_in;
			pk = pk - 2*dy;
		}
		pk = pk + 2*dx;

	}
}


int checkTri(int x1, int y1, int x2, int y2, int x3, int y3)
{
	float d1, d2, d3;

	d1 = sqrt(abs((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)));
	d2 = sqrt(abs((x3 - x2)*(x3 - x2) + (y3 - y2)*(y3 - y2)));
	d3 = sqrt(abs((x1 - x3)*(x1 - x3) + (y1 - y3)*(y1 - y3)));

	if(((d1+d2)<=d3) || ((d1+d3)<=d2) || ((d2+d3)<=d1))
	{
		return 0;
	}
	return 1;
}

int checkRect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    int d1, d2, d3, d4, s1, s2;

    d1 = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
    d2 = (x3-x2)*(x3-x2) + (y3-y2)*(y3-y2);
    d3 = (x4-x3)*(x4-x3) + (y4-y3)*(y4-y3);
    d4 = (x1-x4)*(x1-x4) + (y1-y4)*(y1-y4);

    s1 = (x3-x1)*(x3-x1) + (y3-y1)*(y3-y1);
    s2 = (x2-x4)*(x2-x4) + (y2-y4)*(y2-y4);

    if((d1==d3 && d2==d4) && (s1==s2))
    {
        return 1;
    }
    return 0;
}
