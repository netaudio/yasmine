//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
// This file is part of the Seadex yasmine ecosystem (http://yasmine.seadex.de).                    //
// Copyright (C) 2016 Seadex GmbH                                                                   //
//                                                                                                  //
// Licensing information is available in the folder "license" which is part of this distribution.   //
// The same information is available on the www @ http://yasmine.seadex.de/License.html.            //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef DETECTOR_5EBE86D2_647F_4029_94D8_B5521F641349
#define DETECTOR_5EBE86D2_647F_4029_94D8_B5521F641349


#include "compatibility.hpp"
#include "thread.hpp"
#include "non_copyable.hpp"


namespace examples
{


class detector_callback;


class detector Y_FINAL
{
public:
	explicit detector( detector_callback& _detector_callback );
	~detector();
	Y_NO_COPY( detector )
	void start();
	void stop();
	bool is_on();


private:
	void generate_detector_events();


	detector_callback& detector_callback_;
	bool is_on_;
	sxy::Y_UNIQUE_PTR< sxy::thread > generate_random_detector_events_;
	bool run_;
	sxy::mutex mutex_;
	sxy::condition_variable condition_variable_;
};


}


#endif