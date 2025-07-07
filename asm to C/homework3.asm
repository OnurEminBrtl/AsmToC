
section .data
    radius equ 15
    minimumDistance equ 4
    charOffset equ 60
    space db ' '
    nl db 10, 0         ; new line character definition
    linee equ 31
    
section .text

    global _start

_start:
    mov r12, 0                  ; y = 0
.loop_y:
    mov rax, r12
    sub rax, radius
    mov rdi, rax                ; deltaY = abs(y - radius)
    call _absoluteValue
    mov rax , rdx
    xor rdx, rdx
    mov r11, 0                  ; x = 0
    mov rcx, buffer
.loop_x:
    mov rbx, r11
    sub rbx, radius
    mov rdi, rbx                ; deltaX = abs(x - radius)
    call _absoluteValue
    mov rbx, rdx			;  deltaX
    xor rdx, rdx			
    mov rdx, rax			
    add rdx, rbx			;  deltaY + deltaX =dist
    xor rbx, rbx
    cmp rdx, minimumDistance   
    jle .greater                 ; if dist <= minimumDistance, jump to _greater and add space
    mov r14,charOffset
    add rdx , r14             
    mov [rcx],rdx
    jmp .loop_x_continue         ; continue with the next iteration of loop_x
.greater:
   mov dl,linee+1
   mov [rcx],dl

.loop_x_continue:
    inc r11                    ; x++
    lea rcx, [rcx+1]
    cmp r11, linee              
    jl .loop_x                  ; if x < size, jump to loop_x
    mov dl,10                   ;newline
    mov [rcx],dl
    mov rax, 1                 
    mov rdi, 1                 
    mov rsi, buffer                
    mov rdx, linee+1                 
    syscall                    ;print
    xor rcx,rcx                  
    inc r12                    ; y++
    cmp r12, linee             
    jl .loop_y                  ; if y < size, jump to loop_y

    mov rax, charOffset                
    xor rdi, rdi               
    syscall                    ; make the system call to exit
    
    global abs
_absoluteValue:
    cmp rdi, 0
    jg done1
    neg rdi
    mov rdx,rdi
    ret
done1:
    mov rdx,rdi
    ret

section .bss
	buffer: resb linee+1	

 