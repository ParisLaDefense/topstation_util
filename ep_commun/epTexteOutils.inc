/* version 0.2 du                                                         */
/*  derni�re modification :                                               */
/*         15 06 2016 (SD)                                                */
/*  auteur :                                                              */
/*         SD Samuel D�om (sdeom@epadesa.fr)                              */
/*         VD Vianney Dugrain (vdugrain@epadesa.fr)                       */

/* Liste des routines                                                     */
/*  DelChr34(�prc_entree,�prc_sortie) supprime les guillemets d'une       */
/*         chaine de caract�res                                           */
/*         derni�re modification : 14 12 2012 (SD-VD)                     */
/*  EcritTxtRal(�txt,�cmp,�ral,�attr) �crit un texte dans une rallonge en */
/*         respectant la taille maximale                                  */
/*         derni�re modification : 25 02 2013 (SD)                        */
/*  FormateTexte(�prc_var,�prc_sortie) Formate la chaine en entr�e        */
/*         avec des guillemets                                            */
/*         derni�re modification : 28 11 2012 (SD)                        */
/*  ImprIdent(�txt,�rang,�asci) imprime (impr) le texte �txt avec une     */
/*         identation form�e par �rang fois le charact�re ascii           */
/*         de numero de code �asci                                        */
/*         derni�re modification : 15 06 2016 (SD)                        */
/*  Pos(�prc_A,�prc_B,�prc_sortie) Renvoie le nombre de carat�res dans la */
/*         chaine A pr�c�dant la derni�re occurence de B dans A           */
/*         derni�re modification : 04 06 2014 (SD)                        */
/*  PrcTexte(�prc) Formate le contenu de la proc�dure �prc en entr�e avec */
/*         des guillemets                                                 */
/*         derni�re modification : 22 02 2013 (SD)                        */
/*  SubStr(�prc_entree,�prc_pattern,�prc_str,�prc_sortie) remplace une    */
/*         chaine de caract�res par une autre                             */
/*         derni�re modification : 14 12 2012 (SD-VD)                     */


rout,PrcTexte(�prc)
/* Formate la cha�ne de caract�re contenu dans la poc�dure dont le nom    */
/*  indiqu� dans �prc en ajoutant en cas de besoin des guillemets en      */
/*  premi�re et derni�re position pour que la chaine soit de la forme :   */
/*    "chaine de caract�res"                                              */
{
  run,FormateTexte([�prc],[�prc])
}

rout,FormateTexte(�prc_var,�prc_sortie)
/* Formate la cha�ne de caract�re contenu dans la poc�dure dont le nom    */
/*  indiqu� dans �prc_var en ajoutant en cas de besoin des guillemets en  */
/*  premi�re et derni�re position pour que la chaine renvoy�e dans la     */
/*  proc�dure dont le nom est donn� par �prc_sortie soit de la forme :    */
/*    "chaine de caract�res"                                              */
{
  [�prc_sortie]=[[�prc_var]]
  if,"[pos([�prc_var],chr(34))=-1]"
  /*    S'il n'y a pas de guillemets, on en ajoute    */
  {
    [�prc_sortie]="[[�prc_var]]"
  }
  else
  {
    if,"[pos(`[[�prc_var]]`,chr(34))>0]"
    /*    S'il y a des guillemets, mais pas en d�but de chaine,                 */
    /*    on en ajoute en d�but de chaine                                        */
    {
      [�prc_sortie]="[[�prc_var]]
    }
    if,"[pos([�prc_var],chr(34),1)=-1]"
    /*    S'il n'y a pas de guillemet fermant, on en ajoute en fin de chaine    */
    {
      [�prc_sortie]=[[�prc_var]]"
    }
    else
    /*    S'il y a un guillemet fermant,                                         */
    /*    on tronque la chaine de caract�re apr�s celui-ci                    */
    {
      var,�fin
      �fin=[pos([�prc_sortie],chr(34),1)+1]
      [�prc_sortie]=[xtr([�prc_sortie],0,[�fin])]
    }
  }
}

