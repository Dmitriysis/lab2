#include <stdio.h>

const char *menu[] = {"1. Show", "2. Add", "3. Find", "4. Delete Item", "5. Quit", "6. Save tabble", "7. Show up tree", "8. Show key tree", "9. Show height"};
const int N =9;


typedef struct node
{
    int key;
    char *info;
    struct node*  left;
    struct node*  right;
    int      height;
} node;

node *p, *pf;

void dispose(node* t);
node* find( int e, node *t );
node* find_min( node *t );
node* find_max( node *t );
node* insert( int key, node *t );
node* delete( int key, node *t );
void display_avl(node* t);
int get( node* n );
char *getStr();
int getInt(int *a);
int dialog(const char *menu[], int n);
void SH (node *t);
void PrintTree (node *t);
node* Ndelete( int e, node* t );

int main()
{
    node *t , *p, *f;
    int i, nn; //nn - кол-во узлов.
    int j = 0;
    const int max = 10;

    printf("Lets start!\n");
    st:
    printf("Enter the number of nodes: \n");
    getInt(&nn);
    if (nn <= 0) {
        printf("Error!\n Repeat input\n");
        goto st;
    }

    t = NULL;

    printf("Insert Key: ");
    for( i = 0; i < nn; i++)
    {
         while (1)
    {
        if (getInt(&j) == 0) printf("Error! Repeat input\n");
        else break;
    }
        if (find(j,t) == NULL) t = insert( j, t );
        else
        {
            printf("Error! That key exist\n");
            i--;
        }
        printf("Insert next key: ");
    }
    printf(" into the tree\n\n");

    display_avl(t);

    int ch = 0;
  while (1) {
    ch = dialog(menu, N);
    if (ch == 5) break;
    switch (ch)
        {
        case 1:
            display_avl(t);
            break;

        case 2:
            printf("Insert Key: ");
            while (1)
    {
        if (getInt(&j) == 0) printf("Error! Repeat input\n");
        else break;
    }
        t = insert( j, t );
            break;

        case 3:
            printf("Insert Key: ");
            while (1)
    {
        if (getInt(&j) == 0) printf("Error! Repeat input\n");
        else break;
    }
            if ((f = find(j,t)) == NULL) printf("Not exist\n");
            else printf("Find Key %d, info %s, father %d\n",f->key,f->info,pf->key);
            break;

        case 4:
            printf("Enter delete key: ");
            getInt(&j);
            printf("\n");
           t=delete(j,t);
           if (t == NULL)
           {
               printf("no nodes\n");
           }
            break;

        case 6:
           // SaveTabble(&table,filename);
            break;
        case 7 :
            PrintTree(t);
            break;

        case 8:
            printf("From which key :");
            getInt(&j);
            printf("\n");
            f=find(j,t);
           PrintTree(f);
            break;
        case 9:
            SH(t);
            printf("Height is %d",t->height);
           break;
        }

  }

    dispose(t);

    return 0;
}

/*
    удалить все узлы дерева AVL
*/
void dispose(node* t)
{
    if( t != NULL )
    {
        dispose( t->left );
        dispose( t->right );
        free( t );
    }
}

/*
    найти ключ определенного узла в дереве
*/
node* find(int e, node* t )
{
    if( t == NULL )
        return NULL;
    if( e < t->key ){
            pf=t;
        return find( e, t->left );
    }
    else if( e > t->key ) {
            pf=t;
        return find( e, t->right );
    }
    else
        return t;
}

/*
    найти минимальный ключ узла
*/
node* find_min( node* t )
{
    if( t == NULL )
        return NULL;
    else if( t->left == NULL )
        return t;
    else
        return find_min( t->left );
}

/*
    найти максимальный ключ узла
*/
node* find_max( node* t )
{
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;

    return t;
}

/*
    получить высоту узла
*/
static int height( node* n )
{
    if( n == NULL )
        return -1;
    else
        return n->height;
}

/*
    получить максимальное значение двух целых чисел
*/
static int max( int l, int r)
{
    return l > r ? l: r;
}


