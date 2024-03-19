#ifndef TRAITEMENT_H
#define TRAITEMENT_H
/**
 * \file traitement.hpp
 * \brief Header de la classe Traitement
 * \version 0.1
 * \date 2023-01-27
 * \authors 
 * \copyright Copyright (c) 2023
 * 
 */
// Systeme
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "../header/Bibliotheques.hpp"

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <experimental/filesystem>

/*! \namespace std
*  espace de nommage regroupant les outils composants
* les bibliotheques standard
*/
using namespace std ;
/*! \namespace cv
*  espace de nommage regroupant les outils composants
* les bibliotheques de traitement d'Opencv
*/
using namespace cv ;

/**
 * @class Traitement 
 * @brief La classe Traitement permet la gestion des images et des différents traitements
 *  à appliqué sur l'image
 * Elle herite des fonctions public de la classe Bibliotheque et des descripteurs  
 */

class Traitement : public Bibliotheque, public Descripteurs         //Traitement hérites des fonctions publics Descripteur Bibliotheque
    {
    private :
        /* Attributs */
        Mat m_Image;    /*!< Image sélectionnée pour le traitement*/
        Mat m_Image_trait; /*!< Image après traitement*/
        string m_PathImage; /*!< Image chemin vers l'image sélectionnée pour le traitement */
 
    public :
        /*!
        *  \brief Constructeur
        *
        *  Constructeur de la classe Traitement
        */
        Traitement();

        /*!Getters Image*/
        /** 
        * \brief Permet d'accéder a l'image séléctionnée pour le traitement 
        */
        Mat getImage() const { return m_Image; }

        /*!Setters setImage*/
        /** 
        * \brief Permet de stocker l'image sélectionnée pour le traitement
        */
        void setImage(Mat a_Image) { this->m_Image = a_Image;}
        
        /*!Getters AccesgetPathImag*/
        /** 
        * \brief Permet d'accéder au chemin de l'image selectionnée pour le traitement 
        */
        string getAccesgetPathImage() const { return m_PathImage; }

        /*!Setters AccesgetPathImage*/
        /** 
        * \brief Permet d'affecter un nouveau chemin à l'image sélectionnée
        */
        void setAccesgetPathImage(string a_PathImage) { this->m_PathImage = a_PathImage;}

        /*!Getters getImageTraite*/
        /** 
        * \brief Permet d'accéder a l'image traitée 
        */
        Mat getImageTraite() const { return m_Image_trait; }
        
        /*!Setters ImageTraite*/
        /** 
        * \brief Permet de stocker l'image traitée
        */
        void setImageTraite(Mat a_Image_trait) { this->m_Image_trait = a_Image_trait;}

        /*Methodes*/

        /*!
        * \brief Affichage du contenu de l'image  
        * \param Image_In : Image traitée 
        * Affichage de l'image avant et après traitement 
        */
        void AfficherContenuImage(const Mat Image_In);														// Afficher le contenu de l'image
		
        /*!
        * \brief Menu de sélection de Traitement Image  
        * \n 1 : Histogramme
        * \n 2 : Gaussien
        * \n 3 : Moyenneur
        * \n 4 : Median
        * \n 5 : Sobel
        * \n 6 : Seuillage Simple 
        * \n 7 : Segmentation
        * Modifie les descripteurs d'une image
        */
        void TraitementImage() ;

        /*!
        * \brief Verification de saturation  
        * \param valeur : valeur 
        *  Ramène les pixels dans l'intervalle de 0 et 255  
        */        
        int VerifierSaturation(const int valeur);

        /*!
        * \brief Menu de sélection de Traitement Image  
        * \n 1 : Filtre moyenneur
        * \n 2 : Gradien en x
        * \n 3 : Gradien en y 
        * \n 4 : Laplacien
        * \param typeFiltre : Choix du filtre par l'utilisateur
        * Modifie les descripteurs d'une image
        */
        Mat Filtre(const int typeFiltre);

        /*!
        * \brief Matrice de convolution  
        * \param Image_In : Image sélectionnée pour le traitement d'image
        * \param filtre : Filtre   
        *  Effectue l'opération de convolution entre l'image sélectionné par l'utilisateur et le filtre  
        */       
        Mat MatriceConvolution(const Mat Image_In, const Mat filtre);
        
        
        /*!
        * \brief Norme matriciel  
        * \param Image_In : Image sélectionnée pour le traitement d'image
        * \param filtre : Filtre   
        *  Calcule la norme du gradients  
        */ 
        Mat norme_matriciel (const Mat Image, const Mat Image2);
        
        
        /*!
        * \brief Seuillage  
        *    
        *  Effectue une opération de seuillage; les pixels dont l'intensité sont supérieure ou égale au seuil choisi 
        * prendra la valeur 255 , sinon 0  
        */ 
        Mat Seuillage_simple();

        /*!
        * \brief Sobel  
        *    
        * Détection les bords dans une image 
        */ 
        Mat Sobel();

         /*!
        * \brief Médian  
        *    
        * Pour chaque pixel prend la valeur médiane de ses voisins proches. 
        */
        Mat Median();

        /*!
        * \brief Moyenneur  
        *    
        * Multiplie chaque valeur de pixel de l’image d’entrée par la valeur correspondante dans le kernel 
        */
        Mat Moyenneur();

        /*!
        * \brief Gaussien  
        *    
        * Lissage global de l'image en modifiant la valeur de la variance 
        */
        Mat Gaussien();

        /*!
        * \brief Segmentation  
        *    
        * Segmentation d'image couleur pour filtrer 
        */
        Mat Segmentation();

        /*!
        * \brief Rehaussement
        *    
        * Réalise par la soustraction de l’image originale avec une version de l’image qui a été
        * traité avec le filtre laplacien pour mettre en évidence les contours 
        */
        Mat RehaussementContour();

         /*!
        * \brief Egalisation_histogramme;
        *    
        * Affichage de l'égalisation de l'histogramme 
        */
        void Egalisation_histogramme();


        /*!
        * \brief Recherche_extension  
        * \param a_Image_name : Nom de l'image
        * \param ext : extension   
        *  Recherche une extension compatible pour enregistrer les image  
        */
        bool recherche_extension(const string& a_Image_name, const string& a_ext);
        
        /*!
        * \brief Egalisation_histogramme;
        *    
        * Sauvegarde des traitements  
        */
        void Sauvegarder();


} ;
    
    
    

#endif // TRAITEMENT_H
