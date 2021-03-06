/* version 0.2 du                                                         */
/*  derni�re modification :                                               */
/*         01 10 2013 (SD)                                                */
/*  auteur :                                                              */
/*         SD Samuel D�om (sdeom@epadesa.fr)                              */
/*         VD Vianney Dugrain (vdugrain@epadesa.fr)                       */

/* Pour fonctionner il faut inclure pr�alablement les boites � outils     */
/*  epTexteOutils                                                         */
/*  epNumOutils                                                           */
/*  epRalOutils                                                           */

/* Liste des routines                                                     */
/*  AjCsvToEpl(�prc_csv,�prc_liste,�cas) Extrait une liste du csv et 	  */
/*		   ajoute les rallonges au composant liste correspondant		  */
/*         fait appel � AjLgnLst									      */
/*         derni�re modification : 01 10 2013 (SD)                        */
/*  AjLgnLst(�nom_liste,�V,�Q,�cas) Ajoute une ligne � un 	  			  */
/*		   composant liste												  */
/*         fait appel � EcritTxtRal de la boite � outils epTexteOutils    */
/*         derni�re modification : 18 12 2012 (VD)                        */
/*  CreerLst(�prc_nom,�prc_desc,�temp,�prc_mat,�type_v,�type_q) 		  */
/*		   Cr�e un composant liste vide sur le matricule contenu dans 	  */
/*		   �prc_mat														  */
/*         fait appel � EcritTxtRal de la boite � outils epTexteOutils    */
/*         derni�re modification : 29 11 2012 (VD)                        */
/*  ETlstPRC(�et,�nom_liste,�nom_prc) Renvoie la valeur d'une liste pour  */
/*         un rang donn�                                                  */
/*         derni�re modification : 27 11 2012 (SD)                        */
/*	MajCsvToEpl(�prc_csv,�cas)	Importe les listes d'un csv dans les	  */
/*		   composants epL												  */
/*         fait appel � AjCsvToEpl et CreerListe					      */
/*         derni�re modification : 18 02 2012 (VD)                        */
/*	QtoV(�prc_q,�prc_v,�nom_liste)	Recherche la premi�re valeur          */
/*         correspondante � une �tiquette donn�e                          */
/*         derni�re modification : 14 03 2012 (SD)                        */
/*  SELcmpLST(�nom_liste,�nom_prc) S�lectionne un composant liste         */
/*         � partir de son nom                                            */
/*         derni�re modification : 25 02 2013 (SD)                        */


/* S�rie de proc�dures utiles                                             */
proc,Lst=epL /* radical des composants listes */

rout,SELcmpLST(�nom_liste,�nom_prc)
/* Permet de d'instancier la proc�dure dont le nom est contenu dans       */
/*  �nom_prc pour qu'elle contienne le matricule du composant de liste    */
/*  dont le nom est pass� dans la variable �nom_liste                     */
/* Si aucune liste ne correspond renvoie la valeur "vide"                 */
{
  var,�mat
  �mat=vide
  /* on cherche le composant */
  /* on g�re le maximum de cas en envisageant les `` ou non */
  !EpTemp=[Lst]*!test(&t0:nom==[�nom_liste])
  !EpTemp<[Lst]*!test(&t0:nom=="[�nom_liste]")
  if,"JtDebug=1"
  {
    sell,!EpTemp
  }
  /* on teste qu'il y en a qu'un + gestion des erreurs */
  /* on v�rifie qu'il y a bien autant de rallonges Q que V */
  runs,!EpTemp
  {
    �mat=[mm]
  }
  if,"JtDebug=1"
  {
    impr,mat(�mat)=[�mat]
  }
  !sele,!EpTemp	
  [�nom_prc]=[�mat]
  if,"JtDebug=1"
  {
    impr,nom_prc(�nom_prc)=[�nom_prc]
  }
}

rout,ETlstPRC(�et,�nom_liste,�nom_prc)
/* Permet d'instancier la proc�dure de nom �nom_prc avec la valeur de rang */
/*  �et de la liste dont le nom est pass� dans la variable �nom_liste      */
/* Renvoie la valeur "vide" si aucune valeur n'est trouv�e                 */
{
  var,�liste,�val
  �val=vide
  
  run,SELcmpLST([�nom_liste],�liste) /* selection du bon composant liste et stockage dans le composant �liste */
  if,"�liste><`vide`"
  {
    �val=[[�liste]&V[�et]:]
  }
  [�nom_prc]=[�val]
}

