/* ===============================================================
  E.Incerti - Universit� de Marne-la-Vall�e - incerti@univ-mlv.fr 
       - Librairie G2X - Fonctions de base d'acc�s public -       
                    version 5.0 - Dec.2012                        
  ============================================================= */

#ifdef __cplusplus
  extern "C" {
#else
  #define _GNU_SOURCE
#endif

#ifndef _G2X_TOOLS_H_
  #define _G2X_TOOLS_H_

#include <g2x.h>

  typedef struct
  {
    uint hh;
    uint mm;
    uint ss;
    uint ds; /* dizieme  de sec. */
    uint cs; /* centieme de sec. */
    uint ms; /* millieme de sec. */
  } G2Xclock;

  char*  g2x_ProcTimer(void);
  char*  g2x_Chrono(void);
  void   g2x_GetTime(G2Xclock* clock);
  
  double g2x_RandIntervall(double inf, double sup);    
  double g2x_RandPercent(double root, double percent);
  double g2x_RandDelta(double root, double delta);

  double g2x_Radcos(double rad);
  double g2x_Radsin(double rad);
  double g2x_Degcos(double deg);
  double g2x_Degsin(double deg);
  
  /*= cartes de couleurs -- Rempli un tableau de n couleurs en d�grad� ! =*/
  /* Bas� sur carte HSV : */
  /*    0�= rouge         */
  /*   60�= jaune         */
  /*  120�= vert          */
  /*  180�= cyan          */
  /*  240�= bleu          */
  /*  300�= magenta       */
  /*  360�= rouge         */
  /* n teintes �talonn�es du rouge (0�) au rouge (360�) */
  bool g2x_FillColorMap(G2Xcolor *map, int n);
  bool g2x_FillColorMap_va(G2Xcolor *map, int n, float v, float a);
  bool g2x_BuildColorMap(int n);
  float* g2x_GetColorIndex(int idx);
  


 #endif

#ifdef __cplusplus
  }
#endif
/*===============================================================*/
