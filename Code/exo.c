#include <stdio.h>
#include "exo.h"
/**
 *\ file exo.c
 *\ brief gère le stock d'une entreprise
 *\ author Dorian Hodin & Raphael Lacote
 *\ date 12 novembre 2021
 * Ce programme gère le stock d'une entreprise qui est représenté par le fichier Stock.don
 * Cette gestion de stock ce fait à travers plusieurs option tel que
 * le traitement d'une commande, l'état du stock, le récapitulatif des ventes...
 */

/**
 *\ brief affiche un menu permettant à l'utilisateur de choisir l'option souhaité
 *\ return 0 si la programme a fonctionné
 */
int global(void){
	int choix;
	printf("Que souhaitez faire?");
	while (choix!=6){
		printf("\n\n");
		printf("0- Etat du Stock\n1- Traitement d'une commande\n2- Produits en risque de rupture\n3- Récapitulatif des ventes\n4- Devis d'une commande\n5- Approvisionnement\n6- Sortir du programme\n");
		scanf("%d",&choix);
		if (choix==5){
			if (securite()==0){
				SaisieLivraison();
			}
		}
		if (choix==1){
			SaisieCommande();
		}
			
		if (choix==0){
			stock();
		}
		if (choix==3){
			recapitulatif();
		}
		if (choix==4){
			devis();
		}
		if (choix==2){
			rupture();
		}
	
	}
	return 0;
}
/**
 *\ brief vérifie si le mot de passe est correcte(ici le mot de passe est 123456)
 *\ return 0 si le mot de passe tapé par l'utilisateur est bon
 *\ return 1 si le mot de passe tapé par l'utilisateur est mauvais
 */

int securite(void){
	int taper;
	printf("Taper le mot de passe");
	scanf("%d",&taper);
	if (taper==123456){
		printf("Mot de passe correct\n");
		return 0;
	}
	else{
		printf("Mot de passe invalide\n");
		return 1;
	}
}

/**
 *\ brief affiche le stock de l'entreprise (présent dans le fichier Stock.don)
 *\ return 0 si la fonction a fonctionné correctement
 */

int stock(void){
	FILE *f;
	int stock[4][100],nom,qte,secu,i=0,cont=0,prix;
	f=fopen("Stock.don","r");
	if (f==NULL) return -1;
	while (feof(f)==0){
		fscanf(f,"%d, %d, %d, %d",&nom,&qte,&prix,&secu);
		stock[0][i]=nom;
		stock[1][i]=qte;
		stock[2][i]=prix;
		stock[3][i]=secu;
		i=i+1;
	}
	fclose(f);
	printf("Référence du produit:    Quantité:   Prix Unitaire:    Seuil de Sécurité:\n");
	cont=i-1;
	for (i=0;i<cont;i=i+1){
		printf("   %d                        %d              %d                 %d\n",stock[0][i],stock[1][i],stock[2][i],stock[3][i]);
	}
	return 0;
}

/**
 *\ brief affiche des produits risquant d'etre en rupture de stock
 * ou vérifie si un produit est proche de la rupture après avoir demandé
 * à l'utilisateur quel option choisir
 *\ return 0 si la fonction a fonctionné
 */


int rupture(void){
	FILE *f;
	int stock[4][100],nom,qte,secu,i=0,cont=0,prix,num,choix,test=0;
	f=fopen("Stock.don","r");
	if (f==NULL) return -1;
	while (feof(f)==0){
		fscanf(f,"%d, %d, %d, %d",&nom,&qte,&prix,&secu);
		stock[0][i]=nom;
		stock[1][i]=qte;
		stock[2][i]=prix;
		stock[3][i]=secu;
		i=i+1;
		}
		printf("Tapez 1 si vous souhaitez voir tout les produits proche de la rupture de stock, tapez 2 pour voir l'état pour un seul produit:\n");
		scanf("%d",&choix);
		if (choix==2){
			printf("Donnez le numéro du produit dont vous souhaitez verifier l'etat du stock:\n");
			scanf("%d",&num);
			cont=i;
			for (i=0;i<cont;i=i+1){
				if (stock[0][i]==num){
					if (stock[3][i]>=stock[1][i]){
						printf("Ce produit est bientôt en rupture de stock, il reste seulement %d exemplaire(s) de ce produit.\n",stock[1][i]);
						return 0;
					}else{
						printf("Ce produit n'est pas encore proche de la rupture de stock, il reste %d exemplaires de ce produit\n",stock[1][i]);
						return 0;
					}
				}
			}
		}else if (choix==1){
			cont=i;
			for (i=0;i<cont;i=i+1){
				if (stock[3][i]>=stock[1][i]){
					printf("Le produit %d est bientôt en rupture de stock, il reste seulement %d exemplaire(s) de ce produit.\n",stock[0][i],stock[1][i]);
					test=test+1;
				}
			}
			if (test==0){
				printf("Aucun produit est proche de la rupture de stock.");
			}
		}
		return 0;
	}

