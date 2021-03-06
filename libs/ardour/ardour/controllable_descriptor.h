/*
    Copyright (C) 2009 Paul Davis

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef __libardour_controllable_descriptor_h__
#define __libardour_controllable_descriptor_h__

#include <vector>
#include <string>
#include <stdint.h>

#include "ardour/libardour_visibility.h"

namespace ARDOUR {

class LIBARDOUR_API ControllableDescriptor {
public:
    enum TopLevelType {
	    PresentationOrderRoute,
	    PresentationOrderTrack,
	    PresentationOrderBus,
	    PresentationOrderVCA,
	    NamedRoute,
	    SelectionCount,
    };

    enum SubType {
	    Gain,
	    Trim,
	    Solo,
	    Mute,
	    Recenable,
	    PanDirection,
	    PanWidth,
	    PanElevation,
	    Balance,
	    SendGain,
	    PluginParameter
    };

    ControllableDescriptor ()
	    : _top_level_type (PresentationOrderRoute)
	    , _subtype (Gain)
	    , _banked (false)
	    , _bank_offset (0)
    {}

    int set (const std::string&);

    /* it is only valid to call top_level_name() if top_level_type() returns
       NamedRoute
    */

    TopLevelType top_level_type() const { return _top_level_type; }
    const std::string& top_level_name() const { return _top_level_name; }

    SubType subtype() const { return _subtype; }

    uint32_t presentation_order() const;
    uint32_t selection_id() const;
    uint32_t target (uint32_t n) const;
    bool banked() const { return _banked; }

    void set_bank_offset (uint32_t o) { _bank_offset = o; }

private:
    TopLevelType          _top_level_type;
    SubType               _subtype;
    std::string           _top_level_name;
    union {
	    uint32_t  _presentation_order;
	    uint32_t  _selection_id;
    };
    std::vector<uint32_t> _target;
    uint32_t              _banked;
    uint32_t              _bank_offset;
};

}

#endif /* __libardour_controllable_descriptor_h__ */
