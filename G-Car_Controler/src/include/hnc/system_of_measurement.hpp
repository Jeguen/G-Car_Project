// Copyright © 2013, 2014 Inria, Written by Lénaïc Bagnères, lenaic.bagneres@inria.fr

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#ifndef HNC_SYSTEM_OF_MEASUREMENT_HPP
#define HNC_SYSTEM_OF_MEASUREMENT_HPP

#include "system_of_measurement/degree.hpp"
#include "system_of_measurement/radian.hpp"


namespace hnc
{
	/**
	 * @brief Provides some system of measurement
	 *
	 * @code
	   #include <hnc/system_of_measurement.hpp>
	   @endcode
	 *
	 * @b From http://en.wikipedia.org/wiki/System_of_measurement @n
	 * A system of measurement is a set of units which can be used to specify anything which can be measured and were historically important, regulated and defined because of trade and internal commerce. Scientifically, when later analyzed, some quantities are designated as fundamental units meaning all other needed units can be derived from them, whereas in the early and most historic eras, the units were given by fiat (see statutory law) by the ruling entities and were not necessarily well inter-related or self-consistent.
	 *
	 * Angle:
	 * - degree (hnc::degree)
	 * - radian (hnc::radian)
	 */
	namespace system_of_measurement
	{
		// For Doxygen only
	}
}

#endif
