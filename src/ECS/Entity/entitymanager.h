#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "entityfactory.h"
#include <map>
#include <singleton.h>

namespace ECS {
class EntityManager : public ECS::Singleton{

        std::map<unsigned int, Entity>entityMap;


    public:
        static EntityManager& GetInstance();
        unsigned int CreateEntity();
		bool AddComponent(unsigned int entity, unsigned int componentId);

        const std::vector<unsigned int>& GetComponentsIds(unsigned int entity);
        Entity GetEntity(unsigned int entity);

    };

}

#endif /* __ENTITYMANAGER_H__ */