/*
   выполнить поворот между узлом k2 и его левым дочерним элементом

    примечание: вызовите single_rotate_with_left только в том случае, если у узла k2 есть левый дочерний элемент
*/

static node* single_rotate_with_left( node* k2 )
{
    node* k1 = NULL;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    return k1; /* new root */
}

/*
   выполнить поворот между узлом (k1) и его правым дочерним элементом

    примечание: вызовите single_rotate_with_right, только если
    узел k1 имеет правого потомка
*/

static node* single_rotate_with_right( node* k1 )
{
    node* k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;

    return k2;  /* New root */
}

/*

    выполнить двойной поворот влево-вправо,

    примечание: вызывайте double_rotate_with_left, только если узел k3 имеет
    левый дочерний элемент, а левый дочерний элемент k3 имеет правый дочерний элемент
*/

static node* double_rotate_with_left( node* k3 )
{
    /* Поворот между k1 и k2 */
    k3->left = single_rotate_with_right( k3->left );

    /* Поворот между K3 и k2 */
    return single_rotate_with_left( k3 );
}

/*
    выполнить двойное вращение вправо-влево

   примечания: вызывайте double_rotate_with_right, только если k1 имеет
   правый ребенок, а правый ребенок k1 имеет левого ребенка
*/



static node* double_rotate_with_right( node* k1 )
{
    /* вращаться между K3 и k2 */
    k1->right = single_rotate_with_left( k1->right );

    /* вращаться между k1 и k2 */
    return single_rotate_with_right( k1 );
}

/*
    вставить новый узел в дерево
*/
node* insert(int e, node* t )
{

    if( t == NULL )
    {
        /* Создание и возврат дерева с одним узлом */
        t = (node*)malloc(sizeof(node));
        if( t == NULL )
        {
            fprintf (stderr, "Out of memory!!! (insert)\n");
            exit(1);
        }
        else
        {
            t->key = e;
            printf("info: ");
            t->info = getStr();
            printf("\n");
            t->height = 0;
            t->left = t->right = NULL;
        }
    }
    else if( e < t->key )
    {
        t->left = insert( e, t->left );
        if( height( t->left ) - height( t->right ) == 2 )
            if( e < t->left->key )
                t = single_rotate_with_left( t );
            else
                t = double_rotate_with_left( t );
    }
    else if( e > t->key )
    {
        t->right = insert( e, t->right );
        if( height( t->right ) - height( t->left ) == 2 )
            if( e > t->right->key )
                t = single_rotate_with_right( t );
            else
                t = double_rotate_with_right( t );
    }
    /* В противном случае X уже находится в дереве; мы ничего не будем делать */

    t->height = max( height( t->left ), height( t->right ) ) + 1;
    return t;
}

