/* Event system.
 * Two structures are implemented:
 *   Dispatcher<T>
 *   Subscriber<T>
 * Subscribers can then be subscribed to dispatchers,
 * in which case a configurable callback function
 * T -> void will be called whenever an "event" is
 * dispatched.
 * */

#pragma once
#include "common.h"

#include <vector>
#include <functional>

namespace Gulag {

    template<class T>
    using EventCallback =  std::function<void(const T&)>;

    /* forward declare because of mutual recursion */
    template<class T> class Subscriber;
    template<class T> class Dispatcher;

    template<class T>
    class Dispatcher {
        public:
            void add_subscriber(Subscriber<T>* sub);
            void dispatch(const T& event);
        private:
            std::vector<Subscriber<T>*> subs;
    };


    template<class T>
    class Subscriber {
        public:
            Subscriber(EventCallback<T> callback);
            void subscribe_to(Dispatcher<T> &d);
            void notify(const T& e);
        private:
            EventCallback<T> handle_event;
    };

    template<class T>
    void Dispatcher<T>::add_subscriber(Subscriber<T>* sub) {
        subs.push_back(sub);
    }

    template<class T>
    void Dispatcher<T>::dispatch(const T& e) {
        for (auto s: subs) {
            s->notify(e);
        }
    }

    template<class T>
    Subscriber<T>::Subscriber(EventCallback<T> fn) {
        handle_event = fn;
    }

    template<class T>
    void Subscriber<T>::subscribe_to(Dispatcher<T> &d) {
        d.add_subscriber(this);
    }

    template<class T>
    void Subscriber<T>::notify(const T& e) {
        handle_event(e);
    }
}
