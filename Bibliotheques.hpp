#ifndef BIBLIOTHEQUES_H
#define BIBLIOTHEQUES_H
/**
 * \file Bibliotheque.hpp
 * \brief Header de la classe Bibliotheque
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
#include <experimental/filesystem>

/*! \namespace std
*  espace de nommage regroupant les outils composants
* les bibliotheques standard
*/


using namespace std ;
 

  /*! \struct Descripteurs
   * \brief strucuture de descripteurs d'images qui permettent de manipuler nos fichiers csv 
   */

struct Descripteurs {
private:
    /*!< Liste des morceaux*/
    string m_acces,m_chemin,m_titre,m_source,m_numero, m_largeur,m_hauteur,m_cout;
    

public:
    /*!Getters Acces*/
    /** 
    * \brief Permet de visualiser une image selon le niveau d'utilisateur 
    */
    //Acces
    string getAcces() const { return m_acces; }
    /**
    * \brief Affecter l'acces a l'utilisateur
    */
    void setAcces(string a_acces) { this->m_acces = a_acces;}
    
    /*!Getters Chemin*/
    /** 
    * \brief Permet d'accéder au chemin des images
    */
    //Chemin
    string getChemin() const { return m_chemin; }
     
    /*!Setters Chemin*/
    /**
    * \brief Affecter le chemin de l'image 
    */
    void setChemin(string a_chemin) { this->m_chemin = a_chemin;}

    /*!Getters Titre*/
    /** 
    * \brief Permet d'accéder au titre des images
    */
    string getTitre() const { return m_titre; }

    /*!Setters Titre*/
    /** 
    * \brief Affecter un titre aux images
    */
    void setTitre(string a_titre) { this->m_titre = a_titre;}
    
    /*!Getters Source*/
    /** 
    * \brief Permet d'accéder aux sources des images
    */
    string getSource() const { return m_source; }

    /*!Setters Source*/
    /** 
    * \brief Permet d'affecter une source aux images
    */
    void setSource(string a_source) { this->m_source = a_source;}

    /*!Getters Numero*/
    /** 
    * \brief Permet d'accéder aux numéros des images
    */
    string getNumero() const { return m_numero; }
    /*! Setters Numero*/
    /** 
    * \brief Permet d'affecter un numéro aux images
    */
    void setNumero(string a_numero) { this->m_numero = a_numero;}
    
    /*!Getters Largeur*/
    /** 
    * \brief Permet d'accéder à la largeur des images
    */

    string getLargeur () const { return m_largeur; }

    /*!Setters Largeur*/
    /** 
    * \brief Permet d'affecter une largeur aux images
    */
    void setLargeur(string a_largeur) { this->m_largeur = a_largeur;}

    /*!Getters Hauteur*/
    /** 
    * \brief Permet d'accéder à la hauteur des images
    */
    string getHauteur () const { return m_hauteur; }
    /*!Setters Hauteur*/
    /** 
    * \brief Permet d'affecter une hauteur aux images
    */
    void setHauteur(string a_hauteur) { this->m_hauteur = a_hauteur;}

    /*!Getters Cout*/
    /** 
    * \brief Permet d'accéder aux couts des images
    */
    string getCout() const { return m_cout; }
    /*!Setters Cout*/
    /** 
    * \brief Permet d'affecter un cout aux images
    */
    void setCout(string a_cout) { this->m_cout = a_cout; }
};
  
  /*! \class Bibliotheque
   * \brief classe represente toutes les méthodes que nous allons utilisé 
   *  pour gérer nos fichier de données
   *  
   */

class Bibliotheque {
private:    
    string m_chemincsv; /*!< Chemin vers les fichiers csv*/
protected :
    vector<Descripteurs> bibliotheque; /*!< Vecteur des discripteurs de la bibliotheque*/
    int p_choice_Image; /*!< Numero pour la sélection de l'image pour le traitement d'image*/
public:
    /*!Getters getChemincsv*/
    /** 
    * \brief Permet d'accéder aux chemins csv 
    */
    string getChemincsv() const { return m_chemincsv; }
    /*!Setters setChemincsv*/
    /** 
    * \brief Permet d'affecter un nouveau chemin csv
    */
    void setChemincsv(string a_chemincsv) { this->m_chemincsv = a_chemincsv;}
    
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe Bibliotheque
     */
    Bibliotheque();
    
