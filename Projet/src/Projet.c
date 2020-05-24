/*=============================================================*/
/*= E.Incerti (incerti@univ-eiffel.fr)                        =*/
/*= M2/IMAC3 - ANIMATION / MOTEUR PHYSIQUE                    =*/
/*= Système Masses/Ressort en dimension 1 : Corde             =*/
/*= Modèle 2 : avec force extérieure ("gravité")              =*/
/*=============================================================*/

#include <g3x.h>

#include <PMat.h>
#include <Link.h>

/*#define _RESOLUTION 30*/
#define _DEPTHCAM 1300
#define _NBLIGNE 10
#define _NBPARTICULE_PL 15
#define _NBCOUCHE 1 /* 1 ou 2 */
/*! Paramètres de la fenetre graphique !*/
static int      pixwidth=1280,pixheight=1280;

/*static double   xmin=-_RESOLUTION,ymin=-_RESOLUTION,xmax=+_RESOLUTION,ymax=+_RESOLUTION;*/

/*! VARIABLES DE SIMULATION !*/
static int      Fe;        /* fréquence d'échantillonnage        */
static double   h;         /* pas d'échantillonnage 1./Fech      */
static int      Fa=1;      /* on affiche 1 echantillon sur Faff  */
static double   m,k,z,g,timer_v;   /* paramètres physiques               */
static double   tempo=0.02;/* temporisation de la simul          */ 

/*! systeme "Masses-Ressorts" : les particules et les liaisons !*/

static int      nbm;
static PMat    *TabM=NULL;
static int      nbl;
static Link    *TabL=NULL;

/*paramètre vent*/
static G3Xclock* clock=NULL;
static Vecteurs Fv={0.04,0.35,0.05} ,v = {4800,5700,1150}; 

/*=================================================================*/
/*= sic.                                                          =*/
/*=================================================================*/


void reset(void)
{	
  int i;
  double newy = 0 ;
  double newz = 0 ;
  double newx = 0 ;
  for (i=0;i<nbm;i++) {
    if(TabM[i].type != _POINTFIXE){
     TabM[i].vit.x=TabM[i].frc.x=0.;
     TabM[i].vit.y=TabM[i].frc.y=0.;
     TabM[i].vit.z=TabM[i].frc.z=0.;
     TabM[i].pos.y = newy;
     TabM[i].pos.z = newz;
     newx = newx + 1;
     TabM[i].pos.x = newx;
    } else {
      newx = TabM[i].pos.x;
      newy = TabM[i].pos.y; 
      newz = TabM[i].pos.z;

    }
  }
}


