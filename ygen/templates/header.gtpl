//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
// This file was generated by yasmine's ygen @ $var(datetime).                                 //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef $var(state_machine_name_caps)_HPP_
#define $var(state_machine_name_caps)_HPP_

#include "yasmine.hpp"
$loop(behavior_classes)#include "$var(behavior_class_name).hpp"
$pool$@
$loop(namespace_open)namespace $var(namespace_name) 
{$@$@$pool
$loop(events)$@Y_EVENT_CREATE($var(event_name), $var(event_id))$pool
$@
using state_machine_uptr = std::unique_ptr<$var(state_machine_type)>;

state_machine_uptr create_state_machine(const std::string& _name$loop(behavior_classes), $loop(namespace_open)$var(namespace_name)::$pool$var(behavior_class_name)& _$var(behavior_class_name) $pool);

$loop(namespace_close)}$@$@$pool

#endif
