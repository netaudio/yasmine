//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
// This file is part of the Seadex yasmine ecosystem (http://yasmine.seadex.de).                    //
// Copyright (C) 2016 Seadex GmbH                                                                   //
//                                                                                                  //
// Licensing information is available in the folder "license" which is part of this distribution.   //
// The same information is available on the www @ http://yasmine.seadex.de/License.html.            //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef SHALLOW_HISTORY_2F18336E_AEBD_4040_B40D_E96E0738B83E
#define SHALLOW_HISTORY_2F18336E_AEBD_4040_B40D_E96E0738B83E


#include "history.hpp"
#include "shallow_history_fwd.hpp"


namespace sxy
{


class shallow_history:
	public virtual history
{
public:
	shallow_history()
	{
		// Nothing to do...
	}


	virtual ~shallow_history() Y_NOEXCEPT Y_OVERRIDE
	{
		// Nothing to do...
	}


	Y_NO_COPY(shallow_history)
};


}


#endif