    /*!
     *  \brief Vérifier la présence de l'extension csv
     *
     *  Methode qui permet d'ajouter ou non l'extension csv lors de la saisie
     *  du nom par l'utilisateur
     * 
     *  \param  a_Name_file : le nom dont la présence de l'extension sera csv ; string
     *  \return si le nom comporte l'exention aucun changement dans le cas contraire
     *  ajout de ".csv".
     */
    string Verification_Extensioncsv(string a_Name_file);
    /*!
     *  \brief Lecture des descripteurs  
     *
     *  Stockage des descripteurs images dans le vecteur vector<Descripteurs> bibliotheque
     */
    void Lecture_descripteurs();

    /*!
     *  \brief Ecriture des descripteurs  
     *
     *  \param a_path : Chemin pour enregistrer le fichier csv  string
     *  
     *  Ecriture dans une nouvelle bibliotheque ou non des descripteurs d'image   
     */
    void Ecriture_descripteurs(string const a_path);
     
     /*!
     *  \brief Affichage des descripteurs  
     * 
     *  Affiche les descripteurs des images présents dans la bibliotheque choisie
     *  par l'utilisateur   
     */
    void AfficherDescripteurs();
    
    /*!
     * \brief Affichage des descripteurs selon numéro  
     * 
     * \param a_num : Choix 
     *  Affiche les descripteurs d'une images choisie par l'utilisateur   
     */
    void AfficherDescripteurs(int const a_num);

    /*!
     * \brief Affichage des descripteurs selon numéro  
     * 
     *  Surdéfinition de la fonction AfficherDescripteurs    
     */
    void AfficherCout();

    /*!
     * \brief Suppression de descripteurs  
     * 
     *  Supprime les descripteurs associés à une image choisie par l'utilisateur dans la bibliotheque   
     */
    void Supprimer();

    /*!
     * \brief Ajout de descripteurs  
     * 
     *  Ajoute des descripteurs associés à une image dans la bibliotheque par l'utilisateur   
     */
    void Ajouter_image();

    /*!
     * \brief Tri des images selon les critères suivants :  
     * \n 1 : Cout croissant
     * \n 2 : Par ordre alphabétique
     * \param choix : Choix pour sélectionner un critère de tri
     * Trie les descripteurs selon l'ordre croissant du cout ou bien à les titres rangés par ordre alphabétique   
     */
    void Tri(int choix);

    /*!
     * \brief Affichage d'une sous-liste des images selon les critères suivants :  
     * \n 1 : Gratuit
     * \n 2 : Cout inferieur a 9.99 euros
     * \n 3 : Cout compris entre 10 et 99.99 euros
     * \n 4 : Cout superieur a 100 euros
     * \param prix : choix pour sélectionner la gamme de prix afin de filtrer les images 
     *  Affichage d'une sous-liste d'image selon divers critères de prix   
     */
    void Sous_liste(int prix);

    /*!
     * \brief Affichage d'une sous-liste des images selon le critère suivants :  
     * \n 1 : Par source de l image
     * Affichage d'une sous-liste d'image la nature de la source de l'image
     */
    void Sous_liste_autre();

    /*!
     * \brief Affichage d'une sous-liste des images selon le critère suivants :  
     * \n 1 : Par source de l image
     * Affichage d'une sous-liste d'image la nature de la source de l'image
     */
    void Sauvegarder();

    /*!
     * \brief Modification de descripteurs  
     * 
     * Modifie les descripteurs d'une image
     */
    void ModifierDescripteur() ;


    /*!
     * \brief Sélection de l'image pour le traitement d'image  
     * 
     * Sélectionne l'imge afin d'appliquer un traitement d'image
     */
    void Selection_Image();  
};

#endif // BIBLIOTHEQUES_H
