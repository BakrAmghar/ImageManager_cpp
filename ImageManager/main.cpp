#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <cctype>

using namespace std;

const string path = "testing/";

struct Pixel
{
  int r;
  int g;
  int b;
};



//Ouvrir fichier automatiquement
void ouvrirImage(const string& nomFichier)
{
    system(("start " + path + nomFichier).c_str());
}


//GRAY SCALEEE
bool GrayScale(const string &nomFichierIN,const string &nomFichierOUT)
{
    ifstream fIN(path + nomFichierIN);
    ofstream fOUT(path + nomFichierOUT);

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

                fOUT << moyGris << " ";
                fOUT << moyGris << " ";
                fOUT << moyGris << " ";
            }
         fOUT << endl;
       }
  return true;
}

//RED AND GRAYY
bool RedAndGray(const string &nomFichierIN,const string &nomFichierOUT)
{
    ifstream fIN(path + nomFichierIN);
    ofstream fOUT(path + nomFichierOUT);

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

                          fOUT << moygris << " ";
                          fOUT << moygris << " ";
                          fOUT << moygris << " ";
                        }
                }
            fOUT << endl;
        }
    return true;
}

//Inversee les couleurs
bool InverseCouleur(const string &nomFichierIN, const string &nomFichierOUT)
{
    ifstream fIN(path + nomFichierIN);
    ofstream fOUT(path + nomFichierOUT);

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
    ifstream fIN(path + nomFichierIN);
    ofstream fOUT(path + nomFichierOUT);

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
    ofstream fOUT(path + nomFichierOUT);
    ifstream fIN(path + nomFichierIN);

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

//Rotation d'une image
bool Rotation(const string &nomFichierIN, const string &nomFichierOUT)
{
    ifstream fIN(path + nomFichierIN);
    ofstream fOUT(path + nomFichierOUT);

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

//Cree une Image
bool creerImageTest(const string& nomFichier)
{
    ofstream f(path + nomFichier);

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

//fct qui calcule la moyenne des pixels
Pixel CalculeMoyenne2(const Pixel T1, const Pixel T2)
{
    Pixel Tmoy;

    Tmoy.r = (T1.r + T2.r) / 2;
    Tmoy.g = (T1.g + T2.g) / 2;
    Tmoy.b = (T1.b + T2.b) / 2;

    return Tmoy;
}

Pixel CalculeMoyenne4(const Pixel T1, const Pixel T2, const Pixel T3, const Pixel T4)
{
    Pixel Tmoy;

    Tmoy.r = (T1.r + T2.r + T3.r + T4.r) / 4;
    Tmoy.g = (T1.g + T2.g + T3.g + T4.g) / 4;
    Tmoy.b = (T1.b + T2.b + T3.b + T4.b) / 4;

    return Tmoy;
}

//fct d'agr
bool Agrandissement(const string &nomFichierIN,const string &nomFichierOUT)
{
    ofstream fOUT(path + nomFichierOUT);
    ifstream fIN(path + nomFichierIN);

      if(!fIN || !fOUT) return false;

    string format;
    int largeur, hauteur, lum;

    fIN >> format;
    fIN >> largeur >> hauteur;
    fIN >> lum;

    int hauteur_agr {hauteur * 2 - 1};
    int largeur_agr {largeur * 2 - 1};

    fOUT << format << endl;
    fOUT << largeur_agr << " " << hauteur_agr << endl;
    fOUT << lum << endl;

    vector <vector<Pixel>> tIN(hauteur, vector<Pixel>(largeur));
    vector <vector<Pixel>> tOUT(hauteur_agr, vector<Pixel>(largeur_agr));

    //stockage des valeurs (RGB) initial de fichier !agr + Stockage en nv tableau
    for(int i{0}; i < hauteur; ++i)
        {
            for(int j{0}; j < largeur; ++j)
                {
                    fIN >> tIN[i][j].r;
                    fIN >> tIN[i][j].g;
                    fIN >> tIN[i][j].b;

                    tOUT[2*i][2*j] = tIN[i][j];
                    if(j < largeur - 1) tOUT[2*i][2*j + 1] = CalculeMoyenne2( tIN[i][j], tIN[i][j+1] );
                    if(i < hauteur - 1) tOUT[2*i + 1][2*j] = CalculeMoyenne2( tIN[i][j], tIN[i+1][j] );
                    if(j < largeur - 1 && i < hauteur - 1) tOUT[2*i + 1][2*j + 1] = CalculeMoyenne4( tIN[i][j], tIN[i][j+1], tIN[i+1][j], tIN[i+1][j+1] );
                }
        }

    //Ecriture sur fichier agr
    for(int i{0}; i < hauteur_agr; ++i)
        {
            for(int j{0}; j < largeur_agr; j++)
                {
                    fOUT << tOUT[i][j].r << " ";
                    fOUT << tOUT[i][j].g << " ";
                    fOUT << tOUT[i][j].b << " ";
                }
            fOUT << endl;
        }
    return true;

}



//menu;
void menu()
{
    int choix{};
    string name;
    do
    {
        cout << "\n========= IMAGE MANAGER =========\n";
        cout << "1 - Creer une image test\n";
        cout << "2 - Ouvrir une image et la manipuler\n";
        cout << "3 - GrayScale\n";
        cout << "4 - Rouge et Gris\n";
        cout << "5 - Inversion des couleurs\n";
        cout << "6 - Extraire une partie\n";
        cout << "7 - Symetrie verticale\n";
        cout << "8 - Rotation 90 degres\n";
        cout << "9 - Aggrandissement\n";
        cout << "0 - Quitter\n";
        cout << "Choix : ";

        cin >> choix;

        switch (choix)
        {
        case 1:
            name = "test.ppm";
            if (creerImageTest("test.ppm"))
            {
                cout << "Image creee !" << endl;
                ouvrirImage("test.ppm");
            }
            else
                cout << "Erreur !" << endl;
            break;

        case 2:

            cout << "Nom du fichier  : ";
            cin  >> name;

                ouvrirImage(name);

            break;

        case 3:
            if (GrayScale(name, "GrayScale.ppm"))
            {
                cout << "GrayScale cree !" << endl;
                ouvrirImage("GrayScale.ppm");
            }
            else
                cout << "Erreur !" << endl;
            break;

        case 4:
            if (RedAndGray(name, "RednGray.ppm"))
            {
                cout << "RednGray cree !" << endl;
                ouvrirImage("RednGray.ppm");
            }
            else
                cout << "Erreur !" << endl;
            break;

        case 5:
            if (InverseCouleur(name, "Inverse.ppm"))
            {
                cout << "Inverse cree !" << endl;
                ouvrirImage("Inverse.ppm");
            }
            else
                cout << "Erreur !" << endl;
            break;

        case 6:
            if (ExtraireImage(name, "Extraction.ppm",
                              40, 120, 10, 45))
            {
                cout << "Extraction creee !" << endl;
                ouvrirImage("Extraction.ppm");
            }
            else
                cout << "Erreur !" << endl;
            break;

        case 7:
            if (SymetrieVertical(name, "Symetrie.ppm"))
            {
                cout << "Symetrie creee !" << endl;
                ouvrirImage("Symetrie.ppm");
            }
            else
                cout << "Erreur !" << endl;
            break;

        case 8:
            if (Rotation(name, "Rotation.ppm"))
            {
                cout << "Rotation creee !" << endl;
                ouvrirImage("Rotation.ppm");
            }
            else
                cout << "Erreur !" << endl;
            break;

        case 9:
            if( Agrandissement(name, "Agrandissement.ppm"))
            {
                cout << "Agrandissement cree !" << endl;
                ouvrirImage("Agrandissement.ppm");
            }else
               cout << "Erreuuuuuur!" << endl;
            break;

        case 0:

           while(true)
           {
               char reponseSup;
               system("taskkill /IM i_view64.exe /F"); /* Fermeture de tout les tabs IRFANVIEW */
               cout << "\nVoullez-vous supprimer les images generee (Y/N) : ";
               cin  >> reponseSup;

             if(toupper(reponseSup) == 'Y' )
                {
                   filesystem::remove_all(path);
                   return;
                }
                 else if(toupper(reponseSup) == 'N') return;
           }

            cout << "Au revoir !!!" << endl;
            break;

        default:
            cout << "Choix invalide !" << endl;
        }

    } while (choix != 0);
}

//Art lol
void CreditsArts()
{
cout << "               _ _                            ___        _            _   __  __ ___ _  _   _   ___    \n";
    cout << "   _ _ ___ __ _| (_)___ ___   _ __  __ _ _ _  | _ ) __ _| |___ _     /_\\ |  \\/  |/ __| || | /_\\ | _ \\  \n";
    cout << "  | '_/ -_) _` | | (_-</ -_) | '_ \\/ _` | '_| | _ \\/ _` | / / '_|   / _ \\ |\\/| | (_ | __ |/ _ \\   /  \\ \n";
    cout << "  |_| \\___\\__,_|_|_/__/\\___| | .__/\\__,_|_|   |___/\\__,_|_\\_\\_|  /_/ \\_\\_|  |_|\\___|_||_/_/ \\_\\_|_\\ \n";
    cout << "        _ _   _        |_|___  ___        _        _               _                         \n";
    cout << "   __ _(_) |_| |_ _  _| |__   / __ \\| _ ) __ _| |___ _ /_\\  _ __  __ _| |_  __ _ _ _              \n";
    cout << "  / _` | |  _| ' \\ || | '_ \\ / / _` | _ \\/ _` | / / '_/ _ \\| '  \\/ _` | ' \\/ _` | '_|             \n";
    cout << "  \\__, |_|\\__|_||_\\_,_|_.__/ \\ \\__,_|___/\\__,_|_\\_\\_|/_/ \\_\\_|_|_\\__, |_||_\\__,_|_|                  \n";
    cout << "  |___/     _          _ ___  \\____/ ____  ___        _            |___/          _                 \n";
    cout << "  | (_)_ _ | |_____ __| |_ _|_ _    / __ \\| _ ) __ _| |___ _    /_\\  _ __  __ _| |_  __ _ _ _      \n";
    cout << "  | | | ' \\| / / -_) _` || || ' \\  / / _` | _ \\/ _` | / / '_|  / _ \\| '  \\/ _` | ' \\/ _` | '_|       \n";
    cout << "  |_|_|_||_|_\\_\\___\\__,_|___|_||_| \\ \\__,_|___/\\__,_|_\\_\\_|  /_/ \\_\\_|_|_\\__, |_||_\\__,_|_|          \n";
}
int main()
{
   filesystem::create_directory(path); /* Creation/Lecture de repo */
   CreditsArts();
   menu();
}
