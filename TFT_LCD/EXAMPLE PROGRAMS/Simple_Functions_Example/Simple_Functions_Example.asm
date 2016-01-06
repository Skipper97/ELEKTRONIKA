
_Write_Command:

;lcddriver.c,234 :: 		void Write_Command(unsigned int Wcommand)
;lcddriver.c,236 :: 		TFT_RD = 1;
	BSF         TFT_RD+0, BitPos(TFT_RD+0) 
;lcddriver.c,237 :: 		TFT_RS = 0;
	BCF         TFT_RS+0, BitPos(TFT_RS+0) 
;lcddriver.c,238 :: 		TFT_DP_Hi = wcommand >> 8;
	MOVF        FARG_Write_Command_Wcommand+1, 0 
	MOVWF       R0 
	CLRF        R1 
	MOVF        R0, 0 
	MOVWF       TFT_DP_Hi+0 
;lcddriver.c,239 :: 		TFT_DP_Lo = wcommand ;
	MOVF        FARG_Write_Command_Wcommand+0, 0 
	MOVWF       TFT_DP_Lo+0 
;lcddriver.c,240 :: 		TFT_WR = 0;
	BCF         TFT_WR+0, BitPos(TFT_WR+0) 
;lcddriver.c,241 :: 		TFT_WR = 1;
	BSF         TFT_WR+0, BitPos(TFT_WR+0) 
;lcddriver.c,242 :: 		}
L_end_Write_Command:
	RETURN      0
; end of _Write_Command

_Write_Data:

;lcddriver.c,244 :: 		void Write_Data(unsigned int Wdata)
;lcddriver.c,246 :: 		TFT_RD = 1;
	BSF         TFT_RD+0, BitPos(TFT_RD+0) 
;lcddriver.c,247 :: 		TFT_RS = 1 ;
	BSF         TFT_RS+0, BitPos(TFT_RS+0) 
;lcddriver.c,248 :: 		TFT_DP_Hi = Wdata >>8 ;
	MOVF        FARG_Write_Data_Wdata+1, 0 
	MOVWF       R0 
	CLRF        R1 
	MOVF        R0, 0 
	MOVWF       TFT_DP_Hi+0 
;lcddriver.c,249 :: 		TFT_DP_Lo = wdata;
	MOVF        FARG_Write_Data_Wdata+0, 0 
	MOVWF       TFT_DP_Lo+0 
;lcddriver.c,250 :: 		TFT_WR = 0;
	BCF         TFT_WR+0, BitPos(TFT_WR+0) 
;lcddriver.c,251 :: 		TFT_WR = 1 ;
	BSF         TFT_WR+0, BitPos(TFT_WR+0) 
;lcddriver.c,252 :: 		}
L_end_Write_Data:
	RETURN      0
; end of _Write_Data

_Write_Command_Data:

;lcddriver.c,254 :: 		void Write_Command_Data(unsigned int Wcommand,unsigned int Wdata)
;lcddriver.c,256 :: 		write_Command(Wcommand);
	MOVF        FARG_Write_Command_Data_Wcommand+0, 0 
	MOVWF       FARG_Write_Command_Wcommand+0 
	MOVF        FARG_Write_Command_Data_Wcommand+1, 0 
	MOVWF       FARG_Write_Command_Wcommand+1 
	CALL        _Write_Command+0, 0
;lcddriver.c,257 :: 		Write_Data(Wdata);
	MOVF        FARG_Write_Command_Data_Wdata+0, 0 
	MOVWF       FARG_Write_Data_Wdata+0 
	MOVF        FARG_Write_Command_Data_Wdata+1, 0 
	MOVWF       FARG_Write_Data_Wdata+1 
	CALL        _Write_Data+0, 0
;lcddriver.c,258 :: 		}
L_end_Write_Command_Data:
	RETURN      0
; end of _Write_Command_Data

_TFT_Set_Address:

;lcddriver.c,260 :: 		void TFT_Set_Address(unsigned int PX1,unsigned int PY1,unsigned int PX2,unsigned int PY2)
;lcddriver.c,262 :: 		Write_Command_Data(68,(PX2 << 8) + PX1 );  //Column address start2
	MOVLW       68
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVF        FARG_TFT_Set_Address_PX2+0, 0 
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CLRF        FARG_Write_Command_Data_Wdata+0 
	MOVF        FARG_TFT_Set_Address_PX1+0, 0 
	ADDWF       FARG_Write_Command_Data_Wdata+0, 1 
	MOVF        FARG_TFT_Set_Address_PX1+1, 0 
	ADDWFC      FARG_Write_Command_Data_Wdata+1, 1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,263 :: 		Write_Command_Data(69,PY1);      //Column address start1
	MOVLW       69
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVF        FARG_TFT_Set_Address_PY1+0, 0 
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVF        FARG_TFT_Set_Address_PY1+1, 0 
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,264 :: 		Write_Command_Data(70,Py2);  //Column address end2
	MOVLW       70
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVF        FARG_TFT_Set_Address_PY2+0, 0 
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVF        FARG_TFT_Set_Address_PY2+1, 0 
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,265 :: 		Write_Command_Data(78,PX1);      //Column address end1
	MOVLW       78
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVF        FARG_TFT_Set_Address_PX1+0, 0 
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVF        FARG_TFT_Set_Address_PX1+1, 0 
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,266 :: 		Write_Command_Data(79,PY1);  //Row address start2
	MOVLW       79
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVF        FARG_TFT_Set_Address_PY1+0, 0 
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVF        FARG_TFT_Set_Address_PY1+1, 0 
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,267 :: 		Write_Command(34);
	MOVLW       34
	MOVWF       FARG_Write_Command_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Wcommand+1 
	CALL        _Write_Command+0, 0
;lcddriver.c,268 :: 		}
L_end_TFT_Set_Address:
	RETURN      0
; end of _TFT_Set_Address

_TFT_Init:

;lcddriver.c,270 :: 		void TFT_Init()
;lcddriver.c,272 :: 		TFT_RD = 1;
	BSF         TFT_RD+0, BitPos(TFT_RD+0) 
;lcddriver.c,273 :: 		TFT_RST=1;
	BSF         TFT_RST+0, BitPos(TFT_RST+0) 
;lcddriver.c,274 :: 		delay_ms(5);
	MOVLW       13
	MOVWF       R12, 0
	MOVLW       251
	MOVWF       R13, 0
L_TFT_Init0:
	DECFSZ      R13, 1, 1
	BRA         L_TFT_Init0
	DECFSZ      R12, 1, 1
	BRA         L_TFT_Init0
	NOP
	NOP
;lcddriver.c,275 :: 		TFT_RST=0;
	BCF         TFT_RST+0, BitPos(TFT_RST+0) 
;lcddriver.c,276 :: 		delay_ms(15);
	MOVLW       39
	MOVWF       R12, 0
	MOVLW       245
	MOVWF       R13, 0
L_TFT_Init1:
	DECFSZ      R13, 1, 1
	BRA         L_TFT_Init1
	DECFSZ      R12, 1, 1
	BRA         L_TFT_Init1
;lcddriver.c,277 :: 		TFT_RST=1;
	BSF         TFT_RST+0, BitPos(TFT_RST+0) 
;lcddriver.c,278 :: 		delay_ms(15);
	MOVLW       39
	MOVWF       R12, 0
	MOVLW       245
	MOVWF       R13, 0
L_TFT_Init2:
	DECFSZ      R13, 1, 1
	BRA         L_TFT_Init2
	DECFSZ      R12, 1, 1
	BRA         L_TFT_Init2
;lcddriver.c,279 :: 		TFT_CS =0;
	BCF         TFT_CS+0, BitPos(TFT_CS+0) 
;lcddriver.c,280 :: 		Write_Command_Data(0x0000,0x0001);
	CLRF        FARG_Write_Command_Data_Wcommand+0 
	CLRF        FARG_Write_Command_Data_Wcommand+1 
	MOVLW       1
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,281 :: 		Write_Command_Data(0x0003,0xA8A4);
	MOVLW       3
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       164
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       168
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,282 :: 		Write_Command_Data(0x000C,0x0000);
	MOVLW       12
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	CLRF        FARG_Write_Command_Data_Wdata+0 
	CLRF        FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,283 :: 		Write_Command_Data(0x000D,0x800C);
	MOVLW       13
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       12
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       128
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,284 :: 		Write_Command_Data(0x000E,0x2B00);
	MOVLW       14
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       43
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,285 :: 		Write_Command_Data(0x001E,0x00B7);
	MOVLW       30
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       183
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,286 :: 		Write_Command_Data(0x0001,0x2B3F);
	MOVLW       1
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       63
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       43
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,287 :: 		Write_Command_Data(0x0002,0x0600);
	MOVLW       2
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       6
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,288 :: 		Write_Command_Data(0x0010,0x0000);
	MOVLW       16
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	CLRF        FARG_Write_Command_Data_Wdata+0 
	CLRF        FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,289 :: 		Write_Command_Data(0x0011,0x6070);
	MOVLW       17
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       112
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       96
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,290 :: 		Write_Command_Data(0x0005,0x0000);
	MOVLW       5
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	CLRF        FARG_Write_Command_Data_Wdata+0 
	CLRF        FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,291 :: 		Write_Command_Data(0x0006,0x0000);
	MOVLW       6
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	CLRF        FARG_Write_Command_Data_Wdata+0 
	CLRF        FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,292 :: 		Write_Command_Data(0x0016,0xEF1C);
	MOVLW       22
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       28
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       239
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,293 :: 		Write_Command_Data(0x0017,0x0003);
	MOVLW       23
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       3
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,294 :: 		Write_Command_Data(0x0007,0x0233);
	MOVLW       7
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       51
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       2
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,295 :: 		Write_Command_Data(0x000B,0x0000);
	MOVLW       11
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	CLRF        FARG_Write_Command_Data_Wdata+0 
	CLRF        FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,296 :: 		Write_Command_Data(0x000F,0x0000);
	MOVLW       15
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	CLRF        FARG_Write_Command_Data_Wdata+0 
	CLRF        FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,297 :: 		Write_Command_Data(0x0041,0x0000);
	MOVLW       65
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	CLRF        FARG_Write_Command_Data_Wdata+0 
	CLRF        FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,298 :: 		Write_Command_Data(0x0042,0x0000);
	MOVLW       66
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	CLRF        FARG_Write_Command_Data_Wdata+0 
	CLRF        FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,299 :: 		Write_Command_Data(0x0048,0x0000);
	MOVLW       72
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	CLRF        FARG_Write_Command_Data_Wdata+0 
	CLRF        FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,300 :: 		Write_Command_Data(0x0049,0x013F);
	MOVLW       73
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       63
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       1
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,301 :: 		Write_Command_Data(0x004A,0x0000);
	MOVLW       74
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	CLRF        FARG_Write_Command_Data_Wdata+0 
	CLRF        FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,302 :: 		Write_Command_Data(0x004B,0x0000);
	MOVLW       75
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	CLRF        FARG_Write_Command_Data_Wdata+0 
	CLRF        FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,303 :: 		Write_Command_Data(0x0044,0xEF95);
	MOVLW       68
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       149
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       239
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,304 :: 		Write_Command_Data(0x0045,0x0000);
	MOVLW       69
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	CLRF        FARG_Write_Command_Data_Wdata+0 
	CLRF        FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,305 :: 		Write_Command_Data(0x0046,0x013F);
	MOVLW       70
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       63
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       1
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,306 :: 		Write_Command_Data(0x0030,0x0707);
	MOVLW       48
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       7
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       7
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,307 :: 		Write_Command_Data(0x0031,0x0204);
	MOVLW       49
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       4
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       2
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,308 :: 		Write_Command_Data(0x0032,0x0204);
	MOVLW       50
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       4
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       2
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,309 :: 		Write_Command_Data(0x0033,0x0502);
	MOVLW       51
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       2
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       5
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,310 :: 		Write_Command_Data(0x0034,0x0507);
	MOVLW       52
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       7
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       5
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,311 :: 		Write_Command_Data(0x0035,0x0204);
	MOVLW       53
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       4
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       2
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,312 :: 		Write_Command_Data(0x0036,0x0204);
	MOVLW       54
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       4
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       2
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,313 :: 		Write_Command_Data(0x0037,0x0502);
	MOVLW       55
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       2
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       5
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,314 :: 		Write_Command_Data(0x003A,0x0302);
	MOVLW       58
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       2
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       3
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,315 :: 		Write_Command_Data(0x003B,0x0302);
	MOVLW       59
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       2
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       3
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,316 :: 		Write_Command_Data(0x0023,0x0000);
	MOVLW       35
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	CLRF        FARG_Write_Command_Data_Wdata+0 
	CLRF        FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,317 :: 		Write_Command_Data(0x0024,0x0000);
	MOVLW       36
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	CLRF        FARG_Write_Command_Data_Wdata+0 
	CLRF        FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,318 :: 		Write_Command_Data(0x0025,0x8000);
	MOVLW       37
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wdata+0 
	MOVLW       128
	MOVWF       FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,319 :: 		Write_Command_Data(0x004f,0x0000);
	MOVLW       79
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	CLRF        FARG_Write_Command_Data_Wdata+0 
	CLRF        FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,320 :: 		Write_Command_Data(0x004e,0x0000);
	MOVLW       78
	MOVWF       FARG_Write_Command_Data_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Data_Wcommand+1 
	CLRF        FARG_Write_Command_Data_Wdata+0 
	CLRF        FARG_Write_Command_Data_Wdata+1 
	CALL        _Write_Command_Data+0, 0
;lcddriver.c,321 :: 		Write_Command(0x0022);
	MOVLW       34
	MOVWF       FARG_Write_Command_Wcommand+0 
	MOVLW       0
	MOVWF       FARG_Write_Command_Wcommand+1 
	CALL        _Write_Command+0, 0
;lcddriver.c,322 :: 		TFT_CS =1;
	BSF         TFT_CS+0, BitPos(TFT_CS+0) 
;lcddriver.c,323 :: 		}
L_end_TFT_Init:
	RETURN      0
; end of _TFT_Init

_Set_color:

;lcddriver.c,326 :: 		unsigned int Set_color(unsigned int r,unsigned int g,unsigned int b)
;lcddriver.c,329 :: 		Hi(temp) = (R & 0xF8) | (G >> 5);
	MOVLW       248
	ANDWF       FARG_Set_color_r+0, 0 
	MOVWF       R4 
	MOVLW       5
	MOVWF       R2 
	MOVF        FARG_Set_color_g+0, 0 
	MOVWF       R0 
	MOVF        FARG_Set_color_g+1, 0 
	MOVWF       R1 
	MOVF        R2, 0 
L__Set_color105:
	BZ          L__Set_color106
	RRCF        R1, 1 
	RRCF        R0, 1 
	BCF         R1, 7 
	ADDLW       255
	GOTO        L__Set_color105
L__Set_color106:
	MOVF        R0, 0 
	IORWF       R4, 1 
;lcddriver.c,330 :: 		G = (G & 0x1C);
	MOVLW       28
	ANDWF       FARG_Set_color_g+0, 0 
	MOVWF       R1 
	MOVF        FARG_Set_color_g+1, 0 
	MOVWF       R2 
	MOVLW       0
	ANDWF       R2, 1 
	MOVF        R1, 0 
	MOVWF       FARG_Set_color_g+0 
	MOVF        R2, 0 
	MOVWF       FARG_Set_color_g+1 
;lcddriver.c,331 :: 		Lo(temp) = (G << 3) | (B >>3);
	MOVLW       3
	MOVWF       R0 
	MOVF        R1, 0 
	MOVWF       R3 
	MOVF        R0, 0 
L__Set_color107:
	BZ          L__Set_color108
	RLCF        R3, 1 
	BCF         R3, 0 
	ADDLW       255
	GOTO        L__Set_color107
L__Set_color108:
	MOVF        FARG_Set_color_b+0, 0 
	MOVWF       R0 
	MOVF        FARG_Set_color_b+1, 0 
	MOVWF       R1 
	RRCF        R1, 1 
	RRCF        R0, 1 
	BCF         R1, 7 
	RRCF        R1, 1 
	RRCF        R0, 1 
	BCF         R1, 7 
	RRCF        R1, 1 
	RRCF        R0, 1 
	BCF         R1, 7 
	MOVF        R0, 0 
	IORWF       R3, 1 
