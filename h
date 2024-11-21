
INCLUDE "H6:VARS.ACT"
INCLUDE "H6:SYS.ACT"
INCLUDE "H6:LITFUN.ACT"
INCLUDE "H6:FNTGR.ACT"
INCLUDE "H6:ENEMY.ACT"
INCLUDE "H6:LEVGEN.ACT"
INCLUDE "H6:SKROL.ACT"






; procedura glowna -------------------------------------------------------
PROC MAIN()
BYTE jdir,x,y,x2,y2,xyw

    InitChar()
	InitCol()
	PlanAdr=PEEKC(@plan)
	VRam=PEEKC(@vramtab)
	text=PEEKC(@texts)
	txt2adr=PEEKC(@skroltxt)
	

	DO ;glowan petla
	DLset(1)
	heroS(0)=3 heroS(1)=0 heroS(2)=7 heroS(3)=7 heroS(4)=20 heroS(5)=20
	LevelCurr=1
	lic=0 lic2=0 gtic=0
	MOVEBLOCK(scrmem+640+40+6,text,5)
	MOVEBLOCK(scrmem+640+60+9,text+5,4)

	POKE(77,0)
	DO
	lic2==+1

	if lic2<4 then txt2() fi
	if lic2=50 then lic2=0 fi


	UNTIL Joy()>16 OR CH=33 
	OD

	
	DLset(2)
    
	

	;scroll -----------------



	ClsGr() 
	
    DO
       if heroS(0)=0 THEN
	   MOVEBLOCK(scrmem+80+3,text+12,5)
	   MOVEBLOCK(scrmem+100+3,text+17,5)
	   pause(200)
	   EXIT
	   fi
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
			heroS(4)=heroS(5)
			heroS(2)=heroS(3)
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

            IF xyw=2 or xyw=3+64 or xyw=6+64 or xyw=8+192 or xyw=7+192 or xyw=4 or xyw=5 THEN 
				
				for i=0 to rc-1
					do
						IF ev(i)>0 THEN
							if ex(i)=x2 and ey(i)=y2 then

								if ea(i)>heroS(2) then ;atak < obrony wroga
										ea(i)=ea(i)-heroS(2)  
										POKE(712,$D0) pause(10) POKE(712,0)
									elseif ea(i)<=heroS(2) then ;atak > obrony wroga
										ea(i)=0 ev(i)=0
										POKE(712,$D4) pause(10) POKE(712,0)
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
					heroS(4)==+1
					if heroS(4)>heroS(5) then heroS(5)=heroS(4) fi
					FI
			
				IF xyw=5 THEN ; atak
					SETIT(x2,y2,2)
					heroS(2)==+1
					if heroS(2)>heroS(3) then heroS(3)=heroS(2) fi
					FI
				
				IF xyw=3+64 THEN ; gold
					SETIT(x2,y2,2)
					heroS(1)==+1
					if heroS(1)>49 then
						heroS(0)==+1
						heroS(1)=0
						POKE(712,$FF)
						pause(15)
						POKE(712,0)
						fi
					FI
				
				IF xyw=6+64 THEN ; key
					SETIT(rit(2),rit(3),8+192)
					SETIT(rit(0),rit(1),2)
					FI
				
				IF xyw=8+192 THEN ;exit 
					LevelCurr==+1
					EXIT 
				   FI			   
			 
			 
			MapViz(hx,hy)
			if gtic=4 then EneMov() gtic=0 fi
			EneViz()
			Vram2Scr(0)
            HeroDrw()
			jdir=0
			gtic==+1
			IF CH=28 THEN EXIT FI
			POKE($0284,0) POKE(77,0)
       OD  
;---------------------------------------------	   
	   
	   
	
    plansza_pusta()
	IF CH=28 THEN EXIT FI
    OD
	CH=255
	OD
RETURN

