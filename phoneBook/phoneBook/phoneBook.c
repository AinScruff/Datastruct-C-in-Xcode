//
//  main.c
//  phoneBook
//
//  Created by Dominique Michael Abejar on 21/08/2019.
//  Copyright © 2019 BSIT. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct number{
    char number[14];
}NumType;

typedef struct contact{
    char name[64];
    NumType* number;
    char email[255];
    char org[24];
}Contact;

typedef struct phoneBook{
    Contact cn;
    struct phoneBook *link;
}*PhoneBook;

bool populateCN(Contact *cn);
void populateUpdateCN(Contact *cn);
bool initPhoneBook(PhoneBook *pb);
bool insert(PhoneBook *pb, Contact cn, int pos);
bool append(PhoneBook *pb, Contact cn);
Contact retrieveContact(PhoneBook *pb, int pos);
Contact update(PhoneBook *pb, Contact newCn, int pos);
Contact delete(PhoneBook *pb, int pos);
void displayAll(PhoneBook pb);
int main(){
    PhoneBook pb;
    bool catch;
    Contact cn, updateCN;
    
    catch = initPhoneBook(&pb);
    printf("Init Status: %d\n", catch);
    
    catch = populateCN(&cn);
    printf("Populate Status: %d\n\n", catch);
    
    catch = append(&pb, cn);
    catch = append(&pb, cn);
    catch = append(&pb, cn);
    
    cn = retrieveContact(&pb, 1);
    printf("Retrieved Contact: %s\n\n", cn.name);
    
    displayAll(pb);
    
    cn = delete(&pb, 0);
    
    populateUpdateCN(&updateCN);
    cn = update(&pb, updateCN, 1);
    if(strcmp(cn.name, "XXXXX") == 0){
        printf("---Failed To Update! Position out of Range---\n\n");
    }else{
        printf("---Updated Successfully!---\n\n");
    }
    displayAll(pb);
    return 0;
}

bool populateCN(Contact *cn){
    
    strcpy(cn->name, "Dominique Michael Abejar");
    
    cn->number = (NumType *)malloc(sizeof(NumType) * 2);
    
    strcpy(cn->number[0].number, "09994523934");
    strcpy(cn->number[1].number, "09424570852");
    strcpy(cn->email, "asadasd@gmail.com");
    strcpy(cn->org, "DKO");
    
    return (cn)? true : false;
}

void populateUpdateCN(Contact *cn){
    strcpy(cn->name, "UPDATED");
    cn->number = (NumType*)malloc(sizeof(NumType));
    
    strcpy(cn->number[0].number, "0999999343");
    strcpy(cn->email, "UPDATED@yahoo.com");
    strcpy(cn->org, "ORGUpdate");
}

bool initPhoneBook(PhoneBook * pb){
    
    pb = NULL;
    
    return (pb == NULL)? true : false;
}

bool insert(PhoneBook *pb, Contact cn, int pos){
    PhoneBook temp, *trav;
    int ctr = 0;
    bool retval = false;
    
    for(trav = pb; trav != NULL && ctr != pos; trav = &(*trav)->link, ctr++){} //Loop to the last element or to position
    

    temp = (PhoneBook)malloc(sizeof(struct phoneBook));
        
    if(temp != NULL){ //Insert
        temp->cn = cn;
        temp->link = *trav;
        *trav = temp;
        retval = true;
    }
    
    return retval;
}

bool append(PhoneBook *pb, Contact cn){
    PhoneBook temp, *trav;
    bool retval = false;
    
    temp = (PhoneBook)malloc(sizeof(struct phoneBook));
    
    if(temp != NULL){
        for(trav = pb; *trav != NULL; trav = &(*trav)->link){} //Loop to the last element
        
        temp->cn = cn; //Insert
        temp->link = *trav;
        *trav = temp;
        retval = true;
    }
    
    return retval;
}

Contact retrieveContact(PhoneBook *pb, int pos){
    Contact retval;
    PhoneBook *trav;
    int ctr = 0;
    
    
    for(trav = pb; *trav != NULL && ctr != pos; trav = &(*trav)->link, ctr++){//Loop to the last element or to position
    }
    
    
    if(*trav != NULL){
        retval = (*trav)->cn;
    }else{
        strcpy(retval.name, "NO RECORD: XXXXX");
    }
    
    
    return retval;
}

Contact update(PhoneBook *pb, Contact newCn, int pos){
    Contact retval;
    PhoneBook *trav;
    int ctr = 0;
    
    for(trav = pb; *trav != NULL && ctr != pos; trav = &(*trav)->link, ctr++){} //Loop to the last element or to position
    
    if(*trav != NULL){
        (*trav)->cn = newCn;
        retval = (*trav)->cn;
    }else{
        strcpy(retval.name, "XXXXX");
    }
    
    return retval;
}

Contact delete(PhoneBook *pb, int pos){
    Contact retval;
    PhoneBook temp, *trav;
    int ctr = 0;
    
    for(trav = pb; *trav != NULL && ctr != pos; trav = &(*trav)->link, ctr++){} //Loop to the last element or to position
    
    if(ctr == pos){
        temp = (*trav);
        (*trav) = temp->link;
        retval = temp->cn;
        free(temp);
    }else{
        strcpy(retval.name, "XXXXX");
    }
    
    return retval;
}

void displayAll(PhoneBook pb){
    PhoneBook trav;
    int i = 0;
    
    for(trav = pb; trav != NULL; trav = trav->link){
        printf("Name: %s\n", trav->cn.name);
        for(i = 0; i < ((sizeof(*trav->cn.number)/sizeof(NumType)) + 1); i++){ //Guba ang formula
            printf("Contact: %s\n", trav->cn.number[i].number);
        }
        printf("Email: %s\n", trav->cn.email);
        printf("Organization: %s\n\n", trav->cn.org);
    }
    
}
