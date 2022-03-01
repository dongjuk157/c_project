#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "label.h"
#include "utils.h"

Label* createLabel(){
    Label* label = (Label*)malloc(sizeof(Label));
    label->posx = 0;
    label->posy = 0;
    label->text = NULL;
    return label;
}

bool setLabelPos(Label *label, int posy, int posx){
    if(posx < 0 || posy < 0) return False;

    label->posx = posx;
    label->posy = posy;
    label->text = NULL;

    return True;
}

bool setLabelText(Label *label, const char *text){
    if(text == NULL) return False;

    if(label->text != NULL){
        free(label->text);
    }
    label->text = (char *)malloc(sizeof(char) * strlen(text) + 1);
    strcpy(label->text, text);
    
    return True;
}

