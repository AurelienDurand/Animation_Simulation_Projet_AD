/*=============================================================*/
/*= E.Incerti (incerti@univ-eiffel.fr)                        =*/
/*= M2/IMAC3 - ANIMATION / MOTEUR PHYSIQUE                    =*/
/*= Système Masses/Ressort en dimension 1 : module matériel   =*/
/*=============================================================*/

#include <PMat.h>

/* paramètres de lumière/matière */
/*static G3Xcolor rouge  ={1.0,0.0,0.0};*/
/*static double rayon= 0.66;*/
/*static double alpha= 0.5;*/
static double ambi = 0.2;  
static double diff = 0.3;
static double spec = 0.4;   
static double shin = 0.5;
/*! Algorithme de la masse libre 2D (2° loi de Newton)    !*/
/*! intégration : leapfrog                                !*/
static void leapfrog(PMat* M, double h)
{	
  M->vit.x += h*M->frc.x/M->m;   /* 1° intégration : vitesse   V(n+1)=V(n)+h*F(n)/m - EXplicite */ 
  M->vit.y += h*M->frc.y/M->m;
  M->vit.z += h*M->frc.z/M->m;
 
  M->pos.x += h*M->vit.x;        /* 2° intégration : position  X(n+1)=X(n)+h*V(n+1) - IMplicite */
  M->pos.y += h*M->vit.y;
  M->pos.z += h*M->vit.z;

  M->frc.x = M->frc.y  = M->frc.z  = 0.;              /* on vide le buffer de force */ 



}
/*! intégration : Euler Explicite                           !*/
static void eulerexp(PMat* M, double h)
{	
  M->pos.x += h*M->vit.x;        /* 1° intégration : position  X(n+1)=X(n)+h*V(n)   - EXplicite */
  M->pos.y += h*M->vit.y;
  M->pos.z += h*M->vit.z;

  M->vit.x += h*M->frc.x/M->m;   /* 2° intégration : vitesse   V(n+1)=V(n)+h*F(n)/m - EXplicite */ 
  M->vit.y += h*M->frc.y/M->m;
  M->vit.z += h*M->frc.z/M->m;

  M->frc.x= M->frc.y = M->frc.z = 0.;              /* on vide le buffer de force */ 
}         
 
/*! Algorithme du point fixe (position constante)         !*/
static void pointfixe(PMat* M, double h)
{ /* ne fait rien, à part vider le buffer de force       */
  M->frc.x =  M->frc.y = M->frc.z = 0.; 
  /* ne sert que si on veut "figer" une particule mobile */
  M->vit.x = M->vit.y = M->vit.z = 0.;
}
/*
static void drawcirc(PMat *M)
{ */
/* rayon indexé sur la masse */
/*
  g2x_Circle(M->x,M->pos,0.2*M->m,M->col,2);
}

static void drawdot(PMat *M)
{ *//* rayon indexé sur la masse */
/*  g2x_FillCircle(M->x,M->pos,0.2*M->m,M->col);
}
*/


static void drawSphere(PMat *M)
{ 
  glPushMatrix();
/* rayon indexé sur la masse */
  glTranslatef(M->pos.x,M->pos.y,M->pos.z);
  g3x_Material(M->col,ambi,diff,spec,shin,1.);
 /* glutSolidSphere(0.2*M->m,40,40);*/
  glutSolidSphere(0.2*M->m,40,40);
  glPopMatrix();
}


/*! Création d'une masse libre !*/
/*  Création d'une particule libre : attribution des paramètres de position et masse (vitesse nulle)  */
/*  avec l'intégrateur LeapFrog */
extern void MassLF(PMat* M, double y, double x,double z, double m, double amp)
{
  M->type  = _PARTICULE;
  /* paramètres pour le moteur physique */
  M->pos.y   = y;
  M->pos.z = z;
  M->vit.x = M->vit.y = M->vit.z = 0.;
  M->frc.x = M->frc.y = M->frc.z = 0.;
 /* M->vit_y   = 0.;
  M->frc_y   = 0.;*/
  M->m     = m;
  M->amp = amp;
  M->setup = &leapfrog;
  /* paramètres graphiques */
  M->pos.x    = x;
  memcpy(M->col,G3Xg ,sizeof(G3Xcolor));
  M->draw  = &drawSphere;
}

/* variante, avec l'intégrateur Euler Explicite */
extern void MassEE(PMat* M, double y, double x,double z, double m, double amp)
{
  M->type  = _PARTICULE;
  /* paramètres pour le moteur physique */
  M->pos.y   = y;
  M->pos.z = z;
  M->vit.x = M->vit.y = M->vit.z = 0.;
  M->frc.x = M->frc.y = M->frc.z = 0.;
  M->m     = m;
  M->amp = amp;
  M->setup = &eulerexp;
  /* paramètres graphiques */ 
  M->pos.x    = x; 
  memcpy(M->col,G3Xg ,sizeof(G3Xcolor)); 
  M->draw  = &drawSphere;
} 
    
/*! Création d'une masse fixe !*/
extern void Fixe(PMat *M, double y, double x,double z, double amp)
{
  M->type  = _POINTFIXE;
  /* paramètres pour le moteur physique */
  M->pos.y  = y;
  M->pos.z = z;
  M->vit.x = M->vit.y = M->vit.z = 0.;
  M->frc.x = M->frc.y = M->frc.z = 0.;
  /*M->vit_y  = 0.;
  M->frc_y  = 0.;*/
  M->m    = 1.; /* juste pour le dessin */ 
  M->amp = amp;
  M->setup = &pointfixe;
  /* paramètres graphiques */
  M->pos.x    = x;
  memcpy(M->col,G3Xr ,sizeof(G3Xcolor));
  M->draw  = &drawSphere;
}

