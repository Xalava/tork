#include <iostream>
using namespace std;
#include "console_win.h"
#include <time.h>




#define ltab 85// taille  des tablox
#define ctab 85//Colonnes

#define neutre 128
#define QG 15
#define ville 35
#define mer 16
#define vide 32
#define soldat 1
#define nbjmax 4
#define latence 10
console con;


typedef enum {noir, bleu ,vert,bleuciel, rouge,violet ,marron 
,blanc ,gris ,bleub,vertb,bleucielb ,rougeb,violetb,jaune ,blancb,} couleur;

 

//les deux premieres ont une untilisation courante, cas ou on a plusieurs fois la meme structure de données,
//les deux autressimplifient léchange de variables entre le main et les fonction
typedef struct
      {                             
             char nom[20];
              int couleur;
              int nbcity;
              int nbunit;
			  
                 } Joueur; 

 typedef struct
 		 {	int nat;
 		 	char cont;
 		 	char occup ;
			} Case;                 
//fourni une position et une caractéristique
typedef struct
      {     
              int l;
              int c;
              int car;
                } Etat;

 typedef struct
 		 {	int lter;
 		 	int cter;
	 		int nbj;
	 		int toursmax;
	 		int city;
			} Options;
 
 
//citer ces tablaux ici permet d'éviter de les rappeler pour chaque fonction
Case tab[ltab][ctab];
 
 
 //pour pallier a une limite de consoleEcrire, n'afficher que les chaines, 
//et réunir en une meme fonction tout les parametres d'affichage
void consoleEcrireChar(console& con,char ch,int coul,int l,int c)
{
char buf[2];
consoleCouleur(con,coul);
     buf[0]=ch;buf[1]='\0';
       consoleEcrirePosition(con,buf,l,c);
     buf[0]='\0';
 
  } 
  
  
  
             
int leretourneur(int hauteur,int largeur)
{int c;

   for(c= 1; c < largeur;c++)
	{
	 	  int aleat=rand()%4;
	char ch;
	//on va afficher aléatoirement un des symboles utilisés dans le jeu
		 switch (aleat)
		 {
		 case 0:
		   	  ch=soldat;
   		      break;
   		 case 1	:
			  ch=ville;
			  break;
		case 2:
			  ch=QG;
		      break;
		case 3:
			  ch=2;
			  break;
	 		 }   
	
    
        consoleEcrireChar(con,ch,vertb,1,c);

	    
		 consoleEcrireChar(con,ch,rougeb,hauteur-3,c);
		 
	
         consoleAttente(con,latence*8);
         } 
         
return EXIT_SUCCESS;
}

//La fonction suivante affiche le caractère souhaité sur jusqu'a nblmax lignes sur lune largeur de 20, n fois

int AffichNum(char ch,int n,Etat  eAffich,int nblmax)
{int i,j,k,m,lignes=int(n/20)+1;
char buf[2];
consoleCouleur(con,eAffich.car);
    	
		buf[0]=ch;
       buf[1]='\0';
      for (j=0;j<lignes && j<nblmax;j++)
     {	
       
 	     
	   	  for (i=0;i<n-(j*20) && i<20;i++)
     	 	 {       
 	     	consoleEcrirePosition(con,buf,eAffich.l+j,eAffich.c+i);	
			       
      	    }   
      	    
	   }
	   eAffich.l=eAffich.l+j-1;
	if(n>=20*nblmax)//cas oule nombre de symboles a afficher est trop grand, on met un petit plus sur le coté
		{
 		buf[0]=	'+';
       buf[1]='\0';
 		n=40;
		consoleEcrirePosition(con,buf,eAffich.l,eAffich.c+19);
		
		}
	

       
	eAffich.l=eAffich.l+2;
        
     buf[0]='\0';
 return eAffich.l;
}
//-----------------------------------------------------------------------
// FONCTIONS D'INITIALISATION

