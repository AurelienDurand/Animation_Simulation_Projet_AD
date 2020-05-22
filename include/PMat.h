/*=============================================================*/
/*= E.Incerti (incerti@univ-eiffel.fr)                        =*/
/*= M2/IMAC3 - ANIMATION / MOTEUR PHYSIQUE                    =*/
/*= Système Masses/Ressort en dimension 1 : module matériel   =*/
/*=============================================================*/

#ifndef  _PMAT_
  #define _PMAT_
  
  #include <g3x.h>

  #define _POINTFIXE 0
  #define _PARTICULE 1


 
  typedef struct
  {
    double x,y,z;
  } Point, Vecteurs;


  typedef struct _pmat
  {
		int    type;     /* type pour usages divers            */     
    /*-----------------------------------------------------*/             
    double m, amp;        /* paramètre de masse  amp : amplitude introduite pour limiter l'effet super elastique"*/   
    Point pos;      /* position courante x y z                  */
    Vecteurs vit/*,vit_y*/;      /* vitesse  courante                  */
    Vecteurs frc/*,frc_y*/;      /* buffer de force                    */
    void (*setup)(struct _pmat*, double h); /* intégrateur */
    /*-----------------------------------------------------*/
    G3Xcolor col;   /* couleur RGBA (4 float)              */   
    
    void (*draw)(struct _pmat*);     /* fonction de dessin */     
  } PMat;
  
/*! Création d'une particule mobile !*/
  /* avec l'intégrateur LeapFrog */
  void MassLF(PMat* M, double x, double y,double z, double m, double amp);
  /* variante, avec l'intégrateur Euler Explicite */
  void MassEE(PMat* M, double x, double y,double z, double m, double amp);

/*! Création d'une masse fixe !*/
  void Fixe(PMat *M, double x, double y ,double z, double amp);

#endif
