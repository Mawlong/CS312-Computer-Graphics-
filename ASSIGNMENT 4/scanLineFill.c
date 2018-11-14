#include<stdio.h>
#include<math.h>
#include<dos.h>
#include<stdlib.h>

int colour = 50;
int image[1000][1000];
typedef struct dcPt
{
    int x;
    int y;
} ;
typedef struct tEdge
{
    int yUpper;
    float xIntersect, dxPerScan;
    struct tEdge *next;
} Edge;


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
		image[x][y] = 200;
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
		image[x][y] = 200;
		if( pk > 0)
		{
			x = x + x_in;
			pk = pk - 2*dy;
		}
		pk = pk + 2*dx;

	}
}



void insertEdge (Edge * list, Edge * edge)
{
    Edge * p, *q = list;

    p = q->next;
    while(p!= NULL) {
        if(edge->xIntersect< p->xIntersect)
            p = NULL;
        else {
            q = p;
            p = p ->next;
        }
    }
    edge->next = q->next;
    q->next = edge;
}
int yNext (int k, int cnt, struct dcPt * pts)
{
    int j;

    if((k + 1) > (cnt - 1))
        j = 0;
    else
        j = k + 1;
    while (pts[k].y == pts[j].y)
        if ((j + 1) > (cnt - 1))
        j = 0;
    else
        j++;
    return (pts[j].y);
}

void makeEdgeRec (struct dcPt lower, struct dcPt upper, int yComp, Edge * edge, Edge * edges[])
{
    edge->dxPerScan = (float) (upper.x - lower.x) / (upper.y - lower.y);
    edge->xIntersect = lower.x;
    if(upper.y < yComp)
        edge->yUpper = upper.y - 1;
    else
        edge->yUpper = upper.y;
    insertEdge(edges[lower.y],edge);
}

void buildEdgeList (int cnt, struct dcPt * pts, Edge * edges[])
{
    Edge * edge;
    struct dcPt v1, v2;
    int i, yPrev = pts[cnt - 2].y;

    v1.x = pts[cnt - 1].x; v1.y = pts[cnt - 1].y;
    for (i = 0;i < cnt; i++)
    {
        v2 = pts[i];
        if(v1.y != v2.y)
        {
            edge = (Edge *) malloc(sizeof(Edge));
            if(v1.y < v2.y)
                makeEdgeRec(v1, v2, yNext (i, cnt, pts),edge,edges);
            else
                makeEdgeRec(v2, v1, yPrev, edge, edges);
        }
        yPrev = v1.y;
        v1 = v2;
    }
}
void buildActiveList (int scan,Edge * active, Edge * edges[])
{
    Edge * p, *q;
    p = edges[scan]->next;
    while(p) {
        q = p ->next;
        insertEdge(active, p);
        p = q;
    }

}
void fillScan (int scan, Edge * active)
{
    Edge * p1, *p2;
    int i;
    ++colour;

    p1 = active->next;
    while(p1)
    {
        p2 = p1 -> next;
        for(i = p1 ->xIntersect; i<p2->xIntersect; i++)
            //setPixel ((int) i, scan);
            image[(int) i][scan] = colour;
        p1 = p2 ->next;
    }
}
void deleteAfter(Edge * q)
{
    Edge * p = q->next;
    q -> next = p ->next;
    free(p);
}

void updateActiveList (int scan, Edge * active)
{
    Edge * q = active, * p = active -> next;

    while (p)
    if (scan >= p->yUpper)
    {
        p = p->next;
        deleteAfter(q);
    }
    else
    {
        p->xIntersect = p->xIntersect + p->dxPerScan;
        q = p;
        p = p->next;
    }
}

void resortActiveList (Edge * active)
{
    Edge * q, * p = active->next;
    active->next = NULL;
    while(p)
     {
        q = p->next;
        insertEdge (active, p);
        p = q;
    }
}

void scanFill (int cnt, struct dcPt * pts)
{
    Edge * edges[1000], * active;
    int i, scan;
    for(i=0;i<1000; i++)
    {
        edges[i] = (Edge *) malloc (sizeof (Edge));
        edges[i]->next = NULL;
    }
    buildEdgeList(cnt,pts,edges);
    active = (Edge *) malloc (sizeof(Edge));
    active -> next = NULL;
    for(scan = 0;scan < 1000; scan ++)
    {
        buildActiveList(scan, active, edges);
        if(active->next)
        {
            fillScan(scan, active);
            updateActiveList(scan,active);
            resortActiveList(active);
        }
    }
}
void main ()
{
    int height = 1000, width = 1000, temp,i,j,xCenter,yCenter,radius,x1,y1;
	for (i = 0; i < height; i++)
	{
        for (j = 0; j < width; j++)
            image[i][j] = 0;
    }
    FILE* pgmimg;
    pgmimg = fopen("scanFill.pgm", "wb");
    fprintf(pgmimg, "P2\n");
    fprintf(pgmimg, "%d %d\n", width, height);
    fprintf(pgmimg, "255\n");
    printf("Enter the co-ordinates of the center:\n");
    scanf("%d %d",&xCenter,&yCenter);
    printf("Enter the radius:\n");
    scanf("%d",&radius);
    struct dcPt constructionPoints[6];
    constructionPoints[0].x = xCenter + radius;
    constructionPoints[0].y = yCenter;
    x1 = xCenter + radius;
    y1 = yCenter;
    int t = 60;
    float tP = t * ((3.14)/180);
    for(i = 1;i < 6;i++)
    {
         constructionPoints[i].x = xCenter + (x1 - xCenter) * cos(tP) - (y1 - yCenter) * sin(tP);
         constructionPoints[i].y = yCenter + (x1 - xCenter) * sin(tP) + (y1 - yCenter) * cos(tP);
        t+=60;
        tP = t * ((3.14)/180);
    }

    scanFill(6,constructionPoints);

    draw_line(constructionPoints[0].x, constructionPoints[0].y,constructionPoints[1].x,constructionPoints[1].y);
    draw_line(constructionPoints[1].x, constructionPoints[1].y,constructionPoints[2].x,constructionPoints[2].y);
    draw_line(constructionPoints[2].x, constructionPoints[2].y,constructionPoints[3].x,constructionPoints[3].y);
    draw_line(constructionPoints[3].x, constructionPoints[3].y,constructionPoints[4].x,constructionPoints[4].y);
    draw_line(constructionPoints[4].x, constructionPoints[4].y,constructionPoints[5].x,constructionPoints[5].y);
    draw_line(constructionPoints[5].x, constructionPoints[5].y,constructionPoints[0].x,constructionPoints[0].y);

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
}
