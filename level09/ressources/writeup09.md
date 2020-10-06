# LEVEL 09

### Reconnaissance

Comme pour les niveaux précédent, on trouve un binaire qu'on va tester et un fichier token

```
level09@SnowCrash:~$ ./level09 00000000
01234567
level09@SnowCrash:~$ ./level09 aaaaaaaa
abcdefgh
level09@SnowCrash:~$ cat token 
f4kmm6p|=�p�n��DB�Du{��
```
On remarque que le programme prend un paramètre (Une chaine de caractère) et incrémente les elements de cette chaine en fonction de leurs position.

### Exploitation

On va donc utilisé python pour cette epreuve:
- On va récupéré le contenu du fichier token
- On va reproduire le comportement du binaire mais en décrémentant.

```
level09@SnowCrash:~$ python
Python 2.7.3 (default, Jun 22 2015, 19:43:34) 
[GCC 4.6.3] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> with open("token", "r") as f:
...     for line in f:
...             s = line
... 
>>> s
'f4kmm6p|=\x82\x7fp\x82n\x83\x82DB\x83Du{\x7f\x8c\x89\n'
>>> i = 0
>>> tmp = ""
>>> for i, v in enumerate(s):
...     tmp += str(chr(ord(v) - i))
... 
Traceback (most recent call last):
  File "<stdin>", line 2, in <module>
ValueError: chr() arg not in range(256)
>>> tmp
'f3iji1ju5yuevaus41q1afiuq'

level09@SnowCrash:~$ ./level09 f3iji1ju5yuevaus41q1afiuq > /tmp/test && diff token /tmp/test
level09@SnowCrash:~$ su flag09
Password: 
Don't forget to launch getflag !
flag09@SnowCrash:~$ getflag
Check flag.Here is your token : s5cAJpM8ev6XHw998pRWG728z
```
