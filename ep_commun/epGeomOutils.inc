/* Version 0.1                                                            */
/*  derni�re modification :                                               */
/*         13 12 2013 (SD)                                                */
/*  auteur :                                                              */
/*         SD Samuel D�om (sdeom@epadesa.fr)                              */
/*         VD Vianney Dugrain (vdugrain@epadesa.fr)                       */

/* Cette boite � outils contient des routines permettant le traitement    */
/*  de fonctions g�om�triques                                             */

/* Liste des routines                                                     */
/*  DetPtPlusProche(�prc_cmp,!SelPoints,�prc_tampon,�prc_ppp)             */
/*           D�termine le point le plus proche d'un composant             */
/*         derni�re modification : 13/12/2013 (SD)                        */

rout,DetPlusProch2(�prc_cmp,�prc_sel,�prc_ppp)
/*    D�termine le point le plus proche du composant stock� dans la       */
/*    proc�dure �prc_cmp, parmi la s�lection dont le nom est contenue     */
/*    dans �prc_sel, et renvoie le matricule du r�sultat dans �prc_ppp    */
{
    var,�min_dist,�jeton
    �jeton=1
    !DetPlusProche=[[�prc_sel]]
    !DetPlusProche>[[�prc_cmp]]
    [�prc_ppp]=aucun
    runs,!DetPlusProche
    {
        if,"�jeton=1"
        {
            �min_dist=[dist([�prc_cmp],mm)]
            [�prc_ppp]=[mm]
            �jeton=0
        }
        else
        {
            if,"[[dist([�prc_cmp],mm)]<[�min_dist]]@[[�prc_cmp]><mm]"
            {
                �min_dist=[dist([�prc_cmp],mm)]
                [�prc_ppp]=[mm]
            }
        }
    }
    !sele,!DetPlusProche
}

rout,DetPlusProche(�prc_cmp,�prc_sel,�prc_ppp)
/*    D�termine le point le plus proche du composant stock� dans la       */
/*    proc�dure �prc_cmp, parmi la s�lection dont le nom est contenue     */
/*    dans �prc_sel, et renvoie le matricule du r�sultat dans �prc_ppp    */
{
    var,�min_dist,�jeton,�alea,�i
    
    !DetPlusProche=[[�prc_sel]]
    !DetPlusProche>[[�prc_cmp]]
    [�prc_ppp]=aucun
    
    !EpSelTmp=!pntp([[�prc_cmp]],0)
	!EpSelTmp>[[�prc_cmp]]
    if,test="nmbr(`!EpSelTmp`)>0"
    then
    {
      !DetPlusProche=!EpSelTmp
      �jeton=1
    }
    else
    {
      �jeton=0
    }
	
    whil,test="�jeton=0"
    {
      �alea=[rnd*nmbr(`!DetPlusProche`)%0]
	  �i=0
	  runs,sel=!DetPlusProche
      {
		�min_dist=[dist([�prc_cmp],mm)]
        [�prc_ppp]=[mm]
        exit
      }
      !EpSelTmp=!DetPlusProche*!pntp([[�prc_cmp]],[�min_dist-0.001])
	  !EpSelTmp>[[�prc_ppp]]
      if,test="nmbr(`!EpSelTmp`)=0"
	  then
	  {
	    �jeton=1
	  }
      else
      {
        !DetPlusProche=!EpSelTmp
      }
    }
	
	runs,!DetPlusProche
    {
      if,"�jeton=1"
      {
        �min_dist=[dist([�prc_cmp],mm)]
        [�prc_ppp]=[mm]
        �jeton=0
      }
      else
      {
        if,"[[dist([�prc_cmp],mm)]<[�min_dist]]@[[�prc_cmp]><mm]"
        {
            �min_dist=[dist([�prc_cmp],mm)]
            [�prc_ppp]=[mm]
        }
      }
    }
	
    !sele,!DetPlusProche
    !sele,!EpSelTmp
}