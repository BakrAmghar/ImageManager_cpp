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

//Ouvrir fichier automatiquement
void ouvrirImage(const string& nomFichier)
{
    system(("start " + nomFichier).c_str());
}

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
            for(int j{0}; j < hauteur ; ++j)
                {
                    fOUT << T[j][i].r << " ";
                    fOUT << T[j][i].g << " ";
                    fOUT << T[j][i].b << " ";
                }
            fOUT << endl;
        }
    return true;
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

//menu;
void menu()
{
    int choix{};

    do
    {
        cout << "\n========= IMAGE MANAGER =========\n";
        cout << "1 - Creer une image test\n";
        cout << "2 - GrayScale\n";
        cout << "3 - Rouge et Gris\n";
        cout << "4 - Inversion des couleurs\n";
        cout << "5 - Extraire une partie\n";
        cout << "6 - Symetrie verticale\n";
        cout << "7 - Rotation 90 degres\n";
        cout << "0 - Quitter\n";
        cout << "Choix : ";

        cin >> choix;

        switch (choix)
        {
        case 1:
            if (creerImageTest("test.ppm"))
            {
                cout << "Image creee !" << endl;
                ouvrirImage("test.ppm");
            }
            else
                cout << "Erreur !" << endl;
            break;

        case 2:
            if (GrayScale("test.ppm", "GrayScale.ppm"))
            {
                cout << "GrayScale cree !" << endl;
                ouvrirImage("GrayScale.ppm");
            }
            else
                cout << "Erreur !" << endl;
            break;

        case 3:
            if (RedAndGray("test.ppm", "RednGray.ppm"))
            {
                cout << "RednGray cree !" << endl;
                ouvrirImage("RednGray.ppm");
            }
            else
                cout << "Erreur !" << endl;
            break;

        case 4:
            if (InverseCouleur("test.ppm", "Inverse.ppm"))
            {
                cout << "Inverse cree !" << endl;
                ouvrirImage("Inverse.ppm");
            }
            else
                cout << "Erreur !" << endl;
            break;

        case 5:
            if (ExtraireImage("test.ppm", "Extraction.ppm",
                              40, 120, 10, 45))
            {
                cout << "Extraction creee !" << endl;
                ouvrirImage("Extraction.ppm");
            }
            else
                cout << "Erreur !" << endl;
            break;

        case 6:
            if (SymetrieVertical("test.ppm", "Symetrie.ppm"))
            {
                cout << "Symetrie creee !" << endl;
                ouvrirImage("Symetrie.ppm");
            }
            else
                cout << "Erreur !" << endl;
            break;

        case 7:
            if (Rotation("test.ppm", "Rotation.ppm"))
            {
                cout << "Rotation creee !" << endl;
                ouvrirImage("Rotation.ppm");
            }
            else
                cout << "Erreur !" << endl;
            break;

        case 0:
            cout << "Au revoir !" << endl;
            break;

        default:
            cout << "Choix invalide !" << endl;
        }

    } while (choix != 0);
}

int main()
{
  menu();
}