rout,EcritTxtRal(�prc_txt,�cmp,�rali,�attr)
/* Enregistre dans l'attribut dont le nom est indiqu� dans �attr de la rallonge */
/*  donn�e dans �ral du composant sp�cifi� dans �cmp le texte contenu dans la   */
/*  proc�dure dont le nom est donn� par �txt de mani�re � ce que la rallonge ne */
/*  d�passe pas 160 caract�res                                                    */
/* Par d�faut le texte est ajout� directement dans la rallonge                  */
{
  var,�txta,�rala,�lmax,�lattr,�ral,�ind
  /*    Mise � z�ro de l'attribut de la rallonge        */

  if,"len(�rali)=1"
  {
    run,DetInd([�cmp],[�rali],�ind)
    �ral=[�rali][�ind]
  }
  else
  {
    if,"len(�rali)=0"
    {
      run,DetInd([�cmp],T,�ind)
      �ral=T[�ind]
    }
    else
    {
      �ral=[�rali]
    }
  }
  
  if,"len(�attr)=0"
  {
    [�cmp]&[�ral]:
    �lattr=2 /*    pour les guillemets    */
  }
  else
  {
    ral,[�cmp]&[�ral]:[�attr]=
    /*    Calcul de la longueur du nom de l'attribut                    */
    /*       -  2        guillemets                                        */
    /*       -  2        ',' + '='                                        */
    /*       - longueur du nom de l'attribut                            */
    �lattr=[2+2+len(�attr)]
  }
  /*    Calcul de la taille de la rallonge actuelle �rala            */
  �rala=[�cmp]&[�ral]:[[�cmp]&[�ral]:]
  /*    Calcul de la longueur de l'attribut � ajouter :                */
  /*        = 159 - longueur du nom de l'attribut                    */
  /*              - longueur de la rallonge existante                */        
  �lmax=[158-len(�rala)-[�lattr]]

  �txta=[xtr([�prc_txt],0,[�lmax])]
  run,FormateTexte(�txta,�txta)
  if,"len(�attr)=0"
  /*    Si l'attribut n'est pas renseign�, on ajoute directement la rallonge    */ 
  {
    [�cmp]&[�ral]:[�txta]
  }
  else
  /*    Sinon, on utilise la proc�dure ral    */ 
  {
    ral,[�cmp]&[�ral]:[�attr]=[�txta]
  }
}

rout,SubStr(�prc_entree,�prc_pattern,�prc_str,�prc_sortie)
/*    Remplace la cha�ne de caract�res �prc_pattern contenue dans la    */
/*     proc�dure �prc_entree par �prc_str, et renvoie la proc�dure    */
/*     �prc_sortie                                                    */
{
  var,�bool,�temp,�lpattern,�pos
  �lpattern=[len([�prc_pattern])]
  �temp=[[�prc_entree]]
  if,"[�prc_pattern]<<[�prc_entree]"
  {
    �bool=1
    whil,�bool
    {
      �pos=[pos(�temp,[�prc_pattern])]
      �temp=[xtr(�temp,0,�pos)][[�prc_str]][xtr(�temp,[�pos+�lpattern])]
      �bool=[[�prc_pattern]<<�temp]
    }
  }
  [�prc_sortie]=[�temp]
}

rout,DelChr34(�prc_entree,�prc_sortie)
{
  var,�bool,�temp,�lpattern,�pos
  �lpattern=1
  �temp=[[�prc_entree]]
  if,"chr(34)<<[�prc_entree]"
  {
    �bool=1
    whil,�bool
    {
      �pos=[pos(�temp,chr(34))]
      �temp=[xtr(�temp,0,�pos)][xtr(�temp,[�pos+�lpattern])]
      �bool=[chr(34)<<�temp]
    }
  }
  [�prc_sortie]=[�temp]
}

rout,AtoZ(�prc_entree,�prc_sortie)
/*  supprimme de la cha�ne de caract�res contenue dans la proc�dure */
/*   dont le nom est donn� par la proc�dure �prc_entree tous les    */
/*   caract�res autres que a-z et A-Z, 0-9 et renvoie le r�sultat   */
/*   dans la proc�dure dont le nom est donn� �prc_sortie            */
{
  var,�l,�i
  var,�char,�resultat,�n_ascii
  
  �l=[len([�prc_entree])]
  �resultat=
  
  for,"0->�i","�i<�l","�i+1->�i"
  {
    �char=[xtr([�prc_entree],�i,1)]
    �char=[ltrn(�char)]
    �n_ascii=[asc(�char)]
    if,"�n_ascii>64"
    {
      if,"�n_ascii<91"
      {
        �resultat=[�resultat][�char]
      }
    }
    if,"�n_ascii>96"
    {
      if,"�n_ascii<123"
      {
        �resultat=[�resultat][�char]
      }
    }
    if,"�n_ascii>47"
    {
      if,"�n_ascii<58"
      {
        �resultat=[�resultat][�char]
      }
    }
    if,"�n_ascii=32"
    {
      �resultat=[�resultat]_
    }
    if,"�n_ascii=0"
    {
      �resultat=[�resultat]_
    }
  }
  [�prc_sortie]=[�resultat]
}

rout,Pos(�prc_A,�prc_B,�prc_sortie)
/*  Renvoie le nombre de carat�res dans la chaine contenue dans la  */
/*   proc�dure dont le nom est donn� par �prc_A pr�c�dant la        */
/*   derni�re occurence de la chaine contenue dans la proc�dure     */
/*   dont le nom est donn� par �prc_B dans A. Le retour se fait     */
/*   dans la proc�dure dont le nom est donn� par �prc_sortie        */
/*   Si A n'inclut pas pas B renvoie -1                             */
{
  var,�resultat
  var,�d
 
  �d=[pos([�prc_A],[�prc_B])]
  if,"�d=-1"
  {
    �resultat=-1
  }
  else
  {
    �resultat=0
    whil,"�d<>-1"
    {
      �resultat=[�resultat+�d]
      �d=[[pos([�prc_A],[�prc_B],�resultat+1)]+1]
      if,"�d=0"
      {
        �d=-1
      }
    }
  }
  
  [�prc_sortie]=[�resultat]
}