#include "./../header/Bibliotheques.hpp"

Bibliotheque::Bibliotheque(){
    string l_file_csv ;                                             // nom du fichier
    bool l_exist;                                                // Verification de l'existence du fichier

    string l_name_file;
    string l_path;
    do{
    // Saisie du nom du nouveau fichier
    cout << endl << "********              Choix des bibliotheques              *****" << endl<<endl;
    cout << "Veuillez donner le nom d'une bibliotheque existante: " << endl ;
    cin >> l_file_csv ;

    // Vérification de la présence de l'extension csv
    l_name_file = Verification_Extensioncsv(l_file_csv);
    l_path = "./Data/Bibliotheque/" +l_name_file;

    l_exist = experimental::filesystem::exists(l_path) ;
    }while (l_exist ==false);// Vérification ou non de l'existance du nom
    
    cout<<endl<<"Bienvenue et Félicitation !" << endl;

    m_chemincsv = l_path;
}

string Bibliotheque::Verification_Extensioncsv(string a_Name_file){
    string l_file_extension = ".csv";
    string l_name_file;
    //Rechercher la position de l'extension ".csv" dans le titre du fichier
    string::size_type idx = a_Name_file.rfind(l_file_extension);

    if (idx != std::string::npos) {
        l_name_file = a_Name_file;
    } 
    else {
        //ajout de lextension
        l_name_file = a_Name_file+".csv";
    }
    return l_name_file;
}

void Bibliotheque::Lecture_descripteurs(){
     
    string ligne;
    ifstream fichier_csv(m_chemincsv);

    if (!fichier_csv.good()) {
            cerr << "Erreur lors de l'ouverture du fichier " << m_chemincsv << endl;

    }
    //Ignorer l'entête
    getline(fichier_csv, ligne);
    
    while (getline(fichier_csv, ligne)) {
            
            stringstream ss(ligne);            
            //Descripteurs
            string a_acces,a_chemin,a_titre,a_source;
            string a_numero, a_largeur,a_hauteur;
            string a_cout;

            getline(ss, a_acces, ',');
            getline(ss, a_chemin, ',');
            getline(ss, a_titre, ',');
            getline(ss, a_cout, ',');
            getline(ss, a_source, ',');
            getline(ss, a_numero, ',');
            getline(ss, a_largeur, ',');
            getline(ss, a_hauteur);

            Descripteurs img;

            img.setAcces(a_acces);
            img.setChemin(a_chemin);
            img.setTitre(a_titre);
            img.setCout(a_cout);
            img.setSource(a_source);
            img.setNumero(a_numero);
            img.setLargeur(a_largeur);
            img.setHauteur(a_hauteur);

            //On le met dans un vecteur
            bibliotheque.push_back(img);           
            
    }
    
}

void Bibliotheque::AfficherDescripteurs() {
    //cout << "Afficher les descripteurs des images :" << endl;
    
        for (auto& img : bibliotheque) {
                cout<<endl << "Acces : "<<img.getAcces()
                    << " || " <<  "Chemin :"<<img.getChemin()   
                    << " || "<<  "Titre : "   <<img.getTitre()
                    << " || "<<  "Cout : "    <<img.getCout()
                    << " || "<<  "Source : "  <<img.getSource()
                    << " || "<<  "Numero : "  <<img.getNumero()
                    << " || "<<  "Largeur : " <<img.getLargeur()
                    << " || "<<  "Hauteur : " <<img.getHauteur()
                    << endl<<endl;
        }
    cout << "Taille de la bibliotheque :" << bibliotheque.size()<<endl;

}

