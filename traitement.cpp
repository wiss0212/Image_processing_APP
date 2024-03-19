#include "./../header/traitement.hpp"

Traitement::Traitement()
{

}

void Traitement::AfficherContenuImage(const Mat Image_In){
    Mat l_grayMat;

    cvtColor(getImage(),l_grayMat, CV_BGR2GRAY);

    //Affichage de l'image originale
    namedWindow("originale", WINDOW_AUTOSIZE);
	imshow("originale", l_grayMat);

    namedWindow("Image après Traitement", WINDOW_NORMAL);
    imshow("Image après Traitement", Image_In);
    //resizeWindow("dffd", 620, 620);  
    waitKey(0);
    destroyWindow("Image après Traitement");
}


void Traitement::TraitementImage(){
    string l_path;
    Mat l_Image;
    

    l_path = bibliotheque[p_choice_Image-1].getChemin();
    setAccesgetPathImage(l_path);

    l_Image = imread(getAccesgetPathImage(),IMREAD_COLOR);
    setImage(l_Image);
    


    Mat l_Image_Resultat;
    int l_choixTraitement;
    cout<<"Veuillez faire un choix de traitement"<<endl;

    while(!(cin>>l_choixTraitement)) {
            cout << "Veuillez entrer un numero d'image valide: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch (l_choixTraitement){
        case 1:
            /* Histogramme */
            Egalisation_histogramme();
            Sauvegarder();
            break;
        case 2:
            /* Gaussien */
            l_Image_Resultat = Gaussien();
            AfficherContenuImage(l_Image_Resultat);
            Sauvegarder();
            break;
        
        case 3:
            /* Moyenneur */
            l_Image_Resultat = Moyenneur();
            AfficherContenuImage(l_Image_Resultat);
            Sauvegarder();
            break;
        case 4:
            /* Median */
            l_Image_Resultat = Median();
            AfficherContenuImage(l_Image_Resultat);
            Sauvegarder();
            break;    
        
        case 5:
            /* Sobel */
            l_Image_Resultat = Sobel();
            AfficherContenuImage(l_Image_Resultat); 
            Sauvegarder();       
            break;
        case 6:
            /* Seuillage simple */
            l_Image_Resultat = Seuillage_simple();
            AfficherContenuImage(l_Image_Resultat);
            Sauvegarder();
            break;
        case 7:
            /* Segmentation */
            l_Image_Resultat = Segmentation();
            AfficherContenuImage(l_Image_Resultat);
            Sauvegarder();
            break;

        case 8:
            /* Rehaussement de Contours */
            l_Image_Resultat = RehaussementContour();
            AfficherContenuImage(l_Image_Resultat);
            Sauvegarder();
            break;

        default:
            cin.get();
            break;
        }

        
}


// Verifier la saturation
int Traitement::VerifierSaturation(const int valeur){
    if(valeur > 255){
        return 255 ;
    }else if(valeur < 0){
        return 0 ;
    }else{
        return valeur ;
    }
}

// Généré les filtres Moyenneur; gradient en x et y de Sobel
Mat Traitement::Filtre(const int typeFiltre){
    switch (typeFiltre){
    // Filtre moyenneur
    case 1 :
        return ((Mat_<double>(3,3) << 1, 1, 1, 1, 1, 1, 1, 1, 1)/9) ;
        break ;

    // Filtre gradient en x (Sobel)
    case 2 :
        return (Mat_<double>(3,3) << -1, -2, -1, 0, 0, 0, 1, 2, 1) ;
        break ;
    // Filtre gradient en y (Sobel)
    case 3 :
        return (Mat_<double>(3,3) << -1, 0, 1, -2, 0, 2, -1, 0, 1) ;
        break ;

    //Filtre Laplacien
    case 4 :
        return (Mat_<double>(3,3) << 0, 1,0, 1, -4, 1, 0, 1, 0) ;
        break ;

    default:
        return (Mat_<double>(3,3) << 0, 0, 0, 0, 1, 0, 0, 0, 0) ;
        break;
    }
}

