PUBLIC _timer0_init;
TIMERS SEGMENT CODE;
RSEG TIMERS;

_timer0_init:
	MOV		TMOD,#00H
	MOV		TL0,#00H
	MOV		TH0,#00H
	SETB	TR0
	SETB	ET0
	SETB	EA
	
END