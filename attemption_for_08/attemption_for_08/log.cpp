#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "GLOBAL_CONST.h"
#include "Processing_Func.h"

int log(Processing_Struct MAIN_struct1, Processing_Struct MAIN_struct2, Processing_Struct MAIN_struct3, Processing_Struct MAIN_struct4, long N_itt) {
	out << "1: "<<MAIN_struct1.a6.size() << " of" << N_itt<< " D1: "  << MAIN_struct1.Block_D1[0]<< " D2: " <<MAIN_struct1.Block_D2[0]<< " T_end: " <<MAIN_struct1.T_end<< endl;
	out << "2: "<<MAIN_struct2.a6.size() << " of" << N_itt<< " D1: "  << MAIN_struct2.Block_D1[0]<< " D2: " <<MAIN_struct2.Block_D2[0]<< " T_end: " <<MAIN_struct2.T_end<< endl;
	out << "3: "<<MAIN_struct3.a6.size() << " of" << N_itt*2<< " D1: "  << MAIN_struct3.Block_D1[0]<< " D2: " <<MAIN_struct3.Block_D2[0]<< " T_end: " <<MAIN_struct3.T_end<< endl;
	out << "4: "<<MAIN_struct4.a6.size() << " of" << N_itt*2<< " D1: "  << MAIN_struct4.Block_D1[0]<< " D2: " <<MAIN_struct4.Block_D2[0]<< " T_end: " <<MAIN_struct4.T_end<< endl;
	return 0;
}