// Convolution entre deux matrice
Mat Traitement::MatriceConvolution(const Mat Image_In, const Mat H){
    // Declaration des variables
    int ligne, colonne;                                  // Indices
    int L_image, C_image ;                                          // Dimensions de l'image
    int val ;                                                       // Variable intermediaire
    Mat Image_Out(Image_In.rows,Image_In.cols, CV_8U,double(0)) ;                           // Image resultante
    
    // Dimensions de l'image
    L_image = Image_In.rows ;                                 // Nombre de lignes
    C_image = Image_In.cols ;                                  // Nombre de colonnes
    
    // Produit de convolution
    for(ligne = 1 ; ligne < L_image; ligne++){                // Pour chaque ligne de l'image
        for(colonne = 1 ; colonne < C_image ; colonne++){      // Pour chaque colonne de l'image
            val = Image_In.at<unsigned char>(ligne-1,colonne-1) * H.at<double>(0,0) + Image_In.at<unsigned char>(ligne-1,colonne) * H.at<double>(1,0)
                + Image_In.at<unsigned char>(ligne-1,colonne+1) * H.at<double>(2,0) + Image_In.at<unsigned char>(ligne,colonne-1) * H.at<double>(0,1)
                + Image_In.at<unsigned char>(ligne,colonne) * H.at<double>(1,1) + Image_In.at<unsigned char>(ligne,colonne+1) * H.at<double>(2,1) 
                + Image_In.at<unsigned char>(ligne+1,colonne-1) * H.at<double>(0,2) + Image_In.at<unsigned char>(ligne+1,colonne) * H.at<double>(1,2)
                + Image_In.at<unsigned char>(ligne+1,colonne+1) * H.at<double>(2,2);
            Image_Out.at<unsigned char>(ligne, colonne) = VerifierSaturation(val) ;
            
        }
    }

    // Retour
    return Image_Out ;
}

//Calcul la norme de la matrice
Mat Traitement::norme_matriciel (const Mat Image, const Mat Image2){
    Mat Img_Out (Image.size(), CV_8U) ;                   // Image de résultat
    double X2,Y2;                                         //x² et Y²

    int ligne, colonne ;                                  // indice des lignes et des colonnes
    int L_image, C_image ;                                          // Dimensions de l'image
    // Dimensions de l'image
    L_image = Image.rows ;                                 // Nombre de lignes
    C_image = Image.cols ;                                  // Nombre de colonnes
 
 
    for(ligne = 0; ligne < L_image; ligne ++){
        for(colonne = 0; colonne<C_image; colonne++){
            //Calcul du produit de chaque pixel
            X2 = Image.at<unsigned char>(ligne,colonne) * Image.at<unsigned char>(ligne,colonne);
            Y2 = Image2.at<unsigned char>(ligne,colonne) * Image2.at<unsigned char>(ligne,colonne);

            // Calcul de la norme
            Img_Out.at<unsigned char>(ligne,colonne)= sqrt(X2 + Y2);
            }
        }
    return Img_Out;
}

// Seuillage simple    
Mat Traitement::Seuillage_simple(){
    
    const Mat l_Image_In = getImage();
    Mat l_grayMat;

    //Initialisation de la matrice résultat
    Mat l_Image_Out(l_Image_In.size(), CV_8U, double(0));
      
    int l_ligne,l_colonne;

    int l_seuil;
    cout << "Veuillez entrer la valeur du seuil" << endl;
    cin >> l_seuil; 
      
    // Conversion en niveau de gris de l'image d'origine
    cvtColor(l_Image_In,l_grayMat, CV_BGR2GRAY);

    for (l_ligne = 0; l_ligne< l_grayMat.rows ; l_ligne++) {
        for(l_colonne = 0; l_colonne < l_grayMat.cols; l_colonne++){
            if(l_grayMat.at<unsigned char>(l_ligne,l_colonne) > l_seuil){
              l_Image_Out.at<unsigned char>(l_ligne,l_colonne) = 255;
            }
            else{
               l_Image_Out.at<unsigned char>(l_ligne,l_colonne) = 0;
            }

      }

    }
    setImageTraite(l_Image_Out);
    return l_Image_Out;

}

//Detection de contours Sobel_x et Filtre
Mat Traitement::Sobel(){
    
    Mat l_Image_In = getImage();
    //Initialisation de la matrice résultat
    Mat l_Image_Out(l_Image_In.size(), CV_8U);
    Mat l_grayMat;    //Image en niveau de gris
    Mat l_gradientX;  // Gradient en x de Sobel
    Mat l_gradientY;  // Gradient en y de Sobel

    // Conversion en niveau de gris de l'image d'origine
    cvtColor(l_Image_In,l_grayMat, CV_BGR2GRAY);
     
    //   
    l_gradientX = MatriceConvolution(l_grayMat,Filtre(2));
    l_gradientY = MatriceConvolution(l_grayMat,Filtre(3));
      
    l_Image_Out = norme_matriciel (l_gradientX, l_gradientY);

  setImageTraite(l_Image_Out);  
  return l_Image_Out;
}

