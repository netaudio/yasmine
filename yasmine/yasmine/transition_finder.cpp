//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
// This file is part of the Seadex yasmine ecosystem (http://yasmine.seadex.de).                    //
// Copyright (C) 2016 Seadex GmbH                                                                   //
//                                                                                                  //
// Licensing information is available in the folder "license" which is part of this distribution.   //
// The same information is available on the www @ http://yasmine.seadex.de/License.html.            //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include "transition_finder.hpp"

#include "log_and_throw.hpp"
#include "composite_state.hpp"
#include "region.hpp"
#include "initial_pseudostate.hpp"
#include "choice.hpp"
#include "transition.hpp"
#include "compound_transition_builder.hpp"
#include "event_impl.hpp"


namespace sxy
{


transition_finder::transition_finder() = default;


void transition_finder::search_for_enabled_transitions_in_all_regions( const state& _current_state, 
	const event& _event,	compound_transitions& _enabled_compound_transitions,	bool& _event_is_deferred ) const
{
	search_for_transition( _current_state, _enabled_compound_transitions, _event, _event_is_deferred );
}


void transition_finder::search_for_enabled_completion_transitions_in_all_regions(	const state& _current_state,
	compound_transitions& _enabled_compound_transitions,	bool& _event_is_deferred ) const
{
	const auto completion_event = std::make_shared< event_impl >( COMPLETION_EVENT );
	search_for_transition( _current_state, _enabled_compound_transitions, *completion_event, _event_is_deferred );
}


void transition_finder::search_initial_transitions(	const composite_state& _state,	
	compound_transitions& _compound_transitions )
{
	for( const auto & region : _state.get_regions() )
	{
		Y_LOG( log_level::LL_TRACE, "Searching for initial state in region '%'.", region->get_name() );
		const auto initial_pseudostate = region->get_initial_pseudostate();
		if( initial_pseudostate )
		{
			Y_LOG( log_level::LL_TRACE, "Initial pseudostate '%' found in region '%'.",
				initial_pseudostate->get_name(), region->get_name() );
			const auto transition = initial_pseudostate->get_transition();
			const auto complition_event = std::make_shared< event_impl >( COMPLETION_EVENT );
			if( !try_to_build_compound_transition( *transition, _compound_transitions, *complition_event ) )
			{
				LOG_AND_THROW( log_level::LL_FATAL,
					"A compound transition could not be built for the initial transition emitting from the initial pseudostate '%'!",
					initial_pseudostate->get_name() );
			}
		}
		else
		{
			Y_LOG( log_level::LL_TRACE, "No initial pseudostate found in region '%'.", region->get_name() );
		}
	}
}


void transition_finder::search_choice_transitions( const raw_const_choices& _choices, 
	compound_transitions& _compound_transitions,	const event& _event )
{
	for( const auto choice : _choices )
	{
		Y_ASSERT( choice, "Choice pointer is null. This cannot be a nullptr." );
		Y_LOG( log_level::LL_SPAM, "Checking outgoing transition(s) of choice '%'. It has % outgoing transitions.",
			choice->get_name(), choice->get_outgoing_transitions().size() );
		auto at_least_one_transition_is_enabled = false;

		for( auto & transition : choice->get_outgoing_transitions() )
		{
			Y_ASSERT( transition->can_accept_event(	COMPLETION_EVENT ), 
				"Transition leaving choice is not a completion transition!" );
			Y_LOG( log_level::LL_SPAM, "Checking outgoing transition '%' of choice '%' for guard.",
				transition->get_name(), choice->get_name() );
			const auto guard_evaluated_to_true = transition->check_guard( _event );
			if( guard_evaluated_to_true )
			{
				Y_LOG( log_level::LL_SPAM, "Guard of outgoing transition '%' of choice '%' evaluates to true.",
					transition->get_name(), choice->get_name() );
				if( !try_to_build_compound_transition( *transition, _compound_transitions, _event ) )
				{
					LOG_AND_THROW( log_level::LL_FATAL, 
						"Transition following choice '%' could not be built in compound transition!",	choice->get_name() );
				}
				else
				{
					at_least_one_transition_is_enabled = true;
				}

				break;
			}
			else
			{
				Y_LOG( log_level::LL_SPAM, "Guard of outgoing transition '%' of choice '%' evaluates to false.",
					transition->get_name(), choice->get_name() );
			}
		}

		if( !at_least_one_transition_is_enabled )
		{
			LOG_AND_THROW( log_level::LL_FATAL, "No transition is enabled for choice '%'!", choice->get_name() );
		}
	}
}


transition* transition_finder::search_completion_transition( const state& _state )
{
	transition* completion_transition = nullptr;
	if( _state.is_complete() )
	{
		Y_LOG( log_level::LL_SPAM, "State '%' is complete.", _state.get_name() );
		const auto completion_event = std::make_shared< event_impl >( COMPLETION_EVENT );
		completion_transition = _state.search_transition( *completion_event );
	}

	return( completion_transition );
}


bool transition_finder::search_for_transition( const state& _current_state, 
	compound_transitions& _enabled_compound_transitions,	const event& _event,	bool& _event_is_deferred ) const
{
	Y_LOG( log_level::LL_SPAM, "Search for transition in state '%'.", _current_state.get_name() );
	auto found = false;
	const auto& regions = _current_state.get_regions();

	for( const auto & region : regions )
	{
		Y_LOG( log_level::LL_SPAM, "Search for active state in region '%'.", region->get_name() );
		const auto active_state = region->get_active_state();
		if( active_state )
		{
			Y_LOG( log_level::LL_SPAM, "Found active state '%' in region '%'.", active_state->get_name(),
				region->get_name() );
			auto l_found = search_for_transition( *active_state, _enabled_compound_transitions, _event, _event_is_deferred );
			if( l_found )
			{					
				Y_LOG( log_level::LL_SPAM, "Transition found in active state '%'.", active_state->get_name() );
				found = l_found;
			}
			else
			{
				Y_LOG( log_level::LL_SPAM, "No transition found in active state '%'.", active_state->get_name() );
			}
		}
		else
		{
			Y_LOG( log_level::LL_SPAM, "No active state found in region '%'.", region->get_name() );
		}
	}

	if( !found )
	{
		transition* transition = nullptr;
		if( COMPLETION_EVENT == _event.get_id() )
		{
			Y_LOG( log_level::LL_TRACE, "Search completion transition in state '%'.", _current_state.get_name() );
			transition = search_completion_transition( _current_state );
		}
		else
		{
			Y_LOG( log_level::LL_TRACE, "Search transition with event id % in state '%'.",
				_event.get_id(), _current_state.get_name() );
			transition = _current_state.search_transition( _event );
		}

		if( transition )
		{
			Y_LOG( log_level::LL_TRACE, "Transition '%' found in the current state '%'.",
				transition->get_name(), _current_state.get_name() );
			found = try_to_build_compound_transition( *transition, _enabled_compound_transitions, _event );
			if( found )
			{
				Y_LOG( log_level::LL_SPAM, "Compound transition was built for transition '%'.", transition->get_name() );
			}
			else
			{
				Y_LOG( log_level::LL_SPAM, "Compound transition was not built for transition '%'.", transition->get_name() );
			}
		}
		else
		{
			Y_LOG( log_level::LL_TRACE, "No transition found in current state '%'.", _current_state.get_name() );
			if( _current_state.is_event_deferred( _event.get_id() ) )
			{
				_event_is_deferred = true;
				found = true;
			}
		}
	}

	return( found );
}


}