rout,CreerLst(�prc_nom,�prc_desc,�temp,�prc_mat,�typev,�typeq)
/* Permet de cr�er un composant liste vide correpondant � la liste dont le  */
/*  nom est contenu dans la proc�dure de nom �prc_nom, le commentaire dans  */
/*  la proc�dure dont le nom indiqu� dans �prc_desc, et le caract�re        */
/*  temporaire indiqu�e par la valeur de �temp (0->p�renne, autre->temp.)   */
/*  �typev indique l'alias du type de donn�es des valeurs, �typeq celui des */
/*  �tiquettes                                                              */
/*	Renvoie le matricule par la proc�dure �mat								*/
/* Par d�faut le composant est temporaire                                   */
{
  var,�temp_b,�temp_typev,�temp_typeq,�b_typev,�b_typeq,�mat
  
  �temp_b=1 /* Par d�faut le composant est temporaire */
  �temp_typev=[EpType0] /* Par d�faut les valeurs sont du texte */
  �temp_typeq=[EpType0] /* Par d�faut les �tiquettes sont du texte */
  
  if,"�temp==`0`"
  {
    �temp_b=0
  }
  
  run,EstUnType([�typev],�b_typev)
  if,"�b_typev"
  {
    �temp_typev=[�typev]
  }
  
  run,EstUnType([�typeq],�b_typeq)
  if,"�b_typeq"
  {
    �temp_typeq=[�typeq]
  }
  
  [�prc_mat]=[ml(Lst)]
  �mat=[[�prc_mat]]
  [�mat]&T2:temp=[�temp_b],typeq=[�temp_typeq],typev=[�temp_typev]
  
  /*	ICI Tester le type de la rallonge et ajouter avec la fonction appropri�e	*/
  run,EcritTxtRal([�prc_nom],[�mat],T0,nom)
  run,EcritTxtRal([�prc_desc],[�mat],T1,com)
}

rout,AjLgnLst(�nom_liste,�V,�Q,�cas)
/*	Prend en entr�e une liste dont le nom est stock� dans la proc�dure 		*/
/*		�nom_liste, un attribut dont le nom est stock� dans �v, et 			*/
/*		un attribut dont le nom est stock� dans �q, et ajoute une 			*/
/*		rallonge V et Q au composant correspondant � la liste.				*/
/*  �cas peut prendre les valeurs suivantes                                 */
/*   -1 ajoute purement et simplement                                       */
/*    0 ajoute si aucune entr�e avec m�me V et m�me Q                       */
/*    1 ajoute si aucune entr�e avec m�me V                                 */   
/*    2 ajoute si aucune entr�e avec m�me Q                                 */
/*    3 ajoute si aucune entr�e avec m�me V ou m�me Q                       */
{
  var,�mat_liste,�i,�type_V,�type_Q,�bool,�V_exis,�Q_exis
  �V_exis=0
  �Q_exis=0
  var,�tmp,�tmpV,�tmpQ,�ajout
  var,�cas0
  var,�V_formate,�Q_formate
  /*	Stockent les valeurs qui seront ajout�es aux rallonges				*/

  if,"[[�cas]>3]#[[�cas]<-1]"
  {
    �cas0=-1
  }
  else
  {
    �cas0=[�cas]
  }
  
  run,SELcmpLST([�nom_liste],�mat_liste)
  if,"�mat_liste><`vide`"
  {
    runr,[�mat_liste],V
	/*	On regarde s'il existe une m�me rallonge V							*/
	{
	  run,DelChr34([rr]:,�tmp)
	  run,DelChr34([�V],�tmpV)
	  if,"[�tmp==�tmpV]@[�V_exis=0]"
	  {
	    �V_exis=1
	  }
	}
	
	runr,[�mat_liste],Q
	/*	On regarde s'il existe une m�me rallonge Q							*/
	{
	  run,DelChr34([rr]:,�tmp)
	  run,DelChr34([�Q],�tmpQ)
	  if,"[�tmp==�tmpQ]@[�Q_exis=0]"
	  {
	    �Q_exis=1
	  }
	}
	
	if,"�cas=-1"
	/*	On d�finit le bool�en �ajout selon qu'on ajoute ou non, selon les cas	*/
	{
	  �ajout=1
	}
	else
	{
	  if,"[�Q_exis]@[�V_exis]"
	  {
	    �ajout=0
	  }
	  else
	  {
	    if,"[�Q_exis]@[�cas>1]"
		{
		  �ajout=0
		}
		else
		{
		  if,"[�V_exis]@[[�cas=1]#[�cas=3]]"
		  {
			�ajout=0
		  }
		  else
		  {
		    �ajout=1
		  }
		}
	  }
	}
	
	if,"�ajout=1"
	{
      �type_V=[[�mat_liste]&T2:typev]
	  run,EstUnType([�type_V],�bool)
	  if,"�bool=0"
	  {
	    �type_V=[EpType0]
	  }
	  
	  �type_Q=[[�mat_liste]&T2:typeq]
	  run,EstUnType([�type_Q],�bool)
	  if,"�bool=0"
	  {
	    �type_Q=[EpType0]
	  }
	  run,EcritRal([�V],[�mat_liste],V,,[�type_V])
	  run,EcritRal([�Q],[�mat_liste],Q,,[�type_Q])
	}
  }
}

