/***********************************************************************************
 * ResourceHolder.hpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Class template used for holding the game's resources: Texture, Font and Sound.
 * (for Music, we need to write a new class - MusicPlayer.hpp -
 *  since music must be streamed continuously from file while being played)
 ************************************************************************************
 * NOTE:
 * Since this is a class template, the implementation of the class must be in the
 * same header file as the class definition. However, we still want to separate
 * the interface and the definition. Therefore, we need to include the implementation
 * file (ResourceHolder.inl) at the end of this file.
 ************************************************************************************/

#ifndef RESOURCEHOLDER_HPP_INCLUDED
#define RESOURCEHOLDER_HPP_INCLUDED
#include <string>
#include <map>
#include <cassert>
#include <memory>
#include <stdexcept>

template <typename ResourceType, typename IdentifierType>
class ResourceHolder
{ //Hold map of resources with their id
public:
                            ResourceHolder();
    void                    load(IdentifierType id, const std::string filename); //Allocate new resource and
                                                                                //insert its pointer to map
    ResourceType&           get(IdentifierType id);         //Return reference to resource
    const ResourceType&     get(IdentifierType id) const;   //Return reference to constant resource

private:
    std::map<IdentifierType, std::unique_ptr<ResourceType>> mResourceMap;
};

#include "include/ResourceHolder.inl"
#endif // RESOURCEHOLDER_HPP_INCLUDED
