/**
 * @file sceneimporter.h
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

#ifndef __FDL_SCENE_IMPORTER_H
#define __FDL_SCENE_IMPORTER_H

#include <string>
#include <set>
#include <exception>
#include <iostream>
#include <string>

#include <core/common.h>
#include <io/importerbase.h>

namespace fdl {

class SceneImporter : public ImporterBase {
public:
	SceneImporter();
	~SceneImporter();
    virtual bool load(const std::string &filename);
    virtual bool save(const std::string &filename);

protected:
	std::string m_file;
	int m_level;
};

}	// namespace fdl

#endif	// __FDL_SCENE_IMPORTER_H