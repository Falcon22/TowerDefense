#ifndef TOWERDEFENSE_RESOURCESHOLDER_H
#define TOWERDEFENSE_RESOURCESHOLDER_H

#include <string>
#include <memory>
#include <map>

template<typename Resource, typename Identifier>
class ResourceHolder {
public:
    void load(Identifier id, const std::string& fileName);

    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;

private:
    void insert(Identifier id, std::unique_ptr<Resource> resource);

    std::map<Identifier, std::unique_ptr<Resource>> resourceMap;
};

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &fileName) {
    std::unique_ptr<Resource> resource(new Resource());

    if(!resource->loadFromFile(fileName)) {
        throw std::runtime_error("ResourceHolder::load failed to load" + fileName);
    }
    insert(id, std::move(resource));
}

template<typename Resource, typename Identifier>
Resource &ResourceHolder<Resource, Identifier>::get(Identifier id) {
    return *resourceMap.find(id)->second;
}

template<typename Resource, typename Identifier>
const Resource &ResourceHolder<Resource, Identifier>::get(Identifier id) const {
    return *resourceMap.find(id)->second;
}

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insert(Identifier id, std::unique_ptr<Resource> resource) {
    resourceMap.insert(std::make_pair(id, std::move(resource)));
}

#endif //TOWERDEFENSE_RESOURCESHOLDER_H