/**
 *\ brief effectue la saisie d'un identifiant et d'une quantité de produit
 * lance la fonction VerifLivraison avec les valeurs saisi
 *\ return 0 si VerifLivraison retourne 0
 *\ return 1 sinon
 */

int SaisieLivraison(void){
	int nom,qte;
	printf("Précisez le numéro du produit que vous livrez et la quantité que vous apportez:\n");
	scanf("%d %d",&nom,&qte);
	if (VerifLivraison(nom,qte)==0){
		printf("Livraison effectué\n");
		return 0;
	}
	else
	{
		printf("Livraison non effectué\n");
		return 1;
	}
}

/**
 *\ brief calcule le nombre de lignes du fichier Stock.don
 * Lance ChgmtFichier si l'identifiant tapé par l'utilisateur est déja dans le fichier
 * Lance ChgmtFichierA sinon
 *\ param nomCommande un entier représentant l'identifiant de la livraison
 *  param qteCommande un entier représentant la quantité de la livraison
 *\ return 1 si ChgmtFichierA n'a pas retourné 0
 *\ return 0 sinon
 */

int VerifLivraison(int nomCommande,int qteCommande){
	FILE *f;
	int stock[4][100],nom,qte,secu,i=0,prix,taille;
	f=fopen("Stock.don","r");
	if (f==NULL) return -1;
	while (feof(f)==0){
		fscanf(f,"%d, %d, %d, %d",&nom,&qte,&prix,&secu);
		stock[0][i]=nom;
		stock[1][i]=qte;
		stock[2][i]=prix;
		stock[3][i]=secu;
		i=i+1;
	}
	fclose(f);
	taille=i;
	for (i=0;i<taille;i=i+1){
		if (stock[0][i]==nomCommande){
			ChgmtFichier(nomCommande,qteCommande,stock,taille);
			return 0;
		}
	}
	taille=taille+1;
	if (ChgmtFichierA(nomCommande,qteCommande,stock,taille)==0){
		return 0;
	}
	else{
		return 1;
	}
}

/**
 *\ brief effectue la saisie d'un identifiant et d'une quantité de produit
 * lance la fonction VerifCommande avec les valeurs saisi
 *\ return 0 si VerifCommande retourne 0
 *\ return 1 sinon
 */

int SaisieCommande(void){
	int nom,qte;
	printf("Précisez le nom de la commande et sa quantité:\n");
	scanf("%d %d",&nom,&qte);
	if (VerifCommande(nom,qte)==0){
		printf("Commande effectué\n");
		return 0;
	}
	return 1;
}

/**
 *\ brief calcule le nombre de lignes du fichier Stock.don
 * Lance ChgmtFichier avec un nombre négatif pour la quantité
 *\ param nomCommande un entier représentant l'identifiant de la commande
 *  param qteCommande un entier représentant la quantité de la commande
 *\ return 0 si la fonction a correctement fonctionné
 *\ return 1 sinon
 */

int VerifCommande(int nomLivraison,int qteLivraison){
	FILE *f;
	int stock[4][100],nom,qte,secu,i=0,prix,cont;
	f=fopen("Stock.don","r");
	if (f==NULL) return -1;
	while (feof(f)==0){
		fscanf(f,"%d, %d, %d, %d",&nom,&qte,&prix,&secu);
		stock[0][i]=nom;
		stock[1][i]=qte;
		stock[2][i]=prix;
		stock[3][i]=secu;
		i=i+1;	
	}
	fclose(f);
	cont=i;
	for (i=0;i<100;i=i+1){
		if (stock[0][i]==nomLivraison){
			if (stock[1][i]<qteLivraison){
				printf("Commande non effectué, manque de stock\n");
				return 1;
			}
			else{
				qteLivraison=qteLivraison-(qteLivraison*2);
				ChgmtFichier(nomLivraison,qteLivraison,stock,cont);
				return 0;
			}
		}
	}
	return 1;
}

/**
 *\ brief demander à l'utilisateur de rentrer un prix et un seuil de sécurité
 * Les écrires dans le fichier Stock.don
 *\ param indice un entier représentant l'identifiant de la livraison
 *\ param variation un entier représentant la quantité de la livraison
 *\ param tableau un tableau d'entier contenant les valeurs déja présente dans Stock.don
 *\ param taille un entier représentant le nombre de lignes dans le fichier Stock.don
 *\ return 1 si l'utilisateur a mal remplit le prix ou le seuil de sécurité
 *\ return 0 sinon
 */