//Filtrage avec un filtre moyenneur
Mat Traitement::Moyenneur(){
    Mat l_Image_In = getImage();

    //Initialisation de la matrice résultat
    Mat l_Image_Out(l_Image_In.size(), CV_8U);
    Mat l_grayMat;    //Image en niveau de gris
      
    // Conversion en niveau de gris de l'image d'origine
    cvtColor(l_Image_In,l_grayMat, CV_BGR2GRAY);

    // Convolution entre l'image en niveau de gris et le filtre Moyenneur 
    l_Image_Out = MatriceConvolution(l_grayMat,Filtre(1));
      
     
  setImageTraite(l_Image_Out);  
  return l_Image_Out;

 
}

//Filtre median
Mat Traitement::Median(){
    
    Mat l_Image_In = getImage();
    Mat l_grayMat;
    int l_ligne, l_colonne; 
    //Initialisation de la matrice résultat
    Mat l_Image_Out(l_Image_In.size(), CV_8U,double (0));
          // Conversion en niveau de gris de l'image d'origine
      cvtColor(l_Image_In,l_grayMat, CV_BGR2GRAY);

    l_Image_Out = l_grayMat.clone();

    vector <double> l_fenetre;
    for ( l_ligne = 1; l_ligne < l_grayMat.rows; l_ligne++)
    {

        for ( l_colonne = 1; l_colonne < l_grayMat.cols; l_colonne++)

        {
            l_fenetre.push_back(l_grayMat.at<unsigned char>(l_ligne - 1, l_colonne - 1));
            l_fenetre.push_back(l_grayMat.at<unsigned char>(l_ligne, l_colonne - 1));
            l_fenetre.push_back(l_grayMat.at<unsigned char>(l_ligne + 1, l_colonne - 1));
            l_fenetre.push_back(l_grayMat.at<unsigned char>(l_ligne - 1, l_colonne));
            l_fenetre.push_back(l_grayMat.at<unsigned char>(l_ligne, l_colonne));
            l_fenetre.push_back(l_grayMat.at<unsigned char>(l_ligne + 1, l_colonne));
            l_fenetre.push_back(l_grayMat.at<unsigned char>(l_ligne - 1, l_colonne + 1));
            l_fenetre.push_back(l_grayMat.at<unsigned char>(l_ligne, l_colonne + 1));
            l_fenetre.push_back(l_grayMat.at<unsigned char>(l_ligne + 1, l_colonne + 1));
            
            //Ranger par ordre croissant
            sort(l_fenetre.begin(),l_fenetre.end());
            
            l_Image_Out.at<unsigned char>(l_ligne-1, l_colonne-1) = l_fenetre[4];

            // Supprimer le contenu du filtre
            l_fenetre.clear();
        }
    }
    setImageTraite(l_Image_Out);
    return l_Image_Out;
}

Mat Traitement::Gaussien(){

    //Initialisations 
    Mat l_Image_In = getImage();
    Mat blur(l_Image_In.size(), CV_8U,double (0));
    Mat diferen(l_Image_In.size(), CV_8U,double (0)); 
    Mat Image_Out(l_Image_In.size(), CV_8U,double (0));
    Mat grayMat;
    
    float gauss[25][25] = { 0 };
	int dim = 15;
	int x0 = dim / 2;
	int y0 = dim / 2;
	int sigma;
	float pi = 3.1416;
	float sumFiltr = 0;

    float sum2;
	int promo2;
    
    cvtColor(l_Image_In,grayMat, CV_BGR2GRAY);
    Image_Out = grayMat.clone();
   
    //Initialisation par l'utilisateur de sigma
    cout<<"Veuillez un valeur de sigma :" <<endl; 
    cin>>sigma;

    for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			int cX = i - x0;
			int cY = y0 - j;
			float up = (cX * cX) + (cY * cY);
			float down = 2 * (sigma * sigma);
			float exp1 = exp(-(up) / (down));
			float constant = 1.0 / (sigma * sigma * 2 * pi);
			gauss[i][j] = constant * exp1;
			sumFiltr += constant * exp1;
		}
	}

    for (int i = 0; i < grayMat.rows; i++)
	{
		for (int j = 0; j < grayMat.cols; j++)
		{
			sum2 = 0;
			promo2 = 0;
			int y2 = 0;
			for (int a = -(dim / 2); a <= dim / 2; a++)
			{
				int x2 = 0;
				for (int b = -(dim / 2); b <= dim / 2; b++)
				{
					////// suma
					if ((i + a) >= 0 &&
						(i + a) < grayMat.rows &&
						(j + b) >= 0 &&
						(j + b) < grayMat.cols)
					{
						sum2 += int(grayMat.at<unsigned char>(i + a, j + b)) * gauss[y2][x2];
					}
					x2++;
				}
				y2++;
			}
			promo2 = int(sum2 / sumFiltr);
			Image_Out.at<unsigned char>(i, j) = promo2;
		}
    }
    setImageTraite(Image_Out);
    return Image_Out;
}