;lcddriver.c,332 :: 		return temp;
	MOVF        R3, 0 
	MOVWF       R0 
	MOVF        R4, 0 
	MOVWF       R1 
;lcddriver.c,333 :: 		}
L_end_Set_color:
	RETURN      0
; end of _Set_color

_TFT_Fill:

;lcddriver.c,336 :: 		void TFT_Fill(unsigned int color)
;lcddriver.c,339 :: 		TFT_CS  = 0;
	BCF         TFT_CS+0, BitPos(TFT_CS+0) 
;lcddriver.c,340 :: 		TFT_Set_Address(0,0,239,319);
	CLRF        FARG_TFT_Set_Address_PX1+0 
	CLRF        FARG_TFT_Set_Address_PX1+1 
	CLRF        FARG_TFT_Set_Address_PY1+0 
	CLRF        FARG_TFT_Set_Address_PY1+1 
	MOVLW       239
	MOVWF       FARG_TFT_Set_Address_PX2+0 
	MOVLW       0
	MOVWF       FARG_TFT_Set_Address_PX2+1 
	MOVLW       63
	MOVWF       FARG_TFT_Set_Address_PY2+0 
	MOVLW       1
	MOVWF       FARG_TFT_Set_Address_PY2+1 
	CALL        _TFT_Set_Address+0, 0
;lcddriver.c,341 :: 		Write_Data(color);
	MOVF        FARG_TFT_Fill_color+0, 0 
	MOVWF       FARG_Write_Data_Wdata+0 
	MOVF        FARG_TFT_Fill_color+1, 0 
	MOVWF       FARG_Write_Data_Wdata+1 
	CALL        _Write_Data+0, 0
;lcddriver.c,342 :: 		for(i = 0; i <= 319; i++)
	CLRF        TFT_Fill_i_L0+0 
	CLRF        TFT_Fill_i_L0+1 
L_TFT_Fill3:
	MOVF        TFT_Fill_i_L0+1, 0 
	SUBLW       1
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Fill110
	MOVF        TFT_Fill_i_L0+0, 0 
	SUBLW       63
L__TFT_Fill110:
	BTFSS       STATUS+0, 0 
	GOTO        L_TFT_Fill4
;lcddriver.c,344 :: 		for(j = 0; j <= 239; j++)
	CLRF        TFT_Fill_j_L0+0 
	CLRF        TFT_Fill_j_L0+1 
L_TFT_Fill6:
	MOVLW       0
	MOVWF       R0 
	MOVF        TFT_Fill_j_L0+1, 0 
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Fill111
	MOVF        TFT_Fill_j_L0+0, 0 
	SUBLW       239
L__TFT_Fill111:
	BTFSS       STATUS+0, 0 
	GOTO        L_TFT_Fill7
;lcddriver.c,346 :: 		TFT_WR = 0;
	BCF         TFT_WR+0, BitPos(TFT_WR+0) 
;lcddriver.c,347 :: 		TFT_WR = 1;
	BSF         TFT_WR+0, BitPos(TFT_WR+0) 
;lcddriver.c,344 :: 		for(j = 0; j <= 239; j++)
	INFSNZ      TFT_Fill_j_L0+0, 1 
	INCF        TFT_Fill_j_L0+1, 1 
;lcddriver.c,348 :: 		}
	GOTO        L_TFT_Fill6
L_TFT_Fill7:
;lcddriver.c,342 :: 		for(i = 0; i <= 319; i++)
	INFSNZ      TFT_Fill_i_L0+0, 1 
	INCF        TFT_Fill_i_L0+1, 1 
;lcddriver.c,349 :: 		}
	GOTO        L_TFT_Fill3
L_TFT_Fill4:
;lcddriver.c,350 :: 		TFT_CS  = 1;
	BSF         TFT_CS+0, BitPos(TFT_CS+0) 
;lcddriver.c,351 :: 		}
L_end_TFT_Fill:
	RETURN      0
; end of _TFT_Fill

_TFT_Box:

;lcddriver.c,354 :: 		void TFT_Box(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int color)
;lcddriver.c,357 :: 		TFT_CS  = 0;
	BCF         TFT_CS+0, BitPos(TFT_CS+0) 
;lcddriver.c,358 :: 		TFT_Set_Address(x1,y1,x2,y2);
	MOVF        FARG_TFT_Box_x1+0, 0 
	MOVWF       FARG_TFT_Set_Address_PX1+0 
	MOVF        FARG_TFT_Box_x1+1, 0 
	MOVWF       FARG_TFT_Set_Address_PX1+1 
	MOVF        FARG_TFT_Box_y1+0, 0 
	MOVWF       FARG_TFT_Set_Address_PY1+0 
	MOVF        FARG_TFT_Box_y1+1, 0 
	MOVWF       FARG_TFT_Set_Address_PY1+1 
	MOVF        FARG_TFT_Box_x2+0, 0 
	MOVWF       FARG_TFT_Set_Address_PX2+0 
	MOVF        FARG_TFT_Box_x2+1, 0 
	MOVWF       FARG_TFT_Set_Address_PX2+1 
	MOVF        FARG_TFT_Box_y2+0, 0 
	MOVWF       FARG_TFT_Set_Address_PY2+0 
	MOVF        FARG_TFT_Box_y2+1, 0 
	MOVWF       FARG_TFT_Set_Address_PY2+1 
	CALL        _TFT_Set_Address+0, 0
;lcddriver.c,359 :: 		Write_Data(color);
	MOVF        FARG_TFT_Box_color+0, 0 
	MOVWF       FARG_Write_Data_Wdata+0 
	MOVF        FARG_TFT_Box_color+1, 0 
	MOVWF       FARG_Write_Data_Wdata+1 
	CALL        _Write_Data+0, 0
;lcddriver.c,360 :: 		for(i = y1; i <= y2; i++)
	MOVF        FARG_TFT_Box_y1+0, 0 
	MOVWF       TFT_Box_i_L0+0 
	MOVF        FARG_TFT_Box_y1+1, 0 
	MOVWF       TFT_Box_i_L0+1 
L_TFT_Box9:
	MOVF        TFT_Box_i_L0+1, 0 
	SUBWF       FARG_TFT_Box_y2+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Box113
	MOVF        TFT_Box_i_L0+0, 0 
	SUBWF       FARG_TFT_Box_y2+0, 0 
L__TFT_Box113:
	BTFSS       STATUS+0, 0 
	GOTO        L_TFT_Box10
;lcddriver.c,362 :: 		for(j = x1; j <= x2; j++)
	MOVF        FARG_TFT_Box_x1+0, 0 
	MOVWF       TFT_Box_j_L0+0 
	MOVF        FARG_TFT_Box_x1+1, 0 
	MOVWF       TFT_Box_j_L0+1 
L_TFT_Box12:
	MOVF        TFT_Box_j_L0+1, 0 
	SUBWF       FARG_TFT_Box_x2+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Box114
	MOVF        TFT_Box_j_L0+0, 0 
	SUBWF       FARG_TFT_Box_x2+0, 0 
L__TFT_Box114:
	BTFSS       STATUS+0, 0 
	GOTO        L_TFT_Box13
;lcddriver.c,364 :: 		TFT_WR = 0;
	BCF         TFT_WR+0, BitPos(TFT_WR+0) 
;lcddriver.c,365 :: 		TFT_WR = 1;
	BSF         TFT_WR+0, BitPos(TFT_WR+0) 
;lcddriver.c,362 :: 		for(j = x1; j <= x2; j++)
	INFSNZ      TFT_Box_j_L0+0, 1 
	INCF        TFT_Box_j_L0+1, 1 
;lcddriver.c,366 :: 		}
	GOTO        L_TFT_Box12
L_TFT_Box13:
;lcddriver.c,360 :: 		for(i = y1; i <= y2; i++)
	INFSNZ      TFT_Box_i_L0+0, 1 
	INCF        TFT_Box_i_L0+1, 1 
;lcddriver.c,367 :: 		}
	GOTO        L_TFT_Box9
L_TFT_Box10:
;lcddriver.c,368 :: 		TFT_CS  = 1;
	BSF         TFT_CS+0, BitPos(TFT_CS+0) 
;lcddriver.c,369 :: 		}
L_end_TFT_Box:
	RETURN      0
; end of _TFT_Box

_TFT_Dot:

;lcddriver.c,372 :: 		void TFT_Dot(unsigned int x,unsigned int y,unsigned int color)
;lcddriver.c,374 :: 		TFT_CS  = 0;
	BCF         TFT_CS+0, BitPos(TFT_CS+0) 
;lcddriver.c,375 :: 		TFT_Set_Address(x,y,x,y);
	MOVF        FARG_TFT_Dot_x+0, 0 
	MOVWF       FARG_TFT_Set_Address_PX1+0 
	MOVF        FARG_TFT_Dot_x+1, 0 
	MOVWF       FARG_TFT_Set_Address_PX1+1 
	MOVF        FARG_TFT_Dot_y+0, 0 
	MOVWF       FARG_TFT_Set_Address_PY1+0 
	MOVF        FARG_TFT_Dot_y+1, 0 
	MOVWF       FARG_TFT_Set_Address_PY1+1 
	MOVF        FARG_TFT_Dot_x+0, 0 
	MOVWF       FARG_TFT_Set_Address_PX2+0 
	MOVF        FARG_TFT_Dot_x+1, 0 
	MOVWF       FARG_TFT_Set_Address_PX2+1 
	MOVF        FARG_TFT_Dot_y+0, 0 
	MOVWF       FARG_TFT_Set_Address_PY2+0 
	MOVF        FARG_TFT_Dot_y+1, 0 
	MOVWF       FARG_TFT_Set_Address_PY2+1 
	CALL        _TFT_Set_Address+0, 0
;lcddriver.c,376 :: 		Write_Data(color);
	MOVF        FARG_TFT_Dot_color+0, 0 
	MOVWF       FARG_Write_Data_Wdata+0 
	MOVF        FARG_TFT_Dot_color+1, 0 
	MOVWF       FARG_Write_Data_Wdata+1 
	CALL        _Write_Data+0, 0
;lcddriver.c,377 :: 		TFT_CS = 1;
	BSF         TFT_CS+0, BitPos(TFT_CS+0) 
;lcddriver.c,378 :: 		}
L_end_TFT_Dot:
	RETURN      0
; end of _TFT_Dot

_TFT_Line:

;lcddriver.c,380 :: 		void TFT_Line(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int color)
;lcddriver.c,386 :: 		dx = fabs(x2-x1);
	MOVF        FARG_TFT_Line_x1+0, 0 
	SUBWF       FARG_TFT_Line_x2+0, 0 
	MOVWF       R0 
	MOVF        FARG_TFT_Line_x1+1, 0 
	SUBWFB      FARG_TFT_Line_x2+1, 0 
	MOVWF       R1 
	CALL        _Word2Double+0, 0
	MOVF        R0, 0 
	MOVWF       FARG_fabs_d+0 
	MOVF        R1, 0 
	MOVWF       FARG_fabs_d+1 
	MOVF        R2, 0 
	MOVWF       FARG_fabs_d+2 
	MOVF        R3, 0 
	MOVWF       FARG_fabs_d+3 
	CALL        _fabs+0, 0
	CALL        _Double2Int+0, 0
	MOVF        R0, 0 
	MOVWF       TFT_Line_dx_L0+0 
	MOVF        R1, 0 
	MOVWF       TFT_Line_dx_L0+1 
;lcddriver.c,387 :: 		dy = fabs(y2-y1);
	MOVF        FARG_TFT_Line_y1+0, 0 
	SUBWF       FARG_TFT_Line_y2+0, 0 
	MOVWF       R0 
	MOVF        FARG_TFT_Line_y1+1, 0 
	SUBWFB      FARG_TFT_Line_y2+1, 0 
	MOVWF       R1 
	CALL        _Word2Double+0, 0
	MOVF        R0, 0 
	MOVWF       FARG_fabs_d+0 
	MOVF        R1, 0 
	MOVWF       FARG_fabs_d+1 
	MOVF        R2, 0 
	MOVWF       FARG_fabs_d+2 
	MOVF        R3, 0 
	MOVWF       FARG_fabs_d+3 
	CALL        _fabs+0, 0
	CALL        _Double2Int+0, 0
	MOVF        R0, 0 
	MOVWF       TFT_Line_dy_L0+0 
	MOVF        R1, 0 
	MOVWF       TFT_Line_dy_L0+1 
;lcddriver.c,388 :: 		x = x1;
	MOVF        FARG_TFT_Line_x1+0, 0 
	MOVWF       TFT_Line_x_L0+0 
	MOVF        FARG_TFT_Line_x1+1, 0 
	MOVWF       TFT_Line_x_L0+1 
;lcddriver.c,389 :: 		y = y1;
	MOVF        FARG_TFT_Line_y1+0, 0 
	MOVWF       TFT_Line_y_L0+0 
	MOVF        FARG_TFT_Line_y1+1, 0 
	MOVWF       TFT_Line_y_L0+1 
;lcddriver.c,391 :: 		if(X1 > x2)
	MOVF        FARG_TFT_Line_x1+1, 0 
	SUBWF       FARG_TFT_Line_x2+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Line117
	MOVF        FARG_TFT_Line_x1+0, 0 
	SUBWF       FARG_TFT_Line_x2+0, 0 
L__TFT_Line117:
	BTFSC       STATUS+0, 0 
	GOTO        L_TFT_Line15
;lcddriver.c,393 :: 		addx = -1;
	MOVLW       255
	MOVWF       TFT_Line_addx_L0+0 
	MOVLW       255
	MOVWF       TFT_Line_addx_L0+1 
;lcddriver.c,394 :: 		}
	GOTO        L_TFT_Line16
L_TFT_Line15:
;lcddriver.c,397 :: 		addx = 1;
	MOVLW       1
	MOVWF       TFT_Line_addx_L0+0 
	MOVLW       0
	MOVWF       TFT_Line_addx_L0+1 
;lcddriver.c,398 :: 		}
L_TFT_Line16:
;lcddriver.c,400 :: 		if(y1 > y2)
	MOVF        FARG_TFT_Line_y1+1, 0 
	SUBWF       FARG_TFT_Line_y2+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Line118
	MOVF        FARG_TFT_Line_y1+0, 0 
	SUBWF       FARG_TFT_Line_y2+0, 0 
L__TFT_Line118:
	BTFSC       STATUS+0, 0 
	GOTO        L_TFT_Line17
;lcddriver.c,402 :: 		addy = -1;
	MOVLW       255
	MOVWF       TFT_Line_addy_L0+0 
	MOVLW       255
	MOVWF       TFT_Line_addy_L0+1 
;lcddriver.c,403 :: 		}
	GOTO        L_TFT_Line18
L_TFT_Line17:
;lcddriver.c,406 :: 		addy = 1;
	MOVLW       1
	MOVWF       TFT_Line_addy_L0+0 
	MOVLW       0
	MOVWF       TFT_Line_addy_L0+1 
;lcddriver.c,407 :: 		}
L_TFT_Line18:
;lcddriver.c,410 :: 		if(dx >= dy)
	MOVLW       128
	XORWF       TFT_Line_dx_L0+1, 0 
	MOVWF       R0 
	MOVLW       128
	XORWF       TFT_Line_dy_L0+1, 0 
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Line119
	MOVF        TFT_Line_dy_L0+0, 0 
	SUBWF       TFT_Line_dx_L0+0, 0 
L__TFT_Line119:
	BTFSS       STATUS+0, 0 
	GOTO        L_TFT_Line19
;lcddriver.c,413 :: 		P = (2*dy) - dx;
	MOVF        TFT_Line_dy_L0+0, 0 
	MOVWF       TFT_Line_P_L0+0 
	MOVF        TFT_Line_dy_L0+1, 0 
	MOVWF       TFT_Line_P_L0+1 
	RLCF        TFT_Line_P_L0+0, 1 
	BCF         TFT_Line_P_L0+0, 0 
	RLCF        TFT_Line_P_L0+1, 1 
	MOVLW       0
	BTFSC       TFT_Line_P_L0+1, 7 
	MOVLW       255
	MOVWF       TFT_Line_P_L0+2 
	MOVWF       TFT_Line_P_L0+3 
	MOVF        TFT_Line_dx_L0+0, 0 
	SUBWF       TFT_Line_P_L0+0, 1 
	MOVF        TFT_Line_dx_L0+1, 0 
	SUBWFB      TFT_Line_P_L0+1, 1 
	MOVLW       0
	BTFSC       TFT_Line_P_L0+1, 7 
	MOVLW       255
	MOVWF       TFT_Line_P_L0+2 
	MOVWF       TFT_Line_P_L0+3 
