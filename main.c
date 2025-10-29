#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef struct nodo {
    struct nodo *parent, *left, *right;
    int32_t* available_cars;
    int32_t num_cars;
    int32_t numero;
} node_t;

typedef node_t *node;



int32_t getCar(node n);

node treeMinimum(struct nodo *n);

node treeSuccessor(node checkpoint) {
    if(checkpoint->right != NULL)
        return treeMinimum(checkpoint->right);
    node p = checkpoint->parent;
    while(p != NULL && checkpoint == p->right){
        checkpoint = p;
        p = p->parent;
    }
    return p;
}

node treeFind(node root, int32_t distanza){
    node x = root;
    while(x){
        if(distanza < x->numero){
            x=x->left;
        } else if(distanza > x->numero){
            x=x->right;
        } else{
            return x;
        }
    }
    return NULL;
}

int32_t* andata(node root, int32_t partenza, int32_t arrivo, int32_t *size){
    int32_t *result;
    node head, tail, tmp, checkpoint;
    head = treeFind(root, partenza);
    tail = treeFind(root, arrivo);
    result = (int32_t*)malloc(1*sizeof(int32_t));
    result[0] = tail->numero;
    (*size)=1;
    checkpoint = tail;
    int32_t i=0, j=0;
    while(i==j){
        tmp = head;
        while(tmp->numero < checkpoint->numero){
            if(tmp == NULL) {
                free(result);
                return NULL;
            }
            if(tmp->num_cars>0 && checkpoint->numero <= (tmp->numero + getCar(tmp))) {
                int32_t* bb = (int32_t*)realloc(result, ((*size)+1)*sizeof(int32_t));
                result = bb;
                if(!result) {
                    return NULL;
                }
                result[*size] = tmp->numero;
                (*size)++;
                checkpoint = tmp;
                j++;
                if(tmp == head){
                    return result;
                }
                break;
            }
            tmp = treeSuccessor(tmp);
        }
        i++;
    }
    free(result);
    return NULL;
}

int32_t getCar(node n) {
    int32_t max = n->available_cars[0];
    for(int32_t i=1; i<n->num_cars; i++){
        if(n->available_cars[i] > max){
            max = n->available_cars[i];
        }
    }
    return max;
}

node previous(node node) {

    if(node->left != NULL) {
        node = node->left;
        while(node->right != NULL) {
            node = node->right;
        }
        return node;
    } else if(node->parent != NULL) {

        if(node->parent->right == node) {
            return node->parent;
        }

        if(node->parent->left == node) {

            while(node->parent->right != node) {

                if(node->parent->parent == NULL) {
                    return NULL;
                }
                node = node->parent;
            }
            return node->parent;

        }
    }

    return NULL;
}

node closestHigher(node root, int target) {
    node closestBiggerNode = NULL;
    int32_t minDifference = 999999999;

    while (root != NULL) {
        int32_t difference = root->numero - target;

        if (difference > 0 && difference < minDifference) {
            minDifference = difference;
            closestBiggerNode = root;
        }

        if (difference < 0) {
            root = root->right;
        }else if(difference == 0){
            return root;
        }else {
            root = root->left;
        }
    }

    return closestBiggerNode;
}

node massimoNodo(node a, node b){
    if(a->numero > b->numero)
        return a;
    return b;
}

int32_t* ritorno(node root, int32_t partenza, int32_t arrivo, int32_t *size){
    node step=NULL, tmp=NULL, obiettivo=NULL, explorer=NULL, next=NULL, oldobiettivo=NULL;
    //node min;
    node head = treeFind(root, partenza);
    node tail = treeFind(root, arrivo);
    int32_t * result = NULL, far_stazione;
    int32_t minReach, r;
    (*size)=1;
    result = (int32_t*)malloc(sizeof(int32_t));
    result[0] = head->numero;
    step = head;
    tmp = head;
    oldobiettivo = NULL;
    while(tmp && tmp->numero >= tail->numero){
        far_stazione = step->numero - getCar(step);
        obiettivo = closestHigher(root, far_stazione);

        if(obiettivo->numero <= arrivo){
            return result;
        }

        minReach = far_stazione;
        tmp = step;
        while(tmp && tmp->numero >= obiettivo->numero ){
            r = tmp->numero - getCar(tmp);
            if(r < minReach){
                minReach = r;
                //min = tmp;
            }
            tmp = previous(tmp);
        }
        next = closestHigher(root, minReach);
        explorer = obiettivo;
        next = massimoNodo(next, tail);

        while(explorer->numero - getCar(explorer) > next->numero){
            explorer = treeSuccessor(explorer);
        }

       

        if(oldobiettivo) {
            tmp = oldobiettivo;
            while (tmp && tmp != step) { if(explorer->numero >= step->numero){
            free(result);
            return NULL;
        }

        int32_t *bb = (int32_t*)realloc(result, ((*size)+1)*sizeof(int32_t));
        result = bb;
        (*size)++;

        result[(*size) -1] = explorer->numero;
                if (tmp->numero - getCar(tmp) <= explorer->numero) {
                    result[(*size) - 2] = tmp->numero;
                    break;
                }
                tmp = treeSuccessor(tmp);
            }
        }
        oldobiettivo = obiettivo;

        step = explorer;

    }
    free(result);
    return NULL;
}
void destroyStazione(node stazione){
    free(stazione->available_cars);
    free(stazione);
}

