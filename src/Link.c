/*=============================================================*/
/*= E.Incerti (incerti@univ-eiffel.fr)                        =*/
/*= M2/IMAC3 - ANIMATION / MOTEUR PHYSIQUE                    =*/
/*= Système Masses/Ressort en dimension 1 : module liaison    =*/
/*=============================================================*/

#include <g3x.h>

#include <PMat.h>
#include <Link.h>



/*================================================*/
/*=      ALGORITHMES DES MODULES DE LIAISON      =*/
/*================================================*/



/*calcule distance*/
static double dist3D(PMat* M1,PMat* M2){
  double Xc,Yc,Zc;
  Xc = (M2->pos.x - M1->pos.x);
  Yc = (M2->pos.y - M1->pos.y);
  Zc = (M2->pos.z - M1->pos.z);
  double dist = sqrt(Xc*Xc + Yc*Yc + Zc*Zc); 
  return dist; 
}

static Vecteurs dist3D_vec(PMat* M1,PMat* M2){ 
  double Xc,Yc,Zc;
  Xc = M2->pos.x - M1->pos.x;
  Yc = M2->pos.y - M1->pos.y;
  Zc = M2->pos.z - M1->pos.z;
  Vecteurs dist;
  dist.x = Xc; dist.y = Yc; dist.z = Zc;
  return dist; 
}


/*! Algorithme Force Constante             !*/
/*  1 seul point mat. M1 ou M2, au choix... */
static void AlgoFrcConst(Link* L)
{
  /*gravité*/

  PMat* M=(L->M1?L->M1:L->M2);
  M->frc.y += L->frc.y;


  /*vent*/
  /*printf("time :%f",L->v.x);
  fflush(stdout);*/

  M->frc.x += L->v.x*cos(L->Fv.x * L->timer);

  M->frc.y += L->v.y*cos(L->Fv.y * L->timer);

  M->frc.z += L->v.z*cos(L->Fv.z * L->timer);

  /*printf("v.x :%f\n", L->v.x*cos(L->Fv.x * L->timer));
  printf("M->frc.x :%f\n\n", M->frc.x);

  fflush(stdout);*/


}   
 
/*! Algo. ressort de Hook (linéaire)                            !*/
/* produit une force : F=k*(d-l0).AB                             */
/* où (d-l0) est l'allongement et AB le vecteur inter particules */
static void AlgoRessort(Link* L)
{
  /*double d = L->M2->pos.y-L->M1->pos.y;*/
  /*double f;
  f = L->k*(d-L->l);
  */
  /*double d = dist3D(L->M1,L->M2);*/
  Vecteurs M1M2 = dist3D_vec(L->M1,L->M2);
  double d = sqrt(M1M2.x*M1M2.x + M1M2.y*M1M2.y + M1M2.z*M1M2.z );
  double amp = L->k*(1-L->l/d); 


  L->M1->frc.x += M1M2.x * amp;
  L->M2->frc.x -= M1M2.x * amp;

  L->M1->frc.y += M1M2.y * amp;
  L->M2->frc.y -= M1M2.y * amp;

  L->M1->frc.z += M1M2.z * amp;
  L->M2->frc.z -= M1M2.z * amp;
}
  
/*! Algo. frein cinétique                           !*/
/* produit une force : F=z*(V2-V1)                   */
/* où (V2-V1) est la vitesse relative des particules */
static void AlgoFrein(Link* L)
{
  Vecteurs f;
  f.x = L->z*(L->M2->vit.x-L->M1->vit.x);
  f.y = L->z*(L->M2->vit.y-L->M1->vit.y);
  f.z = L->z*(L->M2->vit.z-L->M1->vit.z);

  L->M1->frc.x += f.x;
  L->M2->frc.x -= f.x;

  L->M1->frc.y += f.y;
  L->M2->frc.y -= f.y;

  L->M1->frc.z += f.z;
  L->M2->frc.z -= f.z;
}

