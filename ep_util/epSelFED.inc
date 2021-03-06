/*  derni�re modification :                                               */
/*         13 01 2016 (SD)                                                */
/*  auteur :                                                              */
/*         SD Samuel D�om (sdeom@epadesa.fr)                              */

/* Pour fonctionner il faut inclure pr�alablement les boites � outils :   */
/*  epCmp (dans ep_util)                                                  */

/* Liste des routines                                                     */
/*  SelFED(�fed) S�lectionner l'ensemble des composants n�cessaires � un  */
/*  �tat descriptif de division en volumes                                */
/*        Derni�re modification : 13/01/2016                              */

/* Proc�dures utiles                                                      */
/*  pas de proc�dures particuli�res                                       */

/* ------------------------- DEBUT DES ROUTINES ------------------------- */

rout,SelFED(�fed,�prc_sel)
/*  Cette routine s�lectionne l'ensemble des composants qui forment       */
/*      l'�tat descriptif de division en volumes dont le matricule est    */
/*      contenu dans la proc�dure �fed et les ajoute � la s�lection dont  */
/*      le nom est contenu dans la proc�dure dont le nom est donn� par    */
/*      contenu dans la proc�dure �fed et les ajoute � la s�lection dont  */
/*  Derni�re modification : 13 01 2016 (SD)                               */
{
  var,�dom
  
  !SelFed_temp=0
  
  !SelOnc_temp=!onc([�fed])
  !SelFed_temp<!SelOnc_temp*[[ProcFCD]]
  !SelFed_temp<!SelOnc_temp*[[ProcFCO]]
  !SelFed_temp<!SelOnc_temp*[[ProcFCL]]
  !SelFed_temp<!SelOnc_temp*[[ProcFED]]
  !SelFed_temp<!SelOnc_temp*[[ProcFEO]]
  !SelFed_temp<!SelOnc_temp*[[ProcFEd]]
  !SelFed_temp<!SelOnc_temp*[[ProcFep]]
  !SelFed_temp<!SelOnc_temp*[[ProcFLD]]
  !SelFed_temp<!SelOnc_temp*[[ProcFLO]]
  !SelFed_temp<!SelOnc_temp*[[ProcFXV]]
  !SelFed_temp<!SelOnc_temp*[[ProcNiv]]
  
  !SelUtil_temp=!util(!SelFed_temp)
  !SelFed_temp<!SelUtil_temp*[[ProcFB]]
  !SelFed_temp<!SelUtil_temp*[[ProcFC]]
  !SelFed_temp<!SelUtil_temp*[[ProcFG]]
  !SelFed_temp<!SelUtil_temp*[[ProcFP]]
  !SelFed_temp<!SelUtil_temp*[[ProcFS]]
  !SelFed_temp<!SelUtil_temp*[[ProcKf]]
  !SelFed_temp<!SelUtil_temp*[[ProcKfn]]

  /* on r�cup�re ce qui figure sur les plans de niveaux (Dimg etc..)      */
  runs,!SelFed_temp*[[ProcNiv]] /* on parcours les niveaux                */
  {
    runr,[mm],D /* nous faisons l'hypoth�se qu'il n'y a qu'un domaine */
    {
      �dom=[[rr]:]
      !SelFed_temp<!util(!dom([�dom]))
    }
  }
  
  [[�prc_sel]]<!SelFed_temp
  
  !sele,!SelFed_temp
  !sele,!SelOnc_temp
  !sele,!SelUtil_temp
}