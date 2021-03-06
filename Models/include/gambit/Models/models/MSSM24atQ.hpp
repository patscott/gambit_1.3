//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  MSSM24atQ model definition. 
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Pat Scott  
///          (p.scott@imperial.ac.uk)
///  \date 2015 Sep
///
///  *********************************************

#ifndef __MSSM24atQ_hpp__
#define __MSSM24atQ_hpp__

// Parent model must be declared first! Include it here to ensure that this happens.
#include "gambit/Models/models/MSSM25atQ.hpp"

#define MODEL MSSM24atQ
#define PARENT MSSM25atQ
  START_MODEL

  DEFINEPARS(Qin,TanBeta,SignMu,
             mHu2,mHd2,M1,M2,M3)

  DEFINEPARS(mq2_1, mq2_2, mq2_3)
 
  DEFINEPARS(ml2_1, ml2_2, ml2_3)

  DEFINEPARS(md2_1, md2_2, md2_3)

  DEFINEPARS(mu2_1, mu2_2, mu2_3)

  DEFINEPARS(me2_1, me2_2, me2_3)

  DEFINEPARS(Ae_3)
  
  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM24atQ_to_MSSM25atQ)

#undef PARENT
#undef MODEL

#endif
