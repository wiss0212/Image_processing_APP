/**
 * @file main.cpp
 * @brief main
 * @version 0.1
 * @date 2023-01-28
 * @authors Lyakout TESSADA, Wissem SMATI, Manel TAIABI,
 * @authors Yasmine KARIM, Hugo ANDRE, Daniela TALBA
 * @copyright Copyright (c) 2023
 * 
 */

#include "../header/Bibliotheques.hpp"
#include "../header/traitement.hpp"

using namespace std;

using namespace cv; // A SUPPRIMER

const int User_niveau_1 = 1;
const int User_niveau_2 = 2;

void droits_user();
void menu_principale(int droits,Traitement biblio);
bool authentification(string userId);
void PourContinuer();
void menu_traitement();

void droits_user() {
    string userId;

    cout << endl << "****************************************************************" << endl
         << endl << "********               Menu d'identification               *****" << endl
         << endl << "****************************************************************" << endl;


    cout <<"bienvenue cher utilisateur"<<endl
    <<"Veuillez entrer votre identifiant : ";
    cin >> userId;
    if (authentification(userId)) {
            cout<<endl << "Connexion réussie!" << endl;
        }
    else {
            cout << "Identifiant incorrect" << endl;
            cout << "Accès refusé" << std::endl;
            PourContinuer();
            droits_user();            
        }

    vector<pair<string, int>> utilisateurs = {{"LL11LL", User_niveau_1}, {"LL22LL", User_niveau_2}};
    for (auto &user : utilisateurs) {
        if (user.first == userId) {
            Traitement l_biblio;
            l_biblio.Lecture_descripteurs();
            
             menu_principale(user.second,l_biblio);
        }
    }

}
 

bool authentification(string userId) {
    vector<string> autorisation_users = {"LL11LL", "LL22LL"};
    for (auto &autorisation : autorisation_users) {
        if (autorisation == userId) {
        
            return true;
        }
    }
   
    return false;
}

void PourContinuer(){
    cout << endl << "Tapez sur la touche Entree pour retourner au menu..."<<endl;
    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
    cin.get();
}

void menu_traitement(){

    cout << endl << "****************************************************************" << endl;
    cout << endl << "********           Menu  de traitement des Images          *****" << endl;
    cout << endl << "****************************************************************" << endl;
    cout << endl << "1. Histogramme" << endl;
    cout << endl << "2. Gaussien" << endl;
    cout << endl << "3. Moyenneur" << endl;
    cout << endl << "4. Median" << endl;
    cout << endl << "5. Sobel" << endl;
    cout << endl << "6. Seuillage" << endl;
    cout << endl << "7. Segmentation" << endl;
    cout << endl << "8. Rehaussement de contours" << endl;
    cout << endl << "0. Retour au précédent" << endl;             
}

