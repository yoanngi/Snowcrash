# LEVEL 02

### Reconnaissance

Une fois connecter la l'utilisateur level02, on peux voir un fichier de capture reseau (pcap) nommer level02.pcap.

### Exploitation

On télécharge le fichier pour l'analyser:
```
$ scp level02.pcap yoginet@192.168.56.1:/home/yoginet/Documents/101/snowcrash/level02.pcap
```

Maintenant, 2 choix s'offre a nous:

- **la version graphique**
```
$ wireshark level02.pcap
```

- **la version en ligne de commande** (celle que nous allons utilisé):
```
$ tshark -r level02.pcap -T fields -e data
// permet de nous lister l'ensemble des paquets
1   0.000000 59.233.235.218 → 59.233.235.223 TCP 74 39247 → 12121 [SYN] Seq=0 Win=14600 Len=0 MSS=1460 SACK_PERM=1 TSval=18592800 TSecr=0 WS=128
2   0.000128 59.233.235.223 → 59.233.235.218 TCP 74 12121 → 39247 [SYN, ACK] Seq=0 Ack=1 Win=14480 Len=0 MSS=1460 SACK_PERM=1 TSval=46280417 TSecr=18592800 WS=32
3   0.000390 59.233.235.218 → 59.233.235.223 TCP 66 39247 → 12121 [ACK] Seq=1 Ack=1 Win=14720 Len=0 TSval=18592800 TSecr=46280417
[...]
```

Pour exporté les données brute en hexa:
```
$ tshark -r level02.pcap -T fields -e data
```

Meme chose mais converti:
```
$ tshark -r level02.pcap -T fields -e data |xxd -r -p
[...]
Linux 2.6.38-8-generic-pae (::ffff:10.1.1.2) (pts/10)
[...]
```

On peux voir:
```
wwwbugs login: lleevveellXX
Password: ft_wandrNDRelL0L
```
le password tel quel ne fonctionne pas, mais en faisant quelques essaie, on arrive a trouvé le bon:

```
$ su flag02
Password: ft_waNDReL0L
$ getflag
Check flag.Here is your token : kooda2puivaav1idi4f57q8iq
```
