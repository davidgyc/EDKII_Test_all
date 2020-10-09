.code


;UINT64 readValue1(void);
readValue1 PROC PUBLIC
  mov dx, 0cf8h
  mov rax, 8000F800h
  out dx, rax
  
  mov dx, 0cfch
  in eax, dx
  sar eax,16
  and eax, 0FFh
  ret
readValue1 ENDP  


;UINT64 readValue2(IN UINT64 var1);
readValue2 PROC PUBLIC
; mov ax,?
; mov ds,ax
  mov al, [1000h]
  add al, cl ;al += var1
  ret
readValue2 ENDP  

;UINT64 readCmos(IN UINT64 offset);
readCmos PROC PUBLIC
  mov rax,rcx
  out 70h,al
  in al, 71h
  ret
readCmos ENDP  

;void writeCmos(IN UINT64 offset, IN UINT64 Data);
writeCmos PROC PUBLIC
  mov rax,rcx
  out 70h,al
  
  mov rax,rdx
  out 71h,al  
  ret
writeCmos ENDP  

;;UINT64 readDs(void);
readDs PROC PUBLIC
  mov ax,ds
  ret
readDs ENDP

;UINT64 readDs1000(void);
readDs1000 PROC PUBLIC
; mov ax,?
; mov ds,ax
  mov al, [1000h]
  ret
readDs1000 ENDP



;asmTest PROC PUBLIC
;  mov rax, rcx
;  mov rbx, rdx
;  mov rax, rbx
;  jle mexit
;  mov rax, rdx
;mexit:
;  ret
;asmTest ENDP
END