node treeInsert(node root, node stazione){
    stazione->left = stazione->right = stazione->parent = NULL;
    node y = NULL;
    node x = root;
    while (x) {
        y = x;
        if (stazione->numero < x->numero) {
            x = x->left;
        } else if(stazione->numero > x->numero){
            x = x->right;
        } else{
            destroyStazione(stazione);
            printf("non aggiunta\n");
            return root;
        }
    }
    stazione->parent = y;
    if (y == NULL) root = stazione;
    else if (stazione->numero < y->numero)  y->left = stazione;
    else    y->right = stazione;
    stazione->left = NULL;
    stazione->right = NULL;
    printf("aggiunta\n");
    return root;
}

node aggiungi_stazione(node root){
    int32_t distanza, num_auto;
    int32_t *cars = NULL;
    node stazione = NULL;
    if(scanf("%d %d ", &distanza, &num_auto)){}

    cars=(int32_t*)malloc(num_auto*sizeof(int32_t));
    for(int32_t i=0; i<num_auto; i++){
        if(scanf("%d ", &cars[i])){}
    }

    stazione=(node)malloc(sizeof(*stazione));
    stazione->numero=distanza;
    stazione->available_cars=cars;
    stazione->num_cars=num_auto;

    root = treeInsert(root, stazione);

    return root;
}
void aggiungi_auto(node root){
    int32_t distanza, autonomia;
    node x = root;
    if(scanf("%d %d ", &distanza, &autonomia)){}
    while(x){
        if(distanza < x->numero){
            x=x->left;
        } else if(distanza > x->numero){
            x=x->right;
        } else{
            int32_t* tmp = (int*)realloc(x->available_cars, (x->num_cars+1)*sizeof(int));
            x->available_cars = tmp;
            x->available_cars[x->num_cars] = autonomia;
            x->num_cars++;
            printf("aggiunta\n");
            return;
        }
    }
    printf("non aggiunta\n");
}
void rottama_auto(node root){
    int32_t distanza, autonomia;
    node x = root;
    if(scanf("%d %d ", &distanza, &autonomia)){}
    while(x){
        if(distanza < x->numero){
            x=x->left;
        } else if(distanza > x->numero){
            x=x->right;
        } else{
            for(int32_t i=0; i<x->num_cars; i++){
                if(x->available_cars[i] == autonomia){
                    x->available_cars[i] = x->available_cars[x->num_cars-1];
                    int32_t* tmp = (int32_t*)realloc(x->available_cars, (x->num_cars-1)*sizeof(int32_t));
                    x->available_cars = tmp;
                    x->num_cars--;
                    printf("rottamata\n");
                    return;
                }
            }
            printf("non rottamata\n");
            return;
        }
    }
    printf("non rottamata\n");
}

node treeMinimum(node n) {
    while(n->left != NULL){
        n = n->left;
    }
    return n;
}

node transplant(node root, node u, node v){
    if(u->parent == NULL){
        root = v;
    } else if (u == u->parent->left){
        u->parent->left = v;
    } else{
        u->parent->right = v;
    }
    if(v != NULL){
        v->parent = u->parent;
    }
    return root;
}

node treeDelete(node root, node z){
    node y = NULL;
    if(z->left == NULL){
        root = transplant(root, z, z->right);
    } else if(z->right == NULL){
        root = transplant(root, z, z->left);
    } else{
        y=treeMinimum(z->right);
        if(y->parent != z){
            root = transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        root = transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    destroyStazione(z);
    return root;
}

node demolisci_stazione(node root){
    int32_t distanza_stazione;
    node current = NULL;

    if(scanf("%d ", &distanza_stazione)){}
    current = treeFind(root, distanza_stazione);
    if(current == NULL){
        printf("non demolita\n");
    } else {
        root = treeDelete(root, current);
        printf("demolita\n");
    }
    return root;
}


bool existsInTree(node root, int32_t distanza){
    node x = root;
    while(x){
        if(distanza < x->numero){
            x=x->left;
        } else if(distanza > x->numero){
            x=x->right;
        } else{
            return true;
        }
    }
    return false;
}
void pianifica_persorso(node root){
    int32_t partenza, arrivo, *result=NULL, size;
    size = 0;
    if(scanf("%d %d ", &partenza, &arrivo)){}
    if(partenza == arrivo){
        if(existsInTree(root, partenza)) {
            printf("%d\n", partenza);
            return;
        }
    }
    else if(partenza < arrivo){

        result = andata(root, partenza, arrivo, &size);
        if(result == NULL){
            printf("nessun percorso\n");
        } else{
            for(int32_t i=size-1; i>=1; i--){
                printf("%d ", result[i]);
            }
            printf("%d\n", result[0]);
            free(result);
        }


    } else{

        result = ritorno(root, partenza, arrivo, &size);
        if(result == NULL){
            printf("nessun percorso\n");
        } else{
            for(int i=0; i<size; i++){
                printf("%d ", result[i]);
            }
            printf("%d\n", arrivo);
            free(result);
        }

    }
}


void treeDestroy(node root){
    if(root==NULL)
        return;
    treeDestroy(root->left);
    treeDestroy(root->right);
    destroyStazione(root);
}

int32_t main(){
    char *buffer = NULL;
    node root=NULL;
    buffer=(char *)malloc(20);
    while(scanf("%s ", buffer)!=EOF){
        if(buffer[0]=='a'){
            if(buffer[9]=='s'){
                root = aggiungi_stazione(root);
            } else{
                aggiungi_auto(root);
            }
        } else if(buffer[0]=='r'){
            rottama_auto(root);
        } else if(buffer[0]=='d') {
            root = demolisci_stazione(root);
        } else{
            pianifica_persorso(root);
        }
    }
    free(buffer);
    treeDestroy(root);
    return 0;
}