/*
    удалить узел в дереве
*/
node* delete( int e, node* t )
{
    node *cur, *par, *grp;
    if (cur = find(e,t) == NULL)
    {
        printf("Not exist\n");
        return NULL;
    }
    else printf ("key exist\n");
    if (t->key == e)
    {
        if (t->left == NULL && t->right == NULL)
        {
            printf("net detey\n");
            free(t);
            return NULL;
        }
        if (t->left != NULL)
        {
            par = t;
            cur = t->left;
            if (cur->right != NULL)
            {
                if (cur->left != NULL)
                {
                    grp = t;
                    while (cur->right != NULL)
                    {
                        par=cur;
                        cur = cur->right;
                    }
                    if (cur->left != NULL)
                    {
                        par->right = cur->left;
                        cur->left = grp->left;
                        cur->right = grp->right;
                        SH(cur);
                        if (height( cur->right ) - height( cur->left ) == 2) cur = double_rotate_with_right(cur);
                        grp->left = NULL;
                        grp->right = NULL;
                        grp->key = 0;
                        free (grp);
                        return cur;

                    }
                    else
                    {
                        cur->left = t->left;
                        cur->right = t->right;
                        par->right = NULL;
                        SH(cur);
                        if (height( cur->right ) - height( cur->left ) == 2) cur = double_rotate_with_right(cur);
                        grp->left = NULL;
                        grp->left = NULL;
                        grp->key = 0;
                        free (grp);
                        return cur;
                    }
                }
                else
                {
                    grp=par;
                    par=cur;
                    cur=par->right;
                    cur->left = par;
                    cur->right = grp->right;
                    free(grp);
                    SH(cur);
                    if (height( cur->right ) - height( cur->left ) == 2) cur = double_rotate_with_right(cur);
                    return cur;
                }
            }
            else
            {
                if (cur->left != NULL)
                {
                    grp = par;
                    par = cur;
                    cur = par->left;
                    par->right=grp->right;
                    free (grp);
                    if(height( cur->right ) - height( cur->left ) == 2) cur = double_rotate_with_right(par);
                    else par->height = max( height( par->left ), height( par->right ) ) + 1;
                    SH(par);
                    return par;

                }
                else
                {
                    cur->right = t->right;
                    t->right = NULL;
                    t->left = NULL;
                    free (t);
                    if (cur->right->left != NULL || cur->right->right != NULL ) cur = single_rotate_with_right(cur);
                    return cur;
                }
            }
        }
        else
        {
        if (t->right != NULL)
        {
            cur = t->right;
            cur->height = 0;
            t->right = NULL;
            free (t);
            return cur;
        }
        else {
            printf("All nodes deleted\n");
            free (t);
            return 0;
        }
        }

    }
    else
    {
    if (e < t->key)
    {
        cur = t->left;
        par = t;
        if (cur->key == e)
        {
            if (cur->left == NULL && cur->right == NULL)
            {
                par->left = NULL;
                free (cur);
                SH(par);
                if (par->right->height == 2) par = single_rotate_with_right(par);
                return t;
            }

            if (cur->right != NULL)
            {
                grp = par;
                par = cur;
                cur = cur->right;
                if (par->left == NULL)
                {
                    grp->left = cur;
                    par->right = NULL;
                    free(par);
                    SH(grp);
                    if (grp->right->height == 2) grp = single_rotate_with_right(grp);
                    return grp;
                }
                else
                {
                    while (cur->left != NULL)
                    {
                        par = cur;
                        cur = cur->left;
                    }
                    par->left = cur->right;
                    cur->right = grp->left->right;
                    cur->left = grp->left->left;
                    par = grp->left;
                    grp->left = cur;
                    free (par);
                    SH(grp);
                    if (grp->right->height == 2) grp = single_rotate_with_right(grp);
                    return grp;
                }
            }
            else //cur->left != NULL
            {
                grp = par;
                par = cur;
                cur = cur->left;
                grp->left = cur;
                free (par);
                SH(grp);
                if (grp->right->height == 2) grp = single_rotate_with_right(grp);
                return grp;
            }

        }
        if (cur->left == NULL && cur->right == NULL) return NULL;
        else
        {
            cur=delete(e,cur);
            return t;
        }



    }
    if (e > t->key)
    {
        cur = t->right;
        par = t;
        if (cur->key == e)
        {
            if (cur->left == NULL && cur->right == NULL)
            {
                par->left = NULL;
                free (cur);
                SH(par);
                if (par->right->height == 2) par = single_rotate_with_right(par);
                return t;
            }
            if (cur->left != NULL)
            {
                grp = par;
                par = cur;
                cur = cur->left;
                if (par->right == NULL)
                {
                    grp->right = cur;
                    par->left = NULL;
                    free(par);
                    SH(grp);
                    if (grp->left->height == 2) grp = single_rotate_with_left(grp);
                    return grp;
                }
                else
                {
                    while (cur->right != NULL)
                    {
                        par = cur;
                        cur = cur->right;
                    }
                    par->right = cur->left;
                    cur->left = grp->right->left;
                    cur->right = grp->right->right;
                    par = grp->right;
                    grp->right = cur;
                    free (par);
                    SH(grp);
                    if (grp->left->height == 2) grp = single_rotate_with_left(grp);
                    return grp;
                }
            }
            else //cur->right != NULL
            {
                grp = par;
                par = cur;
                cur = cur->right;
                grp->right = cur;
                free (par);
                SH(grp);
                if (grp->left->height == 2) grp = single_rotate_with_left(grp);
                return grp;
            }
        }
        if (cur->left == NULL && cur->right == NULL) return NULL;
        else
        {
            cur=delete(e,cur);
            return t;
        }
    }
    }
}

