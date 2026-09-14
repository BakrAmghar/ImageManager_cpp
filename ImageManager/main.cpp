#include <iostream>
#include <fstream>
#include <string>


using namespace std;

//GRAY SCALEEE
bool GrayScale(const string &nomFichierIN,const string &nomFichierOUT)
{
    ifstream fIN(nomFichierIN);
    ofstream fOUT(nomFichierOUT);

    if(!fIN || !fOUT) return false;

    string format;
    int hauteur, longeur, lum;

    fIN >> format;
    fIN >> longeur >> hauteur;
    fIN >> lum;

    fOUT << format << endl;
    fOUT << longeur << " " << hauteur << endl;
    fOUT << lum << endl;

     for(int i{0}; i < hauteur; i++)
       {
        for(int j{0}; j < longeur; j++)
            {
                int r,g,b;
                fIN >> r >> g >> b;

                int moyGris = 0.2126*r + 0.7152 *g + 0.0722*b;

                for(int tmp{0}; tmp < 3; tmp++)
                    {
                        fOUT << moyGris << " ";
                    }
            }
         fOUT << endl;
       }
  return true;
}

//RED AND GRAYY
bool RedAndGray(const string &nomFichierIN,const string &nomFichierOUT)
{
    ifstream fIN(nomFichierIN);
    ofstream fOUT(nomFichierOUT);

    if(!fIN || !fOUT) return false;

    string format;
    int hauteur, longeur, lum;

    fIN >> format;
    fIN >> longeur >> hauteur;
    fIN >> lum;

    fOUT << format << endl;
    fOUT << longeur << " " << hauteur << endl;
    fOUT << lum << endl;

     for(int i{0}; i < hauteur; i++)
        {
            for(int j{0}; j < longeur; j++)
                {
                    int r,g,b;
                    fIN >> r >> g >> b;

                    if((r > 1.3*g) && (r > 1.3*b))
                    {
                        fOUT << r << " " << g << " " << b << " ";
                    }else
                        {
                          int moygris = 0.2126*r + 0.7152 *g + 0.0722*b;
                          for(int tmp{0}; tmp < 3; tmp++)
                            {
                                fOUT << moygris << " ";
                            }
                        }
                }
            fOUT << endl;
        }
    return true;
}

//Inversee les couleurs
bool InverseCouleur(const string &nomFichierIN, const string &nomFichierOUT)
{
    ifstream fIN(nomFichierIN);
    ofstream fOUT(nomFichierOUT);

    if(!fIN || !fOUT) return false;

    string format;
    int largeur, hauteur, lum;

    fIN >> format;
    fIN >> largeur >> hauteur;
    fIN >> lum;

    fOUT << format << endl;
    fOUT << largeur << " " << hauteur << endl;
    fOUT << lum << endl;

    for(int i{0}; i < hauteur; i++)
        {
            for(int j{0}; j < largeur; j++)
                {
                    int r,g,b;
                    fIN >> r >> g >> b;
                    fOUT << 255-r << " " << 255-g << " " << 255-b << " ";
                }
            fOUT << endl;
        }
    return true;
}

//Extraire Image
bool ExtraireImage(const string &nomFichierIN, const string &nomFichierOUT, int c1, int c2, int l1, int l2)
{
    ifstream fIN(nomFichierIN);
    ofstream fOUT(nomFichierOUT);

    if(!fIN || !fOUT) return false;

    string format;
    int largeur, hauteur, lum;

    fIN >> format;
    fIN >> largeur >> hauteur;
    fIN >> lum;

    fOUT << format << endl;
    fOUT << c2 - c1 + 1 << " " << l2 - l1 + 1 << endl;
    fOUT << lum << endl;

     for(int i{0}; i < hauteur; i++)
     {
         for(int j{0}; j < largeur; j++)
            {
                int r,g,b;
                fIN >> r >> g >> b;

                if((i >= l1 && i <= l2) && (j >= c1 && j <=c2))
                {
                    fOUT << r << " " << b << " " << g << " ";
                }
            }
       fOUT << endl;
     }

}
void menu()
{
   int choix;

   do
   {
       cout << "=========MENU IMAGE MANAGER==========\n";
       cout << "1 - GrayScale \n";


       cin >> choix;

       switch(choix)
       {
         case 1:
          break;

         case 0:
            return;
       }


   }while(choix != 0);
}

int main()
{
  cout << "test ";
}
