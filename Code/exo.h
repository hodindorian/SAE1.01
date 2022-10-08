int TransfoTable();
int global();
int securite();
int SaisieCommande();
int VerifLivraison(int nomCommande,int qteCommande);
int SaisieLivraison();
int VerifCommande(int nomLivraison,int qteLivraison);
int ChgmtFichier(int indice,int variation, int tableau[4][100], int taille);
int stock();
int ChgmtFichierA(int indice,int variation, int tableau[4][100], int taille);
int recapitulatif();
int ventes(int numVendu,int qteVendu,int prix);
int devis();
int ChgmtDevis(int numVendu,int qteVendu,int prix);
int rupture();

/*
int chargement(int stock[][100]);
int affichage(int stock[][100]);
int creation(int stock[][100]);
*/