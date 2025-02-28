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

	#ifndef _G2X_H_
  	#define _G2X_H_
  
  #include <stdio.h>            /* les libs standard du C                  */
  #include <stdlib.h>
  #include <string.h>
  #include <math.h>
  #include <unistd.h>
  
	#include <OpenGL/gl.h>        /* la lib. OpenGl                          */
	#include <GLUT/glut.h>        /* la lib. GLUT (Gl Utility Toolkit)       */

  #include <g2x_types.h>        /* types primaires et macros diverses      */
  #include <g2x_colors.h>       /* couleurs pr�d�finies                    */
  #include <g2x_basix.h>        /* routines et fonctions de base           */
  #include <g2x_capture.h>      /* routines de capture d'�cran image/vid�o */
  #include <g2x_tools.h>        /* utilitaires divers                      */
  #include <g2x_draw.h>         /* trac� en mode r�el                      */
  #include <g2x_geoalgo.h>      /* algo. g�om�triques en mode r�el         */
  #include <g2x_polygon.h>      /* manipulation de polyg�nes (listes)      */
  #include <g2x_transfo.h>      /* transformations g�om�triques            */
  
	#endif  

#ifdef __cplusplus
	}
#endif
/*===============================================================*/
