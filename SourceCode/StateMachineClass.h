#pragma once

#include <stack>
#include <memory>

//state class that deals with a single state
class State{
    public:
        //pure virtual initializition function that initializes a state
        virtual void Init() = 0;
        //pure virtual function that handles any input for given state
        virtual void InputHandler() = 0;
        //an update method
        virtual void StateUpdate(float& deltaTime) = 0;
        //draw method, takes a frame difference to keep consistent over different fps
        virtual void StateDraw(float& deltaTime) = 0;
        //pause method, to keep state in a current configuration
        virtual void StatePause(){}
        //resume game state
        virtual void StateResume(){}
};

//typedefine the unique pointer to the state class
typedef std::unique_ptr<State> StateUnqPtr;

//a state machine class that handles all the states
class StateMachine{
    public:
        //constructor and destructor
        StateMachine(){}
        ~StateMachine(){}
        //functon to add the state on the stack, takes a new state and also 
        //has a bool that checks if you are replacing the existing state, 
        //ie. dont keep in memory main menu after starting game
        void AddStateOnTheStack(StateUnqPtr NewState, bool IsReplacingExistingState = true);
        //remove from top of the stack
        void RemoveStateFromTheStack();
        //function to deal with any state changes in the main while loop of game
        void ProcessState();
        //status getter
        //as smart pointers support move semantics, to avoid giving undesired ownership to a smart 
        //pointer the following function returns a refrence to a smart pointer
        //get the topmost stack state that we use for game logic, drawing etc.
        StateUnqPtr& GetCurrentState();

    private:
        //we create a stack of unique pointers to the states
        std::stack<StateUnqPtr> mStates;
        //new state to add
        StateUnqPtr mNewState;
        //bool checks
        bool mIsToAdd = false;
        bool mIsToRemove = false;
        bool mIsToReplaceExisting = false;
};
