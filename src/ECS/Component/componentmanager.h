#ifndef __COMPONENT_MANAGER_H__
#define __COMPONENT_MANAGER_H__
#include <map>
#include <memory>
#include <iostream>
#include "component.h"
#include "ECS/Entity/entitymanager.h"
#include "componentfactory.h"

namespace ECS{

    class ComponentManager_ {

        using ComponentManager = std::shared_ptr<ComponentManager_>;
        std::map<unsigned int, Component>componentMap;

    public:
        static ComponentManager componentManager;
        static ComponentManager GetManager();
        
        template <typename T>
        unsigned int CreateComponent(){

            Component component = ECS::ComponentFactory::CreateComponent<T>();
            componentMap[component->m_id] = component;
            return component->m_id;

        }
        Component GetComponent(unsigned int componentId);
		
    };
    



}


#endif /* __COMPONENT_MANAGER_H__ */