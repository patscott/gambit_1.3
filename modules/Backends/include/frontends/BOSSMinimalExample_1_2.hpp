//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Example of a backend the loads classes.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Pat Scott 
///          (p.scott@imperial.ac.uk)
///  \date 2014 Oct
///
///  *********************************************

// Specify the path to the shared library along with a backend name. */
#include "backend_types/BOSSMinimalExample_1_2/identification.hpp"

// Begin
LOAD_LIBRARY

// Set models that this backend can be used with.  If absent, all models are allowed.

// Functions

// Variables

// Initialisation function (dependencies)

// Convenience functions (registration)

// Initialisation function (definition)
BE_INI_FUNCTION{} DONE

// Convenience functions (definitions)

// End
#include "backend_undefs.hpp"
