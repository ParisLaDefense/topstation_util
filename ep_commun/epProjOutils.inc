/* version 0.1 du                                                         */
/*  derni�re modification :                                               */
/*         22 02 2013 (SD)                                                */
/*  auteur :                                                              */
/*         SD Samuel D�om (sdeom@epadesa.fr)                              */

/* Pour fonctionner il faut inclure pr�alablement les boites � outils :   */
/*  aucune boite � outils                                                 */


/* Liste des routines                                                     */
/*  AplDuClq Ouvre une fen�tre de s�lection de plusieurs composant pour   */
/*      y appliquer la fonction DuClq                                     */
/*        Derni�re modification : 25/01/2013                                  */

rout,Helmert(�prc_xo,�prc_yo,�prc_xf,�prc_yf,�tx,�ty,�fech,�gamma)
{
  var,�xo,�yo
  
  �xo=[�prc_xo]
  �yo=[�prc_yo]

  [�prc_xf]=[[(�xo*cos(�gamma,1)+�yo*sin(�gamma,1))*�fech+�tx]%3]
  [�prc_yf]=[[(-�xo*sin(�gamma,1)+�yo*cos(�gamma,1))*�fech+�ty]%3]
}