/*=-------------------------=*/
/*=  Constructon du modèle  =*/
/*=-------------------------=*/
bool Modeleur(void)
{
  /*! le Modèle : un tableau de particules, un tableau de liaisons !*/
  int nbligne = _NBLIGNE;             /* 9 particules et 2 points fixes     */
  int nbm_pL= _NBPARTICULE_PL; /*nbm_par_Ligne*/ 
  int nbl_td_tt=0, nbl_2D =0, nbl_3D=0; /* valeur pour connaitre le nombre de liaison avant d'introduire le tenseur de courbure*/
                            /* nbl_2D nombre liaison version 2D*/
                            /* nbl_3D nombre d'ajout de liaison version 3D % a la version 2D*/ 
 int nbl_3D_pL =0 ,nbl_3D_diag_pL =0 ; 

 int nbcouche = _NBCOUCHE;
 /*nbl_3D_pL ajout liaison 3D manquante cube par ligne*/
 /*nbl_3D_diag_pL ajout liaison 3D manquante diagonales cube par ligne*/
 nbm = nbm_pL*nbligne;

  /* 2eme rangé -> passage 3D*/
  nbm *= nbcouche; 

  if (!(TabM=(PMat*)calloc(nbm,sizeof(PMat)))) return false;

  int nbl_pL = (nbm_pL-1)+(nbm_pL-1);
  /*nbl = (nbm-1*nbligne)+(nbm-2*nbligne); *drapeau -> pour nb =11 sur une ligne*//* 10 ressorts-freins + 10 "gravités" : nbm-1 + nbm-2*/
  nbl = nbl_pL*nbligne;

  if(nbligne>1){
    /*ajout nb liason tenseur deformation */
    nbl = nbl + (nbm_pL)*(nbligne-1);
    /*printf("\nnbl= %d \n",nbl);
    fflush(stdout);*/

    /*ajout nb liason tenseur diagonale 2D*/
    if(nbcouche == 1){
      nbl = nbl + (nbm_pL-1)*(nbligne-1)*2 ;
    }


     /*ajout nb liason tenseur de courbure */
    nbl_td_tt = nbl;
    /*printf("\nnbl= %d \n",nbl);
    fflush(stdout);*/

    nbl = nbl + (nbm_pL-2)*nbligne + (nbligne-2)*(nbm_pL-1);/* ajout de toute les liaisons de courbure en enlevant la colone des points fixes*/



    if (nbcouche >1){
          /*passage 2D-> 3D */
      nbl_2D = nbl;
      nbl = nbl_2D*nbcouche;
      nbl_3D_pL = nbm_pL;
      nbl_3D_diag_pL = (nbm_pL-1)*4;   
      nbl_3D = nbligne*nbl_3D_pL + (nbligne-1)*nbl_3D_diag_pL ; /* liaison manquante cube + diag du cube */
      nbl = nbl + nbl_3D;
    }

    /*printf("\nnbl= %d \n",nbl);
    fflush(stdout);*/
  }
    printf("\nnombre de Particules = %d \n",nbm);
    printf("\nnombre de liaison = %d \n",nbl);
    fflush(stdout);

  if (!(TabL=(Link*)calloc(nbl,sizeof(Link)))) return false;


  /* printf("oui");
   fflush(stdout); */

  Fe = 1000;           /* paramètre du simulateur Fe=1/h                  */ 
  h = 1./Fe;
  m = 1.;            /* la plupart du temps, toutes les masses sont à 1 */
  /* avec les paramètres ci-dessous : limite de stabilité pour nbm = 11 */
  /* k = 0.866*SQR(Fe);*/ /* raideurs   -> à multiplier par mb*Fe²           */
  /* z = 0.08*Fe;*/       /* viscosirés -> à multiplier par mb*Fe            */
  k= 0.1*(m*Fe*Fe); /*raideur*/
  z = 0.01*(m*Fe); /*viscosité*/
  g = -5.*Fe;        /* la gravité : elle aussi à calibrer avec Fe      */

  timer_v = 0; /*timer pour le vent*/
  if (!(clock=(G3Xclock*)calloc(0,sizeof(G3Xclock)))) return false;
  /*memset(&clock,0,sizeof(G3Xclock));*/


  int j;
  double pfixe = (double)(nbm_pL-1)/2;
  int i;
    /*! les particules !*/
  int count = 0;
  int nbm2D = nbm /nbcouche, nbc = 0;  /*nbm2D -> nombre particule pour une face */
  for(nbc = 0; nbc< nbcouche; nbc++) {
    /*printf("\nbc = %d", nbc);
    fflush(stdout); */

    int nbl_loc = nbc * nbl_2D;
    int nbm_loc = nbc * nbm2D;

    /*printf("\n nbl_loc tot= %d  nbm_loc tot= %d\n", nbl_loc,nbm_loc);
    fflush(stdout); */

    for (j = 0 ; j < nbligne ; j ++) {

      PMat* M = TabM  + j*nbm_pL + nbm_loc;
     /* printf("j = %d", j);*/
    /*  printf("j = %lf", (double)j);
     fflush(stdout);*/ 
      Fixe(M++,j,-pfixe,nbc,1);

      for (i=1;i<nbm_pL;i++) {
        /*amp : amplitude introduite pour limiter l'effet super elastique"*/
        float amp =  1 + i*(-0.9)/(nbm_pL-1); 
        /*printf("i = %d , amp = %f",i,amp);
        fflush(stdout);*/
        /*y =y0 + (x-x0)*(y1-y0)/(x1-x0) avec 
          x0 = -pfixe y0 = 1 , 
          x1 = -pfixe + (nbm_pL -1) et y1 = 10,
          x = -pfixe + i */ 
        MassLF(M++,(double)j,-pfixe+i,nbc,m*amp,amp);
       /* Fixe(M++,(double)j,-pfixe+i);*/

      }

      /*Fixe(M++,j,+pfixe);*/
      /* Liaison par ligne */
    
      Link* L=TabL+j*nbl_pL + nbl_loc;

      for (i=0;i<nbm_pL-1;i++) RessortFrein(L++,k,z);
      for (i=0;i<nbm_pL-1;i++) FrcConst    (L++,g); 

      /*! les connections => topologie fixe !*/
      L=TabL+j*nbl_pL + nbl_loc;
      /* les ressorts inter-particules */
      M=TabM+j*nbm_pL + nbm_loc;


      while (L<TabL+j*nbl_pL+nbm_pL-1 + nbl_loc) 
      {
        count++;
        Connect(M,L,M+1);
        M++;
        L++;
      }

      /* les "gravités" individuelles  */
      M=TabM+j*nbm_pL+1 + nbm_loc; /* 1° particule mobile */

      while (L<TabL+(j+1)*nbl_pL + nbl_loc) 
      {
        count++;
        Connect(M,L,NULL);
        M++;
        L++;
      }
    }

    /* Liaison des lignes entre elle + diagonalle*/

    for(j = 0; j < nbligne-1 ; j++){
      /*tenseur de deformation*/
      int idc1;
      if(nbcouche == 1){
        idc1 = nbligne*nbl_pL + j*nbm_pL + j*(nbm_pL-1)*2 + nbl_loc;
      } else {
        /* En 3D le tenseur de torsion passe des faces du carré 2D au diagonalle du cube 3D*/
        idc1 = nbligne*nbl_pL + j*nbm_pL + nbl_loc;
      }
      Link* L2=TabL+ idc1;
      for (i=0;i<nbm_pL;i++) RessortFrein(L2++,k,z);
      L2=TabL+ idc1;


      /*tenseur de torsion*/ /* avec passage en 3D plus besoin du tenseur de torsion sur les faces*/
     /* (nbm_pL-1)*(nbligne-1)*2*/

      PMat* M=TabM+j*nbm_pL + nbm_loc;

      while (L2<TabL+idc1+nbm_pL) 
      {
        count++;
        Connect(M,L2,M+nbm_pL);
        M++;
        L2++;
      }

      int idc2;
      Link *L3;

      if(nbcouche == 1) {
        idc2 = idc1+ nbm_pL;
        L3=TabL + idc2;
        for (i=0;i<(nbm_pL-1)*2;i++) RessortFrein(L3++,k,z);
        L3= TabL+ idc2;

        M = TabM+j*nbm_pL+1 ;
        while (L3<TabL+idc2+(nbm_pL-1)*2) 
        {
          count++;
          count++;
          Connect(M-1,L3,M+nbm_pL);
          L3++;
          Connect(M,L3,M-1+nbm_pL);
          M++;
          L3++;
        }
      }

    }

    for(j = 0; j < nbligne ; j++){
      /*tenseur de courbure*/
      /*(nbm_pl-2)*nbligne + (nbligne-2)*(nbm_pl-1)*/

      if (j < nbligne - 2 ){
        int idc3 = nbl_td_tt + j*(2*nbm_pL-3) + nbl_loc;
        Link* L4= TabL + idc3;
        
        for (i=0;i< 2*nbm_pL-3 ;i++) RessortFrein(L4++,k,z);
        L4= TabL + idc3;

        PMat* M = TabM+j*nbm_pL+1 + nbm_loc;
        while (L4<TabL+idc3+ 2*nbm_pL-3) 
        {
          if(M->pos.x != +pfixe){
            count++;
            memcpy(L4->color,G3Xr ,sizeof(G3Xcolor)); /* changement de couleur pour la visualisation du maillage pont */
            Connect(M-1,L4,M+1);
            L4++;
          }
          memcpy(L4->color,G3Xr ,sizeof(G3Xcolor)); /* changement de couleur pour la visualisation du maillage pont */
          Connect(M,L4,M+2*nbm_pL);
          L4++;
          count++;
          M++;
        } 
         /*  printf("\ncount lock = %d", count);
           fflush(stdout); */
      } else {
        int idc3 = nbl_td_tt + (nbligne-2)*(2*nbm_pL-3)  + (j-(nbligne-2))*(nbm_pL-2) + nbl_loc;
        Link* L4 = TabL + idc3;
        
        for (i=0;i< nbm_pL-2 ;i++) RessortFrein(L4++,k,z);
        L4= TabL+ idc3;

        PMat* M = TabM+j*nbm_pL + nbm_loc;

        while (L4<TabL+idc3+ nbm_pL-2) 
        {
          count++;
          memcpy(L4->color,G3Xr ,sizeof(G3Xcolor)); /* changement de couleur pour la visualisation du maillage pont */
          Connect(M,L4,M+2);
          M++;
          L4++;
        } 
      }
    }
  } /*fin boucle nbc*/

  /* Ajout diagonal 3D + face 3D manquante */

  /*printf("\ncount = %d\n", count);
  fflush(stdout); */

  if(nbcouche >1){
    int i2;
    for(i2=0; i2 < nbligne; i2++){
      /*printf("\ncount i = %d", i2);
      fflush(stdout); 
      */
      PMat* M = TabM + i2*nbm_pL ;
      PMat* M2 = M + nbm2D;

     /* nbl_3D_pL = nbm_pL;
      nbl_3D_diag_pL = (nbm_pL-1)*4;  */
      int idc1 = nbl_2D*2 + i2*nbl_3D_pL + i2*nbl_3D_diag_pL;
      Link* L = TabL + idc1 ;
      int j;
      for (j=0; j< nbl_3D_pL;j++) RessortFrein(L++,k,z);
      if(i2<nbligne-1) {
        for (j=0; j< nbl_3D_diag_pL;j++) RessortFrein(L++,k,z);
      }
      

      L = TabL + idc1 ;
      /*tenseur de déformation sur les arrête du cube (non traité par le cas 2D)*/
      while (L<TabL + idc1 + nbl_3D_pL) {
          count++;
          Connect(M,L,M2);
          M++;
          M2++;
          L++;
      } 

      if (i2<nbligne-1){
        int idc2 = idc1 + nbl_3D_pL;
        M = TabM + i2*nbm_pL  ;
        M2 = M + nbm2D;
         /*tenseur de torsion sur les diagonales du cube -> remplace le tenseur de torsion 2D*/
        while (L<TabL + idc2 + nbl_3D_diag_pL) {
            fflush(stdout);
            count+=4;
            Connect(M,L,M2+nbm_pL+1);
            L++;
            Connect(M+1,L,M2+nbm_pL);
            L++;
            Connect(M+nbm_pL,L,M2+1);
            L++;
            Connect(M+nbm_pL+1,L,M2);

            M++;
            M2++;
            L++;
        } 
      }
    }
    /*printf("\ncount i2 = %d", i2);
    fflush(stdout); 
*/
  }

  printf("\nVerification du nombre de liaison etablis = %d\n", count);
  printf("Paramètre de simulation : \n h = %f, \n Fe = %d,\n k = %f, \n z = %f,\n g = %f,\n",h,Fe,k,z,g);
  printf("Paramètre de vent initial  : \n fréquence Fr.x = %f, Fr.y = %f, Fr.z = %f. \n force : v.x = %f, v.y = %f, v.z = %f.",Fv.x,Fv.y,Fv.z,v.x,v.y,v.z);
  fflush(stdout); 
  
  reset();

  return true;
}


