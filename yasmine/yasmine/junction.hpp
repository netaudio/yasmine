//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
// This file is part of the Seadex yasmine ecosystem (http://yasmine.seadex.de).                    //
// Copyright (C) 2016 Seadex GmbH                                                                   //
//                                                                                                  //
// Licensing information is available in the folder "license" which is part of this distribution.   //
// The same information is available on the www @ http://yasmine.seadex.de/License.html.            //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef JUNCTION_C9792E4F_85DB_4377_AFE4_E1A1B9F101E0
#define JUNCTION_C9792E4F_85DB_4377_AFE4_E1A1B9F101E0


#include "region_pseudostate.hpp"
#include "join_fwd.hpp"


namespace sxy
{


class junction:
	public virtual region_pseudostate
{
public:
	junction()
	{
		// Nothing to do...
	}


	virtual ~junction() Y_NOEXCEPT Y_OVERRIDE
	{
		// Nothing to do...
	}


	Y_NO_COPY(junction)
};


}


#endif
