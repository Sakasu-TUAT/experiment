/*
$B%(%_%e%l!<%?$N>pJs(B
*/

#if !defined _EMULATER_H_
#define _EMULATER_H_

typedef enum p386_state_ {
  P386_STATE_INIT,  /* $BL$3+;O(B */
  P386_STATE_RUNNING,  /* $B<B9TCf(B */
  P386_STATE_INT,  /* $B3d$j9~$_=hM}Cf(B */
  P386_STATE_UNKINT,  /* $BITL@$J3d$j9~$_$K$h$jDd;_(B */
  P386_STATE_ILINST,  /* $BIT@5$J%3!<%I$K$h$jDd;_(B */
  P386_STATE_HALT,  /* HLT $BL?Na$,<B9T$5$lDd;_(B */
  P386_STATE_UNSRPT  /* $BL$%5%]!<%H$N5!G=$r<B9T$7$h$&$H$7$FDd;_(B */
} p386_state_t;

#endif /* _EMULATER_H_ */