node* Ndelete( int e, node* t )
{
     node *cur, *par, *grp;
     pf = NULL;
    if (cur = find(e,t) == NULL)
    {
        printf("Not exist\n");
        return NULL;
    }
    else printf ("key exist\n");
    printf("prost\n");
    if (cur->right != NULL) printf("pravo ne pusto\n");
    if (cur->right == NULL) printf("pravo pusto\n");
    if (cur->right == NULL && cur->left == NULL)
    {
        printf("pered pf null\n");
        if (pf == NULL)
            {
                printf("All nodes deleted\n");
                free(cur);
                return NULL;
            }
            printf("pedef if\n");
        if (pf->key > cur->key) pf->left = NULL;
        else pf->right = NULL;
        cur->key = 0;
        free (cur);
        SH(t);
        if (t->left->height - t->right->height == 2) t=double_rotate_with_left(t);
        if (t->left->height - t->right->height == -2) t=double_rotate_with_right(t);
        printf("pered retern\n");
        return t;
    }


    t=delete(e,t);
    return t;

}

/*
    Рекурсивно отображать дерево или поддерево AVL
*/
void display_avl(node* t)
{
    if (t == NULL)
        return;
    printf("Height: %d Key: %d, info: %s",t->height,t->key,t->info);

    if(t->left != NULL)
        printf("(L:%d)",t->left->key);
    if(t->right != NULL)
        printf("(R:%d)",t->right->key);
    printf("\n");

    display_avl(t->left);
    display_avl(t->right);
}

int getInt(int *a) // getInt(&m)
{
  int n;
  do {
    n = scanf("%d", a);
    scanf("%*c");
    if (n < 0)
      return 0;
    if (n == 0) {
      printf("%s\n", "Error! Repeat input");
      scanf("%*c");
    }
  } while (n == 0);
  return 1;
}

char *getStr() //info = getStr(); char *info
{
  char buf[21];
  char *data = NULL;
  int num, len = 0;
  do {
    num = scanf("%20[^\n]", buf);
    if (num == -1) return NULL;
    if (num == 0) return data;
    len += strlen(buf) + 1;
    data = (char *)realloc(data, len * sizeof(char));
    if (data == NULL) return NULL;

    if (len <= 21) memcpy(data, buf, strlen(buf) + 1);
    else memcpy((data + strlen(data)), buf, strlen(buf) + 1);
  } while (num == 1);
  return data;
}

int dialog(const char *menu[], int n) {
  char *error = "";
  int rc;
  int i, m;

  do {
    puts(error);
    error = "Wrong number, repeat.";
    for (i = 0; i < n; ++i)
    puts(menu[i]);
    printf("--> ");
    m = getInt(&rc);
    printf("\n");
    if (m == 0)
      rc = 4;
  } while(rc < 0 || rc > n);

  return rc;
}

void SH (node *t)
{
    node *c;
    if (t->left != NULL)
    {
        c = t->left;
        SH(c);
    }
    if (t->right != NULL)
    {
        c = t->right;
        SH(c);
    }
    if (t->right == NULL && t->left == NULL) t->height = 0;
    else t->height = max( height( t->left ), height( t->right ) ) + 1;
}

