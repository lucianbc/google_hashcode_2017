#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct Pizza
{
    int R, C, L, H;
    char** map;

    void afisare()
    {
        cout<<R<<" "<<C<<" "<<L<<" "<<H<<endl;
        for(int i = 0; i < R; i++)
        {
            for(int j = 0; j < C; j++)
                cout<<map[i][j]<<" ";
            cout<<endl;
        }
    }

    void dezaloca()
    {
        for(int i = 0; i < R; i++)
            delete(map[i]);
        delete(map);
    }
};

struct Felie
{
    int xl, yl, xr, yr;
    Felie(int x1, int y1, int x2, int y2)
    {
        xl = x1;
        xr = x2;
        yl = y1;
        yr = y2;
    }
    void afisare()
    {
        cout<<xl<<" "<<yl<<" "<<xr<<" "<<yr<<endl;
    }

    int Arie()
    {
        return (int)(abs(xr - xl + 1) * abs(yr - yl + 1));
    }
};

struct Comb
{
    int w, h;
    Comb(int w, int h)
    {
        this->w = w;
        this->h = h;
    }
};

Pizza citire(char* inputFile)
{
    Pizza p;
    fstream fin;
    fin.open(inputFile, ios::in);

    cout<<fin.is_open()<<endl;

    fin>>p.R>>p.C>>p.L>>p.H;

    p.map = new char*[p.R];

    for(int i = 0; i < p.R; i++)
    {
        p.map[i] = new char[p.C];
        fin>>p.map[i];
    }

    fin.close();

    return p;
}

vector<Comb> generateCombs(Pizza myPizza)
{
    vector<Comb> combs;
    for(int i = 0; i < myPizza.H; i++)
    {
        for(int j = 0; (i + 1) * (j + 1) <= myPizza.H; j++)
        {
            combs.push_back(Comb(i, j));
        }
    }
    return combs;
}

int evalueazaFelie(Pizza myPizza, Felie crtFelie)
{
    if(crtFelie.Arie() > myPizza.R * myPizza.C){ /*cout<<"arie\n";*/ return -1; }
    if(crtFelie.xl > crtFelie.xr || crtFelie.yl > crtFelie.yr) { /*cout<<"indici\n";*/ return -1; }
    if(myPizza.map[crtFelie.yl][crtFelie.xl] != 'T' && myPizza.map[crtFelie.yl][crtFelie.xl] != 'M') { /*cout<<"Luat\n";*/ return -1; }
    if(crtFelie.xr >= myPizza.C || crtFelie.yr >= myPizza.R) { /*cout<<"afara\n";*/ return -1; }
    int nr_t = 0, nr_m = 0;
    for (int i = crtFelie.yl; i <= crtFelie.yr; i++) {
        for (int j = crtFelie.xl; j <= crtFelie.xr; j++)
            if (myPizza.map[i][j] == 'T') nr_t++;
            else if (myPizza.map[i][j] == 'M') nr_m++;
            else return -1;
    }
    if (nr_t >= myPizza.L && nr_m >= myPizza.L) return nr_t + nr_m;
    else return -1;
}

vector<Felie> taie(Pizza myPizza)
{
    vector<Felie> felii;
    vector<Comb> combs = generateCombs(myPizza);

    cout<<"combs generated\n";

    for(int i = 0; i < myPizza.R; i++)
    {
        for(int j = 0; j < myPizza.C; j++)
        {
            int imax = -1, scmax = -1;
            for(int k = 0; k < combs.size(); k++)
            {
                Felie f(j, i, j + combs[k].w, i + combs[k].h);
                int sc = evalueazaFelie(myPizza, f);
                if(sc > scmax)
                {
                    imax = k;
                    scmax = sc;
                }
            }

            if(scmax > -1) {
                Felie f(j, i, j + combs[imax].w, i + combs[imax].h);
                felii.push_back(f);

                for (int ii = f.yl; ii <= f.yr; ii++)
                    for (int jj = f.xl; jj <= f.xr; jj++)
                        myPizza.map[ii][jj] = ' ';

            }
        }
    }
    return felii;
}

void afisare(vector<Felie> felii, char* outputFile)
{
    fstream fout;
    fout.open(outputFile, ios::out);

    fout<<felii.size()<<endl;

    for(int i = 0; i < felii.size(); i++)
        fout<<felii[i].yl<<" "<<felii[i].xl<<" "<<felii[i].yr<<" "<<felii[i].xr<<endl;

    fout.close();
}

int main(int argc, char* argv[]) {

    Pizza myPizza = citire(argv[1]);

    vector<Felie> felii = taie(myPizza);

    cout<<"trece\n";
    afisare(felii, argv[2]);

    myPizza.afisare();

    myPizza.dezaloca();

    return 0;
}