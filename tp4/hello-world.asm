;ce fichier sera utiliser pour le helloworld.asm
;on definir les donnes statiques a utiliser
section  .data 

    hello db 'Hello World !',0
;debut de la zone de code
section .text 
    global _start 
    _start:
;n charge 4 dans le registre eax 4 numero de l'appel system utiliser pour ecrire  
    mov eax, 4
    mov ebx, 1
    mov ecx, hello
    mov edx, 13
    int 0x80
    mov  eax, 1
    xor ebx ,ebx
    int 0x80