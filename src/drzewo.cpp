#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

void zeruj(int **tabl, int a)
{
    for(int i=0;i<a;i++)
    {
        for(int j=0;j<a;j++)
        {
            tabl[i][j]=0;
        }
    }
}

void findm(int **tab, int &x, int &y, int &w, int a)
{
    x=10000;
    y=10000;
    w=1000;
    for(int i=0;i<a;i++)
    {
        for(int j=0;j<a;j++)
        {
            if((tab[i][j]<w)&&(tab[i][j]!=0))
            {
                x=i;
                y=j;
                w=tab[i][j];
            }
        }
    }
    tab[x][y]=0;
    tab[y][x]=0;

}

void sprawdz(int **czysta, int &x, int &y, int &w, int **drzewo,int a )
{
    if(((czysta[x][y]==0) || (czysta[x][x]==0))&&((czysta[y][x]==0)||(czysta[y][y]==0)))
    {
        for(int i=0;i<a;i++)
        {
            czysta[x][i]=czysta[x][i]+czysta[y][i];
            czysta[y][i]=czysta[x][i];
        }
            drzewo[x][y]=w;
            drzewo[y][x]=w;
    }
}

void inic(int **czysta, int a)
{
    for(int i=0;i<a;i++)
    {
        for(int j=0;j<a;j++)
        {
            if(i==j) czysta[i][j]=1;
            else czysta[i][j]=0;
        }
    }
}

int czyend(int **czysta, int a)
{
    for(int i=0;i<a;i++)
    {
        int tmp=0;
        for(int j=0;j<a;j++)
        {
            if (czysta[i][j]!=0) tmp++;
        }
        if (tmp>=a) return 1;
    }
    return 0;
}

void wypisz(int **tab, int a)
{
    for(int i=0;i<a;i++)
    {
        for(int j=0;j<a;j++)
        {
            printf("%4d", tab[i][j]);
        }
        cout << endl;
    }
}


int main()
{
    ifstream myfile("plik.txt");
    int a;
    myfile >> a;
    int **tab=new int*[a];
    int **czysta=new int*[a];
    int **drzewo=new int*[a];
    for(int i=0;i<a;i++)
    {
        tab[i]=new int[a];
        czysta[i]=new int[a];
        drzewo[i]=new int[a];
    }
    int i=0;
    int j=0;
    zeruj(drzewo, a);
    inic(czysta, a);
    int b,x,y,w;
    while(myfile >> b)
    {
       tab[i][j]=b;
       i++;
       if((i>=a))
       {
           i=0;
           j++;
       }
    }
    while(!(czyend(czysta,a))){
    findm(tab,x,y,w,a);
    sprawdz(czysta,x,y,w,drzewo,a);
    }

    myfile.close();
    ofstream myfile2("docel.txt");
    for(int i=0;i<a;i++)
    {
        for(int j=0;j<a;j++)
        {
            myfile2 << drzewo[i][j] << " ";
        }
        myfile2 << endl;
    }
    myfile2.close();


    return 0;
}
