/**
 * This is the p2p messaging component of the Seeks project,
 * a collaborative websearch overlay network.
 *
 * Copyright (C) 2006, 2010  Emmanuel Benazera, juban@free.fr
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */ 

#ifndef LOCATIONTABLE_H
#define LOCATIONTABLE_H

#include "stl_hash.h"
#include "Location.h"
#include "seeks_proxy.h" // for mutexes...

using sp::seeks_proxy;

namespace dht
{
   class LocationTable
     {
      private:
	/**
	 * \brief copy-constructor is not implemented.
	 */
	LocationTable(const LocationTable& lt);
	
      public:
	LocationTable();

	~LocationTable();
	
	bool is_empty() const;
	
	size_t size() const { return _hlt.size(); };
	
      private:
	/**
	 * \brief add new location to table.
	 * @param loc location to be added.
	 */
	void addToLocationTable(Location *&loc);
	
      public:
	/**
	 * \brief create and add location to table.
	 * @param key identification key to be added,
	 * @param na net address of the location to be added,
	 * @param loc location pointer to be filled with the new location info.
	 */
	void addToLocationTable(const DHTKey& key, const NetAddress& na, Location *&loc);
	
	/**
	 * \brief - lookup for the key in the hashtable. Replace based on the existing location
	 *          (use up_time in case of a key conflict ?).
	 *        - if nothing is found, create a location object and add it to the table.
	 */
	Location* addOrFindToLocationTable(const DHTKey& key, const NetAddress& na);
	
	/**
	 * \brief remove location from table.
	 */
	void removeLocation(Location *loc);
	
	/**
	 * \brief find location. 
	 */
	Location* findLocation(const DHTKey& dk);
	
	/**
	 * \brief find closest successor.
	 * XXX: could be faster with an ordered structure.
	 * For now, only used for estimating the number of nodes on the circle.
	 */
	void findClosestSuccessor(const DHTKey &dk,
				  DHTKey &dkres);
	
	/**
	 * \brief prints the location table.
	 */
	void print(std::ostream &out) const;
	
      public:
	/**
	 * TODO: hashtable of known peers on this system.
	 * TODO: should we add the local virtual nodes to it ? (why not?).
	 */
	hash_map<const DHTKey*, Location*, hash<const DHTKey*>, eqdhtkey> _hlt;
	
	/**
	 * (TODO: table of ranked known peers on this system ?) PatTree ?.
	 */
	
	
	/**
	 * TODO: set of cached peers (locations) ?.
	 */
	
	/**
	 * mutex for table.
	 */
	sp_mutex_t _lt_mutex;
     };
     
} /* end of namespace. */

#endif
