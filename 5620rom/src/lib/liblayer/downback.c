/* */
/*									*/
/*	Copyright (c) 1985,1986,1987,1988,1989,1990,1991,1992   AT&T	*/
/*			All Rights Reserved				*/
/*									*/
/*	  THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T.		*/
/*	    The copyright notice above does not evidence any		*/
/*	   actual or intended publication of such source code.		*/
/*									*/
/* */
/*
 * Move a layer to the back of the screen
 */
#include <dmd.h>
#include <layer.h>

/*
#undef	lfront
#undef	lback
Layer	*lfront, *lback;
#define	lfront	Slfront
#define	lback	Slback
*/

#undef	downback
downback(lp)
#define	downback Sdownback
	register Layer *lp;
{
	register Layer *bk, *m;
	register Obscured *op, *next;
	Rectangle r;
	if(lp==0 || lp->back==0)
		return;		/* Why continue? */
	cursinhibit();
	for(bk=lp->back; bk; bk=bk->back){
		/* Do they overlap? */
		if(rectXrect(bk->rect, lp->rect)==0)	/* Nothing to do */
			continue;
		for(op=bk->obs; op; op=next){
			next=op->next;	/* remember... */
			if(op->lobs==lp){	/* overlap */
				/*
				 * Swap obscured portion and screen
				 */
				screenswap(op->bmap, op->rect, op->rect);
				/*
				 * Remove op from bk
				 */
				if(op->prev)
					op->prev->next=op->next;
				else
					bk->obs=op->next;
				if(op->next)
					op->next->prev=op->prev;
				/* Put in lp */
				op->next=lp->obs;
				op->prev=0;
				if(lp->obs)
					lp->obs->prev=op;
				lp->obs=op;
				/*
				 * A new layer now occupies this space, so
				 * fix all the lobs's.
				 */
				op->lobs=bk;
				r=op->rect;
				for(m=lback; m!=bk; m=m->front)
					for(op=m->obs; op; op=op->next)
						if(rectXrect(op->rect, r))
							op->lobs=bk;
			}
		}
	}
	/*
	 * Put lp at back
	 */
	if(lback!=lp){
		if(lfront==lp)
			lfront=lp->back;
		if(lp->front)
			lp->front->back=lp->back;
		lp->back->front=lp->front;
		lback->back=lp;
		lp->front=lback;
		lp->back=0;
		lback=lp;
	}
	cursallow();
}