/*! Algo. ressort+frein         !*/
/*combine les 2 algos précédents */
static void AlgoRessortFrein(Link* L)
{ 
  /*double d = L->M2->pos.y-L->M1->pos.y;*/
  Vecteurs M1M2 = dist3D_vec(L->M1,L->M2);
  double d = sqrt(M1M2.x*M1M2.x + M1M2.y*M1M2.y + M1M2.z*M1M2.z );
  double amp = L->k*(1-L->l/d); 
  Vecteurs f;

  /*Version 2*/
  /*f.x = L->k*(d.x-L->lo.x)+L->z*(L->M2->vit.x-L->M1->vit.x);
  f.y = L->k*(d.y-L->lo.y)+L->z*(L->M2->vit.y-L->M1->vit.y);
  f.z = L->k*(d.z-L->lo.z)+L->z*(L->M2->vit.z-L->M1->vit.z);*/

  /*Version 1*/
  f.x = amp*M1M2.x + L->z*(L->M2->vit.x-L->M1->vit.x);
  f.y = amp*M1M2.y + L->z*(L->M2->vit.y-L->M1->vit.y);
  f.z = amp*M1M2.z + L->z*(L->M2->vit.z-L->M1->vit.z);

  L->M1->frc.x += f.x; 
  L->M2->frc.x -= f.x;

  L->M1->frc.y += f.y;
  L->M2->frc.y -= f.y;

  L->M1->frc.z += f.z;
  L->M2->frc.z -= f.z;

}  

/*! Algo. butée visco-élastique                    !*/
/*! active uniquement si dist. < seuil             !*/
/* comme précédemment mais avec un seuil d'activité */
static void AlgoRF_Butee(Link* L)
{ 
  double d = dist3D(L->M1,L->M2);
  /*double d = L->M2->pos.y-L->M1->pos.y;*/
  if (d>L->s) return;
  Vecteurs f;

  f.x = L->k*(d-L->l)+L->z*(L->M2->vit.x-L->M1->vit.x);
  f.y = L->k*(d-L->l)+L->z*(L->M2->vit.y-L->M1->vit.y);
  f.z = L->k*(d-L->l)+L->z*(L->M2->vit.z-L->M1->vit.z);

  L->M1->frc.x += f.x; 
  L->M2->frc.x -= f.x;

  L->M1->frc.y += f.y;
  L->M2->frc.y -= f.y;


  L->M1->frc.z += f.z;
  L->M2->frc.z -= f.z;
}  


/*! Algo. lien visco-élastique "cassable"          !*/
/*! si d>seuil, la liaison devient inactive        !*/
static void AlgoRF_CondPos(Link* L)
{ /* si la liaison est déjà cassée : rien */
  if (!L->on_off) return;

  /*double d = L->M2->pos.y-L->M1->pos.y;*/
  double d = dist3D(L->M1,L->M2);
  /* si l'allongement est trop fort : la liaison casse */
  if (d>L->s) { L->on_off=0; return; }
  Vecteurs f;
  f.x = L->k*(d-L->l)+L->z*(L->M2->vit.x-L->M1->vit.x);
  f.y = L->k*(d-L->l)+L->z*(L->M2->vit.y-L->M1->vit.y);
  f.z = L->k*(d-L->l)+L->z*(L->M2->vit.z-L->M1->vit.z);

  L->M1->frc.x += f.x; 
  L->M2->frc.x -= f.x;

  L->M1->frc.y += f.y;
  L->M2->frc.y -= f.y;


  L->M1->frc.z += f.z;
  L->M2->frc.z -= f.z;
}

/* quelques couleurs (cf. <g2x_Colors.h>) */
static G3Xcolor Lcols[8]={G3Xr,G3Xo,G3Xy,G3Xg,G3Xb,G3Xc,G3Xm,G3Xk};




