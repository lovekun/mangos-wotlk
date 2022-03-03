/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "Vmap/GameObjectModelVmaps.h"

ModelList LoadGameObjectModelList(std::string fileName)
{
    ModelList model_list;
    FILE* model_list_file = fopen(fileName.c_str(), "rb");
    if (!model_list_file)
        return model_list;

    uint32 name_length, displayId;
    char buff[500];
    while (!feof(model_list_file))
    {
        fread(&displayId, sizeof(uint32), 1, model_list_file);
        fread(&name_length, sizeof(uint32), 1, model_list_file);

        if (name_length >= sizeof(buff))
        {
            // sLog.outDebug("File %s seems to be corrupted", VMAP::GAMEOBJECT_MODELS);
            break;
        }

        fread(&buff, sizeof(char), name_length, model_list_file);
        G3D::Vector3 v1, v2;
        fread(&v1, sizeof(G3D::Vector3), 1, model_list_file);
        fread(&v2, sizeof(G3D::Vector3), 1, model_list_file);

        model_list.emplace(displayId, GameobjectModelData(std::string(buff, name_length), G3D::AABox(v1, v2)));
    }
    fclose(model_list_file);
    return model_list;
}