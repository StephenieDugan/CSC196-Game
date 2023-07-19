#include "Scene.h"

namespace Twili
{
    void Scene::Update(float dt)
    {
      
            //removed destroyed actors
           auto iter = m_actors.begin();

           while (iter != m_actors.end())
           { 
               (*iter)->Update(dt);
               if (iter->get()->m_destroyed)
               {
                   iter = m_actors.erase(iter);
               }
               else {
                   iter++;
               }
              
           }
       
    }

    void Scene::Draw(Renderer& renderer)
    {
        for (auto& actor : m_actors)
        {
            actor->Draw(renderer);
        }
    }

    void Scene::Add(std::unique_ptr<Actor> actor)
    {
        actor->m_scene = this;
        m_actors.push_back(std::move(actor));
    }

    void Scene::Remove(Actor* actor)
    {
        //m_actors.remove(actor);
    }

    void Scene::RemoveAll()
    {
        m_actors.clear();
    }

}