;lcddriver.c,415 :: 		for(i = 1; i <= (dx +1); i++)
	MOVLW       1
	MOVWF       TFT_Line_i_L0+0 
	MOVLW       0
	MOVWF       TFT_Line_i_L0+1 
L_TFT_Line20:
	MOVLW       1
	ADDWF       TFT_Line_dx_L0+0, 0 
	MOVWF       R1 
	MOVLW       0
	ADDWFC      TFT_Line_dx_L0+1, 0 
	MOVWF       R2 
	MOVF        TFT_Line_i_L0+1, 0 
	SUBWF       R2, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Line120
	MOVF        TFT_Line_i_L0+0, 0 
	SUBWF       R1, 0 
L__TFT_Line120:
	BTFSS       STATUS+0, 0 
	GOTO        L_TFT_Line21
;lcddriver.c,418 :: 		TFT_dot(x,y,color);
	MOVF        TFT_Line_x_L0+0, 0 
	MOVWF       FARG_TFT_Dot_x+0 
	MOVF        TFT_Line_x_L0+1, 0 
	MOVWF       FARG_TFT_Dot_x+1 
	MOVF        TFT_Line_y_L0+0, 0 
	MOVWF       FARG_TFT_Dot_y+0 
	MOVF        TFT_Line_y_L0+1, 0 
	MOVWF       FARG_TFT_Dot_y+1 
	MOVF        FARG_TFT_Line_color+0, 0 
	MOVWF       FARG_TFT_Dot_color+0 
	MOVF        FARG_TFT_Line_color+1, 0 
	MOVWF       FARG_TFT_Dot_color+1 
	CALL        _TFT_Dot+0, 0
;lcddriver.c,420 :: 		if(P < 0)
	MOVLW       128
	XORWF       TFT_Line_P_L0+3, 0 
	MOVWF       R0 
	MOVLW       128
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Line121
	MOVLW       0
	SUBWF       TFT_Line_P_L0+2, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Line121
	MOVLW       0
	SUBWF       TFT_Line_P_L0+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Line121
	MOVLW       0
	SUBWF       TFT_Line_P_L0+0, 0 
L__TFT_Line121:
	BTFSC       STATUS+0, 0 
	GOTO        L_TFT_Line23
;lcddriver.c,422 :: 		P = P + (2*dy);
	MOVF        TFT_Line_dy_L0+0, 0 
	MOVWF       R0 
	MOVF        TFT_Line_dy_L0+1, 0 
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVF        R0, 0 
	ADDWF       TFT_Line_P_L0+0, 1 
	MOVF        R1, 0 
	ADDWFC      TFT_Line_P_L0+1, 1 
	MOVLW       0
	BTFSC       R1, 7 
	MOVLW       255
	ADDWFC      TFT_Line_P_L0+2, 1 
	ADDWFC      TFT_Line_P_L0+3, 1 
;lcddriver.c,423 :: 		x = (x + addx);
	MOVF        TFT_Line_addx_L0+0, 0 
	ADDWF       TFT_Line_x_L0+0, 1 
	MOVF        TFT_Line_addx_L0+1, 0 
	ADDWFC      TFT_Line_x_L0+1, 1 
;lcddriver.c,424 :: 		}
	GOTO        L_TFT_Line24
L_TFT_Line23:
;lcddriver.c,427 :: 		P = P+(2*dy) - (2*dx);
	MOVF        TFT_Line_dy_L0+0, 0 
	MOVWF       R0 
	MOVF        TFT_Line_dy_L0+1, 0 
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVF        R0, 0 
	ADDWF       TFT_Line_P_L0+0, 1 
	MOVF        R1, 0 
	ADDWFC      TFT_Line_P_L0+1, 1 
	MOVLW       0
	BTFSC       R1, 7 
	MOVLW       255
	ADDWFC      TFT_Line_P_L0+2, 1 
	ADDWFC      TFT_Line_P_L0+3, 1 
	MOVF        TFT_Line_dx_L0+0, 0 
	MOVWF       R0 
	MOVF        TFT_Line_dx_L0+1, 0 
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVF        R0, 0 
	SUBWF       TFT_Line_P_L0+0, 1 
	MOVF        R1, 0 
	SUBWFB      TFT_Line_P_L0+1, 1 
	MOVLW       0
	BTFSC       R1, 7 
	MOVLW       255
	SUBWFB      TFT_Line_P_L0+2, 1 
	SUBWFB      TFT_Line_P_L0+3, 1 
;lcddriver.c,428 :: 		x = x + addx;
	MOVF        TFT_Line_addx_L0+0, 0 
	ADDWF       TFT_Line_x_L0+0, 1 
	MOVF        TFT_Line_addx_L0+1, 0 
	ADDWFC      TFT_Line_x_L0+1, 1 
;lcddriver.c,429 :: 		y = y + addy;
	MOVF        TFT_Line_addy_L0+0, 0 
	ADDWF       TFT_Line_y_L0+0, 1 
	MOVF        TFT_Line_addy_L0+1, 0 
	ADDWFC      TFT_Line_y_L0+1, 1 
;lcddriver.c,430 :: 		}
L_TFT_Line24:
;lcddriver.c,415 :: 		for(i = 1; i <= (dx +1); i++)
	INFSNZ      TFT_Line_i_L0+0, 1 
	INCF        TFT_Line_i_L0+1, 1 
;lcddriver.c,431 :: 		}
	GOTO        L_TFT_Line20
L_TFT_Line21:
;lcddriver.c,432 :: 		}
	GOTO        L_TFT_Line25
L_TFT_Line19:
;lcddriver.c,435 :: 		P = (2*dx) - dy;
	MOVF        TFT_Line_dx_L0+0, 0 
	MOVWF       TFT_Line_P_L0+0 
	MOVF        TFT_Line_dx_L0+1, 0 
	MOVWF       TFT_Line_P_L0+1 
	RLCF        TFT_Line_P_L0+0, 1 
	BCF         TFT_Line_P_L0+0, 0 
	RLCF        TFT_Line_P_L0+1, 1 
	MOVLW       0
	BTFSC       TFT_Line_P_L0+1, 7 
	MOVLW       255
	MOVWF       TFT_Line_P_L0+2 
	MOVWF       TFT_Line_P_L0+3 
	MOVF        TFT_Line_dy_L0+0, 0 
	SUBWF       TFT_Line_P_L0+0, 1 
	MOVF        TFT_Line_dy_L0+1, 0 
	SUBWFB      TFT_Line_P_L0+1, 1 
	MOVLW       0
	BTFSC       TFT_Line_P_L0+1, 7 
	MOVLW       255
	MOVWF       TFT_Line_P_L0+2 
	MOVWF       TFT_Line_P_L0+3 
;lcddriver.c,437 :: 		for(i = 1; i <= (dy +1); i++)
	MOVLW       1
	MOVWF       TFT_Line_i_L0+0 
	MOVLW       0
	MOVWF       TFT_Line_i_L0+1 
L_TFT_Line26:
	MOVLW       1
	ADDWF       TFT_Line_dy_L0+0, 0 
	MOVWF       R1 
	MOVLW       0
	ADDWFC      TFT_Line_dy_L0+1, 0 
	MOVWF       R2 
	MOVF        TFT_Line_i_L0+1, 0 
	SUBWF       R2, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Line122
	MOVF        TFT_Line_i_L0+0, 0 
	SUBWF       R1, 0 
L__TFT_Line122:
	BTFSS       STATUS+0, 0 
	GOTO        L_TFT_Line27
;lcddriver.c,440 :: 		TFT_dot(x,y,color);
	MOVF        TFT_Line_x_L0+0, 0 
	MOVWF       FARG_TFT_Dot_x+0 
	MOVF        TFT_Line_x_L0+1, 0 
	MOVWF       FARG_TFT_Dot_x+1 
	MOVF        TFT_Line_y_L0+0, 0 
	MOVWF       FARG_TFT_Dot_y+0 
	MOVF        TFT_Line_y_L0+1, 0 
	MOVWF       FARG_TFT_Dot_y+1 
	MOVF        FARG_TFT_Line_color+0, 0 
	MOVWF       FARG_TFT_Dot_color+0 
	MOVF        FARG_TFT_Line_color+1, 0 
	MOVWF       FARG_TFT_Dot_color+1 
	CALL        _TFT_Dot+0, 0
;lcddriver.c,442 :: 		if(P<0)
	MOVLW       128
	XORWF       TFT_Line_P_L0+3, 0 
	MOVWF       R0 
	MOVLW       128
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Line123
	MOVLW       0
	SUBWF       TFT_Line_P_L0+2, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Line123
	MOVLW       0
	SUBWF       TFT_Line_P_L0+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Line123
	MOVLW       0
	SUBWF       TFT_Line_P_L0+0, 0 
L__TFT_Line123:
	BTFSC       STATUS+0, 0 
	GOTO        L_TFT_Line29
;lcddriver.c,444 :: 		P = P + (2*dx);
	MOVF        TFT_Line_dx_L0+0, 0 
	MOVWF       R0 
	MOVF        TFT_Line_dx_L0+1, 0 
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVF        R0, 0 
	ADDWF       TFT_Line_P_L0+0, 1 
	MOVF        R1, 0 
	ADDWFC      TFT_Line_P_L0+1, 1 
	MOVLW       0
	BTFSC       R1, 7 
	MOVLW       255
	ADDWFC      TFT_Line_P_L0+2, 1 
	ADDWFC      TFT_Line_P_L0+3, 1 
;lcddriver.c,445 :: 		y = y + addy;
	MOVF        TFT_Line_addy_L0+0, 0 
	ADDWF       TFT_Line_y_L0+0, 1 
	MOVF        TFT_Line_addy_L0+1, 0 
	ADDWFC      TFT_Line_y_L0+1, 1 
;lcddriver.c,446 :: 		}
	GOTO        L_TFT_Line30
L_TFT_Line29:
;lcddriver.c,449 :: 		P = P + (2*dx) - (2*dy);
	MOVF        TFT_Line_dx_L0+0, 0 
	MOVWF       R0 
	MOVF        TFT_Line_dx_L0+1, 0 
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVF        R0, 0 
	ADDWF       TFT_Line_P_L0+0, 1 
	MOVF        R1, 0 
	ADDWFC      TFT_Line_P_L0+1, 1 
	MOVLW       0
	BTFSC       R1, 7 
	MOVLW       255
	ADDWFC      TFT_Line_P_L0+2, 1 
	ADDWFC      TFT_Line_P_L0+3, 1 
	MOVF        TFT_Line_dy_L0+0, 0 
	MOVWF       R0 
	MOVF        TFT_Line_dy_L0+1, 0 
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVF        R0, 0 
	SUBWF       TFT_Line_P_L0+0, 1 
	MOVF        R1, 0 
	SUBWFB      TFT_Line_P_L0+1, 1 
	MOVLW       0
	BTFSC       R1, 7 
	MOVLW       255
	SUBWFB      TFT_Line_P_L0+2, 1 
	SUBWFB      TFT_Line_P_L0+3, 1 
;lcddriver.c,450 :: 		x = x + addx;
	MOVF        TFT_Line_addx_L0+0, 0 
	ADDWF       TFT_Line_x_L0+0, 1 
	MOVF        TFT_Line_addx_L0+1, 0 
	ADDWFC      TFT_Line_x_L0+1, 1 
;lcddriver.c,451 :: 		y = y + addy;
	MOVF        TFT_Line_addy_L0+0, 0 
	ADDWF       TFT_Line_y_L0+0, 1 
	MOVF        TFT_Line_addy_L0+1, 0 
	ADDWFC      TFT_Line_y_L0+1, 1 
;lcddriver.c,452 :: 		}
L_TFT_Line30:
;lcddriver.c,437 :: 		for(i = 1; i <= (dy +1); i++)
	INFSNZ      TFT_Line_i_L0+0, 1 
	INCF        TFT_Line_i_L0+1, 1 
;lcddriver.c,453 :: 		}
	GOTO        L_TFT_Line26
L_TFT_Line27:
;lcddriver.c,454 :: 		}
L_TFT_Line25:
;lcddriver.c,455 :: 		}
L_end_TFT_Line:
	RETURN      0
; end of _TFT_Line

_TFT_H_Line:

;lcddriver.c,457 :: 		void TFT_H_Line(char x1,char x2,unsigned int y_pos,unsigned int color)
;lcddriver.c,459 :: 		TFT_Box(x1,y_pos,x2,y_pos+1,color);
	MOVF        FARG_TFT_H_Line_x1+0, 0 
	MOVWF       FARG_TFT_Box_x1+0 
	MOVLW       0
	MOVWF       FARG_TFT_Box_x1+1 
	MOVF        FARG_TFT_H_Line_y_pos+0, 0 
	MOVWF       FARG_TFT_Box_y1+0 
	MOVF        FARG_TFT_H_Line_y_pos+1, 0 
	MOVWF       FARG_TFT_Box_y1+1 
	MOVF        FARG_TFT_H_Line_x2+0, 0 
	MOVWF       FARG_TFT_Box_x2+0 
	MOVLW       0
	MOVWF       FARG_TFT_Box_x2+1 
	MOVLW       1
	ADDWF       FARG_TFT_H_Line_y_pos+0, 0 
	MOVWF       FARG_TFT_Box_y2+0 
	MOVLW       0
	ADDWFC      FARG_TFT_H_Line_y_pos+1, 0 
	MOVWF       FARG_TFT_Box_y2+1 
	MOVF        FARG_TFT_H_Line_color+0, 0 
	MOVWF       FARG_TFT_Box_color+0 
	MOVF        FARG_TFT_H_Line_color+1, 0 
	MOVWF       FARG_TFT_Box_color+1 
	CALL        _TFT_Box+0, 0
;lcddriver.c,460 :: 		}
L_end_TFT_H_Line:
	RETURN      0
; end of _TFT_H_Line

_TFT_V_Line:

;lcddriver.c,462 :: 		void TFT_V_Line(unsigned int y1,unsigned int y2,char x_pos,unsigned int color)
;lcddriver.c,464 :: 		TFT_Box(x_pos,y1,x_pos+1,y2,color);
	MOVF        FARG_TFT_V_Line_x_pos+0, 0 
	MOVWF       FARG_TFT_Box_x1+0 
	MOVLW       0
	MOVWF       FARG_TFT_Box_x1+1 
	MOVF        FARG_TFT_V_Line_y1+0, 0 
	MOVWF       FARG_TFT_Box_y1+0 
	MOVF        FARG_TFT_V_Line_y1+1, 0 
	MOVWF       FARG_TFT_Box_y1+1 
	MOVF        FARG_TFT_V_Line_x_pos+0, 0 
	ADDLW       1
	MOVWF       FARG_TFT_Box_x2+0 
	CLRF        FARG_TFT_Box_x2+1 
	MOVLW       0
	ADDWFC      FARG_TFT_Box_x2+1, 1 
	MOVF        FARG_TFT_V_Line_y2+0, 0 
	MOVWF       FARG_TFT_Box_y2+0 
	MOVF        FARG_TFT_V_Line_y2+1, 0 
	MOVWF       FARG_TFT_Box_y2+1 
	MOVF        FARG_TFT_V_Line_color+0, 0 
	MOVWF       FARG_TFT_Box_color+0 
	MOVF        FARG_TFT_V_Line_color+1, 0 
	MOVWF       FARG_TFT_Box_color+1 
	CALL        _TFT_Box+0, 0
;lcddriver.c,465 :: 		}
L_end_TFT_V_Line:
	RETURN      0
; end of _TFT_V_Line

_TFT_Rectangle:

