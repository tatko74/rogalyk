
proc cyf2byt(byte n,c) 
byte cros=[48]
if c=0 then elseif c=1 then cros=cros+96 elseif c=2 then cros=cros+128 elseif c=3 then cros=cros+160 fi

putd(6,(n /100)+cros)  
putd(6,((n mod 100)/10)+cros)
putd(6,(n mod 10)+cros)
putde(6)

RETURN


PROC MAIN()
byte a

graphics(2)

POKE(708,21)  ;srodowisko - braz
POKE(709,200) ;dobre- zielone
POKE(710,72)  ;zle - fiolet
POKE(711,30)  ;ramka,hiro - zloty
POKE(712,0)   ;tlo

cyf2byt(1,0)
cyf2byt(20,1)
cyf2byt(100,2)
cyf2byt(305,3)

a=getd(7)

RETURN
