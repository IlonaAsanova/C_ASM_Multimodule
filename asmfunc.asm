section .rodata
    c1 dq 1.0
    c2 dq 0.5
    c3 dq 3.0
    c4 dq -1.0
    c5 dq 2.0
    c6 dq 6.0
    
section .bss
    tmp resq 1

section .text
    extern exp

GLOBAL F1
GLOBAL F2
GLOBAL F3
;;; Hi = dFi / dx
GLOBAL H1
GLOBAL H2
GLOBAL H3

F1: ;;; F1 = 3 / ((x - 1)^2 + 1)
    push ebp
    mov ebp, esp
    
    finit
    fld qword[c3]
    fld qword[ebp + 8]
    fsub qword[c1]
    fld st0
    fmulp ; st0 contain (x - 1)^2
    fadd qword[c1]
    fdivp
    
    mov esp, ebp
    pop ebp
    ret

H1: ;;; H1 = (6 - 6x) / ((x - 1)^2 + 1)^2
    push ebp
    mov ebp, esp
    
    finit
    fld qword[ebp + 8]
    fld qword[c6]
    fmulp
    fld qword[c4]
    fmulp
    fadd qword[c6]
    fld qword[ebp + 8]
    fsub qword[c1]
    fld st0
    fmulp
    fadd qword[c1]
    fld st0
    fmulp
    fdivp
    
    mov esp, ebp
    pop ebp
    ret

F2: ;;; F2 = sqrt(x + 0.5)
    push ebp
    mov ebp, esp
    
    finit
    fld qword[ebp + 8]
    fadd qword[c2]
    
    fsqrt    
    
    mov esp, ebp
    pop ebp
    ret
    
H2: ;;; H2 = 1 / (2 * sqrt(x + 0.5))
    push ebp
    mov ebp, esp
    
    finit
    fld1
    fld qword[ebp + 8]
    fadd qword[c2]
    fsqrt
    
    fld qword[c5]
    fmulp
    fdivp
    
    mov esp, ebp
    pop ebp
    ret
    
F3: ;;; F3 = exp(-x)
    push ebp
    mov ebp, esp
    and esp, -16
    
    finit
    fld qword[ebp + 8]
    fld qword[c4]
    fmulp
    fst qword[tmp]
    
    sub esp, 8
    push dword[tmp + 4]
    push dword[tmp]
    call exp
    add esp, 16
    
    mov esp, ebp
    pop ebp
    ret
    
H3: ;;; H3 = -exp(-x)
    push ebp
    mov ebp, esp
    and esp, -16
    
    finit
    fld qword[ebp + 8]
    fld qword[c4]
    fmulp
    fst qword[tmp]
    
    sub esp, 8
    push dword[tmp + 4]
    push dword[tmp]
    call exp
    add esp, 16
    
    fld qword[c4]
    fmulp
    
    mov esp, ebp
    pop ebp
    ret
