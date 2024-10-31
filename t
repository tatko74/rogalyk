BYTE CH=$02FC, FK=$D01F

PROC MAIN()
byte test,test2
CH=255 
DO 

;test=CH
;if test<>255 and test<>28 then 
;		printb(test) 
;		CH=255 
;elseif test=28 then 
;	exit 
;fi

test2=FK
;if test2<>8 then 
		printb(test2) 
		FK=8 
;fi



OD

RETURN
