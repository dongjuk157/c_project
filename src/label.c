#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "label.h"
#include "utils.h"

Label* createLabel(){
    Label* label = (Label*)malloc(sizeof(Label));
    label->posx = 0;
    label->posy = 0;
    label->color = 0;
    label->text = NULL;
    return label;
}

int setLabel(Label* label, int posy, int posx, const char* text, int color){
    setLabelPos(label,posy,posx);
    setLabelText(label, text);
    label->color = color;

    return LABEL_EOK;
}

int setLabelPos(Label *label, int posy, int posx){
    if(posx < 0 || posy < 0) return LABEL_NOT_VALID_INPUT;

    label->posx = posx;
    label->posy = posy;
    label->text = NULL;

    return LABEL_EOK;
}

int setLabelText(Label *label, const char *text){
    if(text == NULL) return LABEL_NOT_VALID_INPUT;

    if(label->text != NULL){
        free(label->text);
    }
    label->text = (char *)malloc(sizeof(char) * strlen(text) + 1);
    strcpy(label->text, text);
    
    return LABEL_EOK;
}

int setLabelBackgrounColor(Label *label, int color){
    label->color = color;
    return LABEL_EOK;
}
