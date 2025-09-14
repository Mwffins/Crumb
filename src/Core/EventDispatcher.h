#pragma once
#include "Event.h"
#include <functional>
#include <vector>
#include <unordered_map>
#include <typeindex>

namespace Crumb
{
    template <typename T>
    using EventHandler = std::function<bool(const T &)>;

    class EventDispatcher
    {
    private:
        std::unordered_map<std::type_index, std::vector<std::function<bool(const Event &)>>> m_handlers;

    public:
        template <typename T>
        void subscribe(EventHandler<T> handler)
        {
            auto wrapper = [handler](const Event &e) -> bool
            {
                return handler(static_cast<const T &>(e));
            };
            m_handlers[std::type_index(typeid(T))].push_back(wrapper);
        }

        template <typename T>
        bool dispatch(const T &event)
        {
            auto it = m_handlers.find(std::type_index(typeid(T)));
            if (it != m_handlers.end())
            {
                for (auto &handler : it->second)
                {
                    if (handler(event))
                    {
                        return true;
                    }
                }
            }
            return false;
        }

        void clear()
        {
            m_handlers.clear();
        }
    };
}