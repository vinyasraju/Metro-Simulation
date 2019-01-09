#include<windows.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
float color[2][3]={{0.7,0.43,0.077},{0.86,0.6848,0.4558}};
int n=9,tt=0;
char num[10]={'0','1','2','3','4','5','6','7','8','9'};
static int menu_id;
static int value=0;
static int enter=0;
static int tno=1;//350,200,850,470
int tf=850,te=1350;
int s=0;
int token=0,ticket=0;
int scene=0;
int permission;
int inside=0,outside=0;
int noTickets=0;
int sceneChange;
int *getEntry;
int goBack=0;
int in=0;
int view=1;
int gd=0;

float toRadians(float n);
void keyboard(unsigned char key,int x,int y);
void menu(int num);
void createMenu(void);
void mouseFunc(int b,int s,int x,int y);
void insideMenu(int id);
void createTrackFront();
void createTrain();
void drawCircle(int x,int y,float r);
void selectColor();
void createFloor();
void createMachine(int,int);
void noEntry();
void Entry();
void enterPlatform();
void billingCounter(int *token,int *ticket,int *scene);
void putToken(int *t,int *p,int *s);
void platform(int *inside);
void getInside(int *outside);
void createTitle();;
void createCounter();
void displayMessage();
void createWall();
void createStand();
void createFrontFloor();
void createBackFloor();
void pillars();
void idle();
void Train(int x1,int x2,int y1,int y2);
void createTrack();
void createProperties();
void genChair(int x1,int x2,int y1,int y2);
void genStripes(int x1,int x2,int y1,int y2);
void genPillars(int x1,int x2,int y1,int y2);
void genCementBlocks(int x1,int x2,int y1,int y2);
void genElectricLines(int x1,int x2,int y1,int y2);
void countdown();
void trainMenu(int);
void trainFront();
void genHolders(int x);
void smallTrain();
void front();
void side();
void top();