rout,AjCsvToEpl(�prc_csv,�prc_liste,�cas)
/*	Import des lignes d'une liste depuis un csv vers le composant epL corresp.	*/
/*	Le fichier doit �tre structur� �tre de la forme : 							*/
/*			nom_de_la_liste;valeur;etiquette (T0;Vi;Qi)							*/
/*  �cas peut prendre les valeurs suivantes (cf AjLgnLst)                       */
/*   -1 ajoute purement et simplement                    	                    */
/*    0 ajoute si aucune entr�e avec m�me V et m�me Q        	                */
/*    1 ajoute si aucune entr�e avec m�me V                      	            */   
/*    2 ajoute si aucune entr�e avec m�me Q                          	        */
/*    3 ajoute si aucune entr�e avec m�me V ou m�me Q                    	    */
{
  /*	D�claration des variables :												*/
  /*		�t,�v,�q -> Rallonges T, V et Q du composant cr��					*/
  var,�t,�v,�q,�mat,�type_v,�type_q
  �mat=0
  var,�liste
  �liste=[�prc_liste]
  run,SELcmpLST([�prc_liste],�mat)	/*	On selectionne le composant */
  if,"�mat><`vide`"
  {
    runf,[�prc_csv],`�t;�v;�q` /*	On parcourt le fichier csv	*/
    {
	  if,"�t==�prc_liste"
	  {
	    if,"�v==``"
	    /*	On g�re les cas o� �v ou �q est vide	*/
	    {
	      if,"�q><``"
	      /*	Si �v uniquement est vide, il prend la valeur "vide"	*/
	      {
	        �v=vide
	      }
	    }
	    else
	    {
	      if,"�q==``"
	      /*	Si �q uniquement est vide, il prend la valeur de �v entre guillemets	*/
	      {
	    	  run,FormateTexte(�v,�q)
	      }
		  if,"�v==`typev`"
	      /* Si �v est le mot cl� "typev" �q devient vide de mani�re � sauter la ligne  */
	      {
	    	  �q=
	      }
		  if,"�v==`typeq`"
	      /* Si �v est le mot cl� "typeq" �q devient vide de mani�re � sauter la ligne  */
	      {
	    	  �q=
	      }
		  if,"�v==`_`"
	      /* Si �v est le mot cl� "_" �q devient vide de mani�re � sauter la ligne  	*/
	      {
	    	  �q=
	      }
	    }
	    
	    if,"�q><``"
	    /*	Si �q n'est pas vide, on traite la ligne	*/
	    {
	      run,AjLgnLst([�prc_liste],�v,�q,[�cas])
	    }
	  }
    }
  }
}

