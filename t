
proc cyf2byt(byte n,c) 
byte cros=[48]

cros=cros+c
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

cyf2byt(4,0)
cyf2byt(120,96)
cyf2byt(208,128)
cyf2byt(250,160)

a=getd(7)

RETURN
