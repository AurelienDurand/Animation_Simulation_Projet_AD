/* ===============================================================
  E.Incerti - Université de Marne-la-Vallée - incerti@univ-mlv.fr 
       - Librairie G2X - Fonctions de base d'accès public -       
                    version 5.0 - Dec.2012                        
  ============================================================= */

#ifdef __cplusplus
  extern "C" {
#endif

#ifndef _G2X_COLORS_H
  #define _G2X_COLORS_H
  
  /* DES COULEURS RGBA PREDEFINIES                           */
  /* les 6 teintes primaires (RGB) et secondaires (CMY)      */
  /* plus Orange, blanc (->gris) et , noir                   */
  /* 5 niveaux d'intensité 100%,75%,50%,33%,16%              */
  /* 4 niveaux de densité (transp.) 00%,25%,50%,75%          */
  
  /* densité   100%                                          */
  /* intensité 100%                                          */
  #define G2Xw    (const float[4]){1.00,1.00,1.00,0.00} /* blanc   */
  #define G2Xr    (const float[4]){1.00,0.00,0.00,0.00} /* rouge   */
  #define G2Xo    (const float[4]){1.00,0.50,0.25,0.00} /* orange  */
  #define G2Xy    (const float[4]){1.00,1.00,0.00,0.00} /* jaune   */
  #define G2Xg    (const float[4]){0.00,1.00,0.00,0.00} /* vert    */
  #define G2Xc    (const float[4]){0.00,1.00,1.00,0.00} /* cyan    */
  #define G2Xb    (const float[4]){0.00,0.00,1.00,0.00} /* bleu    */
  #define G2Xm    (const float[4]){1.00,0.00,1.00,0.00} /* magenta */
  #define G2Xk    (const float[4]){0.00,0.00,0.00,0.00} /* noir    */
  /* intensité  75%                                          */
  #define G2Xwa   (const float[4]){0.75,0.75,0.75,0.00} /*         */
  #define G2Xra   (const float[4]){0.75,0.00,0.00,0.00} /*         */
  #define G2Xoa   (const float[4]){0.75,0.37,0.12,0.00} /*         */
  #define G2Xya   (const float[4]){0.75,0.75,0.00,0.00} /*         */
  #define G2Xga   (const float[4]){0.00,0.75,0.00,0.00} /*         */
  #define G2Xca   (const float[4]){0.00,0.75,0.75,0.00} /*         */
  #define G2Xba   (const float[4]){0.00,0.00,0.75,0.00} /*         */
  #define G2Xma   (const float[4]){0.75,0.00,0.75,0.00} /*         */
  /* intensité  50%                                          */
  #define G2Xwb   (const float[4]){0.50,0.50,0.50,0.00} /*         */
  #define G2Xrb   (const float[4]){0.50,0.12,0.12,0.00} /*         */
  #define G2Xob   (const float[4]){0.50,0.25,0.06,0.00} /*         */
  #define G2Xyb   (const float[4]){0.50,0.50,0.12,0.00} /*         */
  #define G2Xgb   (const float[4]){0.12,0.50,0.12,0.00} /*         */
  #define G2Xcb   (const float[4]){0.12,0.50,0.50,0.00} /*         */
  #define G2Xbb   (const float[4]){0.12,0.12,0.50,0.00} /*         */
  #define G2Xmb   (const float[4]){0.50,0.12,0.50,0.00} /*         */
  /* intensité  33%                                          */
  #define G2Xwc   (const float[4]){0.33,0.33,0.33,0.00} /*         */
  #define G2Xrc   (const float[4]){0.33,0.06,0.06,0.00} /*         */
  #define G2Xoc   (const float[4]){0.33,0.16,0.06,0.00} /*         */
  #define G2Xyc   (const float[4]){0.33,0.33,0.06,0.00} /*         */
  #define G2Xgc   (const float[4]){0.06,0.33,0.06,0.00} /*         */
  #define G2Xcc   (const float[4]){0.06,0.33,0.33,0.00} /*         */
  #define G2Xbc   (const float[4]){0.06,0.06,0.33,0.00} /*         */
  #define G2Xmc   (const float[4]){0.33,0.06,0.33,0.00} /*         */
  /* intensité  16%                                          */
  #define G2Xwd   (const float[4]){0.16,0.12,0.12,0.00} /*         */
  #define G2Xrd   (const float[4]){0.16,0.04,0.04,0.00} /*         */
  #define G2Xod   (const float[4]){0.16,0.08,0.04,0.00} /*         */
  #define G2Xyd   (const float[4]){0.16,0.16,0.04,0.00} /*         */
  #define G2Xgd   (const float[4]){0.04,0.16,0.04,0.00} /*         */
  #define G2Xcd   (const float[4]){0.04,0.16,0.16,0.00} /*         */
  #define G2Xbd   (const float[4]){0.04,0.04,0.16,0.00} /*         */
  #define G2Xmd   (const float[4]){0.16,0.04,0.16,0.00} /*         */


  /* densité    75%                                          */
  /* intensité 100%                                          */
  #define G2Xw_a  (const float[4]){1.00,1.00,1.00,0.25} /* blanc   */
  #define G2Xr_a  (const float[4]){1.00,0.00,0.00,0.25} /* rouge   */
  #define G2Xo_a  (const float[4]){1.00,0.50,0.25,0.25} /* orange  */
  #define G2Xy_a  (const float[4]){1.00,1.00,0.00,0.25} /* jaune   */
  #define G2Xg_a  (const float[4]){0.00,1.00,0.00,0.25} /* vert    */
  #define G2Xc_a  (const float[4]){0.00,1.00,1.00,0.25} /* cyan    */
  #define G2Xb_a  (const float[4]){0.00,0.00,1.00,0.25} /* bleu    */
  #define G2Xm_a  (const float[4]){1.00,0.00,1.00,0.25} /* magenta */
  #define G2Xk_a  (const float[4]){0.00,0.00,0.00,0.25} /* noir    */
  /* intensité  75%                                          */
  #define G2Xwa_a (const float[4]){0.75,0.75,0.75,0.25} /*         */
  #define G2Xra_a (const float[4]){0.75,0.00,0.00,0.25} /*         */
  #define G2Xoa_a (const float[4]){0.75,0.37,0.12,0.25} /*         */
  #define G2Xya_a (const float[4]){0.75,0.75,0.00,0.25} /*         */
  #define G2Xga_a (const float[4]){0.00,0.75,0.00,0.25} /*         */
  #define G2Xca_a (const float[4]){0.00,0.75,0.75,0.25} /*         */
  #define G2Xba_a (const float[4]){0.00,0.00,0.75,0.25} /*         */
  #define G2Xma_a (const float[4]){0.75,0.00,0.75,0.25} /*         */
  /* intensité  50%                                          */
  #define G2Xwb_a (const float[4]){0.50,0.50,0.50,0.25} /*         */
  #define G2Xrb_a (const float[4]){0.50,0.12,0.12,0.25} /*         */
  #define G2Xob_a (const float[4]){0.50,0.25,0.06,0.25} /*         */
  #define G2Xyb_a (const float[4]){0.50,0.50,0.12,0.25} /*         */
  #define G2Xgb_a (const float[4]){0.12,0.50,0.12,0.25} /*         */
  #define G2Xcb_a (const float[4]){0.12,0.50,0.50,0.25} /*         */
  #define G2Xbb_a (const float[4]){0.12,0.12,0.50,0.25} /*         */
  #define G2Xmb_a (const float[4]){0.50,0.12,0.50,0.25} /*         */
  /* intensité  33%                                          */
  #define G2Xwc_a (const float[4]){0.33,0.33,0.33,0.25} /*         */
  #define G2Xrc_a (const float[4]){0.33,0.06,0.06,0.25} /*         */
  #define G2Xoc_a (const float[4]){0.33,0.16,0.06,0.25} /*         */
  #define G2Xyc_a (const float[4]){0.33,0.33,0.06,0.25} /*         */
  #define G2Xgc_a (const float[4]){0.06,0.33,0.06,0.25} /*         */
  #define G2Xcc_a (const float[4]){0.06,0.33,0.33,0.25} /*         */
  #define G2Xbc_a (const float[4]){0.06,0.06,0.33,0.25} /*         */
  #define G2Xmc_a (const float[4]){0.33,0.06,0.33,0.25} /*         */
  /* intensité  16%                                          */
  #define G2Xwd_a (const float[4]){0.16,0.12,0.12,0.25} /*         */
  #define G2Xrd_a (const float[4]){0.16,0.04,0.04,0.25} /*         */
  #define G2Xod_a (const float[4]){0.16,0.08,0.04,0.25} /*         */
  #define G2Xyd_a (const float[4]){0.16,0.16,0.04,0.25} /*         */
  #define G2Xgd_a (const float[4]){0.04,0.16,0.04,0.25} /*         */
  #define G2Xcd_a (const float[4]){0.04,0.16,0.16,0.25} /*         */
  #define G2Xbd_a (const float[4]){0.04,0.04,0.16,0.25} /*         */
  #define G2Xmd_a (const float[4]){0.16,0.04,0.16,0.25} /*         */

  /* densité    50%                                          */
  /* intensité 100%                                          */
  #define G2Xw_b  (const float[4]){1.00,1.00,1.00,0.50} /* blanc   */
  #define G2Xr_b  (const float[4]){1.00,0.00,0.00,0.50} /* rouge   */
  #define G2Xo_b  (const float[4]){1.00,0.50,0.25,0.50} /* orange  */
  #define G2Xy_b  (const float[4]){1.00,1.00,0.00,0.50} /* jaune   */
  #define G2Xg_b  (const float[4]){0.00,1.00,0.00,0.50} /* vert    */
  #define G2Xc_b  (const float[4]){0.00,1.00,1.00,0.50} /* cyan    */
  #define G2Xb_b  (const float[4]){0.00,0.00,1.00,0.50} /* bleu    */
  #define G2Xm_b  (const float[4]){1.00,0.00,1.00,0.50} /* magenta */
  #define G2Xk_b  (const float[4]){0.00,0.00,0.00,0.50} /* noir    */
  /* intensité  75%                                          */
  #define G2Xwa_b (const float[4]){0.75,0.75,0.75,0.50} /*         */
  #define G2Xra_b (const float[4]){0.75,0.00,0.00,0.50} /*         */
  #define G2Xoa_b (const float[4]){0.75,0.37,0.12,0.50} /*         */
  #define G2Xya_b (const float[4]){0.75,0.75,0.00,0.50} /*         */
  #define G2Xga_b (const float[4]){0.00,0.75,0.00,0.50} /*         */
  #define G2Xca_b (const float[4]){0.00,0.75,0.75,0.50} /*         */
  #define G2Xba_b (const float[4]){0.00,0.00,0.75,0.50} /*         */
  #define G2Xma_b (const float[4]){0.75,0.00,0.75,0.50} /*         */
  /* intensité  50%                                          */
  #define G2Xwb_b (const float[4]){0.50,0.50,0.50,0.50} /*         */
  #define G2Xrb_b (const float[4]){0.50,0.12,0.12,0.50} /*         */
  #define G2Xob_b (const float[4]){0.50,0.25,0.06,0.50} /*         */
  #define G2Xyb_b (const float[4]){0.50,0.50,0.12,0.50} /*         */
  #define G2Xgb_b (const float[4]){0.12,0.50,0.12,0.50} /*         */
  #define G2Xcb_b (const float[4]){0.12,0.50,0.50,0.50} /*         */
  #define G2Xbb_b (const float[4]){0.12,0.12,0.50,0.50} /*         */
  #define G2Xmb_b (const float[4]){0.50,0.12,0.50,0.50} /*         */
  /* intensité  33%                                          */
  #define G2Xwc_b (const float[4]){0.33,0.33,0.33,0.50} /*         */
  #define G2Xrc_b (const float[4]){0.33,0.06,0.06,0.50} /*         */
  #define G2Xoc_b (const float[4]){0.33,0.16,0.06,0.50} /*         */
  #define G2Xyc_b (const float[4]){0.33,0.33,0.06,0.50} /*         */
  #define G2Xgc_b (const float[4]){0.06,0.33,0.06,0.50} /*         */
  #define G2Xcc_b (const float[4]){0.06,0.33,0.33,0.50} /*         */
  #define G2Xbc_b (const float[4]){0.06,0.06,0.33,0.50} /*         */
  #define G2Xmc_b (const float[4]){0.33,0.06,0.33,0.50} /*         */
  /* intensité  16%                                          */
  #define G2Xwd_b (const float[4]){0.16,0.12,0.12,0.50} /*         */
  #define G2Xrd_b (const float[4]){0.16,0.04,0.04,0.50} /*         */
  #define G2Xod_b (const float[4]){0.16,0.08,0.04,0.50} /*         */
  #define G2Xyd_b (const float[4]){0.16,0.16,0.04,0.50} /*         */
  #define G2Xgd_b (const float[4]){0.04,0.16,0.04,0.50} /*         */
  #define G2Xcd_b (const float[4]){0.04,0.16,0.16,0.50} /*         */
  #define G2Xbd_b (const float[4]){0.04,0.04,0.16,0.50} /*         */
  #define G2Xmd_b (const float[4]){0.16,0.04,0.16,0.50} /*         */

  /* densité    25%                                          */
  /* intensité 100%                                          */
  #define G2Xw_c  (const float[4]){1.00,1.00,1.00,0.75} /* blanc   */
  #define G2Xr_c  (const float[4]){1.00,0.00,0.00,0.75} /* rouge   */
  #define G2Xo_c  (const float[4]){1.00,0.50,0.25,0.75} /* orange  */
  #define G2Xy_c  (const float[4]){1.00,1.00,0.00,0.75} /* jaune   */
  #define G2Xg_c  (const float[4]){0.00,1.00,0.00,0.75} /* vert    */
  #define G2Xc_c  (const float[4]){0.00,1.00,1.00,0.75} /* cyan    */
  #define G2Xb_c  (const float[4]){0.00,0.00,1.00,0.75} /* bleu    */
  #define G2Xm_c  (const float[4]){1.00,0.00,1.00,0.75} /* magenta */
  #define G2Xk_c  (const float[4]){0.00,0.00,0.00,0.75} /* noir    */
  /* intensité  75%                                          */
  #define G2Xwa_c (const float[4]){0.75,0.75,0.75,0.75} /*         */
  #define G2Xra_c (const float[4]){0.75,0.00,0.00,0.75} /*         */
  #define G2Xoa_c (const float[4]){0.75,0.37,0.12,0.75} /*         */
  #define G2Xya_c (const float[4]){0.75,0.75,0.00,0.75} /*         */
  #define G2Xga_c (const float[4]){0.00,0.75,0.00,0.75} /*         */
  #define G2Xca_c (const float[4]){0.00,0.75,0.75,0.75} /*         */
  #define G2Xba_c (const float[4]){0.00,0.00,0.75,0.75} /*         */
  #define G2Xma_c (const float[4]){0.75,0.00,0.75,0.75} /*         */
  /* intensité  50%                                          */
  #define G2Xwb_c (const float[4]){0.50,0.50,0.50,0.75} /*         */
  #define G2Xrb_c (const float[4]){0.50,0.12,0.12,0.75} /*         */
  #define G2Xob_c (const float[4]){0.50,0.25,0.06,0.75} /*         */
  #define G2Xyb_c (const float[4]){0.50,0.50,0.12,0.75} /*         */
  #define G2Xgb_c (const float[4]){0.12,0.50,0.12,0.75} /*         */
  #define G2Xcb_c (const float[4]){0.12,0.50,0.50,0.75} /*         */
  #define G2Xbb_c (const float[4]){0.12,0.12,0.50,0.75} /*         */
  #define G2Xmb_c (const float[4]){0.50,0.12,0.50,0.75} /*         */
  /* intensité  33%                                          */
  #define G2Xwc_c (const float[4]){0.33,0.33,0.33,0.75} /*         */
  #define G2Xrc_c (const float[4]){0.33,0.06,0.06,0.75} /*         */
  #define G2Xoc_c (const float[4]){0.33,0.16,0.06,0.75} /*         */
  #define G2Xyc_c (const float[4]){0.33,0.33,0.06,0.75} /*         */
  #define G2Xgc_c (const float[4]){0.06,0.33,0.06,0.75} /*         */
  #define G2Xcc_c (const float[4]){0.06,0.33,0.33,0.75} /*         */
  #define G2Xbc_c (const float[4]){0.06,0.06,0.33,0.75} /*         */
  #define G2Xmc_c (const float[4]){0.33,0.06,0.33,0.75} /*         */
  /* intensité  16%                                         */
  #define G2Xwd_c (const float[4]){0.16,0.12,0.12,0.75} /*         */
  #define G2Xrd_c (const float[4]){0.16,0.04,0.04,0.75} /*         */
  #define G2Xod_c (const float[4]){0.16,0.08,0.04,0.75} /*         */
  #define G2Xyd_c (const float[4]){0.16,0.16,0.04,0.75} /*         */
  #define G2Xgd_c (const float[4]){0.04,0.16,0.04,0.75} /*         */
  #define G2Xcd_c (const float[4]){0.04,0.16,0.16,0.75} /*         */
  #define G2Xbd_c (const float[4]){0.04,0.04,0.16,0.75} /*         */
  #define G2Xmd_c (const float[4]){0.16,0.04,0.16,0.75} /*         */

#endif

#ifdef __cplusplus
  }
#endif
/*=============================================================================*/
