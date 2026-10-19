    org #1000
    
    ld a,5
    
    PLY_STUFF = 1
    
    IFDEF PLY_STUFF
        ld a,6
    ENDIF
    
    UNDEF PLY_STUFF     ;Undefs an existing var.
    
    IFDEF PLY_STUFF
        ld a,7
    ENDIF
    
    UNDEF PLY_STUFF     ;Undefs an non-existing var.
    
    IFDEF PLY_STUFF
        ld a,8
    ENDIF
    
    IFDEF PLY_NEWSTUFF     ;Undefs a never-existed var.
        ld a,9
    ENDIF