void Traitement::Egalisation_histogramme(){
    //initialisation des tableaux pour stockage  
	int arr[256] = { 0 };
	float arr2[256] = { 0 };
	float arr3[256] = { 0 };
    Mat l_Image_In = getImage();
    Mat l_Image_Out(l_Image_In.size(), CV_8U,double (0));
    Mat grayMat;

    cvtColor(l_Image_In,grayMat, CV_BGR2GRAY);
    l_Image_Out = grayMat.clone();

	for (int i = 0; i < grayMat.rows; i++) {
		for (int j = 0; j < grayMat.cols; j++) {
			int index = (int)(grayMat.at<unsigned char>(i, j));
			arr[index]++;
		}
	}

	int max = 0;

	for (int i = 0; i < 255; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}


	//int height = grayMat.rows;
	//int width = grayMat.cols;

	Mat hist(1000, 1000, CV_8U, Scalar(0));

	int inc = 1000 / 256;


	// calculer l'histogramme de l'image originale 
	for (int i = 0; i < 255; i++) {
		rectangle(hist, Point(inc * i, hist.rows), Point((inc * (i + 1) - 1), hist.rows - ((arr[i] * hist.rows) / (max))), Scalar(255, 255, 255));

		
		float total = grayMat.cols * grayMat.rows;
		for (int i = 0; i < 255; i++)
		{
			arr2[i] = float(arr[i]) / total;
		}
		arr3[0] = arr2[0];

		
		for (int i = 1; i < 255; i++)
		{
			arr3[i] = arr2[i] + arr3[i - 1];
		}

		for (int i = 0; i < grayMat.rows; i++) {
			for (int j = 0; j < grayMat.cols; j++) {

				l_Image_Out.at<unsigned char>(i, j) = floor((256 - 1) * arr3[grayMat.at<unsigned char>(i, j)]);

			}
		}

		// egalisation d'image
		int h2[256] = { 0 };


		for (int i = 0; i < l_Image_Out.rows; i++) {
			for (int j = 0; j < l_Image_Out.cols; j++) {
				int index = (int)(l_Image_Out.at<unsigned char>(i, j));
				h2[index]++;
			}
		}

		int maxH2 = 0;

		for (int i = 0; i < 255; i++) {
			if (h2[i] > maxH2) {
				maxH2 = h2[i];
			}
		}


		Mat hist2(1000, 1000, CV_8U, Scalar(0));

		inc = 1000 / 256;


		// calculer l'histogramme egaliser 
		for (int i = 0; i < 255; i++) {
			rectangle(hist2, Point(inc * i, hist2.rows), Point((inc * (i + 1) - 1), hist2.rows - ((h2[i] * hist2.rows) / (maxH2))), Scalar(255, 255, 255, 0));
		}

		namedWindow("Histogramme image Originale", WINDOW_NORMAL);
        resizeWindow("Histogramme image Originale", hist.rows/2, hist.cols);
        imshow("Histogramme image Originale", hist);

		
        namedWindow("Histogram Egaliser", WINDOW_NORMAL);
        resizeWindow("Histogram Egaliser", hist2.rows/2, hist2.cols);
        imshow("Histogram Egaliser", hist2);

        
        namedWindow("Image egaliser ", WINDOW_AUTOSIZE);
	    imshow("Image egaliser ", l_Image_Out);
        setImageTraite(l_Image_Out);
        

	}
    
    waitKey(0);

    destroyWindow("Histogramme image Originale");
    destroyWindow("Histogram Egaliser");
    destroyWindow("Image egaliser ");
        

}