/*///////////////////////Cylindre pris sur http://lifeofaprogrammergeek.blogspot.com/2008/07/rendering-cylinder-between-two-points.html///////////// */
static void renderCylinder(float x1, float y1, float z1, float x2,float y2, float z2, float radius,int subdivisions,GLUquadricObj *quadric)
{
  float vx = x2-x1;
  float vy = y2-y1;
  float vz = z2-z1;
  float v = sqrt( vx*vx + vy*vy + vz*vz );
  float ax;

  if (fabs(vz) < 1.0e-3) {
    ax = 57.2957795*acos( vx/v ); /*rotation angle in x-y plane*/
    if ( vy <= 0.0 )
      ax = -ax;
  }
  else {
    ax = 57.2957795*acos( vz/v ); /* rotation angle*/
    if ( vz <= 0.0 )
      ax = -ax;
  } 
  
  float rx = -vy*vz;
  float ry = vx*vz;
  
  glPushMatrix();
  /*draw the cylinder body*/
  glTranslatef( x1,y1,z1 );
  if (fabs(vz) < 1.0e-3) {
    glRotated(90.0, 0, 1, 0.0); /* Rotate & align with x axis*/
    glRotated(ax, -1.0, 0.0, 0.0); /* Rotate to point 2 in x-y plane*/
  }
  else {
    glRotated(ax, rx, ry, 0.0); /*Rotate about rotation vector*/
  }
  gluQuadricOrientation(quadric,GLU_OUTSIDE);
  gluCylinder(quadric, radius, radius, v, subdivisions, 1);

  /*draw the first cap*/
  gluQuadricOrientation(quadric,GLU_INSIDE);
  gluDisk( quadric, 0.0, radius, subdivisions, 1);
  glTranslatef( 0,0,v );

  /*draw the second cap*/
  gluQuadricOrientation(quadric,GLU_OUTSIDE);
  gluDisk( quadric, 0.0, radius, subdivisions, 1);
  glPopMatrix();
}

static void renderCylinder_convenient(float x1, float y1, float z1, float x2,float y2, float z2, float radius,int subdivisions)
{
  /*the same quadric can be re-used for drawing many cylinders*/
  GLUquadricObj *quadric=gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  renderCylinder(x1,y1,z1,x2,y2,z2,radius,subdivisions,quadric);
  gluDeleteQuadric(quadric);
}
/*//////////////////////////////////////////////////////////////////////////////*/
static double ambi = 0.2;
static double diff = 0.3;
static double spec = 0.4;
static double shin = 0.5;
extern void g3x_Line(double xa, double ya, double za,double xb, double yb, double zb, G3Xcolor col, int width)
{


  /*GLfloat sizes[2];  *//* Store supported line width range*/
  /*GLfloat step;     *//* Store supported line width increments*/
  /*Get supported line width range and step size*/
 /* glGetFloatv(GL_LINE_WIDTH_RANGE,sizes);
  glGetFloatv(GL_LINE_WIDTH_GRANULARITY,&step);*/
  /*printf("\nline width %f %f\n", sizes[0],sizes[1]);
  fflush(stdout);*/
  /*glLineWidth(width);*/
 /* glColor4fv(G3Xo); */
  g3x_Material(col,ambi,diff,spec,shin,1.);
  renderCylinder_convenient(xa,ya,za,xb,yb,zb,0.01,10);
  /*glBegin(GL_LINES);
    glVertex3d(xa,ya,za);
    glVertex3d(xb,yb,zb);
  glEnd();*/
  glLineWidth(1.); /* defaul value*/
}


static void DrawM1M2(Link* L)
{
    g3x_Line(L->M1->pos.x,L->M1->pos.y,L->M1->pos.z,L->M2->pos.x,L->M2->pos.y,L->M2->pos.z,L->color,L->M1->m);
}


static void DrawFrc(Link* L)
{
  PMat* M=(L->M1!=NULL?L->M1:L->M2);
  /*g2x_Line(M->x,M->pos,M->x,M->pos+0.001*L->frc,L->color,1);*/
  g3x_Line(M->pos.x,M->pos.y,M->pos.z,M->pos.x,M->pos.y+0.001*L->frc.y,M->pos.z,L->color,1);
}

/*================================================*/
/*= FONCTIONS DE CREATION DES MODULES DE LIAISON =*/
/*================================================*/

/*! Création d'un module Force Constante (exp. Gravité) !*/
/*Et intégration d'un modèle de vent*/
extern void FrcConst(Link* L, double force_const)
{
  L->type   = _FRC_CONST;
  /* paramètres pour le moteur physique */
  L->frc.y    = force_const; /*-> gravité force vertical constante*/
  L->frc.x = L->frc.z = 0;

  L->k      = 0.;
  L->z      = 0.; 
  L->s      = 0.;
  L->l      = 0.;
  L->lo.x = L->lo.y = L->lo.z = 0;

  L->on_off = true;
  L->setup  = &AlgoFrcConst;
  /* paramètres graphiques              */
  memcpy(L->color,Lcols[L->type] ,sizeof(G3Xcolor));
  L->draw   = &DrawFrc;
}