/*=------------------------------=*/
/*=        Initialisation        =*/
/*=------------------------------=*/
void init(void)
{
  /* construction du modèle   */
	if (!Modeleur()) exit(1);
  /* les paramètres réglables */
  g3x_SetScrollWidth(10); 
  g3x_CreateScrollv_i("Fa",&Fa,1,20,1,"Fa"); /*  fq affichage */
  g3x_CreateScrollv_d("tmp",&tempo,0.,.1,1.,"tempo");
	g3x_CreateScrollh_d("k raideurs",&k,k*0.01,k*5.,1,"k");
	g3x_CreateScrollh_d("z viscosirés",&z,z*0.01,z*5.,1,"z");

  double upv = 10000;
  double downv = -10000;
  double upFv = 1;
  double downFv = 0.0001;

  g3x_CreateScrollv_d("v.x  ",&v.x,downv,upv,1,"v.x");
  g3x_CreateScrollv_d("Fv.x  ",&Fv.x,downFv,upFv,1,"Fv.x"); 
  g3x_CreateScrollv_d("v.y  ",&v.y,downv,upv,1,"v.y");
  g3x_CreateScrollv_d("Fv.y  ",&Fv.y,downFv,upFv,1,"Fv.y");
  g3x_CreateScrollv_d("v.z  ",&v.z,downv,upv,1,"v.z");
  g3x_CreateScrollv_d("Fv.z  ",&Fv.z,downFv,upFv,1,"Fv.z");

	g3x_CreatePopUp("reset",reset,"reset");
}
 
