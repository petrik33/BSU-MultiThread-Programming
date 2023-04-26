#ifndef INCLUDES_STATE_H_
#define INCLUDES_STATE_H_

#include "actor.h"
#include "types.h"

namespace colloq {

class StateHappy;
class StateIdle;
class StateSad;
class Actor;

class State {
   public:
    State();
    virtual ~State();
    State* Update();

   protected:
    shared_ptr<Actor> actor;
    virtual void Render() = 0;
    virtual void Move() = 0;
    virtual State* HandleInput();
};

class StateHappy : public State {
   public:
    StateHappy();

   protected:
    void Render() override;
    void Move() override;
};

class StateIdle : public State {
   public:
    StateIdle();

   private:
    void Render() override;
    void Move() override;
};

class StateSad : public State {
   public:
    StateSad();

   private:
    void Render() override;
    void Move() override;
};

}  // namespace colloq

#endif /* INCLUDES_STATE_H_ */