Mat Traitement::Segmentation() 
{
    Mat image = getImage();

         // Convertir l'image en YUV
    Mat l_yuvImage;
    cvtColor(image, l_yuvImage, COLOR_BGR2YUV);

        // Définir les limites de la plage de couleurs à sélectionner
    int yMin = 0, yMax = 255;
    int uMin = 90, uMax = 140;
    int vMin = 90, vMax = 140;
    /*
    int yMin, yMax;
    int uMin, uMax;
    int vMin, vMax;

    cout<<"entrez la valeur de yMin :"<<endl;
    cin >> yMin;
    cout<<"entrez la valeur de yMax :"<<endl;
    cin >> yMax;

    cout<<"entrez la valeur de uMin :"<<endl;
    cin >> uMin;
    cout<<"entrez la valeur de uMax :"<<endl;
    cin >> uMax;

    cout<<"entrez la valeur de vMin :"<<endl;
    cin >> vMin;
    cout<<"entrez la valeur de vMax :"<<endl;
    cin >> vMax;
*/
    Mat l_segmentedImage = Mat::zeros(image.size(), image.type());
    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            //décomposition des composante couleur
            int yValue = l_yuvImage.at<cv::Vec3b>(y, x)[0];
            int uValue = l_yuvImage.at<cv::Vec3b>(y, x)[1];
            int vValue = l_yuvImage.at<cv::Vec3b>(y, x)[2];

            if (yValue >= yMin && yValue <= yMax && uValue >= uMin && uValue <= uMax && vValue >= vMin && vValue <= vMax) {
                l_segmentedImage.at<cv::Vec3b>(y, x) = image.at<cv::Vec3b>(y, x);
            }
        }
    }

    setImageTraite(l_segmentedImage);
    return l_segmentedImage;
}


Mat Traitement::RehaussementContour() 
{
    Mat l_Image_In = getImage();
    Mat l_Image_Out;
    Mat l_Image_laplacien;
    Mat l_grayMat;
    
    cvtColor(l_Image_In,l_grayMat, CV_BGR2GRAY);

    l_Image_laplacien = MatriceConvolution(l_grayMat,Filtre(4));

    l_Image_Out = Mat::zeros(l_grayMat.size(), l_grayMat.type());
    for (int i = 0; i < l_Image_laplacien.rows; i++) {
		for (int j = 0; j < l_Image_laplacien.cols; j++) {

				l_Image_Out.at<unsigned char>(i, j) = VerifierSaturation((int) l_grayMat.at<unsigned char>(i, j) - l_Image_laplacien.at<unsigned char>(i, j));

			}
		}
    setImageTraite(l_Image_Out);
    return l_Image_Out;
    
}



bool Traitement::recherche_extension(const string& a_Image_name, const string& a_ext) {
    return a_Image_name.length() >= a_ext.length() &&
           a_Image_name.compare(a_Image_name.length() - a_ext.length(), a_ext.length(), a_ext) == 0;
}

void Traitement::Sauvegarder(){
    
    bool l_found = false;
    bool l_exist;
    string l_Image_name;
    string l_path;
    vector <string> extensions = {"jpeg", "jpg", "JPEG","JPG", "png", "PNG"};
    

                bool isValid_reponse1 = false;
            

    string l_reponse1; //Réponse au question de confirmation Y ou N posé
            while (!isValid_reponse1) {
                cout << "Vous voulez enregister votre traitement Y ou N" << endl ;;
                cin >> l_reponse1;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (l_reponse1 == "Y" || l_reponse1 == "N") {
                    isValid_reponse1 = true;
                } 
                else {
                    std::cout << "Acces non valide. Veuillez saisir Y ou N." <<endl;
                    cin.clear();
                }
    }


    if(l_reponse1== "Y"){

            // Vérification de la présence d'une extension
        do{
            int i = 0;
            cout << "Veuillez saisir un nom pour enregister l'image : " << endl ;
            cin >> l_Image_name ;
            // Vérification de la présence d'une extension
            while (i < int(extensions.size()) && !l_found) {

                if (recherche_extension(l_Image_name, extensions[i])) {
                    l_found = true;
                }
                i++;
            }

            if (l_found) {
            cout << "Extension de l image valide" << endl;
            } 
            else {
                cout << "Veuillez saisir une extension d image valide avec le nom" << endl;
            }
        }while(!l_found);



        l_path = "./Data/Image/" +l_Image_name;

        l_exist = experimental::filesystem::exists(l_path) ;
        
        if(l_exist){
            

            /*  "isValid_reponse" qui est initialisé à false. La boucle while va continuer
            tant que la saisie n'est pas valide (isValid_reponse = false).
            Si la saisie est valide, isValid_reponse est mis à true et la boucle s'arrête.
            */
            bool isValid_reponse = false;
            

            string l_reponse; //Réponse au question de confirmation Y ou N posé
            while (!isValid_reponse) {
                cout << l_Image_name <<" existe deja. Voulez-vous le remplacez ? Y ou N" << endl ;;
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
                setImage(getImageTraite());
                imwrite(l_path, getImageTraite());
            }
        }
        else{
            imwrite(l_path, getImageTraite());
            Ajouter_image();
        }
    
    } 
    else{
        setImageTraite(getImage());
    }
    cout << "Tapez sur la touche Entree pour sortir des traitement...";
    //cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
    cin.get();
       
}