/*=------------------------------=*/
/*=          L'Affichage         =*/
/*=------------------------------=*/
void dessin(void) 
{

	/* fréquence d'affichage réglable */
  /*printf("verif 0\n");*/
	g3x_SetRefreshFreq(Fa);
  PMat *M=TabM;/*
  printf("verif 1\n");
  fflush(stdout); */
  while (M<TabM+nbm)  { 
    M->draw(M);
     ++M; 
   }

 
  Link *L=TabL; 
/*
 printf("verif 2\n");
  fflush(stdout); */
  /*int nbliaison_verif = 0;*/

  /*Timer vent */
  g3x_GetTime(clock); 
  timer_v = clock->ss;
  /*printf("time %d: \n", clock->ss);
  fflush(stdout);*/
 
  while (L<TabL+nbl)  { 
   /* printf("l= %d ",nbliaison_verif);
    fflush(stdout);
    nbliaison_verif++;*/
    L->timer = timer_v; 
    L->draw(L); 

    L->v = v; L->Fv = Fv;
    L->k=k *L->amp ; L->z=z *L->amp ; ++L; 

  } /* mise à jour des paramètres => scrollbar */
  /*printf("\n verif 3");
  fflush(stdout); */
}


/*=------------------------------=*/
/*=        Le Simulateur         =*/
/*=------------------------------=*/
void Moteur_Physique(void)
{  
  PMat *M=TabM;
  while (M<TabM+nbm) { M->setup(M,h); ++M; } 
  Link *L=TabL;
  while (L<TabL+nbl) { L->setup(L)  ; ++L; } 
  g3x_tempo(tempo); /* temporisation, si ça va trop vite */
}


