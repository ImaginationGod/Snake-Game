// Snake Game
#include<iostream>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<vector>
using namespace std;

void Color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

char space[100][100]; // Stores whitespace in 100x100 area --> space[height level][width]
char fruit;
int height,width,x,y,x2,y2;
int num,countL=0,fruitWin=0,a=0,b=0,c=0,point=0,once=0;
int head=0;
int prevx,prevy,prev2x,prev2y;
int tailx[100],taily[100];

void tail_logic() // Copied 
{
    prevx = tailx[0]; // Holds last value of 'x'
    prevy = taily[0]; // Holds last value of 'y'
    tailx[0] = x; 
    taily[0] = y;
    for(int i=1;i<point;i++)
    {
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }
}

void title()
{
    Color(14);
    cout<<"\t      SNAKE GAME"<<endl;
    Color(7);
}

void gameWin()
{
    Color(11);
    cout<<"\t      VICTORY!!!"<<endl;
    Color(7);
}

void gameOver()
{
    Color(4);
    cout<<"\t      GAME OVER!!!"<<endl;
    Color(7);
}

void totalPoints()
{
    Color(11);
    cout<<"\t    TOTAL POINTS : "<<point<<endl;
    Color(7);
}

void initialize()
{
    for(int i=0;i<100;i++)
    {
        for(int j=0;j<100;j++)
        {
            space[i][j]=' '; // space[height level][width]
        }
    }
    height = 12;
    width = 40;
    x = width/2; // Default value
    y = height/2; // Default value
}

void fruitPosition()
{
    srand(time(0));
    {x2 = rand()%(width-2);} // Randomizes b/w x=0 & x=38
    srand(time(0));
    {y2 = rand()%height;}
}

void grid()
{
    system("cls"); // Clears previous screen --> Makes it look animated
    title();
    if(fruitWin==0) // Makes it randomize only once
    {
        fruitPosition();
        fruitWin = 1;
    }
    head=0; // Snake head
    for(int i=0;i<width;i++) // border width
    {
        cout<<"=";
        if(i==(width-1))
        {
            cout<<endl;
            for(int j=0;j<height;j++) // y-axis 
            {
                cout<<"|";
                for(int k=0;k<(width-2);k++) // x-axis = (width - 2)
                {
                    if(x==-1 && once==1) // Snake hitting 'left' wall
                    {
                        x=width-2;
                        k--;
                        once=0;
                        continue;
                    }
                    if(x==width-1 && once==1) // Snake hitting 'right' wall
                    {
                        x=0;
                        k--;
                        once=0;
                        continue;
                    }
                    if(y==-1 && once==1) // Snake hitting 'top' wall
                    {
                        y=height;
                        k--;
                        once=0;
                        continue;
                    }
                    if(y==height+1 && once==1) // Snake hitting 'bottom' wall
                    {
                        y=0;
                        k--;
                        once=0;
                        continue;
                    }

                    if(j==y2 && k==x2 && c<1) // Executes once per frame
                    {
                        Color(5);
                        cout<<"$";
                        Color(7);
                        continue;
                    }
                    if(x==x2 && y==y2 && c<1)
                    {
                        c=1;
                        point++; // Increases points
                        a=point;
                        b=a; // For assigning value later to 'a'
                        fruitWin=0;
                        goto increment;
                    }
                    if((j==y && k==x))
                    {
                        increment:
                        {
                            Color(2);
                            // cout<<"O";
                            if(head==0){cout<<"O";head=1;}
                            Color(7);
                            a=b;
                            continue;
                        }
                    }
                    if(a>0)
                    {
                        // bool print = false;
                        int print = 0;
                        for(int l=0;l<point;l++)
                        {
                            if(tailx[l]==k && taily[l]==j)
                            {
                                cout<<"x";
                                print = /*true*/ 1;
                                a--;
                                goto go_on;
                            }
                        }
                        if(print>0){goto spaces;}
                    }

                    // Tail movement
                    spaces:
                    {cout<<space[j][k];}
                    go_on: continue;
                }
                cout<<"|"<<endl;
            }
            for(int l=0;l<width;l++)
            {
                cout<<"=";
            }
            cout<<endl;
        }
    }
}

void input()
{
    if (_kbhit ()) // _kbhit returns a nonzero value if a key has been pressed. Otherwise, it returns 0
    {
        switch (_getch ()) // Gets a character from the console without echo
        {
            case 'a':
            num = 1;
            break;

            case 'd':
            num = 2;
            break;

            case 'w':
            num = 3;
            break;

            case 's':
            num = 4;
            break;

            case 'x':
            countL = 1;
            break;
        }
    }
}

int main()
{
    initialize();
    for(int i=0;;i++)
    {
        if(countL!=0)
        {
            grid();
            gameOver();
            totalPoints();
            break;
        }
        if(point==10)
        {
            grid();
            gameWin();
            totalPoints();
            break;
        }
        grid();
        tail_logic();
        totalPoints();
        input();
        if(num==1)
        {x--;c=0;once=1;}
        else if(num==2)
        {x++;c=0;once=1;}
        else if(num==3)
        {y--;c=0;once=1;}
        else if(num==4) 
        {y++;c=0;once=1;}
        Sleep(150);
    }
    return 0;
}