void Bibliotheque::AfficherDescripteurs(int const a_num){
    
    cout << "Acces : "<<bibliotheque[a_num-1].getAcces()
         << " || " <<  "Chemin :"<<bibliotheque[a_num-1].getChemin()   
         << " || "<<  "Titre : "   <<bibliotheque[a_num-1].getTitre()
         << " || "<<  "Cout : "    <<bibliotheque[a_num-1].getCout()
         << " || "<<  "Source : "  <<bibliotheque[a_num-1].getSource()
         << " || "<<  "Numero : "  <<bibliotheque[a_num-1].getNumero()
         << " || "<<  "Largeur : " <<bibliotheque[a_num-1].getLargeur()
         << " || "<<  "Hauteur : " <<bibliotheque[a_num-1].getHauteur()
        << endl<<endl;

}

void Bibliotheque::Ajouter_image(){
    
string a_acces,a_chemin,a_titre,a_source;
string a_numero;
string a_cout,a_largeur,a_hauteur;
int a_cout_tmp,a_largeur_tmp,a_hauteur_tmp;

string l_path;
bool isValid_acces = false;
bool isValid_titre = false;

string l_last_nombre_img; // numero de la dernier image
int l_tmp; // numero de l'image en int

Descripteurs img;
//Acces
/*  "isValid_acces" qui est initialisé à false. La boucle while va continuer
    tant que la saisie n'est pas valide (isValid_acces = false).
    Si la saisie est valide, isValid est mis à true et la boucle s'arrête.
 */
while (!isValid_acces) {
        cout << "Quel Acces à donner à l'image (A ou N ) : ";
        cin >> a_acces;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (a_acces == "A" || a_acces == "N") {
            isValid_acces = true;
        } else {
            std::cout << "Acces non valide. Veuillez saisir 'A' ou 'N'." <<endl;
            
        }
    }

    //Chemin
    while (!isValid_titre) {
        
        cout << "Veuillez saisir le nom de l'image a rajouter "<< endl;
        getline(cin,a_titre);

        l_path = "./Data/Image/" + a_titre +".png";

        isValid_titre = experimental::filesystem::exists(l_path);
        
    }
    a_chemin = l_path;
    
    //Cout
    cout<<"Entrez la valeur du cout de l'image : "<<endl;
    while(!(cin>>a_cout_tmp)) {
            cout << "Veuillez une valeur de cout valide: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    a_cout = to_string(a_cout_tmp);

    //Source
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Entrez la source de l'image : "<<endl;
    getline(cin,a_source);

    //Numero
    l_last_nombre_img = bibliotheque.back().getNumero();
    l_tmp = atoi(l_last_nombre_img.c_str())+1;
    a_numero = to_string(l_tmp);

    //Largeur
    cout <<"Entrez la largeur de l'image : "<<endl;
    while(!(cin>>a_largeur_tmp)) {
            cout << "Veuillez une valeur de largeur valide: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    a_largeur = to_string(a_largeur_tmp);


    //Hauteur
    cout <<"Entrez la hauteur de l'image : "<<endl;
    while(!(cin>>a_hauteur_tmp)) {
            cout << "Veuillez une valeur de hauteur valide: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    a_hauteur = to_string(a_hauteur_tmp);
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    img.setAcces(a_acces);
    img.setChemin(a_chemin);
    img.setTitre(a_titre);
    img.setCout(a_cout);
    img.setSource(a_source);
    img.setNumero(a_numero);
    img.setLargeur(a_largeur);
    img.setHauteur(a_hauteur);
    bibliotheque.push_back(img);

}

void Bibliotheque::Tri(int choix) {

    int l_size_biblio;
    l_size_biblio = int(bibliotheque.size()); 
    switch (choix)
    {
    case 1 :
            sort(bibliotheque.begin(), bibliotheque.end(), [](const Descripteurs& a, const Descripteurs& b) {
        return stoi(a.getCout()) < stoi(b.getCout());
        });

        // réécrire les lignes triees 
        for (const auto& row : bibliotheque) {
            row.getAcces();row.getTitre();row.getChemin();
            row.getSource();row.getCout();row.getHauteur();
            row.getLargeur();row.getNumero();
        }

        for(int i = 1; i <=l_size_biblio;i++){
            bibliotheque[i-1].setNumero(to_string(i));
        }
        break;
    case 2:
           // trier les lignes  de fichier par Trie 
        std::sort(bibliotheque.begin(), bibliotheque.end(), [](const Descripteurs& a, const Descripteurs& b) {
            return a.getTitre() < b.getTitre();
            });

        // réécrire les lignes triees 
        for (const auto& row : bibliotheque) {
            row.getAcces();row.getTitre();row.getChemin();
            row.getSource();row.getCout();row.getHauteur();
            row.getLargeur();row.getNumero();
        }

        for(int i = 1; i <=l_size_biblio;i++){
            bibliotheque[i-1].setNumero(to_string(i));
        }
        break;
    default:
        break;
    }

    AfficherDescripteurs();

}

void Bibliotheque:: Sous_liste(int prix){



    
    vector<Descripteurs> l_sub_images;       

    if(prix == 1 ){
        
        copy_if(bibliotheque.begin(), bibliotheque.end(), back_inserter(l_sub_images), [](const Descripteurs& img){
        return img.getCout() == "0";});

    }

    if(prix == 2) {
        copy_if(bibliotheque.begin(), bibliotheque.end(), back_inserter(l_sub_images), [](const Descripteurs& img){
        return atoi(img.getCout().c_str()) <= 9.99;});

    }
        
    if(prix==3){
        copy_if(bibliotheque.begin(), bibliotheque.end(), back_inserter(l_sub_images), [](const Descripteurs& img){
        return atoi(img.getCout().c_str()) <= 99.99 && atoi(img.getCout().c_str()) > 10;});

    }   

    if(prix == 4) {
        copy_if(bibliotheque.begin(), bibliotheque.end(), back_inserter(l_sub_images), [](const Descripteurs& img){
        return atoi(img.getCout().c_str()) > 100;});

    }

    for (auto& img : l_sub_images) {
                cout<<endl << "Acces : "<<img.getAcces()
                    << " || " <<  "Chemin :"<<img.getChemin()   
                    << " || "<<  "Titre : "   <<img.getTitre()
                    << " || "<<  "Cout : "    <<img.getCout()
                    << " || "<<  "Source : "  <<img.getSource()
                    << " || "<<  "Numero : "  <<img.getNumero()
                    << " || "<<  "Largeur : " <<img.getLargeur()
                    << " || "<<  "Hauteur : " <<img.getHauteur()
                    << endl<<endl;
        }
  

}

void Bibliotheque:: Sous_liste_autre(){
    string  l_source;
    Descripteurs descripteur_sub_images;
    vector<Descripteurs> l_sub_images;



    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Veuillez entrer une source"<<endl;
    getline(cin,l_source);   
         for (auto & img : bibliotheque) {
            //cout << "Image " << i + 1 << " : " << bibliotheque[i].getSource() << endl;
            
            if(img.getSource() == l_source)
            {
                descripteur_sub_images.setAcces(img.getAcces());
                descripteur_sub_images.setChemin(img.getChemin());
                descripteur_sub_images.setTitre(img.getTitre());
                descripteur_sub_images.setCout(img.getCout());
                descripteur_sub_images.setSource(img.getSource());
                descripteur_sub_images.setNumero(img.getNumero());
                descripteur_sub_images.setLargeur(img.getLargeur());
                descripteur_sub_images.setHauteur(img.getHauteur());
                l_sub_images.push_back(descripteur_sub_images);
             }
        }
        
        for (auto& img : l_sub_images) {
                cout<<endl << "Acces : "<<img.getAcces()
                    << " || " <<  "Chemin :"<<img.getChemin()   
                    << " || "<<  "Titre : "   <<img.getTitre()
                    << " || "<<  "Cout : "    <<img.getCout()
                    << " || "<<  "Source : "  <<img.getSource()
                    << " || "<<  "Numero : "  <<img.getNumero()
                    << " || "<<  "Largeur : " <<img.getLargeur()
                    << " || "<<  "Hauteur : " <<img.getHauteur()
                    << endl<<endl;
        }


}

void Bibliotheque::Sauvegarder(){
    string l_file_csv ;                                             // nom du fichier
    bool l_exist;                                                // Verification de l'existence du fichier
      
    string l_name_file;
    string l_path;


    cout << "Veuillez saisir un nom pour enregister vos modifications : " << endl ;
    cin >> l_file_csv ;

        // Vérification de la présence de l'extension csv
    l_name_file = Verification_Extensioncsv(l_file_csv);
    l_path = "./Data/Bibliotheque/" +l_name_file;

    l_exist = experimental::filesystem::exists(l_path) ;

     if(l_exist){
        //e

        /*  "isValid_reponse" qui est initialisé à false. La boucle while va continuer
        tant que la saisie n'est pas valide (isValid_reponse = false).
        Si la saisie est valide, isValid_reponse est mis à true et la boucle s'arrête.
        */
        bool isValid_reponse = false;
        string l_reponse; //Réponse au question de confirmation Y ou N posé
        while (!isValid_reponse) {
            cout << l_name_file <<" existe deja. Voulez-vous le remplacez ? Y ou N" << endl ;;
            cin >> l_reponse;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (l_reponse == "Y" || l_reponse == "N") {
                isValid_reponse = true;
            } 
            else {
                std::cout << "Acces non valide. Veuillez saisir Y ou N." <<endl;
                cin.clear();
            }
        }
        if(l_reponse == "N"){
            //Nous revenous au début de la methode et on recommence la procédure
            Sauvegarder();
        }
        else{
            Ecriture_descripteurs(l_path);
            cout <<l_name_file<<" a été écrasé"<<endl;
        }
    
     }
     else{
        Ecriture_descripteurs(l_path);
        m_chemincsv = l_path;
     } 
        

}

void Bibliotheque::Ecriture_descripteurs(string const a_path){
    ofstream l_file_csv;

    //Permet d'ecrire dans une bibliothèque existant ou bibliothèque nouvelle
    l_file_csv.open(a_path);

    //Première ligne du fichier csv qui correspond au descripteur
    l_file_csv<<"Acces,Chemin,Titre,Cout,Source,Numero,Largeur,Hauteur";
    
    for(auto& row :bibliotheque){

        l_file_csv <<endl<<row.getAcces() << "," << row.getChemin()<<","<< row.getTitre() << ","
        << row.getCout() << "," << row.getSource() << "," << row.getNumero() << ","
        << row.getLargeur()<<","<<row.getHauteur();
    }

    l_file_csv.close();

}

void Bibliotheque::AfficherCout(){
    // demander le numero d'image que l'utilisateur il veut afficher son prix
    int l_Numero_ligne;
    int l_size_biblio;

    cout << "Entrer numero d'image que tu veux afficher son prix : ";

    l_size_biblio = int(bibliotheque.size());
    while(!(cin>>l_Numero_ligne)||(l_Numero_ligne<=0)||(l_Numero_ligne>l_size_biblio)) {
        cout << "Veuillez entrer un numero d'image valide: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

               cout << "Image " << l_Numero_ligne << " : " << bibliotheque[l_Numero_ligne-1].getCout() << endl;
}

void Bibliotheque::Supprimer() {
    // demander a l'utilisateur le numero de ligne qu'il vaut supprimer
    int l_Numero_ligne;
    int l_size_biblio;
    vector <Descripteurs> test ;
    
    l_size_biblio = int(bibliotheque.size());
    cout<<"Veuillez entrer le numero a supprimer"<<endl;
    
    while(!(cin>>l_Numero_ligne)||(l_Numero_ligne<=0)||(l_Numero_ligne>l_size_biblio)) {
        cout << "Veuillez entrer un numero d'image valide: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    
    // supprimer la ligne

    bibliotheque.erase(bibliotheque.begin() + l_Numero_ligne - 1);
    // Mise à jour des numero
    for(int i = l_Numero_ligne; i <=l_size_biblio;i++){
       bibliotheque[i-1].setNumero(to_string(i));
    }
     
}

void Bibliotheque::ModifierDescripteur() {
     int l_Numero_ligne;
     int l_size_biblio;
    
    l_size_biblio = bibliotheque.size();

    cout<< endl << "Entrer le numero d'image que tu veux modifier : ";
    while(!(cin>>l_Numero_ligne)||(l_Numero_ligne<=0)||(l_Numero_ligne>l_size_biblio)) {
        cout << "Veuillez entrer un numero d'image valide: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }


    bool isValid_reponse;
    string l_reponse; //Réponse au question de confirmation Y ou N posé
    
     string l_nouveux_titre;
     string l_nouveux_Source;
     string l_nouveux_acces;
     string l_nouveux_cout;
     string l_nouveux_numero;
     string l_nouveux_largeur;
     string l_nouveux_hauteur;

     Descripteurs selected_row = bibliotheque.at(l_Numero_ligne - 1);
     cin.ignore(numeric_limits<streamsize>::max(), '\n');
     do{
         cout << "Enter un titre : ";
         getline(cin,l_nouveux_titre);
         bibliotheque[l_Numero_ligne - 1].setTitre(l_nouveux_titre);

         cout << "Enter une Source : ";
         getline(cin,l_nouveux_Source);
        bibliotheque[l_Numero_ligne - 1].setSource(l_nouveux_Source);


        cout << "Enter un Acces : ";
        getline(cin,l_nouveux_acces);
        bibliotheque[l_Numero_ligne - 1].setAcces(l_nouveux_acces);

        cout << "Enter un cout : ";
        getline(cin,l_nouveux_cout);
        bibliotheque[l_Numero_ligne - 1].setCout(l_nouveux_cout);

        cout << "Enter un Numero : ";
        getline(cin,l_nouveux_numero);
        bibliotheque[l_Numero_ligne - 1].setNumero(l_nouveux_numero);

        cout << "Enter  Largeur  d'image : ";
        getline(cin,l_nouveux_largeur);
        bibliotheque[l_Numero_ligne - 1].setLargeur(l_nouveux_largeur);

        cout << "Enter  Hauteur  d'image : ";
        getline(cin,l_nouveux_hauteur);
        bibliotheque[l_Numero_ligne - 1].setHauteur(l_nouveux_hauteur);

        
        AfficherDescripteurs(l_Numero_ligne);
        
        isValid_reponse = false;
        
        while (!isValid_reponse) {
                cout << "Etes vous satisfait de votre modification ? Y or N ?" << endl ;;
                cin >> l_reponse;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (l_reponse == "Y" || l_reponse == "N") {
                    isValid_reponse = true;
                } 
                else {
                    cout << "Acces non valide. Veuillez saisir Y ou N." <<endl;
                    cin.clear();
                }
            }

            if(l_reponse == "N"){
                //Nous revenous au début de la methode et on recommence la procédure
                isValid_reponse = false;
            }
     }while(!isValid_reponse);
    


 }

 void Bibliotheque::Selection_Image() {
    int l_Numero_ligne;
    int l_size_biblio;
    cout<< endl << "Enter le rang de l'image sur laquelle vous voulez appliquer des traitements : "<<endl;
    l_size_biblio = int(bibliotheque.size());
    
    
    while(!(cin>>l_Numero_ligne)||(l_Numero_ligne<=0)||(l_Numero_ligne>l_size_biblio)) {
        cout << "Veuillez entrer un numero d'image valide: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    p_choice_Image = l_Numero_ligne;
 }