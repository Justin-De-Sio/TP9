/**
 *@file main.cpp
 * @author M. De Sio
 * @date 01/06/2021
 * @brief Partie d'echec
 */
#include <iostream>
#include <vector>
#include <string>

using namespace std;


namespace  {
    enum    Couleur{KNoir, KBlanc};
    enum    Piece_t{KReine,KRoi,KFoue,KPion,KTour};

    class Piece;
    class Case;
    class Echiquier;
    class Joueur;


    typedef  vector<Piece*> VPiece;
    typedef  vector<Case> CVcase;
    typedef  vector<CVcase> CMatCase;



    class Echiquier{
    private:
        vector<vector<Case>> myPlateau;
        VPiece myPiece;
    public:
        Echiquier(void);
        VPiece getPieces(const Couleur & couleur) const;
        Case * getCase(unsigned ligne, unsigned colonne);
    }; // Echiquier

    class Joueur{
        VPiece myPiece;
        Echiquier * myEchiquier;
        string myNom;
    public:
        Joueur(const string & nom, const VPiece & piece, Echiquier * echiquier);
        Piece * choisirPiece(void);
        void jouer(Piece * piece);
    }; // Joueur

    class Partie{
    private:
        Echiquier * myEchiquier;
        vector <Joueur * > myJoueurs;
    public:
        Partie(Joueur * joueur1, Joueur * joueur2, Echiquier * echiquier);
    }; // Partie

    class Case{
        unsigned myLigne;
        unsigned myColonne;
        Piece * myPiece;

    public:
        Case(unsigned ligne, unsigned colonne, Piece * piece = nullptr);
        unsigned getLigne(void) const;
        unsigned getColonne(void) const;
        Piece * getPiece(void);
        void setPiece(Piece * );
        void setJoueur(Joueur * joueur);
    };

    class Piece{
        Case * myCase;
        Joueur * myJoueur;
    protected:
        Couleur myCouleur;
        Piece_t myNom;
    public:
        Piece(const Couleur couleur, const Piece_t nom, Case * myCase = nullptr, Joueur * joueur = nullptr);
        void move(Piece * piece, Case * uneCase);
        virtual bool operator() (Case * uneCase) const;
        virtual ~Piece (void){}
        Couleur getCouleur (void) const;
        Piece_t getNom(void) const ;
        Joueur * getJoueur(void) const;
        Case * getCase(void) const;
        void setCase(Case * uneCase);

    };

   class Roi : public Piece{
   public:
        Roi (const Couleur couleur, const Piece_t nom, Case * myCase = nullptr, Joueur * joueur = nullptr);
   };

   VPiece Echiquier::getPieces(const Couleur &couleur) const
   {
       VPiece vPiece;
       vPiece.reserve(16);
       for(vector<Case> vCase : myPlateau){
           for(Case uneCase : vCase){
               if(uneCase.getPiece() != nullptr)
                   if(uneCase.getPiece()->getCouleur()==couleur)
                       vPiece.push_back(uneCase.getPiece());
        return vPiece;


           }
       }
   }

   Case *Echiquier::getCase(unsigned ligne, unsigned colonne)
   {
       return  &myPlateau [ligne][colonne];
   }


   Case::Case(unsigned ligne, unsigned colonne, Piece *piece) : myLigne(ligne), myColonne(colonne), myPiece(piece) {}


   Joueur::Joueur(const string &nom, const VPiece &pieces, Echiquier *Echiquier): myPiece(pieces), myNom(nom), myEchiquier(Echiquier){}

   void Joueur::jouer(Piece *piece){
       unsigned ligne;
       unsigned colonne;
       do{

           cout << "saisir la ligne et la colone du déplcament : " << endl ;
           cin >> ligne >> colonne;

       }while((*piece) (myEchiquier->getCase(ligne, colonne)));
       piece->move(piece,myEchiquier->getCase(ligne,colonne));

   }

   void Piece::move(Piece *piece, Case *uneCase)
   {
        piece->getCase()->setPiece(nullptr);
        uneCase->setPiece(piece);
        piece->setCase(uneCase);
   }

   Partie::Partie(Joueur *joueur1, Joueur *joueur2, Echiquier * echiquier) : myEchiquier {echiquier}, myJoueurs{joueur1,joueur2}
   {
       unsigned quiJoue(0);
       while (true) {
           Piece * piece ((myJoueurs [quiJoue]->choisirPiece()));
           (myJoueurs [quiJoue]->jouer(piece));
//           quiJoue = (quiJoue + 1) % 2;
           quiJoue = !quiJoue;


       }
   }
}




int main()
{
    Echiquier echiquier;

    Joueur jouer1("Justin",VPiece(),&echiquier);
    Joueur jouer2("TOTO",VPiece(),&echiquier);
    Partie partie(&jouer1, &jouer2, & echiquier);
    return 0;
}