void PrintTree (node *t)
{
    int a[10] = {0};
    printf("Draws only up to 2 heights and two-digit keys\n");
    switch (t->height)
    {
    case 0:
        printf("          |%2.2d|\n",t->key);
        break;
    case 1:
        printf("          |%2.2d|\n",t->key);
        printf("          /   \\\n");
        if (t->left != NULL && t->right != NULL) printf("      |%2.2d|     |%2.2d|\n",t->left->key,t->right->key);
        if (t->left != NULL && t->right == NULL) printf("      |%2.2d|     |  |\n",t->left->key);
        if (t->left == NULL && t->right != NULL) printf("      |  |     |%2.2d|\n",t->right->key);
        break;
    case 2:
        printf("          |%2.2d|\n",t->key);
        printf("          /   \\\n");
        printf("      |%2.2d|     |%2.2d|\n",t->left->key,t->right->key);
        printf("      /  \\     /   \\\n");
        if (t->left->left != NULL) a[1] = 1;
        if (t->left->right != NULL) a[2] = 1;
        if (t->right->left != NULL) a[3] = 1;
        if (t->right->right != NULL) a[4] = 1;
        if (a[1] && a[2] && a[3] && a[4])
        {
            printf("  |%2.2d| |%2.2d|  |%2.2d| |%2.2d|\n", t->left->left->key, t->left->right->key, t->right->left->key, t->right->right->key);
            break;
        }
        if (a[2] && a[3] && a[4])
        {
            printf("  |  | |%2.2d|  |%2.2d| |%2.2d|\n", t->left->right->key, t->right->left->key, t->right->right->key);
            break;
        }
        if (a[1] && a[3] && a[4])
        {
            printf("  |%2.2d| |  |  |%2.2d| |%2.2d|\n", t->left->left->key, t->right->left->key, t->right->right->key);
            break;
        }
        if (a[1] && a[2] && a[4])
        {
            printf("  |%2.2d| |%2.2d|  |  | |%2.2d|\n", t->left->left->key, t->left->right->key, t->right->right->key);
            break;
        }
        if (a[1] && a[2] && a[3])
        {
            printf("  |%2.2d| |%2.2d|  |%2.2d| |  |\n", t->left->left->key, t->left->right->key, t->right->left->key);
            break;
        }
        if (a[3] && a[4])
        {
            printf("  |  | |  |  |%2.2d| |%2.2d|\n", t->right->left->key, t->right->right->key);
            break;
        }
        if (a[2] && a[4])
        {
            printf("  |  | |%2.2d|  |  | |%2.2d|\n", t->left->right->key, t->right->right->key);
            break;
        }
        if (a[2] && a[3])
        {
            printf("  |  | |%2.2d|  |%2.2d| |  |\n", t->left->right->key, t->right->left->key);
            break;
        }
        if (a[1] && a[4])
        {
            printf("  |%2.2d| |  |  |  | |%2.2d|\n", t->left->left->key, t->right->right->key);
            break;
        }
        if (a[1] && a[3])
        {
            printf("  |%2.2d| |  |  |%2.2d| |  |\n", t->left->left->key, t->right->left->key);
            break;
        }
        if (a[1] && a[2])
        {
            printf("  |%2.2d| |%2.2d|  |  | |  |\n", t->left->left->key, t->left->right->key);
            break;
        }
        if (a[1])
        {
            printf("  |%2.2d| |  |  |  | |  |\n", t->left->left->key);
            break;
        }
        if (a[2])
        {
            printf("  |  | |%2.2d|  |  | |  |\n", t->left->right->key);
            break;
        }
        if (a[3])
        {
            printf("  |  | |  |  |%2.2d| |  |\n", t->right->left->key);
            break;
        }
        if (a[4])
        {
            printf("  |  | |  |  |  | |%2.2d|\n",t->right->right->key);
            break;
        }
    }
    /*
    printf("          |%2d|\n",t->key);
    printf("          /   \\\n");
    if (t->left != NULL && t->right != Null) printf("      |%2d|     |%2d|\n",t->left->key,t->right->key);
    else
    {
        if (t->right == NULL)
    }
     printf("      /  \\     /   \\\n");
     printf("  |%2d| |%2d|  |%2d| |%2d|\n", t->left->left->key, t->left->right->key, t->right->left->key, t->right->right->key);
     printf("   / \\  / \\    / \\  / \\\n");
     printf("|%2d|%2d|%2d|%2d|%2d|%2d|%2d|%2d|\n",t->left->left->left->key, t->left->left->right->key, t->left->right->left->key, t->left->right->right->key, t->right->left->left->key, t->right->left->right->key, t->right->right->left->key, t->right->right->right->key);
     */
}