Options chOptions(int hauteur,int largeur)
{Options opt;
int taille,b;


	consoleCouleur(con,violetb);
	consoleEcrirePosition(con," Options",hauteur/4,largeur/4);
	consoleCouleur(con,gris);
	do
	{
    cout<<endl<<" * Nombre de joueurs?  ( 2 ou 4)"<<endl;
	opt.nbj=consoleAttenteTouche(con)-48;
    
	}
	while ((opt.nbj!=2)&&(opt.nbj!=4));
	cout<<opt.nbj<<endl;
	
	do
	{cout<<" * Taille de la carte?  (1=petite,2=moyenne,3=grande)"<<endl;//enum?
	taille=consoleAttenteTouche(con)-48;
   
       
	}
	while(taille!=1 &&taille !=2 && taille!=3);
	switch (taille)
		 {
		     case 1:
                  opt.lter=10;opt.cter=15;
                  cout<<"Petite"<<endl;
                  break;
 		    case 2:
                 opt.lter=20;opt.cter=30;
                 cout<<"Moyenne"<<endl;
                 break;
		   	case 3:
                   opt.lter=hauteur-2;opt.cter=largeur-25;
                     cout<<"Grande"<<endl;
                   break;
	
			}
	do
	{
     cout<<" * Nombre de tours maximum?  ( de 10 a 99)"<<endl;
	 opt.toursmax=(consoleAttenteTouche(con)-48);
	 cout<<opt.toursmax;
	 b=consoleAttenteTouche(con)-48;
	 cout<<b<<endl;
      opt.toursmax=b+opt.toursmax*10; 
	}
	while ((opt.toursmax<10)||(opt.toursmax>99));
	  
	
	do
	{cout<<" * Richesse de la carte en villes? ( de 0 a 9)"<<endl;
	opt.city=consoleAttenteTouche(con)-48;
    
	}
	while ((opt.city<0)||(opt.city>10));
		cout<<opt.city<<endl;
    	
	cout<<endl<<"     Validation..."<<endl;
	consoleAttente(con,latence*100);
	return opt;
}

	


void creationtab(Options opt,Joueur liste[])
{
	int l,c,aleat,tiersc=opt.cter/3,tiersl=opt.lter/3;
//initialisation du tableau
	for(l= 1; l <= opt.lter; l++)
		{
        for(c= 1; c <= opt.cter; c++)
			{
          tab[l][c].nat=neutre;
		  tab[l][c].cont=vide;
		  tab[l][c].occup=vide;
		
			      }
        }
        
   
// commun, quelque soit le nombre de joueur de la création de la carte        
  //création des mers
   for(l= 1;l <= opt.lter; l= l+1)
		{
        for(c= (tiersc-3); c <= (opt.cter-tiersc+4); c= c+1)
			{aleat=rand()%7;
			if (aleat==1)
            tab[l][c].nat=mer;
            }
  
  }
 

 
 switch (opt.nbj)//Apparaissent cici les diddérences en fonction du nombre de joueurs
 		{
		 case 2:
 			  //prérépartition du térrain
			 for(l= 1;l <= opt.lter; l= l+1)
			  	{
			        for(c=1 ; c <= tiersc; c= c+1)
						{tab[l][c].nat=liste[0].couleur;}
			         
			        for(c= opt.cter-tiersc+1; c <= opt.cter; c= c+1)
						{tab[l][c].nat=liste[1].couleur;}
			            
			     }
			
			
				//définit l'emplacement des QG     
			  
			  tab[opt.lter/2][1].cont=QG;
			  
			  tab[opt.lter/2][opt.cter].cont=QG;
		  break;
		  
		  case 4:
		  	   //création des mers supplémentaires
  			    for(l= tiersl-3; l <= opt.lter-tiersl+4; l++)
					{
      				  for(c= 1;c <= opt.cter; c++)
					  	{aleat=rand()%10;
							if (aleat==1)
          				  tab[l][c].nat=mer;
						}
            		  }
			
			//prérépartition du térrain
			 for(l=1 ; l <= tiersl; l= l+1)
			  	{
			        for(c=1 ; c <= tiersc; c= c+1)
						{tab[l][c].nat=liste[0].couleur;}
			         
			        for(c= opt.cter-tiersc+1; c <= opt.cter; c= c+1)
						{tab[l][c].nat=liste[1].couleur;}
			            
			     }
			for(l= opt.lter-tiersl+1; l <= opt.lter; l= l+1)
			  	{
			        for(c=1 ; c <= tiersc; c= c+1)
						{tab[l][c].nat=liste[2].couleur;}
						       
			        for(c= opt.cter-tiersc+1; c <= opt.cter; c= c+1)
						{tab[l][c].nat=liste[3].couleur;}
			            
			     }
			
				//définit l'emplacement des QG     
			  
			  tab[2][2].cont=QG;
			  tab[opt.lter][opt.cter].cont=QG;
			  tab[opt.lter][2].cont=QG;
			  tab[2][opt.cter].cont=QG;
			
			
		
			
			break;// ça sert a rien , mais c'est plus propre
			
			
		
		}
  
 //encore commun:création des villes
  for(l= 2;l <= opt.lter-1; l++)
		{
        for(c= 2; c <= opt.cter-1; c++)
			{aleat=rand()%100;
			if ((aleat<opt.city*2) && (tab[l][c].nat!=mer) && tab[l][c].cont!=QG)
               tab[l][c].cont=ville;
            }
  
  			}
return;
}


      
        

