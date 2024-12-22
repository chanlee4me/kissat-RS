#ifndef _bump_h_INCLUDED
#define _bump_h_INCLUDED

#include <stdbool.h>

struct kissat;
//added by cl
void kissat_bump_analyzed (struct kissat *, int);
//end
void kissat_update_scores (struct kissat *);
void kissat_rescale_scores (struct kissat *);
//added bl cl
void kissat_bump_variable (struct kissat *, unsigned , int);
//end
void kissat_bump_score_increment (struct kissat *);

#define MAX_SCORE 1e150

#endif
