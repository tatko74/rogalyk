
INCLUDE "H6:VARS.ACT"
INCLUDE "H6:SYS.ACT"
INCLUDE "H6:LITFUN.ACT"
INCLUDE "H6:FNTGR.ACT"
INCLUDE "H6:ENEMY.ACT"
INCLUDE "H6:LEVGEN.ACT"
INCLUDE "H6:SKROL.ACT"



PROC MapViz(int x,y)
	BYTE x3,y3
    CARD plaoff
    INT ofss
    ii=9
    IF x<4 THEN tx=x x3=4-x ELSE tx=4 x3=0 FI
    IF y<4 THEN ty=y y3=4-y ELSE ty=4 y3=0 FI
    IF x>mx-4 THEN ii=mx+5-x FI
    ofss=PosP(x-tx,y-ty)
    FOR i=0 TO 8-y3
        DO
        plaoff=(ofss+(i*(mx+1)))
		MOVEBLOCK(VRam+x3+((i+y3)*9),PlanAdr+plaoff,ii-x3)
        OD
RETURN



PROC Vram2Scr()
ii=0
FOR i=21 TO 181 STEP 20
DO
MOVEBLOCK(scrmem+i,VRam+ii,9)
ii=ii+9
OD

ZERO(VRam,80)
RETURN

PROC HeroDrw()
POKE(scrmem+105,9+192)   
RETURN



; procedura glowna -------------------------------------------------------
PROC MAIN()
BYTE jdir,x,y,x2,y2,xyw

    
	;Close (7)
	;Open (7,"K:",4,0)	
	
    InitChar()
    InitCol()
	PlanAdr=PEEKC(@plan)
	VRam=PEEKC(@vramtab)
	text=PEEKC(@texts)
	;scroll -----------------
	meloadr=PEEKC(@skroltxt)
	licznik=0

	;POKEC(552,$XXXX) ; odwrocone miejscami po nazwie procki i C0
	;POKE(538,8)
	
	ClsGr() 
    DO
       Generator_Poziomu()
	   ;Generator_Enemy()
       ramka_pusta()

		hx=rx(0) hy=ry(0) ; wspol. bohatera
        x2=hx y2=hy
		
		MapViz(x2,y2) 
		EneMov()
		EneViz()
		
		Vram2Scr()
		POSITION(12,1)
		PutD(6,108) PutD(6,118) PutD(6,108) PutD(6,2)
		PRINTBD(6,LevelCurr)
		
        HeroDrw()
;---------------------------------------------		
        DO
            jdir = Joy(0)
			IF jdir=14 AND hy>0  THEN y2=hy-1 FI ;u
            IF jdir=13 AND hy<my THEN y2=hy+1 FI ;d
            IF jdir=11 AND hx>0  THEN x2=hx-1 FI ;l
            IF jdir=7  AND hx<mx THEN x2=hx+1 FI ;r

            IF jdir=10 AND hy>0 AND hx>0 THEN y2=hy-1 x2=hx-1 FI ;ul
            IF jdir=6 AND hy>0 AND hx<mx THEN y2=hy-1 x2=hx+1 FI ;ur
			
			IF jdir=9 and hy<my AND hx>0 THEN y2=hy+1 x2=hx-1 FI ;dl
            IF jdir=5 and hy<my AND hx<mx THEN y2=hy+1 x2=hx+1 FI ;dr
			
			xyw=GETIT(x2,y2)
            IF xyw=2 THEN 
				hx=x2 hy=y2 
				ELSE
				y2=hy x2=hx
		       FI
			IF xyw=06+192 THEN 
                SETIT(rit(2),rit(3),08+64)
                SETIT(rit(0),rit(1),2)
				y2=hy x2=hx
                FI
            IF xyw=08+64 THEN 
				LevelCurr==+1
				EXIT 
               FI			   
			   
			MapViz(x2,y2)
			EneMov()
			EneViz()
			Vram2Scr()
            HeroDrw()
			jdir=0
       OD  
;---------------------------------------------	   
	   
	   
	   ;stop()
    plansza_pusta()
    OD
	;Close (7)
RETURN

