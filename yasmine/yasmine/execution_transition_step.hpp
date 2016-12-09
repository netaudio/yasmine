//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
// This file is part of the Seadex yasmine ecosystem (http://yasmine.seadex.de).                    //
// Copyright (C) 2016 Seadex GmbH                                                                   //
//                                                                                                  //
// Licensing information is available in the folder "license" which is part of this distribution.   //
// The same information is available on the www @ http://yasmine.seadex.de/License.html.            //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef EXECUTION_TRANSITION_STEP_H_94397D2C_C792_4163_B87A_1CB4931208779
#define EXECUTION_TRANSITION_STEP_H_94397D2C_C792_4163_B87A_1CB4931208779


#include "execution_step.hpp"


namespace sxy
{


class transition_step;


class execution_transition_step Y_FINAL:
	public execution_step
{
public:
	explicit execution_transition_step( transition_step& _transition_step );
	virtual ~execution_transition_step() Y_NOEXCEPT Y_OVERRIDE;
	Y_NO_COPY(execution_transition_step)
	virtual bool execute_behaviour( event_processing_callback* const _event_processing_callback, 
		const event& _event, events& _exception_events,	async_event_handler* const _async_event_handler ) const Y_OVERRIDE;
	virtual void accept( execution_step_visitor& _visitor ) const Y_OVERRIDE;
	const transition_step& get_transition_step() const;


private:
	transition_step& transition_step_;
};


}


#endif
