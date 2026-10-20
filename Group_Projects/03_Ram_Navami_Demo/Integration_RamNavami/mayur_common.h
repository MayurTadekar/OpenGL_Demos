

#ifndef     VALUE_FROM_PERCENT
#define 	VALUE_FROM_PERCENT(complete, percent)	(complete * percent / 100.0)
#define 	VFP(complete, percent)	(VALUE_FROM_PERCENT(complete, percent))
#define 	VFP_2F(x, y, p)	glVertex2f(VFP(x,p), VFP(y,p))
#define 	VFP_2FXY(x, y, px, py)	glVertex2f(VFP(x,px), VFP(y,py))
#define 	VFP_2FXY_TXY(x, y, px, py, xp, yp)	glVertex2f(VFP(x,px) + xp, VFP(y,py) + yp)
#define 	V2F(x, y)	glVertex2f(x, y)
#endif      /* VALUE_FROM_PERCENT */
