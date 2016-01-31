
%module swig

%include "std_string.i"

%import "entity.h"
%import "typedef.h"

using namespace std;

%{

	/* Includes the header in the wrapper code */
	#include "npc.h"
	typedef arg3::game::storage storage;
	typedef arg3::game::storage_builder storage_builder;
%}

/* Parse the header file to generate wrappers */
typedef arg3::game::storage storage;
typedef arg3::game::storage_builder storage_builder;
%include "character.h"
%include "npc.h"