;lcddriver.c,467 :: 		void TFT_Rectangle(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int color)
;lcddriver.c,469 :: 		TFT_H_Line(x1,x2,y1,color);
	MOVF        FARG_TFT_Rectangle_x1+0, 0 
	MOVWF       FARG_TFT_H_Line_x1+0 
	MOVF        FARG_TFT_Rectangle_x2+0, 0 
	MOVWF       FARG_TFT_H_Line_x2+0 
	MOVF        FARG_TFT_Rectangle_y1+0, 0 
	MOVWF       FARG_TFT_H_Line_y_pos+0 
	MOVF        FARG_TFT_Rectangle_y1+1, 0 
	MOVWF       FARG_TFT_H_Line_y_pos+1 
	MOVF        FARG_TFT_Rectangle_color+0, 0 
	MOVWF       FARG_TFT_H_Line_color+0 
	MOVF        FARG_TFT_Rectangle_color+1, 0 
	MOVWF       FARG_TFT_H_Line_color+1 
	CALL        _TFT_H_Line+0, 0
;lcddriver.c,470 :: 		TFT_H_Line(x1,x2,y2,color);
	MOVF        FARG_TFT_Rectangle_x1+0, 0 
	MOVWF       FARG_TFT_H_Line_x1+0 
	MOVF        FARG_TFT_Rectangle_x2+0, 0 
	MOVWF       FARG_TFT_H_Line_x2+0 
	MOVF        FARG_TFT_Rectangle_y2+0, 0 
	MOVWF       FARG_TFT_H_Line_y_pos+0 
	MOVF        FARG_TFT_Rectangle_y2+1, 0 
	MOVWF       FARG_TFT_H_Line_y_pos+1 
	MOVF        FARG_TFT_Rectangle_color+0, 0 
	MOVWF       FARG_TFT_H_Line_color+0 
	MOVF        FARG_TFT_Rectangle_color+1, 0 
	MOVWF       FARG_TFT_H_Line_color+1 
	CALL        _TFT_H_Line+0, 0
;lcddriver.c,471 :: 		TFT_V_Line(y1,y2,x1,color);
	MOVF        FARG_TFT_Rectangle_y1+0, 0 
	MOVWF       FARG_TFT_V_Line_y1+0 
	MOVF        FARG_TFT_Rectangle_y1+1, 0 
	MOVWF       FARG_TFT_V_Line_y1+1 
	MOVF        FARG_TFT_Rectangle_y2+0, 0 
	MOVWF       FARG_TFT_V_Line_y2+0 
	MOVF        FARG_TFT_Rectangle_y2+1, 0 
	MOVWF       FARG_TFT_V_Line_y2+1 
	MOVF        FARG_TFT_Rectangle_x1+0, 0 
	MOVWF       FARG_TFT_V_Line_x_pos+0 
	MOVF        FARG_TFT_Rectangle_color+0, 0 
	MOVWF       FARG_TFT_V_Line_color+0 
	MOVF        FARG_TFT_Rectangle_color+1, 0 
	MOVWF       FARG_TFT_V_Line_color+1 
	CALL        _TFT_V_Line+0, 0
;lcddriver.c,472 :: 		TFT_V_Line(y1,y2,x2,color);
	MOVF        FARG_TFT_Rectangle_y1+0, 0 
	MOVWF       FARG_TFT_V_Line_y1+0 
	MOVF        FARG_TFT_Rectangle_y1+1, 0 
	MOVWF       FARG_TFT_V_Line_y1+1 
	MOVF        FARG_TFT_Rectangle_y2+0, 0 
	MOVWF       FARG_TFT_V_Line_y2+0 
	MOVF        FARG_TFT_Rectangle_y2+1, 0 
	MOVWF       FARG_TFT_V_Line_y2+1 
	MOVF        FARG_TFT_Rectangle_x2+0, 0 
	MOVWF       FARG_TFT_V_Line_x_pos+0 
	MOVF        FARG_TFT_Rectangle_color+0, 0 
	MOVWF       FARG_TFT_V_Line_color+0 
	MOVF        FARG_TFT_Rectangle_color+1, 0 
	MOVWF       FARG_TFT_V_Line_color+1 
	CALL        _TFT_V_Line+0, 0
;lcddriver.c,473 :: 		}
L_end_TFT_Rectangle:
	RETURN      0
; end of _TFT_Rectangle

_TFT_Circle:

;lcddriver.c,475 :: 		void TFT_Circle(unsigned int x,unsigned int y,char radius,char fill,unsigned int color)
;lcddriver.c,478 :: 		a_ = 0;
	CLRF        TFT_Circle_a__L0+0 
	CLRF        TFT_Circle_a__L0+1 
;lcddriver.c,479 :: 		b_ = radius;
	MOVF        FARG_TFT_Circle_radius+0, 0 
	MOVWF       TFT_Circle_b__L0+0 
	MOVLW       0
	MOVWF       TFT_Circle_b__L0+1 
;lcddriver.c,480 :: 		P = 1 - radius;
	MOVF        FARG_TFT_Circle_radius+0, 0 
	SUBLW       1
	MOVWF       TFT_Circle_P_L0+0 
	CLRF        TFT_Circle_P_L0+1 
	MOVLW       0
	SUBWFB      TFT_Circle_P_L0+1, 1 
;lcddriver.c,481 :: 		while (a_ <= b_)
L_TFT_Circle31:
	MOVLW       128
	XORWF       TFT_Circle_b__L0+1, 0 
	MOVWF       R0 
	MOVLW       128
	XORWF       TFT_Circle_a__L0+1, 0 
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Circle128
	MOVF        TFT_Circle_a__L0+0, 0 
	SUBWF       TFT_Circle_b__L0+0, 0 
L__TFT_Circle128:
	BTFSS       STATUS+0, 0 
	GOTO        L_TFT_Circle32
;lcddriver.c,483 :: 		if(fill == 1)
	MOVF        FARG_TFT_Circle_fill+0, 0 
	XORLW       1
	BTFSS       STATUS+0, 2 
	GOTO        L_TFT_Circle33
;lcddriver.c,485 :: 		TFT_Box(x-a_,y-b_,x+a_,y+b_,color);
	MOVF        TFT_Circle_a__L0+0, 0 
	SUBWF       FARG_TFT_Circle_x+0, 0 
	MOVWF       FARG_TFT_Box_x1+0 
	MOVF        TFT_Circle_a__L0+1, 0 
	SUBWFB      FARG_TFT_Circle_x+1, 0 
	MOVWF       FARG_TFT_Box_x1+1 
	MOVF        TFT_Circle_b__L0+0, 0 
	SUBWF       FARG_TFT_Circle_y+0, 0 
	MOVWF       FARG_TFT_Box_y1+0 
	MOVF        TFT_Circle_b__L0+1, 0 
	SUBWFB      FARG_TFT_Circle_y+1, 0 
	MOVWF       FARG_TFT_Box_y1+1 
	MOVF        TFT_Circle_a__L0+0, 0 
	ADDWF       FARG_TFT_Circle_x+0, 0 
	MOVWF       FARG_TFT_Box_x2+0 
	MOVF        TFT_Circle_a__L0+1, 0 
	ADDWFC      FARG_TFT_Circle_x+1, 0 
	MOVWF       FARG_TFT_Box_x2+1 
	MOVF        TFT_Circle_b__L0+0, 0 
	ADDWF       FARG_TFT_Circle_y+0, 0 
	MOVWF       FARG_TFT_Box_y2+0 
	MOVF        TFT_Circle_b__L0+1, 0 
	ADDWFC      FARG_TFT_Circle_y+1, 0 
	MOVWF       FARG_TFT_Box_y2+1 
	MOVF        FARG_TFT_Circle_color+0, 0 
	MOVWF       FARG_TFT_Box_color+0 
	MOVF        FARG_TFT_Circle_color+1, 0 
	MOVWF       FARG_TFT_Box_color+1 
	CALL        _TFT_Box+0, 0
;lcddriver.c,486 :: 		TFT_Box(x-b_,y-a_,x+b_,y+a_,color);
	MOVF        TFT_Circle_b__L0+0, 0 
	SUBWF       FARG_TFT_Circle_x+0, 0 
	MOVWF       FARG_TFT_Box_x1+0 
	MOVF        TFT_Circle_b__L0+1, 0 
	SUBWFB      FARG_TFT_Circle_x+1, 0 
	MOVWF       FARG_TFT_Box_x1+1 
	MOVF        TFT_Circle_a__L0+0, 0 
	SUBWF       FARG_TFT_Circle_y+0, 0 
	MOVWF       FARG_TFT_Box_y1+0 
	MOVF        TFT_Circle_a__L0+1, 0 
	SUBWFB      FARG_TFT_Circle_y+1, 0 
	MOVWF       FARG_TFT_Box_y1+1 
	MOVF        TFT_Circle_b__L0+0, 0 
	ADDWF       FARG_TFT_Circle_x+0, 0 
	MOVWF       FARG_TFT_Box_x2+0 
	MOVF        TFT_Circle_b__L0+1, 0 
	ADDWFC      FARG_TFT_Circle_x+1, 0 
	MOVWF       FARG_TFT_Box_x2+1 
	MOVF        TFT_Circle_a__L0+0, 0 
	ADDWF       FARG_TFT_Circle_y+0, 0 
	MOVWF       FARG_TFT_Box_y2+0 
	MOVF        TFT_Circle_a__L0+1, 0 
	ADDWFC      FARG_TFT_Circle_y+1, 0 
	MOVWF       FARG_TFT_Box_y2+1 
	MOVF        FARG_TFT_Circle_color+0, 0 
	MOVWF       FARG_TFT_Box_color+0 
	MOVF        FARG_TFT_Circle_color+1, 0 
	MOVWF       FARG_TFT_Box_color+1 
	CALL        _TFT_Box+0, 0
;lcddriver.c,487 :: 		}
	GOTO        L_TFT_Circle34
L_TFT_Circle33:
;lcddriver.c,490 :: 		TFT_Dot(a_+x, b_+y, color);
	MOVF        FARG_TFT_Circle_x+0, 0 
	ADDWF       TFT_Circle_a__L0+0, 0 
	MOVWF       FARG_TFT_Dot_x+0 
	MOVF        FARG_TFT_Circle_x+1, 0 
	ADDWFC      TFT_Circle_a__L0+1, 0 
	MOVWF       FARG_TFT_Dot_x+1 
	MOVF        FARG_TFT_Circle_y+0, 0 
	ADDWF       TFT_Circle_b__L0+0, 0 
	MOVWF       FARG_TFT_Dot_y+0 
	MOVF        FARG_TFT_Circle_y+1, 0 
	ADDWFC      TFT_Circle_b__L0+1, 0 
	MOVWF       FARG_TFT_Dot_y+1 
	MOVF        FARG_TFT_Circle_color+0, 0 
	MOVWF       FARG_TFT_Dot_color+0 
	MOVF        FARG_TFT_Circle_color+1, 0 
	MOVWF       FARG_TFT_Dot_color+1 
	CALL        _TFT_Dot+0, 0
;lcddriver.c,491 :: 		TFT_Dot(b_+x, a_+y, color);
	MOVF        FARG_TFT_Circle_x+0, 0 
	ADDWF       TFT_Circle_b__L0+0, 0 
	MOVWF       FARG_TFT_Dot_x+0 
	MOVF        FARG_TFT_Circle_x+1, 0 
	ADDWFC      TFT_Circle_b__L0+1, 0 
	MOVWF       FARG_TFT_Dot_x+1 
	MOVF        FARG_TFT_Circle_y+0, 0 
	ADDWF       TFT_Circle_a__L0+0, 0 
	MOVWF       FARG_TFT_Dot_y+0 
	MOVF        FARG_TFT_Circle_y+1, 0 
	ADDWFC      TFT_Circle_a__L0+1, 0 
	MOVWF       FARG_TFT_Dot_y+1 
	MOVF        FARG_TFT_Circle_color+0, 0 
	MOVWF       FARG_TFT_Dot_color+0 
	MOVF        FARG_TFT_Circle_color+1, 0 
	MOVWF       FARG_TFT_Dot_color+1 
	CALL        _TFT_Dot+0, 0
;lcddriver.c,492 :: 		TFT_Dot(x-a_, b_+y, color);
	MOVF        TFT_Circle_a__L0+0, 0 
	SUBWF       FARG_TFT_Circle_x+0, 0 
	MOVWF       FARG_TFT_Dot_x+0 
	MOVF        TFT_Circle_a__L0+1, 0 
	SUBWFB      FARG_TFT_Circle_x+1, 0 
	MOVWF       FARG_TFT_Dot_x+1 
	MOVF        FARG_TFT_Circle_y+0, 0 
	ADDWF       TFT_Circle_b__L0+0, 0 
	MOVWF       FARG_TFT_Dot_y+0 
	MOVF        FARG_TFT_Circle_y+1, 0 
	ADDWFC      TFT_Circle_b__L0+1, 0 
	MOVWF       FARG_TFT_Dot_y+1 
	MOVF        FARG_TFT_Circle_color+0, 0 
	MOVWF       FARG_TFT_Dot_color+0 
	MOVF        FARG_TFT_Circle_color+1, 0 
	MOVWF       FARG_TFT_Dot_color+1 
	CALL        _TFT_Dot+0, 0
;lcddriver.c,493 :: 		TFT_Dot(x-b_, a_+y, color);
	MOVF        TFT_Circle_b__L0+0, 0 
	SUBWF       FARG_TFT_Circle_x+0, 0 
	MOVWF       FARG_TFT_Dot_x+0 
	MOVF        TFT_Circle_b__L0+1, 0 
	SUBWFB      FARG_TFT_Circle_x+1, 0 
	MOVWF       FARG_TFT_Dot_x+1 
	MOVF        FARG_TFT_Circle_y+0, 0 
	ADDWF       TFT_Circle_a__L0+0, 0 
	MOVWF       FARG_TFT_Dot_y+0 
	MOVF        FARG_TFT_Circle_y+1, 0 
	ADDWFC      TFT_Circle_a__L0+1, 0 
	MOVWF       FARG_TFT_Dot_y+1 
	MOVF        FARG_TFT_Circle_color+0, 0 
	MOVWF       FARG_TFT_Dot_color+0 
	MOVF        FARG_TFT_Circle_color+1, 0 
	MOVWF       FARG_TFT_Dot_color+1 
	CALL        _TFT_Dot+0, 0
;lcddriver.c,494 :: 		TFT_Dot(b_+x, y-a_, color);
	MOVF        FARG_TFT_Circle_x+0, 0 
	ADDWF       TFT_Circle_b__L0+0, 0 
	MOVWF       FARG_TFT_Dot_x+0 
	MOVF        FARG_TFT_Circle_x+1, 0 
	ADDWFC      TFT_Circle_b__L0+1, 0 
	MOVWF       FARG_TFT_Dot_x+1 
	MOVF        TFT_Circle_a__L0+0, 0 
	SUBWF       FARG_TFT_Circle_y+0, 0 
	MOVWF       FARG_TFT_Dot_y+0 
	MOVF        TFT_Circle_a__L0+1, 0 
	SUBWFB      FARG_TFT_Circle_y+1, 0 
	MOVWF       FARG_TFT_Dot_y+1 
	MOVF        FARG_TFT_Circle_color+0, 0 
	MOVWF       FARG_TFT_Dot_color+0 
	MOVF        FARG_TFT_Circle_color+1, 0 
	MOVWF       FARG_TFT_Dot_color+1 
	CALL        _TFT_Dot+0, 0
;lcddriver.c,495 :: 		TFT_Dot(a_+x, y-b_, color);
	MOVF        FARG_TFT_Circle_x+0, 0 
	ADDWF       TFT_Circle_a__L0+0, 0 
	MOVWF       FARG_TFT_Dot_x+0 
	MOVF        FARG_TFT_Circle_x+1, 0 
	ADDWFC      TFT_Circle_a__L0+1, 0 
	MOVWF       FARG_TFT_Dot_x+1 
	MOVF        TFT_Circle_b__L0+0, 0 
	SUBWF       FARG_TFT_Circle_y+0, 0 
	MOVWF       FARG_TFT_Dot_y+0 
	MOVF        TFT_Circle_b__L0+1, 0 
	SUBWFB      FARG_TFT_Circle_y+1, 0 
	MOVWF       FARG_TFT_Dot_y+1 
	MOVF        FARG_TFT_Circle_color+0, 0 
	MOVWF       FARG_TFT_Dot_color+0 
	MOVF        FARG_TFT_Circle_color+1, 0 
	MOVWF       FARG_TFT_Dot_color+1 
	CALL        _TFT_Dot+0, 0
