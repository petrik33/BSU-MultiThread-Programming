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
    State(Actor* actor);
    virtual ~State();
    State* Update(char input);

   protected:
    Actor* actor_;
    virtual void Render() = 0;
    virtual void Move() = 0;
    virtual State* HandleInput(char input);
};

class StateHappy : public State {
   public:
    StateHappy(Actor* actor);

   protected:
    void Render() override;
    void Move() override;
};

class StateIdle : public State {
   public:
    StateIdle(Actor* actor);

   private:
    void Render() override;
    void Move() override;
};

class StateSad : public State {
   public:
    StateSad(Actor* actor);

   private:
    void Render() override;
    void Move() override;
};

}  // namespace colloq

#endif /* INCLUDES_STATE_H_ */