void AffichTab(Options opt)
{ int l,c;


	for(l= 1; l <= opt.lter; l++)
	{	for(c= 1; c <= opt.cter; c++)
			{ (tab[l][c].occup==vide)?/*si la case comporte une unité on affiche celle si 
            sinon on affche le contenu (ville ou qg le cas échéant de la carte)
            dans tout les cas un caractère est affiché pour permettre l'affichage de la couleur*/
                  	   
                consoleEcrireChar(con,(char)tab[l][c].cont,tab[l][c].nat,l,c):
			   	 consoleEcrireChar(con,(char)tab[l][c].occup,tab[l][c].nat,l,c);
	
         }
    }
}

Joueur creationjoueur(Joueur list[],int ordre)
{int i,k,touche=0;
bool dejapris;
 Joueur j;

consoleCouleur(con,blancb) ;


//tant qu'une couleur n'aura pas étée choisi ,
// par l'appui sur entree, les couleurs défileront a l'appui de la barre d'espace
j.couleur=0; 
cout<<endl<<endl;
	consoleEcrire(con,"  Choix de la couleur:");

consoleCouleur(con,gris) ;
cout<<endl;
     consoleEcrire(con,"appuyez sur espace pour faire défiler, et entrée pour valider");
     
cout<<endl<<endl;
do
{	 
		  for(i= 10; i < 16;i++)
			{
		 	dejapris=0;
			 	  
				   for (k=0;k<ordre;k++)//test sur tout les joueurs deja enregistré 
                   //pour éviter que deux joueurs aient la meme couleur
					 {
			   		   if (list[k].couleur==i*16)
			   		   dejapris=1;
					  }
			   	
				if (dejapris==0)   	   
			 	 {
					consoleCouleur(con, i*16);
				 	cout<<"Choisir?"<<endl;
			
					touche= consoleAttenteCodeTouche(con);
					while(touche!=VK_RETURN && touche!=VK_SPACE)
					touche= consoleAttenteCodeTouche(con);
					if (touche==VK_RETURN)
						{ 
                          j.couleur=i*16;
						  break;break;
                       }	 
					}
								
			}
}
while (j.couleur==0);
	
 consoleCouleur(con,j.couleur/16);
 cout<<endl<<"Nom du joueur ?"<<endl;   
 fgets (j.nom,19,stdin); 
 cout<<endl<<"Joueur pret"<<endl;

 j.nbcity=1;
 j.nbunit=0;
 return j;
 }
 
 
 //------------------------------------------------------------------------------
 //Voici maintenant les fonctions  de la séquence de jeu

//**********    SUPPORT  ********* ( ravitaillement des unités)

void initSupport(Joueur J,int lter,int cter)
{
     int l,c;
     for(l= 1; l <= lter; l++)
	{	for(c= 1; c <= cter; c++)
		{
               if (tab[l][c].nat==J.couleur)
		tab[l][c].nat=J.couleur-128;//toutes les cases du joueur son t obscurcies
                                    		
		
         }
    }
    
}   

void Support(Joueur J,int l,int c,int lter, int cter) 
{
 	 int a,b;
     tab[l][c].nat=J.couleur ;//et là pouf , elles sont ravitaillées

for(a= -1; a <= 1;a=a+2)
	{
		if ((tab[l+a][c].nat==J.couleur-128)&&(l+a!=0)&&(l+a!=lter+1))//on évite tout risque de sortir du tableau                                               
             Support(J,l+a,c,lter,cter);		
         
    }

for(b=-1; b <= 1;b=b+2)
    {
		if ((tab[l][c+b].nat==J.couleur-128)&&(c+b!=0)&&(c+b!=cter+1))//on évite tout risque de sortir du tableau                                               
 		 Support(J,l,c+b,lter,cter);		
         
    }
return;

}   