;lcddriver.c,496 :: 		TFT_Dot(x-a_, y-b_, color);
	MOVF        TFT_Circle_a__L0+0, 0 
	SUBWF       FARG_TFT_Circle_x+0, 0 
	MOVWF       FARG_TFT_Dot_x+0 
	MOVF        TFT_Circle_a__L0+1, 0 
	SUBWFB      FARG_TFT_Circle_x+1, 0 
	MOVWF       FARG_TFT_Dot_x+1 
	MOVF        TFT_Circle_b__L0+0, 0 
	SUBWF       FARG_TFT_Circle_y+0, 0 
	MOVWF       FARG_TFT_Dot_y+0 
	MOVF        TFT_Circle_b__L0+1, 0 
	SUBWFB      FARG_TFT_Circle_y+1, 0 
	MOVWF       FARG_TFT_Dot_y+1 
	MOVF        FARG_TFT_Circle_color+0, 0 
	MOVWF       FARG_TFT_Dot_color+0 
	MOVF        FARG_TFT_Circle_color+1, 0 
	MOVWF       FARG_TFT_Dot_color+1 
	CALL        _TFT_Dot+0, 0
;lcddriver.c,497 :: 		TFT_Dot(x-b_, y-a_, color);
	MOVF        TFT_Circle_b__L0+0, 0 
	SUBWF       FARG_TFT_Circle_x+0, 0 
	MOVWF       FARG_TFT_Dot_x+0 
	MOVF        TFT_Circle_b__L0+1, 0 
	SUBWFB      FARG_TFT_Circle_x+1, 0 
	MOVWF       FARG_TFT_Dot_x+1 
	MOVF        TFT_Circle_a__L0+0, 0 
	SUBWF       FARG_TFT_Circle_y+0, 0 
	MOVWF       FARG_TFT_Dot_y+0 
	MOVF        TFT_Circle_a__L0+1, 0 
	SUBWFB      FARG_TFT_Circle_y+1, 0 
	MOVWF       FARG_TFT_Dot_y+1 
	MOVF        FARG_TFT_Circle_color+0, 0 
	MOVWF       FARG_TFT_Dot_color+0 
	MOVF        FARG_TFT_Circle_color+1, 0 
	MOVWF       FARG_TFT_Dot_color+1 
	CALL        _TFT_Dot+0, 0
;lcddriver.c,498 :: 		}
L_TFT_Circle34:
;lcddriver.c,499 :: 		if (P < 0 )
	MOVLW       128
	XORWF       TFT_Circle_P_L0+1, 0 
	MOVWF       R0 
	MOVLW       128
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Circle129
	MOVLW       0
	SUBWF       TFT_Circle_P_L0+0, 0 
L__TFT_Circle129:
	BTFSC       STATUS+0, 0 
	GOTO        L_TFT_Circle35
;lcddriver.c,501 :: 		P = (P + 3) + (2* a_);
	MOVLW       3
	ADDWF       TFT_Circle_P_L0+0, 1 
	MOVLW       0
	ADDWFC      TFT_Circle_P_L0+1, 1 
	MOVF        TFT_Circle_a__L0+0, 0 
	MOVWF       R0 
	MOVF        TFT_Circle_a__L0+1, 0 
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVF        R0, 0 
	ADDWF       TFT_Circle_P_L0+0, 1 
	MOVF        R1, 0 
	ADDWFC      TFT_Circle_P_L0+1, 1 
;lcddriver.c,502 :: 		a_ ++;
	INFSNZ      TFT_Circle_a__L0+0, 1 
	INCF        TFT_Circle_a__L0+1, 1 
;lcddriver.c,503 :: 		}
	GOTO        L_TFT_Circle36
L_TFT_Circle35:
;lcddriver.c,506 :: 		P = (P + 5) + (2* (a_ - b_));
	MOVLW       5
	ADDWF       TFT_Circle_P_L0+0, 1 
	MOVLW       0
	ADDWFC      TFT_Circle_P_L0+1, 1 
	MOVF        TFT_Circle_b__L0+0, 0 
	SUBWF       TFT_Circle_a__L0+0, 0 
	MOVWF       R3 
	MOVF        TFT_Circle_b__L0+1, 0 
	SUBWFB      TFT_Circle_a__L0+1, 0 
	MOVWF       R4 
	MOVF        R3, 0 
	MOVWF       R0 
	MOVF        R4, 0 
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVF        R0, 0 
	ADDWF       TFT_Circle_P_L0+0, 1 
	MOVF        R1, 0 
	ADDWFC      TFT_Circle_P_L0+1, 1 
;lcddriver.c,507 :: 		a_ ++;
	INFSNZ      TFT_Circle_a__L0+0, 1 
	INCF        TFT_Circle_a__L0+1, 1 
;lcddriver.c,508 :: 		b_ --;
	MOVLW       1
	SUBWF       TFT_Circle_b__L0+0, 1 
	MOVLW       0
	SUBWFB      TFT_Circle_b__L0+1, 1 
;lcddriver.c,509 :: 		}
L_TFT_Circle36:
;lcddriver.c,510 :: 		}
	GOTO        L_TFT_Circle31
L_TFT_Circle32:
;lcddriver.c,511 :: 		}
L_end_TFT_Circle:
	RETURN      0
; end of _TFT_Circle

_TFT_Char:

;lcddriver.c,513 :: 		void TFT_Char(char C,unsigned int x,unsigned int y,char DimFont,unsigned int Fcolor,unsigned int Bcolor)
;lcddriver.c,522 :: 		if(DimFont == 8)
	MOVF        FARG_TFT_Char_DimFont+0, 0 
	XORLW       8
	BTFSS       STATUS+0, 2 
	GOTO        L_TFT_Char37
;lcddriver.c,524 :: 		ptrfont = &Font_8x8;
	MOVLW       _FONT_8x8+0
	MOVWF       TFT_Char_PtrFont_L0+0 
	MOVLW       hi_addr(_FONT_8x8+0)
	MOVWF       TFT_Char_PtrFont_L0+1 
	MOVLW       higher_addr(_FONT_8x8+0)
	MOVWF       TFT_Char_PtrFont_L0+2 
;lcddriver.c,525 :: 		Cptrfont = (C-32)*8;
	MOVLW       32
	SUBWF       FARG_TFT_Char_C+0, 0 
	MOVWF       R3 
	CLRF        R4 
	MOVLW       0
	SUBWFB      R4, 1 
	MOVLW       3
	MOVWF       R2 
	MOVF        R3, 0 
	MOVWF       R0 
	MOVF        R4, 0 
	MOVWF       R1 
	MOVF        R2, 0 
L__TFT_Char131:
	BZ          L__TFT_Char132
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	ADDLW       255
	GOTO        L__TFT_Char131
L__TFT_Char132:
;lcddriver.c,526 :: 		ptrfont = ptrfont + Cptrfont;
	MOVF        R0, 0 
	ADDWF       TFT_Char_PtrFont_L0+0, 1 
	MOVF        R1, 0 
	ADDWFC      TFT_Char_PtrFont_L0+1, 1 
	MOVLW       0
	ADDWFC      TFT_Char_PtrFont_L0+2, 1 
;lcddriver.c,528 :: 		for(k = 0; k <= 7; k++)
	CLRF        TFT_Char_k_L0+0 
L_TFT_Char38:
	MOVF        TFT_Char_k_L0+0, 0 
	SUBLW       7
	BTFSS       STATUS+0, 0 
	GOTO        L_TFT_Char39
;lcddriver.c,530 :: 		font8x8[k] = *ptrfont;
	MOVF        TFT_Char_k_L0+0, 0 
	MOVWF       R0 
	MOVLW       0
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVLW       TFT_Char_font8x8_L0+0
	ADDWF       R0, 0 
	MOVWF       FSR1 
	MOVLW       hi_addr(TFT_Char_font8x8_L0+0)
	ADDWFC      R1, 0 
	MOVWF       FSR1H 
	MOVF        TFT_Char_PtrFont_L0+0, 0 
	MOVWF       TBLPTRL 
	MOVF        TFT_Char_PtrFont_L0+1, 0 
	MOVWF       TBLPTRH 
	MOVF        TFT_Char_PtrFont_L0+2, 0 
	MOVWF       TBLPTRU 
	TBLRD*+
	MOVFF       TABLAT+0, R0
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	MOVLW       0
	MOVWF       POSTINC1+0 
;lcddriver.c,531 :: 		ptrFont++;
	MOVLW       1
	ADDWF       TFT_Char_PtrFont_L0+0, 1 
	MOVLW       0
	ADDWFC      TFT_Char_PtrFont_L0+1, 1 
	ADDWFC      TFT_Char_PtrFont_L0+2, 1 
;lcddriver.c,528 :: 		for(k = 0; k <= 7; k++)
	INCF        TFT_Char_k_L0+0, 1 
;lcddriver.c,532 :: 		}
	GOTO        L_TFT_Char38
L_TFT_Char39:
;lcddriver.c,534 :: 		TFT_CS = 0;
	BCF         TFT_CS+0, BitPos(TFT_CS+0) 
;lcddriver.c,535 :: 		TFT_Set_Address(x,y,x+7,y+7);
	MOVF        FARG_TFT_Char_x+0, 0 
	MOVWF       FARG_TFT_Set_Address_PX1+0 
	MOVF        FARG_TFT_Char_x+1, 0 
	MOVWF       FARG_TFT_Set_Address_PX1+1 
	MOVF        FARG_TFT_Char_y+0, 0 
	MOVWF       FARG_TFT_Set_Address_PY1+0 
	MOVF        FARG_TFT_Char_y+1, 0 
	MOVWF       FARG_TFT_Set_Address_PY1+1 
	MOVLW       7
	ADDWF       FARG_TFT_Char_x+0, 0 
	MOVWF       FARG_TFT_Set_Address_PX2+0 
	MOVLW       0
	ADDWFC      FARG_TFT_Char_x+1, 0 
	MOVWF       FARG_TFT_Set_Address_PX2+1 
	MOVLW       7
	ADDWF       FARG_TFT_Char_y+0, 0 
	MOVWF       FARG_TFT_Set_Address_PY2+0 
	MOVLW       0
	ADDWFC      FARG_TFT_Char_y+1, 0 
	MOVWF       FARG_TFT_Set_Address_PY2+1 
	CALL        _TFT_Set_Address+0, 0
;lcddriver.c,536 :: 		for(i = 0; i <= 7; i++)
	CLRF        TFT_Char_i_L0+0 
L_TFT_Char41:
	MOVF        TFT_Char_i_L0+0, 0 
	SUBLW       7
	BTFSS       STATUS+0, 0 
	GOTO        L_TFT_Char42
;lcddriver.c,538 :: 		for(k = 0; k <= 7; k++)
	CLRF        TFT_Char_k_L0+0 
L_TFT_Char44:
	MOVF        TFT_Char_k_L0+0, 0 
	SUBLW       7
	BTFSS       STATUS+0, 0 
	GOTO        L_TFT_Char45
;lcddriver.c,540 :: 		print1 = (font8x8[i] & 0x80);
	MOVF        TFT_Char_i_L0+0, 0 
	MOVWF       R0 
	MOVLW       0
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVLW       TFT_Char_font8x8_L0+0
	ADDWF       R0, 0 
	MOVWF       FSR0 
	MOVLW       hi_addr(TFT_Char_font8x8_L0+0)
	ADDWFC      R1, 0 
	MOVWF       FSR0H 
	MOVLW       128
	ANDWF       POSTINC0+0, 0 
	MOVWF       R2 
;lcddriver.c,541 :: 		print2 = print1 >>7;
	MOVLW       7
	MOVWF       R0 
	MOVF        R2, 0 
	MOVWF       R1 
	MOVF        R0, 0 
L__TFT_Char133:
	BZ          L__TFT_Char134
	RRCF        R1, 1 
	BCF         R1, 7 
	ADDLW       255
	GOTO        L__TFT_Char133
L__TFT_Char134:
;lcddriver.c,542 :: 		if(print2 == 1)
	MOVF        R1, 0 
	XORLW       1
	BTFSS       STATUS+0, 2 
	GOTO        L_TFT_Char47
;lcddriver.c,544 :: 		Write_Data(Fcolor);
	MOVF        FARG_TFT_Char_Fcolor+0, 0 
	MOVWF       FARG_Write_Data_Wdata+0 
	MOVF        FARG_TFT_Char_Fcolor+1, 0 
	MOVWF       FARG_Write_Data_Wdata+1 
	CALL        _Write_Data+0, 0
;lcddriver.c,545 :: 		}
	GOTO        L_TFT_Char48
L_TFT_Char47:
;lcddriver.c,548 :: 		Write_Data(Bcolor);
	MOVF        FARG_TFT_Char_Bcolor+0, 0 
	MOVWF       FARG_Write_Data_Wdata+0 
	MOVF        FARG_TFT_Char_Bcolor+1, 0 
	MOVWF       FARG_Write_Data_Wdata+1 
	CALL        _Write_Data+0, 0
;lcddriver.c,549 :: 		}
L_TFT_Char48:
;lcddriver.c,550 :: 		font8x8[i] = font8x8[i] << 1;
	MOVF        TFT_Char_i_L0+0, 0 
	MOVWF       R0 
	MOVLW       0
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVLW       TFT_Char_font8x8_L0+0
	ADDWF       R0, 0 
	MOVWF       R5 
	MOVLW       hi_addr(TFT_Char_font8x8_L0+0)
	ADDWFC      R1, 0 
	MOVWF       R6 
	MOVFF       R5, FSR0
	MOVFF       R6, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       R3 
	MOVF        POSTINC0+0, 0 
	MOVWF       R4 
	MOVF        R3, 0 
	MOVWF       R0 
	MOVF        R4, 0 
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVFF       R5, FSR1
	MOVFF       R6, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	MOVF        R1, 0 
	MOVWF       POSTINC1+0 
;lcddriver.c,538 :: 		for(k = 0; k <= 7; k++)
	INCF        TFT_Char_k_L0+0, 1 
;lcddriver.c,551 :: 		}
	GOTO        L_TFT_Char44
L_TFT_Char45:
;lcddriver.c,536 :: 		for(i = 0; i <= 7; i++)
	INCF        TFT_Char_i_L0+0, 1 
;lcddriver.c,552 :: 		}
	GOTO        L_TFT_Char41
L_TFT_Char42:
;lcddriver.c,553 :: 		TFT_CS = 1;
	BSF         TFT_CS+0, BitPos(TFT_CS+0) 
;lcddriver.c,554 :: 		}
	GOTO        L_TFT_Char49
L_TFT_Char37:
;lcddriver.c,556 :: 		else if(DimFont == 16)
	MOVF        FARG_TFT_Char_DimFont+0, 0 
	XORLW       16
	BTFSS       STATUS+0, 2 
	GOTO        L_TFT_Char50
;lcddriver.c,558 :: 		ptrfont = &Font_16x16;
	MOVLW       _FONT_16x16+0
	MOVWF       TFT_Char_PtrFont_L0+0 
	MOVLW       hi_addr(_FONT_16x16+0)
	MOVWF       TFT_Char_PtrFont_L0+1 
	MOVLW       higher_addr(_FONT_16x16+0)
	MOVWF       TFT_Char_PtrFont_L0+2 
;lcddriver.c,559 :: 		Cptrfont = (C-32)*32;
	MOVLW       32
	SUBWF       FARG_TFT_Char_C+0, 0 
	MOVWF       R3 
	CLRF        R4 
	MOVLW       0
	SUBWFB      R4, 1 
	MOVLW       5
	MOVWF       R2 
	MOVF        R3, 0 
	MOVWF       R0 
	MOVF        R4, 0 
	MOVWF       R1 
	MOVF        R2, 0 
L__TFT_Char135:
	BZ          L__TFT_Char136
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	ADDLW       255
	GOTO        L__TFT_Char135
L__TFT_Char136:
;lcddriver.c,560 :: 		ptrfont = ptrfont + Cptrfont;
	MOVF        R0, 0 
	ADDWF       TFT_Char_PtrFont_L0+0, 1 
	MOVF        R1, 0 
	ADDWFC      TFT_Char_PtrFont_L0+1, 1 
	MOVLW       0
	ADDWFC      TFT_Char_PtrFont_L0+2, 1 
