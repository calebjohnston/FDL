/**
 * @file importer.h
 * @version 0.1
 *
 * @section LICENSE
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __FDL_IMPORTER_BASE_H
#define __FDL_IMPORTER_BASE_H

#include <string>
#include <set>
#include <exception>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <core/common.h>

namespace fdl {

class ImporterBase {
public:
    virtual bool load(const std::string &filename) = 0;
    virtual bool save(const std::string &filename) = 0;

protected:
	boost::property_tree::ptree pt;
};

}	// namespace fdl

#endif	// __FDL_IMPORTER_BASE_H