void testville(Joueur J,int lter,int cter)
{
     int l,c;
  for(l= 1; l <= lter; l++)
	{
         for(c= 1; c <= cter; c++)
		{
               if (tab[l][c].nat==J.couleur-128 || tab[l][c].nat==J.couleur)
                  {
                  if(tab[l][c].cont==ville || tab[l][c].cont==QG )   
                   Support(J,l,c,lter,cter);
                   }		
                   
                              
         }
    }
    return;
    
}

void endSupport(Joueur J,int lter,int cter)
{
    int l,c;
  for(l= 1; l <= lter; l++)
	{	for(c= 1; c <= cter; c++)
		{if (tab[l][c].nat==J.couleur-128)
		 {tab[l][c].nat=neutre;
		tab[l][c].occup=0;
        }
		
         }
    }
}


//****************** fin du SUPPORT ****************
 
int comptervilles(Joueur j,int lter ,int cter)
{int l,c;
     j.nbcity=0;
     
	 for(l= 1; l <= lter; l++)
	{	for(c= 1; c <= cter; c++)
		{if ((tab[l][c].nat==j.couleur)&&(tab[l][c].cont==ville))
		j.nbcity=1+j.nbcity;
         }
    }
    return j.nbcity;
} 
//------------------------------------------------------------------------------------------------------
//FONCTIONS DE LA BOUCLE D'ACTION 

int CalcCas(Etat e,int jcouleur)
{
	 if (jcouleur==tab[e.l][e.c].nat)
	 
	 return 0;
    if  (mer==(int)tab[e.l][e.c].nat)
         return 10;                       
	 else return 4
     +((int)tab[e.l][e.c].occup==soldat )*3
     -((int)tab[e.l][e.c].nat==neutre)*2
     +((int)tab[e.l][e.c].cont==ville)
     + ((int)tab[e.l][e.c].cont==QG)*2;
//cette formule (magique) nous évite une gigantesque cascade de structures conditionnnelles  

}	

 	
int CalcDiff(int cas)
{ 
  return cas*10;//retourne la le pourcentage a optenir pour capturer la case
}

Etat AffichErr(Etat eA,int erreur)
{
     consoleCouleur(con,eA.car);
switch (erreur)
       {
       case 0:
            eA.l=eA.l+1; 
            return eA;
            
       case 1:   
            consoleEcrirePosition(con,"Impossible            ",eA.l,eA.c);
            eA.l=eA.l+1; 
            return eA;
       case 2:
            consoleEcrirePosition(con,"Echec                  ",eA.l,eA.c);
            eA.l=eA.l+1;
               return eA;
       case 3:
            consoleEcrirePosition(con,"Tour1,pas de combat ",eA.l,eA.c);
            eA.l=eA.l+1; 
            return eA;   
       case 4:
            consoleEcrirePosition(con,"C'est déja a vous!    ",eA.l,eA.c);
            eA.l=eA.l+1; 
            return eA;            

       }
}

Etat AffichDiff(Etat eA,int diff)
{consoleCouleur(con,eA.car);
consoleEcrirePosition(con,"P=",eA.l,eA.c);
cout<<(100-diff);cout<<"% ";
           
eA.l=eA.l+1;
return eA;
}

//on va afficher les carctérisstiques du joueur, retourne la position du prochain affichage et sa couleur
Etat AffichStat(int tour,Joueur J,Etat eAffich)
{	
 	
 	 eAffich.car=J.couleur/16;
  	 consoleCouleur(con,eAffich.car);
  	 
  	 
  	 consoleEcrirePosition(con,"tour n° ",eAffich.l,eAffich.c);
  	 cout<<tour;
       eAffich.l=eAffich.l+1;
	 consoleEcrirePosition(con,J.nom,eAffich.l,eAffich.c);
eAffich.l=eAffich.l+1;
                                                            
	  consoleEcrirePosition(con,"Nombre de villes:",eAffich.l,eAffich.c);
eAffich.l=eAffich.l+1;
                      AffichNum(vide,150,eAffich,10);
					  eAffich.l=AffichNum(ville,J.nbcity,eAffich,2);

	  consoleEcrirePosition(con,"Unités en réserve:",eAffich.l,eAffich.c);
eAffich.l=eAffich.l+1;
					  eAffich.l=AffichNum(soldat,J.nbunit,eAffich,3);
   
	
	 return eAffich ;
	 }
 

