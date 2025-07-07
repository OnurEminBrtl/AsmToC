section .data
    numbers: dq 321762410, 9, 2943018, 0, 19371039, 18, -76241, -208424
    nl: db 10
    neg: db "-"

section .text
    global _start

write9digits:
    push rbp
    mov rbp, rsp
    sub rsp, 8
    
    mov rax, 100000000
    mov [rbp-8], rax
    xor rax, rax
    mov [rbp-12], rax
    
    mov rdi, rdi  ; 
    cmp rdi, 0
    jge .not_negative
    mov rdi, -rdi
    mov byte [rbp-12], 1
    
.not_negative:
    cmp byte [rbp-12], 1
    jne .not_negative_label
    mov rsi, neg
    mov edx, 1
    mov eax, 4
    syscall

.not_negative_label:
    mov rcx, 9
    mov rsi, rsp
    mov rdx, 1
    
    .digit_loop:
        xor rax, rax
        div qword [rbp-8]
        add al, '0'
        mov [rsi], al
        inc rsi
        mov rax, [rbp-8]
        xor rdx, rdx
        div rax
        mov [rbp-8], rax
        loop .digit_loop
        
    mov rax, 1
    mov rdi, 1
    mov rdx, 9
    mov rsi, rsp
    syscall
    
    cmp byte [rbp-12], 1
    jne .exit
    mov rsi, nl
    mov edx, 1
    mov eax, 4
    syscall
    
.exit:
    leave
    ret

_start:
    mov rdi, numbers ; 
    mov rcx, 8
    
    .loop:
        mov rsi, [rdi] ; 
        call write9digits
        add rdi, 8
        loop .loop
        
    mov eax, 1
    xor ebx, ebx
    syscall