rout,MajCsvToEpl(�prc_csv,�cas)
/*	Fonction de mise � jour des composants epL � partir d'un csv						*/
/*	Trouve les lignes de titre (underscores), et v�rifie que le composant existe		*/
/*		�prc_csv = nom de la proc�dure qui contient le nom chemin vers le fichier csv	*/
/*	Selon les cas : 																	*/
/*		�cas=0 -> Si la liste existe, on ne fait rien									*/
/*		�cas=1 -> Si la liste existe, on la remplace									*/
/*		�cas=9-10-11-12 -> Si la liste existe, on la met � jour (cf AjLgnLst)			*/
/*		�cas=2 -> Si la liste existe, on l'ajoute quand m�me							*/
{

  if,"[[�cas]>2]@[[�cas]<9]@[[�cas]>12]"
  {
    /*	Par d�faut, on consid�re le cas = 0												*/
    �cas=0	
  }
  
  var,�t,�v,�q
  var,�ta,�va,�qa
  
  /* Bool�en d'existence de la liste trouv�e 											*/
  var,�lExist
  
  /* Nombre de listes similaires existantes												*/
  var,�nbExist
  var,�underscore
  var,�mat
  var,�typev,�typeq,�temp,�prc_tv,�prc_tq
  
  /* Par d�faut les valeurs et les �tiquettes sont du texte 							*/
  �typev=[EpType0] 							
  �typeq=[EpType0] 				
  
  /* Par d�faut le cmp n'est pas temporaire	*/  
  �temp=0									
  
  �lExist=0
  �underscore=_
  �prc_tv=typev
  �prc_tq=typeq

  runf,[�prc_csv],`�t;�v;�q`
  {
    if,"�v==�underscore"
    {
	  runf,[�prc_csv],`�ta;�va;�qa`
	  {
		if,"[�ta==�t]@[�va==�prc_tv]"
		{
		  �typev=[�qa]
		}
		if,"[�ta==�t]@[�va==�prc_tq]"
		{
		  �typeq=[�qa]
		}
	  }
	  run,SELcmpLST([�t],�mat)
	  if,"�mat==`vide`"
	  /*	Si la liste n'existe pas, on la cr��e	*/
	  {
	    run,CreerLst(�t,�q,[�temp],�mat,[�typev],[�typeq])
		run,AjCsvToEpl([�prc_csv],[�t],-1)
	  }
	  else
	  /*	Sinon, on teste le cas 					*/
	  {
	    if,"[�cas]=1"
		{
		  !cmpe,[�mat] /* on supprime le composant liste */
	      run,CreerLst(�t,�q,[�temp],�mat,[�typev],[�typeq]) /* on le recr�e */
		  run,AjCsvToEpl([�prc_csv],[�t],-1)
		}
		else
		{
		  if,"[�cas]=2"
		  {
			run,CreerLst(�t,�q,[�temp],�mat,[�typev],[�typeq])
		    run,AjCsvToEpl([�prc_csv],[�t],-1)
		  }
		  else
		  {
		    if,"[�cas]<>0"
			{
			  var,�scas
			  �scas=[�cas-10]
			  run,AjCsvToEpl([�prc_csv],[�t],[�scas])
			}
		  }
		}
	  }
    }
  }
}

rout,QtoV(�prc_q,�prc_v,�nom_liste)
/* Fonction permettant d'obtenir la premi�re valeur correspondant � une �tiquette pour	*/
/*	    une liste donn�e. La valeur de l'�tiquette recherch�e est contenue dans la		*/
/*		proc�dure �prc_q, le nom de la liste est contenu dans �nom_liste et le r�sultat	*/
/*	    sera enregistr�e dans la proc�dure dont le nom est donn�e dans �prc_v			*/
/* Si aucune valeur n'est trouv�e, renvoie le mot cl� "vide"                            */
{
  var,�v,�liste,�typeq,�text,�test
  �v=vide
  �text="txt"
  
  run,SELcmpLST([�nom_liste],�liste) /* selection du bon composant liste et stockage dans le composant �liste */
  
  if,"�liste><`vide`"
  {
    �typeq=[[�liste]&T2:typeq]
	run,PrcTexte(�typeq)
	if,"�typeq==�text"
    {
      run,FormateTexte([�prc_q],�test)
    }
	else
	{
	  �test={[�prc_q]}
	}
	
    runr,comp=[�liste],type=V
    {
      if,"[mm]&Q[ii]:==�test"
	  {
	    �v=[[mm]&V[ii]:]
		[fi]
	  }
    }
  }
  [�prc_v]=[�v]
}

rout,VtoQ(�prc_v,�prc_q,�nom_liste)
/* Fonction permettant d'obtenir la premi�re �tiquette correspondant � une valeur pour	*/
/*	    une liste donn�e. La valeur de l'�tiquette recherch�e est contenue dans la		*/
/*		proc�dure �prc_v, le nom de la liste est contenu dans �nom_liste et le r�sultat	*/
/*	    sera enregistr�e dans la proc�dure dont le nom est donn�e dans �prc_q			*/
/* Si aucune valeur n'est trouv�e, renvoie le mot cl� "vide"                            */
{
  var,�q,�liste,�typev,�text,�test
  �q=vide
  �text="txt"
  
  run,SELcmpLST([�nom_liste],�liste) /* selection du bon composant liste et stockage dans le composant �liste */
  
  if,"�liste><`vide`"
  {
    �typev=[[�liste]&T2:typev]
	run,PrcTexte(�typev)
	if,"�typev==�text"
    {
      run,FormateTexte([�prc_v],�test)
    }
	else
	{
	  �test={[�prc_v]}
	}
	
    runr,comp=[�liste],type=V
    {
      if,"[mm]&V[ii]:==�test"
	  {
	    �q=[[mm]&Q[ii]:]
		[fi]
	  }
    }
  }
  [�prc_q]=[�q]
}