void menu_principale(int droits,Traitement biblio) {

        int Choice;
        
        if (droits == User_niveau_1) {
                
                cout << "Accès autorisé aux fonctionnalités d'un utilisateur de niveau 1" << endl;
                
                while(1){
                    
                    string saisi;
                    cout << endl << "****************************************************************" << endl;
                    cout << endl << "********   Menu Principal de la gestion de bibliotheque   *****" << endl;
                    cout << endl << "****************************************************************" << endl;
                    cout << endl << "1. Affichage" << endl;
                    cout << endl << "2. Mise a jour de la bibliotheque" << endl;
                    cout << endl << "3. Triage de la bibliotheque" << endl;
                    cout << endl << "4. Sous liste des descripteurs" << endl;
                    cout << endl << "5. Sauvegarder la bibliotheque" << endl;
                    cout << endl << "6. Application d'un traitement d'images" << endl;
                    cout << endl << "0. Retour au menu d identification" << endl;
                    cout << endl << "Veuillez saisir votre choix!"<<endl;
                    
                    while(!(cin>>Choice)) {
                        cout << "Veuillez entrer un numero d'image valide: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    switch(Choice){
                        case 1:
                            int Choice_aff;
                            while(1){

                            
                                cout << endl << "********             1. AFFICHAGE              *****" << endl<<endl;
                                cout << endl << "1. Affichage de la liste des descripteurs" << endl;
                                cout << endl << "2. Affichage du cout d'une image particuliere" << endl;
                                cout << endl << "0. Retour au menu precedent" << endl;
                                cout << endl << "Veuillez saisir votre choix!" << endl;
                                while(!(cin>>Choice_aff)) {
                                    cout << "Veuillez entrer un numero d'image valide: ";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }

                                switch (Choice_aff)
                                {
                                case 1 :
                                    biblio.AfficherDescripteurs();
                                    break;
                                
                                case 2 :
                                    biblio.AfficherCout();
                                    break;
                                
                                default:
                                    menu_principale(droits,biblio);
                                    break;
                                }
                                PourContinuer();
                            }
                            
                            break;
                        
                        case 2:
                            int Choice_maj;

                            while(1){
                            cout << endl << "********          2. MISE A JOUR DE LA BIBLIOTHEQUE           *****" << endl<<endl;
                            cout << endl << "1. Supprimer l'image" << endl;
                            cout << endl << "2. Ajouter une image" << endl;
                            cout << endl << "3. Modifier une ou des caracteristiques d'une image" << endl;
                            cout << endl << "0. Retour au menu precedent" << endl;
                            cout << endl << "Veuillez saisir votre choix!" << endl;
                            
                           
                            
                            
                            while(!(cin>>Choice_maj)) {
                                    cout << "Veuillez entrer un numero d'image valide: ";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                            
                            switch (Choice_maj)
                            {

                                case 1:
                                    biblio.Supprimer();
                                    biblio.AfficherDescripteurs();
                                    break;
                                
                                case 2:
                                    biblio.Ajouter_image();
                                    biblio.AfficherDescripteurs();
                                    break;

                                case 3:
                                    biblio.ModifierDescripteur();
                                    break;    
                                
                                default:
                                    menu_principale(droits,biblio);
                                    break;
                                }
                                PourContinuer();
                            }
                            break;
                            
                        case 3:
                            int Choice_tri;
                            while(1){
                                cout << endl << "********             3. TRIAGE DE LA BIBLIOTHEQUE              *****" << endl<<endl;
                                cout << endl << "1. Trier par ordre croissant" << endl;
                                cout << endl << "2. Trier par ordre alphabetique" << endl;                          
                                cout << endl << "0. Retour au menu precedent" << endl;
                                cout << endl << "Veuillez saisir votre choix!" << endl;   

                                while(!(cin>>Choice_tri)) {
                                        cout << "Veuillez entrer un numero d'image valide: ";
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                                
                                switch (Choice_tri)
                                {

                                    case 1:
                                        biblio.Tri(Choice_tri);
                                        //biblio.AfficherDescripteurs();
                                        break;
                                    
                                    case 2:
                                        biblio.Tri(Choice_tri);
                                        //biblio.AfficherDescripteurs();                                    
                                        
                                        break;

                                    default:
                                        menu_principale(droits,biblio);
                                        break;
                                    }
                                    PourContinuer();
                            }


                            break;
                        
                        case 4:
                            int Choice_lst;
                            while(1){
                                cout << endl << "********             4. SOUS LISTE DES DESCRIPTEURS              *****" << endl<<endl;
                                cout << endl << "1. Gratuit" << endl;
                                cout << endl << "2. Cout inferieur a 9.99 euros" << endl;
                                cout << endl << "3. Cout compris entre 10 et 99.99 euros" << endl;
                                cout << endl << "4. Cout superieur a 100 euros" << endl;
                                cout << endl << "5. Par source de l image" << endl;
                                cout << endl << "0. Retour au menu precedent" << endl;
                                cout << endl << "Veuillez saisir votre choix!" << endl;
                                
                                while(!(cin>>Choice_lst)) {
                                        cout << "Veuillez entrer un numero d'image valide: ";
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    }
                                
                                switch (Choice_lst)
                                {
                                    case 1:
                                        biblio.Sous_liste(Choice_lst);
                                        
                                        break;
                                    
                                    case 2:
                                        biblio.Sous_liste(Choice_lst);
                                        
                                        break;

                                    case 3:
                                        biblio.Sous_liste(Choice_lst);
                                        
                                        break;
                                        
                                    case 4:
                                        biblio.Sous_liste(Choice_lst);
                                        
                                        break;
                                        
                                    case 5:
                                        biblio.Sous_liste_autre();
                                        
                                        break;
                                        
                                    default:
                                        menu_principale(droits,biblio);
                                        break;
                                    }
                                    PourContinuer();
                                }
                            break;
                        
                        case 5:
                            int svg;
                            while(1){
                                cout << endl << "********             5. SAUVEGARDER LA BIBLIOTHEQUE              *****" << endl<<endl;
                                cout << endl << "1. Sauvegarder les modifications apportées sur la bibliotheque" << endl;
                                cout << endl << "0. Retour au menu precedent" << endl;
                                cout << endl << "Veuillez saisir votre choix!" << endl;
                                    
                                while(!(cin>>svg)) {
                                        cout << "Veuillez entrer un numero d'image valide: ";
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                                
                                switch (svg)
                                {
                                    case 1:
                                        biblio.Bibliotheque::Sauvegarder();
                                        break;

                                    default:
                                        menu_principale(droits,biblio);
                                        break;
                                    
                                }
                                PourContinuer();
                            }
                            break;
                            
                        case 6:
                            int Choice_app;
                            while(1){
                                cout << endl << "********     6. APPLICATION D UN TRAITEMENT D IMAGE       *****" << endl<<endl;
                                cout << endl << "1. Application d'un traitement d'images" << endl;
                                cout << endl << "0. Retour au menu precedent" << endl;
                                cout << endl << "Veuillez saisir votre choix!" << endl;
                                    
                                while(!(cin>>Choice_app)) {
                                        cout << "Veuillez entrer un numero d'image valide: ";
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                                
                                switch (Choice_app)
                                {
                                    case 1:
                                        
                                            
                                        biblio.AfficherDescripteurs();
                                        biblio.Selection_Image(); //Obligatoire
                                        menu_traitement();
                                        biblio.TraitementImage(); //Obligatoire

                                        break;

                                    default:
                                        menu_principale(droits,biblio);
                                        break;
                                    
                                } 
                                    cout << endl << "Tapez sur la touche Entree pour revenir au menu d'application de traitements d image"<<endl;
                                    cin.get();
                                
                            }
                            
                            break;
                            
                        default:
                            cout << endl << "Retour au menu precedent" << endl;
                            droits_user();
                            break;
                
                            
                            
                    }
                    PourContinuer();
                }
        } else if (droits == User_niveau_2) {
            
            cout << "Accès autorisé aux fonctionnalités d'un utilisateur de niveau 2" << endl<<endl;
            while(1){
                cout << endl << "****************************************************************" << endl;
                cout << endl << "********   Menu Principal de la gestion de bibliotheque   *****" << endl;
                cout << endl << "****************************************************************" << endl;
                cout << endl << "1. Affichage de la liste des descripteurs" << endl;
                cout << endl << "2. Affichage du cout d'une image particuliere" << endl;
                cout << endl << "0. Retour au menu precedent" << endl;
                cout << endl << "Veuillez saisir votre choix!" << endl;
                cin>>Choice;
                
                

                    switch(Choice){
                    case 1:
                        biblio.AfficherDescripteurs();
                        
                        break;
                    
                    case 2:
                        biblio.AfficherCout();    
                        break;
                    
                    default :
                        droits_user();
                        break;
                        
                }
                PourContinuer(); 
            }
           
        }
            
    
}




int main (void)
{
    droits_user();  
    //menu_principale();

    //Gestion Bibliotheque
    //Traitement biblio;
    //biblio.Lecture_descripteurs(); //Olbigatoire
    //biblio.AfficherDescripteurs();
    //biblio.Ajouter_image();
    //biblio.AfficherCout();
    //biblio.Tri();
    //biblio.Supprimer();
    //biblio.ModifierDescripteur();
    //biblio.AfficherDescripteurs();
    //ligne de commabde
    //biblio.Selection_Image(); //Obligatoire
    //biblio.TraitementImage(); //Obligatoire
    //biblio.Sous_liste();
    //biblio.Sous_liste_autre();
    //biblio.Sauvegarder();
    
    //A SUPPRIMER COMMANDE SUIVANTE
 /*  Traitement biblio;
     Mat Image_originale;
     Mat Image_originale_gray;
     Mat Image_bruit;
     Mat gaussine_noise;
     Mat Img_rslt;
     Image_originale = imread("./Data/Image/Fille.png",IMREAD_COLOR);
    gaussine_noise = Image_originale.clone();
    randn(gaussine_noise,18,30);
    Image_bruit = gaussine_noise + Image_originale;
    Mat saltpepper_noise = Mat::zeros(Image_originale.rows, Image_originale.cols,CV_8U);
    randu(saltpepper_noise,0,255);

    Mat black = saltpepper_noise < 30;
    Mat white = saltpepper_noise > 225;

    Mat saltpepper_img = Image_originale.clone();
    saltpepper_img.setTo(255,white);
    saltpepper_img.setTo(0,black);
    cvtColor(saltpepper_img,Image_originale_gray, CV_BGR2GRAY);
    cvtColor(Image_bruit,Image_originale_gray, CV_BGR2GRAY);
    imwrite("./Data/Image/Fille_random_noise.png", Image_originale_gray);*/

    return 0;
}