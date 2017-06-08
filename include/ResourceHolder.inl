/***********************************************************************************
 * ResourceHolder.inl
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Implementation file for ResourceHolder class template.
 * Need to be included at the end of ResourceHolder.hpp.
 ************************************************************************************/


template <typename ResourceType, typename IdentifierType>
ResourceHolder<ResourceType, IdentifierType>::ResourceHolder()
    : mResourceMap()
{

}


//Allocate new resource and insert its pointer to map
template <typename ResourceType, typename IdentifierType>
void ResourceHolder<ResourceType, IdentifierType>::load (IdentifierType id, const std::string filename)
{
    //Allocate new resource and assign unique pointer to it
    std::unique_ptr<ResourceType> ptr (new ResourceType());

    //Load resource from file and check
    if (!ptr->loadFromFile(filename))
    {
        throw std::runtime_error("ResourceHolder::load() - Failed to load " + filename);
    }

    //Insert the pointer into mResourceMap and check whether its inserted
    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(ptr)));
    assert(inserted.second && "Could not insert into map (The ID already inserted)");
}

//Return resource for the id
template <typename ResourceType, typename IdentifierType>
ResourceType& ResourceHolder<ResourceType, IdentifierType>::get(IdentifierType id)
{
    auto found = mResourceMap.find(id);

    //Check if resource could be found
    assert (found != mResourceMap.end() && "ResourceHolder::get() - Could not find resource");

    //Return value of the resource to the reference
    //(found is a iterator to a pair in mResourceMap, whose second part is a unique pointer to resource)
    return *(found->second);
}

//Constant version of get() - Implementation is the same
template <typename ResourceType, typename IdentifierType>
const ResourceType& ResourceHolder<ResourceType, IdentifierType>::get(IdentifierType id) const
{

    auto found = mResourceMap.find(id);

    assert (found != mResourceMap.end() && "ResourceHolder::get() - Could not find resource");

    return *(found->second);
}
