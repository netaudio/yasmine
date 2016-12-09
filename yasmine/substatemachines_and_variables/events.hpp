//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
// This file is part of the Seadex yasmine ecosystem (http://yasmine.seadex.de).                    //
// Copyright (C) 2016 Seadex GmbH                                                                   //
//                                                                                                  //
// Licensing information is available in the folder "license" which is part of this distribution.   //
// The same information is available on the www @ http://yasmine.seadex.de/License.html.            //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef EVENTS_9579372F_23DD_4365_927A_48C94C0A2585
#define EVENTS_9579372F_23DD_4365_927A_48C94C0A2585


#include "yasmine.hpp"


namespace sxy
{


namespace
{


		// DONE we need defines for C++03!
#ifndef Y_CPP03_BOOST
	constexpr event_id EVENT_1 = 1;
	constexpr event_id EVENT_2 = 2;
	constexpr event_id EVENT_3 = 3;
	constexpr event_id EVENT_4 = 4;
	constexpr event_id EVENT_5 = 5;
#else
	#define EVENT_1 1
	#define EVENT_2 2
	#define EVENT_3 3
	#define EVENT_4 4
	#define EVENT_5 5
#endif

}


		Y_EVENT_WITH_ID( event_1, EVENT_1 );
		Y_EVENT_WITH_ID( event_2, EVENT_2 );
		Y_EVENT_WITH_ID( event_3, EVENT_3 );
		Y_EVENT_WITH_ID( event_4, EVENT_4 );
		Y_EVENT_1PARAM_WITH_ID( event_5, std::string, get_param, EVENT_5 );


}


#endif
