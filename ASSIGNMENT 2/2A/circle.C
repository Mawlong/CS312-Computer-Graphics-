#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int image[1000][1000];
void PlotPoints (int xC, int yC, int x, int y)
{
    image[xC + x][yC + y] = 255;
    image[xC + x][yC - y] = 255;
    image[xC - x][yC + y] = 255;
    image[xC - x][yC - y] = 255;


    image[xC + y][yC + x] = 255;
    image[xC + y ][yC - x] = 255;
    image[xC - y][yC + x] = 255;

    image[xC - y][yC - x] = 255;
}

void PlotPointsLeft (int xC, int yC, int x, int y, int radiuss)
{
    image[xC + x+(2*radiuss)][ yC + y]=255;
    image[xC - x +(2* radiuss)][ yC + y]=255;
    image[xC + y +(2 * radiuss)][ yC + x]=255;
    image[xC - y +(2* radiuss)][ yC + x]=255;
}

void PlotPointsRight (int xC, int yC, int x, int y, int r)
{
    image[xC + x - (2 * r)][ yC - y]=255;
    image[xC - x - (2 * r)][ yC - y]=255;
    image[xC + y - (2 * r)][ yC - x]=255;
    image[xC - y - (2 * r)][yC - x]=255;
}

void drawLine (int x1, int y1, int x2, int y2)
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
	for(i = 0; i <= steps ;i++){
    image[(int)x][(int)y]=255;
	x = x + x_inc;
	y = y + y_inc;
	}
}

void circleMidpoint(int xC, int yC, int radius)
{
    int x=0;
    int y=radius;
    int p = 1 - radius;
    PlotPoints(xC,yC,x,y);
    
    while(x < y)
    {
        x++;
        
        if(p < 0)
        {
            p += 2 * x +1;
        }
        else
        {
            y--;
            p += 2 * (x - y) + 1;
        }
        
        PlotPoints(xC, yC,x,y);
        PlotPointsRight(xC, yC, x, y, radius);
        PlotPointsLeft(xC, yC,x,y,radius);
    }
}

int main()
 {
    int xC, yC, radius;int i, j, temp;
    int height = 1000, width = 1000;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
            image[i][j] = 0;
    }

    printf("Enter the value of xc:\n");
    scanf("%d",&xC);
    printf("Enter the value of yc:\n");
    scanf("%d",&yC);
    printf("Enter the value of radius:\n");
    scanf("%d",&radius);

    FILE* pgmimg;
    pgmimg = fopen("circle.pgm", "wb");
    fprintf(pgmimg, "P2\n");
    fprintf(pgmimg, "%d %d\n", width, height);
    fprintf(pgmimg, "255\n");
    int count = 0;
    circleMidpoint(xC, yC,radius);
    drawLine(xC - (3 * radius), yC, xC + (3 * radius), yC);
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            temp = image[j][i];
            fprintf(pgmimg, "%d ", temp);
        }
        fprintf(pgmimg, "\n");
    }
    fclose(pgmimg);
    return 0;

}
