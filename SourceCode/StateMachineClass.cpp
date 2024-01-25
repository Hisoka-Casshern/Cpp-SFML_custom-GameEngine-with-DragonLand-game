#include "StateMachineClass.h"

//implementation of functions
void StateMachine::AddStateOnTheStack(StateUnqPtr NewState, bool IsReplacingExistingState){
    //set the bool checkers
    this->mIsToAdd = true;
    this->mIsToReplaceExisting = IsReplacingExistingState;
    //move the state object into member variable of state machine
    this->mNewState = std::move(NewState);
}

void StateMachine::RemoveStateFromTheStack(){
    //just set the state to be removed as true as any change will be dealt with 
    //in ProccessState function
    this -> mIsToRemove = true;
}

void StateMachine::ProcessState(){
    //
    //first check if we want to remove the topmost state,
    //we need to have aleready some state on the stack
    if(this->mStates.empty()==false && this->mIsToRemove == true){
        //remove from top of the stack
        this->mStates.pop();
        //resume run of the now currenty topmost state if exists
        if(mStates.empty() == false){
            this->mStates.top()->StateResume(); 
        }
        //reset the check
        this->mIsToRemove = false;
    }
    //
    //now we check if we want to add the state on the stack
    if(this->mIsToAdd == true){
        //first we implement the logic based on if we wnt to replace the state with the topmost
        //state or not, this implies there exists alreadz at least one state on the stack
        if(this->mStates.empty() == false){
            //to replace we just remove the topmost as we will add the state later at the top
            //if we dont want to replace we just pasue the topmost and put the new active above it
            if(this->mIsToReplaceExisting) this->mStates.pop();
            else this->mStates.top();
        }
        //now we add to the stack
        this->mStates.push(std::move(this->mNewState));
        //initilize the state
        this->mStates.top()->Init();
        //finnaly reset the check
        this->mIsToAdd=false;
    }
}

StateUnqPtr& StateMachine::GetCurrentState(){
    //just return the topmost state
    return this->mStates.top();
}

