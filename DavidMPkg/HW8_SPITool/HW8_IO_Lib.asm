.code



;UINT64 IOReadCfgAsm(IN UINT64 bdfr);
IOReadCfgAsm PROC PUBLIC
  mov dx, 0cf8h
  mov rax, rcx
  out dx, rax
  
  mov dx, 0cfch
  in eax, dx
   ret
IOReadCfgAsm ENDP 


END