;lcddriver.c,562 :: 		for(k = 0; k <= 15; k++)
	CLRF        TFT_Char_k_L0+0 
L_TFT_Char51:
	MOVF        TFT_Char_k_L0+0, 0 
	SUBLW       15
	BTFSS       STATUS+0, 0 
	GOTO        L_TFT_Char52
;lcddriver.c,564 :: 		font16x16[k] = *ptrfont;
	MOVF        TFT_Char_k_L0+0, 0 
	MOVWF       R0 
	MOVLW       0
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVLW       TFT_Char_font16x16_L0+0
	ADDWF       R0, 0 
	MOVWF       FSR1 
	MOVLW       hi_addr(TFT_Char_font16x16_L0+0)
	ADDWFC      R1, 0 
	MOVWF       FSR1H 
	MOVF        TFT_Char_PtrFont_L0+0, 0 
	MOVWF       TBLPTRL 
	MOVF        TFT_Char_PtrFont_L0+1, 0 
	MOVWF       TBLPTRH 
	MOVF        TFT_Char_PtrFont_L0+2, 0 
	MOVWF       TBLPTRU 
	TBLRD*+
	MOVFF       TABLAT+0, R0
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	MOVLW       0
	MOVWF       POSTINC1+0 
;lcddriver.c,565 :: 		ptrFont++;
	MOVLW       1
	ADDWF       TFT_Char_PtrFont_L0+0, 1 
	MOVLW       0
	ADDWFC      TFT_Char_PtrFont_L0+1, 1 
	ADDWFC      TFT_Char_PtrFont_L0+2, 1 
;lcddriver.c,566 :: 		font16x16[k] = (font16x16[k] << 8);
	MOVF        TFT_Char_k_L0+0, 0 
	MOVWF       R0 
	MOVLW       0
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVLW       TFT_Char_font16x16_L0+0
	ADDWF       R0, 0 
	MOVWF       R5 
	MOVLW       hi_addr(TFT_Char_font16x16_L0+0)
	ADDWFC      R1, 0 
	MOVWF       R6 
	MOVFF       R5, FSR0
	MOVFF       R6, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       R3 
	MOVF        POSTINC0+0, 0 
	MOVWF       R4 
	MOVF        R3, 0 
	MOVWF       R1 
	CLRF        R0 
	MOVFF       R5, FSR1
	MOVFF       R6, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	MOVF        R1, 0 
	MOVWF       POSTINC1+0 
;lcddriver.c,567 :: 		font16x16[k] = font16x16[k] + *ptrfont;
	MOVF        TFT_Char_k_L0+0, 0 
	MOVWF       R0 
	MOVLW       0
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVLW       TFT_Char_font16x16_L0+0
	ADDWF       R0, 0 
	MOVWF       R4 
	MOVLW       hi_addr(TFT_Char_font16x16_L0+0)
	ADDWFC      R1, 0 
	MOVWF       R5 
	MOVFF       R4, FSR0
	MOVFF       R5, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       R2 
	MOVF        POSTINC0+0, 0 
	MOVWF       R3 
	MOVF        TFT_Char_PtrFont_L0+0, 0 
	MOVWF       TBLPTRL 
	MOVF        TFT_Char_PtrFont_L0+1, 0 
	MOVWF       TBLPTRH 
	MOVF        TFT_Char_PtrFont_L0+2, 0 
	MOVWF       TBLPTRU 
	TBLRD*+
	MOVFF       TABLAT+0, R0
	MOVLW       0
	MOVWF       R1 
	MOVF        R2, 0 
	ADDWF       R0, 1 
	MOVF        R3, 0 
	ADDWFC      R1, 1 
	MOVFF       R4, FSR1
	MOVFF       R5, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	MOVF        R1, 0 
	MOVWF       POSTINC1+0 
;lcddriver.c,568 :: 		ptrFont++;
	MOVLW       1
	ADDWF       TFT_Char_PtrFont_L0+0, 1 
	MOVLW       0
	ADDWFC      TFT_Char_PtrFont_L0+1, 1 
	ADDWFC      TFT_Char_PtrFont_L0+2, 1 
;lcddriver.c,562 :: 		for(k = 0; k <= 15; k++)
	INCF        TFT_Char_k_L0+0, 1 
;lcddriver.c,569 :: 		}
	GOTO        L_TFT_Char51
L_TFT_Char52:
;lcddriver.c,571 :: 		TFT_CS = 0;
	BCF         TFT_CS+0, BitPos(TFT_CS+0) 
;lcddriver.c,572 :: 		TFT_Set_Address(x,y,x+15,y+15);
	MOVF        FARG_TFT_Char_x+0, 0 
	MOVWF       FARG_TFT_Set_Address_PX1+0 
	MOVF        FARG_TFT_Char_x+1, 0 
	MOVWF       FARG_TFT_Set_Address_PX1+1 
	MOVF        FARG_TFT_Char_y+0, 0 
	MOVWF       FARG_TFT_Set_Address_PY1+0 
	MOVF        FARG_TFT_Char_y+1, 0 
	MOVWF       FARG_TFT_Set_Address_PY1+1 
	MOVLW       15
	ADDWF       FARG_TFT_Char_x+0, 0 
	MOVWF       FARG_TFT_Set_Address_PX2+0 
	MOVLW       0
	ADDWFC      FARG_TFT_Char_x+1, 0 
	MOVWF       FARG_TFT_Set_Address_PX2+1 
	MOVLW       15
	ADDWF       FARG_TFT_Char_y+0, 0 
	MOVWF       FARG_TFT_Set_Address_PY2+0 
	MOVLW       0
	ADDWFC      FARG_TFT_Char_y+1, 0 
	MOVWF       FARG_TFT_Set_Address_PY2+1 
	CALL        _TFT_Set_Address+0, 0
;lcddriver.c,573 :: 		for(i = 0; i <= 15; i++)
	CLRF        TFT_Char_i_L0+0 
L_TFT_Char54:
	MOVF        TFT_Char_i_L0+0, 0 
	SUBLW       15
	BTFSS       STATUS+0, 0 
	GOTO        L_TFT_Char55
;lcddriver.c,575 :: 		for(k = 0; k <= 15; k++)
	CLRF        TFT_Char_k_L0+0 
L_TFT_Char57:
	MOVF        TFT_Char_k_L0+0, 0 
	SUBLW       15
	BTFSS       STATUS+0, 0 
	GOTO        L_TFT_Char58
;lcddriver.c,577 :: 		print3 = (font16x16[i] & 0x8000);
	MOVF        TFT_Char_i_L0+0, 0 
	MOVWF       R0 
	MOVLW       0
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVLW       TFT_Char_font16x16_L0+0
	ADDWF       R0, 0 
	MOVWF       FSR0 
	MOVLW       hi_addr(TFT_Char_font16x16_L0+0)
	ADDWFC      R1, 0 
	MOVWF       FSR0H 
	MOVLW       0
	ANDWF       POSTINC0+0, 0 
	MOVWF       R3 
	MOVF        POSTINC0+0, 0 
	ANDLW       128
	MOVWF       R4 
;lcddriver.c,578 :: 		print4 = print3 >>15;
	MOVLW       15
	MOVWF       R0 
	MOVF        R3, 0 
	MOVWF       R1 
	MOVF        R4, 0 
	MOVWF       R2 
	MOVF        R0, 0 
L__TFT_Char137:
	BZ          L__TFT_Char138
	RRCF        R2, 1 
	RRCF        R1, 1 
	BCF         R2, 7 
	ADDLW       255
	GOTO        L__TFT_Char137
L__TFT_Char138:
;lcddriver.c,580 :: 		if(print4 == 1)
	MOVLW       0
	XORWF       R2, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Char139
	MOVLW       1
	XORWF       R1, 0 
L__TFT_Char139:
	BTFSS       STATUS+0, 2 
	GOTO        L_TFT_Char60
;lcddriver.c,582 :: 		Write_Data(Fcolor);
	MOVF        FARG_TFT_Char_Fcolor+0, 0 
	MOVWF       FARG_Write_Data_Wdata+0 
	MOVF        FARG_TFT_Char_Fcolor+1, 0 
	MOVWF       FARG_Write_Data_Wdata+1 
	CALL        _Write_Data+0, 0
;lcddriver.c,583 :: 		}
	GOTO        L_TFT_Char61
L_TFT_Char60:
;lcddriver.c,586 :: 		Write_Data(Bcolor);
	MOVF        FARG_TFT_Char_Bcolor+0, 0 
	MOVWF       FARG_Write_Data_Wdata+0 
	MOVF        FARG_TFT_Char_Bcolor+1, 0 
	MOVWF       FARG_Write_Data_Wdata+1 
	CALL        _Write_Data+0, 0
;lcddriver.c,587 :: 		}
L_TFT_Char61:
;lcddriver.c,589 :: 		font16x16[i] = font16x16[i] << 1;
	MOVF        TFT_Char_i_L0+0, 0 
	MOVWF       R0 
	MOVLW       0
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVLW       TFT_Char_font16x16_L0+0
	ADDWF       R0, 0 
	MOVWF       R5 
	MOVLW       hi_addr(TFT_Char_font16x16_L0+0)
	ADDWFC      R1, 0 
	MOVWF       R6 
	MOVFF       R5, FSR0
	MOVFF       R6, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       R3 
	MOVF        POSTINC0+0, 0 
	MOVWF       R4 
	MOVF        R3, 0 
	MOVWF       R0 
	MOVF        R4, 0 
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVFF       R5, FSR1
	MOVFF       R6, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	MOVF        R1, 0 
	MOVWF       POSTINC1+0 
;lcddriver.c,575 :: 		for(k = 0; k <= 15; k++)
	INCF        TFT_Char_k_L0+0, 1 
;lcddriver.c,590 :: 		}
	GOTO        L_TFT_Char57
L_TFT_Char58:
;lcddriver.c,573 :: 		for(i = 0; i <= 15; i++)
	INCF        TFT_Char_i_L0+0, 1 
;lcddriver.c,591 :: 		}
	GOTO        L_TFT_Char54
L_TFT_Char55:
;lcddriver.c,592 :: 		TFT_CS = 1;
	BSF         TFT_CS+0, BitPos(TFT_CS+0) 
;lcddriver.c,593 :: 		}
L_TFT_Char50:
L_TFT_Char49:
;lcddriver.c,595 :: 		}
L_end_TFT_Char:
	RETURN      0
; end of _TFT_Char

_TFT_Text:

;lcddriver.c,598 :: 		void TFT_Text(unsigned char* S,unsigned int x,unsigned int y,char DimFont,unsigned int Fcolor,unsigned int Bcolor)
;lcddriver.c,602 :: 		lenght = strlen(S);
	MOVF        FARG_TFT_Text_S+0, 0 
	MOVWF       FARG_strlen_s+0 
	MOVF        FARG_TFT_Text_S+1, 0 
	MOVWF       FARG_strlen_s+1 
	CALL        _strlen+0, 0
	MOVF        R0, 0 
	MOVWF       TFT_Text_lenght_L0+0 
	MOVF        R1, 0 
	MOVWF       TFT_Text_lenght_L0+1 
;lcddriver.c,604 :: 		for(cnt = 0; cnt <= (lenght - 1); cnt++)
	CLRF        TFT_Text_cnt_L0+0 
	CLRF        TFT_Text_cnt_L0+1 
L_TFT_Text62:
	MOVLW       1
	SUBWF       TFT_Text_lenght_L0+0, 0 
	MOVWF       R1 
	MOVLW       0
	SUBWFB      TFT_Text_lenght_L0+1, 0 
	MOVWF       R2 
	MOVLW       128
	XORWF       R2, 0 
	MOVWF       R0 
	MOVLW       128
	XORWF       TFT_Text_cnt_L0+1, 0 
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Text141
	MOVF        TFT_Text_cnt_L0+0, 0 
	SUBWF       R1, 0 
L__TFT_Text141:
	BTFSS       STATUS+0, 0 
	GOTO        L_TFT_Text63
;lcddriver.c,606 :: 		buffer[cnt] = S[cnt];
	MOVLW       TFT_Text_buffer_L0+0
	ADDWF       TFT_Text_cnt_L0+0, 0 
	MOVWF       FSR1 
	MOVLW       hi_addr(TFT_Text_buffer_L0+0)
	ADDWFC      TFT_Text_cnt_L0+1, 0 
	MOVWF       FSR1H 
	MOVF        TFT_Text_cnt_L0+0, 0 
	ADDWF       FARG_TFT_Text_S+0, 0 
	MOVWF       FSR0 
	MOVF        TFT_Text_cnt_L0+1, 0 
	ADDWFC      FARG_TFT_Text_S+1, 0 
	MOVWF       FSR0H 
	MOVF        POSTINC0+0, 0 
	MOVWF       POSTINC1+0 
;lcddriver.c,604 :: 		for(cnt = 0; cnt <= (lenght - 1); cnt++)
	INFSNZ      TFT_Text_cnt_L0+0, 1 
	INCF        TFT_Text_cnt_L0+1, 1 
;lcddriver.c,607 :: 		}
	GOTO        L_TFT_Text62
L_TFT_Text63:
;lcddriver.c,609 :: 		if(DimFont == 8)
	MOVF        FARG_TFT_Text_DimFont+0, 0 
	XORLW       8
	BTFSS       STATUS+0, 2 
	GOTO        L_TFT_Text65
;lcddriver.c,611 :: 		for(cnt = 0; cnt <= (lenght - 1); cnt++)
	CLRF        TFT_Text_cnt_L0+0 
	CLRF        TFT_Text_cnt_L0+1 
L_TFT_Text66:
	MOVLW       1
	SUBWF       TFT_Text_lenght_L0+0, 0 
	MOVWF       R1 
	MOVLW       0
	SUBWFB      TFT_Text_lenght_L0+1, 0 
	MOVWF       R2 
	MOVLW       128
	XORWF       R2, 0 
	MOVWF       R0 
	MOVLW       128
	XORWF       TFT_Text_cnt_L0+1, 0 
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Text142
	MOVF        TFT_Text_cnt_L0+0, 0 
	SUBWF       R1, 0 
L__TFT_Text142:
	BTFSS       STATUS+0, 0 
	GOTO        L_TFT_Text67
;lcddriver.c,613 :: 		TFT_Char(buffer[cnt],x,y,DimFont,Fcolor,Bcolor);
	MOVLW       TFT_Text_buffer_L0+0
	ADDWF       TFT_Text_cnt_L0+0, 0 
	MOVWF       FSR0 
	MOVLW       hi_addr(TFT_Text_buffer_L0+0)
	ADDWFC      TFT_Text_cnt_L0+1, 0 
	MOVWF       FSR0H 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_TFT_Char_C+0 
	MOVF        FARG_TFT_Text_x+0, 0 
	MOVWF       FARG_TFT_Char_x+0 
	MOVF        FARG_TFT_Text_x+1, 0 
	MOVWF       FARG_TFT_Char_x+1 
	MOVF        FARG_TFT_Text_y+0, 0 
	MOVWF       FARG_TFT_Char_y+0 
	MOVF        FARG_TFT_Text_y+1, 0 
	MOVWF       FARG_TFT_Char_y+1 
	MOVF        FARG_TFT_Text_DimFont+0, 0 
	MOVWF       FARG_TFT_Char_DimFont+0 
	MOVF        FARG_TFT_Text_Fcolor+0, 0 
	MOVWF       FARG_TFT_Char_Fcolor+0 
	MOVF        FARG_TFT_Text_Fcolor+1, 0 
	MOVWF       FARG_TFT_Char_Fcolor+1 
	MOVF        FARG_TFT_Text_Bcolor+0, 0 
	MOVWF       FARG_TFT_Char_Bcolor+0 
	MOVF        FARG_TFT_Text_Bcolor+1, 0 
	MOVWF       FARG_TFT_Char_Bcolor+1 
	CALL        _TFT_Char+0, 0
;lcddriver.c,614 :: 		x = x + 8;
	MOVLW       8
	ADDWF       FARG_TFT_Text_x+0, 1 
	MOVLW       0
	ADDWFC      FARG_TFT_Text_x+1, 1 
;lcddriver.c,611 :: 		for(cnt = 0; cnt <= (lenght - 1); cnt++)
	INFSNZ      TFT_Text_cnt_L0+0, 1 
	INCF        TFT_Text_cnt_L0+1, 1 