/*! Création d'un ressort linéaire (de Hook) !*/
extern void Ressort(Link* L, double k)
{
  L->type   = _RESSORT;
  /* paramètres pour le moteur physique */
  L->k      = k ;
  L->z      = 0.;
  L->s      = 0.;
  L->l      = 0.;
  L->lo.x = L->lo.y = L->lo.z = 0;
  L->on_off = true;
  L->setup  = &AlgoRessort;
  /* paramètres graphiques              */
  memcpy(L->color,Lcols[L->type] ,sizeof(G3Xcolor));
  L->draw   = &DrawM1M2;
}
  
/*! Création d'un frein cinétique linéaire !*/
extern void Frein(Link* L, double z)
{
  L->type   = _FREIN;
  /* paramètres pour le moteur physique */
  L->k      = 0.;
  L->z      = z ;
  L->s      = 0.;
  L->on_off = true;
  L->setup  = &AlgoFrein;
  /* paramètres graphiques              */
  memcpy(L->color,Lcols[L->type] ,sizeof(G3Xcolor));
  L->draw   = &DrawM1M2;
}

/*! Création d'un ressort+frein !*/
extern void RessortFrein(Link* L, double k, double z)
{
  L->type   = _RESSORT_FREIN;
  /* paramètres pour le moteur physique */
  L->k      = k ;
  L->z      = z ;
  L->s      = 0.;
  L->l      = 0.;
  L->lo.x = L->lo.y = L->lo.z = 0;
  L->on_off = true;
  L->setup  = &AlgoRessortFrein;
  /* paramètres graphiques              */
  memcpy(L->color,Lcols[L->type] ,sizeof(G3Xcolor));
  L->draw   = &DrawM1M2;

}

/*! Création d'une butée visco-élastique seuillée !*/
extern void RF_Butee(Link *L, double k, double z, double s)
{
  L->type   = _RF_BUTEE;
  /* paramètres pour le moteur physique */
  L->k      = k ;
  L->z      = z ;
  L->s      = s ; /* seuil de distance pour détachement   */
  L->l      = 0.;
  L->lo.x = L->lo.y = L->lo.z = 0;
  L->on_off = true;
  L->setup  = &AlgoRF_Butee;
  /* paramètres graphiques              */
  memcpy(L->color,Lcols[L->type] ,sizeof(G3Xcolor));
  L->draw   = &DrawM1M2;
}

         
/*! Création d'une liaison de rupture avec condition sur l'élongation !*/
extern void RF_CondPos(Link *L, double k, double z, double s)
{
  L->type   = _CONDIT_RF;
  /* paramètres pour le moteur physique */
  L->k      = k ;
  L->z      = z ; 
  L->s      = s ; /* seuil d'elongation pour rupture      */
  L->l      = 0.;
  L->on_off = true;
  L->setup  = &AlgoRF_CondPos; 
  /* paramètres graphiques              */
  memcpy(L->color,Lcols[L->type] ,sizeof(G3Xcolor));
  L->draw   = &DrawM1M2;
} 


/*! Connexion d'une Liaison entre 2 points Mat !*/
/* pas utilisé dans sytèmes de particules       */
/* ça sert surtout pour les topologies fixes    */
extern void Connect(PMat *M1, Link *L, PMat *M2)
{
  L->M1=M1;
  L->M2=M2;

  if(M1!=NULL && M2!=NULL){
    float amp = (M1->amp + M2->amp) /2;
    L->k = L->k*amp;
    L->z = L->z*amp;
    L->amp = amp;
  } else if(M1!=NULL && M2==NULL){
      float amp = M1->amp;
      L->k = L->k*amp;
      L->z = L->z*amp;
      L->amp = amp;
  } else if(M1==NULL && M2!=NULL){
      float amp = M2->amp;
      L->k = L->k*amp;
      L->z = L->z*amp;
      L->amp = amp;
  } 


  if (M1==NULL || M2==NULL) return;
 /* L->l = ; L->M2->pos - L->M1->pos*/
  L->l = dist3D(L->M1,L->M2);
  Vecteurs lvid = dist3D_vec(L->M1,L->M2);
  L->lo.x = lvid.x;
  L->lo.y = lvid.y;
  L->lo.z = lvid.z;

}
  