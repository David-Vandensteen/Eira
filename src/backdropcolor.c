#include <stdlib.h>
#include <video.h>
#include <math.h>
#include "backdropcolor.h"
#include "neo_db.h"

void backdropColorNext(WORD *curColorTableIndex){
	switch (*curColorTableIndex)
	{
	case 0:
		BGCOLOR000
			*curColorTableIndex += 1;
		break;
	case 1:
		BGCOLOR001
			*curColorTableIndex += 1;
		break;
	case 2:
		BGCOLOR002
			*curColorTableIndex += 1;
		break;
	case 3:
		BGCOLOR003
			*curColorTableIndex += 1;
		break;
	case 4:
		BGCOLOR004
			*curColorTableIndex += 1;
		break;
	case 5:
		BGCOLOR005
			*curColorTableIndex += 1;
		break;
	case 6:
		BGCOLOR006
			*curColorTableIndex += 1;
		break;
	case 7:
		BGCOLOR007
			*curColorTableIndex += 1;
		break;
	case 8:
		BGCOLOR008
			*curColorTableIndex += 1;
		break;
	case 9:
		BGCOLOR009
			*curColorTableIndex += 1;
		break;
	case 10:
		BGCOLOR010
			*curColorTableIndex += 1;
		break;
	case 11:
		BGCOLOR011
			*curColorTableIndex += 1;
		break;
	default:
		break;
	}
}
