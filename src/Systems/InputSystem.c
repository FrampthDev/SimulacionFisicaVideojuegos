#include "Systems.h"

void InputSystem_Update(bool* cursor, bool* can_move){

    //TODO: arreglar este horror
    if (IsKeyPressed(KEY_SPACE)){
        if (cursor){
            *cursor= false;
            *can_move= true;
            DisableCursor();
        }
        else{
            *cursor= true;
            *can_move= false;
            EnableCursor();
        }
    }
}
