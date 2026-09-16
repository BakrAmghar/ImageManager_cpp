#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <filesystem>

struct Pixel
{
  int r;
  int g;
  int b;
};


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
                    fOUT << r << " " << g << " " << b << " ";
                }
            }

      if(i >= l1 && i <= l2) fOUT << endl; //retour a la ligne

     }
  return true;
}

//Symetrie Vertical D'une image
bool SymetrieVertical(const string &nomFichierIN, const string &nomFichierOUT)
{
    ofstream fOUT(nomFichierOUT);
    ifstream fIN(nomFichierIN);

    if(!fIN || !fOUT) return false;

    string format;
    int largeur, hauteur, lum;

    fIN >> format;
    fIN >> largeur >> hauteur;
    fIN >> lum;

    fOUT << format << endl;
    fOUT << largeur << " " << hauteur << endl;
    fOUT << lum << endl;

    vector<vector<Pixel>> T(hauteur, vector<Pixel>(largeur));

    //Extrait les donnees (r,g,b) du fichier
    for(int i{0}; i < hauteur; ++i)
        {
            for(int j{0}; j < largeur; ++j)
                {
                    fIN >> T[i][j].r;
                    fIN >> T[i][j].g;
                    fIN >> T[i][j].b;
                }
        }

    //Ecriture Inverse dans fichier OUT
    for(int i{0}; i < hauteur; ++i)
        {
            for(int j{largeur - 1}; j >=0; --j)
                {
                    fOUT << T[i][j].r << " ";
                    fOUT << T[i][j].g << " ";
                    fOUT << T[i][j].b << " ";
                }
          fOUT << endl;
        }

   return true;
}

//Rotation d'une image:
bool Rotation(const string &nomFichierIN, const string &nomFichierOUT)
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
    fOUT << hauteur << " " << largeur << endl;
    fOUT << lum << endl;

    vector <vector<Pixel>> T(hauteur, vector<Pixel>(largeur));

    //extraction
    for(int i{0}; i < hauteur; ++i)
        {
            for(int j{0}; j < largeur; ++j)
                {
                    fIN >> T[i][j].r;
                    fIN >> T[i][j].g;
                    fIN >> T[i][j].b;
                }
        }

    for(int i{largeur - 1}; i >= 0; --i)
        {
            for(int j{hauteur - 1}; j >= 0; --j)
                {
                    fOUT << T[j][i].r << " ";
                    fOUT << T[j][i].g << " ";
                    fOUT << T[j][i].b << " ";
                }
            fOUT << endl;
        }
}

bool creerImageTest(const string& nomFichier)
{
    ofstream f(nomFichier);

    if(!f) return false;

    f << "P3" << endl;
    f << "256 60" << endl;
    f << "255" << endl;

    for (int i{0}; i < 60; ++i)
    {
        for (int j{0}; j < 256; ++j)
        {
            if (j < 64)
                f << "255 0 0 ";        // rouge
            else if (j < 128)
                f << "0 255 0 ";        // vert
            else if (j < 192)
                f << "0 0 255 ";        // bleu
            else
                f << "255 255 0 ";      // jaune
        }

        f << endl;
    }

    f.close();
  return true;
}

void menu()
{
   int choix;


   do
   {
       cout << "=========MENU IMAGE MANAGER==========\n";
       cout << "1 - Creer une Image \n";
       cout << "2 - GrayScale \n";
       cout << "3 - Rouge et Gris \n";
       cout << "4 - Inverstion d'image \n";
       cout << "5 - Extraire une partie d'image \n";
       cout << "6 - Symetrie Vertical \n";
       cout << "7 - Rotation d'image \n";


       cin >> choix;

       switch(choix)
       {
         case 1:

             if(creerImageTest("test.ppm")) cout << "Creation avec success du test.ppm" << endl;
              else
                {
                  cout << "Erreur lors de la creation" << endl;
                }

          break;

         case 2:

             if(GrayScale("test.ppm","GrayScale.ppm") cout << "Creation avec success du GrayScale.ppm" << endl;
              else
                {
                  cout << "Erreur lors de la creation" << endl;
                }

         case 3:
             if(RedAndGray("test.ppm", "RednGray.ppm")) cout << "Creation avec success du RednGray.ppm" << endl;
              else
              {
                  cout << "Erreur lors de la creation" << endl
              }
         case 0:
            return;
       }


   }while(choix != 0);
}

int main()
{

   creerImageTest("test.ppm");

    SymetrieVertical("test.ppm", "symetrie.ppm");
    Rotation("test.ppm", "rotation.ppm");

    cout << "Tests termines !" << endl;
    cout << filesystem::current_path() << endl;

  cout << "test ";
}
