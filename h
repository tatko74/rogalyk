
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



PROC Vram2Scr(byte ani)

if ani=1 then
ii=0
FOR i=21 TO 181 STEP 40
	DO
	MOVEBLOCK(scrmem+i,VRam+ii,9)
	ii=ii+9
	Pause(2)
	OD
fi

ii=0
FOR i=21 TO 181 STEP 20
	DO
	MOVEBLOCK(scrmem+i,VRam+ii,9)
	ii=ii+9
if ani=1 then Pause(1) fi	
	OD
ZERO(VRam,80)
RETURN

PROC HeroDrw()
if heroS(4)<>0 then
POKE(scrmem+105,9+192)   
else
POKE(scrmem+105,$1A)   
pause(5)
fi

RETURN

PROC Tablica()
	MOVEBLOCK(scrmem+12,text+9,3) cyf2(scrmem+17,LevelCurr,3) ;level
	poke(scrmem+52,9+192) cyf2(scrmem+53,heroS(0),1) ;ilo zyc
	poke(scrmem+56,3+192) cyf2(scrmem+57,heroS(1),1);gold
	poke(scrmem+92,5+192) cyf2(scrmem+93,heroS(2),1) ;atak
	poke(scrmem+96,32+192) cyf2(scrmem+97,heroS(3),2) 
	poke(scrmem+132,4+192) cyf2(scrmem+133,heroS(4),1) ;hp
	poke(scrmem+136,32+192) cyf2(scrmem+137,heroS(5),2) 
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
       Tablica()
	   
	   Generator_Poziomu()
       ramka_pusta()
		hx=rx(0) hy=ry(0) ; wspol. bohatera
        x2=hx y2=hy
		
		MapViz(x2,y2) 
		EneMov()
		EneViz()
		Vram2Scr(1)
        HeroDrw()

;---------------------------------------------		
        DO
		
	    Tablica()
		
            if heroS(4)<>0 then jdir = Joy()
			else
			heroS(0)==-1
			exit
			fi
			
			IF jdir=14 AND hy>0  THEN y2=hy-1 FI ;u
            IF jdir=13 AND hy<my THEN y2=hy+1 FI ;d
            IF jdir=11 AND hx>0  THEN x2=hx-1 FI ;l
            IF jdir=7  AND hx<mx THEN x2=hx+1 FI ;r
            IF jdir=10 AND hy>0 AND hx>0 THEN y2=hy-1 x2=hx-1 FI ;ul
            IF jdir=6 AND hy>0 AND hx<mx THEN y2=hy-1 x2=hx+1 FI ;ur
			IF jdir=9 and hy<my AND hx>0 THEN y2=hy+1 x2=hx-1 FI ;dl
            IF jdir=5 and hy<my AND hx<mx THEN y2=hy+1 x2=hx+1 FI ;dr
			 

			
			xyw=GETIT(x2,y2)

            IF xyw=2 or xyw=3+192 or xyw=6+192 or xyw=8+64 or xyw=7+64 or xyw=4 or xyw=5 THEN 
				
				for i=0 to rc-1
					do
						IF ev(i)>0 THEN
							if ex(i)=x2 and ey(i)=y2 then

								if ea(i)>heroS(2) then ea(i)=ea(i)-heroS(2)
									elseif ea(i)<=heroS(2) then ea(i)=0 ev(i)=0
								fi
							fi
						fi
					od
				
				hx=x2 hy=y2 
				else
				x2=hx y2=hy 
			FI
				
				IF xyw=4 THEN ; HP
					SETIT(x2,y2,2)
					heroS(4)==+5
					if heroS(4)>heroS(5) then heroS(5)=heroS(4) fi
					FI
			
				IF xyw=5 THEN ; atak
					SETIT(x2,y2,2)
					heroS(2)==+2
					if heroS(2)>heroS(3) then heroS(3)=heroS(2) fi
					FI
				
				IF xyw=3+192 THEN ; gold
					SETIT(x2,y2,2)
					heroS(1)==+1
					FI
				
				IF xyw=6+192 THEN ; key
					SETIT(rit(2),rit(3),8+64)
					SETIT(rit(0),rit(1),2)
					FI
				
				IF xyw=8+64 THEN ;exit 
					LevelCurr==+1
					EXIT 
				   FI			   
			 
			 
			MapViz(hx,hy)
			if gtic=5 then EneMov() gtic=0 fi
			EneViz()
			Vram2Scr(0)
            HeroDrw()
			jdir=0
			gtic==+1
       OD  
;---------------------------------------------	   
	   
	   
	   ;stop()
    plansza_pusta()
    OD
	;Close (7)
RETURN

