//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
// This file is part of the Seadex yasmine ecosystem (http://yasmine.seadex.de).                    //
// Copyright (C) 2016 Seadex GmbH                                                                   //
//                                                                                                  //
// Licensing information is available in the folder "license" which is part of this distribution.   //
// The same information is available on the www @ http://yasmine.seadex.de/License.html.            //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef VERTEX_FWD_9F913860_C5C3_4773_BB31_D98183BE0565
#define VERTEX_FWD_9F913860_C5C3_4773_BB31_D98183BE0565


#include <vector>

#include "compatibility.hpp"


namespace sxy
{


class vertex;
typedef Y_UNIQUE_PTR< vertex > vertex_uptr;
typedef std::vector< const vertex* > raw_const_vertices;
typedef std::vector< vertex_uptr > vertices;


}


#endif