;lcddriver.c,615 :: 		}
	GOTO        L_TFT_Text66
L_TFT_Text67:
;lcddriver.c,616 :: 		}
	GOTO        L_TFT_Text69
L_TFT_Text65:
;lcddriver.c,617 :: 		else if(DimFont == 16)
	MOVF        FARG_TFT_Text_DimFont+0, 0 
	XORLW       16
	BTFSS       STATUS+0, 2 
	GOTO        L_TFT_Text70
;lcddriver.c,619 :: 		for(cnt = 0; cnt <= (lenght - 1); cnt++)
	CLRF        TFT_Text_cnt_L0+0 
	CLRF        TFT_Text_cnt_L0+1 
L_TFT_Text71:
	MOVLW       1
	SUBWF       TFT_Text_lenght_L0+0, 0 
	MOVWF       R1 
	MOVLW       0
	SUBWFB      TFT_Text_lenght_L0+1, 0 
	MOVWF       R2 
	MOVLW       128
	XORWF       R2, 0 
	MOVWF       R0 
	MOVLW       128
	XORWF       TFT_Text_cnt_L0+1, 0 
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Text143
	MOVF        TFT_Text_cnt_L0+0, 0 
	SUBWF       R1, 0 
L__TFT_Text143:
	BTFSS       STATUS+0, 0 
	GOTO        L_TFT_Text72
;lcddriver.c,621 :: 		TFT_Char(buffer[cnt],x,y,DimFont,Fcolor,Bcolor);
	MOVLW       TFT_Text_buffer_L0+0
	ADDWF       TFT_Text_cnt_L0+0, 0 
	MOVWF       FSR0 
	MOVLW       hi_addr(TFT_Text_buffer_L0+0)
	ADDWFC      TFT_Text_cnt_L0+1, 0 
	MOVWF       FSR0H 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_TFT_Char_C+0 
	MOVF        FARG_TFT_Text_x+0, 0 
	MOVWF       FARG_TFT_Char_x+0 
	MOVF        FARG_TFT_Text_x+1, 0 
	MOVWF       FARG_TFT_Char_x+1 
	MOVF        FARG_TFT_Text_y+0, 0 
	MOVWF       FARG_TFT_Char_y+0 
	MOVF        FARG_TFT_Text_y+1, 0 
	MOVWF       FARG_TFT_Char_y+1 
	MOVF        FARG_TFT_Text_DimFont+0, 0 
	MOVWF       FARG_TFT_Char_DimFont+0 
	MOVF        FARG_TFT_Text_Fcolor+0, 0 
	MOVWF       FARG_TFT_Char_Fcolor+0 
	MOVF        FARG_TFT_Text_Fcolor+1, 0 
	MOVWF       FARG_TFT_Char_Fcolor+1 
	MOVF        FARG_TFT_Text_Bcolor+0, 0 
	MOVWF       FARG_TFT_Char_Bcolor+0 
	MOVF        FARG_TFT_Text_Bcolor+1, 0 
	MOVWF       FARG_TFT_Char_Bcolor+1 
	CALL        _TFT_Char+0, 0
;lcddriver.c,622 :: 		x = x + 16;
	MOVLW       16
	ADDWF       FARG_TFT_Text_x+0, 1 
	MOVLW       0
	ADDWFC      FARG_TFT_Text_x+1, 1 
;lcddriver.c,619 :: 		for(cnt = 0; cnt <= (lenght - 1); cnt++)
	INFSNZ      TFT_Text_cnt_L0+0, 1 
	INCF        TFT_Text_cnt_L0+1, 1 
;lcddriver.c,623 :: 		}
	GOTO        L_TFT_Text71
L_TFT_Text72:
;lcddriver.c,624 :: 		}
L_TFT_Text70:
L_TFT_Text69:
;lcddriver.c,625 :: 		}
L_end_TFT_Text:
	RETURN      0
; end of _TFT_Text

_TFT_Image:

;lcddriver.c,628 :: 		void TFT_Image(unsigned int pos_x,unsigned int pos_y,unsigned int dim_x,unsigned int dim_y,const unsigned int *picture){
;lcddriver.c,631 :: 		TFT_CS  = 0;
	BCF         TFT_CS+0, BitPos(TFT_CS+0) 
;lcddriver.c,632 :: 		TFT_Set_Address(pos_x, pos_y, pos_x + dim_x - 1, pos_y + dim_y - 1);
	MOVF        FARG_TFT_Image_pos_x+0, 0 
	MOVWF       FARG_TFT_Set_Address_PX1+0 
	MOVF        FARG_TFT_Image_pos_x+1, 0 
	MOVWF       FARG_TFT_Set_Address_PX1+1 
	MOVF        FARG_TFT_Image_pos_y+0, 0 
	MOVWF       FARG_TFT_Set_Address_PY1+0 
	MOVF        FARG_TFT_Image_pos_y+1, 0 
	MOVWF       FARG_TFT_Set_Address_PY1+1 
	MOVF        FARG_TFT_Image_dim_x+0, 0 
	ADDWF       FARG_TFT_Image_pos_x+0, 0 
	MOVWF       FARG_TFT_Set_Address_PX2+0 
	MOVF        FARG_TFT_Image_dim_x+1, 0 
	ADDWFC      FARG_TFT_Image_pos_x+1, 0 
	MOVWF       FARG_TFT_Set_Address_PX2+1 
	MOVLW       1
	SUBWF       FARG_TFT_Set_Address_PX2+0, 1 
	MOVLW       0
	SUBWFB      FARG_TFT_Set_Address_PX2+1, 1 
	MOVF        FARG_TFT_Image_dim_y+0, 0 
	ADDWF       FARG_TFT_Image_pos_y+0, 0 
	MOVWF       FARG_TFT_Set_Address_PY2+0 
	MOVF        FARG_TFT_Image_dim_y+1, 0 
	ADDWFC      FARG_TFT_Image_pos_y+1, 0 
	MOVWF       FARG_TFT_Set_Address_PY2+1 
	MOVLW       1
	SUBWF       FARG_TFT_Set_Address_PY2+0, 1 
	MOVLW       0
	SUBWFB      FARG_TFT_Set_Address_PY2+1, 1 
	CALL        _TFT_Set_Address+0, 0
;lcddriver.c,633 :: 		for(y = pos_y; y < (pos_y + dim_y); y++ ) {
	MOVF        FARG_TFT_Image_pos_y+0, 0 
	MOVWF       TFT_Image_y_L0+0 
	MOVF        FARG_TFT_Image_pos_y+1, 0 
	MOVWF       TFT_Image_y_L0+1 
L_TFT_Image74:
	MOVF        FARG_TFT_Image_dim_y+0, 0 
	ADDWF       FARG_TFT_Image_pos_y+0, 0 
	MOVWF       R1 
	MOVF        FARG_TFT_Image_dim_y+1, 0 
	ADDWFC      FARG_TFT_Image_pos_y+1, 0 
	MOVWF       R2 
	MOVF        R2, 0 
	SUBWF       TFT_Image_y_L0+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Image145
	MOVF        R1, 0 
	SUBWF       TFT_Image_y_L0+0, 0 
L__TFT_Image145:
	BTFSC       STATUS+0, 0 
	GOTO        L_TFT_Image75
;lcddriver.c,634 :: 		for(x = pos_x; x < (pos_x + dim_x); x++ ) {
	MOVF        FARG_TFT_Image_pos_x+0, 0 
	MOVWF       TFT_Image_x_L0+0 
	MOVF        FARG_TFT_Image_pos_x+1, 0 
	MOVWF       TFT_Image_x_L0+1 
L_TFT_Image77:
	MOVF        FARG_TFT_Image_dim_x+0, 0 
	ADDWF       FARG_TFT_Image_pos_x+0, 0 
	MOVWF       R1 
	MOVF        FARG_TFT_Image_dim_x+1, 0 
	ADDWFC      FARG_TFT_Image_pos_x+1, 0 
	MOVWF       R2 
	MOVF        R2, 0 
	SUBWF       TFT_Image_x_L0+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__TFT_Image146
	MOVF        R1, 0 
	SUBWF       TFT_Image_x_L0+0, 0 
L__TFT_Image146:
	BTFSC       STATUS+0, 0 
	GOTO        L_TFT_Image78
;lcddriver.c,635 :: 		Write_Data(*picture++);
	MOVF        FARG_TFT_Image_picture+0, 0 
	MOVWF       TBLPTRL 
	MOVF        FARG_TFT_Image_picture+1, 0 
	MOVWF       TBLPTRH 
	MOVF        FARG_TFT_Image_picture+2, 0 
	MOVWF       TBLPTRU 
	TBLRD*+
	MOVFF       TABLAT+0, FARG_Write_Data_Wdata+0
	TBLRD*+
	MOVFF       TABLAT+0, FARG_Write_Data_Wdata+1
	CALL        _Write_Data+0, 0
	MOVLW       2
	ADDWF       FARG_TFT_Image_picture+0, 1 
	MOVLW       0
	ADDWFC      FARG_TFT_Image_picture+1, 1 
	ADDWFC      FARG_TFT_Image_picture+2, 1 
;lcddriver.c,634 :: 		for(x = pos_x; x < (pos_x + dim_x); x++ ) {
	INFSNZ      TFT_Image_x_L0+0, 1 
	INCF        TFT_Image_x_L0+1, 1 
;lcddriver.c,636 :: 		}
	GOTO        L_TFT_Image77
L_TFT_Image78:
;lcddriver.c,633 :: 		for(y = pos_y; y < (pos_y + dim_y); y++ ) {
	INFSNZ      TFT_Image_y_L0+0, 1 
	INCF        TFT_Image_y_L0+1, 1 
;lcddriver.c,637 :: 		}
	GOTO        L_TFT_Image74
L_TFT_Image75:
;lcddriver.c,638 :: 		TFT_CS = 1;
	BSF         TFT_CS+0, BitPos(TFT_CS+0) 
;lcddriver.c,639 :: 		}
L_end_TFT_Image:
	RETURN      0
; end of _TFT_Image

_main:

;Simple_Functions_Example.c,201 :: 		void main() {
;Simple_Functions_Example.c,203 :: 		ADCON0 = 0x0F;           // turn off analog inputs
	MOVLW       15
	MOVWF       ADCON0+0 
;Simple_Functions_Example.c,204 :: 		ADCON1 = 0x0F;           // turn off analog inputs
	MOVLW       15
	MOVWF       ADCON1+0 
;Simple_Functions_Example.c,205 :: 		CMCON  |= 7;                            // Disable comparators
	MOVLW       7
	IORWF       CMCON+0, 1 
;Simple_Functions_Example.c,207 :: 		TRISA = 0;
	CLRF        TRISA+0 
;Simple_Functions_Example.c,208 :: 		TRISB = 0;
	CLRF        TRISB+0 
;Simple_Functions_Example.c,209 :: 		TRISD = 0;
	CLRF        TRISD+0 
;Simple_Functions_Example.c,210 :: 		TRISE = 0;
	CLRF        TRISE+0 
;Simple_Functions_Example.c,211 :: 		latA = 0x00;
	CLRF        LATA+0 
;Simple_Functions_Example.c,212 :: 		latB = 0x00;
	CLRF        LATB+0 
;Simple_Functions_Example.c,213 :: 		latD = 0x00;
	CLRF        LATD+0 
;Simple_Functions_Example.c,214 :: 		latE = 0x00;
	CLRF        LATE+0 
;Simple_Functions_Example.c,216 :: 		TFT_Init();
	CALL        _TFT_Init+0, 0
;Simple_Functions_Example.c,217 :: 		TFT_Fill(black);
	CLRF        FARG_TFT_Fill_color+0 
	CLRF        FARG_TFT_Fill_color+1 
	CALL        _TFT_Fill+0, 0
;Simple_Functions_Example.c,219 :: 		TFT_Text("A small text",0,0,8,black,white);
	MOVLW       ?lstr1_Simple_Functions_Example+0
	MOVWF       FARG_TFT_Text_S+0 
	MOVLW       hi_addr(?lstr1_Simple_Functions_Example+0)
	MOVWF       FARG_TFT_Text_S+1 
	CLRF        FARG_TFT_Text_x+0 
	CLRF        FARG_TFT_Text_x+1 
	CLRF        FARG_TFT_Text_y+0 
	CLRF        FARG_TFT_Text_y+1 
	MOVLW       8
	MOVWF       FARG_TFT_Text_DimFont+0 
	CLRF        FARG_TFT_Text_Fcolor+0 
	CLRF        FARG_TFT_Text_Fcolor+1 
	MOVLW       255
	MOVWF       FARG_TFT_Text_Bcolor+0 
	MOVLW       255
	MOVWF       FARG_TFT_Text_Bcolor+1 
	CALL        _TFT_Text+0, 0
;Simple_Functions_Example.c,220 :: 		delay_ms(1000);
	MOVLW       11
	MOVWF       R11, 0
	MOVLW       38
	MOVWF       R12, 0
	MOVLW       93
	MOVWF       R13, 0
L_main80:
	DECFSZ      R13, 1, 1
	BRA         L_main80
	DECFSZ      R12, 1, 1
	BRA         L_main80
	DECFSZ      R11, 1, 1
	BRA         L_main80
	NOP
	NOP
;Simple_Functions_Example.c,221 :: 		TFT_Text("A large text",0,20,16,black,white);
	MOVLW       ?lstr2_Simple_Functions_Example+0
	MOVWF       FARG_TFT_Text_S+0 
	MOVLW       hi_addr(?lstr2_Simple_Functions_Example+0)
	MOVWF       FARG_TFT_Text_S+1 
	CLRF        FARG_TFT_Text_x+0 
	CLRF        FARG_TFT_Text_x+1 
	MOVLW       20
	MOVWF       FARG_TFT_Text_y+0 
	MOVLW       0
	MOVWF       FARG_TFT_Text_y+1 
	MOVLW       16
	MOVWF       FARG_TFT_Text_DimFont+0 
	CLRF        FARG_TFT_Text_Fcolor+0 
	CLRF        FARG_TFT_Text_Fcolor+1 
	MOVLW       255
	MOVWF       FARG_TFT_Text_Bcolor+0 
	MOVLW       255
	MOVWF       FARG_TFT_Text_Bcolor+1 
	CALL        _TFT_Text+0, 0
;Simple_Functions_Example.c,222 :: 		delay_ms(1000);
	MOVLW       11
	MOVWF       R11, 0
	MOVLW       38
	MOVWF       R12, 0
	MOVLW       93
	MOVWF       R13, 0
L_main81:
	DECFSZ      R13, 1, 1
	BRA         L_main81
	DECFSZ      R12, 1, 1
	BRA         L_main81
	DECFSZ      R11, 1, 1
	BRA         L_main81
	NOP
	NOP
;Simple_Functions_Example.c,225 :: 		delay_ms(500);
	MOVLW       6
	MOVWF       R11, 0
	MOVLW       19
	MOVWF       R12, 0
	MOVLW       173
	MOVWF       R13, 0
L_main82:
	DECFSZ      R13, 1, 1
	BRA         L_main82
	DECFSZ      R12, 1, 1
	BRA         L_main82
	DECFSZ      R11, 1, 1
	BRA         L_main82
	NOP
	NOP
;Simple_Functions_Example.c,226 :: 		TFT_Fill(blue);
	MOVLW       31
	MOVWF       FARG_TFT_Fill_color+0 
	MOVLW       0
	MOVWF       FARG_TFT_Fill_color+1 
	CALL        _TFT_Fill+0, 0
;Simple_Functions_Example.c,227 :: 		delay_ms(500);
	MOVLW       6
	MOVWF       R11, 0
	MOVLW       19
	MOVWF       R12, 0
	MOVLW       173
	MOVWF       R13, 0
L_main83:
	DECFSZ      R13, 1, 1
	BRA         L_main83
	DECFSZ      R12, 1, 1
	BRA         L_main83
	DECFSZ      R11, 1, 1
	BRA         L_main83
	NOP
	NOP
;Simple_Functions_Example.c,228 :: 		TFT_Fill(black);
	CLRF        FARG_TFT_Fill_color+0 
	CLRF        FARG_TFT_Fill_color+1 
	CALL        _TFT_Fill+0, 0
;Simple_Functions_Example.c,229 :: 		delay_ms(500);
	MOVLW       6
	MOVWF       R11, 0
	MOVLW       19
	MOVWF       R12, 0
	MOVLW       173
	MOVWF       R13, 0
L_main84:
	DECFSZ      R13, 1, 1
	BRA         L_main84
	DECFSZ      R12, 1, 1
	BRA         L_main84
	DECFSZ      R11, 1, 1
	BRA         L_main84
	NOP
	NOP
;Simple_Functions_Example.c,230 :: 		TFT_Fill(green);
	MOVLW       224
	MOVWF       FARG_TFT_Fill_color+0 
	MOVLW       7
	MOVWF       FARG_TFT_Fill_color+1 
	CALL        _TFT_Fill+0, 0
;Simple_Functions_Example.c,231 :: 		delay_ms(500);
	MOVLW       6
	MOVWF       R11, 0
	MOVLW       19
	MOVWF       R12, 0
	MOVLW       173
	MOVWF       R13, 0
L_main85:
	DECFSZ      R13, 1, 1
	BRA         L_main85
	DECFSZ      R12, 1, 1
	BRA         L_main85
	DECFSZ      R11, 1, 1
	BRA         L_main85
	NOP
	NOP
;Simple_Functions_Example.c,232 :: 		TFT_Fill(l_gray);
	MOVLW       239
	MOVWF       FARG_TFT_Fill_color+0 
	MOVLW       123
	MOVWF       FARG_TFT_Fill_color+1 
	CALL        _TFT_Fill+0, 0
;Simple_Functions_Example.c,233 :: 		delay_ms(500);
	MOVLW       6
	MOVWF       R11, 0
	MOVLW       19
	MOVWF       R12, 0
	MOVLW       173
	MOVWF       R13, 0
L_main86:
	DECFSZ      R13, 1, 1
	BRA         L_main86
	DECFSZ      R12, 1, 1
	BRA         L_main86
	DECFSZ      R11, 1, 1
	BRA         L_main86
	NOP
	NOP
;Simple_Functions_Example.c,234 :: 		TFT_Fill(d_gray);
	MOVLW       138
	MOVWF       FARG_TFT_Fill_color+0 
	MOVLW       82
	MOVWF       FARG_TFT_Fill_color+1 
	CALL        _TFT_Fill+0, 0
;Simple_Functions_Example.c,235 :: 		delay_ms(500);
	MOVLW       6
	MOVWF       R11, 0
	MOVLW       19
	MOVWF       R12, 0
	MOVLW       173
	MOVWF       R13, 0
L_main87:
	DECFSZ      R13, 1, 1
	BRA         L_main87
	DECFSZ      R12, 1, 1
	BRA         L_main87
	DECFSZ      R11, 1, 1
	BRA         L_main87
	NOP
	NOP
;Simple_Functions_Example.c,236 :: 		TFT_Fill(cyan);
	MOVLW       255
	MOVWF       FARG_TFT_Fill_color+0 
	MOVLW       7
	MOVWF       FARG_TFT_Fill_color+1 
	CALL        _TFT_Fill+0, 0
;Simple_Functions_Example.c,237 :: 		delay_ms(500);
	MOVLW       6
	MOVWF       R11, 0
	MOVLW       19
	MOVWF       R12, 0
	MOVLW       173
	MOVWF       R13, 0
L_main88:
	DECFSZ      R13, 1, 1
	BRA         L_main88
	DECFSZ      R12, 1, 1
	BRA         L_main88
	DECFSZ      R11, 1, 1
	BRA         L_main88
	NOP
	NOP
;Simple_Functions_Example.c,238 :: 		TFT_Fill(red);
	MOVLW       0
	MOVWF       FARG_TFT_Fill_color+0 
	MOVLW       248
	MOVWF       FARG_TFT_Fill_color+1 
	CALL        _TFT_Fill+0, 0
;Simple_Functions_Example.c,239 :: 		delay_ms(500);
	MOVLW       6
	MOVWF       R11, 0
	MOVLW       19
	MOVWF       R12, 0
	MOVLW       173
	MOVWF       R13, 0
L_main89:
	DECFSZ      R13, 1, 1
	BRA         L_main89
	DECFSZ      R12, 1, 1
	BRA         L_main89
	DECFSZ      R11, 1, 1
	BRA         L_main89
	NOP
	NOP
;Simple_Functions_Example.c,240 :: 		TFT_Fill(yellow);
	MOVLW       224
	MOVWF       FARG_TFT_Fill_color+0 
	MOVLW       255
	MOVWF       FARG_TFT_Fill_color+1 
	CALL        _TFT_Fill+0, 0
;Simple_Functions_Example.c,241 :: 		delay_ms(1000);
	MOVLW       11
	MOVWF       R11, 0
	MOVLW       38
	MOVWF       R12, 0
	MOVLW       93
	MOVWF       R13, 0
L_main90:
	DECFSZ      R13, 1, 1
	BRA         L_main90
	DECFSZ      R12, 1, 1
	BRA         L_main90
	DECFSZ      R11, 1, 1
	BRA         L_main90
	NOP
	NOP
;Simple_Functions_Example.c,243 :: 		TFT_Box(10,10,60,80,blue);
	MOVLW       10
	MOVWF       FARG_TFT_Box_x1+0 
	MOVLW       0
	MOVWF       FARG_TFT_Box_x1+1 
	MOVLW       10
	MOVWF       FARG_TFT_Box_y1+0 
	MOVLW       0
	MOVWF       FARG_TFT_Box_y1+1 
	MOVLW       60
	MOVWF       FARG_TFT_Box_x2+0 
	MOVLW       0
	MOVWF       FARG_TFT_Box_x2+1 
	MOVLW       80
	MOVWF       FARG_TFT_Box_y2+0 
	MOVLW       0
	MOVWF       FARG_TFT_Box_y2+1 
	MOVLW       31
	MOVWF       FARG_TFT_Box_color+0 
	MOVLW       0
	MOVWF       FARG_TFT_Box_color+1 
	CALL        _TFT_Box+0, 0
;Simple_Functions_Example.c,244 :: 		delay_ms(1000);
	MOVLW       11
	MOVWF       R11, 0
	MOVLW       38
	MOVWF       R12, 0
	MOVLW       93
	MOVWF       R13, 0
L_main91:
	DECFSZ      R13, 1, 1
	BRA         L_main91
	DECFSZ      R12, 1, 1
	BRA         L_main91
	DECFSZ      R11, 1, 1
	BRA         L_main91
	NOP
	NOP
;Simple_Functions_Example.c,246 :: 		TFT_Dot(100,50,black);
	MOVLW       100
	MOVWF       FARG_TFT_Dot_x+0 
	MOVLW       0
	MOVWF       FARG_TFT_Dot_x+1 
	MOVLW       50
	MOVWF       FARG_TFT_Dot_y+0 
	MOVLW       0
	MOVWF       FARG_TFT_Dot_y+1 
	CLRF        FARG_TFT_Dot_color+0 
	CLRF        FARG_TFT_Dot_color+1 
	CALL        _TFT_Dot+0, 0
;Simple_Functions_Example.c,247 :: 		delay_ms(1000);
	MOVLW       11
	MOVWF       R11, 0
	MOVLW       38
	MOVWF       R12, 0
	MOVLW       93
	MOVWF       R13, 0
L_main92:
	DECFSZ      R13, 1, 1
	BRA         L_main92
	DECFSZ      R12, 1, 1
	BRA         L_main92
	DECFSZ      R11, 1, 1
	BRA         L_main92
	NOP
	NOP
;Simple_Functions_Example.c,249 :: 		TFT_Line(10,10,200,200,purple);
	MOVLW       10
	MOVWF       FARG_TFT_Line_x1+0 
	MOVLW       0
	MOVWF       FARG_TFT_Line_x1+1 
	MOVLW       10
	MOVWF       FARG_TFT_Line_y1+0 
	MOVLW       0
	MOVWF       FARG_TFT_Line_y1+1 
	MOVLW       200
	MOVWF       FARG_TFT_Line_x2+0 
	MOVLW       0
	MOVWF       FARG_TFT_Line_x2+1 
	MOVLW       200
	MOVWF       FARG_TFT_Line_y2+0 
	MOVLW       0
	MOVWF       FARG_TFT_Line_y2+1 
	MOVLW       31
	MOVWF       FARG_TFT_Line_color+0 
	MOVLW       241
	MOVWF       FARG_TFT_Line_color+1 
	CALL        _TFT_Line+0, 0
;Simple_Functions_Example.c,250 :: 		delay_ms(1000);
	MOVLW       11
	MOVWF       R11, 0
	MOVLW       38
	MOVWF       R12, 0
	MOVLW       93
	MOVWF       R13, 0
L_main93:
	DECFSZ      R13, 1, 1
	BRA         L_main93
	DECFSZ      R12, 1, 1
	BRA         L_main93
	DECFSZ      R11, 1, 1
	BRA         L_main93
	NOP
	NOP
;Simple_Functions_Example.c,252 :: 		TFT_H_Line(100,150,100,l_gray);
	MOVLW       100
	MOVWF       FARG_TFT_H_Line_x1+0 
	MOVLW       150
	MOVWF       FARG_TFT_H_Line_x2+0 
	MOVLW       100
	MOVWF       FARG_TFT_H_Line_y_pos+0 
	MOVLW       0
	MOVWF       FARG_TFT_H_Line_y_pos+1 
	MOVLW       239
	MOVWF       FARG_TFT_H_Line_color+0 
	MOVLW       123
	MOVWF       FARG_TFT_H_Line_color+1 
	CALL        _TFT_H_Line+0, 0
;Simple_Functions_Example.c,253 :: 		delay_ms(1000);
	MOVLW       11
	MOVWF       R11, 0
	MOVLW       38
	MOVWF       R12, 0
	MOVLW       93
	MOVWF       R13, 0
L_main94:
	DECFSZ      R13, 1, 1
	BRA         L_main94
	DECFSZ      R12, 1, 1
	BRA         L_main94
	DECFSZ      R11, 1, 1
	BRA         L_main94
	NOP
	NOP
;Simple_Functions_Example.c,255 :: 		TFT_V_Line(100,150,100,l_gray);
	MOVLW       100
	MOVWF       FARG_TFT_V_Line_y1+0 
	MOVLW       0
	MOVWF       FARG_TFT_V_Line_y1+1 
	MOVLW       150
	MOVWF       FARG_TFT_V_Line_y2+0 
	MOVLW       0
	MOVWF       FARG_TFT_V_Line_y2+1 
	MOVLW       100
	MOVWF       FARG_TFT_V_Line_x_pos+0 
	MOVLW       239
	MOVWF       FARG_TFT_V_Line_color+0 
	MOVLW       123
	MOVWF       FARG_TFT_V_Line_color+1 
	CALL        _TFT_V_Line+0, 0
;Simple_Functions_Example.c,256 :: 		delay_ms(1000);
	MOVLW       11
	MOVWF       R11, 0
	MOVLW       38
	MOVWF       R12, 0
	MOVLW       93
	MOVWF       R13, 0
L_main95:
	DECFSZ      R13, 1, 1
	BRA         L_main95
	DECFSZ      R12, 1, 1
	BRA         L_main95
	DECFSZ      R11, 1, 1
	BRA         L_main95
	NOP
	NOP
;Simple_Functions_Example.c,258 :: 		TFT_Rectangle(10,10,200,200,d_gray);
	MOVLW       10
	MOVWF       FARG_TFT_Rectangle_x1+0 
	MOVLW       0
	MOVWF       FARG_TFT_Rectangle_x1+1 
	MOVLW       10
	MOVWF       FARG_TFT_Rectangle_y1+0 
	MOVLW       0
	MOVWF       FARG_TFT_Rectangle_y1+1 
	MOVLW       200
	MOVWF       FARG_TFT_Rectangle_x2+0 
	MOVLW       0
	MOVWF       FARG_TFT_Rectangle_x2+1 
	MOVLW       200
	MOVWF       FARG_TFT_Rectangle_y2+0 
	MOVLW       0
	MOVWF       FARG_TFT_Rectangle_y2+1 
	MOVLW       138
	MOVWF       FARG_TFT_Rectangle_color+0 
	MOVLW       82
	MOVWF       FARG_TFT_Rectangle_color+1 
	CALL        _TFT_Rectangle+0, 0
;Simple_Functions_Example.c,259 :: 		delay_ms(1000);
	MOVLW       11
	MOVWF       R11, 0
	MOVLW       38
	MOVWF       R12, 0
	MOVLW       93
	MOVWF       R13, 0
L_main96:
	DECFSZ      R13, 1, 1
	BRA         L_main96
	DECFSZ      R12, 1, 1
	BRA         L_main96
	DECFSZ      R11, 1, 1
	BRA         L_main96
	NOP
	NOP
;Simple_Functions_Example.c,261 :: 		TFT_Circle(80,80,20,1,black);
	MOVLW       80
	MOVWF       FARG_TFT_Circle_x+0 
	MOVLW       0
	MOVWF       FARG_TFT_Circle_x+1 
	MOVLW       80
	MOVWF       FARG_TFT_Circle_y+0 
	MOVLW       0
	MOVWF       FARG_TFT_Circle_y+1 
	MOVLW       20
	MOVWF       FARG_TFT_Circle_radius+0 
	MOVLW       1
	MOVWF       FARG_TFT_Circle_fill+0 
	CLRF        FARG_TFT_Circle_color+0 
	CLRF        FARG_TFT_Circle_color+1 
	CALL        _TFT_Circle+0, 0
;Simple_Functions_Example.c,262 :: 		delay_ms(1000);
	MOVLW       11
	MOVWF       R11, 0
	MOVLW       38
	MOVWF       R12, 0
	MOVLW       93
	MOVWF       R13, 0
L_main97:
	DECFSZ      R13, 1, 1
	BRA         L_main97
	DECFSZ      R12, 1, 1
	BRA         L_main97
	DECFSZ      R11, 1, 1
	BRA         L_main97
	NOP
	NOP
;Simple_Functions_Example.c,264 :: 		TFT_Circle(80,80,20,0,purple);
	MOVLW       80
	MOVWF       FARG_TFT_Circle_x+0 
	MOVLW       0
	MOVWF       FARG_TFT_Circle_x+1 
	MOVLW       80
	MOVWF       FARG_TFT_Circle_y+0 
	MOVLW       0
	MOVWF       FARG_TFT_Circle_y+1 
	MOVLW       20
	MOVWF       FARG_TFT_Circle_radius+0 
	CLRF        FARG_TFT_Circle_fill+0 
	MOVLW       31
	MOVWF       FARG_TFT_Circle_color+0 
	MOVLW       241
	MOVWF       FARG_TFT_Circle_color+1 
	CALL        _TFT_Circle+0, 0
;Simple_Functions_Example.c,265 :: 		delay_ms(1000);
	MOVLW       11
	MOVWF       R11, 0
	MOVLW       38
	MOVWF       R12, 0
	MOVLW       93
	MOVWF       R13, 0
L_main98:
	DECFSZ      R13, 1, 1
	BRA         L_main98
	DECFSZ      R12, 1, 1
	BRA         L_main98
	DECFSZ      R11, 1, 1
	BRA         L_main98
	NOP
	NOP
;Simple_Functions_Example.c,267 :: 		TFT_Image(0,240,40,83,image);
	CLRF        FARG_TFT_Image_pos_x+0 
	CLRF        FARG_TFT_Image_pos_x+1 
	MOVLW       240
	MOVWF       FARG_TFT_Image_pos_y+0 
	MOVLW       0
	MOVWF       FARG_TFT_Image_pos_y+1 
	MOVLW       40
	MOVWF       FARG_TFT_Image_dim_x+0 
	MOVLW       0
	MOVWF       FARG_TFT_Image_dim_x+1 
	MOVLW       83
	MOVWF       FARG_TFT_Image_dim_y+0 
	MOVLW       0
	MOVWF       FARG_TFT_Image_dim_y+1 
	MOVLW       _image+0
	MOVWF       FARG_TFT_Image_picture+0 
	MOVLW       hi_addr(_image+0)
	MOVWF       FARG_TFT_Image_picture+1 
	MOVLW       higher_addr(_image+0)
	MOVWF       FARG_TFT_Image_picture+2 
	CALL        _TFT_Image+0, 0
;Simple_Functions_Example.c,269 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