Etat Deplacement(Etat position,int lter,int cter)
{
	int touche;//on tutilise une nouvelle variable pour la lisibilité
		touche=0;
	
	
	
		// afficher le curseur a la nouvelle position
	
        consoleCurseurPosition(con, position.l, position.c);

		// attendre que l'utilisateur appuye sur une fleche de direction ou sur returnou espace
		touche= consoleAttenteCodeTouche(con);
		while(touche!=VK_UP && touche!=VK_DOWN && touche!=VK_LEFT
		 && touche!=VK_RIGHT && touche!=VK_RETURN && touche!=VK_SPACE)
			touche= consoleAttenteCodeTouche(con);

		// deplacer la position du curseur selon la touche de direction
		switch(touche)
		{
			case VK_UP:	// ligne du dessus, si on est pas au bord
				if(position.l > 1)
				
                   position.l=position.l-1;
					else position.l=lter;//sinon on passe de l'autre coté!!!
                    
			break;
				
			case VK_DOWN:	// ligne du dessous, si possible
				
				if(position.l < lter)
					
                  position.l= position.l +1;
                  else position.l =1;//sinon on passe de l'autre coté!!!
                  
			break;

			case VK_LEFT:	// colonne a gauche, si possible
				if(position.c > 1)
				
                 position.c= position.c  -1;
                 else position.c=cter;
                 
			break;

			case VK_RIGHT:	// colonne a droite, si possible
				if(position.c < cter)
				
                  position.c= position.c +1;
                  else position.c=1;
			break;
		}


	// renvoyer la position a sonder
	
	position.car=touche;
	return position;
}

int action(int cas,int diff,Joueur& J,Etat ePosTouch,int tour)
{int l=ePosTouch.l,c=ePosTouch.c;
     int aleat;
      
if (tab[l][c].nat==J.couleur-128)//case du joueur non ravitaillée
   return 4;    
if (cas==10)//mer
	return 1;
//cas ou on est dans son propre camp 
if (cas==0)
    {
		if(tab[l][c].occup==soldat)
			{ 
   			    tab[l][c].occup=0;
                   J.nbunit=J.nbunit+1;
                   consoleEcrireChar(con,tab[l][c].cont,J.couleur,l,c);
                   consoleEcrireChar(con,vide,J.couleur,l,c);
					
			}
		else
			{
			 	if(J.nbunit>0)
				{    
                     tab[l][c].occup=1;
                     J.nbunit=J.nbunit-1;
                     consoleEcrireChar(con,tab[l][c].cont,J.couleur,l,c);
                     consoleEcrireChar(con,soldat,J.couleur,l,c);
				}
				else
				{
				return 2;
				}
				
			}
	return 0;		
	}
if (tour==1)
      return 3;	
//prise de case 
	
  aleat=rand()%100;  
 //test si on est dans une case adjacente a une case du joueur
if ( tab[l][c+1].nat==J.couleur || tab[l+1][c].nat==J.couleur 
 ||tab[l-1][c].nat==J.couleur ||tab[l][c-1].nat==J.couleur ) 
   {
    //Test de réussite
     if (aleat>diff )
    	{
    	tab[l][c].occup=1;
        tab[l][c].nat=J.couleur;
      
    				if((cas==9)||(cas==6))//prise de QG
    					{
    						consoleEffacer(con);
                            //cout<<(char)7<<endl;							
    						consoleEcrirePosition(con,"Victoire!!!",10,10);
    						consoleAttente(con,1000);
    					exit(0);
    	    			}
         J.nbcity=J.nbcity+(cas==3||cas==5||cas==8); //comme le LMD
         J.nbunit=J.nbunit-1; 
         consoleEcrireChar(con,tab[l][c].cont,J.couleur,l,c);   
         consoleEcrireChar(con,soldat,J.couleur,l,c);        
    	}		 
    	else 
    	{
    	return 2;
    	J.nbunit=J.nbunit-1;
    	} 
     }
     else 
     {
     return 1;
     }  
			
  return 0;//ça devrait jamais arriver
}	


//*********************************************************************************************************************************