int ChgmtFichierA(int indice,int variation, int tableau[4][100], int taille){
	FILE *f;
	int i,prix,secu;
	f=fopen("Stock.don","w");
	if (f==NULL) return -1;	
	for (i=0;i<taille-2;i++){
		fprintf(f,"%d,%d,%d,%d\n",tableau[0][i],tableau[1][i],tableau[2][i],tableau[3][i]);
	}
	printf("Ce produit est nouveau, veuillez rentrer son prix et son seuil de sécurité:\n");
	scanf("%d %d",&prix,&secu);
	if (prix>0){
		if (secu>0){
			tableau[0][taille]=indice;
			tableau[1][taille]=variation;
			tableau[2][taille]=prix;
			tableau[3][taille]=secu;
			fprintf(f,"%d,%d,%d,%d\n",tableau[0][taille],tableau[1][taille],tableau[2][taille],tableau[3][taille] );
			printf("Message bien recu\n");
		}
		else{
			printf("Numéro de securité incorrecte\n");
			return 1;
		}
	}
	else{
		printf("Le prix doit être au dessus de 0!!!\n");
		return 1;
	}
	fclose(f);
	return 0;
}

/**
 *\ brief écrire des modifications de la quantité d'un produit dans le fichier Stock.don
 *\ param indice un entier représentant l'identifiant du produit auquel une modification va etra apporté
 *\ param variation un entier représentant le changement de quantité du produit
 *\ param tableau un tableau d'entier contenant les valeurs déja présente dans Stock.don
 *\ param taille un entier représentant le nombre de lignes dans le fichier Stock.don
 *\ return 0 si la fonction a fonctionné
 */


int ChgmtFichier(int indice,int variation, int tableau[4][100], int taille){
	FILE *f;
	int i;
	f=fopen("Stock.don","w");
	if (f==NULL) return -1;
	tableau[1][indice-1]=tableau[1][indice-1]+variation;
	if (variation<0){
		ventes(tableau[0][indice-1],variation-variation*2,tableau[2][indice-1]);
	}
	for (i=0;i<taille-1;i++){
		fprintf(f,"%d,%d,%d,%d\n",tableau[0][i],tableau[1][i],tableau[2][i],tableau[3][i]);
	}
	printf("Message bien recu\n");
	fclose(f);
	return 0;
}

/**
 *\ brief affiche les valeurs présentes dans Ventes.don sous la forme d'une phrase
 *\ return 0 si la fonction a fonctionné
 */

int recapitulatif(){
	FILE *f;
	int a,b,c;
	f=fopen("Ventes.don","r");
	if (f==NULL) return -1;
	while (feof(f)==0){
		fscanf(f,"%d,%d,%d\n",&a,&b,&c);
		printf("Achat de %d produit ayant l'identifiant %d pour un prix total de %d\n",b,a,c);
	}
	fclose(f);
	return 0;
}

/**
 *\ brief ajoute une ligne à Ventes.don avec les valeurs de la dernière vente
 *\ param numVendu un entier représentant l'identifiant du produit vendu
 *\ param qteVendu un entier représentant la quantité du produit vendu
 *\ param prix un entier représentant l'argent apporté par la vente du produit
 *\ return 0 si la fonction a fonctionné
 */

int ventes(int numVendu,int qteVendu,int prix){
	FILE *f;
	prix=prix*qteVendu;
	f=fopen("Ventes.don","a");
	fprintf(f,"%d,%d,%d\n",numVendu,qteVendu,prix);
	fclose(f);
	ChgmtDevis(numVendu,qteVendu,prix);
	return 0;
}

/**
 *\ brief Met les valeurs de la dernière vente dans le fichier Devis.don
 *\ param numVendu un entier représentant l'identifiant du produit vendu
 *\ param qteVendu un entier représentant la quantité du produit vendu
 *\ param prix un entier représentant l'argent apporté par la vente du produit
 *\ return 0 si la fonction a fonctionné
 */

int ChgmtDevis(int numVendu,int qteVendu,int prix){
	FILE *f;
	f=fopen("Devis.don","w");
	fprintf(f,"%d,%d,%d\n",numVendu,qteVendu,prix);
	fclose(f);
	return 0;
}

/**
 *\ brief Affiche sous forme de phrase les valeurs présentes dans Devis.don
 *\ return 0 si la fonction a fonctionné
 */

int devis(){
	int a,b,c;
	FILE *f;
	f=fopen("Devis.don","r");
	if (f==NULL) return -1;
	while(feof(f)==0){
		fscanf(f,"%d,%d,%d",&a,&b,&c);
	}
	printf("Identifiant de la commande:%d\n",a);
	printf("Quantité du produit:%d\n",b);
	printf("Montant à payer:%d\n",c);
	fclose(f);
	return 0;
}
