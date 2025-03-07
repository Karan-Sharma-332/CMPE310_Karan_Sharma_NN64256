; Hamming Distance Calculator (Bit-Level)
; CMPE 310 Project 1

section .data
    prompt1 db "Enter first string: ", 0
    prompt1_len equ $ - prompt1
    prompt2 db "Enter second string: ", 0
    prompt2_len equ $ - prompt2
    result_msg db "Hamming Distance: ", 0
    result_len equ $ - result_msg
    newline db 10, 0
    
section .bss
    string1 resb 256    ; Buffer for first string (255 chars + null)
    string2 resb 256    ; Buffer for second string (255 chars + null)
    distance resd 1     ; Store the hamming distance
    temp resb 10        ; Temp buffer for number output

section .text
global _start

_start:
    ; Print first prompt
    mov eax, 4          ; sys_write
    mov ebx, 1          ; stdout
    mov ecx, prompt1
    mov edx, prompt1_len
    int 0x80

    ; Read first string
    mov eax, 3          ; sys_read
    mov ebx, 0          ; stdin
    mov ecx, string1
    mov edx, 255        ; max length
    int 0x80
    call remove_newline ; Remove trailing newline

    ; Print second prompt
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt2
    mov edx, prompt2_len
    int 0x80

    ; Read second string
    mov eax, 3
    mov ebx, 0
    mov ecx, string2
    mov edx, 255
    int 0x80
    call remove_newline

    ; Calculate Hamming distance
    xor esi, esi        ; Index counter
    xor edi, edi        ; Distance counter

compare_loop:
    mov al, [string1 + esi]
    mov bl, [string2 + esi]
    
    ; Check if we reached end of either string
    cmp al, 0
    je end_calc
    cmp bl, 0
    je end_calc
    
    ; Compare characters at bit level
    call bit_compare    ; Compare bits of al and bl, adds to edi
    inc esi             ; Move to next character
    jmp compare_loop

end_calc:
    mov [distance], edi ; Store final distance

    ; Print result message
    mov eax, 4
    mov ebx, 1
    mov ecx, result_msg
    mov edx, result_len
    int 0x80

    ; Convert distance to string and print
    mov eax, [distance]
    call print_number
    
    ; Print newline
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 0x80

    ; Exit program
    mov eax, 1          ; sys_exit
    xor ebx, ebx        ; return 0
    int 0x80

; Subroutine to remove newline from input
remove_newline:
    push eax
    push ecx
    xor ecx, ecx
find_nl:
    mov al, [ecx + string1]
    cmp al, 10          ; Check for newline
    je replace_nl
    cmp al, 0           ; Check for null
    je end_remove
    inc ecx
    jmp find_nl
replace_nl:
    mov byte [ecx + string1], 0
end_remove:
    pop ecx
    pop eax
    ret

; Subroutine to print a number
print_number:
    push eax
    push ebx
    push ecx
    push edx
    
    mov ebx, 10         ; Base 10
    xor ecx, ecx        ; Digit counter
    
convert_loop:
    xor edx, edx
    div ebx             ; Divide by 10
    add dl, '0'         ; Convert to ASCII
    mov [temp + ecx], dl
    inc ecx
    test eax, eax
    jnz convert_loop
    
    ; Print digits in reverse
print_loop:
    dec ecx
    mov eax, 4
    mov ebx, 1
    lea ecx, [temp + ecx]
    mov edx, 1
    int 0x80
    cmp ecx, 0
    jg print_loop
    
    pop edx
    pop ecx
    pop ebx
    pop eax
    ret

; Subroutine to compare bits of two characters (in al and bl)
; Adds the number of differing bits to edi
bit_compare:
    push eax
    push ebx
    push ecx
    
    xor al, bl          ; XOR to find differing bits (1 where bits differ)
    mov ecx, 8          ; 8 bits to check (since we're working with ASCII chars)
    xor ebx, ebx        ; Bit counter
    
count_bits:
    shl al, 1           ; Shift left to check each bit
    jnc next_bit        ; If carry is 0, no difference at this bit
    inc ebx             ; Increment counter if bit differs
next_bit:
    loop count_bits     ; Repeat for all 8 bits
    
    add edi, ebx        ; Add bit differences to total distance
    
    pop ecx
    pop ebx
    pop eax
    ret