# LEVEL 13

### Reconnaissance

On se connecte sur l'user level13

```
level13@SnowCrash:~$ ls -la
total 20
dr-x------ 1 level13 level13  120 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level13 level13  220 Apr  3  2012 .bash_logout
-r-x------ 1 level13 level13 3518 Aug 30  2015 .bashrc
-rwsr-sr-x 1 flag13  level13 7303 Aug 30  2015 level13
-r-x------ 1 level13 level13  675 Apr  3  2012 .profile
level13@SnowCrash:~$ ./level13 
UID 2013 started us but we we expect 4242
```

Le programme cherche un certain uid pour nous donnée le token
On télécharge le binaire et on le reverse avec r2:

```
[0x080483c0]> pdf@main
            ; DATA XREF from entry0 @ 0x80483d7
┌ 94: int main (int argc, char **argv, char **envp);
│           ; var uid_t var_10h @ esp+0x4
│           ; var int32_t var_ch @ esp+0x8
│           0x0804858c      55             push ebp
│           0x0804858d      89e5           mov ebp, esp
│           0x0804858f      83e4f0         and esp, 0xfffffff0
│           0x08048592      83ec10         sub esp, 0x10
│           0x08048595      e8e6fdffff     call sym.imp.getuid         ; uid_t getuid(void)
│           0x0804859a      3d92100000     cmp eax, 0x1092
│       ┌─< 0x0804859f      742a           je 0x80485cb
│       │   0x080485a1      e8dafdffff     call sym.imp.getuid         ; uid_t getuid(void)
│       │   0x080485a6      bac8860408     mov edx, str.UID__d_started_us_but_we_we_expect__d ; 0x80486c8 ; "UID %d started us but we we expect %d\n"
│       │   0x080485ab      c74424089210.  mov dword [var_ch], 0x1092  ; [0x1092:4]=-1
│       │   0x080485b3      89442404       mov dword [var_10h], eax
│       │   0x080485b7      891424         mov dword [esp], edx        ; const char *format
│       │   0x080485ba      e8a1fdffff     call sym.imp.printf         ; int printf(const char *format)
│       │   0x080485bf      c70424010000.  mov dword [esp], 1          ; int status
│       │   0x080485c6      e8d5fdffff     call sym.imp.exit           ; void exit(int status)
│       │   ; CODE XREF from main @ 0x804859f
│       └─> 0x080485cb      c70424ef8604.  mov dword [esp], str.boe__ai0FB_.:_L6l_A__qJ_I ; [0x80486ef:4]=0x5d656f62 ; "boe]!ai0FB@.:|L6l@A?>qJ}I"
│           0x080485d2      e89dfeffff     call sym.ft_des
│           0x080485d7      ba09870408     mov edx, str.your_token_is__s ; 0x8048709 ; "your token is %s\n"
│           0x080485dc      89442404       mov dword [var_10h], eax
│           0x080485e0      891424         mov dword [esp], edx        ; const char *format
│           0x080485e3      e878fdffff     call sym.imp.printf         ; int printf(const char *format)
│           0x080485e8      c9             leave
└           0x080485e9      c3             ret
```

Pas de protection anti débug, pas de protection sur LD_PRELOAD, un appel a getuid.
```
│           0x08048595      e8e6fdffff     call sym.imp.getuid         ; uid_t getuid(void)
```

### Exploitation

On télécharge le binaire:
```
$ scp -P 4242 level13@192.168.56.103:/home/user/level13/level13 ./level13_binary
```

On va donc importé notre propre fonction:

```
$ cat ressources/getuid.c 
#include <unistd.h>

uid_t	getuid(void)
{
	return 0x1092;
}

uid_t	getgid(void)
{
	return 0x1092;
}

$ gcc -shared -fPIC -m32 ressources/getuid.c -o lib.so
$ env -i LD_PRELOAD=./lib.so ./level13_binary
your token is 2A31L79asukciNyi8uppkEuSx
```


