#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<dos.h>
#include<stdlib.h>
void Line(int,int,int,int);
void main (){
	int x1,x2,x3,y1,y2,y3,x4,y4,check =1,choice=0;
	int gdriver = DETECT, gmode;
	initgraph(&gdriver, &gmode, "C://TURBOC3//BGI");
	while(check)
	{
		printf("Enter your choice:\n1.Triangle\n2.Rectangle\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:

				printf("Enter the value of the first point (x1,y1): ");
				scanf("%d %d",&x1,&y1);
				printf("\nEnter the value of the second point (x2,y2): ");
				scanf("%d %d",&x2,&y2);
				printf("\nEnter the value of the third point (x3,y3): ");
				scanf("%d %d",&x3,&y3);
				clrscr();
				Line(x1,y1,x2,y2);
				Line(x2,y2,x3,y3);
				Line(x3,y3,x1,y1);
				getch();
				break;
			case 2:
				printf("Enter the value of the first corner (x1,y1): ");;
				scanf("%d %d", &x1,&y1);
				printf("\nEnter the value of the second corner (x2,y2): ");
				scanf("%d %d",&x2,&y2);
				printf("\nEnter the value of the third corner (x3,y3): ");
				scanf("%d %d",&x3,&y3);
				printf("\nEnter the value of the fourth corner (x3,y3): ");
				scanf("%d %d",&x4,&y4);
				clrscr();
				Line(x1,y1,x2,y2);
				Line(x2,y2,x3,y3);
				Line(x3,y3,x4,y4);
				Line(x4,y4,x1,y1);
				getch();
				break;

			default:
				clrscr();
				printf("WRONG CHOICE\nPlease enter your choice. Do You Want to re-enter your choice? (yes = 1 | no = 0) : ");
				scanf("%d",&check);
				break;
		}

		printf("\nDo You want to draw again? (yes = 1 | no = 0: ");
		scanf("%d", &check);
    }

    closegraph();


}
void Line (int x1, int y1, int x2, int y2)
{
	int dx, dy, steps,i;
	float x_inc, y_inc, x, y;
	dx = x2 - x1;
	dy =y2 - y1;
	if (abs(dx) >abs(dy))
	steps =abs(dx);
	else
	steps = abs(dy);
	x_inc = dx/(float) steps;
	y_inc =dy/(float) steps;
	x = x1;
	y = y1;
	for(i = 0; i <= steps ;i++)
	{
		putpixel(x,y,GREEN);
		x = x + x_inc;
		y = y + y_inc;
	}

}