float toRadians(float n)
{
    return 3.1456*n/180;
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(50,750,0,700,0,700);
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    glutReshapeWindow(950,800);
    billingCounter(&token,&ticket,&scene);
    if(token==6)
    {
        scene=1;
        putToken(&ticket,&permission,&scene);
    }
   if(permission==1 && scene==2)
    {

       platform(&inside);
    }
   if(inside==1)
        getInside(&outside);
    if(outside==1)
        platform(&inside);
    glutSwapBuffers();
    glFlush();
}
int main(int argc,char *argv[])
{

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(950,800);
    glutCreateWindow("Metro");
    glutInitWindowPosition(100,100);
    init();
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

}
void billingCounter(int *token,int *ticket,int *scene)
{
    glClearColor(0,0,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    s=*scene;
    if(*scene==0)
        createMenu();
    *token=value;
    if(value>0 && value!=6)
    {
        displayMessage();
        *ticket+=1;
    }
    createTitle();
    createCounter();
    createStand();
    createWall();
}
void createWall()
{
    glColor3fv(color[0]);
    glBegin(GL_POLYGON);
        glVertex3f(0,0,0);
        glVertex3f(0,750,0);
        glColor3fv(color[1]);
        glVertex3f(800,750,0);
        glVertex3f(800,0,0);
    glEnd();
}
void createQuad(int l,int h)
{
    glVertex3f(l,h,0);
    glVertex3f(l+10,h,0);
    glVertex3f(l+10,h-10,0);
    glVertex3f(l,h-10,0);
}
void createTitle()
{
    int i,l=250,h1=680,h2=590;
    //METRO
    glLineWidth(2);
    glColor3f(1,1,1);
    glBegin(GL_LINES);
        //M
        glVertex3f(290,605,0);
        glVertex3f(290,655,0);
        glVertex3f(290,655,0);
        glVertex3f(310,605,0);
        glVertex3f(310,605,0);
        glVertex3f(330,655,0);
        glVertex3f(330,655,0);
        glVertex3f(330,605,0);

        //E
        glVertex3f(345,605,0);
        glVertex3f(345,655,0);
        glVertex3f(345,655,0);
        glVertex3f(375,655,0);
        glVertex3f(345,630,0);
        glVertex3f(375,630,0);
        glVertex3f(345,605,0);
        glVertex3f(375,605,0);

        //T
        glVertex3f(410,605,0);
        glVertex3f(410,655,0);
        glVertex3f(388,655,0);
        glVertex3f(432,655,0);

        //R
        glVertex3f(445,605,0);
        glVertex3f(445,655,0);
        glVertex3f(445,655,0);
        glVertex3f(475,655,0);
        glVertex3f(445,630,0);
        glVertex3f(475,630,0);
        glVertex3f(475,655,0);
        glVertex3f(475,630,0);
        glVertex3f(445,630,0);
        glVertex3f(475,605,0);

        //O
        glVertex3f(495,605,0);
        glVertex3f(495,655,0);
        glVertex3f(495,655,0);
        glVertex3f(525,655,0);
        glVertex3f(525,655,0);
        glVertex3f(525,605,0);
        glVertex3f(525,605,0);
        glVertex3f(495,605,0);
    glEnd();
    //top
    glBegin(GL_QUADS);
    for(i=0;i<30;i++)
    {
        if(i%2==0)
        {
            glColor3f(0,0.4,0);
            createQuad(l,h1);
            createQuad(l,h2);
        }
        else
        {
            glColor3f(1,1,0);
            createQuad(l,h1);
            createQuad(l,h2);
        }
        l+=10;
    }
    int l1=250,l2=540,h=670;
    for(i=0;i<8;i++)
    {
        if(i%2!=0)
        {
            glColor3f(0,0.4,0);
            createQuad(l1,h);
            createQuad(l2,h);
        }
        else
        {
            glColor3f(1,1,0);
            createQuad(l1,h);
            createQuad(l2,h);
        }
        h-=10;
    }
    glEnd();
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_QUADS);
        glVertex3f(250,580,0);
        glVertex3f(250,680,0);
        glVertex3f(550,680,0);
        glVertex3f(550,580,0);
    glEnd();

}
void createCounter()
{
    int i;
    float x,y;
    char str[]="TICKETS";
    glLineWidth(50);
    //Booked Board
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
        glVertex3f(255,270,0);
        glVertex3f(255,290,0);
        glVertex3f(345,290,0);
        glVertex3f(345,270,0);
    glEnd();
    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
        glVertex3f(250,265,0);
        glVertex3f(250,295,0);
        glVertex3f(350,295,0);
        glVertex3f(350,265,0);
    glEnd();
    glColor3f(1,0,0);
    //Red Strip
    glBegin(GL_POLYGON);
        glVertex3f(300,265,0);
        glVertex3f(300,250,0);
        glVertex3f(140,0,0);
        glVertex3f(150,-10,0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(500,265,0);
        glVertex3f(500,250,0);
        glVertex3f(640,0,0);
        glVertex3f(650,-10,0);
    glEnd();
    //Pillars
    glColor3f(0,0,0);
    glBegin(GL_LINES);
        glVertex3f(255,185,0);
        glVertex3f(255,20,0);
        glVertex3f(543,183,0);
        glVertex3f(543,20,0);
    glEnd();
    //Tickets
    glColor3f(0,0,0);
    glRasterPos3d(355,495,0);
    for(i=0;i<(int)strlen(str);i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
    //Green inside top
    glColor3f(1,1,0);
    glBegin(GL_POLYGON);
        glVertex3f(490,485,0);
        glVertex3f(490,525,0);
        glVertex3f(310,525,0);
        glVertex3f(310,485,0);
    glEnd();
    //Top
    glColor3f(0.3619,0.0864,0.48);
    glBegin(GL_POLYGON);
        glVertex3f(500,450,0);
        glVertex3f(500,550,0);
        glVertex3f(300,550,0);
        glVertex3f(300,450,0);
    glEnd();
    //Hole
    glColor3f(0.85,0.85,0.850);
    glBegin(GL_POLYGON);
    for(i=0;i<=180;i++)
    {
        x=30*cos(toRadians(i));
        y=30*sin(toRadians(i));
        glVertex3f(400+x,265+y,0);
    }
    glEnd();
    //Glass
    glColor3f(0.4982,0.5152,0.53);
    glBegin(GL_POLYGON);
        glVertex3f(500,450,0);
        glVertex3f(500,265,0);
        //glColor3f(0.2328,0.2366,0.24);
        glColor3f(0.5734,0.5929,0.61);
        glVertex3f(300,265,0);
        glVertex3f(300,450,0);
    glEnd();
    //Red part above white part
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex3f(500,250,0);
        glVertex3f(500,265,0);
        glVertex3f(300,265,0);
        glVertex3f(300,250,0);
    glEnd();
    //White part in bottom of counter
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
        glVertex3f(475,125,0);
        glVertex3f(475,225,0);
        glVertex3f(325,225,0);
        glVertex3f(325,125,0);
    glEnd();
    //Bottom of counter
    glColor3f(0.0096,0.2605,0.48);
    glBegin(GL_POLYGON);
        glVertex3f(500,100,0);
        glVertex3f(500,250,0);
        glVertex3f(300,250,0);
        glVertex3f(300,100,0);
    glEnd();
    //Floor
    glColor3f(0.51,0.3663,0.1785);
    glBegin(GL_POLYGON);
        glVertex3f(0,0,0);
        glVertex3f(750,0,0);
        glColor3f(0.62,0.4507,0.2294);
        glVertex3f(750,100,0);
        glVertex3f(0,100,0);
    glEnd();
}
void displayMessage()
{
    //255,264
    char str[]="BOOKED";
    float x,y;
    int i;
    glColor3f(1,1,1);
    glRasterPos3d(268,272,0);
    for(int i=0;i<(int)strlen(str);i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
    }
    //Coin
    glColor3f(0.1168,0.21,0.0588);
    glPointSize(3);
    glBegin(GL_POINTS);
        glVertex3f(638,430,0);
        glVertex3f(634,458,0);
        glVertex3f(674,464,0);
        glVertex3f(670,442,0);
    glEnd();
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
        glVertex3f(650,445,0);
        glVertex3f(635,435,0);
        glVertex3f(630,425,0);
        glVertex3f(640,420,0);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex3f(650,455,0);
        glVertex3f(635,450,0);
        glVertex3f(620,459,0);
        glVertex3f(635,465,0);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex3f(660,455,0);
        glVertex3f(675,457,0);
        glVertex3f(685,470,0);
        glVertex3f(670,470,0);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex3f(660,455,0);
        glVertex3f(660,445,0);
        glVertex3f(650,445,0);
        glVertex3f(650,455,0);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex3f(660,445,0);
        glVertex3f(670,450,0);
        glVertex3f(685,440,0);
        glVertex3f(665,435,0);
    glEnd();

    glBegin(GL_LINE_LOOP);
    for(i=0;i<360;i++)
    {
        x=60*cos(toRadians(i));
        y=60*sin(toRadians(i));
        glVertex3f(635+x,445+y,0);
    }
    glEnd();

    glRasterPos3d(595,440,0);
    char str1[]="namma";
    for(i=0;i<(int)strlen(str);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,str1[i]);
    glRasterPos3d(585,425,0);
    char str2[]="metro";
    for(i=0;i<(int)strlen(str);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str2[i]);
    glColor3f(0.1807,0.34,0.0816);
    glBegin(GL_POLYGON);
    for(i=0;i<360;i++)
    {
        x=70*cos(toRadians(i));
        y=70*sin(toRadians(i));
        glVertex3f(635+x,445+y,0);
    }
    glEnd();

}
void createStand()
{
    int i;
    char str[]="PLATFORM 1";
    //Right side board
    glColor3f(1,1,1);
    glRasterPos3d(545,165,0);
    for(i=0;i<(int)strlen(str);i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
    }
    glColor3f(0.0957,0.2641,0.29);
    glBegin(GL_QUADS);
        glVertex3f(530,150,0);
        glVertex3f(530,200,0);
        glVertex3f(690,200,0);
        glVertex3f(690,150,0);
        glVertex3f(590,100,0);
        glVertex3f(590,150,0);
        glVertex3f(610,150,0);
        glVertex3f(610,100,0);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex3f(690,200,0);
        glVertex3f(690,150,0);
        glVertex3f(720,175,0);
    glEnd();
    //Map
    glPointSize(10);
    glLineWidth(5);
    glBegin(GL_LINES);
            glColor3f(0,0,1);
        glVertex3f(95,360,0);
        glVertex3f(125,430,0);
        glVertex3f(125,430,0);
        glVertex3f(165,430,0);
        glVertex3f(165,430,0);
        glVertex3f(205,390,0);
        glVertex3f(205,390,0);
        glVertex3f(235,390,0);
            glColor3f(1,0,0);
        glVertex3f(95,430,0);
        glVertex3f(130,350,0);
        glVertex3f(130,350,0);
        glVertex3f(220,430,0);
        glVertex3f(220,430,0);
        glVertex3f(240,430,0);
    glEnd();
    glBegin(GL_POINTS);
            glColor3f(0,0,1);
        glVertex3f(95,360,0);
        glVertex3f(125,430,0);
        glVertex3f(125,430,0);
        glVertex3f(165,430,0);
        glVertex3f(165,430,0);
        glVertex3f(205,390,0);
        glVertex3f(205,390,0);
        glVertex3f(235,390,0);
            glColor3f(1,0,0);
        glVertex3f(95,430,0);
        glVertex3f(130,350,0);
        glVertex3f(130,350,0);
        glVertex3f(220,430,0);
        glVertex3f(220,430,0);
        glVertex3f(240,430,0);
    glEnd();
    glColor3f(1,1,1);
    glRasterPos3d(115,467,0);
    char str1[]="ROUTE MAP";
    for(i=0;i<=(int)strlen(str);i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str1[i]);
    }
    glBegin(GL_QUADS);
            glColor3f(0.4,0.4,0.4);
        glVertex3f(75,490,0);
        glVertex3f(250,490,0);
        glVertex3f(250,460,0);
        glVertex3f(75,460,0);
            glColor3f(0.9,0.9,0.9);
        glVertex3f(75,330,0);
        glVertex3f(75,490,0);
        glVertex3f(250,490,0);
        glVertex3f(250,330,0);
    glEnd();
    glColor3f(0,1,0);
    glBegin(GL_LINE_LOOP);
        glVertex3f(550,360,0);
        glVertex3f(550,530,0);
        glVertex3f(720,530,0);
        glVertex3f(720,360,0);
    glEnd();

}

void putToken(int *t,int *p,int *s)
{
    noTickets=*t;
    *s=sceneChange;
    getEntry=p;
    glutDetachMenu(GLUT_LEFT_BUTTON);
    enterPlatform();
    if(goBack==1)
    {
        return;
    }
}
void enterPlatform()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutKeyboardFunc(keyboard);
    if(enter==0 || noTickets==0)
    {
        noEntry();
    }
    else
    {
        Entry();
    }
    createMachine(550,100);
    createMachine(50,100);
    createFloor();
}
void noEntry()
{
    int i;
    //Tape
    glColor3f(0,0,0);
    glBegin(GL_QUADS);
        glVertex3f(210,300,0);
        glVertex3f(210,350,0);
        glVertex3f(550,350,0);
        glVertex3f(550,300,0);
    glEnd();
    //Text 575 250
    glColor3f(1,1,1);
    char str[]="NO";
    glRasterPos3d(610,315,0);
    for(i=0;i<(int)strlen(str);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
    char str1[]="TICKET";
    glRasterPos3d(595,285,0);
    for(i=0;i<(int)strlen(str1);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str1[i]);
}
void Entry()
{
    int i;
    float x,y;
    glColor3f(1,1,1);
    char str[]="WELCOME";
    glRasterPos3d(585,290,0);
    for(i=0;i<(int)strlen(str);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
    *getEntry=1;
    glColor3f(0.8,0.8,0.8);
    glPointSize(1);
    glColor3f(0.1807,0.34,0.0816);
    glBegin(GL_POLYGON);
    for(i=0;i<360;i++)
    {
        x=15*cos(toRadians(i));
        y=15*sin(toRadians(i));
        glVertex3f(625+x,200+y,0);
    }
    glEnd();

}
void createMachine(int x,int y)
{
    int i;
    float x1,y1;
    //coin outline
    glColor3f(0.8,0.8,0.8);
    glPointSize(1);
    glBegin(GL_POINTS);
    for(i=0;i<360;i++)
    {
        x1=20*cos(toRadians(i));
        y1=20*sin(toRadians(i));
        glVertex3f(x+75+x1,y+100+y1,0);
    }
    glEnd();
    //Text
    glColor3f(0.3,0.3,0.3);
    glRasterPos3f(x+65,y+350,0);
    char str[]="namma";
    for(i=0;i<(int)strlen(str);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,str[i]);
    glRasterPos3f(x+55,y+330,0);
    char str1[]="metro";
    for(i=0;i<(int)strlen(str1);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str1[i]);
    //Grey in red
    glColor3f(0.75,0.75,0.75);
    glBegin(GL_QUADS);
        glVertex3f(x+40,y+300,0);
        glVertex3f(x+40,y+380,0);
        glVertex3f(x+110,y+380,0);
        glVertex3f(x+110,y+300,0);
        //display board
        glColor3f(0.3619,0.0864,0.48);
        glVertex3f(x+25,y+150,0);
        glVertex3f(x+25,y+250,0);
        glVertex3f(x+125,y+250,0);
        glVertex3f(x+125,y+150,0);
    glEnd();
    //Light red
    glColor3f(0.75,0.36,0.36);
    glBegin(GL_QUADS);
        glVertex3f(x+25,y+300,0);
        glVertex3f(x+25,y+400,0);
        glVertex3f(x+125,y+400,0);
        glVertex3f(x+125,y+300,0);
    glEnd();
    //Red part
    glColor3f(1,0,0);
    glBegin(GL_QUADS);
        glVertex3f(x,y,0);
        glVertex3f(x,y+450,0);
        glVertex3f(x+150,y+450,0);
        glVertex3f(x+150,y,0);
        //yellow strips
        glColor3f(0,1,1);
        glVertex3f(x+65,y,0);
        glVertex3f(x+65,y-450,0);
        glVertex3f(x+85,y-450,0);
        glVertex3f(x+85,y,0);
    glEnd();
}
void createFloor()
{
    ///Text
    glColor3f(1,1,1);
    char *str;
    if(*getEntry==0)
        str="Press M to place token and enter";
    else
        str="Press P to move to platform";
    glRasterPos3d(150,650,0);
    for(int i=0;i<(int)strlen(str);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
    glColor3f(0.3,0.3,0.3);
    glLineWidth(8);
    glBegin(GL_LINES);
        glVertex3f(0,200,0);
        glVertex3f(900,200,0);
        glVertex3f(0,400,0);
        glVertex3f(900,400,0);
        glVertex3f(0,600,0);
        glVertex3f(900,600,0);
        glVertex3f(200,0,0);
        glVertex3f(200,800,0);
        glVertex3f(500,0,0);
        glVertex3f(500,800,0);
    glEnd();
    glColor3f(0.4,0.4,0.4);
    glBegin(GL_QUADS);
        glVertex3f(0,0,0);
        glVertex3f(0,700,0);
        glColor3f(0.6,0.6,0.6);
        glVertex3f(900,700,0);
        glVertex3f(900,0,0);
    glEnd();

}

void platform(int *inside)
{
    glClearColor(0.5,0.5,0.5,1);
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    glutDetachMenu(GLUT_RIGHT_BUTTON);
    countdown();
    createProperties();
    pillars();
    createFrontFloor();
    createTrack();
    createBackFloor();
    if(in==1)
    {
        *inside=1;
        return;
    }
}
void countdown()
{
    if(n==999)
    {
        glutCreateMenu(trainMenu);
        glutAddMenuEntry("Quit",3);
        glutAttachMenu(GLUT_LEFT_BUTTON);
        glutPostRedisplay();
    }

    else if(n>0 && tt==0)
    {
        //Board

        glColor3f(1,1,1);
        char str1[]="TIME";
        glRasterPos3f(80,420,0);
        for(int p=0;p<(int)strlen(str1);p++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str1[p]);
        Sleep(1000);
        glRasterPos3f(160,420,0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,num[n]);
        n--;
        glutPostRedisplay();
    }
    else if(n>=-2)
    {
       trainFront();
       Sleep(1000);
       glutDetachMenu(GLUT_LEFT_BUTTON);
            glutCreateMenu(trainMenu);
            glutAddMenuEntry("Enter Train",1);
            glutAddMenuEntry("Next Train",2);
            glutAddMenuEntry("Quit",3);
            glutAttachMenu(GLUT_LEFT_BUTTON);
       n--;
       glutPostRedisplay();
    }
    else if(n>=-503)
    {
        n--;
        tt=1;
        Train(tf--,200,te--,470);
        glutPostRedisplay();
    }
    else{
        tt=1;
        glutDetachMenu(GLUT_LEFT_BUTTON);
        glutCreateMenu(trainMenu);
        glutAddMenuEntry("Enter Train",1);
        glutAddMenuEntry("Next Train",2);
        glutAddMenuEntry("Quit",3);
        glutAttachMenu(GLUT_LEFT_BUTTON);
        Train(tf,200,te,470);
        glutPostRedisplay();
    }
}
void Train(int x1,int y1,int x2,int y2)
{
    float my,x,y;
    my=(float)(y1+y2)/2;
    char str[]="namma";
    glColor3f(0.1,0.1,0.1);
    glRasterPos3f(x1+40,y1+100,0);
    for(int i=0;i<(int)strlen(str);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,str[i]);
    char str1[]="metro";
    //Doors
    glRasterPos3f(x1+50,y1+90,0);
    for(int i=0;i<(int)strlen(str1);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str1[i]);
    glBegin(GL_LINES);
    glLineWidth(4);
    glColor3f(0.3,0.3,0.3);
        glVertex3f(x1+130,y1,0);
        glVertex3f(x1+130,y1+130,0);
        glVertex3f(x1+240,y1,0);
        glVertex3f(x1+240,y1+130,0);

        glVertex3f(x1+260,y1,0);
        glVertex3f(x1+260,y1+130,0);
        glVertex3f(x1+370,y1,0);
        glVertex3f(x1+370,y1+130,0);
    glLineWidth(2);
    glEnd();
    //Pink or green
    selectColor();
    glRectf(x1,y2-25,x2,y2);
    glRectf(x1,y1,x1+10,y2);
    glRectf(x1+20,y1+40,x2,y1+70);
     glColor3f(0.8,0.8,0.8);
    //windows
    glRectf(x1+60,y1+140,x1+100,y2-70);
    glRectf(x1+140,y1+140,x1+180,y2-70);
    glRectf(x1+190,y1+140,x1+230,y2-70);
    glRectf(x1+270,y1+140,x1+310,y2-70);
    glRectf(x1+320,y1+140,x1+360,y2-70);
    //bottom gradient
    glBegin(GL_QUADS);
        glColor3f(0.6,0.6,0.6);
        glVertex3f(x1,y1,0);
        glVertex3f(x1,y1+130,0);
        glColor3f(0.7,0.7,0.7);
        glVertex3f(x2,y1+130,0);
        glVertex3f(x2,y1,0);
    glEnd();
    glColor3f(0.1,0.1,0.1);
    //black window panel
    glRectf(x1+30,y1+130,x2-50,y2-60);
    glColor3f(0.5,0.5,0.5);
    glRectf(x1+50,y2-55,x2,y2-30);
    glColor3f(0.8,0.8,0.8);
    glRectf(x1,y1,x2,y2);
    glColor3f(0.4,0.4,0.4);
     glBegin(GL_POLYGON);
    for(float i=90;i<=180;i++)
    {
        x=135*cos(toRadians(i));
        y=135*sin(toRadians(i));
        glVertex3f(x+x1+50,y+my,0);
    }
    glVertex3f(135+x1+50,my,0);
    glVertex3f(x1+50,135+my,0);
    glEnd();
    glColor3f(0.8,0.8,0.8);
    glBegin(GL_POLYGON);
    for(float i=110;i<250;i++)
    {
        x=135*cos(toRadians(i));
        y=135*sin(toRadians(i));
        glVertex3f(x+x1+50,y+my,0);
    }
    glEnd();
}

void createFrontFloor()
{
    //Black slant stripe
    glColor3f(0.32,0.2819,0.144);
    for(int x=20;x<=750;x+=140)
        genStripes(x,x+30,0,140);
    glBegin(GL_QUADS);
    //Yellow floor
        glColor3f(0.94,0.778,0.1924);
        glVertex3f(0,0,0);
        glVertex3f(750,0,0);
        glColor3f(0.57,0.4971,0.2337);
        glVertex3f(750,200,0);
        glVertex3f(0,200,0);
    glEnd();
}

void createProperties()
{
    float x,y,i;
    //To mg Road
    char str[]="STATION";
    glColor3f(1,1,1);
    glRasterPos3f(620,620,0);
    for(int p=0;p<(int)strlen(str);p++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[p]);
    glBegin(GL_LINES);
        glVertex3f(620,605,0);
        glVertex3f(690,605,0);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex3f(690,595,0);
        glVertex3f(690,615,0);
        glVertex3f(710,605,0);
    glEnd();
    glBegin(GL_QUADS);
        glColor3f(0,0.1,0);
        glVertex3f(70,390,0);
        glVertex3f(70,470,0);
        glVertex3f(190,470,0);
        glVertex3f(190,390,0);
        glColor3f(0,0.7,0);
        glVertex3f(60,380,0);
        glVertex3f(60,480,0);
        glVertex3f(200,480,0);
        glVertex3f(200,380,0);
        //To MG Road board
        glColor3f(0,0,0.2);
        glVertex3f(600,590,0);
        glVertex3f(600,650,0);
        glVertex3f(720,650,0);
        glVertex3f(720,590,0);
    glEnd();

    glColor3f(0,0,0);
    glLineWidth(3);
    glBegin(GL_LINES);
        glVertex3f(110,600,0);
        glVertex3f(110+30,600,0);
        glVertex3f(110,600,0);
        glVertex3f(110,600+45,0);
    glEnd();
    //Clock
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    for(i=0;i<=360;i++)
        {
            x=50*cos(i);
            y=50*sin(i);
            glVertex3f(x+110,y+600,0);
        }
    glEnd();
    glColor3f(0,0,0.4);
    glBegin(GL_POLYGON);
    for(i=0;i<=360;i++)
        {
            x=60*cos(i);
            y=60*sin(i);
            glVertex3f(x+110,y+600,0);
        }
    glEnd();
    genChair(450,550,560,610);
    genChair(290,390,560,610);
}

void createBackFloor()
{
    //Black slant stripe
    glColor3f(0.32,0.2819,0.144);
    for(int x=50;x<=750;x+=140)
        genStripes(x,x+30,430,510);
    glBegin(GL_QUADS);
        glColor3f(0.56,0.5248,0.3976);
        glVertex3f(0,400,0);
        glVertex3f(750,400,0);
        glColor3f(0.94,0.778,0.1924);
        glVertex3f(750,600,0);
        glVertex3f(0,600,0);
        //Wall
         glColor3f(0.0627,0.57,0.477);
        glVertex3f(750,600,0);
        glVertex3f(0,600,0);
        glVertex3f(0,800,0);
        glVertex3f(750,800,0);
    glEnd();

}

void genChair(int x1,int x2,int y1,int y2)
{
    glBegin(GL_QUADS);
    glColor3f(0.5,0.5,0.5);
        glVertex3f(x1,y1,0);
        glVertex3f(x1,y2,0);
        glVertex3f(x2,y2,0);
        glVertex3f(x2,y1,0);
    glColor3f(0.3,0.3,0.3);
        glVertex3f(x1,y1,0);
        glVertex3f(x2,y1,0);
        glVertex3f(x2-10,y1-20,0);
        glVertex3f(x1-10,y1-20,0);
    glEnd();
    glLineWidth(5);
    glBegin(GL_LINES);
        glVertex3f(x1-6,y1-20,0);
        glVertex3f(x1-6,y1-40,0);
        glVertex3f(x2-12,y1-20,0);
        glVertex3f(x2-12,y1-40,0);
        glVertex3f(x2-2,y1-20,0);
        glVertex3f(x2-2,y1,0);
    glEnd();

}

void pillars()
{
    genPillars(0,120,0,700);
    genPillars(180,230,530,700);
    genPillars(630,680,530,700);
}

void createTrack()
{
    int x,y;
    for(x=60;x<=750;x+=230)
    {
        genCementBlocks(x,x+200,260,290);
    }
    glColor3f(0.2,0.2,0.2);
    for(y=220;y<340;y+=40)
    {
        genElectricLines(0,750,y,y+10);
    }
    glBegin(GL_QUADS);
        glColor3f(0.1,0.1,0.1);
        glVertex3f(0,400,0);
        glVertex3f(750,400,0);
        glVertex3f(750,340,0);
        glVertex3f(0,340,0);
        glColor3f(0.5,0.5,0.5);
        glVertex3f(0,200,0);
        glVertex3f(750,200,0);
        glColor3f(0.3,0.3,0.3);
        glVertex3f(750,340,0);
        glVertex3f(0,340,0);
    glEnd();

}

void genStripes(int x1,int x2,int y1,int y2)
{
    glBegin(GL_QUADS);
        glVertex3f(x1,y1,0);
        glVertex3f(x1+40,y2,0);
        glVertex3f(x2+40,y2,0);
        glVertex3f(x2,y1,0);
    glEnd();

}

void genCementBlocks(int x1,int x2,int y1,int y2)
{
    glBegin(GL_QUADS);
        glColor3f(0.7,0.7,0.7);
        glVertex3f(x1,y1,0);
        glVertex3f(x1+20,y2,0);
        glVertex3f(x2+20,y2,0);
        glVertex3f(x2,y1,0);
        glColor3f(0.5,0.5,0.5);
        glVertex3f(x1,y1-10,0);
        glVertex3f(x1,y1,0);
        glVertex3f(x2,y1,0);
        glVertex3f(x2,y1-10,0);
        glVertex3f(x2,y1-10,0);
        glVertex3f(x2,y1,0);
        glVertex3f(x2+20,y2,0);
        glVertex3f(x2+20,y2-13,0);
    glEnd();
}

void genElectricLines(int x1,int x2,int y1,int y2)
{
    glBegin(GL_QUADS);
        glVertex3f(x1,y1,0);
        glVertex3f(x2,y1,0);
        glVertex3f(x2,y2,0);
        glVertex3f(x1,y2,0);
    glEnd();
}

void genPillars(int x1,int x2,int y1,int y2)
{
    glBegin(GL_QUADS);
            glColor3f(0.37,0.2304,0.0999);
        glVertex3f(x1,y1,0);
        glVertex3f(x1,y2,0);
        glVertex3f(x2,y2,0);
        glVertex3f(x2,y1,0);
            glColor3f(0.23,0.1456,0.0667);
        glVertex3f(x2,y1,0);
        glVertex3f(x2+20,y1+30,0);
        glVertex3f(x2+20,y2,0);
        glVertex3f(x2,y2,0);
    glEnd();
}

void trainFront()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    createTrain();
    createTrackFront();
}

void createTrain()
{
    float x,y;
    glColor3f(1,1,0);
    char str[]="4070";
    glRasterPos3f(385,500,0);
    for(int i=0;i<(int)strlen(str);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
    glColor3f(0.8,0.6,0);
    drawCircle(310,300,10);
    drawCircle(490,300,10);
    glColor3f(1,1,0);
    drawCircle(340,300,12);
    drawCircle(460,300,12);
    glBegin(GL_QUADS);
        //bottom thing
         glColor3f(0.3,0.3,0.3);
         glVertex3f(370,235,0);
         glVertex3f(430,235,0);
         glVertex3f(430,220,0);
         glVertex3f(370,220,0);

         glVertex3f(350,175,0);
         glVertex3f(450,175,0);
         glVertex3f(450,220,0);
         glVertex3f(350,220,0);
        //Driver
        glColor3f(0.6,0.6,0.6);
        glVertex3f(300,380,0);
        glVertex3f(500,380,0);
        glColor3f(0.7,0.7,0.7);
        glVertex3f(500,470,0);
        glVertex3f(300,470,0);
        //Number
        glColor3f(0.6,0.6,0.6);
        glVertex3f(360,490,0);
        glVertex3f(440,490,0);
        glVertex3f(440,520,0);
        glVertex3f(360,520,0);
        //black
        glColor3f(0.3,0.3,0.3);
        glVertex3f(290,280,0);
        glVertex3f(510,280,0);
        glColor3f(0.1,0.1,0.1);
        glVertex3f(510,540,0);
        glVertex3f(290,540,0);
        //pink
        //glColor3f(0.6134,0.1312,0.82);
        selectColor();
        glVertex3f(270,260,0);
        glVertex3f(530,260,0);
        glVertex3f(530,560,0);
        glVertex3f(270,560,0);
        //Lower gray
        glColor3f(0.6,0.6,0.6);
        glVertex3f(270,220,0);
        glVertex3f(270,260,0);
        glVertex3f(530,260,0);
        glVertex3f(530,220,0);
    glEnd();
    //top pink
    glBegin(GL_POLYGON);
    //glColor3f(0.6134,0.1312,0.82);
    selectColor();
    for(float i=38;i<=140;i++)
    {
        x=168*cos(toRadians(i));
        y=168*sin(toRadians(i));
        glVertex3f(x+400,y+452,0);
    }
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.8,0.8,0.8);
    for(float i=180;i<=360;i++)
    {
        x=130*cos(toRadians(i));
        y=130*sin(toRadians(i));
        glVertex3f(x+400,y+220,0);
    }
    glEnd();
}

void createTrackFront()
{
    glLineWidth(50);
    glBegin(GL_QUADS);
        glColor3f(0.3,0.3,0.3);
        //right
        glVertex3f(690,0,0);
        glVertex3f(540,300,0);
        glVertex3f(560,300,0);
        glVertex3f(710,0,0);

        //left
        glVertex3f(110,0,0);
        glVertex3f(260,300,0);
        glVertex3f(240,300,0);
        glVertex3f(90,0,0);

        //block
        glColor3f(0.7,0.7,0.7);
        glVertex3f(380,00,0);
        glVertex3f(380,50,0);
        glVertex3f(420,50,0);
        glVertex3f(420,00,0);
    glEnd();
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3f(0.1,0.1,0.1);
    for(int x=300;x<=500;x+=20)
    {
        if(x<(500+300)/2)
        {
            glVertex3f(x-15,0,0);
            glVertex3f(x,200,0);
        }
        else{
            int t=x;
            glVertex3f(t+15,0,0);
            glVertex3f(t,200,0);
        }
    }
    glEnd();
    glBegin(GL_QUADS);
        glColor3f(0.3,0.3,0.3);
        glVertex3f(250,0,0);
        glVertex3f(300,200,0);
        glVertex3f(500,200,0);
        glVertex3f(550,0,0);

        glColor3f(0.45,0.324,0.09);
        glVertex3f(230,0,0);
        glVertex3f(280,200,0);
        glVertex3f(300,200,0);
        glVertex3f(250,0,0);

        glVertex3f(550,0,0);
        glVertex3f(500,200,0);
        glVertex3f(520,200,0);
        glVertex3f(570,0,0);
        //Yellow Rail
        glColor3f(0.8,0.5536,0.096);
        glVertex3f(200,0,0);
        glVertex3f(250,200,0);
        glVertex3f(300,200,0);
        glVertex3f(250,0,0);
        glVertex3f(550,0,0);
        glVertex3f(500,200,0);
        glVertex3f(550,200,0);
        glVertex3f(600,0,0);
        //side walls
        glColor3f(0.6,0.6,0.6);
        glVertex3f(690,0,0);
        glVertex3f(540,300,0);
        glVertex3f(540,200,0);
        glVertex3f(540,0,0);
        glVertex3f(110,0,0);
        glVertex3f(260,300,0);
        glVertex3f(260,200,0);
        glVertex3f(210,0,0);
        //Background
        glColor3f(0,0,0.8);
        glVertex3f(0,0,0);
        glVertex3f(0,850,0);
        glVertex3f(750,850,0);
        glVertex3f(750,0,0);
    glEnd();
}

void drawCircle(int x,int y,float r)
{
    float x1,y1;
    glBegin(GL_POLYGON);
    for(float i=0;i<=360;i++)
    {
        x1=r*cos(i);
        y1=r*sin(i);
        glVertex3f(x1+x,y1+y,0);
    }
    glEnd();
}

void selectColor()
{
    if(tno%2!=0)
    {
        glColor3f(0.4835,0.1008,0.56);
    }
    else
    {
        glColor3f(0,0.4,0);
    }
}

void getInside(int *outside)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5,0.5,0.5,1);
    glutDetachMenu(GLUT_LEFT_BUTTON);
    glutMouseFunc(mouseFunc);
    glutCreateMenu(insideMenu);
    glutAddMenuEntry("Get Down",1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    if(gd==1)
    {
        *outside=1;
        return;
    }
    if(view%3==0)
        top();
    else if(view%2==0)
        side();
    else
        front();
}

void top()
{
    //holders
    glColor3f(1,1,0);
    glLineWidth(10);
    genHolders(200);
    genHolders(390);
    genHolders(580);
    //poles
    glColor3f(1,1,0);
    glRectf(100,0,120,550);
    glRectf(660,0,680,550);
    glRectf(0,410,920,380);
    glColor3f(0.8,0.8,0);
    glRectf(630,520,710,580);
    glRectf(70,520,150,580);
    //red box
    smallTrain();
    glColor3f(0.7,0.7,0.7);
    glRectf(190,360,300,250);
    glColor3f(1,0,0);
    glRectf(170,380,320,230);
    //ac
    glColor3f(0.5,0.5,0.5);
    glRectf(760,510,950,620);
    glRectf(560,510,750,620);
    glRectf(360,510,550,620);
    glRectf(200,510,350,620);
    glRectf(000,510,190,620);
    //Top
    glColor3f(0.2,0.2,0.2);
    glRectf(0,450,920,500);
    glColor3f(0.3,0.3,0.3);
    glRectf(0,450,920,650);
    glColor3f(0.4,0.4,0.4);
    glRectf(0,650,920,850);
    //window
    glColor3f(0.0648,0.5989,0.81);
    glRectf(450,100,920,0);
    glColor3f(1,0.7,0);
    glRectf(440,110,920,0);
}

void smallTrain()
{
    int i;
    char str[]="namma";
    glRasterPos3f(430,560,0);
    for(i=0;i<(int)strlen(str);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
    char str1[]="metro";
    glRasterPos3f(430,540,0);
    for(i=0;i<(int)strlen(str);i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str1[i]);
    glColor3f(0.8,0.8,0.8);
    glRectf(250,300,280,330);
    glColor3f(0,0.5,0);
    glRectf(290,250,240,340);
    glColor3f(0.9,0.7,0);
    glRectf(190,250,240,290);
}

void genHolders(int x)
{
    glBegin(GL_LINE_LOOP);
        glVertex3f(x,380,0);
        glVertex3f(x+20,380,0);
        glVertex3f(x+20,370,0);
        glVertex3f(x+30,350,0);
        glVertex3f(x+30,320,0);
        glVertex3f(x-10,320,0);
        glVertex3f(x-10,350,0);
        glVertex3f(x,370,0);
        glVertex3f(x,380,0);
    glEnd();
}

void side()
{
    //pole
    glColor3f(1,1,0);
    glRectf(700,140,715,850);
    glRectf(200,140,215,850);
    //Pillars
        glColor3f(0.48,0.2986,0.0768);
    glRectf(360,540,720,580);
    glRectf(20,540,110,580);
    glRectf(150,540,250,580);
        glColor3f(0.4,0.4,0.4);
    glRectf(400,510,420,560);
    glRectf(460,510,480,560);
    glRectf(520,510,540,560);
    glRectf(580,510,600,560);
    glRectf(640,510,660,560);
    glRectf(700,510,720,560);
    glRectf(20,450,40,580);
    glRectf(80,450,100,580);
    glRectf(160,450,180,580);
    glRectf(220,450,240,580);
    glColor3f(0,0.4,0);
    glRectf(300,240,650,450);
    glColor3f(0,0.2,0);
    glRectf(650,240,660,470);
    //door pannel
    glColor3f(0.3,0.3,0.3);
    glRectf(130,200,136,700);
    glRectf(0,670,270,700);
    glColor3f(0.0648,0.5989,0.81);
    glRectf(20,450,110,600);
    glRectf(150,450,250,600);
    glRectf(360,510,720,740);
    glColor3f(0.6,0.6,0.6);
    glRectf(0,200,270,700);
    glBegin(GL_QUADS);

        //seat bottom
        glColor3f(0.8,0.8,0.8);
        glVertex3f(300,240,0);
        glVertex3f(230,150,0);
        glVertex3f(550,150,0);
        glVertex3f(650,240,0);
        glColor3f(0.4,0.4,0.4);
        glVertex3f(230,150,0);
        glVertex3f(550,150,0);
        glVertex3f(550,130,0);
        glVertex3f(230,130,0);
        glVertex3f(550,140,0);
        glVertex3f(550,130,0);
        glVertex3f(660,240,0);
        glVertex3f(650,240,0);
        glColor3f(0,0.2,0);
        glVertex3f(300,450,0);
        glVertex3f(320,470,0);
        glVertex3f(650,470,0);
        glVertex3f(650,450,0);
        //floor
        glColor3f(0,0,0.3);
        glVertex3f(0,0,0);
        glVertex3f(0,200,0);
        glVertex3f(900,200,0);
        glVertex3f(900,0,0);
    glEnd();
        //windows
    glColor3f(0.0648,0.5989,0.81);
    glRectf(20,450,110,600);
    //border
    glColor3f(1,0.7,0);
    glRectf(350,500,730,750);

}
void front()
{
    glColor3f(1,1,0);
    glRectf(155,210,175,850);
    glRectf(605,210,625,850);
    glRectf(230,320,245,850);
    glRectf(510,320,525,850);
    glRectf(280,460,290,850);
    glRectf(460,460,470,850);
    glBegin(GL_QUADS);
        glColor3f(0.3283,0.6529,0.67);
    glVertex3f(555,560,0);
    glVertex3f(575,540,0);
    glVertex3f(575,560,0);
    glVertex3f(555,580,0);
    glVertex3f(185,540,0);
    glVertex3f(205,560,0);
    glVertex3f(205,580,0);
    glVertex3f(185,560,0);
    //Board
    glColor3f(0.6,0.6,0.6);
    glVertex3f(665,625,0);
    glVertex3f(725,600,0);
    glColor3f(0.8,0.8,0.8);
    glVertex3f(725,540,0);
    glVertex3f(665,570,0);
        glColor3f(1,0,0);
    glVertex3f(655,650,0);
    glVertex3f(735,620,0);
    glVertex3f(735,520,0);
    glVertex3f(655,560,0);
    //left seat
        glColor3f(0,0.2,0);
    glVertex3f(0,200,0);
    glVertex3f(30,200,0);
    glVertex3f(130,360,0);
    glVertex3f(110,360,0);
        glColor3f(0,0.4,0);
    glVertex3f(30,0,0);
    glVertex3f(30,200,0);
    glVertex3f(130,360,0);
    glVertex3f(130,200,0);
        glColor3f(0.8,0.8,0.8);
    glVertex3f(130,200,0);
    glVertex3f(220,200,0);
    glVertex3f(150,0,0);
    glVertex3f(0,0,0);

    //Right seat
        glColor3f(0,0.2,0);
    glVertex3f(830,200,0);
    glVertex3f(800,200,0);
    glVertex3f(700,360,0);
    glVertex3f(720,360,0);
        glColor3f(0,0.4,0);
    glVertex3f(800,0,0);
    glVertex3f(800,200,0);
    glVertex3f(700,360,0);
    glVertex3f(700,200,0);
        glColor3f(0.8,0.8,0.8);
    glVertex3f(720,200,0);
    glVertex3f(610,190,0);
    glVertex3f(680,0,0);
    glVertex3f(830,0,0);
    //inner inner wall
    glColor3f(0.45,0.45,0.45);
    glVertex3f(280,500,0);
    glVertex3f(280,850,0);;
    glVertex3f(480,850,0);
    glVertex3f(480,500,0);
    //inner inner floor
        glColor3f(0,0,0.3);
    glVertex3f(220,350,0);
    glVertex3f(280,500,0);
    glVertex3f(480,500,0);
    glVertex3f(540,350,0);
    //inner wall
    glColor3f(0.5,0.5,0.5);
    glVertex3f(220,350,0);
    glVertex3f(220,850,0);
    glVertex3f(540,850,0);
    glVertex3f(540,350,0);
    //inner floor
    glColor3f(0,0,0.3);
    glVertex3f(170,250,0);
    glVertex3f(220,350,0);
    glVertex3f(540,350,0);
    glVertex3f(590,250,0);
    //door sides
    glColor3f(0.4,0.4,0.4);
    glVertex3f(170,900,0);
    glVertex3f(170,250,0);
    glVertex3f(590,250,0);
    glVertex3f(590,900,0);
    //floor
    glColor3f(0,0,0.3);
    glVertex3f(0,0,0);
    glVertex3f(130,250,0);
    glVertex3f(630,250,0);
    glVertex3f(800,0,0);
    //left
    glColor3f(0.6,0.6,0.6);
    glVertex3f(0,0,0);
    glVertex3f(0,900,0);
    glVertex3f(130,900,0);
    glVertex3f(130,250,0);
    //right
    glVertex3f(630,250,0);
    glVertex3f(630,900,0);
    glVertex3f(850,900,0);
    glVertex3f(800,0,0);
    glEnd();
}
void mouseFunc(int b,int s,int x,int y)
{
    if(b==GLUT_LEFT_BUTTON && s==GLUT_DOWN)
    {
        view++;
        glutPostRedisplay();
    }
    glutPostRedisplay();
}
void menu(int num)
{
  value = num;
  glutPostRedisplay();
}
void createMenu(void){
    menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Byappanahalli - 35 RS",1);
    glutAddMenuEntry("Vijaynagar - 25Rs",3);
    glutAddMenuEntry("Nayandhalli - 30Rs",2);
    glutAddMenuEntry("Magadi Road -20Rs ",4);
    glutAddMenuEntry("MG Road - 15Rs",5);
    glutAddMenuEntry("Move to Token check",6);
    glutAttachMenu(GLUT_LEFT_BUTTON);
}
void insideMenu(int id)
{
    glutDetachMenu(GLUT_LEFT_BUTTON);
    n=999;
    gd=1;
    glutPostRedisplay();
}
void trainMenu(int id)
{
    if(id==1)
    {
         in=1;
    }
    if(id==2)
    {
        n=10;
        tt=0;
        tno++;
        tf=850;
        te=1350;
        glutPostRedisplay();
    }
    if(id==3)
        exit(0);
}
void keyboard(unsigned char key,int x,int y)
{
    if(key=='p' || key=='P')
        {
            sceneChange=2;
            glutPostRedisplay();
        }
    if(key=='M' || key=='m')
        {
            enter=1;
            glutPostRedisplay();
        }

}
