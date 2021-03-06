/* version 0.1 du                                                           */
/*  derni�re modification :                                                 */
/*         01 06 2015 (SD)                                                  */
/*  auteur :                                                                */
/*         SD Samuel D�om (sdeom@epadesa.fr)                                */


/* Pour fonctionner il faut inclure pr�alablement les boites � outils :     */
/*  epTypeOutils                                                            */
/*  epPlanOutils                                                            */
/*  epTexteOutils (pour epPlanOutils)                                       */

/* Proc�dures de l'environnement                                            */
proc,Fed_md=EP_ZON_EDDV

/* Liste des routines                                                       */
/*  AplPlan Applique le plan du m�me �tat descriptif de division en volumes */
/*           dont l'altitude est imm�diatement sup�rieure ou inf�rieure �   */
/*           celle du plan actuellement trac�                               */
/*  DetFED(�prc_fed) D�termine le matricule correspondant � l'�tat descrip- */
/*           tif associ� au plan qui est trac�                              */
/*  DetPlanInf(�prc_plan) D�termine le matricule correspondant au plan du   */
/*           m�me �tat descriptif de division en volumes dont l'altitude    */
/*           est imm�diatement inf�rieur � celle du plan actuellement trac� */
/*  DetPlanSup(�prc_plan) D�termine le matricule correspondant au plan du   */
/*           m�me �tat descriptif de division en volumes dont l'altitude    */
/*           est imm�diatement sup�rieur � celle du plan actuellement trac� */


/*--------------------------------------------------------------------------*/
/*                                ROUTINES                                  */
/*                         par ordre alphab�tique                           */
/*--------------------------------------------------------------------------*/

rout,AplPlan(�type)
/*  Applique le plan du m�me �tat descriptif de division en volumes dont    */
/*           l'altitude est imm�diatement inf�rieure ou sup�rieure � celle  */
/*           du plan actuellement trac� selon que �type vaut "Inf" ou "Sup" */
/*    S'il n'y a pas de plan r�pondant � ce crit�re, ne fait rien           */
/*  Derni�re modification : 01 06 2015 (SD)                                 */
{
  var,�mat
  �mat=[EpTypeVide]
  if,"[�type==`Inf`]#[�type==`Sup`]"
  {
    run,DetPlanEdd([�type],�mat)
  }
  if,"�mat><EpTypeVide"
  {
    plna,[�mat]
  }
}

rout,DetFED(�prc_fed)
/* D�termine le matricule correspondant � l'�tat descriptif associ� au plan */
/*           qui est trac�                                                  */
/*    L'indice en renvoy� dans la proc�dure dont le nom est indiqu� dans    */
/*           �prc_fed                                                       */
/*  Derni�re modification : 01 06 2015 (SD)                                 */
{
  var,�fed
  
  �fed=
  if,"defprc(`jtMatPlan`)"
  {
    �fed=[[jtMatPlan]&r0:E]
  }
  
  if,"�fed><``"
  {
    [�prc_fed]=[�fed]
  }
  else
  {
    [�prc_fed]=[EpTypeVide]
  }
}

rout,DetPlanEdd(�type,�prc_plan)
/*  D�termine le matricule correspondant au plan du m�me �tat descriptif de */
/*           division en volumes dont l'altitude est imm�diatement inf�ri-  */
/*           eure ou sup�rieure � celle du plan actuellement trac�          */
/*    L'indice en renvoy� dans la proc�dure dont le nom est indiqu� dans    */
/*           �prc_plan                                                      */
/*  Derni�re modification : 01 06 2015 (SD)                                 */
{
  var,�fed,�test
  
  [�prc_plan]=[EpTypeVide]
  
  run,DetFED(�fed)
  if,"�fed><EpTypeVide"
  {
    �test=!test(&r0:e==[�fed])
    run,DetPlan([�type],�test,[�prc_plan])
  }
}

rout,TraPlan(�type)
/*  Applique le plan du m�me �tat descriptif de division en volumes dont    */
/*           l'altitude est imm�diatement inf�rieure ou sup�rieure � celle  */
/*           du plan actuellement trac� selon que �type vaut "Inf" ou "Sup" */
/*           en conservant les param�tres de vue                            */
/*    S'il n'y a pas de plan r�pondant � ce crit�re, ne fait rien           */
/*  Derni�re modification : 01 06 2015 (SD)                                 */
{
  var,�x,�y,�l,�h,�g,�ec
  var,�mat
  �mat=[EpTypeVide]
  
  �x=[xmvue]
  �y=[ymvue]
  �l=[2*dlvue]
  �h=[2*dhvue]
  �g=[%PLA:G]
  �ec=[%PLA:E]
  
  /* on simule une application de plan */
  if,"[�type==`Inf`]#[�type==`Sup`]"
  {
    run,DetPlanEdd([�type],�mat)
  }
  if,"�mat><EpTypeVide"
  {
    %PLA:X=[[�mat]:X]
    %PLA:Y=[[�mat]:Y]
    %PLA:L=[[�mat]:Cx]
    %PLA:H=[[�mat]:Cy]
    runr,comp=[�mat],type=K
    {
      [[rr]:][ex]
    }
    jtMatPlan=[�mat]
  }
  
  %PLA:G=[�g]
  %PLA:E=[�ec]
  cvue,x=[�x],y=[�y],l=[�l],h=[�h]
}