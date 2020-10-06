# LEVEL 00

On se connecte en ssh avec le password level00

On commence par la reconnaissance, notre cible est *flag00*. Partant de là, on chercher si un fichier fait partis de ce groupe:

```
level00@SnowCrash:~$ find / -group flag00 2>&-
/usr/sbin/john
/rofs/usr/sbin/john
level00@SnowCrash:~$ cat /usr/sbin/john 
cdiiddwpgswtgt
level00@SnowCrash:~$ cat /rofs/usr/sbin/john 
cdiiddwpgswtgt
```

On a 2 fichiers au contenu identique. Le mot de passe telle qu'elle ne fonctionne pas. Après quelques test, il s'avère que le chiffre de César est la solution.

Extrait de <a href="https://fr.wikipedia.org/wiki/Chiffrement_par_d%C3%A9calage">wikipédia</a>:

*En cryptographie, le chiffrement par décalage, aussi connu comme le chiffre de César ou le code de César (voir les différents noms), est une méthode de chiffrement très simple utilisée par Jules César dans ses correspondances secrètes (ce qui explique le nom « chiffre de César »).*

*Le texte chiffré s'obtient en remplaçant chaque lettre du texte clair original par une lettre à distance fixe, toujours du même côté, dans l'ordre de l'alphabet. Pour les dernières lettres (dans le cas d'un décalage à droite), on reprend au début. Par exemple avec un décalage de 3 vers la droite, A est remplacé par D, B devient E, et ainsi jusqu'à W qui devient Z, puis X devient A etc. Il s'agit d'une permutation circulaire de l'alphabet. La longueur du décalage, 3 dans l'exemple évoqué, constitue la clé du chiffrement qu'il suffit de transmettre au destinataire — s'il sait déjà qu'il s'agit d'un chiffrement de César — pour que celui-ci puisse déchiffrer le message. Dans le cas de l'alphabet latin, le chiffre de César n'a que 26 clés possibles (y compris la clé nulle, qui ne modifie pas le texte).*

Pour cela, le site dcode nous permet de le décodé facilement: https://www.dcode.fr/chiffre-cesar

Et le mot de passe est : **nottoohardhere**


 ```
 level00@SnowCrash:~$ su flag00
Password: 
Don't forget to launch getflag !
flag00@SnowCrash:~$ getflag 
Check flag.Here is your token : x24ti5gi3x0ol2eh4esiuxias
```

