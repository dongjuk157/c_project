#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "label.h"
#include "utils.h"

Label* createLabel(){
    Label* label = (Label*)malloc(sizeof(Label));
    label->posx = 0;
    label->posy = 0;
    return label;
}

bool setLabelPos(Label *label, int posy, int posx){
    if(posx < 0 || posy < 0) return False;

    label->posx = posx;
    label->posy = posy;

    return True;
}

bool setLabelText(Label *label, const char *text){
    if(text == NULL) return False;

    strcpy(label->text, text);
    
    return True;
}