/*=-------------------------=*/
/*= Fonction de libération  =*/
/*= appelée à la fin.       =*/
/*=-------------------------=*/
void quit(void)
{
  if (TabM!=NULL) free(TabM); 
  if (TabL!=NULL) free(TabL); 
}

/*=-------------------------=*/
/*=                         =*/
/*=-------------------------=*/
int main(int argc, char* argv[])
{
  g3x_InitWindow(*argv,pixwidth,pixheight);  
  glClearColor(255,255,255,1);
  /*g3x_SetWindowCoord(xmin,ymin,xmax,ymax);*/
  /* param. géométrique de la caméra. cf. gluLookAt(...) */
  float fardepth = 2000;
  g3x_SetPerspective(1.,fardepth,1.);
  /* position, orientation de la caméra */
   g3x_SetCameraSpheric(0.51*PI,-0.55*PI,-_DEPTHCAM,(G3Xpoint){0,_NBLIGNE/2,0.5});
  /*g3x_SetCameraCartesian( (G3Xpoint){0,0,_DEPTHCAM}, (G3Xpoint){0,_NBLIGNE/2,0.5});*/

  g3x_SetInitFunction(init);
  g3x_SetAnimFunction(Moteur_Physique);
  g3x_SetDrawFunction(dessin); 
  g3x_SetExitFunction(quit);      
  return g3x_MainStart();
}