int main(void)
{//déclaration-initialisation des variables
 	
	Joueur liste[nbjmax+1];
	
	   int i,tour,ordre,lter,cter,cas=0,diff=0,erreur;

	Etat ePosTouche,eAffich;
	Options opt;
 
  srand(time(NULL));
  //consoleInitialiser(con);
  	consoleInitialiserDimensions(con,51,80);
  	
	int largeur=con.nb_colonnes,hauteur=con.nb_lignes;
//------------------------------------------------------------------------------------------
//voici l'introduction
        consoleEcrirePosition(con ,"Appuyez sur alt+entree",1,20);
        consoleAttente(con,latence*100);
        consoleEffacer(con);

  	consoleCurseur(con, 0, FALSE); //on fait disparaitre le curseur , , c'est jamais joli
	  consoleEcrirePosition(con, "* TorK *",hauteur/3,int(largeur*0.45));
	    
	leretourneur(hauteur,largeur);//petite fonction d'affichage
	consoleAttente(con,latence*20);
	consoleEffacer(con);
//----------------------------------------------------------
//le choix des options, dans un menu indépendant , ce qui simplifie l'ajout de nouvelles 
	opt=chOptions(hauteur,largeur);
		
	lter=opt.lter; 
    cter=opt.cter;//très utiles ces deux variables sont isolées
    
	eAffich.c=cter+2;
	
//---------------------------------------------
//les joueurs sont stockés dans la liste, l'envoie de la liste permettrade vérifier qu'ils ne prennent pas les memes couleurs										   											   

	 	
   consoleEffacer(con);
    consoleCouleur(con,violetb) ;
    consoleEcrirePosition(con,"# Création des Joueurs #",5,20);
  for(i= 0; i < opt.nbj;i++)
	{
	 	  liste[i]=creationjoueur(liste,i);
 		  }
    cout<<endl<<"Validation..."<<endl;
   
	consoleAttente(con,latence*100);
//---------------------------------------
    consoleEffacer(con);
    creationtab(opt,liste);
    AffichTab(opt);
   
   
   
    
    consoleCurseur(con, 100,TRUE);//
//sequence de jeu

for(tour= 1;tour<=opt.toursmax ;tour++)
	{
 	for(ordre=0;ordre<opt.nbj ;ordre++)
		{
			
	
		//séquence support des cases
		 initSupport(liste[ordre],lter,cter);
      testville(liste[ordre],lter,cter);
	    
	     
	    
	    AffichTab(opt);
	     //on récupère le nombre de villes et d'unités
	     liste[ordre].nbcity=comptervilles(liste[ordre],lter,cter);
	    liste[ordre].nbunit=liste[ordre].nbunit+liste[ordre].nbcity/(opt.city/2)+1;
	    
	    
	    //on place le curseur au ccentre
	    ePosTouche.l=lter/2;
	    ePosTouche.c=cter/2;
	    //on affichele nom du joueur de sa couleur sur le oté
	    consoleCouleur(con,blancb);//liste[ordre].couleur/16);
	    consoleEcrirePosition(con,liste[ordre].nom,3,eAffich.c);
	    consoleEcrirePosition(con,"tour n°",4,eAffich.c);
	    cout<<tour<<"/"<<opt.toursmax<<endl;
	  	   	
	   //--------------------------------
	   // BOUCLE D'ACTION
	     do 
	     { 
	   		 eAffich.l=1;//on reprend l'affichage au début
	   		 consoleCurseur(con,100,TRUE);
	   		  erreur=0;
		     ePosTouche=Deplacement(ePosTouche,lter , cter);  
		     consoleCurseur(con,0,FALSE);
		     
			 cas=CalcCas(ePosTouche,liste[ordre].couleur);
			 
		     diff=CalcDiff(cas);
		     
		     eAffich=AffichDiff(eAffich,diff);//affiche la probabilité de réussir
		     //cas ou on a enfoncé la touche d'action
			
                      if (ePosTouche.car==VK_RETURN)
                      erreur=action(cas,diff,liste[ordre],ePosTouche,tour);
			     	      	 	 	      	 	
				
		   	
	    eAffich=AffichStat(tour,liste[ordre],eAffich);
	    eAffich.car=blancb;//change la couleur , pour la boucle suivante
	    eAffich=AffichErr(eAffich,erreur);
		 }
	      while(ePosTouche.car!=VK_SPACE);
		  testville(liste[ordre],lter,cter);
	    endSupport(liste[ordre],lter,cter);	        	
	     consoleEffacer(con);   
	   }
    }
    
  //cas ou le nombre de tour est épuisé sans qu'il y ai eu victoire
      consoleEffacer(con);
     cout<<(char)7<<endl;
     
     
      //On peut ici relancer compter ville pour donner un gangnat par défault
      cout<<"fin des tours, statu quo"<<endl;
      
      consoleAttente(con,10000);
     
      

    return EXIT_SUCCESS;
}
         
